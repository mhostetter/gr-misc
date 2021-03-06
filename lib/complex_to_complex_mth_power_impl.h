/* -*- c++ -*- */
/* 
 * Copyright 2017 Matt Hostetter.
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

#ifndef INCLUDED_MISC_COMPLEX_TO_COMPLEX_MTH_POWER_IMPL_H
#define INCLUDED_MISC_COMPLEX_TO_COMPLEX_MTH_POWER_IMPL_H

#include <misc/complex_to_complex_mth_power.h>

namespace gr {
  namespace misc {

    class complex_to_complex_mth_power_impl : public complex_to_complex_mth_power
    {
     private:
      int d_power;

     public:
      complex_to_complex_mth_power_impl(int power);
      ~complex_to_complex_mth_power_impl();
      void set_power(int power);

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace misc
} // namespace gr

#endif /* INCLUDED_MISC_COMPLEX_TO_COMPLEX_MTH_POWER_IMPL_H */

