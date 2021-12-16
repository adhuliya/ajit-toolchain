#!/bin/bash

# Script that 
#       - boot the built Ajit-linux image on Ajit C model
#       - create a log of the Linux run
#       - copy the relevant br2 output, corresponding mmaps and log in a 
#               directory named <refname> within "logs"

CWD=$PWD

# Check for presence of Arguments and throw an error when there is none or invalid one.
if [ "$#" -ne 1 ] || [ "$1" -lt 0 ] || [ "$1" -gt 2 ]; then
  echo "ERROR: Invalid or missing argument...."
  echo "Usage: $0 <refname>"
  echo ""
  echo "Please provide a reference name for the Linux boot"
  echo " eg. $0 trial-run"
  exit 1
fi

mkdir logs/$1 && cd logs/$1
mkdir br2-output

cp $CWD/build/Generated_memory_map.f0004000/Output.f0004000/boot_loader_plus_kernel.mmap ./
cp -r $CWD/build/buildroot-2014.08/output/images/* ./br2-output

stdbuf -o 0 ajit_C_system_model -m ./boot_loader_plus_kernel.mmap -i 0xf0000000 2>&1 |tee $1-ajit.txt
