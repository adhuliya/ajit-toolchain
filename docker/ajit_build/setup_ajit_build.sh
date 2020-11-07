#!/usr/bin/env bash

export TERM=xterm;

# cd $AJIT_HOME; # see ../ajit_base/Dockerfile

bash ./buildroot_src/setup.sh;
bash ./scripts/build_simulator.sh;
bash ./scripts/build_tools.sh;

