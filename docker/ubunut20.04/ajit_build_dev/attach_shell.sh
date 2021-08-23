#!/usr/bin/env bash
# execute or source this file

_IMG_NAME="ajit_build_dev_20.04";
_AJIT_HOME="/home/ajit/ajit-toolchain";

for x in "root" "sudo"; do
  if [[ $x == $1 ]]; then
    ## Attach shell as root user (use only when necessary):
    docker exec -w $_AJIT_HOME -it $_IMG_NAME  /bin/bash;
    exit;
  fi
done

# If the above for loop doesn't lead to exit then attache shell as normal user.
# Attach shell as a normal user:
docker exec -u $(id -nu) -w $_AJIT_HOME -it $_IMG_NAME  /bin/bash;


