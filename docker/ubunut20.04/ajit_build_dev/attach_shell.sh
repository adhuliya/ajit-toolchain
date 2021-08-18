#!/usr/bin/env bash
# execute or source this file

_IMG_NAME="ajit_build_dev_20.04";
_AJIT_HOME="/home/ajit/ajit-toolchain";

# Attach shell as a normal user:
docker exec -u $(id -nu) -w $_AJIT_HOME -it $_IMG_NAME  /bin/bash;


## Attach shell as root user (use only when necessary):
#docker exec -w $_AJIT_HOME -it $_IMG_NAME  /bin/bash;
