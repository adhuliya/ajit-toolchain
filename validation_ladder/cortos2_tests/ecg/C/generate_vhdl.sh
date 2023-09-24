#!/bin/bash
DEFINES="-D FPGA -D NUSE_DOUBLE -D NMONITORBACKEND -D NMONITORFRONTEND -D NREADBACK -D FREADWRITE "
INCLUDES="-I $AHIR_RELEASE/include -I include"
LIBPATH="-L $AHIR_RELEASE/lib "
LIBS=" -lpthread -lPipeHandler -lm "
CFLAGS=" -m32 -O3 -std=gnu89 -emit-llvm  "
#LLVM2AAOPTS="-extract_do_while=true --storageinit=true -pipedepths=pipedepths.txt"
LLVM2AAOPTS=" -extract_do_while=true "
TOPMODULES=" -T controllerDaemon -T hermiteFitterDaemon -T beatDaemon"
rm -rf objvhdl
mkdir objvhdl
rm -rf .Aa
mkdir .Aa
rm -rf .vC
mkdir .vC
#./src:
clang $CFLAGS -c src/best_fit.c  $DEFINES $INCLUDES -o objvhdl/best_fit.o
opt --indvars --loopsimplify objvhdl/best_fit.o -o objvhdl/best_fit.opt.o
llvm-dis objvhdl/best_fit.opt.o -o objvhdl/best_fit.opt.o.ll
llvm2aa $LLVM2AAOPTS  objvhdl/best_fit.opt.o | vcFormat > .Aa/best_fit.aa

clang $CFLAGS -c src/hermite_fitter.c $DEFINES $INCLUDES -o objvhdl/hermite_fitter.o
opt --indvars --loopsimplify objvhdl/hermite_fitter.o -o objvhdl/hermite_fitter.opt.o
llvm-dis objvhdl/hermite_fitter.opt.o -o objvhdl/hermite_fitter.opt.o.ll
llvm2aa $LLVM2AAOPTS  objvhdl/hermite_fitter.opt.o | vcFormat > .Aa/hermite_fitter.aa

clang $CFLAGS -c src/frontend.c $DEFINES $INCLUDES -o objvhdl/frontend.o
opt --indvars --loopsimplify objvhdl/frontend.o -o objvhdl/frontend.opt.o
llvm-dis objvhdl/frontend.opt.o -o objvhdl/frontend.opt.o.ll
llvm2aa $LLVM2AAOPTS  objvhdl/frontend.opt.o | vcFormat > .Aa/frontend.aa

clang $CFLAGS -c src/result_buffer.c $DEFINES $INCLUDES -o objvhdl/result_buffer.o
opt --indvars --loopsimplify objvhdl/result_buffer.o -o objvhdl/result_buffer.opt.o
llvm-dis objvhdl/result_buffer.opt.o -o objvhdl/result_buffer.opt.o.ll
llvm2aa $LLVM2AAOPTS  objvhdl/result_buffer.opt.o | vcFormat > .Aa/result_buffer.aa

clang $CFLAGS -c src/beat.c  $DEFINES $INCLUDES -o objvhdl/beat.o
opt --indvars --loopsimplify objvhdl/beat.o -o objvhdl/beat.opt.o
llvm-dis objvhdl/beat.opt.o -o objvhdl/beat.opt.o.ll
llvm2aa $LLVM2AAOPTS  objvhdl/beat.opt.o | vcFormat > .Aa/beat.aa


clang $CFLAGS -c src/derivative.c  $DEFINES $INCLUDES -o objvhdl/derivative.o
opt --indvars --loopsimplify objvhdl/derivative.o -o objvhdl/derivative.opt.o
llvm-dis objvhdl/derivative.opt.o -o objvhdl/derivative.opt.o.ll
llvm2aa $LLVM2AAOPTS  objvhdl/derivative.opt.o | vcFormat > .Aa/derivative.aa

clang $CFLAGS -c src/band_pass_filter.c  $DEFINES $INCLUDES -o objvhdl/band_pass_filter.o
opt --indvars --loopsimplify objvhdl/band_pass_filter.o -o objvhdl/band_pass_filter.opt.o
llvm-dis objvhdl/band_pass_filter.opt.o -o objvhdl/band_pass_filter.opt.o.ll
llvm2aa $LLVM2AAOPTS  objvhdl/band_pass_filter.opt.o | vcFormat > .Aa/band_pass_filter.aa

clang $CFLAGS -c src/moving_average.c  $DEFINES $INCLUDES -o objvhdl/moving_average.o
opt --indvars --loopsimplify objvhdl/moving_average.o -o objvhdl/moving_average.opt.o
llvm-dis objvhdl/moving_average.opt.o -o objvhdl/moving_average.opt.o.ll
llvm2aa $LLVM2AAOPTS  objvhdl/moving_average.opt.o | vcFormat > .Aa/moving_average.aa

clang $CFLAGS -c src/qrs_peak_detect.c  $DEFINES $INCLUDES -o objvhdl/qrs_peak_detect.o
opt --indvars --loopsimplify objvhdl/qrs_peak_detect.o -o objvhdl/qrs_peak_detect.opt.o
llvm-dis objvhdl/qrs_peak_detect.opt.o -o objvhdl/qrs_peak_detect.opt.o.ll
llvm2aa $LLVM2AAOPTS  objvhdl/qrs_peak_detect.opt.o | vcFormat > .Aa/qrs_peak_detect.aa

AaLinkExtMem .Aa/band_pass_filter.aa .Aa/result_buffer.aa .Aa/best_fit.aa .Aa/beat.aa .Aa/derivative.aa .Aa/frontend.aa .Aa/hermite_fitter.aa .Aa/moving_average.aa .Aa/qrs_peak_detect.aa Aa/utils.aa Aa/fp_enhanced.aa  | vcFormat > .Aa/ecg.linked.aa
AaOpt -C .Aa/ecg.linked.aa | vcFormat > .Aa/ecg.linked.optC.aa
AaOpt -B .Aa/ecg.linked.optC.aa | vcFormat > .Aa/ecg.linked.opt.aa
Aa2VC -O -C -r controllerDaemon -r hermiteFitterDaemon -r beatDaemon .Aa/ecg.linked.opt.aa | vcFormat > .vC/ecg.vc

	
# generate vhdl from vc
rm -rf vhdl
mkdir vhdl
vc2vhdl  -O -I 2  -a -C -e ecg_core -w -s ghdl $TOPMODULES -f .vC/ecg.vc 
vhdlFormat < ecg_core_global_package.unformatted_vhdl > vhdl/ecg_core_global_package.vhdl
vhdlFormat < ecg_core.unformatted_vhdl > vhdl/ecg_core.vhdl
vhdlFormat < ecg_core_test_bench.unformatted_vhdl > vhdl/ecg_core_test_bench.vhdl
rm -f *.unformatted_vhdl

