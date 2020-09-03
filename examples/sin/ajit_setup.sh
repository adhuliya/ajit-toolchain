# source this bash script
# Author: Anshuman Dhuliya (dhuliya@cse.iitb.ac.in)

# save the current dir to later come back
CURRDIR=$(pwd)

# enable the old settings
#cd /usr/local/ajit_release
#source ./ajit_bashrc

cd /usr/local/ahir_release
source ./ahir_bashrc

THE_BUILDROOT=/home/gaurip/OPEN_ME_TO_README/buildroot-2014.08

# needed for `sparc-linux-gcc` etc...
export PATH=$THE_BUILDROOT/output/host/usr/bin:$PATH

# needed for `-lc` and `-lm` libraries and the header files
export AJIT_UCLIBC_INSTALL_DIR=$THE_BUILDROOT/output/build/uclibc-0.9.33.2/  

# needed for `libgcc.a` and the `-lgcc` flag passed to the linker
export AJIT_LIBGCC_INSTALL_DIR=$THE_BUILDROOT/output/build/host-gcc-final-4.7.4/build/gcc 

# needed to run the local compileToSparc.py
# not needed when using the original compileToSparc.py script
export PYTHONPATH=/home/gaurip/ajit_release/tools/scripts:$PYTHONPATH

# needed to run the ./pt_load_sections.py script
# since it depends on the `pyelftools` python package
export PYTHONPATH=$CURRDIR/pyelftools-0.25:$PYTHONPATH

# return back to the current directory
cd $CURRDIR

