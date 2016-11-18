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

import time
from gnuradio import gr, gr_unittest
from gnuradio import blocks
from timestamp_ccf import timestamp_ccf

class qa_timestamp_ccf (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        # data
        data = [5.323, 342.43, 2038.1]
        expected1 = [5.323, 342.43, 2038.1]
        expected2 = range(3)
        for n in range(3):
            expected2[n] = (time.time() - (time.time() // 1000)*1000)

        # blocks
        src = blocks.vector_source_f(data)
        sync = timestamp_ccf()
        snk1 = blocks.vector_sink_f()
        snk2 = blocks.vector_sink_f()

        # connections
        self.tb.connect(src, sync)
        self.tb.connect((sync, 0), snk1)
        self.tb.connect((sync, 1), snk2)
        self.tb.run ()

        # check data
        self.assertFloatTuplesAlmostEqual(expected1, snk1.data(),1)
        self.assertFloatTuplesAlmostEqual(expected2, snk2.data(),1)


if __name__ == '__main__':
    gr_unittest.run(qa_timestamp_ccf, "qa_timestamp_ccf.xml")
