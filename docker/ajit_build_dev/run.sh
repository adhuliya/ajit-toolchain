#!/usr/bin/env bash

# run the docker image -- takes one (optional) argument - the tag
# Names starting with `_` are not exported.

echo "Ajit: Removing any container with name ajit_build_dev";
docker rm --force ajit_build_dev;

echo "Ajit: Starting container with name ajit_build_dev";
echo "Ajit: Mounting Host Dir: ajit-toolchain in container at $_CONT_MOUNT_POINT";
docker run \
  --detach \
  --name ajit_build_dev \
  -v $(dirname $(dirname $(pwd))):/home/ajit/ajit-toolchain \
  ajit_build_dev:1.0;
##To use USB devices inside docker, add the line given below to the 'docker run' command- 
##  -v /dev:/dev --device-cgroup-rule='c 188:* rmw' \ 
echo -e "\nAjit: Docker container started? Status: $? (Non Zero = ERROR)";


