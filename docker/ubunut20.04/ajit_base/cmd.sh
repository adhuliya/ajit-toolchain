# source this file
# run an arbitrary command on the docker container

_IMG_NAME="ajit_base_20.04";
_AJIT_HOME="/home/ajit/ajit-toolchain";

docker exec -w $_AJIT_HOME -it $_IMG_NAME  "$@";
