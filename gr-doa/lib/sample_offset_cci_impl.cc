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
#include "sample_offset_cci_impl.h"
#include <algorithm>

namespace gr {
  namespace doa {

    sample_offset_cci::sptr
    sample_offset_cci::make(int vector_len, int num_xcorr)
    {
      return gnuradio::get_initial_sptr
        (new sample_offset_cci_impl(vector_len, num_xcorr));
    }

    /*
     * The private constructor
     */
    sample_offset_cci_impl::sample_offset_cci_impl(int vector_len, int num_xcorr)
      : gr::sync_block("sample_offset_cci",
              gr::io_signature::make(2, 2, sizeof(gr_complex)*vector_len),
              gr::io_signature::make(1, 1, sizeof(int)))
    {
        d_vector_len = vector_len;
        d_fft_width = d_vector_len*2-1;
        d_num_xcorr = num_xcorr;
        d_which = 0;
        d_shift = 0;
        d_results = new int[d_num_xcorr];
        d_buffer1 = new gr_complex[d_fft_width];
        d_buffer2 = new gr_complex[d_fft_width];
        d_fft = new gr::fft::fft_complex(d_fft_width, true, 1);
        d_ifft = new gr::fft::fft_complex(d_fft_width, false, 1);

        message_port_register_in(pmt::mp("recalc"));
        set_msg_handler(pmt::mp("recalc"), boost::bind(&sample_offset_cci_impl::recalc_msg, this, _1));
    }

    /*
     * Our virtual destructor.
     */
    sample_offset_cci_impl::~sample_offset_cci_impl()
    {
        delete[] d_results;
        delete[] d_buffer1;
        delete[] d_buffer2;
        delete d_fft;
        delete d_ifft;
    }

    void sample_offset_cci_impl::recalc_msg(pmt::pmt_t msg) {
        if (pmt::is_pair(msg)) {
            pmt::pmt_t key = pmt::car(msg);
            pmt::pmt_t val = pmt::cdr(msg);
            if (pmt::eq(key, pmt::intern("recalc"))) {
                if (pmt::is_integer(val)) {
                    if (d_which > d_num_xcorr) {
                        d_num_xcorr = pmt::to_long(val);
                        delete[] d_results;
                        d_results = new int[d_num_xcorr];
                        d_which = 0;
                    }
                }
            } else {
                GR_LOG_WARN(d_logger, boost::format("Sample Offset Recalcuate message must have the key = 'recalc'; got '%1%'.") % pmt::write_string(key));
            }
        } else {
            GR_LOG_WARN(d_logger, "Sample Offset Recalculate message must be a key:value pair where the key is 'recalc'.");
        }
    }

    int sample_offset_cci_impl::get_shift(const gr_complex* &in0, const gr_complex* &in1) {
        // zero pad in0 and take fft
        memcpy(d_fft->get_inbuf(), in0, sizeof(gr_complex)*d_vector_len);
        bzero(d_fft->get_inbuf()+d_vector_len, sizeof(gr_complex)*(d_vector_len-1));
        d_fft->execute();
        memcpy(d_buffer1, d_fft->get_outbuf(), sizeof(gr_complex)*d_fft_width);

        // zero pad in1 and take fft
        memcpy(d_fft->get_inbuf(), in1, sizeof(gr_complex)*d_vector_len);
        bzero(d_fft->get_inbuf()+d_vector_len, sizeof(gr_complex)*(d_vector_len-1));
        d_fft->execute();
        memcpy(d_buffer2, d_fft->get_outbuf(), sizeof(gr_complex)*d_fft_width);

        // multiply conjugate
        for (int i=0; i<d_fft_width; ++i) {
            d_buffer1[i] *= conj(d_buffer2[i]);
        }

        // take ifft
        memcpy(d_ifft->get_inbuf(), d_buffer1, sizeof(gr_complex)*d_fft_width);
        d_ifft->execute();
        memcpy(d_buffer2, d_ifft->get_outbuf(), sizeof(gr_complex)*d_fft_width);

        // find argmax
        int argmax = 0;
        for (int i=1; i<d_fft_width; ++i) {
            if (norm(d_buffer2[argmax]) < norm(d_buffer2[i])) {
                argmax = i;
            }
        }

        return (argmax < d_fft_width/2) ? argmax : argmax - d_fft_width;
    }

    int
    sample_offset_cci_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in0 = (const gr_complex *) input_items[0];
      const gr_complex *in1 = (const gr_complex *) input_items[1];
      int *out = (int *) output_items[0];

      for (int i=0; i<noutput_items; ++i) {
          if (d_which < d_num_xcorr) {
              // do xcorr
              d_results[d_which] = get_shift(in0, in1);
              d_which++;
          }
          if (d_which == d_num_xcorr) {
              // do median
              std::sort(d_results, d_results+d_num_xcorr);
              printf("\nsorted results: [");
              for (int i=0; i<d_num_xcorr; ++i) {
                  printf("%d, ", d_results[i]);
              }
              printf("]\n");
              d_shift = d_results[d_num_xcorr/2];
              d_which++;
          }
          out[i] = d_shift;
          in0 += d_vector_len;
          in1 += d_vector_len;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace doa */
} /* namespace gr */

