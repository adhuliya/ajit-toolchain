#!/bin/bash
UARTINCL="./uart_interface/include"
UARTLIB="./uart_interface/lib"
DEFINES=" -D FPGA -D NUSE_DOUBLE -D FREADWRITE  -D NDEBUGPRINT "
INCLUDES="-I $AHIR_RELEASE/include -I include -I ./ -I $UARTINCL"
LIBPATH="-L $AHIR_RELEASE/lib -L $UARTLIB"
LIBS="  -lBitVectors -lPipeHandler -l SockPipes -lm -luart_interface -lpthread "
CFLAGS=" -g "
rm -rf objsw
mkdir objsw
#./driver:
gcc $CFLAGS -c driver/tb_utils.c $DEFINES $INCLUDES -o objsw/tb_utils.o
gcc $CFLAGS -c driver/receive_fits.c $DEFINES $INCLUDES -o objsw/receive_fits.o
# link
if [ ! -d ./bin ] 
then
  mkdir bin
fi
gcc $CFLAGS -o bin/receive_fits objsw/*.o $LIBPATH $LIBS
