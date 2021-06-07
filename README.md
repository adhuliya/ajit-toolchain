README
=============
Tested to work on: Ubuntu 16.04.
If you are going to use the docker setup below,
it will use Ubuntu 16.04 by default.
For troubleshooting in a local setup one can refer to the
docker setup steps which have been well tested.


## Building and Installation

Run the following command from this `README.md`'s directory,
to set the `AJIT_HOME` environment variable,

    source ./set_ajit_home


### Install/Setup docker images

    source ./set_ajit_home;   # sets AJIT_HOME
    ./install_docker.sh;      # installs docker and more
    ./docker_setup.sh;        # creates the docker images 

    # on success
    cd ./docker/ajit_build_dev; # go to the image utility directory
    ./run.sh;                   # starts docker container `ajit_build_dev`
    ./attach_shell;             # gives you shell access to the container
    ## now you are inside the container ajit_build_dev
    ./setup.sh;                 # build and setup the Ajit system
    exit;
    ## now you are outside the container

Once the above setup is done refer `./docker/README.md` for more details.

## Run a test program

To run and test a sample examples,

    # STEP 1: Enter the docker container.
    cd ./docker/ajit_build_dev; # go to the image utility directory
    ./run.sh;                   # starts docker container `ajit_build_dev`
    ./attach_shell;             # gives you shell access to the container
    ## now you are inside the container ajit_build_dev
    # STEP 2: Execute a single test.
    cd ./tests/examples/misc/sin-model-test;
    ./build.sh;
    ./run_cmodel.sh;
    ./clean.sh;

The output of `./run_cmodel.sh` should have a line `Tests Successful`.
If so, the system is probably ready to use.
To be on a safer side do run all the automated tests as given below.

### Running (all) automated tests

Run the following sequence of commands as given,
from the root of the repository,

    # STEP 1: Enter the docker container.
    cd ./docker/ajit_build_dev; # go to the image utility directory
    ./run.sh;                   # starts docker container `ajit_build_dev`
    ./attach_shell;             # gives you shell access to the container
    ## now you are inside the container ajit_build_dev
    # STEP 2: Execute all the tests.
    cd ./tests; ./test.sh;
    cd ..; cd ./tests/verfication; ./verify.sh;


### Do a local setup

To setup Ajit Toolchain on the local system run,

    source ./set_ajit_home;   # sets AJIT_HOME
    ./setup.sh;               # builds the system
    source ./ajit_env;        # to setup the environment

Note that if this setup fails, the user should
refer the `./docker_setup.sh` which stands as a
reference to a well tested system environment.


## Clean the slate

To cleanup the local system setup use,

    ./clean.sh;

You can also call the above script from inside
`ajit_build_dev` image container to clean the
whole ajit build. 

To cleanup a sub-build in the Ajit toolchain,
read the script to see which sub-scripts it invokes.


## Setup environment to start using the toolchain

To setup the environment to start using Ajit Toolchain,

    source ./set_ajit_home;
    source ./ajit_env;

`./ajit_env` contains all the truth about the global
environment variables needed for Ajit development and use.


## Important Files and Directories

* `tests/examples/` folder contains examples that demonstrate the
  use of many of the tools in this repo.



General Information
------------------

The Ajit build is divided into three stages.
These stages are designed keeping docker images in mind.
However, for a local setup the script `./setup.sh` executes
similar steps without creating docker images.
(Docker image names are in quotes.)

1. "ajit\_base":
   Prepare a base system with all the necessary
   dependencies. If you are using docker,
   this is done in an image named `ajit_base`.

2. Start building from the sources. For a local build,
   docker images are not created and the whole build
   is kept in the current directory. For a docker build,
   the following images are created,

    * "ajit\_build\_dev":
      This docker image is derived from "ajit\_base"
      and mounts the current directory to start building
      from the sources. All the build files are kept in the
      current directory and can be used from within the docker
      container.
      
    * "ajit\_build" (Optional):
      This docker image is derived from "ajit\_base".
      If you are using docker, this build is saved
      in an image named `ajit_build`.
      This image contains the whole of the ajit build,
      and hence maybe many GBs in size.

After this stage you can use the whole of Ajit Toolchain
from the created docker image;
And in case of a local setup you can use the system from
the directory housing the built system (which we refer
to as `AJIT_HOME`)

3. "ajit\_tools" (Optional):
   To reduce the docker image size, the third step 
   removes intermediate files (from "ajit\_build" image 
   and keeps the installed files necessary.
   This is useful for someone interested
   in using the Ajit Toolchain (vs its development).
   If you are using docker, this is done in the image
   `ajit_tools` (this image is generally less than
   1/5th the size of the image `ajit_build` but
   a few hundred megabytes bulkier than `ajit_build_dev` image).

When using docker the `./docker_setup.sh` by default
only builds `ajit_base` and `ajit_build_dev` images.
To build the other two images, comment the line with
`exit;` on it (the line is clearly documented in the script).

If you are building the system locally (not creating docker images),
then the third step has to be done manually.
You may refer `./docker/ajit_tools/Dockerfile` to know
which directories need to be deleted/kept to reduce the 
disk size of the system (this step will be automated in future).


