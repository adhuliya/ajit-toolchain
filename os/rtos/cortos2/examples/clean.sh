#!/usr/bin/env bash

# Cleans all the build xfiles in all the example folders.

find -name cortos_build -type d | xargs rm -rf;
