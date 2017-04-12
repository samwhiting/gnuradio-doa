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

class qa_phase2doa_ff (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        # data
        self.data = (3.0000,-3.0000,1.1000,-1.1000,0)
        self.expected = (-1.2694,1.2694,-0.3577,0.3577,0)

        # blocks
        self.src = blocks.vector_source_f(self.data)
        self.p2d = doa.phase2doa_ff(.5)
        self.snk = blocks.vector_sink_f()

        # connections
        self.tb.connect(self.src, self.p2d)
        self.tb.connect(self.p2d,self.snk)
        self.tb.run ()

        # check data
        self.results = self.snk.data()
        self.assertFloatTuplesAlmostEqual(self.expected,self.results,3)

if __name__ == '__main__':
    gr_unittest.run(qa_phase2doa_ff, "qa_phase2doa_ff.xml")
