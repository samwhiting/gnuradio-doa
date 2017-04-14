THIS_PATH = $(PWD)
OUT       = $(THIS_PATH)/out

# toolchain flags
EXTRA_CFLAGS = -Wall -fpic -DANDROID

# set the library name
LIB_NAME = libgr-doa

# paths to includes, sources, etc
SRC_PATH = $(THIS_PATH)/..
INC_PATH = -I$(SDKTARGETSYSROOT)/usr/include -I$(SRC_PATH)/lib -I$(SRC_PATH)/include

#------------------------------------------------------------------------------

all: clean create_out_dir compile_sources create_static_lib create_shared_lib install

create_out_dir:
	mkdir $(OUT)

compile_sources:
	$(CXX) $(EXTRA_CFLAGS) $(INC_PATH) -c $(SRC_PATH)/lib/capon_ccf_impl.cc -o $(OUT)/capon_ccf.o
	$(CXX) $(EXTRA_CFLAGS) $(INC_PATH) -c $(SRC_PATH)/lib/sample_offset_cci_impl.cc -o $(OUT)/sample_offset_cci.o
	$(CXX) $(EXTRA_CFLAGS) $(INC_PATH) -c $(SRC_PATH)/lib/delay_impl.cc -o $(OUT)/delay.o
	$(CXX) $(EXTRA_CFLAGS) $(INC_PATH) -c $(SRC_PATH)/lib/message_sink_i_impl.cc -o $(OUT)/message_sink_i.o
	$(CXX) $(EXTRA_CFLAGS) $(INC_PATH) -c $(SRC_PATH)/lib/message_sink_f_impl.cc -o $(OUT)/message_sink_f.o
	$(CXX) $(EXTRA_CFLAGS) $(INC_PATH) -c $(SRC_PATH)/lib/add_const_ff_impl.cc -o $(OUT)/add_const_ff.o
	$(CXX) $(EXTRA_CFLAGS) $(INC_PATH) -c $(SRC_PATH)/lib/hold_state_ff_impl.cc -o $(OUT)/hold_state_ff.o
	$(CXX) $(EXTRA_CFLAGS) $(INC_PATH) -c $(SRC_PATH)/lib/pi2pi_ff_impl.cc -o $(OUT)/pi2pi_ff.o
	$(CXX) $(EXTRA_CFLAGS) $(INC_PATH) -c $(SRC_PATH)/lib/phase2doa_ff_impl.cc -o $(OUT)/phase2doa_ff.o

create_static_lib:
	$(AR) rcs $(OUT)/$(LIB_NAME).a $(OUT)/capon_ccf.o $(OUT)/sample_offset_cci.o $(OUT)/delay.o $(OUT)/message_sink_i.o $(OUT)/message_sink_f.o \
	$(OUT)/add_const_ff.o $(OUT)/hold_state_ff.o $(OUT)/pi2pi_ff.o $(OUT)/phase2doa_ff.o

create_shared_lib:
	$(CC) -shared -o $(OUT)/$(LIB_NAME).so $(OUT)/capon_ccf.o $(OUT)/sample_offset_cci.o $(OUT)/delay.o $(OUT)/message_sink_i.o $(OUT)/message_sink_f.o \
	$(OUT)/add_const_ff.o $(OUT)/hold_state_ff.o $(OUT)/pi2pi_ff.o $(OUT)/phase2doa_ff.o

install:
	@echo ""
	mkdir -p $(SDKTARGETSYSROOT)/usr/include/doa
	cp $(OUT)/$(LIB_NAME).a $(SDKTARGETSYSROOT)/usr/lib/$(LIB_NAME).a
	cp $(OUT)/$(LIB_NAME).so $(SDKTARGETSYSROOT)/usr/lib/$(LIB_NAME).so
	@echo "  ** copied static (.a) and shared (.so) libraries to $(SDKTARGETSYSROOT)/usr/lib"
	cp $(SRC_PATH)/include/doa/api.h $(SDKTARGETSYSROOT)/usr/include/doa
	cp $(SRC_PATH)/include/doa/capon_ccf.h $(SDKTARGETSYSROOT)/usr/include/doa
	cp $(SRC_PATH)/include/doa/sample_offset_cci.h $(SDKTARGETSYSROOT)/usr/include/doa
	cp $(SRC_PATH)/include/doa/delay.h $(SDKTARGETSYSROOT)/usr/include/doa
	cp $(SRC_PATH)/include/doa/message_sink_i.h $(SDKTARGETSYSROOT)/usr/include/doa
	cp $(SRC_PATH)/include/doa/message_sink_f.h $(SDKTARGETSYSROOT)/usr/include/doa
	cp $(SRC_PATH)/include/doa/add_const_ff.h $(SDKTARGETSYSROOT)/usr/include/doa
	cp $(SRC_PATH)/include/doa/hold_state_ff.h $(SDKTARGETSYSROOT)/usr/include/doa
	cp $(SRC_PATH)/include/doa/pi2pi_ff.h $(SDKTARGETSYSROOT)/usr/include/doa
	cp $(SRC_PATH)/include/doa/phase2doa_ff.h $(SDKTARGETSYSROOT)/usr/include/doa
	@echo "  ** copied header files to $(SDKTARGETSYSROOT)/usr/include/doa"
	@echo ""

.PHONY: uninstall
uninstall:
	@echo ""
	rm -rf $(SDKTARGETSYSROOT)/usr/include/doa
	@echo "  ** removed $(SDKTARGETSYSROOT)/usr/include/doa include directory"
	rm  -f $(SDKTARGETSYSROOT)/usr/lib/$(LIB_NAME).a
	rm  -f $(SDKTARGETSYSROOT)/usr/lib/$(LIB_NAME).so
	@echo "  ** removed static (.a) and shared (.so) libraries from $(SDKTARGETSYSROOT)/usr/lib"
	@echo ""

clean:
	rm -fR $(OUT)
