# this file is automatically sourced

# Expects the env variables (see setup.sh):
#   BUILDROOT_DIR_NAME
#   BUILDROOT_SOURCE_TAR
#   RELATIVE_BIN_DIR_PATH
#   BUILD_OUTFILE
#   DEVELOPMENT

# Assumptions:
#   1. Assumes the following files are in the src folder are:
#        * buildroot-2014.08-offline.tar.gz
#        * cfns.h
#        * e_sqrt.c
#        * README.md
#        * update-all-ajit-code-and-run-tests.sh

if [[ -e $BUILDROOT_DIR_NAME ]]; then
  echo "ERROR: $BUILDROOT_DIR_NAME already exists." |& tee -a $BUILD_OUTFILE;
  exit 2;
fi

if [[ ! -e "src/$BUILDROOT_DIR_NAME" ]]; then
  echo "ERROR: src/$BUILDROOT_DIR_NAME doesn't exist in the current directory" |& tee -a $BUILD_OUTFILE;
  exit 1;
fi

if [[ ! -e src/cfns.h ]]; then
  echo "ERROR: cfns.h doesn't exist in the current directory" |& tee -a $BUILD_OUTFILE;
  exit 1;
fi

if [[ ! -e src/e_sqrt.c ]]; then
  echo "ERROR: e_sqrt.c doesn't exist in the current directory" |& tee -a $BUILD_OUTFILE;
  exit 1;
fi

if [[ ! -e src/update-all-ajit-code-and-run-tests.sh ]]; then
  echo "ERROR: update-all-ajit-code-and-run-tests.sh doesn't exist in the current directory" |& tee -a $BUILD_OUTFILE;
  exit 1;
fi

if [[ ! -e "src/$DEVELOPMENT" ]]; then
  echo "ERROR: src/$DEVELOPMENT doesn't exist in the current directory" |& tee -a $BUILD_OUTFILE;
  exit 1;
fi

