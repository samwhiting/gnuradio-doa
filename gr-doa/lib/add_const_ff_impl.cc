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
#include "add_const_ff_impl.h"

namespace gr {
  namespace doa {

    add_const_ff::sptr
    add_const_ff::make()
    {
      return gnuradio::get_initial_sptr
        (new add_const_ff_impl());
    }

    /*
     * The private constructor
     */
    add_const_ff_impl::add_const_ff_impl()
      : gr::sync_block("add_const_ff",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
        d_k = 0;
        message_port_register_in(pmt::mp("msg"));
        set_msg_handler(pmt::mp("msg"), boost::bind(&add_const_ff_impl::handle_msg, this, _1));
    }

    /*
     * Our virtual destructor.
     */
    add_const_ff_impl::~add_const_ff_impl()
    {
    }

    /*
     * Change the added Constant
     */
    void
    add_const_ff_impl::set_const(float k)
    {
      if(k != d_k) {
        d_k = k;
//        printf("const set to %f\n", d_k);
      }
    }

    /*
     * Handle Messages
     */
    void
    add_const_ff_impl::handle_msg(pmt::pmt_t msg) {
        if (pmt::is_number(msg)) {
            float value = pmt::to_float(msg);
            set_const(value);
        } else {
            GR_LOG_WARN(d_logger, boost::format("Delay message must be a number"));
        }
    }

    int
    add_const_ff_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];

      int size = noutput_items;

      while (size>=8) {
        *out++ = *in++ + d_k;
        *out++ = *in++ + d_k;
        *out++ = *in++ + d_k;
        *out++ = *in++ + d_k;
        *out++ = *in++ + d_k;
        *out++ = *in++ + d_k;
        *out++ = *in++ + d_k;
        *out++ = *in++ + d_k;
        size -= 8;
      }

      while (size-- > 0) {
        *out++ = *in++ + d_k;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace doa */
} /* namespace gr */

