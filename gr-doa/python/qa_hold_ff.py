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

class qa_hold_ff (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        # data
        self.vector_length = 5
        self.data = (1.1,2.1,3.1,4.1,5.1)
        self.expected = (1.1,2.1,3.1,4.1,5.1)

        # blocks
        self.src = blocks.vector_source_f(self.data)
        self.hold = doa.hold_ff(False)
        self.snk = blocks.vector_sink_f()

        # connections
        self.tb.connect(self.src,self.hold,self.snk)
        self.tb.run ()

        # check data
        self.results = self.snk.data()
        self.assertFloatTuplesAlmostEqual(self.expected,self.results, 3)

    def test_002_t (self):
        # data
        self.vector_length = 5
        self.data = (1.2,2.2,3.2,4.2,5.2)
        self.expected = (0,0,0,0,0)

        # blocks
        self.src = blocks.vector_source_f(self.data)
        self.hold = doa.hold_ff(True)
        self.snk = blocks.vector_sink_f()

        # connections
        self.tb.connect(self.src,self.hold,self.snk)
        self.tb.run ()

        # check data
        self.results = self.snk.data()
        self.assertFloatTuplesAlmostEqual(self.expected,self.results)

if __name__ == '__main__':
    gr_unittest.run(qa_hold_ff, "qa_hold_ff.xml")
