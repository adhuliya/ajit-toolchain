#!/bin/bash

CWD=$PWD
BUILD_FPGA_DIR=$CWD/build/fpga

# Check for presence of Arguments and throw an error when there is none or invalid one.
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
  ./GeneratememMapForAjit.sh $1
  echo ""
  ./vmLinuzToMemmapAtf0004000.sh
  cd $BUILD_FPGA_DIR/linux_boot
  ./compile.sh
} |& tee $CWD/build/build.log

# # Smarter script. WORK IN PROGRESS

# pflag=
# rflag=

# function usage_message() {
#   echo "ERROR: Invalid or missing argument...."
#   echo "Usage: $0 -p <PLATFORM> -r <ROOTFS>"
#   echo ""
#   echo "PLATFORM values"
#   echo "    cmodel "
#   echo "    fpga "
#   echo ""
#   echo "ROOTFS values"
#   echo "    initramfs "
#   echo "    tmpfs "
#   exit 1
# }

# # Check for presence of Arguments and throw an error when there is none or invalid one.
# if [ -z "$1" ]; then
#   usage_message
#   exit 1
# fi

# while getopts p:r: name
# do
#     case $name in
#     p)  pflag=1
#         pval="$OPTARG";;
#     r)  rflag=1
#         rval="$OPTARG";;
#     ?)  usage_message
#         exit 2;;
#     esac
# done

# if [ ! -z "$pflag" ]; then
#     printf 'Option -r "%s" specified\n' "$pval"
# fi
# if [ ! -z "$rflag" ]; then
#     printf 'Option -c "%s" specified\n' "$rval"
# fi