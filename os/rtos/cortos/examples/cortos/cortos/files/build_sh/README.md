Contains build scripts to build
user's `main.c` file.

CoRtos builds the user program twice.
The first static build is to check the size of
the generated elf. Using the size of the elf
generated in the first build, it is rebuilt
to generate a second static build which starts at pre-computed
offsets to reside in a different region of the memory
with no overlap with other programs.
A programmatically generated linker script controls
this behavior.

The `build/` directory inside each program's directory
contains the build files of the program.
The top level folder `build_all/` contains the final build
for the processor, containing the `main.mmap` file which
can be loaded into the processor memory.
