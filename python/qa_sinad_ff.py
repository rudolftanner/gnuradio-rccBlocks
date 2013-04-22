#!/usr/bin/env python
# 
# Copyright 2013 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
import rccBlocks_swig as rccBlocks
from sinad_ff import sinad_ff
import numpy as np
from math import *

class qa_sinad_ff (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_sinad_ff(self):
	Fs = 48000
	f = 1000
	time = np.arange(0,1.0,1.0/Fs)
        src_data = 1.0*np.sin(2*pi*f*time) + 0.25*np.sin(2*pi*2*f*time)
        expected_result = 12.304
        src = gr.vector_source_f(src_data)
        SinAD = rccBlocks.sinad_ff()
        dst = gr.probe_signal_f()
        self.tb.connect(src, SinAD)
        self.tb.connect(SinAD, dst)
        self.tb.run()
        result_data = dst.data()
        self.assertEqual(expected_result, result_data)
        
        
   


if __name__ == '__main__':
    gr_unittest.run(qa_sinad_ff, "qa_sinad_ff.xml")
