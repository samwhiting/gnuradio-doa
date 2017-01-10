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

#ifndef INCLUDED_DOA_PEAK_ESTIMATOR_CIF_IMPL_H
#define INCLUDED_DOA_PEAK_ESTIMATOR_CIF_IMPL_H

#include <doa/peak_estimator_cif.h>

namespace gr {
  namespace doa {

    class peak_estimator_cif_impl : public peak_estimator_cif
    {
     private:
      int d_vector_len;
      double delta(const gr_complex &left, const gr_complex &peak, const gr_complex &right);
      int peak(const gr_complex* &in);

     public:
      peak_estimator_cif_impl(int vector_len);
      ~peak_estimator_cif_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace doa
} // namespace gr

#endif /* INCLUDED_DOA_PEAK_ESTIMATOR_CIF_IMPL_H */

