# source this file

# Expects the env variables (see setup.sh):
#   ABS_BIN_DIR_PATH
#   BUILD_OUTFILE

echo "\n\n\n`date`\n\n" >> $BUILD_OUTFILE;

# STEP 0: Some basic tests.
if [[ ! -e $ABS_BIN_DIR_PATH ]]; then
  echo -e "\nERROR: $ABS_BIN_DIR_PATH doesn't exist. Cannot set path.\n" |& tee -a $BUILD_OUTFILE;
  exit 1;
fi

export PATH=$ABS_BIN_DIR_PATH:$PATH;


