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
#include "full_capon_ccf_impl.h"
#include <algorithm>
#include <numeric>

namespace gr {
  namespace doa {

    full_capon_ccf::sptr
    full_capon_ccf::make(int vec_in, int vec_out)
    {
      return gnuradio::get_initial_sptr
        (new full_capon_ccf_impl(vec_in,vec_out));
    }

    /*
     * The private constructor
     */
    full_capon_ccf_impl::full_capon_ccf_impl(int vec_in, int vec_out)
      : gr::sync_block("full_capon_ccf",
              gr::io_signature::make(2, 2, sizeof(gr_complex)*vec_in),
              gr::io_signature::make(1, 1, sizeof(float)*vec_out)),
          d_vec_in(vec_in),
          d_vec_out(vec_out)
    {}

    /*
     * Our virtual destructor.
     */
    full_capon_ccf_impl::~full_capon_ccf_impl()
    {
    }


    void full_capon_ccf_impl::capon(const gr_complex* in0, const gr_complex* in1, float* out) {

        // put in0 and in1 into vectors x1 and x2
        std::vector<gr_complex> x1(in0, in0+d_vec_in);
        std::vector<gr_complex> x2(in1, in1+d_vec_in);

        // find average value of each one
        gr_complex x1_avg = accumulate(x1.begin(), x1.end(), gr_complex(0,0)) / gr_complex(d_vec_in,0);
        gr_complex x2_avg = accumulate(x2.begin(), x2.end(), gr_complex(0,0)) / gr_complex(d_vec_in,0);

        // subtract the average value from each element
        for (int i=0; i<d_vec_in; ++i) { x1[i] -= x1_avg; }
        for (int i=0; i<d_vec_in; ++i) { x2[i] -= x2_avg; }
        
        // find conjugates of x1 and x2
        std::vector<gr_complex> x1_c, x2_c;
        x1_c.reserve(d_vec_in);
        x2_c.reserve(d_vec_in);
        for (int i=0; i<d_vec_in; ++i) { x1_c.push_back(conj(x1[i])); }
        for (int i=0; i<d_vec_in; ++i) { x2_c.push_back(conj(x2[i])); }
        
        // multiply vectors together
        std::vector<gr_complex> c11, c12, c22;
        c11.reserve(d_vec_in);
        c12.reserve(d_vec_in);
        c22.reserve(d_vec_in);
        transform(x1.begin(), x1.end(), x1_c.begin(), back_inserter(c11), std::multiplies<gr_complex>());
        transform(x1.begin(), x1.end(), x2_c.begin(), back_inserter(c12), std::multiplies<gr_complex>());
        transform(x2.begin(), x2.end(), x2_c.begin(), back_inserter(c22), std::multiplies<gr_complex>());
        
        // make covariance matrix
        std::vector<std::vector<gr_complex> > covar(2, std::vector<gr_complex>(2, 0));
        covar[0][0] = accumulate(c11.begin(), c11.end(), gr_complex(0,0)) / gr_complex(d_vec_in,0);
        covar[0][1] = accumulate(c12.begin(), c12.end(), gr_complex(0,0)) / gr_complex(d_vec_in,0);
        covar[1][1] = accumulate(c22.begin(), c22.end(), gr_complex(0,0)) / gr_complex(d_vec_in,0);
        covar[1][0] = conj(covar[0][1]);

        // invert the covariance matrix
        std::vector<std::vector<gr_complex> > inverse(2, std::vector<gr_complex>(2, 0));

        gr_complex determ = ((covar[0][0]*covar[1][1]) - (covar[0][1]*covar[1][0]));
        //gr_complex determ = ((covar[0][0]*covar[1][1]));
        
        gr_complex neg = -1; 
        inverse[0][0] = covar[1][1] / determ;
        inverse[0][1] = neg * covar[0][1] / determ;
        inverse[1][0] = neg * covar[1][0] / determ;
        inverse[1][1] = covar[0][0] / determ;

        // solve for every theta
        const gr_complex step = 6.28318530718/d_vec_out;
        gr_complex theta = -3.14159265359;
        const gr_complex imag(0, 1);
        for(int i=0; i<d_vec_out; ++i){
          out[i] = abs(gr_complex(1)/(inverse[0][0] + (inverse[1][0] + inverse[0][1]) * std::exp(imag*theta) + inverse[1][1] * std::exp(gr_complex(2) * imag * theta)));
          theta += step;
        }
    }


    int
    full_capon_ccf_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in0 = (const gr_complex *) input_items[0];
      const gr_complex *in1 = (const gr_complex *) input_items[1];
      float *out = (float *) output_items[0];

      for (int i=0; i<noutput_items; ++i) {
          capon(in0, in1, out);
          in0 += d_vec_in;
          in1 += d_vec_in;
          out += d_vec_out;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace doa */
} /* namespace gr */

