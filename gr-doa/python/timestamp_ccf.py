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
import numpy
from gnuradio import gr

class timestamp_ccf(gr.sync_block):
    """
    docstring for block timestamp_ccf
    """
    def __init__(self):
        gr.sync_block.__init__(self,
            name="timestamp_ccf",
            in_sig=[numpy.float32],
            out_sig=[numpy.float32, numpy.float32])


    def work(self, input_items, output_items):
        in0 = input_items[0]
        out0 = output_items[0]
        out1 = output_items[1]
        out0[:] = in0
        for n in range(len(in0)):
            out1[n] = (time.time() - (time.time() // 1000)*1000)
        return len(output_items[0])

