#!/bin/bash
# clean up
buildHierarchicalModel.py -R -a sys_test_bed
rm -f *.o *.cf *.ghw *.log *_test_bench
