# set the environment
export AJIT_DEBUG_UART=/dev/ttyUSB1
cd /home/ajit/ajit-toolchain
source set_ajit_home
source ajit_env
# go to work directory..
#  THIS IS SPECIFIC TO THE EXAMPLE.
cd $AJIT_HOME/docs/verification/fpga/example/hello_world
# generate the adm script. Note that the initial PC is also yours to define (here 0x40000000)
adm_script_gen 2 1 0x40000000 cortos_build/main.mmap.remapped  results.txt  adm_script.txt ignore_log.txt
# calibrate the UART
calibrateUart $AJIT_DEBUG_UART 1000000
#  ajit debug monitor run inside the container.
ajit_debug_monitor_mt -u $AJIT_DEBUG_UART -B 1000000 -n 2 -t 1 -O -f adm_script.txt | tee adm.log 
# thats it.
exit
