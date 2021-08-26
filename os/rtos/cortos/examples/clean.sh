#!/usr/bin/env bash

# Cleans all the build files in all the example folders.

find -name cortos_build -type d | xargs rm -rf;
