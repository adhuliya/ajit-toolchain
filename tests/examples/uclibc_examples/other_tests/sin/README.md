This example uses `sin` math function from glibc.

The `compileToSparc_local.py` expects the glibc install libraries
sitting in the following directory,

    $AJIT_PROJECT_HOME/tools/glibc/<glibc_version>/lib/

Where `glibc_version` is a string like `2.21` for glibc version 2.21.

The header files are exptected to be at (see `sin/build.sh`):

    $AJIT_PROJECT_HOME/tools/glibc/<glibc_version>/

Note: `glibc` is known to cause trouble if built and installed to
       a separate absoute path than above. One work around is to 
       create symbolic links such that the absolute path is also
       present in the system.

### How to run the example?

The program is written in `main.c` file. One needs only the following two steps to run,

    ./build.sh
    ./run_cmodel.sh

### How to use `compleToSparc_local.py` with glibc?

A new option `-G` is added, for a glibc version say `2.21` it takes the following
arguments,

* `-G 2.21`
* `-G 2.21_debug` -- for debug version
* `-G 2.21_sectioned` -- for sectioned (each function in separate section)
* `-G 2.21_sectioned_debug` -- for sectioned debug version

The arguments are basically the folder names in the
`$AJIT_PROJECT_HOME/tools/glibc/` folder.
