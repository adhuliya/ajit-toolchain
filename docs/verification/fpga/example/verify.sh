export AJIT_DEBUG_UART=/dev/ttyUSB1
CWD=$(pwd)
source /opt/Xilinx/Vivado/2019.1/settings64.sh
# generate the fpga scripts.
cd ../fpga/scripts
source generate_tcl.sh
# program the fpga 
./program.sh 
cd $CWD
# run the hello-world test
cd hello_world
../../scripts/toplevel.sh $AJIT_DEBUG_UART
cd $CWD
# reset the FPGA
cd ../fpga/scripts
./reset.sh
cd $CWD
# run the mmul test
cd mmul
../../scripts/toplevel.sh $AJIT_DEBUG_UART
cd $CWD
