# template for running ajit debug monitor
# inside a running docker container. 
# This is called from 
cd /home/ajit/ajit-toolchain
source set_ajit_home
source ajit_env
#  Supply all your arguments here (paths in container)
ajit_debug_monitor_mt  
# thats it.
exit
