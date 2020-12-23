#!/bin/bash
rm -rf lib/*.o lib/*.a
gcc -g -c src/fpunit_exec_exec_aa_c_model.c -I include/ -I $AHIR_RELEASE/include -o lib/fpunit_exec_exec_aa_c_model.o
ar -rcs lib/libFpExecAa.a lib/fpunit_exec_exec_aa_c_model.o 



