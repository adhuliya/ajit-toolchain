set AHIR_RELEASE $::env(AHIR_RELEASE)
set AJIT_PROJECT_HOME $::env(AJIT_PROJECT_HOME)

read_vhdl -library ahir_ieee_proposed $AHIR_RELEASE/vhdl/aHiR_ieee_proposed.vhdl
read_vhdl -library ahir $AHIR_RELEASE/vhdl/ahir.vhdl
read_vhdl -library simpleUartLib $AJIT_PROJECT_HOME/processor/vhdl/lib/simpleUartLib.vhdl
read_vhdl -library GlueModules ../../debug_aggregator/vhdl/GlueModules/debug_aggregator_four_core.vhdl
read_vhdl -library adm_test_lib ../../pinger/vhdl/adm_test_lib/pinger.vhdl
read_vhdl -library adm_test_lib ../../vhdl/adm_test_lib/adm_test_setup.vhdl
read_vhdl -library work ../VHDL/serial_uart.vhdl
read_vhdl -library work ../VHDL/basys3_top.vhdl

############# CONSTRAINT FILE ###########
read_xdc ../constraints/basys3.xdc

############# IP CORE FILES #############
set_property part xc7a35tcpg236-3 [current_project]

############### SYNTHESIZE ##############
synth_design -fsm_extraction off -flatten_hierarchy none -top basys3_top -part xc7a35tcpg236-3
write_checkpoint -force PostSynthCheckpoint.dcp
report_timing_summary -file timing.postsynth.rpt -nworst 4

report_utilization -file utilization_post_synth.rpt
report_utilization -hierarchical -file utilization_post_synth.hierarchical.rpt
opt_design  
place_design  -directive Explore
place_design -post_place_opt 
phys_opt_design  -directive Explore
route_design  -directive Explore
write_checkpoint -force PostPlaceRouteCheckpoint.dcp
report_timing_summary -file timing.rpt -nworst 10 -verbose
report_utilization -file utilization_post_place_and_route.rpt
report_utilization -hierarchical -file utilization_post_place_and_route.hierarchical.rpt
write_bitstream -force adm_test_setup.bit
