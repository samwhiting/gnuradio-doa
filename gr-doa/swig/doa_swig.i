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
