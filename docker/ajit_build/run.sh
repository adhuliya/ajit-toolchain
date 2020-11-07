#!/usr/bin/env bash

# run the docker image -- takes one (optional) argument - the tag
# Names starting with `_` are not exported.

_NAME="ajit_build";

if [[ $1 != "" ]]; then
  _TAG="$1";
else
  _TAG="1.0";
fi

_IMG_NAME="$_NAME:$_TAG";
_CONT_NAME="$_NAME";

echo "Ajit: Removing any container with name '$_CONT_NAME'";
docker rm --force $_CONT_NAME;

echo "Ajit: Starting container with name '$_CONT_NAME'";
# if using --network="itsoflife" create the network first (only once):
#   docker network create itsoflife;
docker run \
  --detach \
  --name $_CONT_NAME \
  $_IMG_NAME;

echo "Ajit: Docker container started? Status: $?";


