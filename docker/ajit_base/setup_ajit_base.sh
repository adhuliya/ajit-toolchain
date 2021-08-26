#!/usr/bin/env bash

# This script installs the required packages
# needed to build or use the Ajit Toolchain.

# Do the needed in one step.
# REF: https://buildroot.org/downloads/manual/manual.html#requirement-mandatory
# EXTRA packages for Ajit:
#   For testing: time, parallel
#   Others: libncurses5-dev, gedit
#   For deviceTreeCompiler: bison, flex

  apt-get update \
&& \
  apt-get -y install --no-install-recommends \
    sed \
    make \
    binutils \
    build-essential \
    gcc \
    g++ \
    bash \
    patch \
    gzip \
    bzip2 \
    perl \
    tar \
    cpio \
    unzip \
    rsync \
    file \
    bc \
    wget \
    vim-tiny \
    python \
    python3 \
    scons \
    openjdk-8-jre-headless \
    time \
    parallel \
    libncurses5-dev \
    bison \
    flex \
    libreadline-dev \
    gedit \
<<<<<<< HEAD
    git \
=======
    software-properties-common \
&& \
  add-apt-repository ppa:deadsnakes/ppa \
&& \
  apt-get update \
&& \
  apt-get -y install python3.6 \
>>>>>>> 1414aeafc1dd958386ccdbf51788ad1baa1dbbd9
&& \
  apt-get -y autoremove \
&& \
  apt-get clean \
&& \
  wget https://bootstrap.pypa.io/get-pip.py \
&& \
  python3.6 get-pip.py \
&& \
  pip install --no-cache-dir pyelftools pyyaml \
&& \
  rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

#  libncurses5-dev \
#  libsigsegv-dev \

