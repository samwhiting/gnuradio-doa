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

    /*
     * Our virtual destructor.
     */
    full_capon3_ccf_impl::~full_capon3_ccf_impl()
    {
    }

// capon method
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
        luDecomp(covar,lower,upper);

        // find the inverse of the lower matrix
        std::vector<std::vector<gr_complex> > inv_lower(3, std::vector<gr_complex>(3, 0));
        invert_lower(lower,inv_lower);

        // find the inverse of the upper matrix
        std::vector<std::vector<gr_complex> > inv_upper(3, std::vector<gr_complex>(3, 0));
        invert_upper(upper,inv_upper);

        /*
        // debug
        printf("\n************************************\n");
        printf("Covariance matrix:\n");
        printMatrix(covar);

        printf("\nLower matrix:\n");
        printMatrix(lower);

        printf("\nUpper matrix:\n");
        printMatrix(upper);

        printf("\nLower matrix inverse:\n");
        printMatrix(inv_lower);

        printf("\nUpper matrix inverse:\n");
        printMatrix(inv_upper);
        printf("\n************************************\n");
        */

        // solve for every theta
        const gr_complex step = 6.28318530718/d_vec_out;
        gr_complex theta = -3.14159265359;
        const gr_complex imag(0, 1);
        gr_complex exp1,exp2,exp3,exp4;
        gr_complex block1,block2,block3;

        for(int i=0; i<d_vec_out; ++i){
          exp1 = std::exp(-1.0f*imag*theta);
          exp2 = std::exp(imag*theta);
          exp3 = std::exp(-2.0f*imag*theta);
          exp4 = std::exp(2.0f*imag*theta);

          block1 = inv_upper[0][0]*inv_lower[0][0];
          block2 = (inv_upper[0][1] + inv_upper[1][1]*exp1) * (inv_lower[1][0] + inv_lower[1][1]*exp2);
          block3 = (inv_upper[0][2] + inv_upper[1][2]*exp1 + inv_upper[2][2]*exp3)*(inv_lower[2][0] + inv_lower[2][1]*exp2 + inv_lower[2][2]*exp4);

          out[i] = abs(1.0f/(block1+block2+block3)); 
          theta += step;
        }
    }
    
// decompose matrix 'original' into lower and upper matrices. 
void full_capon3_ccf_impl::luDecomp(std::vector<std::vector<gr_complex> >& original,std::vector<std::vector<gr_complex> >& lower,std::vector<std::vector<gr_complex> >& upper){

  // intialize lower to identity
  lower[0][0] = 1;lower[0][1] = 0;lower[0][2] = 0;
  lower[1][0] = 0;lower[1][1] = 1;lower[1][2] = 0;
  lower[2][0] = 0;lower[2][1] = 0;lower[2][2] = 1;

  // copy original to upper
  upper = original;

  gr_complex factor = 0;

  // clear [1][0]
  if(upper[0][0].real() == 0 && upper[0][0].imag() == 0) printf("\n\n****ERROR - DIVIDE BY ZERO ****\n\n"); //error - divide by zero
  factor = upper[1][0]/upper[0][0];
  lower[1][0] = factor; //save for lower matrix
  for(int i=0; i<3; ++i){upper[1][i] -= factor*upper[0][i];}
  
  // clear [2][0]
  factor = upper[2][0]/upper[0][0];
  lower[2][0] = factor; //save for lower matrix
  for(int i=0; i<3; ++i){upper[2][i] -= factor*upper[0][i];}
  
  // clear [2][1]
  if(upper[1][1].real() == 0 && upper[1][1].imag() == 0) printf("\n\n****ERROR - DIVIDE BY ZERO ****\n\n"); //error - divide by zero
  factor = upper[2][1]/upper[1][1];
  lower[2][1] = factor; //save for lower matrix
  for(int i=0; i<3; ++i){upper[2][i] -= factor*upper[1][i];}
  
}

// invert a lower triangular matrix with 1s on the diagonal
void full_capon3_ccf_impl::invert_lower(std::vector<std::vector<gr_complex> >& original,std::vector<std::vector<gr_complex> >& inverse){
  // gr_complex constants
  gr_complex neg_one = -1;

  // the inverse is also lower, with 1s on the diagonal
  inverse[0][0] = 1;inverse[0][1] = 0;inverse[0][2] = 0;
                    inverse[1][1] = 1;inverse[1][2] = 0;
                                      inverse[2][2] = 1;
  // easy ones are just negatives
  inverse[1][0] = neg_one*original[1][0];
  inverse[2][1] = neg_one*original[2][1];
  
  // forward sub the last
  inverse[2][0] = original[1][0] * original[2][1] - original[2][0];
}

// invert an upper triangular matrix
void full_capon3_ccf_impl::invert_upper(std::vector<std::vector<gr_complex> >& original,std::vector<std::vector<gr_complex> >& inverse){
  // gr_complex constants
  gr_complex neg_one = -1;
  gr_complex one = 1;

  // the inverse is also an upper triangle matrix
  inverse[0][0] = 1;inverse[0][1] = 0;inverse[0][2] = 0;
  inverse[1][0] = 0;inverse[1][1] = 1;inverse[1][2] = 0;
  inverse[2][0] = 0;inverse[2][1] = 0;inverse[2][2] = 1;
  
  // diagonals are inverses
  inverse[0][0] = one/original[0][0];
  inverse[1][1] = one/original[1][1];
  inverse[2][2] = one/original[2][2];

  // back sub for the rest
  inverse[1][2] = neg_one*original[1][2]/(original[2][2]*original[1][1]);
  inverse[0][1] = neg_one*original[0][1]/(original[1][1]*original[0][0]);
  inverse[0][2] = ((neg_one*original[0][1] * inverse[1][2]) - (original[0][2] * inverse[2][2])) / original[0][0];
}

// prints out a 3x3 matrix that is a 2d vector
void full_capon3_ccf_impl::printMatrix(std::vector<std::vector<gr_complex> > a){
  printf("| %7.3f%+7.3fj,%7.3f%+7.3fj,%7.3f%+7.3fj |\n",a[0][0].real(),a[0][0].imag(),a[0][1].real(),a[0][1].imag(),a[0][2].real(),a[0][2].imag());
  printf("| %7.3f%+7.3fj,%7.3f%+7.3fj,%7.3f%+7.3fj |\n",a[1][0].real(),a[1][0].imag(),a[1][1].real(),a[1][1].imag(),a[1][2].real(),a[1][2].imag());
  printf("| %7.3f%+7.3fj,%7.3f%+7.3fj,%7.3f%+7.3fj |\n",a[2][0].real(),a[2][0].imag(),a[2][1].real(),a[2][1].imag(),a[2][2].real(),a[2][2].imag());
}

    // the work function
    int full_capon3_ccf_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items){
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

