Ajit's Base Docker Image
=========================
Maintainer: Anshuman Dhuliya (anshumandhuliya@gmail.com)

This folder contains Dockerfile to build
the base image with most packaged resources
needed to build the ajit system toolchain.

The intent of this image is to isolate all the
third party dependencies that Ajit needs into
a base image. This has the following advantages,

1. Rebuilding any image derived from this image
   doesn't need to pull resources from the internet
   again and again during development.

2. This image can stand as a reference as to the
   environment that works for Ajit tools.
