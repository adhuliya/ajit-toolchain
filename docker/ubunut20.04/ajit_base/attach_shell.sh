#!/usr/bin/env bash
# execute or source this file

_IMG_NAME="ajit_base_20.04";
_AJIT="/home/ajit";

docker exec -w $_AJIT -it $_IMG_NAME  /bin/bash;
