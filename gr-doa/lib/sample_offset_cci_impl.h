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

#ifndef INCLUDED_DOA_SAMPLE_OFFSET_CCI_IMPL_H
#define INCLUDED_DOA_SAMPLE_OFFSET_CCI_IMPL_H

#include <doa/sample_offset_cci.h>
#include <gnuradio/fft/fft.h>

namespace gr {
  namespace doa {

    class sample_offset_cci_impl : public sample_offset_cci
    {
     private:
      gr::fft::fft_complex* d_fft;
      gr::fft::fft_complex* d_ifft;
      int d_vector_len, d_num_xcorr;
      int d_fft_width;
      int d_which;
      int d_shift;
      int* d_results;

      gr_complex* d_buffer1;
      gr_complex* d_buffer2;

      void recalc_msg(pmt::pmt_t msg);
      int get_shift(const gr_complex* &in0, const gr_complex* &in1);

     public:
      sample_offset_cci_impl(int vector_len, int num_xcorr);
      ~sample_offset_cci_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace doa
} // namespace gr

#endif /* INCLUDED_DOA_SAMPLE_OFFSET_CCI_IMPL_H */

