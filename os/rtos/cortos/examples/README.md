Test Examples
=================

Yaml Tutorial: <https://www.youtube.com/watch?v=cdLNKUoMc6c>

* 001 to 049: Single Core, Single Thread
* 050 to 099: Multithreads, no collaboration
* 100 to 149: Multithreads, only with synchronization
* 150 to 199: Multithreads, only with queues
* 200 to 249: Multithreads, only with bget
* 250 to 299: Multithreads, with sync, queue, and bget


## What constitutes a project?
A project consists of the following necessary components,

* A set of C source files and header files. Currently, CoRTOS doesn't support
  sub-directories of source files.
* A `main()` function to enable the building,
  although for CoRTOS `main()` is not required.
* A `config.yaml` file to specify the necessary details of the project.
  Details of the `config.yaml` file can be studied using the examples
  in this directory. Specifically the following config files are a good
  reference point,
  
   * [./example_001/config.yaml](example_001/config.yaml)
   * [./example_050/config.yaml](example_050/config.yaml)
   * [./example_100/config.yaml](example_100/config.yaml)
   * [./example_150/config.yaml](example_150/config.yaml)
   * [./example_200/config.yaml](example_200/config.yaml)
   * [./example_250/config.yaml](example_250/config.yaml)
     

## How to run the examples?
In each example_XXX project directory do the following,

    ./build.sh  # builds the project
    ./run.sh    # runs the project


## How a cortos project is built?

Once the user invokes `cortos build` command on the project,
the `cortos` program reads the configuration from `config.yaml` file.
Then a directory `cortos_build/` is created in the current directory
and is populated with all the necessary (dynamically generated)
files to build the project.
The user's `*.c` and `*.h` files are copied into the `cortos_build/` dir too.


## What API does CoRTOS provide?
The API and its documentation can be read from `cortos.h` file.
This file can be found in `cortos_build/` directory once the `cortos build`
has been invoked.
This is a dynamically generated file hence to view it, one has to 
create a skeleton project with a `config.yaml` and a `.c` file to
be able to invoke the `cortos build` command.
Any one of the examples in this directory can be used for this purpose.

