#!/usr/bin/env bash

# build the docker image -- takes one argument - the tag

_IMG_NAME="ajit_build_dev";

if [[ $1 != "" ]]; then
  _TAG="$1";
else
  _TAG="1.0";
fi

cp Dockerfile ../../;

docker build --tag $_IMG_NAME:$_TAG ../..;
