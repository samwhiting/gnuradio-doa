/* -*- c++ -*- */
/* 
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
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
#include "cumulative_ff_impl.h"

namespace gr {
  namespace doa {

    cumulative_ff::sptr
    cumulative_ff::make(float start)
    {
      return gnuradio::get_initial_sptr
        (new cumulative_ff_impl(start));
    }

    /*
     * The private constructor
     */
    cumulative_ff_impl::cumulative_ff_impl(float start)
      : gr::sync_block("cumulative_ff",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float))),
        sum(start)
    {
        message_port_register_in(pmt::mp("reset"));
        set_msg_handler(pmt::mp("reset"), boost::bind(&cumulative_ff_impl::reset, this, _1));
    }

    /*
     * Our virtual destructor.
     */
    cumulative_ff_impl::~cumulative_ff_impl()
    {
    }

    void cumulative_ff_impl::reset(pmt::pmt_t msg)
    {
        if (pmt::is_pair(msg)) {
            pmt::pmt_t key = pmt::car(msg);
            pmt::pmt_t val = pmt::cdr(msg);
            if (pmt::eq(key, pmt::intern("reset_sum"))) {
                if (pmt::is_number(val)) {
                    sum = pmt::to_double(val);
                }
            } else {
                GR_LOG_WARN(d_logger, boost::format("Cumulative Sum Reset message must have the key = 'reset_sum'; got '%1%'.") % pmt::write_string(key));
            }
        } else {
            GR_LOG_WARN(d_logger, "Cumulative Sum Reset message must be a key:value pair where the key is 'reset_sum'.");
        }
    }

    int
    cumulative_ff_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];

      // Add to cumulative sum and return
      for (int i=0; i<noutput_items; ++i) {
          if (std::isfinite(in[i])) {
              sum += in[i];
          }
          out[i] = sum;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace doa */
} /* namespace gr */

