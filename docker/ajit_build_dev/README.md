Ajit's Build Dev Docker Image
=========================
Maintainer: Anshuman Dhuliya (anshumandhuliya@gmail.com)

TODO: not started the work yet.

This folder contains Dockerfile to build
the build image with the whole build and
the temporary files with sources of the 
build.

This image is similar to `ajit_build`.
It is a developer friendly build with all
the build files sitting on the host machine
(preferably under a well maintained git repository)
which are conveniently mounted in the
docker container as a read-only file system.
