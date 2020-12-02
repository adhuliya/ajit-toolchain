README
=============
Tested to work on: Ubuntu 16.04.


The Ajit build is divided into three stages,

1. Prepare a base system with all the necessary
   dependencies. If you are using docker,
   this is done in an image named `ajit_base`.

2. Start building from the sources.
   If you are using docker, this build is saved
   in an image named `ajit_build`.
   After this stage you can use the whole of Ajit Toolchain.

3. To reduce the system size, the third step 
   removes unnecessary files and only keeps the
   install files necessary for someone interested
   in using the Ajit Toolchain (vs its development).
   If you are using docker, this is done in the image
   `ajit_tools` (this image is genearlly less than
   1/5th the size of the image `ajit_build`).

If you are building the system locally (not creating docker images),
then the third step has to be done manually.
You may refer `./docker/ajit_tools/Dockerfile` for the same.


## Building and Installation

First set `AJIT_HOME` environment variable to the
directory this README.md file is in. This is `AJIT_HOME`.
(Or run `source ./ajit_home_env` from this directory)


### Install docker images

This needs docker to be installed and running on the user
machine. This, on an Ubuntu system, can be done using the
provided script, please use it as a reference on other systems,

    ./install_docker.sh

To build docker images with Ajit Toolchain run,
(Needs docker (on ubuntu run: `sudo apt-get install docker.io`))

    source ./ajit_home_env; 
    ./docker_setup.sh;

Once setup is done refer `./docker/README.md`.


### Install a local setup

To setup Ajit Toolchain on the local system run,

    source ./ajit_home_env; 
    ./setup.sh

Note that if this setup fails, the user should
refer the `./docker_setup.sh` which stands as a
reference to the well tested system environment.


## Clean the slate

To cleanup the local system setup use,

    ./clean.sh


## Setup environment to start using the toolchain

To setup the environment to start using Ajit Toolchain,

    source ./ajit_home_env;
    source ./docker/ajit_build/ajit_env;


## Test the setup

To run and test a sample example,

    cd ./examples/sin
    ./build.sh
    ./run.sh

The output of `./run.sh` should have a line `Tests Successful`.
If so, the system is ready to use.


## Important Files and Directories

* `examples/` folder contains examples that demonstrate the
  use of many of the tools in this repo.



