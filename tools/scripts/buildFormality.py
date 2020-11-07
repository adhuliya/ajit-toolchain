#!/usr/bin/env python

# Generates the .tcl files necessary for Formality by Synopsys for formal verification.
# It is recommended to run this script after synthesizing the design with topo_pnr.sh script.
#
# Written by : Ch V kalyani
# Date : 22/05/2017


# Assumptions : $design.svf file is present in the present working folder.
# 	      : $design.ddc file is present in the $design_$period_op_data folder in the WORK_AREA
#	      : All the vhdl files of chip are present in vhdl_files folder in the WORK_AREA
#
 
import os
import sys
import getopt
import os.path


current_dir = os.getcwd()

def logError(mesg):
    print "Error: " + mesg

def SetGlobals():

    global SCL_LIB1
    global SCL_LIB2
    global SCL_LIB3
    global SCL_LIB4
    global SCL_LIB5
    global SCL_LIB6
    global SCL_LIB7
    global SCL_LIB8
    global SCL_LIB17
    global WORK_AREA
    SCL_LIB1 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/tsl18fs120_scl_ss.db "
    SCL_LIB2 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/tsl18_memory_max_16_4.db "
    SCL_LIB3 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/spram_32_16_max.db "
    SCL_LIB4 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/obc11_256x8_max.db "
    SCL_LIB5 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/tsl18_memory_max_512_24.db "
    SCL_LIB6 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/obc11_dpram_16x8_max.db "
    SCL_LIB7 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/tsl18_memory_max_DP_16x4.db "
    SCL_LIB8 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/tsl18_memory_max_DP_32x8.db "
    SCL_LIB17 =  "$AJIT_ASIC_TAPEOUT_HOME/tech/scl180/db_files/tsl18cio250_max.db "
    WORK_AREA= "[pwd]/work"

def display_usage():
    print "\n Please provide the correct number of arguments.\n"
    print " Correct usage is given below.\n"
    print " $ buildFormality.py -d < design name > -l < library name > -p < clock period >\n"
    print "     with -d possible options: iunit/fpunit/cpu/icache/dcache/mmu/chip_with_io \n"
    print " -h < no parameter required. used to get help > \n"
    

    
def generateTCL(design, library, period):
    tcl_file_name = "formality_" + design + "_" + period +  ".tcl" 
    tcl_file = open(tcl_file_name,"w")
    print >> tcl_file, "set AJIT_ASIC_TAPEOUT_HOME $::env(AJIT_ASIC_TAPEOUT_HOME)"
        
    print >> tcl_file, "set design "+ design  
    print >> tcl_file, "set synopsys_auto_setup true "
    print >> tcl_file, "set_svf -append ./${design}.svf\n"



    print >> tcl_file, "set hdlin_interface_only *SplitGuardInterfaceBase*" 

    if (design == "cpu"):
       print >> tcl_file, "set hdlin_interface_only fpunit"
       print >> tcl_file, "set hdlin_interface_only iunit"

    if (design == "chip_with_io"):
       print >> tcl_file, "set hdlin_interface_only fpunit"
       print >> tcl_file, "set hdlin_interface_only iunit"
       print >> tcl_file, "set hdlin_interface_only cpu"
       print >> tcl_file, "set hdlin_interface_only dcache"
       print >> tcl_file, "set hdlin_interface_only icache"
       print >> tcl_file, "set hdlin_interface_only mmu"

    print >> tcl_file, "\n"
    print >> tcl_file, "set hdlin_enable_rtldrc_info true"
    print >> tcl_file, "set hdlin_infer_fsm TRUE"
    print >> tcl_file, "set fsm_auto_inferring TRUE"
    print >> tcl_file, "set hdlin_report_fsm TRUE"
    print >> tcl_file, "set hdlin_enable_rtldrc_info true"
    
    print >> tcl_file, "read_vhdl -container r -work_library aHiR_ieee_proposed ./vhdl_files/aHiR_ieee_proposed.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library ahir ./vhdl_files/ahirASIC.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library AjitCustom ./vhdl_files/AjitCustomForAsic.vhdl"

    print >> tcl_file, "read_vhdl -container r -work_library cpu_ccu ./vhdl_files/ccu.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library cpu_debug_interface ./vhdl_files/debug_interface.vhdl"

    print >> tcl_file, "read_vhdl -container r -work_library teu_iexception ./vhdl_files/iexception.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library teu_idecode_idispatch ./vhdl_files/idecode_idispatch.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library teu_ifetch ./vhdl_files/ifetch.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library teu_iretire ./vhdl_files/iretire.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library teu_loadstore ./vhdl_files/loadstore.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library teu_stream_corrector ./vhdl_files/stream_corrector.vhdl"

    print >> tcl_file, "read_vhdl -container r -work_library fpunit_exec ./vhdl_files/exec.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library fpunit_registers ./vhdl_files/registers.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library fpunit_writeback ./vhdl_files/writeback.vhdl"
 
    print >> tcl_file, "read_vhdl -container r -work_library iunit_exec ./vhdl_files/iu_exec.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library iunit_registers ./vhdl_files/iu_registers.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library iunit_writeback ./vhdl_files/iu_writeback.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library teu_fpunit ./vhdl_files/fpunit.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library teu_iunit ./vhdl_files/iunit.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library cpu_teu ./vhdl_files/teu.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library core_cpu ./vhdl_files/cpu.vhdl"
    
    print >> tcl_file, "read_vhdl -container r -work_library core_timer ./vhdl_files/timer.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library core_spi ./vhdl_files/spi.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library core_serial ./vhdl_files/serial.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library core_mmu ./vhdl_files/mmu.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library core_irc ./vhdl_files/irc.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library core_icache ./vhdl_files/icache.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library core_dcache ./vhdl_files/dcache.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library core_bridge ./vhdl_files/bridge.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library core_bootmem ./vhdl_files/bootmem.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library chip_core ./vhdl_files/core.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library chip_ahblite_controller ./vhdl_files/ahblite_controller.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library debug_spi_slave_stub ./vhdl_files/debug_spi_stub.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library debug_spi_slave_adapter ./vhdl_files/debug_adapter.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library chip_debug_spi_slave ./vhdl_files/debug_spi_slave.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library chip_interrupt_stub ./vhdl_files/interrupt_stub.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library chip_logger_stub ./vhdl_files/logger_stub.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library chip_reset_pmode_stub ./vhdl_files/reset_pmode_stub.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library serial_spi_slave_stub ./vhdl_files/serial_spi_stub.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library serial_spi_slave_adapter ./vhdl_files/serial_adapter.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library chip_serial_spi_slave ./vhdl_files/serial_spi_slave.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library chip_spi_master_interface ./vhdl_files/spi_master_interface.vhdl"

    print >> tcl_file, "read_vhdl -container r -work_library sys_chip ./vhdl_files/chip.vhdl"
    print >> tcl_file, "read_vhdl -container r -work_library chip_top ./vhdl_files/chip_with_io.vhdl"

    print >> tcl_file, "\n"

    print >> tcl_file, "read_db " +  SCL_LIB1 
    print >> tcl_file, "read_db " +  SCL_LIB2 
    print >> tcl_file, "read_db " +  SCL_LIB3 
    print >> tcl_file, "read_db " +  SCL_LIB4 
    print >> tcl_file, "read_db " +  SCL_LIB5 
    print >> tcl_file, "read_db " +  SCL_LIB6 
    print >> tcl_file, "read_db " +  SCL_LIB7   
    print >> tcl_file, "read_db " +  SCL_LIB8 
    print >> tcl_file, "read_db " +  SCL_LIB17 
 
 
    print >> tcl_file, "\n"
    print >> tcl_file, "set_top r:/" + library + "/" + design
    print >> tcl_file, "\n"
    print >> tcl_file, "read_ddc -container i ./" + design + "_" + period + "_" + "op_data/" + design + ".ddc"
    print >> tcl_file, "set_top i:/WORK/" + design
    print >> tcl_file, "\n"
    print >> tcl_file, "match"
    print >> tcl_file, "verify"
    print >> tcl_file, "\n"
    print >> tcl_file, "report_failing > ./" + design + "_formality.fail"
   
   
    tcl_file.close()


def main ():
    SetGlobals()
    
    if (len(sys.argv) < 7 ): 
        display_usage()
        return 1
    else :
        arg_list = sys.argv[1:]
        opts,args = getopt.getopt(arg_list,'d:p:l:h')
        for option, parameter in opts:
            if option ==  '-d':
                design = parameter
            if option == '-p':
            	period = parameter
            if option == '-l':
            	library = parameter
            if option ==  '-h':
                display_usage()
		return 0
            
                
    if (design != "iunit") and (design != "fpunit") and (design != "cpu") and (design != "chip_with_io") and (design != "mmu") and (design != "icache") and (design != "dcache"):
       print "ERROR: -d " + design + ": iunit/fpunit/cpu/chip_with_io/mmu/icache/dcache are the only possible options\n" 
       return 0

    generateTCL(design, library, period)
        
    return 0





if __name__ == '__main__':
    ret = main()
    sys.exit(ret)
