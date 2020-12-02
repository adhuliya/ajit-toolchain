#!/usr/bin/env bash

isdocker () {
  local count=$(cat /proc/1/cgroup | grep "/docker" | wc -l);
  if [[ count -eq 0 ]]; then false; else true; fi
}

if isdocker; then
  echo "Inside a docker container. EXITING!"
  exit 1;
fi


# installs docker and takes necessary steps for you.
sudo apt-get install -y docker.io \
  && \
sudo usermod -a -G docker $USER \
  && \
chown -R $USER:docker $AJIT_HOME; # change the group owner of this repo


echo "Ajit: Please logout and login again for some changes to take effect!";

