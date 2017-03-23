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
from time import sleep
from gnuradio import gr
from PyQt4 import Qt, QtCore, QtGui

class arrow_f(gr.sync_block, QtGui.QWidget):
    """
    needs simplearrowup.png
    """
    def __init__(self, *args):
        gr.sync_block.__init__(self,
            name="arrow_f",
            in_sig=[numpy.float32],
            out_sig=None)
        
        # call parent constructor
        QtGui.QWidget.__init__(self, *args)
        
        # angle starts at 0
        self.angle = 0
        
        self.setMinimumWidth(100)
        self.setMinimumHeight(100)

    def paintEvent(self, e):
      print("Paint event ran\n")

      # transform object to rotate the image
      transform = QtGui.QTransform(1,0,0,1, self.width()/2, self.height()/2)
      transform.rotate(self.angle)

      # image is a pixel map object, from file
      arrow = QtGui.QPixmap("simplearrowup.png")

      # painter object to draw the image
      painter = QtGui.QPainter(self)
      painter.setTransform(transform)
      painter.drawPixmap(-arrow.width()/2,-arrow.height()/2, arrow) 
#      painter.drawPixmap(100,100,arrow) 

    def rotateArrow(self, new_angle):
      print("Rotate Arrow  ran\n")
      # rotate our image by the input (radians)
      self.angle = numpy.rad2deg(new_angle)/2
      # draw
      self.update()

    def work(self, input_items, output_items):
        in0 = input_items[0]

        # use the last sample to update
        self.rotateArrow(in0[-1])

        return len(input_items[0])

