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
#include "peak_estimator_cif_impl.h"

namespace gr {
  namespace doa {

    peak_estimator_cif::sptr
    peak_estimator_cif::make(int vector_len)
    {
      return gnuradio::get_initial_sptr
        (new peak_estimator_cif_impl(vector_len));
    }

    /*
     * The private constructor
     */
    peak_estimator_cif_impl::peak_estimator_cif_impl(int vector_len)
      : gr::sync_block("peak_estimator_cif",
              gr::io_signature::make(1, 1, sizeof(gr_complex)*vector_len),
              gr::io_signature::make2(2, 2, sizeof(int), sizeof(float))),
        d_vector_len(vector_len)
    {}

    /*
     * Our virtual destructor.
     */
    peak_estimator_cif_impl::~peak_estimator_cif_impl()
    {
    }

    double peak_estimator_cif_impl::delta(const gr_complex &left, const gr_complex &peak, const gr_complex &right) {
        gr_complex d = 0;
        d = (right - left) / (peak*2.0f - left - right);
        return -d.real();
    }

    int peak_estimator_cif_impl::peak(const gr_complex* &in) {
        int value = 0;
        int bin = 0;
        for (int i=0; i<d_vector_len; ++i) {
            if (norm(in[i]) > value) {
                value = norm(in[i]);
                bin = i;
            }
        }
        return bin;
    }

    int
    peak_estimator_cif_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      int *bins = (int *) output_items[0];
      float *deltas = (float *) output_items[1];

      int peak_bin = 0;
      for (int i=0; i<noutput_items; ++i) {
          peak_bin = peak(in);
          if (peak_bin != 0 && peak_bin != d_vector_len-1)
              deltas[i] = delta(in[peak_bin-1], in[peak_bin], in[peak_bin+1]);
          else
              deltas[i] = 0;
          bins[i] = peak_bin;
          in += d_vector_len;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace doa */
} /* namespace gr */

