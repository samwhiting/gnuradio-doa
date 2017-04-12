# Copyright 2011 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
install(FILES
    doa_capon_ccf.xml
    doa_timestamp_ccf.xml
    doa_unwrap_ff.xml
    doa_linearslope_ff.xml
    doa_mode_ii.xml
    doa_lin_delay_cc.xml
    doa_peak_estimator_cif.xml
    doa_cub_delay_cc.xml
    doa_cumulative_ff.xml
    doa_variance_ff.xml
    doa_zero_pad_cc.xml
    doa_sample_offset_cci.xml
    doa_hold_ii.xml
    doa_hold_ff.xml
    doa_full_capon_ccf.xml
    doa_full_capon3_ccf.xml
    doa_multiply_exp_cc.xml
    doa_pi2pi_ff.xml
    doa_arrow_f.xml
    doa_delay.xml
    doa_message_sink_i.xml
    doa_message_sink_f.xml
    doa_add_const_ff.xml
    doa_phase2doa_ff.xml
    doa_hold_state_ff.xml DESTINATION share/gnuradio/grc/blocks
)
