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

#ifndef INCLUDED_DOA_LIN_DELAY_CC_IMPL_H
#define INCLUDED_DOA_LIN_DELAY_CC_IMPL_H

#include <doa/lin_delay_cc.h>
#include <queue>

namespace gr {
  namespace doa {

    class lin_delay_cc_impl : public lin_delay_cc
    {
     private:
         gr_complex interpolate(const gr_complex &p1, const gr_complex &p2, float ratio);
         int d_samp_rate;
         float d_delay;
         std::queue<gr_complex> buffer;
         std::queue<gr_complex> points;
         double offset, curr_offset;
         gr::thread::mutex d_mutex_delay;

     public:
      lin_delay_cc_impl(int samp_rate, float delay);
      ~lin_delay_cc_impl();
      void set_dly(float new_delay);
      float dly() const { return d_delay; }

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace doa
} // namespace gr

#endif /* INCLUDED_DOA_LIN_DELAY_CC_IMPL_H */

