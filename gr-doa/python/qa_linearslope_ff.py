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

class qa_linearslope_ff (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        # data
        self.vector_length = 10
        self.data = (0, 2, 4, 6, 8, 10, 12, 14, 16, 18)
        self.expected = (2)

        # blocks
        self.src = blocks.vector_source_f(self.data, False, self.vector_length)
        self.slope = doa.linearslope_ff(self.vector_length)
        self.snk = blocks.vector_sink_f()

        # connections
        self.tb.connect(self.src, self.slope, self.snk)
        self.tb.run ()

        # check data
        self.result = self.snk.data()
        self.assertAlmostEqual(self.expected, self.result[0], 3)

    def test_002_t (self):
        # data
        self.vector_length = 14
        self.data = (8.20790161799184, 3.49305812845213, -10.4987542488625, -10.8902293772389, -26.9431985796270, -31.5665494172156, -37.0733569125835, -42.5999494669715, -50.0151488866644, -64.7814485454000, -79.4944306401058, -87.7927247918695, -94.5985852503684, -94.1370259834500)
        self.expected = -8.4295

        # blocks
        self.src = blocks.vector_source_f(self.data, False, self.vector_length)
        self.slope = doa.linearslope_ff(self.vector_length)
        self.snk = blocks.vector_sink_f()

        # connections
        self.tb.connect(self.src, self.slope, self.snk)
        self.tb.run ()

        # check data
        self.result = self.snk.data()
        print (self.result)
        self.assertAlmostEqual(self.expected, self.result[0], 3)


if __name__ == '__main__':
    gr_unittest.run(qa_linearslope_ff, "qa_linearslope_ff.xml")
