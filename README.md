README
=============

The `src/` directory contains the source
to build the required buildroot for ajit.

Effort has been taken to separate the source
and the `buildroot-2014-08` setup folder,
which will be created in this folder.
(i.e. outside the source folder)

To build stay in this directory and execute:

  ./src/setup.sh

  To add buildroot binaries paths and uclibc paths execute:

	source build_path.sh

To restart the build always clean the current directory first:

  ./src/clean.sh;./src/setup.sh;


## Important Locations

* `examples/` folder contains examples that demonstrate the
  use of many of the tools in this repo.


