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

#ifndef INCLUDED_DOA_HOLD_STATE_FF_IMPL_H
#define INCLUDED_DOA_HOLD_STATE_FF_IMPL_H

#include <doa/hold_state_ff.h>

namespace gr {
  namespace doa {

    class hold_state_ff_impl : public hold_state_ff
    {
     private:
      float d_value;
      float d_scale0;
      float d_scale1;
      int d_state;

      void handle_state(pmt::pmt_t msg);

     public:
      hold_state_ff_impl(int state, float scale0, float scale1);
      ~hold_state_ff_impl();

      void set_state(int new_state);
      int get_state() {return d_state;}

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace doa
} // namespace gr

#endif /* INCLUDED_DOA_HOLD_STATE_FF_IMPL_H */

