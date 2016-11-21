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

class qa_capon_ccf (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        # data
        self.vector_length = 5;
        self.data1 = ((5.0 + 0.0j),(-0.398558983590390 - 4.984089760086529j),(-4.936460294639758 + 0.794581499561343j),(1.185547222616765 + 4.857414722148571j),(4.747456096221939 - 1.568968009375955j))
        self.data2 = ((1.508457516102848 + 4.767027996782988j),(4.631617226080932 - 1.883645898535703j),(-2.246846577705473 - 4.466730398877148j),(-4.273416870763394 + 2.595748109635216j),(2.928130051493258 + 4.052906907583998j))
        self.expected = (1.26433000)

        # blocks
        self.src1 = blocks.vector_source_c(self.data1,False,self.vector_length)
        self.src2 = blocks.vector_source_c(self.data2,False,self.vector_length)
        self.capon = doa.capon_ccf(self.vector_length)
        self.snk = blocks.vector_sink_f()

        # connections
        self.tb.connect(self.src1, (self.capon,0))
        self.tb.connect(self.src2, (self.capon,1))
        self.tb.connect(self.capon,self.snk)
        self.tb.run ()

        # check data
        self.results = self.snk.data()
        self.assertAlmostEqual(self.expected,self.results[0],3)

if __name__ == '__main__':
    gr_unittest.run(qa_capon_ccf, "qa_capon_ccf.xml")
