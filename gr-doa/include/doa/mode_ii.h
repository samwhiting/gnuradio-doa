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


#ifndef INCLUDED_DOA_MODE_II_H
#define INCLUDED_DOA_MODE_II_H

#include <doa/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace doa {

    /*!
     * \brief <+description of block+>
     * \ingroup doa
     *
     */
    class DOA_API mode_ii : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<mode_ii> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of doa::mode_ii.
       *
       * To avoid accidental use of raw pointers, doa::mode_ii's
       * constructor is in a private implementation
       * class. doa::mode_ii::make is the public interface for
       * creating new instances.
       */
      static sptr make(int vector_size, int max_value);
    };

  } // namespace doa
} // namespace gr

#endif /* INCLUDED_DOA_MODE_II_H */

