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
#include "hold_state_ff_impl.h"

namespace gr {
  namespace doa {

    hold_state_ff::sptr
    hold_state_ff::make(int state, float scale0, float scale1)
    {
      return gnuradio::get_initial_sptr
        (new hold_state_ff_impl(state, scale0, scale1));
    }

    /*
     * The private constructor
     */
    hold_state_ff_impl::hold_state_ff_impl(int state, float scale0, float scale1)
      : gr::sync_block("hold_state_ff",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
      d_value = 0;
      d_scale0 = scale0;
      d_scale1 = scale1;
      set_state(state);

      // a message port to set the state
      message_port_register_in(pmt::mp("state"));
      set_msg_handler(pmt::mp("state"), boost::bind(&hold_state_ff_impl::handle_state, this, _1));
    }

    /*
     * Our virtual destructor.
     */
    hold_state_ff_impl::~hold_state_ff_impl()
    {
    }

    void 
    hold_state_ff_impl::set_state(int new_state) {
        if (new_state != d_state) {
            d_state = new_state;
            printf("\nnew state: %d\n",d_state);
        }
    }

    void
    hold_state_ff_impl::handle_state(pmt::pmt_t msg) {
        if (pmt::is_number(msg)) {
            int value = (int)pmt::to_long(msg);
            set_state(value);
        } else {
            GR_LOG_WARN(d_logger, boost::format("State set message must be a number"));
        }
    }

    int
    hold_state_ff_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];

      // state 1 means update value
      if(d_state == 1){
          //pass every sample through, save the last one into d_value
          for (int i=0; i<noutput_items; i++) {out[i] = in[i] * d_scale1;}
          d_value = in[noutput_items-1];
      }
      // state 0 means don't update value
      else{
          for (int i=0; i<noutput_items; i++) {out[i] = d_value * d_scale0;}
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace doa */
} /* namespace gr */

