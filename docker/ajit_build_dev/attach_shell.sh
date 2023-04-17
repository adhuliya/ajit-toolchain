#!/usr/bin/env bash
# execute or source this file

for x in "root" "sudo"; do
  if [[ $x == $1 ]]; then
    ## Attach shell as root user (use only when necessary):
    docker exec -w /home/ajit/ajit-toolchain -it ajit_build_dev  /bin/bash;
    exit;
  fi
done

# If the above for loop doesn't lead to exit then attache shell as normal user.
# Attach shell as a normal user:
docker exec -u $(id -nu) -w /home/ajit/ajit-toolchain -it ajit_build_dev  /bin/bash;


