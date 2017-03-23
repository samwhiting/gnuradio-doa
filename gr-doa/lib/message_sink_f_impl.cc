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
#include "message_sink_f_impl.h"

namespace gr {
  namespace doa {

    message_sink_f::sptr
    message_sink_f::make()
    {
      return gnuradio::get_initial_sptr
        (new message_sink_f_impl());
    }

    /*
     * The private constructor
     */
    message_sink_f_impl::message_sink_f_impl()
      : gr::sync_block("message_sink_f",
              gr::io_signature::make(1, -1, sizeof(float)),
              gr::io_signature::make(0, 0, 0))
    {
        message_port_register_out(pmt::mp("out"));
        set_max_noutput_items(1);
    }

    /*
     * Our virtual destructor.
     */
    message_sink_f_impl::~message_sink_f_impl()
    {
    }

    int
    message_sink_f_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];

      message_port_pub(pmt::mp("out"), pmt::mp(in[0]));

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace doa */
} /* namespace gr */

