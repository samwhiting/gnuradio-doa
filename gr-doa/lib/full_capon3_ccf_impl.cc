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
#include "full_capon3_ccf_impl.h"
#include <algorithm>
#include <numeric>

namespace gr {
  namespace doa {

    full_capon3_ccf::sptr
    full_capon3_ccf::make(int vec_in, int vec_out)
    {
      return gnuradio::get_initial_sptr
        (new full_capon3_ccf_impl(vec_in, vec_out));
    }

    /*
     * The private constructor
     */
    full_capon3_ccf_impl::full_capon3_ccf_impl(int vec_in, int vec_out)
      : gr::sync_block("full_capon3_ccf",
              gr::io_signature::make(3, 3, sizeof(gr_complex)*vec_in),
              gr::io_signature::make(1, 1, sizeof(float)*vec_out)),
        d_vec_in(vec_in),
        d_vec_out(vec_out)
    {}

    void full_capon3_ccf_impl::capon(const gr_complex* in0, const gr_complex* in1,const gr_complex* in2, float* out){

        // put in's into vectors
        std::vector<gr_complex> x1(in0, in0+d_vec_in);
        std::vector<gr_complex> x2(in1, in1+d_vec_in);
        std::vector<gr_complex> x3(in2, in2+d_vec_in);

        // find average values
        gr_complex x1_avg = accumulate(x1.begin(), x1.end(), gr_complex(0,0)) / gr_complex(d_vec_in,0);
        gr_complex x2_avg = accumulate(x2.begin(), x2.end(), gr_complex(0,0)) / gr_complex(d_vec_in,0);
        gr_complex x3_avg = accumulate(x3.begin(), x3.end(), gr_complex(0,0)) / gr_complex(d_vec_in,0);

        // make our data zero-mean
        for (int i=0; i<d_vec_in; ++i) { x1[i] -= x1_avg; }
        for (int i=0; i<d_vec_in; ++i) { x2[i] -= x2_avg; }
        for (int i=0; i<d_vec_in; ++i) { x3[i] -= x3_avg; }
        
        // find conjugates
        std::vector<gr_complex> x1_c, x2_c, x3_c;
        x1_c.reserve(d_vec_in);
        x2_c.reserve(d_vec_in);
        x3_c.reserve(d_vec_in);
        for (int i=0; i<d_vec_in; ++i) { x1_c.push_back(conj(x1[i])); }
        for (int i=0; i<d_vec_in; ++i) { x2_c.push_back(conj(x2[i])); }
        for (int i=0; i<d_vec_in; ++i) { x3_c.push_back(conj(x3[i])); }
        
        // Find variances
        std::vector<gr_complex> r11, r22, r33;
        r11.reserve(d_vec_in);
        r22.reserve(d_vec_in);
        r33.reserve(d_vec_in);

        transform(x1.begin(), x1.end(), x1_c.begin(), back_inserter(r11), std::multiplies<gr_complex>());
        transform(x2.begin(), x2.end(), x2_c.begin(), back_inserter(r22), std::multiplies<gr_complex>());
        transform(x3.begin(), x3.end(), x3_c.begin(), back_inserter(r33), std::multiplies<gr_complex>());
        
        // Find covariances
        std::vector<gr_complex> r12, r13, r23;
        r12.reserve(d_vec_in);
        r13.reserve(d_vec_in);
        r23.reserve(d_vec_in);

        transform(x1.begin(), x1.end(), x2_c.begin(), back_inserter(r12), std::multiplies<gr_complex>());
        transform(x1.begin(), x1.end(), x3_c.begin(), back_inserter(r13), std::multiplies<gr_complex>());
        transform(x2.begin(), x2.end(), x3_c.begin(), back_inserter(r23), std::multiplies<gr_complex>());
        
        // make covariance matrix
        std::vector<std::vector<gr_complex> > covar(3, std::vector<gr_complex>(3, 0));
        covar[0][0] = accumulate(r11.begin(), r11.end(), gr_complex(0,0)) / gr_complex(d_vec_in,0);
        covar[1][1] = accumulate(r22.begin(), r22.end(), gr_complex(0,0)) / gr_complex(d_vec_in,0);
        covar[2][2] = accumulate(r33.begin(), r33.end(), gr_complex(0,0)) / gr_complex(d_vec_in,0);

        covar[0][1] = accumulate(r12.begin(), r12.end(), gr_complex(0,0)) / gr_complex(d_vec_in,0);
        covar[0][2] = accumulate(r13.begin(), r13.end(), gr_complex(0,0)) / gr_complex(d_vec_in,0);
        covar[1][2] = accumulate(r23.begin(), r23.end(), gr_complex(0,0)) / gr_complex(d_vec_in,0);

        covar[1][0] = conj(covar[0][1]);
        covar[2][0] = conj(covar[0][2]);
        covar[2][1] = conj(covar[1][2]);

        // decompose the matrix into lower and upper components
        std::vector<std::vector<gr_complex> > upper(3, std::vector<gr_complex>(3, 0));
        std::vector<std::vector<gr_complex> > lower(3, std::vector<gr_complex>(3, 0));

        
        // solve for every theta
        const gr_complex step = 6.28318530718/d_vec_out;
        gr_complex theta = -3.14159265359;
        const gr_complex imag(0, 1);

//        for(int i=0; i<d_vec_out; ++i){
//          out[i] = abs(gr_complex(1)/(inverse[0][0] + (inverse[1][0] + inverse[0][1]) * std::exp(imag*theta) + inverse[1][1] * std::exp(gr_complex(2) * imag * theta)));
//          theta += step;
//        }
    }
    
    /*
     * Our virtual destructor.
     */
    full_capon3_ccf_impl::~full_capon3_ccf_impl()
    {
    }

    int
    full_capon3_ccf_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in0 = (const gr_complex *) input_items[0];
      const gr_complex *in1 = (const gr_complex *) input_items[1];
      const gr_complex *in2 = (const gr_complex *) input_items[2];
      float *out = (float *) output_items[0];

      for (int i=0; i<noutput_items; ++i) {
          capon(in0, in1, in2, out);
          in0 += d_vec_in;
          in1 += d_vec_in;
          in2 += d_vec_in;
          out += d_vec_out;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace doa */
} /* namespace gr */

