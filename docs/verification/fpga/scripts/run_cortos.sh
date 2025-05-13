# template for running ajit debug monitor
# inside a running docker container. 
# This is called from 
cd /home/ajit/ajit-toolchain
source set_ajit_home
source ajit_env
# you will need to supply work area
cd $AJIT_HOME/work_area
#  Supply all your arguments here (paths in container)
./build.sh
# thats it.
exit
