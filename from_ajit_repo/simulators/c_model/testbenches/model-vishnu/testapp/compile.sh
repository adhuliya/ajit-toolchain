#!/bin/bash

gcc -o run \
        main.c \
        ../model/src/Device_utils.c \
        ../model/common/src/Ancillary.c \
        ../model/src/sdhc_helper.c \
        ../model/src/sdhc.c \
        -I ../model/include/ \
        -I ../model/common/include \
        -I $AHIR_RELEASE/include \
        -L $AHIR_RELEASE/lib \
        -lPipeHandler -lBitVectors -lpthread -lm