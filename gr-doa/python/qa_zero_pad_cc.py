#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2017 <+YOU OR YOUR COMPANY+>.
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
from gnuradio import blocks
import doa_swig as doa

class qa_zero_pad_cc (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        # data
        self.vector_length = 3
        self.vector_length_out = 5
        self.data = ((5.0 + 0.0j),(3.2 + 1.1j),(0.0 + 1.4j))
        self.expected = ((5.0 + 0.0j),(3.2 + 1.1j),(0.0 + 1.4j),(0.0 + 0.0j),(0.0 + 0.0j))
 
        # blocks
        self.src = blocks.vector_source_c(self.data,False,self.vector_length)
        self.zero = doa.zero_pad_cc(self.vector_length,self.vector_length_out)
        self.snk = blocks.vector_sink_c(self.vector_length_out)

        # connections
        self.tb.connect(self.src, self.zero,self.snk)
        self.tb.run ()

        # check data
        self.results = self.snk.data()
        self.assertComplexTuplesAlmostEqual(self.expected,self.results,3)


if __name__ == '__main__':
    gr_unittest.run(qa_zero_pad_cc, "qa_zero_pad_cc.xml")
