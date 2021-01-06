#!/usr/bin/env bash
find ajit32 -type d | \
  while read x; do
    if [ ! -f $x/*.vprj ]; then continue; fi
    pushd $x # &> /dev/null;
    validation_outer_env_v3.py -j 1 -t 10 -C ./;
    popd # &> /dev/null;
    exit;
  done;


