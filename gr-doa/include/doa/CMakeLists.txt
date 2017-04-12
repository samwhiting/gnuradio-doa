# Copyright 2011,2012 Free Software Foundation, Inc.
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

########################################################################
# Install public header files
########################################################################
install(FILES
    api.h
    capon_ccf.h
    unwrap_ff.h
    linearslope_ff.h
    mode_ii.h
    lin_delay_cc.h
    peak_estimator_cif.h
    cub_delay_cc.h
    cumulative_ff.h
    variance_ff.h
    zero_pad_cc.h
    sample_offset_cci.h
    hold_ii.h
    hold_ff.h
    full_capon_ccf.h
    full_capon3_ccf.h
    multiply_exp_cc.h
    pi2pi_ff.h
    delay.h
    message_sink_i.h
    message_sink_f.h
    add_const_ff.h
    phase2doa_ff.h
    hold_state_ff.h DESTINATION include/doa
)
