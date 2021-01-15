#!/usr/bin/env bash

# build the docker image -- takes one argument - the tag

_APP_NAME="ajit_toolchain";

if [[ $1 != "" ]]; then
  TAG="$1";
else
  TAG="1.0";
fi

docker build --tag $_APP_NAME:${TAG} ..;
