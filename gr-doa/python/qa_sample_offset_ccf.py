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

class qa_sample_offset_cci (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        # data
        self.width = 10
        self.median = 1
        self.data1 = ((3+4j),(-10-10j),(6-5j),(8-10j),(3-9j),(5+6j),(4+3j),(-3-4j),(3+9j),(-7-10j))
        self.data2 = ((3+4j),(-10-10j),(6-5j),(8-10j),(3-9j),(5+6j),(4+3j),(-3-4j),(3+9j),(-7-10j))
        self.expected = (0)

        # blocks
        self.src1 = blocks.vector_source_c(self.data1,False,self.width)
        self.src2 = blocks.vector_source_c(self.data2,False,self.width)
        self.corr = doa.sample_offset_cci(self.width, self.median)
        self.snk = blocks.vector_sink_i()

        # connections
        self.tb.connect(self.src1, (self.corr,0))
        self.tb.connect(self.src2, (self.corr,1))
        self.tb.connect(self.corr, self.snk)
        self.tb.run ()

        # check data
        self.results = self.snk.data()
        self.assertAlmostEqual(self.expected,self.results[0],3)


    def test_002_t (self):
        # data
        self.width = 10
        self.median = 1
        self.data1 = ((3+4j),(-10-10j),(6-5j),(8-10j),(3-9j),(5+6j),(4+3j),(-3-4j),(3+9j),(-7-10j))
        self.data2 = ((1+2j),(10+0j),(2+2j),(3+4j),(-10-10j),(6-5j),(8-10j),(3-9j),(5+6j),(4+3))
        self.expected = (-3)

        # blocks
        self.src1 = blocks.vector_source_c(self.data1,False,self.width)
        self.src2 = blocks.vector_source_c(self.data2,False,self.width)
        self.corr = doa.sample_offset_cci(self.width, self.median)
        self.snk = blocks.vector_sink_i()

        # connections
        self.tb.connect(self.src1, (self.corr,0))
        self.tb.connect(self.src2, (self.corr,1))
        self.tb.connect(self.corr, self.snk)
        self.tb.run ()

        # check data
        self.results = self.snk.data()
        self.assertAlmostEqual(self.expected,self.results[0],3)


    def test_003_t (self):
        # data
        self.width = 10
        self.median = 1
        self.data1 = ((1+2j),(10+0j),(2+2j),(3+4j),(-10-10j),(6-5j),(8-10j),(3-9j),(5+6j),(4+3))
        self.data2 = ((3+4j),(-10-10j),(6-5j),(8-10j),(3-9j),(5+6j),(4+3j),(-3-4j),(3+9j),(-7-10j))
        self.expected = (3)

        # blocks
        self.src1 = blocks.vector_source_c(self.data1,False,self.width)
        self.src2 = blocks.vector_source_c(self.data2,False,self.width)
        self.corr = doa.sample_offset_cci(self.width, self.median)
        self.snk = blocks.vector_sink_i()

        # connections
        self.tb.connect(self.src1, (self.corr,0))
        self.tb.connect(self.src2, (self.corr,1))
        self.tb.connect(self.corr, self.snk)
        self.tb.run ()

        # check data
        self.results = self.snk.data()
        self.assertAlmostEqual(self.expected,self.results[0],3)


if __name__ == '__main__':
    gr_unittest.run(qa_sample_offset_cci, "qa_sample_offset_cci.xml")
