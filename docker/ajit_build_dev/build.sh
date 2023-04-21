#!/usr/bin/env bash

# build the docker image -- takes one argument - the tag

docker build \
  --build-arg uid="$(id -u)" \
  --build-arg user="$(id -nu)" \
  --tag ajit_tools:1.0\
  .;

