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

class qa_unwrap_ff (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        # data
        self.vector_length = 12
        self.data = (0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3)
        self.expected = (0, 1, 2, 3, 3, 4, 5, 6, 6, 7, 8, 9)
        self.min = 0
        self.max = 3

        # blocks
        self.src = blocks.vector_source_f(self.data, False, self.vector_length)
        self.unwrap = doa.unwrap_ff(self.vector_length, self.min, self.max)
        self.snk = blocks.vector_sink_f(self.vector_length)

        # connections
        self.tb.connect(self.src, self.unwrap, self.snk)
        self.tb.run ()

        # check data
        self.result = self.snk.data()
        print (self.result)
        self.assertFloatTuplesAlmostEqual(self.expected, self.result, 3)

    def test_002_t (self):
        # data
        self.vector_length = 12
        self.data = (1.1, 1.5, 3.6, 6.1, 0.1, 2.5, 4.3, 5.5, 1.0, 2.0, 3.0, 4.0)
        self.expected = (1.1, 1.5, 3.6, 6.1, 6.38, 8.78, 10.58, 11.78, 13.56, 14.56, 15.56, 16.56)
        self.min = 0
        self.max = 6.28

        # blocks
        self.src = blocks.vector_source_f(self.data, False, self.vector_length)
        self.unwrap = doa.unwrap_ff(self.vector_length, self.min, self.max)
        self.snk = blocks.vector_sink_f(self.vector_length)

        # connections
        self.tb.connect(self.src, self.unwrap, self.snk)
        self.tb.run ()

        # check data
        self.result = self.snk.data()
        print (self.result)
        self.assertFloatTuplesAlmostEqual(self.expected, self.result, 3)

    def test_003_t (self):
        # data
        self.vector_length = 33
        self.data = (0.292036732051034, -0.707963267948966, -1.70796326794897, -2.70796326794897, 2.57522203923062,  1.57522203923062,  0.575222039230621, -0.424777960769379, -1.42477796076938, -2.42477796076938, 2.85840734641021,  1.85840734641021,  0.858407346410207, -0.141592653589793, -1.14159265358979, -2.14159265358979, -3.14159265358979, 2.14159265358979,  1.14159265358979,  0.141592653589793, -0.858407346410207, -1.85840734641021, -2.85840734641021, 2.42477796076938,  1.42477796076938,  0.424777960769379, -0.575222039230621, -1.57522203923062, -2.57522203923062, 2.70796326794897,  1.70796326794897,  0.707963267948966, -0.292036732051034)
        self.expected = (0.292036732051034, -0.707963267948966, -1.70796326794897, -2.70796326794897, -3.70796326794897, -4.70796326794897, -5.70796326794897, -6.70796326794897, -7.70796326794897, -8.70796326794897, -9.70796326794897, -10.7079632679490, -11.7079632679490, -12.7079632679490, -13.7079632679490, -14.7079632679490, -15.7079632679490, -16.7079632679490, -17.7079632679490, -18.7079632679490, -19.7079632679490, -20.7079632679490, -21.7079632679490, -22.7079632679490, -23.7079632679490, -24.7079632679490, -25.7079632679490, -26.7079632679490, -27.7079632679490, -28.7079632679490, -29.7079632679490, -30.7079632679490, -31.7079632679490)
        self.min = -3.14159
        self.max = 3.14159

        # blocks
        self.src = blocks.vector_source_f(self.data, False, self.vector_length)
        self.unwrap = doa.unwrap_ff(self.vector_length, self.min, self.max)
        self.snk = blocks.vector_sink_f(self.vector_length)

        # connections
        self.tb.connect(self.src, self.unwrap, self.snk)
        self.tb.run ()

        # check data
        self.result = self.snk.data()
        print (self.result)
        self.assertFloatTuplesAlmostEqual(self.expected, self.result, 3)


if __name__ == '__main__':
    gr_unittest.run(qa_unwrap_ff, "qa_unwrap_ff.xml")
