#!/usr/bin/env bash

_CWD="`pwd`";
_OUT_FILE="$_CWD/test-results.out";

# A test case directory is identified by the presence
# of the following file:
_TEST_FILE="Ajit.TestCase";
_TMP_FILE="tmp_test_dirs.out";
# _TEST_STRING="Tests Successful."; # unused


# invariant check: check if the the script is run from its location
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )";
if [[ $DIR != "`pwd`" ]]; then
  echo "AD: Must run this script from its directory as './...'";
  exit;  # if not then exit
fi


{
  # STEP 1: Run each test.
  _FAILED=0;
  _COUNT=0;
  _TOTAL=$(find -name "$_TEST_FILE" | wc -l);
  _CWD=`pwd`;
  find -name "$_TEST_FILE" |\
    while read x; do
      _COUNT=$((_COUNT+1));
      _DIR=`dirname "$x"`;
      cd $_DIR;
      ./build.sh;
      if ./run_cmodel.sh < /dev/null; then
        echo -e "\nSUCCESS($_COUNT/$_TOTAL): $_DIR\n";
      else
        _FAILED=$((_FAILED+1));
        echo -e "\nFAILURE($_COUNT/$_TOTAL): $_DIR\n";
      fi
      ./clean.sh;
      cd $_CWD;
    done;


  # STEP 2: Print the summary.
  echo -e "\nTEST SUMMARY: $((_TOTAL - _FAILED)) passed. $_FAILED failed.\n";
} |& tee $_OUT_FILE;


