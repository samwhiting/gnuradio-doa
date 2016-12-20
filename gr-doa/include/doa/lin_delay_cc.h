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


#ifndef INCLUDED_DOA_LIN_DELAY_CC_H
#define INCLUDED_DOA_LIN_DELAY_CC_H

#include <doa/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace doa {

    /*!
     * \brief <+description of block+>
     * \ingroup doa
     *
     */
    class DOA_API lin_delay_cc : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<lin_delay_cc> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of doa::lin_delay_cc.
       *
       * To avoid accidental use of raw pointers, doa::lin_delay_cc's
       * constructor is in a private implementation
       * class. doa::lin_delay_cc::make is the public interface for
       * creating new instances.
       */
      static sptr make(int samp_rate, float delay);

      virtual float dly() const = 0;
      virtual void set_dly(float new_delay) = 0;
    };

  } // namespace doa
} // namespace gr

#endif /* INCLUDED_DOA_LIN_DELAY_CC_H */

