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

class qa_peak_estimator_cif (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        # data
        self.vector_length = 5;
        self.data = (1+1j, 3+3j, 5+5j, 3+3j, 1+1j);
        self.expected1 = (2.0)
        self.expected2 = (0.0)

        # blocks
        self.src = blocks.vector_source_c(self.data,False,self.vector_length)
        self.peak = doa.peak_estimator_cif(self.vector_length)
        self.snk1 = blocks.vector_sink_f()
        self.snk2 = blocks.vector_sink_f()

        # connections
        self.tb.connect(self.src, self.peak)
        self.tb.connect((self.peak, 0), self.snk1);
        self.tb.connect((self.peak, 1), self.snk2);
        self.tb.run ()

        # check data
        self.results1 = self.snk1.data()
        self.results2 = self.snk2.data()
        self.assertAlmostEqual(self.expected1,self.results1[0],3)
        self.assertAlmostEqual(self.expected2,self.results2[0],3)


    def test_002_t (self):
        # data
        self.vector_length = 10;
        self.data = (1.62182308193243+4.50541598502498j, 7.94284540683907+0.838213779969326j, 3.11215042044805+2.28976968716819j, 5.28533135506213+9.13337361501670j, 1.65648729499781+1.52378018969223j, 6.01981941401637+8.25816977489548j, 2.62971284540144+5.38342435260057j, 6.54079098476782+9.96134716626886j, 6.89214503140008+0.781755287531837j, 7.48151592823709+4.42678269775446j)
        self.expected1 = (7.0)
        self.expected2 = (0.2384)

        # blocks
        self.src = blocks.vector_source_c(self.data,False,self.vector_length)
        self.peak = doa.peak_estimator_cif(self.vector_length)
        self.snk1 = blocks.vector_sink_f()
        self.snk2 = blocks.vector_sink_f()

        # connections
        self.tb.connect(self.src, self.peak)
        self.tb.connect((self.peak, 0), self.snk1);
        self.tb.connect((self.peak, 1), self.snk2);
        self.tb.run ()

        # check data
        self.results1 = self.snk1.data()
        self.results2 = self.snk2.data()
        self.assertAlmostEqual(self.expected1,self.results1[0],3)
        self.assertAlmostEqual(self.expected2,self.results2[0],3)


if __name__ == '__main__':
    gr_unittest.run(qa_peak_estimator_cif, "qa_peak_estimator_cif.xml")
