#!/usr/bin/env bash
# REF: https://www.digitalocean.com/community/tutorials/how-to-install-and-use-docker-on-ubuntu-16-04

isdocker () {
  local count=$(cat /proc/1/cgroup | grep "/docker" | wc -l);
  if [[ count -eq 0 ]]; then false; else true; fi
}

if isdocker; then
  echo "Inside a docker container. EXITING!"
  exit 1;
fi

# installs docker and takes necessary steps for you.
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add - \
  && \
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable" \
  && \
sudo apt-get update \
  && \
sudo apt-get install -y docker-ce \
  && \
sudo usermod -aG docker $USER \
  && \
chown -R $USER:docker $AJIT_HOME; # change the group owner of this repo


echo "Ajit: Please logout and login again for user changes to take effect!";

