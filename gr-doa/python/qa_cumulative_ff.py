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

class qa_cumulative_ff (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        # data
        self.default = 1.5
        self.data = (-0.5, 3, -0.2, -0.8, 1, 1, 0, 1.12, -0.12, 0)
        self.expected = (1, 4, 3.8, 3, 4, 5, 5, 6.12, 6, 6)

        # blocks
        self.src = blocks.vector_source_f(self.data)
        self.sum = doa.cumulative_ff(self.default)
        self.snk = blocks.vector_sink_f()

        # connections
        self.tb.connect(self.src, self.sum, self.snk)
        self.tb.run ()

        # check data
        self.results = self.snk.data()
        print (self.results)
        self.assertComplexTuplesAlmostEqual(self.expected,self.results,5)


if __name__ == '__main__':
    gr_unittest.run(qa_cumulative_ff, "qa_cumulative_ff.xml")
