#!/usr/bin/env bash
# REF: https://www.digitalocean.com/community/tutorials/how-to-install-and-use-docker-on-ubuntu-16-04

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

function OR() {
  # Executes the given command. Continues on error.
  # Takes three arguments
  #  $1 Quoted Command
  #  $2 Error msg (optional)
  echo -e "\nOR: START:" "$1" "\n";
  bash -c "$1";
  local _EXITCODE=$?;
  if [[ $_EXITCODE != "0" ]]; then
    echo -e "OR: ERROR:($_EXITCODE): '$1'\n$2";
  else
    echo -e "OR:  DONE: $1";
  fi
}

isdocker () {
  local count=$(cat /proc/1/cgroup | grep "/docker" | wc -l);
  if [[ count -eq 0 ]]; then false; else true; fi
}

if isdocker; then
  echo "Inside a docker container. EXITING!"
  exit 1;
fi

# installs docker and takes necessary steps for you.
AND "curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -" \
  "Please review the error";

_ARG="deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
AND "sudo add-apt-repository '$_ARG'" \
  "Problem in adding to apt repository.";

AND "sudo apt-get update" \
  "Please correct the apt-get errors.";

AND "sudo apt-get install -y docker-ce";

AND "sudo usermod -aG docker $USER" \
  "Probably 'docker' group is not created.";

# change the group owner of this repo
AND "chown -R $USER:docker $AJIT_HOME" \
  "Probably 'docker' group is not created.";

echo -e "\nAjit: Please logout and login again for user changes to take effect!";
echo -e "\nAjit: To test docker after re-login run the following script:"
echo "    ./docker/test_docker_install.sh;";
echo "DONE.";


