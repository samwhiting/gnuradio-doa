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

class qa_multiply_exp_cc (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        # data
        self.arg = 2;
        self.data = ((1+1j),(2+2j),(3-3j))
        self.expected = ((-1.3254 + 0.4932j), (-2.6509 + 0.9863j), (1.4795 + 3.9763j))

        # blocks
        self.src = blocks.vector_source_c(self.data)
        self.mul = doa.multiply_exp_cc(self.arg)
        self.snk = blocks.vector_sink_c()

        # connections
        self.tb.connect(self.src, self.mul, self.snk)
        self.tb.run ()

        # check data
        self.results = self.snk.data()
        self.assertComplexTuplesAlmostEqual(self.expected,self.results,2)


if __name__ == '__main__':
    gr_unittest.run(qa_multiply_exp_cc, "qa_multiply_exp_cc.xml")
