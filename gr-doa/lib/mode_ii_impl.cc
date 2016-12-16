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
#include "mode_ii_impl.h"

namespace gr {
  namespace doa {

    mode_ii::sptr
    mode_ii::make(int vector_size, int max_value)
    {
      return gnuradio::get_initial_sptr
        (new mode_ii_impl(vector_size, max_value));
    }

    /*
     * The private constructor
     */
    mode_ii_impl::mode_ii_impl(int vector_size,int max_value)
      : gr::sync_block("mode_ii",
              gr::io_signature::make(1, 1, sizeof(int)*vector_size),
              gr::io_signature::make(1, 1, sizeof(int))),
        d_vector_size(vector_size),
        d_max_value(max_value)
    {}

    /*
     * Our virtual destructor.
     */
    mode_ii_impl::~mode_ii_impl()
    {
    }

    int mode_ii_impl::mode(const int* in) {
      int* hash = (int*)calloc(d_max_value, sizeof(int));
      int max = 0;
      
      for (int i=0; i<d_vector_size; ++i){
       if( hash[max] < ++hash[in[i]]) max = in[i]; 
      }
      
      free(hash);
      return max;
    }

    int
    mode_ii_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const int *in = (const int *) input_items[0];
      int *out = (int *) output_items[0];
 
      // Do <+signal processing+>
      for (int i=0; i<noutput_items; ++i) {
          out[i] = mode(in);
          in += d_vector_size;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace doa */
} /* namespace gr */

