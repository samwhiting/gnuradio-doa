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

class qa_full_capon_ccf (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        # data
        self.vector_length_in = 5;
        self.vector_length_out = 6;
        self.data1 = ((1.3685 + 2.6736j),(0.3466 + 2.9633j),(-0.5820 + 2.9629j),(-1.3638 + 2.6724j),(-1.9690 + 2.1204j))
        self.data2 = ((-1.9847 + 2.3153j),(-2.4927 + 1.6124j),(-2.9269 + 0.7517j),(-2.8827 - 0.1825j),(-2.9004 - 1.0989j))
        self.expected = (0.0060,0.0043,0.0054,0.0145,0.8080,0.0201)

        # blocks
        self.src1 = blocks.vector_source_c(self.data1,False,self.vector_length_in)
        self.src2 = blocks.vector_source_c(self.data2,False,self.vector_length_in)
        self.capon = doa.full_capon_ccf(self.vector_length_in,self.vector_length_out)
        self.snk = blocks.vector_sink_f(self.vector_length_out)

        # connections
        self.tb.connect(self.src1, (self.capon,0))
        self.tb.connect(self.src2, (self.capon,1))
        self.tb.connect(self.capon,self.snk)
        self.tb.run ()

        # check data
        self.results = self.snk.data()
        print "***********************"
        print "we got back: ",["%5.3f" % i for i in self.results]
        print "we expected: ",["%5.3f" % i for i in self.expected]
        print "***********************"
        self.assertFloatTuplesAlmostEqual(self.expected,self.results,0)


if __name__ == '__main__':
    gr_unittest.run(qa_full_capon_ccf, "qa_full_capon_ccf.xml")
