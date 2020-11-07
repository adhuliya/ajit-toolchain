#!/usr/bin/env bash
# Copy data from a docker volume.

_VOL_NAME=ajit

# copy the current direcotry to the volume
docker run
  --rm \
  -v `pwd`:/src \
  -v $_VOL_NAME:/data \
  busybox \
  cp -r /data /src;
  
# the last line above could also be:
#   tar cvf /src/backup.tar /data;


# Another method:
# # create a temporary container (busybox image comes with docker)
# docker container create --name $_CONT_NAME -v $_VOL_NAME:/data busybox;
# 
# # copy the current directory contents
# docker cp . $_CONT_NAME:/data;
# 
# # delete the container
# docker rm $_CONT_NAME;

