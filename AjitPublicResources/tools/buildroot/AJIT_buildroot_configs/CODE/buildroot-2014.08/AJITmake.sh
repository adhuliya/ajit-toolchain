#!/bin/bash

cd output/build/linux-3.16.1/arch/sparc/AJIT/device_tree/ 
./compile_device_tree.sh
cd -
#make AJIT_defconfig
make
