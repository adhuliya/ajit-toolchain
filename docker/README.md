Ajit's Docker Images
=========================
Maintainer: Anshuman Dhuliya (anshumandhuliya@gmail.com)

Each of the four folders here correspond to a
specific docker image.
The following dependency exists between the images.

* `ajit_base` --> `ajit_build_dev`
* `ajit_base` --> `ajit_build`
* `ajit_base` --> (`ajit_build`) --> `ajit_tools`


## Building `ajit_build_dev` image.

For most needs one may only need `ajit_build_dev`
image. To build it do the following,

    cd ./ajit_base;
    ./build.sh;             # builds the image `ajit_base`
    cd ../ajit_build_dev;
    ./build.sh;             # builds the image `ajit_build_dev`
    cd ..;                  # return back to this folder

As per the dependency given above building other
images follows similar steps.

For `ajit_build_dev` image the following steps are required,

    cd ./ajit_build_dev;
    ./run.sh;               # run the container
    ./attach_shell.sh;      # attach a shell to the container
    ## now you are inside the container
    ./setup.sh;             # build and setup the Ajit system
    exit;
    ## now you are outside the container


## Image folder contents

Each folder contains the
following useful files that work with their
respective docker images and containers,

0. `Dockerfile` specifies the docker image content and configuration.
1. `./build.sh` is used to build a fresh docker image.
2. `./run.sh` runs the docker image (creating a container).
3. `./remove.sh` removes a running docker container.
4. `./attach_shell.sh`. attaches shell to a running docker container.
5. `./logs.sh` shows the (stdout) output logs generated by the container.


## How to use `ajit_build_dev` image?

Note: To use other images follow similar (almost identical) steps.

To start using the `ajit_build_dev` image first
build the image as given above and then refer below.

First start the container,

    cd ./ajit_build_dev;
    ./run.sh;             # if status printed is '0' container has started

The container should be running if docker is
setup properly on the system.
To setup docker properly on an ubuntu system refer
[How to install Docker on Ubuntu 16.04][1] or see the
script `../docker_install.sh`.

Now refer to this list to do specific tasks by first
cd'ing into the folder that corresponds to the image
you are using. For example, for `ajit_build_dev`,
do `cd ./ajit_build_dev` then use the following reference.

* The environment variables in effect in the system can
  be found in `./ajit_build/ajit_env`;

* **Attach a working shell**:
  Attach a working shell to the container using the following
  script,

        ./attach_shell.sh;

  One can attach as many shells to the container. The containers
  are built such that they don't die if all the shells quit.


* **Run a command on the container**:
  One can run arbitrary commands on the container without
  explicitly opening up an interactive shell as follows,

        ./cmd.sh <user_command>;


* **Remove the container**:
  Occasionally one might want to force stop the container.
  This can be done as follows,

        ./remove.sh;

* **Restart the container**:

        ./run.sh;  # this script restarts the container

* **Build a the container image**:
  When you are experimenting with a docker image
  creation process you will need to rebuild the image to
  start using it. Use the following command,

        ./build.sh;

  To use the new image one must restart the container using
  `./run.sh`.


* **View the list of images built in the system**:

        docker image ls;

* **Remove an image from the system**:

        docker image rm --force <IMAGE ID>;

  The image id can be obtained with `docker image ls`.


* **View the list of containers**:

        docker container ls --all;


* **Remove a container**:

        docker container rm <CONTAINER ID>;

  Sometimes its necessary to remove containers as they may consume
  a huge amount of space when running for a long time (10s of GBs).



[1]: https://www.digitalocean.com/community/tutorials/how-to-install-and-use-docker-on-ubuntu-16-04 "How to install Docker on Ubuntu 16.04"


