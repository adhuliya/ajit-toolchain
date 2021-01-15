#!/usr/bin/env bash

# This script builds the buildroot with the required features.

# Expects the env variables (see setup.sh):
#   BUILDROOT_DIR_NAME
#   BUILDROOT_SOURCE_TAR
#   RELATIVE_BIN_DIR_PATH
#   BUILD_OUTFILE


echo -e "\nStarting build.\n" |& tee -a $BUILD_OUTFILE;
sleep 3;

# STEP 1: Copying BUILDROOT_DIR_NAME
echo "Copying $SRC/$BUILDROOT_DIR_NAME" |& tee -a $BUILD_OUTFILE;
sleep 3;
cp -r $SRC/$BUILDROOT_DIR_NAME $BUILD_DIR/$BUILDROOT_DIR_NAME;

# STEP 1.5: Merge the splits of gcc and linuz archives
cd $BUILD_DIR/$BUILDROOT_DIR_NAME/dl;
cat gcc-4.7.4.tar.bz2.aa gcc-4.7.4.tar.bz2.ab > gcc-4.7.4.tar.bz2;
cat linux-3.15.6.tar.xz.aa linux-3.15.6.tar.xz.ab > linux-3.15.6.tar.xz;

# STEP 2: Start the build

cd $BUILD_DIR/$BUILDROOT_DIR_NAME;
echo "Changing directory to $BUILDROOT_DIR_NAME" |& tee -a $BUILD_OUTFILE;
cd $BUILD_DIR/$BUILDROOT_DIR_NAME;

echo -e "\nStarting make\n" |& tee -a $BUILD_OUTFILE;
sleep 3;
make |& tee -a $BUILD_OUTFILE;


# STEP 3 : If the above leads to the following error:
#     cfns.gprof:101:1:error: 'gnu_inline' attribute present on 'libc_name_p'
#     cfns.gprof:26:14:error: but not here
# Resource: <https://unix.stackexchange.com/questions/335717/how-to-handle-error-compiling-gcc-4-7-0-using-gcc-6-2-1>
# then replace the cfns.h header in three locations with the cfns.h in this folder.

COUNT=`egrep "cfns.gperf.* error: .* attribute present" $BUILD_OUTFILE | wc -l`

echo "The error count is : $COUNT" |& tee -a $BUILD_OUTFILE;

if [[ $COUNT -gt 0 ]]; then
  echo -e "\nCopying cfns.h to mitigate make error ...\n" |& tee -a $BUILD_OUTFILE;
  sleep 3;

  DIR_PREFIX=output/build
  CFNS_FILE=$SRC/cfns.h

  if [[ ! -e $DIR_PREFIX ]]; then
    echo "ERROR: Directory $DIR_PREFIX doesn't exist in $BUILD_DIR/$BUILDROOT_DIR_NAME" |& tee -a $BUILD_OUTFILE;
    exit 1;
  fi

  cp $CFNS_FILE ./$DIR_PREFIX/host-gcc-initial-4.7.4/gcc/cp/cfns.h
  cp $CFNS_FILE ./$DIR_PREFIX/host-gcc-final-4.7.4/gcc/cp/cfns.h
  cp $CFNS_FILE ./$DIR_PREFIX/host-gcc-intermediate-4.7.4/gcc/cp/cfns.h

  # restart make
  echo -e "\nRestarting make for ${CFNS_FILE} error.\n" |& tee -a $BUILD_OUTFILE;
  sleep 3;
  make |& tee -a $BUILD_OUTFILE;
fi


# STEP 4: update the e_sqrt.c file and do a quick rebuild

echo -e "\nUpdating the e_sqrt.c file ...\n" |& tee -a $BUILD_OUTFILE;
sleep 3;
cp $SRC/e_sqrt.c output/build/uclibc-0.9.33.2/libm;
cd output/build/uclibc-0.9.33.2;
echo -e "\nRestarting make for e_sqrt.c update.\n" |& tee -a $BUILD_OUTFILE;
sleep 3;
make |& tee -a $BUILD_OUTFILE;



