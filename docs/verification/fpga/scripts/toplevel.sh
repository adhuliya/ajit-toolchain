#
export AJIT_DEBUG_UART=$1
echo AJIT_DEBUG_UART=$AJIT_DEBUG_UART
CWD=$(pwd)
# run compile inside docker.
../../scripts/attach_cortos_compile.sh
cd $CWD
# run ajit_debug_monitor_mt inside docker.
../../scripts/attach_run_adm.sh
# done.
