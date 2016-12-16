#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2016 <+YOU OR YOUR COMPANY+>.
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

class qa_mode_ii (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        # data
        self.vector_length = 12
        self.data = (1,1,1,1,1,1,5,3,5,2,3,787)
        self.expected = (1)

        # blocks
        self.src = blocks.vector_source_i(self.data, False, self.vector_length)
        self.mode = doa.mode_ii(self.vector_length,1000)
        self.snk = blocks.vector_sink_i()

        # connections
        self.tb.connect(self.src, self.mode, self.snk)
        self.tb.run ()

        # check data
        self.result = self.snk.data()
        self.assertAlmostEqual(self.expected, self.result[0], 3)

    def test_002_t (self):
        # data
        self.vector_length = 3
        self.data = (2,3,4)
        self.expected = (2)

        # blocks
        self.src = blocks.vector_source_i(self.data, False, self.vector_length)
        self.mode = doa.mode_ii(self.vector_length,1000)
        self.snk = blocks.vector_sink_i()

        # connections
        self.tb.connect(self.src, self.mode, self.snk)
        self.tb.run ()

        # check data
        self.result = self.snk.data()
        self.assertAlmostEqual(self.expected, self.result[0], 3)


 
if __name__ == '__main__':
    gr_unittest.run(qa_mode_ii, "qa_mode_ii.xml")
