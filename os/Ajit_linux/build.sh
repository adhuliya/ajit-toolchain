#!/bin/bash

CWD=$PWD

# Check for presence of Argumentsand throw an error when there is none or invalid one.
if [ "$#" -ne 1 ] || [ "$1" -lt 0 ] || [ "$1" -gt 3 ]; then
  echo "ERROR: Invalid or missing argument...."
  echo "Usage: $0 <DEFCONFIG>"
  echo ""
  echo "DEFCONFIG values"
  echo "    <1> legacy initramfs system config;no rootfs-tmpfs present"
  echo "    <2> rootfs-tmpfs with satic-lib & static device list"
  exit 1
fi

{
./GeneratememMapForAjit.sh $1 && \
echo "" && \
./vmLinuzToMemmapAtf0004000.sh
} |& tee $CWD/build/build.log

