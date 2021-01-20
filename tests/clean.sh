#!/usr/bin/env bash

# invariant check: check if the the script is run from its location
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )";
if [[ $DIR != "`pwd`" ]]; then
  echo "AD: Must run this script from its directory as './...'";
  exit;  # if not then exit
fi


rm -Rf test-results.out &> /dev/null;

cd verification;
./clean.sh;


