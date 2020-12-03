#!/usr/bin/env bash

# run the docker image -- takes one (optional) argument - the tag
# Names starting with `_` are not exported.

_NAME="ajit_build_dev";
_HOST_MOUNT_DIR="$(dirname $(dirname $(pwd)))"; # i.e. the whole ajit-toolchain git repo
_CONT_MOUNT_POINT="/home/ajit/ajit-toolchain";

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
echo "Ajit: Mounting Host Dir: $_HOST_MOUNT_DIR in container at $_CONT_MOUNT_POINT";
docker run \
  --detach \
  --name $_CONT_NAME \
  --mount type=bind,source=$_HOST_MOUNT_DIR,target=$_CONT_MOUNT_POINT \
  $_IMG_NAME;

echo "Ajit: Docker container started? Status: $? (Non Zero = ERROR)";


