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
#include "zero_pad_cc_impl.h"

namespace gr {
  namespace doa {

    zero_pad_cc::sptr
    zero_pad_cc::make(int vec_len_in, int vec_len_out)
    {
      return gnuradio::get_initial_sptr
        (new zero_pad_cc_impl(vec_len_in, vec_len_out));
    }

    /*
     * The private constructor
     */
    zero_pad_cc_impl::zero_pad_cc_impl(int vec_len_in, int vec_len_out)
      : gr::sync_block("zero_pad_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)*vec_len_in),
              gr::io_signature::make(1, 1, sizeof(gr_complex)*vec_len_out)),
              d_vec_len_in(vec_len_in),
              d_vec_len_out(vec_len_out)
    {}

    /*
     * Our virtual destructor.
     */
    zero_pad_cc_impl::~zero_pad_cc_impl()
    {
    }

    int
    zero_pad_cc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

      // Do <+signal processing+>
      for (int i=0; i<noutput_items; ++i) {

          //memset(out,0,sizeof(gr_complex)*d_vec_len_out);
          memcpy(out,in,sizeof(gr_complex)*d_vec_len_in);
          memset(out+d_vec_len_in,0,sizeof(gr_complex)*(d_vec_len_out-d_vec_len_in));
          in += d_vec_len_in;
          out += d_vec_len_out;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace doa */
} /* namespace gr */

