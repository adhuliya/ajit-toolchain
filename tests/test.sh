#!/usr/bin/env bash

TEST_DIR=$AJIT_HOME/tests;

# A test case directory is identified by the presence
# of the following file:
_TEST_FILE="Ajit.TestCase";
_TMP_FILE="tmp_test_dirs.out";
# _TEST_STRING="Tests Successful."; # unused

function AND() {
  # Executes the given command. Exits on error.
  # Takes three arguments
  #  $1 Quoted Command
  #  $2 Error msg (optional)
  #  $3 Exit Code (optional)
  sh -c "$1";
  local _EXITCODE=$?;
  if [[ $_EXITCODE != "0" ]]; then
    echo -e "AND: ERROR:($_EXITCODE): '$1'\n$2";
    exit $3;
  fi
}

function OR() {
  # Executes the given command. Continues on error.
  # Takes three arguments
  #  $1 Quoted Command
  #  $2 Error msg (optional)
  echo -e "\nOR: START:" "$1" "\n";
  sh -c "$1";
  local _EXITCODE=$?;
  if [[ $_EXITCODE != "0" ]]; then
    echo -e "OR: ERROR:($_EXITCODE): '$1'\n$2";
  else
    echo -e "OR:  DONE: $1";
  fi
}

# STEP 1: Discover all the tests.
AND "find -name $_TEST_FILE" > $_TMP_FILE;


# STEP 2: Run each test.
_FAILED=0;
_COUNT=0;
_TOTAL=`cat $_TMP_FILE | wc -l`;
_CWD=`pwd`;
while read x; do
  _COUNT=$((_COUNT+1));
  _DIR=`dirname "$x"`;
  cd $_DIR;
  ./build.sh &> /dev/null;
  if ./run_cmodel.sh &> /dev/null < /dev/null; then
    echo "SUCCESS($_COUNT/$_TOTAL): $_DIR";
  else
    _FAILED=$((_FAILED+1));
    echo "FAILURE($_COUNT/$_TOTAL): $_DIR";
  fi
  cd $_CWD;
done < $_TMP_FILE;

echo -e "\nTEST SUMMARY: $((_TOTAL - _FAILED)) passed. $_FAILED failed.\n";


