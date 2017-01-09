#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Interpolation Test
# Generated: Mon Jan  2 16:01:37 2017
##################################################

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"

import os
import sys
sys.path.append(os.environ.get('GRC_HIER_PATH', os.path.expanduser('~/.grc_gnuradio')))

from PyQt4 import Qt
from cross_correlation import cross_correlation  # grc-generated hier_block
from gnuradio import analog
from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import qtgui
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
import doa
import osmosdr
import sip
import threading
import time


class interpolation_test(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Interpolation Test")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Interpolation Test")
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
            pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "interpolation_test")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())

        ##################################################
        # Variables
        ##################################################
        self.n_points = n_points = 5000
        self.lag2 = lag2 = 0
        self.drift = drift = 0
        self.downsample = downsample = 100
        self.transition = transition = 2e5
        self.slope_samples = slope_samples = 100
        self.rtl_samp_rate = rtl_samp_rate = 2048000
        self.pi = pi = 3.1415926535
        self.lag_of_signals_2 = lag_of_signals_2 = lag2
        self.fft_width = fft_width = 2**14
        self.drift_correction = drift_correction = drift
        self.down_width = down_width = n_points/downsample
        self.cutoff = cutoff = 1e5
        self.center_freq = center_freq = 94.5e6
        self.c = c = 299792458

        ##################################################
        # Blocks
        ##################################################
        self.probe3 = blocks.probe_signal_i()
        self.tab = Qt.QTabWidget()
        self.tab_widget_0 = Qt.QWidget()
        self.tab_layout_0 = Qt.QBoxLayout(Qt.QBoxLayout.TopToBottom, self.tab_widget_0)
        self.tab_grid_layout_0 = Qt.QGridLayout()
        self.tab_layout_0.addLayout(self.tab_grid_layout_0)
        self.tab.addTab(self.tab_widget_0, 'Aligned DOA')
        self.tab_widget_1 = Qt.QWidget()
        self.tab_layout_1 = Qt.QBoxLayout(Qt.QBoxLayout.TopToBottom, self.tab_widget_1)
        self.tab_grid_layout_1 = Qt.QGridLayout()
        self.tab_layout_1.addLayout(self.tab_grid_layout_1)
        self.tab.addTab(self.tab_widget_1, 'X-Corr')
        self.top_layout.addWidget(self.tab)
        
        def _lag2_probe():
            while True:
                val = self.probe3.level()
                try:
                    self.set_lag2(val)
                except AttributeError:
                    pass
                time.sleep(1.0 / (10))
        _lag2_thread = threading.Thread(target=_lag2_probe)
        _lag2_thread.daemon = True
        _lag2_thread.start()
            
        
        def _drift_probe():
            while True:
                val = self.drift_probe.level()
                try:
                    self.set_drift(val)
                except AttributeError:
                    pass
                time.sleep(1.0 / (10))
        _drift_thread = threading.Thread(target=_drift_probe)
        _drift_thread.daemon = True
        _drift_thread.start()
            
        self.to_samples_per_second_0 = blocks.multiply_const_vff((rtl_samp_rate/(center_freq*2*pi), ))
        self.to_radians_per_second_0 = blocks.multiply_const_vff((rtl_samp_rate/float(n_points), ))
        self.rtlsdr_source_0_0 = osmosdr.source( args="numchan=" + str(1) + " " + "rtl=1" )
        self.rtlsdr_source_0_0.set_sample_rate(rtl_samp_rate)
        self.rtlsdr_source_0_0.set_center_freq(center_freq, 0)
        self.rtlsdr_source_0_0.set_freq_corr(0, 0)
        self.rtlsdr_source_0_0.set_dc_offset_mode(0, 0)
        self.rtlsdr_source_0_0.set_iq_balance_mode(0, 0)
        self.rtlsdr_source_0_0.set_gain_mode(False, 0)
        self.rtlsdr_source_0_0.set_gain(10, 0)
        self.rtlsdr_source_0_0.set_if_gain(20, 0)
        self.rtlsdr_source_0_0.set_bb_gain(20, 0)
        self.rtlsdr_source_0_0.set_antenna('', 0)
        self.rtlsdr_source_0_0.set_bandwidth(0, 0)
          
        self.rtlsdr_source_0 = osmosdr.source( args="numchan=" + str(1) + " " + "rtl=0" )
        self.rtlsdr_source_0.set_sample_rate(rtl_samp_rate)
        self.rtlsdr_source_0.set_center_freq(center_freq, 0)
        self.rtlsdr_source_0.set_freq_corr(0, 0)
        self.rtlsdr_source_0.set_dc_offset_mode(0, 0)
        self.rtlsdr_source_0.set_iq_balance_mode(0, 0)
        self.rtlsdr_source_0.set_gain_mode(False, 0)
        self.rtlsdr_source_0.set_gain(10, 0)
        self.rtlsdr_source_0.set_if_gain(20, 0)
        self.rtlsdr_source_0.set_bb_gain(20, 0)
        self.rtlsdr_source_0.set_antenna('', 0)
        self.rtlsdr_source_0.set_bandwidth(0, 0)
          
        self.qtgui_vector_sink_f_0 = qtgui.vector_sink_f(
            fft_width,
            0,
            1.0,
            "bins",
            "magnitude^2",
            "Cross-Correlation",
            1 # Number of inputs
        )
        self.qtgui_vector_sink_f_0.set_update_time(0.10)
        self.qtgui_vector_sink_f_0.set_y_axis(-140, 1e7)
        self.qtgui_vector_sink_f_0.enable_autoscale(False)
        self.qtgui_vector_sink_f_0.enable_grid(False)
        self.qtgui_vector_sink_f_0.set_x_axis_units("")
        self.qtgui_vector_sink_f_0.set_y_axis_units("")
        self.qtgui_vector_sink_f_0.set_ref_level(0)
        
        labels = ['', '', '', '', '',
                  '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
                  "magenta", "yellow", "dark red", "dark green", "dark blue"]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]
        for i in xrange(1):
            if len(labels[i]) == 0:
                self.qtgui_vector_sink_f_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_vector_sink_f_0.set_line_label(i, labels[i])
            self.qtgui_vector_sink_f_0.set_line_width(i, widths[i])
            self.qtgui_vector_sink_f_0.set_line_color(i, colors[i])
            self.qtgui_vector_sink_f_0.set_line_alpha(i, alphas[i])
        
        self._qtgui_vector_sink_f_0_win = sip.wrapinstance(self.qtgui_vector_sink_f_0.pyqwidget(), Qt.QWidget)
        self.tab_layout_1.addWidget(self._qtgui_vector_sink_f_0_win)
        self.qtgui_time_sink_x_1 = qtgui.time_sink_f(
        	1024, #size
        	rtl_samp_rate/float(fft_width), #samp_rate
        	"", #name
        	1 #number of inputs
        )
        self.qtgui_time_sink_x_1.set_update_time(0.10)
        self.qtgui_time_sink_x_1.set_y_axis(-1, 1)
        
        self.qtgui_time_sink_x_1.set_y_label('Amplitude', "")
        
        self.qtgui_time_sink_x_1.enable_tags(-1, True)
        self.qtgui_time_sink_x_1.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_1.enable_autoscale(False)
        self.qtgui_time_sink_x_1.enable_grid(False)
        self.qtgui_time_sink_x_1.enable_axis_labels(True)
        self.qtgui_time_sink_x_1.enable_control_panel(False)
        
        if not True:
          self.qtgui_time_sink_x_1.disable_legend()
        
        labels = ['', '', '', '', '',
                  '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
                  "magenta", "yellow", "dark red", "dark green", "blue"]
        styles = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
                   -1, -1, -1, -1, -1]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]
        
        for i in xrange(1):
            if len(labels[i]) == 0:
                self.qtgui_time_sink_x_1.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_time_sink_x_1.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_1.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_1.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_1.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_1.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_1.set_line_alpha(i, alphas[i])
        
        self._qtgui_time_sink_x_1_win = sip.wrapinstance(self.qtgui_time_sink_x_1.pyqwidget(), Qt.QWidget)
        self.tab_layout_0.addWidget(self._qtgui_time_sink_x_1_win)
        self.qtgui_time_sink_x_0_0_0_0 = qtgui.time_sink_f(
        	20, #size
        	rtl_samp_rate/float(n_points)/float(slope_samples), #samp_rate
        	"Slope of capon angle vs. Time", #name
        	1 #number of inputs
        )
        self.qtgui_time_sink_x_0_0_0_0.set_update_time(0.10)
        self.qtgui_time_sink_x_0_0_0_0.set_y_axis(-4, 4)
        
        self.qtgui_time_sink_x_0_0_0_0.set_y_label("Rate of change of capon angle (samples/s)", "Time")
        
        self.qtgui_time_sink_x_0_0_0_0.enable_tags(-1, True)
        self.qtgui_time_sink_x_0_0_0_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_0_0_0_0.enable_autoscale(True)
        self.qtgui_time_sink_x_0_0_0_0.enable_grid(False)
        self.qtgui_time_sink_x_0_0_0_0.enable_axis_labels(True)
        self.qtgui_time_sink_x_0_0_0_0.enable_control_panel(True)
        
        if not True:
          self.qtgui_time_sink_x_0_0_0_0.disable_legend()
        
        labels = ['', '', '', '', '',
                  '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
                  "magenta", "yellow", "dark red", "dark green", "blue"]
        styles = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
                   -1, -1, -1, -1, -1]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]
        
        for i in xrange(1):
            if len(labels[i]) == 0:
                self.qtgui_time_sink_x_0_0_0_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_time_sink_x_0_0_0_0.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_0_0_0_0.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_0_0_0_0.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_0_0_0_0.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_0_0_0_0.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_0_0_0_0.set_line_alpha(i, alphas[i])
        
        self._qtgui_time_sink_x_0_0_0_0_win = sip.wrapinstance(self.qtgui_time_sink_x_0_0_0_0.pyqwidget(), Qt.QWidget)
        self.tab_layout_0.addWidget(self._qtgui_time_sink_x_0_0_0_0_win)
        self.qtgui_time_sink_x_0 = qtgui.time_sink_f(
        	256, #size
        	rtl_samp_rate/float(n_points), #samp_rate
        	"", #name
        	1 #number of inputs
        )
        self.qtgui_time_sink_x_0.set_update_time(0.10)
        self.qtgui_time_sink_x_0.set_y_axis(-1, 1)
        
        self.qtgui_time_sink_x_0.set_y_label('Amplitude', "")
        
        self.qtgui_time_sink_x_0.enable_tags(-1, True)
        self.qtgui_time_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_0.enable_autoscale(False)
        self.qtgui_time_sink_x_0.enable_grid(False)
        self.qtgui_time_sink_x_0.enable_axis_labels(True)
        self.qtgui_time_sink_x_0.enable_control_panel(False)
        
        if not True:
          self.qtgui_time_sink_x_0.disable_legend()
        
        labels = ['', '', '', '', '',
                  '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
                  "magenta", "yellow", "dark red", "dark green", "blue"]
        styles = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
                   -1, -1, -1, -1, -1]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]
        
        for i in xrange(1):
            if len(labels[i]) == 0:
                self.qtgui_time_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_time_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_0.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_0.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_0.set_line_alpha(i, alphas[i])
        
        self._qtgui_time_sink_x_0_win = sip.wrapinstance(self.qtgui_time_sink_x_0.pyqwidget(), Qt.QWidget)
        self.tab_layout_0.addWidget(self._qtgui_time_sink_x_0_win)
        self.qtgui_number_sink_0 = qtgui.number_sink(
            gr.sizeof_float,
            0,
            qtgui.NUM_GRAPH_NONE,
            1
        )
        self.qtgui_number_sink_0.set_update_time(0.10)
        self.qtgui_number_sink_0.set_title('')
        
        labels = ["Drift Correction", '', '', '', '',
                  '', '', '', '', '']
        units = ['', '', '', '', '',
                 '', '', '', '', '']
        colors = [("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"),
                  ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black")]
        factor = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        for i in xrange(1):
            self.qtgui_number_sink_0.set_min(i, -1)
            self.qtgui_number_sink_0.set_max(i, 1)
            self.qtgui_number_sink_0.set_color(i, colors[i][0], colors[i][1])
            if len(labels[i]) == 0:
                self.qtgui_number_sink_0.set_label(i, "Data {0}".format(i))
            else:
                self.qtgui_number_sink_0.set_label(i, labels[i])
            self.qtgui_number_sink_0.set_unit(i, units[i])
            self.qtgui_number_sink_0.set_factor(i, factor[i])
        
        self.qtgui_number_sink_0.enable_autoscale(False)
        self._qtgui_number_sink_0_win = sip.wrapinstance(self.qtgui_number_sink_0.pyqwidget(), Qt.QWidget)
        self.tab_layout_0.addWidget(self._qtgui_number_sink_0_win)
        self._lag_of_signals_2_tool_bar = Qt.QToolBar(self)
        
        if None:
          self._lag_of_signals_2_formatter = None
        else:
          self._lag_of_signals_2_formatter = lambda x: x
        
        self._lag_of_signals_2_tool_bar.addWidget(Qt.QLabel('Shift from correlation'+": "))
        self._lag_of_signals_2_label = Qt.QLabel(str(self._lag_of_signals_2_formatter(self.lag_of_signals_2)))
        self._lag_of_signals_2_tool_bar.addWidget(self._lag_of_signals_2_label)
        self.tab_layout_0.addWidget(self._lag_of_signals_2_tool_bar)
          
        self.drift_probe = blocks.probe_signal_f()
        self._drift_correction_tool_bar = Qt.QToolBar(self)
        
        if None:
          self._drift_correction_formatter = None
        else:
          self._drift_correction_formatter = lambda x: x
        
        self._drift_correction_tool_bar.addWidget(Qt.QLabel('Drift Correction'+": "))
        self._drift_correction_label = Qt.QLabel(str(self._drift_correction_formatter(self.drift_correction)))
        self._drift_correction_tool_bar.addWidget(self._drift_correction_label)
        self.tab_layout_0.addWidget(self._drift_correction_tool_bar)
          
        self.doa_unwrap_ff_0_0 = doa.unwrap_ff(slope_samples, -3.14159265, 3.14159265)
        self.doa_peak_estimator_cff_0 = doa.peak_estimator_cff(fft_width)
        self.doa_linearslope_ff_0_0 = doa.linearslope_ff(slope_samples)
        self.doa_cumulative_ff_0 = doa.cumulative_ff(0)
        self.doa_cub_delay_cc_0 = doa.cub_delay_cc(rtl_samp_rate, -drift)
        self.doa_capon_ccf_0_0 = doa.capon_ccf(down_width)
        self.cross_correlation_0_0 = cross_correlation(
            xcorr_width=fft_width,
        )
        self.blocks_stream_to_vector_2_0 = blocks.stream_to_vector(gr.sizeof_float*1, slope_samples)
        self.blocks_stream_to_vector_0_1 = blocks.stream_to_vector(gr.sizeof_gr_complex*1, down_width)
        self.blocks_stream_to_vector_0_0_0 = blocks.stream_to_vector(gr.sizeof_gr_complex*1, down_width)
        self.blocks_multiply_xx_0 = blocks.multiply_vcc(1)
        self.blocks_keep_one_in_n_0_1 = blocks.keep_one_in_n(gr.sizeof_gr_complex*1, downsample)
        self.blocks_keep_one_in_n_0_0_0 = blocks.keep_one_in_n(gr.sizeof_gr_complex*1, downsample)
        self.blocks_float_to_int_1 = blocks.float_to_int(1, 1)
        self.blocks_delay_0_0 = blocks.delay(gr.sizeof_gr_complex*1, lag2)
        self.blocks_complex_to_mag_squared_0 = blocks.complex_to_mag_squared(fft_width)
        self.analog_sig_source_x_0 = analog.sig_source_c(rtl_samp_rate, analog.GR_COS_WAVE, -drift*46.2, 1, 0)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_sig_source_x_0, 0), (self.blocks_multiply_xx_0, 1))    
        self.connect((self.blocks_complex_to_mag_squared_0, 0), (self.qtgui_vector_sink_f_0, 0))    
        self.connect((self.blocks_delay_0_0, 0), (self.blocks_keep_one_in_n_0_0_0, 0))    
        self.connect((self.blocks_float_to_int_1, 0), (self.probe3, 0))    
        self.connect((self.blocks_keep_one_in_n_0_0_0, 0), (self.blocks_stream_to_vector_0_1, 0))    
        self.connect((self.blocks_keep_one_in_n_0_1, 0), (self.blocks_stream_to_vector_0_0_0, 0))    
        self.connect((self.blocks_multiply_xx_0, 0), (self.doa_cub_delay_cc_0, 1))    
        self.connect((self.blocks_stream_to_vector_0_0_0, 0), (self.doa_capon_ccf_0_0, 0))    
        self.connect((self.blocks_stream_to_vector_0_1, 0), (self.doa_capon_ccf_0_0, 1))    
        self.connect((self.blocks_stream_to_vector_2_0, 0), (self.doa_unwrap_ff_0_0, 0))    
        self.connect((self.cross_correlation_0_0, 0), (self.blocks_complex_to_mag_squared_0, 0))    
        self.connect((self.cross_correlation_0_0, 0), (self.doa_peak_estimator_cff_0, 0))    
        self.connect((self.doa_capon_ccf_0_0, 0), (self.blocks_stream_to_vector_2_0, 0))    
        self.connect((self.doa_capon_ccf_0_0, 0), (self.qtgui_time_sink_x_0, 0))    
        self.connect((self.doa_cub_delay_cc_0, 1), (self.blocks_delay_0_0, 0))    
        self.connect((self.doa_cub_delay_cc_0, 0), (self.blocks_keep_one_in_n_0_1, 0))    
        self.connect((self.doa_cub_delay_cc_0, 1), (self.cross_correlation_0_0, 1))    
        self.connect((self.doa_cub_delay_cc_0, 0), (self.cross_correlation_0_0, 0))    
        self.connect((self.doa_cumulative_ff_0, 0), (self.drift_probe, 0))    
        self.connect((self.doa_cumulative_ff_0, 0), (self.qtgui_number_sink_0, 0))    
        self.connect((self.doa_linearslope_ff_0_0, 0), (self.to_radians_per_second_0, 0))    
        self.connect((self.doa_peak_estimator_cff_0, 0), (self.blocks_float_to_int_1, 0))    
        self.connect((self.doa_peak_estimator_cff_0, 1), (self.qtgui_time_sink_x_1, 0))    
        self.connect((self.doa_unwrap_ff_0_0, 0), (self.doa_linearslope_ff_0_0, 0))    
        self.connect((self.rtlsdr_source_0, 0), (self.doa_cub_delay_cc_0, 0))    
        self.connect((self.rtlsdr_source_0_0, 0), (self.blocks_multiply_xx_0, 0))    
        self.connect((self.to_radians_per_second_0, 0), (self.to_samples_per_second_0, 0))    
        self.connect((self.to_samples_per_second_0, 0), (self.doa_cumulative_ff_0, 0))    
        self.connect((self.to_samples_per_second_0, 0), (self.qtgui_time_sink_x_0_0_0_0, 0))    

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "interpolation_test")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_n_points(self):
        return self.n_points

    def set_n_points(self, n_points):
        self.n_points = n_points
        self.set_down_width(self.n_points/self.downsample)
        self.to_radians_per_second_0.set_k((self.rtl_samp_rate/float(self.n_points), ))
        self.qtgui_time_sink_x_0_0_0_0.set_samp_rate(self.rtl_samp_rate/float(self.n_points)/float(self.slope_samples))
        self.qtgui_time_sink_x_0.set_samp_rate(self.rtl_samp_rate/float(self.n_points))

    def get_lag2(self):
        return self.lag2

    def set_lag2(self, lag2):
        self.lag2 = lag2
        self.set_lag_of_signals_2(self._lag_of_signals_2_formatter(self.lag2))
        self.blocks_delay_0_0.set_dly(self.lag2)

    def get_drift(self):
        return self.drift

    def set_drift(self, drift):
        self.drift = drift
        self.set_drift_correction(self._drift_correction_formatter(self.drift))
        self.doa_cub_delay_cc_0.set_dly(-self.drift)
        self.analog_sig_source_x_0.set_frequency(-self.drift*46.2)

    def get_downsample(self):
        return self.downsample

    def set_downsample(self, downsample):
        self.downsample = downsample
        self.set_down_width(self.n_points/self.downsample)
        self.blocks_keep_one_in_n_0_1.set_n(self.downsample)
        self.blocks_keep_one_in_n_0_0_0.set_n(self.downsample)

    def get_transition(self):
        return self.transition

    def set_transition(self, transition):
        self.transition = transition

    def get_slope_samples(self):
        return self.slope_samples

    def set_slope_samples(self, slope_samples):
        self.slope_samples = slope_samples
        self.qtgui_time_sink_x_0_0_0_0.set_samp_rate(self.rtl_samp_rate/float(self.n_points)/float(self.slope_samples))

    def get_rtl_samp_rate(self):
        return self.rtl_samp_rate

    def set_rtl_samp_rate(self, rtl_samp_rate):
        self.rtl_samp_rate = rtl_samp_rate
        self.to_samples_per_second_0.set_k((self.rtl_samp_rate/(self.center_freq*2*self.pi), ))
        self.to_radians_per_second_0.set_k((self.rtl_samp_rate/float(self.n_points), ))
        self.rtlsdr_source_0_0.set_sample_rate(self.rtl_samp_rate)
        self.rtlsdr_source_0.set_sample_rate(self.rtl_samp_rate)
        self.qtgui_time_sink_x_1.set_samp_rate(self.rtl_samp_rate/float(self.fft_width))
        self.qtgui_time_sink_x_0_0_0_0.set_samp_rate(self.rtl_samp_rate/float(self.n_points)/float(self.slope_samples))
        self.qtgui_time_sink_x_0.set_samp_rate(self.rtl_samp_rate/float(self.n_points))
        self.analog_sig_source_x_0.set_sampling_freq(self.rtl_samp_rate)

    def get_pi(self):
        return self.pi

    def set_pi(self, pi):
        self.pi = pi
        self.to_samples_per_second_0.set_k((self.rtl_samp_rate/(self.center_freq*2*self.pi), ))

    def get_lag_of_signals_2(self):
        return self.lag_of_signals_2

    def set_lag_of_signals_2(self, lag_of_signals_2):
        self.lag_of_signals_2 = lag_of_signals_2
        Qt.QMetaObject.invokeMethod(self._lag_of_signals_2_label, "setText", Qt.Q_ARG("QString", str(self.lag_of_signals_2)))

    def get_fft_width(self):
        return self.fft_width

    def set_fft_width(self, fft_width):
        self.fft_width = fft_width
        self.qtgui_time_sink_x_1.set_samp_rate(self.rtl_samp_rate/float(self.fft_width))
        self.cross_correlation_0_0.set_xcorr_width(self.fft_width)

    def get_drift_correction(self):
        return self.drift_correction

    def set_drift_correction(self, drift_correction):
        self.drift_correction = drift_correction
        Qt.QMetaObject.invokeMethod(self._drift_correction_label, "setText", Qt.Q_ARG("QString", eng_notation.num_to_str(self.drift_correction)))

    def get_down_width(self):
        return self.down_width

    def set_down_width(self, down_width):
        self.down_width = down_width

    def get_cutoff(self):
        return self.cutoff

    def set_cutoff(self, cutoff):
        self.cutoff = cutoff

    def get_center_freq(self):
        return self.center_freq

    def set_center_freq(self, center_freq):
        self.center_freq = center_freq
        self.to_samples_per_second_0.set_k((self.rtl_samp_rate/(self.center_freq*2*self.pi), ))
        self.rtlsdr_source_0_0.set_center_freq(self.center_freq, 0)
        self.rtlsdr_source_0.set_center_freq(self.center_freq, 0)

    def get_c(self):
        return self.c

    def set_c(self, c):
        self.c = c


def main(top_block_cls=interpolation_test, options=None):

    from distutils.version import StrictVersion
    if StrictVersion(Qt.qVersion()) >= StrictVersion("4.5.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()
    tb.start()
    tb.show()

    def quitting():
        tb.stop()
        tb.wait()
    qapp.connect(qapp, Qt.SIGNAL("aboutToQuit()"), quitting)
    qapp.exec_()


if __name__ == '__main__':
    main()
