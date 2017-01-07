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
#include "capon_ccf_impl.h"
#include <algorithm>
#include <numeric>

namespace gr {
  namespace doa {

    capon_ccf::sptr
    capon_ccf::make(int vector_size)
    {
      return gnuradio::get_initial_sptr
        (new capon_ccf_impl(vector_size));
    }

    /*
     * The private constructor
     */
    capon_ccf_impl::capon_ccf_impl(int vector_size)
      : gr::sync_block("capon_ccf",
              gr::io_signature::make(2, 2, sizeof(gr_complex)*vector_size),
              gr::io_signature::make(1, 1, sizeof(float))),
        d_vector_size(vector_size)
    {}

    /*
     * Our virtual destructor.
     */
    capon_ccf_impl::~capon_ccf_impl()
    {
    }

    float capon_ccf_impl::direction(const gr_complex* in0, const gr_complex* in1) {
        // put in0 and in1 into vectors x1 and x2
        std::vector<gr_complex> x1(in0, in0+d_vector_size);
        std::vector<gr_complex> x2(in1, in1+d_vector_size);

        // find average value of each one
        gr_complex x1_avg = accumulate(x1.begin(), x1.end(), gr_complex(0,0)) / gr_complex(d_vector_size,0);
        gr_complex x2_avg = accumulate(x2.begin(), x2.end(), gr_complex(0,0)) / gr_complex(d_vector_size,0);
        // subtract the average value from each element
        for (int i=0; i<d_vector_size; ++i) { x1[i] -= x1_avg; }
        for (int i=0; i<d_vector_size; ++i) { x2[i] -= x2_avg; }
        // find conjugates of x1 and x2
        std::vector<gr_complex> x1_c, x2_c;
        x1_c.reserve(d_vector_size);
        x2_c.reserve(d_vector_size);
        for (int i=0; i<d_vector_size; ++i) { x1_c.push_back(conj(x1[i])); }
        for (int i=0; i<d_vector_size; ++i) { x2_c.push_back(conj(x2[i])); }
        // multiply vectors together
        std::vector<gr_complex> c11, c12, c22;
        c11.reserve(d_vector_size);
        c12.reserve(d_vector_size);
        c22.reserve(d_vector_size);
        transform(x1.begin(), x1.end(), x1_c.begin(), back_inserter(c11), std::multiplies<gr_complex>());
        transform(x1.begin(), x1.end(), x2_c.begin(), back_inserter(c12), std::multiplies<gr_complex>());
        transform(x2.begin(), x2.end(), x2_c.begin(), back_inserter(c22), std::multiplies<gr_complex>());
        // make covariance matrix
        std::vector<std::vector<gr_complex> > covar(2, std::vector<gr_complex>(2, 0));
        covar[0][0] = accumulate(c11.begin(), c11.end(), gr_complex(0,0)) / gr_complex(d_vector_size,0);
        covar[0][1] = accumulate(c12.begin(), c12.end(), gr_complex(0,0)) / gr_complex(d_vector_size,0);
        covar[1][1] = accumulate(c22.begin(), c22.end(), gr_complex(0,0)) / gr_complex(d_vector_size,0);
        covar[1][0] = conj(covar[0][1]);

        // find eigenvalues
        gr_complex lambda0 = (covar[0][0]+covar[1][1]+sqrt(pow((covar[0][0]+covar[1][1]),2)-gr_complex(4,0)*(covar[0][0]*covar[1][1]-covar[0][1]*covar[1][0])))/gr_complex(2,0);
        gr_complex lambda1 = (covar[0][0]+covar[1][1]-sqrt(pow((covar[0][0]+covar[1][1]),2)-gr_complex(4,0)*(covar[0][0]*covar[1][1]-covar[0][1]*covar[1][0])))/gr_complex(2,0);
        gr_complex max_lambda = (abs(lambda0) > abs(lambda1)) ? abs(lambda0) : abs(lambda1);

        return std::arg((max_lambda - covar[0][0])/covar[0][1]);
    }

    int
    capon_ccf_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in0 = (const gr_complex *) input_items[0];
      const gr_complex *in1 = (const gr_complex *) input_items[1];
      float *out = (float *) output_items[0];

      for (int i=0; i<noutput_items; ++i) {
          out[i] = direction(in0, in1);
          in0 += d_vector_size;
          in1 += d_vector_size;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace doa */
} /* namespace gr */

