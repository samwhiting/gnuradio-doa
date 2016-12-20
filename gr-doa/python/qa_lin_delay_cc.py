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

class qa_lin_delay_cc (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        # data
        self.drift = -0.5
        self.samp_rate = 5
        self.data1 = (6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9)
        self.data2 = (6, 4.9, 3.8, 2.7, 1.6, 0.5, -0.6, -1.7, -2.8, -3.9, -5, -6.1, -7.2, -8.3, -9.4, -10.5)
        self.expected1 = (6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9)
        self.expected2 = (6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9)

        # blocks
        self.src1 = blocks.vector_source_c(self.data1)
        self.src2 = blocks.vector_source_c(self.data2)
        self.delay = doa.lin_delay_cc(self.samp_rate, self.drift)
        self.snk1 = blocks.vector_sink_c()
        self.snk2 = blocks.vector_sink_c()

        # connections
        self.tb.connect(self.src1, (self.delay,0))
        self.tb.connect(self.src2, (self.delay,1))
        self.tb.connect((self.delay,0), self.snk1)
        self.tb.connect((self.delay,1), self.snk2)
        self.tb.run ()

        # check data
        self.results1 = self.snk1.data()
        self.results2 = self.snk2.data()
        print (self.results1)
        print (self.results2)
        self.assertComplexTuplesAlmostEqual(self.expected1,self.results1,1)
        self.assertComplexTuplesAlmostEqual(self.expected2,self.results2,1)


if __name__ == '__main__':
    gr_unittest.run(qa_lin_delay_cc, "qa_lin_delay_cc.xml")
