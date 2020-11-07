#!/usr/bin/env bash
# Run only once per host.

_VOL_NAME=ajit;

docker volume create $_VOL_NAME;


# Help:
# List docker volumes:
#    docker volume list;
# Inspect docker volume:
#    docker volume inspect [volume_name];
# Delete docker volume:
#    docker volume rm [volume_name];

