Ajit's Build Dev Docker Image
=========================
Maintainer: Anshuman Dhuliya (anshumandhuliya@gmail.com)

This image is similar to `ajit_build_20.04`.
But, it is a developer friendly build with all
the build files sitting on the host machine
(preferably under a well maintained git repository)
which are conveniently mounted in the
docker container as a read-write file system.

This image is not self-sufficient. It needs
the ajit-toolchain git repository to be mounted
at the mount point `/home/ajit/ajit-toolchain`
inside the created image to be useful.
