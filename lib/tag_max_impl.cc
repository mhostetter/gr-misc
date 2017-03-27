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
#include "tag_max_impl.h"
#include <volk/volk.h>

namespace gr {
  namespace misc {

    tag_max::sptr
    tag_max::make(float thresh, int look_ahead, int tag_offset, int post_tag_blank, const std::string& tag_name)
    {
      return gnuradio::get_initial_sptr
        (new tag_max_impl(thresh, look_ahead, tag_offset, post_tag_blank, tag_name));
    }

    /*
     * The private constructor
     */
    tag_max_impl::tag_max_impl(float thresh, int look_ahead, int tag_offset, int post_tag_blank, const std::string& tag_name)
      : gr::sync_block("tag_max",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float))),
        d_thresh(thresh),
        d_look_ahead(look_ahead),
        d_tag_offset(tag_offset),
        d_post_tag_blank(post_tag_blank),
        d_tag_name(tag_name),
        d_blank_until(0),
        d_finding_max(false),
        d_find_max_until(0xFFFFFFFFFFFFFFFF)
    {
      // set_min_noutput_items(-1*d_tag_offset + 2*d_look_ahead);
      set_min_noutput_items(1000);
      set_min_output_buffer(1000*sizeof(gr_complex));
      set_tag_propagation_policy(TPP_ALL_TO_ALL);
    }

    /*
     * Our virtual destructor.
     */
    tag_max_impl::~tag_max_impl()
    {
    }

    int
    tag_max_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];
      uint64_t i;
      uint16_t max_index;

      printf("\nnoutput_items = %d", noutput_items);
      // printf("\nlen = %d", noutput_items - d_look_ahead + d_tag_offset);

      for(i = -1*d_tag_offset; i < noutput_items - d_look_ahead; i++) {
        // out[i] = in[i]; // Input passes to output
        printf("\nin[%d]", i);

        if(nitems_read(0) + i >= d_blank_until) {
          // if(!d_finding_max) {
            // if(i < noutput_items - d_look_ahead) {
            // Good keep looking
            // Haven't seen a threshold crossing yet, look for one
            if(in[i] > d_thresh) {
              // Find the max
              volk_32f_index_max_16u(&max_index, &in[i], d_look_ahead);
              // d_finding_max = true;
              d_max_offset = nitems_read(0) + i + max_index;
              d_max = in[i + max_index];
              i += d_look_ahead; // Advance this loop
              add_item_tag(
                0,
                d_max_offset + d_tag_offset,
                pmt::string_to_symbol(d_tag_name),
                pmt::from_double((double) d_max),
                alias_pmt()
              );
              d_blank_until = d_max_offset + d_tag_offset + d_post_tag_blank;
              // d_find_max_until = nitems_read(0) + i + d_look_ahead;
            }
            // }
            // else {
            //   break;
            // }
          // }
          // else if(nitems_read(0) + i < d_find_max_until) {
          //   // Are currently searching for a max, search while valid
          //   if(in[i] > d_max) {
          //     d_max_offset = nitems_read(0) + i;
          //     d_max = in[i];
          //   }
          // }
          // else {
            // Finished searching for max
            // add_item_tag(
            //   0,
            //   d_max_offset + d_tag_offset,
            //   pmt::string_to_symbol(d_tag_name),
            //   pmt::from_double((double) d_max),
            //   alias_pmt()
            // );

            // Reset values
            // d_finding_max = false;
            // d_blank_until = d_max_offset + d_tag_offset + d_post_tag_blank;
          // }
        }
      }

      printf("\nused = %d", i + d_tag_offset);

      memcpy(out, in, sizeof(gr_complex)*(i + d_tag_offset));

      // Tell runtime system how many output items we produced.
      return (i + d_tag_offset);
    }

  } /* namespace misc */
} /* namespace gr */

