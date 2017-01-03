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
#include "variance_ff_impl.h"

namespace gr {
  namespace doa {

    variance_ff::sptr
    variance_ff::make(int vec_len)
    {
      return gnuradio::get_initial_sptr
        (new variance_ff_impl(vec_len));
    }

    /*
     * The private constructor
     */
    variance_ff_impl::variance_ff_impl(int vec_len)
      : gr::sync_block("variance_ff",
              gr::io_signature::make(1, 1, sizeof(float)*vec_len),
              gr::io_signature::make(1, 1, sizeof(int))),
      d_vec_len(vec_len)
    {}

    /*
     * Our virtual destructor.
     */
    variance_ff_impl::~variance_ff_impl()
    {
    }

    // return the variance of given vector
    float variance_ff_impl::variance(const float* in){
      float avg = 0;
      float var = 0;

      for(int i=0; i<d_vec_len;i++){
        avg += in[i];
      }
      
      avg /= d_vec_len;
      
      for(int i=0; i<d_vec_len;i++){
         var += (in[i]-avg)*(in[i]-avg); 
      }

      var /= (d_vec_len-1);

      return var;
    }

    int
    variance_ff_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];

      // Do <+signal processing+>
      for (int i=0; i<noutput_items; ++i) {
          out[i] = variance(in);
          in += d_vec_len;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace doa */
} /* namespace gr */

