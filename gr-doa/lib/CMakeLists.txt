# Copyright 2011,2012,2016 Free Software Foundation, Inc.
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
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
list(APPEND doa_sources
    capon_ccf_impl.cc
    unwrap_ff_impl.cc
    linearslope_ff_impl.cc
    mode_ii_impl.cc
    lin_delay_cc_impl.cc
    peak_estimator_cif_impl.cc
    cub_delay_cc_impl.cc
    cumulative_ff_impl.cc
    variance_ff_impl.cc
    zero_pad_cc_impl.cc
    sample_offset_cci_impl.cc
    hold_ii_impl.cc
    hold_ff_impl.cc
    full_capon_ccf_impl.cc
    full_capon3_ccf_impl.cc
    multiply_exp_cc_impl.cc
    pi2pi_ff_impl.cc
    delay_impl.cc
    message_sink_i_impl.cc
    message_sink_f_impl.cc
    add_const_ff_impl.cc
    phase2doa_ff_impl.cc
    hold_state_ff_impl.cc )

set(doa_sources "${doa_sources}" PARENT_SCOPE)
if(NOT doa_sources)
	MESSAGE(STATUS "No C++ sources... skipping lib/")
	return()
endif(NOT doa_sources)

add_library(gnuradio-doa SHARED ${doa_sources})
target_link_libraries(gnuradio-doa ${Boost_LIBRARIES} ${GNURADIO_ALL_LIBRARIES})
set_target_properties(gnuradio-doa PROPERTIES DEFINE_SYMBOL "gnuradio_doa_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-doa PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
include(GrMiscUtils)
GR_LIBRARY_FOO(gnuradio-doa RUNTIME_COMPONENT "doa_runtime" DEVEL_COMPONENT "doa_devel")

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})
list(APPEND test_doa_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_doa.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_doa.cc
    )

add_executable(test-doa ${test_doa_sources})

target_link_libraries(
  test-doa
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-doa
)

GR_ADD_TEST(test_doa test-doa)

########################################################################
# Print summary
########################################################################
message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Building for version: ${VERSION} / ${LIBVER}")

