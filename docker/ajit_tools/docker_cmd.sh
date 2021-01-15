#!/usr/bin/env bash

# this script keeps the docker container alive.

BASHRC=/root/.bashrc

echo -e "\n\n\n## Ajit_Content START\n" >> $BASHRC;
cat $AJIT_HOME/ajit_env >> $BASHRC;
echo -e "\n## Ajit_Content END\n" >> $BASHRC;

while true; do
  echo "AjitTools: `date`";
  sleep 60;
done
