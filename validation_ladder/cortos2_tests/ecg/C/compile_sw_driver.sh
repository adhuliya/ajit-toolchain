#!/bin/bash
DEFINES="-D SW -D NAA2C -D NUSE_DOUBLE -D NMONITORBACKEND -D NMONITORFRONTEND -D NREADBACK -D NDEBUGPRINT "
INCLUDES="-I $AHIR_RELEASE/include -I include -I ./ "
LIBPATH="-L $AHIR_RELEASE/lib -L $UARTLIB"
LIBS="  -lBitVectors -lPipeHandler -l SockPipes -lm -lpthread "
CFLAGS=" -g "
rm -rf objsw
mkdir objsw
#./src:
gcc $CFLAGS -c src/best_fit.c  $DEFINES $INCLUDES -o objsw/best_fit.o
gcc $CFLAGS -c src/hermite_fitter.c $DEFINES $INCLUDES -o objsw/hermite_fitter.o
gcc $CFLAGS -c src/frontend.c $DEFINES $INCLUDES -o objsw/frontend.o
gcc $CFLAGS -c src/utils.c  $DEFINES $INCLUDES -o objsw/utils.o
gcc $CFLAGS -c src/beat.c  $DEFINES $INCLUDES -o objsw/beat.o
#rmdir -f aa2c
#mkdir -f aa2c
#Aa2C -P ajit_fpu_  Aa/ajit_fpu.aa  -o aa2c
#gcc $CFLAGS -D AA2C -c aa2c/ajit_fpu_aa_c_model.c -I aa2c/   $DEFINES $INCLUDES -o objsw/ajit_fpu_aa_c_model.o
gcc $CFLAGS -c src/fpops.c -I aa2c/ $DEFINES $INCLUDES -o objsw/fpops.o
gcc $CFLAGS -c src/derivative.c  $DEFINES $INCLUDES -o objsw/derivative.o
gcc $CFLAGS -c src/band_pass_filter.c  $DEFINES $INCLUDES -o objsw/band_pass_filter.o
gcc $CFLAGS -c src/moving_average.c  $DEFINES $INCLUDES -o objsw/moving_average.o
gcc $CFLAGS -c src/qrs_peak_detect.c  $DEFINES $INCLUDES -o objsw/qrs_peak_detect.o
gcc $CFLAGS -c src/result_buffer.c  $DEFINES $INCLUDES -o objsw/result_buffer.o
#./driver:
gcc $CFLAGS -c driver/config.c $DEFINES $INCLUDES -o objsw/config.o
gcc $CFLAGS -c driver/hermite.c $DEFINES $INCLUDES -o objsw/hermite.o
gcc $CFLAGS -c driver/test_best_fit.c $DEFINES $INCLUDES -o objsw/test_best_fit.o
gcc $CFLAGS -c driver/tb_utils.c $DEFINES $INCLUDES -o objsw/tb_utils.o
# link
if [ ! -d ./bin ] 
then
  mkdir bin
fi
gcc $CFLAGS -o bin/test_best_fit_sw objsw/*.o $LIBPATH $LIBS
