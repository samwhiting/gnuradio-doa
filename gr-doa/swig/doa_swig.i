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
#include "doa/peak_estimator_cff.h"
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
%include "doa/peak_estimator_cff.h"
GR_SWIG_BLOCK_MAGIC2(doa, peak_estimator_cff);
