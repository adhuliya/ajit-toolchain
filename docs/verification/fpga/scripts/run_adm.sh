cd /home/ajit/ajit-toolchain
source set_ajit_home
source ajit_env
ajit_debug_monitor_mt -n 2 -t 1 -u /dev/ttyUSB1 -B 1000000 -O -f adm.script
exit
