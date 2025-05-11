# template for running ajit debug monitor
# inside a running docker container. 
# This is called from 
cd /home/ajit/ajit-toolchain
source set_ajit_home
source ajit_env
cd validation_ladder/cortos2_tests/prints/1x1/
#  Supply all your arguments here (paths in container)
./build.sh
# thats it.
exit
