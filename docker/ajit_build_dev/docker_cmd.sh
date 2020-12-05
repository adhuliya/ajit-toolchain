#!/usr/bin/env bash

# this script keeps the docker container alive.

BASHRC=/home/ajit/.bashrc

echo -e "\n\n\n## Ajit_Content START\n" >> $BASHRC;
cat $AJIT_HOME/ajit_env >> $BASHRC;
echo -e "\n## Ajit_Content END\n" >> $BASHRC;

while true; do
  echo "AjitBuildDev: `date`";
  sleep 60;
done
