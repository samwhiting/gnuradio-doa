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

class qa_full_capon3_ccf (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        # data
        self.vector_length_in = 8;
        self.vector_length_out = 8;
        self.data1 = ((2.101765 - 0.1136365j),(0.6830077 + 0.1766335j),(4.741745 + 0.07127096j),(1.037089 + 0.08937196j),(2.013856 + 0.08394291j),(4.518792 + 0.5311512j),(1.142077 - 0.1150589j),(-10.51938 - 0.6250837j)) 
        self.data2 = ((-0.9668710 + 3.410859j),(1.675037 - 0.7679004j),(1.076942 + 4.065166j),(0.9010103 + 0.3478354j),(1.026168 + 0.9570264j),(5.078891 - 0.9142112j),(-1.145686 + 2.144195j),(-6.622580 - 4.368002j))
        self.data3 = ((-4.652023 + 0.5961858j),(2.492679 - 0.2852718j),(-3.200703 + 0.5038460j),(0.8181259 - 0.04016215j),(-0.06216002 + 0.05145182j),(6.141905 - 0.6604887j),(-3.260490 + 0.4184076j),(-1.788836 + 0.007123172j))
        self.expected = (0.00694161700084806, 0.00515712471678853, 0.00819214154034853, 0.0390417091548443,  2.37873339653018,  0.159786492586136, 3.01280951509776,  0.0243304856121540) 


        # blocks
        self.src1 = blocks.vector_source_c(self.data1,False,self.vector_length_in)
        self.src2 = blocks.vector_source_c(self.data2,False,self.vector_length_in)
        self.src3 = blocks.vector_source_c(self.data3,False,self.vector_length_in)
        self.capon = doa.full_capon3_ccf(self.vector_length_in,self.vector_length_out)
        self.snk = blocks.vector_sink_f(self.vector_length_out)

        # connections
        self.tb.connect(self.src1, (self.capon,0))
        self.tb.connect(self.src2, (self.capon,1))
        self.tb.connect(self.src3, (self.capon,2))
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
    gr_unittest.run(qa_full_capon3_ccf, "qa_full_capon3_ccf.xml")
