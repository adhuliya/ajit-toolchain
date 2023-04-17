#!/usr/bin/env bash
# Maintainer: Anshuman Dhuliya (anshumandhuliya@gmail.com)

# This script builds the required docker images
# It depends on the $AJIT_HOME env variable.

_OUT_FILE=$AJIT_HOME/docker_build.log;

isdocker () {
  local count=$(cat /proc/1/cgroup | grep "/docker" | wc -l);
  if [[ count -eq 0 ]]; then false; else true; fi
}

function AND() {
  # Executes the given command. Exits on error.
  # Takes three arguments
  #  $1 Quoted Command
  #  $2 Error msg (optional)
  #  $3 Exit Code (optional)
  echo -e "\nAND: START:" "$1" "\n";
  bash -c "$1";
  local _EXITCODE=$?;
  if [[ $_EXITCODE != "0" ]]; then
    echo -e "AND: ERROR:($_EXITCODE): '$1'\n$2";
    exit $3;
  else
    echo -e "AND:  DONE: $1";
  fi
}


if [[ -z $AJIT_HOME ]]; then
  echo "ERROR: Please set the env variable \$AJIT_HOME";
  echo "USE COMMAND: source ./set_ajit_home";
  exit 1;
fi


{
  echo -e "\nSee log file: $_OUT_FILE\n";
  sleep 1;

  if isdocker; then
    echo "Inside a docker container. EXITING!"
    exit 1;
  fi


  if ! which docker; then
    # install docker first
    AND "$AJIT_HOME/install_docker.sh";
  fi
  echo "Good. Docker is installed!";
  sleep 1;

  mkdir -p $AJIT_HOME/build;
  wget --no-check-certificate --load-cookies /tmp/cookies.txt "https://docs.google.com/uc?export=download&confirm=$(wget --quiet --save-cookies /tmp/cookies.txt --keep-session-cookies --no-check-certificate 'https://docs.google.com/uc?export=download&id=1ck2jSq8LTO-q2RFrwc49mPkXTH9LecVx' -O- | sed -rn 's/.*confirm=([0-9A-Za-z_]+).*/\1\n/p')&id=1ck2jSq8LTO-q2RFrwc49mPkXTH9LecVx" -O docker/ajit_build_dev.tar && rm -rf /tmp/cookies.txt
  docker load -i $AJIT_HOME/docker/ajit_build_dev.tar;

##  echo -e "\n\n\n\n\n";
##  echo "################################################";
##  echo "##  Building ajit_base image.";
##  echo "################################################";
##  sleep 1;
##  pushd $AJIT_HOME/docker/ajit_base;
##  ./build.sh;
##  popd;


  echo -e "\n\n\n\n\n";
  echo "################################################";
  echo "##  Building ajit_build_dev image.";
  echo "################################################";
  sleep 1;
  pushd $AJIT_HOME/docker/ajit_build_dev;
  ./run.sh;
  popd;


  ################################################################################
  exit;  ############## Comment this line if images below are needed #############
  ################################################################################


  echo -e "\n\n\n\n\n";
  echo "################################################";
  echo "##  Building ajit_build image.";
  echo "################################################";
  sleep 1;
  pushd $AJIT_HOME/docker/ajit_build;
  ./build.sh;
  popd;


  echo -e "\n\n\n\n\n";
  echo "################################################";
  echo "##  Building ajit_tools image.";
  echo "################################################";
  sleep 1;
  pushd $AJIT_HOME/docker/ajit_tools;
  ./build.sh;
  popd &> /dev/null;
} |& tee $_OUT_FILE;


