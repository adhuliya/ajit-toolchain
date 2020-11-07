#!/usr/bin/env bash

# This script installs the required packages
# needed to build or use the Ajit Toolchain.

# Do the needed in one step.
apt-get update \
  && \
apt-get -y install --no-install-recommends \
  build-essential \
  python \
  python3 \
  libncurses5-dev \
  libsigsegv-dev \
  rsync \
  wget \
  cpio \
  unzip \
  bc \
  vim \
  gcc-multilib \
  flex \
  bison \
  tar \
  locales \
  perl \
  sed \
  gcc \
  g++ \
  git \
  scons \
  openjdk-8-jre-headless \
&& \
  apt-get -y autoremove \
&& \
  apt-get clean \
&& \
  rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*


