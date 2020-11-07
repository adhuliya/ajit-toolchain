#!/usr/bin/env bash
# REF: https://lebkowski.name/docker-volumes/

# Reclaim hard disk space by deleting unused resources.

# remove exited containers:
docker ps --filter status=dead --filter status=exited -aq | xargs -r docker rm -v

# remove unused images:
docker images --no-trunc | grep '<none>' | awk '{ print $3 }' | \
  tee -a /dev/tty | xargs -r docker image rm --force

# remove all images (CONTEMPLATE BEFORE UNCOMMENTING)
docker image ls | grep -v REPOSITORY | awk '{ print $3 }' | \
  tee -a /dev/tty | xargs -r docker image rm --force 

# remove unused volumes (CONTEMPLATE BEFORE UNCOMMENTING)
docker volume ls -qf dangling=true | xargs -r docker volume rm
