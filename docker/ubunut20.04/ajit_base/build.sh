#!/usr/bin/env bash

# build the docker image -- takes one argument - the tag

_IMG_NAME="ajit_base_20.04";

if [[ $1 != "" ]]; then
  TAG="$1";
else
  TAG="1.0";
fi

docker build --tag $_IMG_NAME:${TAG} .;
