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
#include "linearslope_ff_impl.h"

namespace gr {
  namespace doa {

    linearslope_ff::sptr
    linearslope_ff::make(int vector_size)
    {
      return gnuradio::get_initial_sptr
        (new linearslope_ff_impl(vector_size));
    }

    /*
     * The private constructor
     */
    linearslope_ff_impl::linearslope_ff_impl(int vector_size)
      : gr::sync_block("linearslope_ff",
              gr::io_signature::make(1, 1, sizeof(float)*vector_size),
              gr::io_signature::make(1, 1, sizeof(float))),
        d_vector_size(vector_size)
    {
        x_mean = (d_vector_size-1)/2.0;
        denominator = 0;
        float tmp;

        x_hat = new float[d_vector_size];
        for (int i=0; i<d_vector_size; ++i) {
            tmp = i - x_mean;
            x_hat[i] = tmp;
            denominator += tmp*tmp; // (X-X_mean)^2
        }
    }

    /*
     * Our virtual destructor.
     */
    linearslope_ff_impl::~linearslope_ff_impl()
    {
        delete x_hat;
    }

    float linearslope_ff_impl::slope(const float* in) {
        float y_mean = 0;
        float numerator = 0;
        for (int i=0; i<d_vector_size; ++i) {
            y_mean += in[i];
        }
        y_mean /= (float) d_vector_size;

        for (int i=0; i<d_vector_size; ++i) {
            numerator += x_hat[i] * (in[i]-y_mean);  // (x-x_mean)(y-y_mean)
        }
        return numerator/denominator;
    }

    int
    linearslope_ff_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];

      // Do <+signal processing+>
      for (int i=0; i<noutput_items; ++i) {
          out[i] = slope(in);
          in += d_vector_size;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace doa */
} /* namespace gr */

