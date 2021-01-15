#!/usr/bin/env bash
# execute or source this file

_IMG_NAME="ajit_base";
_AJIT="/home/ajit";

docker exec -w $_AJIT -it $_IMG_NAME  /bin/bash;
