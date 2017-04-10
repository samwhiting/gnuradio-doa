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
#include "multiply_exp_cc_impl.h"

namespace gr {
  namespace doa {

    multiply_exp_cc::sptr
    multiply_exp_cc::make(float arg)
    {
      return gnuradio::get_initial_sptr
        (new multiply_exp_cc_impl(arg));
    }

    /*
     * The private constructor
     */
    multiply_exp_cc_impl::multiply_exp_cc_impl(float arg)
      : gr::sync_block("multiply_exp_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)))
    {
      set_arg(arg);

      // a message port to reset the argument
      message_port_register_in(pmt::mp("arg"));
      set_msg_handler(pmt::mp("arg"), boost::bind(&multiply_exp_cc_impl::handle_arg, this, _1));
    }

    /*
     * Our virtual destructor.
     */
    multiply_exp_cc_impl::~multiply_exp_cc_impl()
    {
    }

    void
    multiply_exp_cc_impl::handle_arg(pmt::pmt_t arg) {
        if (pmt::is_number(arg)) {
            float value = (float)pmt::to_double(arg);
            set_arg(value);
        } else {
            GR_LOG_WARN(d_logger, boost::format("Exp arg message must be a number"));
        }
    }

    void multiply_exp_cc_impl::set_arg(float new_arg) {
        if (new_arg != d_arg) {
            d_arg = new_arg;
        }
    }

    int
    multiply_exp_cc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

      // Do <+signal processing+>
      const gr_complex imag(0, 1);
      gr_complex exp1 = std::exp(imag*d_arg);
      for (int i=0; i<noutput_items; ++i){
        out[i] = in[i]*exp1;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace doa */
} /* namespace gr */

