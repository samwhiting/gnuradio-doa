/* -*- c++ -*- */
/* 
 * Copyright 2016 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "cub_delay_cc_impl.h"

namespace gr {
  namespace doa {

    cub_delay_cc::sptr
    cub_delay_cc::make(int samp_rate, float delay)
    {
      return gnuradio::get_initial_sptr
        (new cub_delay_cc_impl(samp_rate, delay));
    }

    /*
     * The private constructor
     */
    cub_delay_cc_impl::cub_delay_cc_impl(int samp_rate, float delay)
      : gr::sync_block("cub_delay_cc",
              gr::io_signature::make(2, 2, sizeof(gr_complex)),
              gr::io_signature::make(2, 2, sizeof(gr_complex))),
        d_samp_rate(samp_rate),
        buffer(),
        points()
    {
        set_dly(delay);
        curr_offset=0;

        message_port_register_in(pmt::mp("reset"));
        set_msg_handler(pmt::mp("reset"), boost::bind(&cub_delay_cc_impl::reset, this, _1));
    }

    /*
     * Our virtual destructor.
     */
    cub_delay_cc_impl::~cub_delay_cc_impl()
    {
    }

    gr_complex cub_delay_cc_impl::interpolate(const gr_complex &p0, const gr_complex &p1, const gr_complex &p2, const gr_complex &p3, float mu) {
        gr_complex a0, a1, a2;
        float mu2;
        mu2 = mu*mu;
        a0 = p3 - p2 - p0 + p1;
        a1 = p0 - p1 - a0;
        a2 = p2 - p0;
        
        return (a0*mu*mu2 + a1*mu2 + a2*mu + p1);
    }

    void cub_delay_cc_impl::set_dly(float new_delay) {
        if (new_delay != d_delay) {
            gr::thread::scoped_lock l(d_mutex_delay);
            d_delay = new_delay;
            offset = fabs(d_delay) / (double) d_samp_rate;
            //printf("\n<><><><><><><><><><><><>\n");
            //printf("new delay: %f\n", new_delay);
            //printf("new offset: %f\n", offset);
        }
    }

    void cub_delay_cc_impl::reset(pmt::pmt_t msg) {
        gr::thread::scoped_lock l(d_mutex_delay);
        if (pmt::is_symbol(msg)) {
            if (pmt::eq(msg, pmt::intern("reset_buffer"))) {
                std::queue<gr_complex> empty;
                std::swap(buffer, empty);
                points.clear();
            } else {
                GR_LOG_WARN(d_logger, boost::format("Cubic Delay Buffer Reset message must be 'reset_buffer'; got '%1%'.") % pmt::write_string(msg));
            }
        } else if (pmt::is_pair(msg)) {
            pmt::pmt_t key = pmt::car(msg);
            pmt::pmt_t val = pmt::cdr(msg);
            if (pmt::eq(key, pmt::intern("reset_buffer"))) {
                if (pmt::is_integer(val)) {
                    std::queue<gr_complex> empty;
                    std::swap(buffer, empty);
                    points.clear();
                }
            } else {
                GR_LOG_WARN(d_logger, boost::format("Cubic Delay Buffer Reset message must have the key = 'reset_buffer'; got '%1%'.") % pmt::write_string(key));
            }
        } else {
            GR_LOG_WARN(d_logger, "Cubic Delay Buffer Reset message must be either a string or a key:value pair where the key is 'reset_buffer'.");
        }
    }

    int
    cub_delay_cc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      gr::thread::scoped_lock l(d_mutex_delay);

      const gr_complex *ref_in;
      const gr_complex *in;
      gr_complex *ref_out;
      gr_complex *out;

      if (d_delay >= 0) {
          ref_in = (const gr_complex *) input_items[1];
          in = (const gr_complex *) input_items[0];
          ref_out = (gr_complex *) output_items[1];
          out = (gr_complex *) output_items[0];
      } else {
          ref_in = (const gr_complex *) input_items[0];
          in = (const gr_complex *) input_items[1];
          ref_out = (gr_complex *) output_items[0];
          out = (gr_complex *) output_items[1];
      }

      if (points.empty()) {
          points.push_back(gr_complex(0,0));
          points.push_back(gr_complex(0,0));
          points.push_back(gr_complex(0,0));
          points.push_back(gr_complex(0,0));
      }

      memcpy(ref_out, ref_in, sizeof(gr_complex)*noutput_items);

      for (int i=0; i<noutput_items; ++i) {
          buffer.push(in[i]);
          if (curr_offset > 1) {
              curr_offset--;
          } else {
              points.pop_front();
              points.push_back(buffer.front());
              buffer.pop();
          }
          out[i] = interpolate(points[0], points[1], points[2], points[3], 1-curr_offset);
          curr_offset += offset;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace doa */
} /* namespace gr */

