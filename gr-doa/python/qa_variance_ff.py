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

class qa_variance_ff (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
         # data
        self.vector_length = 8;
        self.data = (1, 3, 5, 5, 6, 6, 8, 9) 
        self.expected = (6.5536)

        # blocks
        self.src = blocks.vector_source_f(self.data,False,self.vector_length)
        self.var = doa.variance_ff(self.vector_length)
        self.snk = blocks.vector_sink_f()

        # connections
        self.tb.connect(self.src,self.var,self.snk)
        self.tb.run ()

        # check data
        self.results = self.snk.data()
        self.assertAlmostEqual(self.expected,self.results[0],3)

       # set up fg
        self.tb.run ()
        # check data


if __name__ == '__main__':
    gr_unittest.run(qa_variance_ff, "qa_variance_ff.xml")
