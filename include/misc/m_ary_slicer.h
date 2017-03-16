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


#ifndef INCLUDED_MISC_M_ARY_SLICER_H
#define INCLUDED_MISC_M_ARY_SLICER_H

#include <misc/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace misc {

    /*!
     * \brief <+description of block+>
     * \ingroup misc
     *
     */
    class MISC_API m_ary_slicer : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<m_ary_slicer> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of misc::m_ary_slicer.
       *
       * To avoid accidental use of raw pointers, misc::m_ary_slicer's
       * constructor is in a private implementation
       * class. misc::m_ary_slicer::make is the public interface for
       * creating new instances.
       */
      static sptr make(int M, std::vector<uint8_t> slice_map, float center, float deviation);
    };

  } // namespace misc
} // namespace gr

#endif /* INCLUDED_MISC_M_ARY_SLICER_H */

