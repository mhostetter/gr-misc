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
#include "m_ary_slicer_impl.h"
#include <volk/volk.h>

namespace gr {
  namespace misc {

    m_ary_slicer::sptr
    m_ary_slicer::make(int M, std::vector<uint8_t> slice_map, float center, float deviation)
    {
      return gnuradio::get_initial_sptr
        (new m_ary_slicer_impl(M, slice_map, center, deviation));
    }

    /*
     * The private constructor
     */
    m_ary_slicer_impl::m_ary_slicer_impl(int M, std::vector<uint8_t> slice_map, float center, float deviation)
      : gr::sync_block("m_ary_slicer",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(uint8_t)))
    {
      d_M = M;
      d_slice_map = slice_map;
      d_center = center;
      d_deviation = deviation;

      d_mask = ((uint8_t) M) - 1;

      // TODO: explain shifting and slicing
      if(d_M == 2) {
        d_deviation = 0.0f;
      }

      d_alignment = volk_get_alignment();
      const int alignment_multiple = d_alignment/sizeof(gr_complex);
      set_alignment(std::max(1, alignment_multiple));
    }

    /*
     * Our virtual destructor.
     */
    m_ary_slicer_impl::~m_ary_slicer_impl()
    {
    }

    int
    m_ary_slicer_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      uint8_t *out = (uint8_t *) output_items[0];

      float temp;
      for(int i=0; i<noutput_items; i++) {
        // Adjust to center and shift up to that the lowest section is below 0
        temp = in[i] - d_center + (d_M/2 - 1)*d_deviation;
        if(temp < 0) {
          out[i] = d_slice_map[0] & d_mask;
        }
        else if(temp > (d_M-1)*d_deviation) {
          out[i] = d_slice_map[d_M-1] & d_mask;
        }
        else {
          out[i] = d_slice_map[temp/d_deviation] & d_mask;
        }
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace misc */
} /* namespace gr */

