#!/usr/bin/env bash

# NOTE: This deletes all the images and containers in the system.

# remove all the containers
docker container rm `docker container ls -aq`;

# remove all the images
docker image rm `docker image ls -q`;


