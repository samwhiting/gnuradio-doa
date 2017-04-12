/* -*- c++ -*- */

#define DOA_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "doa_swig_doc.i"

%{
#include "doa/capon_ccf.h"
#include "doa/unwrap_ff.h"
#include "doa/linearslope_ff.h"
#include "doa/mode_ii.h"
#include "doa/lin_delay_cc.h"
#include "doa/peak_estimator_cif.h"
#include "doa/cub_delay_cc.h"
#include "doa/cumulative_ff.h"
#include "doa/variance_ff.h"
#include "doa/zero_pad_cc.h"
#include "doa/sample_offset_cci.h"
#include "doa/hold_ii.h"
#include "doa/hold_ff.h"
#include "doa/full_capon_ccf.h"
#include "doa/full_capon3_ccf.h"
#include "doa/multiply_exp_cc.h"
#include "doa/pi2pi_ff.h"
#include "doa/delay.h"
#include "doa/message_sink_i.h"
#include "doa/message_sink_f.h"
#include "doa/add_const_ff.h"
#include "doa/phase2doa_ff.h"
#include "doa/hold_state_ff.h"
%}


%include "doa/capon_ccf.h"
GR_SWIG_BLOCK_MAGIC2(doa, capon_ccf);

%include "doa/unwrap_ff.h"
GR_SWIG_BLOCK_MAGIC2(doa, unwrap_ff);
%include "doa/linearslope_ff.h"
GR_SWIG_BLOCK_MAGIC2(doa, linearslope_ff);

%include "doa/mode_ii.h"
GR_SWIG_BLOCK_MAGIC2(doa, mode_ii);

%include "doa/lin_delay_cc.h"
GR_SWIG_BLOCK_MAGIC2(doa, lin_delay_cc);
%include "doa/peak_estimator_cif.h"
GR_SWIG_BLOCK_MAGIC2(doa, peak_estimator_cif);
%include "doa/cub_delay_cc.h"
GR_SWIG_BLOCK_MAGIC2(doa, cub_delay_cc);

%include "doa/cumulative_ff.h"
GR_SWIG_BLOCK_MAGIC2(doa, cumulative_ff);
%include "doa/variance_ff.h"
GR_SWIG_BLOCK_MAGIC2(doa, variance_ff);

%include "doa/zero_pad_cc.h"
GR_SWIG_BLOCK_MAGIC2(doa, zero_pad_cc);
%include "doa/sample_offset_cci.h"
GR_SWIG_BLOCK_MAGIC2(doa, sample_offset_cci);
%include "doa/hold_ii.h"
GR_SWIG_BLOCK_MAGIC2(doa, hold_ii);
%include "doa/hold_ff.h"
GR_SWIG_BLOCK_MAGIC2(doa, hold_ff);
%include "doa/full_capon_ccf.h"
GR_SWIG_BLOCK_MAGIC2(doa, full_capon_ccf);
%include "doa/full_capon3_ccf.h"
GR_SWIG_BLOCK_MAGIC2(doa, full_capon3_ccf);

%include "doa/multiply_exp_cc.h"
GR_SWIG_BLOCK_MAGIC2(doa, multiply_exp_cc);
%include "doa/pi2pi_ff.h"
GR_SWIG_BLOCK_MAGIC2(doa, pi2pi_ff);

%include "doa/delay.h"
GR_SWIG_BLOCK_MAGIC2(doa, delay);
%include "doa/message_sink_i.h"
GR_SWIG_BLOCK_MAGIC2(doa, message_sink_i);
%include "doa/message_sink_f.h"
GR_SWIG_BLOCK_MAGIC2(doa, message_sink_f);
%include "doa/add_const_ff.h"
GR_SWIG_BLOCK_MAGIC2(doa, add_const_ff);
%include "doa/phase2doa_ff.h"
GR_SWIG_BLOCK_MAGIC2(doa, phase2doa_ff);
%include "doa/hold_state_ff.h"
GR_SWIG_BLOCK_MAGIC2(doa, hold_state_ff);
