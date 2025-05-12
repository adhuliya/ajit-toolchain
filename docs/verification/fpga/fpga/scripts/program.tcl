open_hw 
connect_hw_server
open_hw_target
current_hw_device [get_hw_devices xc7vx690t_0]
refresh_hw_device -update_hw_probes false [lindex [get_hw_devices xc7vx690t_0] 0]
set_property PROBES.FILE {/home/madhav/AjitToolChain/ajit-toolchain/docs/verification/fpga/fpga/bitfile/ajit_sac_processor.vc709.ltx}  [get_hw_devices xc7vx690t_0]
set_property FULL_PROBES.FILE {/home/madhav/AjitToolChain/ajit-toolchain/docs/verification/fpga/fpga/bitfile/ajit_sac_processor.vc709.ltx} [get_hw_devices xc7vx690t_0]
set_property PROGRAM.FILE {/home/madhav/AjitToolChain/ajit-toolchain/docs/verification/fpga/fpga/bitfile/ajit_sac_processor.vc709.adm.bit}  [get_hw_devices xc7vx690t_0]
program_hw_devices [get_hw_devices xc7vx690t_0]
refresh_hw_device [lindex [get_hw_devices xc7vx690t_0] 0]
set_property OUTPUT_VALUE 1 [get_hw_probes reset_vio -of_objects [get_hw_vios -of_objects [get_hw_devices xc7vx690t_0] -filter {CELL_NAME=~"vio_inst"}]]
commit_hw_vio [get_hw_probes {reset_vio} -of_objects [get_hw_vios -of_objects [get_hw_devices xc7vx690t_0] -filter {CELL_NAME=~"vio_inst"}]]
set_property OUTPUT_VALUE 0 [get_hw_probes reset_vio -of_objects [get_hw_vios -of_objects [get_hw_devices xc7vx690t_0] -filter {CELL_NAME=~"vio_inst"}]]
commit_hw_vio [get_hw_probes {reset_vio} -of_objects [get_hw_vios -of_objects [get_hw_devices xc7vx690t_0] -filter {CELL_NAME=~"vio_inst"}]]

