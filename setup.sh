#!/usr/bin/env bash
# Maintainer: Anshuman Dhuliya (anshumandhuliya@gmail.com)

# This script attempts to build and setup ajit toolchain
# on the local machine (no dockerization is attempted).
# For dockerization see `./docker_setup.sh`.
# It depends on the $AJIT_HOME env variable.

isdocker () {
  local count=$(cat /proc/1/cgroup | grep docker | wc -l);
  if [[ count -eq 0 ]]; then
    false;
  else
    true;
  fi
}

if [[ -z $AJIT_HOME ]]; then
  echo "Please set the env variable \$AJIT_HOME";
  exit 1;
fi

_OUT_LOG=$AJIT_HOME/build.log;

{
  echo -e "\nOutput log file: $_OUT_LOG \n";
  sleep 2;

  mkdir -p $AJIT_HOME/build;

  if isdocker; then 
    echo "Inside a docker container.";
    echo "Skipping ajit_base setup!";
  else
    #echo "################################################";
    #echo "##  Setting up ajit_base.";
    #echo "################################################";
    #sleep 3;
    #bash $AJIT_HOME/docker/ajit_base/setup_ajit_base.sh;
  fi

  echo "################################################";
  echo "##  Setting up ajit_builds.";
  echo "################################################";
  sleep 3;
  bash $AJIT_HOME/docker/ajit_build/setup_ajit_build.sh;


  #echo "################################################";
  #echo "##  Setting up ajit_tools.";
  #echo "################################################";
  #sleep 3;
  #bash $AJIT_HOME/docker/ajit_tools/setup_ajit_tools.sh;

  echo "DONE!";
} |& tee $_OUT_LOG;

