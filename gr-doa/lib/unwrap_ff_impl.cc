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
#include "unwrap_ff_impl.h"

namespace gr {
  namespace doa {

    unwrap_ff::sptr
    unwrap_ff::make(int vector_size, float min, float max)
    {
      return gnuradio::get_initial_sptr
        (new unwrap_ff_impl(vector_size, min, max));
    }

    /*
     * The private constructor
     */
    unwrap_ff_impl::unwrap_ff_impl(int vector_size, float min, float max)
      : gr::sync_block("unwrap_ff",
              gr::io_signature::make(1, 1, sizeof(float)*vector_size),
              gr::io_signature::make(1, 1, sizeof(float)*vector_size)),
        d_vector_size(vector_size),
        d_min(min),
        d_max(max)
    {}

    /*
     * Our virtual destructor.
     */
    unwrap_ff_impl::~unwrap_ff_impl()
    {
    }

    void
    unwrap_ff_impl::unwrap(const float* in, float* out) {
        float range = d_max - d_min;
        float threshold = range/2.0;
        int level = 0;
        float difference;
        out[0] = in[0];
        for (int i=1; i<d_vector_size; ++i) {
            difference = in[i-1]-in[i];
            if (fabs(difference) > threshold) {
                if (difference > 0) {
                    level++;
                } else {
                    level--;
                }
            }
            out[i] = in[i] + range*level;
        }
    }

    int
    unwrap_ff_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];

      // Do <+signal processing+>
      for (int i=0; i<noutput_items; ++i) {
          unwrap(in, out);
          in += d_vector_size;
          out += d_vector_size;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace doa */
} /* namespace gr */

