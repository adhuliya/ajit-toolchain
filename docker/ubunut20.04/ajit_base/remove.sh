#!/usr/bin/env bash

# remove the docker container -- takes one argument - the container name

_CONT_NAME="ajit_base_20.04";

if [[ $1 != "" ]]; then
  _CONT_NAME="$1";
fi

docker rm --force $_CONT_NAME;
