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


#ifndef INCLUDED_DOA_SAMPLE_OFFSET_CCI_H
#define INCLUDED_DOA_SAMPLE_OFFSET_CCI_H

#include <doa/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace doa {

    /*!
     * \brief <+description of block+>
     * \ingroup doa
     *
     */
    class DOA_API sample_offset_cci : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<sample_offset_cci> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of doa::sample_offset_cci.
       *
       * To avoid accidental use of raw pointers, doa::sample_offset_cci's
       * constructor is in a private implementation
       * class. doa::sample_offset_cci::make is the public interface for
       * creating new instances.
       */
      static sptr make(int vector_len, int num_xcorr);
    };

  } // namespace doa
} // namespace gr

#endif /* INCLUDED_DOA_SAMPLE_OFFSET_CCI_H */

