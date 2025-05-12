# template for running ajit debug monitor
# inside a running docker container. 
# This is called from 
cd /home/ajit/ajit-toolchain
source set_ajit_home
source ajit_env
# you will need to supply work area
cd $AJIT_HOME/docs/verification/fpga/example/hello_world
#  run the cortos build script.
./build.sh
# thats it.
exit
