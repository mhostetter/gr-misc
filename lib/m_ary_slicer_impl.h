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

#ifndef INCLUDED_MISC_M_ARY_SLICER_IMPL_H
#define INCLUDED_MISC_M_ARY_SLICER_IMPL_H

#include <misc/m_ary_slicer.h>

namespace gr {
  namespace misc {

    class m_ary_slicer_impl : public m_ary_slicer
    {
     private:
      int d_M;
      std::vector<uint8_t> d_slice_map;
      float d_center;
      float d_deviation;
      uint8_t d_mask;
      unsigned int d_alignment;

     public:
      m_ary_slicer_impl(int M, std::vector<uint8_t> slice_map, float center, float deviation);
      ~m_ary_slicer_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace misc
} // namespace gr

#endif /* INCLUDED_MISC_M_ARY_SLICER_IMPL_H */

