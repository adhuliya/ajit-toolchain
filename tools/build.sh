#!/usr/bin/env bash

# must run this script from its absolute position

_CWD="`pwd`";
_OUT_BUILD_FILE="$_CWD/build.log";

function AND() {
  # Executes the given command. Exits on error.
  # Takes three arguments
  #  $1 Quoted Command
  #  $2 Error msg (optional)
  #  $3 Exit Code (optional)
  echo -e "\nAND: START:" "$1" "\n";
  bash -c "$1";
  local _EXITCODE=$?;
  if [[ $_EXITCODE != "0" ]]; then
    echo -e "AND: ERROR:($_EXITCODE): '$1'\n$2";
    exit $3;
  else
    echo -e "AND:  DONE: $1";
  fi
}

# invariant check: check if the the script is run from its location
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )";
if [[ $DIR != "`pwd`" ]]; then
  echo "AD: Must run this script from its directory as './...'";
  exit;  # if not then exit
fi

{
  echo -e "Log file: $_OUT_BUILD_FILE \n"; sleep 1;
  
  # invariant check: check if the the script is run from its location
  DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )";
  if [[ $DIR != "`pwd`" ]]; then
    echo "AD: Must run this script from its directory as './...'";
    exit;  # if not then exit
  fi

  if [[ -z $AHIR_RELEASE ]]; then
    echo "ERROR: Please set the env variable \$AHIR_RELEASE";
    echo "Find the file 'ahir_bashrc' and source it from its dir.";
    exit 1;
  fi

  echo -e "\nBuilding the tools.\n";     sleep 1;
  AND "scons";

} |& tee $_OUT_BUILD_FILE;


