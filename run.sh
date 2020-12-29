#!/usr/bin/env bash

# run the docker image -- takes one (optional) argument - the tag
# Names starting with `_` are not exported.

# For production either don't define DEV_SERVER env variable or
# set it to an empty string. (by default production is assumed)

# MUST run this script as `./run.sh`

# invariant check: check if the the script is run from its location
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )";
if [[ $DIR != "`pwd`" ]]; then
  echo "AD: Must run this script from its directory as './...'";
  exit;  # if not then exit
fi

# docker container defaults (see the Dockerfile for comments)
# These variables should be in sync with ../Dockerfile ENV settings
_DOCKER_DJANGO_PROJECT=/app/app
_DOCKER_RUN=/app/run
_DOCKER_DATA=/app/data
_DOCKER_SECRETS=/app/secrets
_DOCKER_KNOTS=/app/mnt/knots-git
_DOCKER_MYDATA=/app/mnt/mydata

# DigitalOcean droplet defaults
_HOST_BASE_DIR=/home/admin;
_HOST_DJANGO_PROJECT="`pwd`/../app";  # the path in host
_CONT_NAME="mysite";
_VOL_NAME="iol";
_NET_NAME="iol";
_HOST_IP="0.0.0.0";
_HOST_PORT=80;
_SSL_PORT=443;

# run server inits
_HOST_RUN=$_HOST_DJANGO_PROJECT/../run;
_HOST_SECRETS=$_HOST_DJANGO_PROJECT/../secrets;
_HOST_KNOTS=$_HOST_BASE_DIR/knots-git;
_HOST_MYDATA=$_HOST_BASE_DIR/mydata;

if [[ -n "$DEV_SERVER" ]];
then
  # its a development server
  echo "AD: Going to run DEVELOPMENT server!";
  _HOST_KNOTS=/home/codeman/.itsoflife/knots-git;
  _HOST_MYDATA=/home/codeman/.itsoflife/mydata;
  _HOST_PORT=5055;
  _SSL_PORT=4430;
else
  echo "AD: Going to run PRODUCTION server!"; # default
fi

echo "AD: Removing any container with name '$_CONT_NAME'";
/usr/bin/docker rm --force $_CONT_NAME;

if [[ $1 != "" ]]; then
  _TAG="$1";
else
  _TAG="1.0";
fi

echo "AD: Starting container with name '$_CONT_NAME'";
# if using --network="iol" create the network first (only once):
#   docker network create iol;
/usr/bin/docker run \
  --detach \
  --ulimit nofile=100000:100000 \
  --publish $_HOST_IP:$_HOST_PORT:5050 \
  --publish $_HOST_IP:$_SSL_PORT:443 \
  --mount type=bind,source=$_HOST_DJANGO_PROJECT,target=$_DOCKER_DJANGO_PROJECT \
  --mount type=bind,source=$_HOST_SECRETS,target=$_DOCKER_SECRETS,readonly \
  --mount type=bind,source=$_HOST_RUN,target=$_DOCKER_RUN,readonly \
  -v $_VOL_NAME:$_DOCKER_DATA \
  --mount type=bind,source=$_HOST_KNOTS,target=$_DOCKER_KNOTS,readonly \
  --mount type=bind,source=$_HOST_MYDATA,target=$_DOCKER_MYDATA,readonly \
  --env DEV_SERVER="$DEV_SERVER" \
  --network=$_NET_NAME \
  --name $_CONT_NAME \
  $_CONT_NAME:$_TAG;

echo "AD: Docker container started? Status: $? (Non-zero = Error)";

# REFS:
#  https://ss64.com/bash/ulimit.html

