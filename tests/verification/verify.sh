#!/usr/bin/env bash

# The command.
_CMD="validation_outer_env_v3.py -j 1 -t 20000 -C "
_CWD="`pwd`";
_OUT_FILE="$_CWD/test-results.out";

# invariant check: check if the the script is run from its location
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )";
if [[ $DIR != "`pwd`" ]]; then
  echo "AD: Must run this script from its directory as './...'";
  exit;  # if not then exit
fi

{
  echo "You can review the output in file: $_OUT_FILE";
  sleep 1;

  echo -e "Testing STARTED: `date`\n\n" > $_OUT_FILE; 


  # Verify the 32 bit ajit
  _AJIT32_DIR="./ajit32/";

  bash -c "$_CMD $_AJIT32_DIR |& tee $_OUT_FILE";

  echo -e "\n\nYou can review the output in file: $_OUT_FILE";

} |& tee $_OUT_FILE;
