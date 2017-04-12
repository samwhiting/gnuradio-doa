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
#include "phase2doa_ff_impl.h"

namespace gr {
  namespace doa {

    phase2doa_ff::sptr
    phase2doa_ff::make(float alpha)
    {
      return gnuradio::get_initial_sptr
        (new phase2doa_ff_impl(alpha));
    }

    /*
     * The private constructor
     */
    phase2doa_ff_impl::phase2doa_ff_impl(float alpha)
      : gr::sync_block("phase2doa_ff",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
      //alpha is 1/2 for half-wavelength spacing etc...
      d_alpha = alpha;
    }

    /*
     * Our virtual destructor.
     */
    phase2doa_ff_impl::~phase2doa_ff_impl()
    {
    }

    int
    phase2doa_ff_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];
      float arg;

      for(int i=0; i<noutput_items; i++) {
        // DOA = arccos(phase/(2*pi*alpha)) - pi/2
        arg = in[i]/(2*M_PI*d_alpha);
        // clip at -1 and 1 so we don't get NaNs
        if (arg>1) {arg=1;}
        else if (arg<-1) {arg=-1;}
        out[i] = acos(arg)-M_PI_2; 
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace doa */
} /* namespace gr */

