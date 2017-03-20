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

#ifndef INCLUDED_MISC_TAG_MAX_IMPL_H
#define INCLUDED_MISC_TAG_MAX_IMPL_H

#include <misc/tag_max.h>

namespace gr {
  namespace misc {

    class tag_max_impl : public tag_max
    {
     private:
      float d_thresh;
      int d_look_ahead;
      int d_tag_offset;
      int d_post_tag_blank;
      std::string d_tag_name;
      uint64_t d_blank_until;
      bool d_finding_max;
      uint64_t d_find_max_until;
      float d_max;
      uint64_t d_max_offset;

     public:
      tag_max_impl(float thresh, int look_ahead, int tag_offset, int post_tag_blank, const std::string& tag_name);
      ~tag_max_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace misc
} // namespace gr

#endif /* INCLUDED_MISC_TAG_MAX_IMPL_H */

