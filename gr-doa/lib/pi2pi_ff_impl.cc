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
#define PI 3.141593
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "pi2pi_ff_impl.h"
#include <math.h>

namespace gr {
  namespace doa {

    pi2pi_ff::sptr
    pi2pi_ff::make()
    {
      return gnuradio::get_initial_sptr
        (new pi2pi_ff_impl());
    }

    /*
     * The private constructor
     */
    pi2pi_ff_impl::pi2pi_ff_impl()
      : gr::sync_block("pi2pi_ff",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {}

    /*
     * Our virtual destructor.
     */
    pi2pi_ff_impl::~pi2pi_ff_impl()
    {
    }

    int
    pi2pi_ff_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];

      // Do <+signal processing+>
      for (int i=0; i<noutput_items; ++i) {
          out[i] = fmod(in[i]+20*PI,2*PI);
          if(out[i] > PI) out[i] -= 2*PI;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace doa */
} /* namespace gr */

