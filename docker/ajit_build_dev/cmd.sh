# source this file
# run an arbitrary command on the docker container

_IMG_NAME="ajit_build_dev";
_AJIT_HOME="/home/ajit/ajit-toolchain";

#docker exec -u $(id -nu) -w $_AJIT_HOME -it $_IMG_NAME  "$@";
docker run -u 500 -v $(pwd):$(pwd) -w $(pwd) -i -t ad27e3ebefb1  bash
