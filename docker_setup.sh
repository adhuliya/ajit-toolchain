#!/usr/bin/env bash
# Maintainer: Anshuman Dhuliya (anshumandhuliya@gmail.com)

# This script builds the required docker images
# It depends on the $AJIT_HOME env variable.


if ! which docker; then
  # install docker first
  sudo apt-get install -y docker.io;
fi
echo "Good. Docker is installed!";
sleep 1;

if [[ -z $AJIT_HOME ]]; then
  echo "Please set the env variable \$AJIT_HOME";
  exit 1;
fi

mkdir -p $AJIT_HOME/build;
OUTFILE_LOG=$AJIT_HOME/build/docker_build.log;

echo -e "\nOutput log file: $OUTFILE_LOG\n";
sleep 1;

echo "\n\n\n\n\n" &>> $OUTFILE_LOG;
echo "################################################" &>> $OUTFILE_LOG;
echo "##  Building ajit_base image." &>> $OUTFILE_LOG;
echo "################################################" &>> $OUTFILE_LOG;
sleep 1;
pushd $AJIT_HOME/docker/ajit_base;
./build.sh &>> $OUTFILE_LOG;
popd;


echo "\n\n\n\n\n" &>> $OUTFILE_LOG;
echo "################################################" &>> $OUTFILE_LOG;
echo "##  Building ajit_build image." &>> $OUTFILE_LOG;
echo "################################################" &>> $OUTFILE_LOG;
sleep 1;
pushd $AJIT_HOME/docker/ajit_build;
./build.sh &>> $OUTFILE_LOG;
popd;


echo "\n\n\n\n\n" &>> $OUTFILE_LOG;
echo "################################################" &>> $OUTFILE_LOG;
echo "##  Building ajit_tools image." &>> $OUTFILE_LOG;
echo "################################################" &>> $OUTFILE_LOG;
sleep 1;
pushd $AJIT_HOME/docker/ajit_tools;
./build.sh &>> $OUTFILE_LOG;
popd;


