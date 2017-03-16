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
#include "complex_to_complex_mth_power_impl.h"
#include <volk/volk.h>

namespace gr {
  namespace misc {

    complex_to_complex_mth_power::sptr
    complex_to_complex_mth_power::make(int power)
    {
      return gnuradio::get_initial_sptr
        (new complex_to_complex_mth_power_impl(power));
    }

    /*
     * The private constructor
     */
    complex_to_complex_mth_power_impl::complex_to_complex_mth_power_impl(int power)
      : gr::sync_block("complex_to_complex_mth_power",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)))
    {
      d_power = power;

      d_alignment = volk_get_alignment();
      const int alignment_multiple = d_alignment/sizeof(gr_complex);
      set_alignment(std::max(1, alignment_multiple));
    }

    /*
     * Our virtual destructor.
     */
    complex_to_complex_mth_power_impl::~complex_to_complex_mth_power_impl()
    {
    }

    int
    complex_to_complex_mth_power_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

      volk_32fc_x2_multiply_32fc(&out[0], &in[0], &in[0], noutput_items);
      for(int i=1; i<d_power-1; i++) {
        volk_32fc_x2_multiply_32fc(&out[0], &out[0], &in[0], noutput_items);
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace misc */
} /* namespace gr */

