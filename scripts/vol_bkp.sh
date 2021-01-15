#!/usr/bin/env bash
# Take backup of the given volume.
# Takes one optional argument: volume name

_VOL_NAME=ajit;

if [[ $1 != "" ]]; then
  _VOL_NAME="$1";
fi

_BKP_FILE="${_VOL_NAME}_$(date +%Y%m%d.%H%M%S).bkp.tgz"

docker run \
  --rm \
  -v `pwd`:/src \
  -v $_VOL_NAME:/data \
  busybox \
  tar czvf /src/$_BKP_FILE /data;
  

