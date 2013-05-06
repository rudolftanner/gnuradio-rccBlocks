/* -*- c++ -*- */
/* 
 * Copyright 2013 <+YOU OR YOUR COMPANY+>.
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

#include <gr_io_signature.h>
#include "channelModel_cc_impl.h"

namespace gr {
  namespace rccBlocks {

    channelModel_cc::sptr
    channelModel_cc::make(int seed, float fD, float pwr, bool flag_indep)
    {
      return gnuradio::get_initial_sptr (new channelModel_cc_impl(seed, fD, pwr, flag_indep));
    }
static const int MIN_IN = 1;	// mininum number of input streams
static const int MAX_IN = 1;	// maximum number of input streams
static const int MIN_OUT = 1;	// minimum number of output streams
static const int MAX_OUT = 1;	// maximum number of output streams

    /*
     * The private constructor
     */
    channelModel_cc_impl::channelModel_cc_impl(int seed, float fD, float pwr, bool flag_indep)
      : gr_sync_block("channelModel_cc",
		      gr_make_io_signature(MIN_IN, MAX_IN, sizeof (gr_complex)),
		      gr_make_io_signature(MIN_IN, MAX_IN, sizeof (gr_complex)))
    {
	    mychan = new flat_rayleigh(seed, fD, pwr, flag_indep);	
    }

    /*
     * Our virtual destructor.
     */
    channelModel_cc_impl::~channelModel_cc_impl()
    {
	    // frees the allocated memory.
		delete mychan;
    }

    int
    channelModel_cc_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        Complex *in = (Complex *) input_items[0];
		Complex *out = (Complex *) output_items[0];

        
		// Performs the channel fading.
		mychan->pass_through(noutput_items, in, out);
        // Tell runtime system how many input items we consumed on
        // each input stream.

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace rccBlocks */
} /* namespace gr */
