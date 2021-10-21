#!/bin/sh

# Simple script to cross-compile

NAME="hello"
SRC="$NAME.c"
BIN="$NAME.bin"

# compile using the cross-compiler
sparc-linux-gcc $SRC -o $BIN
