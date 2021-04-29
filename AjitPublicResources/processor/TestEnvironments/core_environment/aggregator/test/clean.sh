#!/bin/bash
cd test_bed
./clean.sh
rm -f *.o *_test_bench
cd -
cd tb
scons -c
cd -
