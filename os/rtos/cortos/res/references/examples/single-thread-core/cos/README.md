Author: Anshuman Dhuliya (dhuliya@cse.iitb.ac.in)

How to run the example in this directory?

Steps to use
--------------

    ./build.sh  # builds main.elf and mmap file

    ./run_cmodel.sh  # runs the cmodel on the mapped file

    ./clean.sh  # cleans the directory of unnecessary files

Also `LinkerScript.lnk` has been modified to make `--gc-sections` work.

The `pt_load_sections.py` script extracts the section names that need
to be loaded, and formats the output to be used as a command line
argument to the `sparc-linux-readelf` program.

NOTE: Each of the script is well commented. If still in doubt,
or something is left out, please contact me at:
  dhuliya@cse.iitb.ac.in, anshumandhuliya@gmail.com

