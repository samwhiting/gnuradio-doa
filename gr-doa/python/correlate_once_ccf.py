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

import numpy
from gnuradio import gr

class correlate_once_ccf(gr.sync_block):
    """
    docstring for block correlate_once_ccf
    """
    def __init__(self, width, median):
        self.width = width
        self.median = median
        self.which = 0
        self.shifts = numpy.zeros(self.median)
        self.shift = 0
        gr.sync_block.__init__(self,
            name="correlate_once_ccf",
            in_sig=[(numpy.complex64,self.width), (numpy.complex64,self.width)],
            out_sig=[numpy.intc])


    def get_shift(self, in0, in1):
        correlation = numpy.correlate(in0, in1, "full")
        maximum = numpy.argmax(correlation)
        return maximum - (self.width*2-1)/2


    def work(self, input_items, output_items):
        in0 = input_items[0]
        in1 = input_items[1]
        out = output_items[0]
        for i in range(numpy.shape(in0)[0]):
            if self.which < self.median:
                self.shifts[self.which] = self.get_shift(in0[i,:], in1[i,:])
                self.which = self.which + 1
            if self.which == self.median:
                self.shift = numpy.median(self.shifts)
                for k in range(self.median):
                    print self.shifts[k]
                self.which = self.which + 1
            out[i] = self.shift
        return len(output_items[0])

