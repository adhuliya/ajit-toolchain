#!/bin/sh

export GUSERNAME=`id -u -n`        # current user's username
export GUID=`id -u`                # current user's user id
export GGROUP=`id -g -n`           # current user's primary group name
export GGID=`id -g`                # current user's primary group id
export GHOME=$HOME                 # current user's home directory
export GSHELL=$SHELL               # current user's shell
export GPWD=`pwd`                  # current working directory

docker run      -h AJITHOST                       \
                --rm                              \
                -v $HOME:$HOME                    \
                -e GUSERNAME=$GUSERNAME           \
                -e GUID=$GUID                     \
                -e GGROUP=$GGROUP                 \
                -e GGID=$GGID                     \
                -e GHOME=$GHOME                   \
                -e GSHELL=$SHELL                  \
                -e GPWD=$GPWD                     \
                --name ajit-trial                 \
                -it ajit                          \
                --colour=auto
