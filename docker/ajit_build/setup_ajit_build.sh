#!/usr/bin/env bash

export TERM=xterm;

# cd $AJIT_HOME; # see ../ajit_base/Dockerfile

echo "################################################";
echo "  Building buildroot.";
echo "################################################";
sleep 3;
bash $AJIT_HOME/buildroot_src/setup.sh;


echo "################################################";
echo "  Building C Model.";
echo "################################################";
sleep 3;
bash $AJIT_HOME/scripts/build_simulator.sh;


echo "################################################";
echo "  Building Ajit Tools/Scripts.";
echo "################################################";
sleep 3;
bash $AJIT_HOME/scripts/build_tools.sh;

