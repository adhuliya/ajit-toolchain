ghdl --clean
ghdl --remove
ghdl -i --work=GhdlLink /home/madhav/AHIR/gitHub/ahir/release/vhdl/GhdlLink.vhdl
ghdl -i --work=aHiR_ieee_proposed /home/madhav/AHIR/gitHub/ahir/release/vhdl/aHiR_ieee_proposed.vhdl
ghdl -i --work=ahir /home/madhav/AHIR/gitHub/ahir/release/vhdl/ahir.vhdl
ghdl -i --work=AjitCustom /home/madhav/AjitProject/Git/AjitRepoV2/processor/vhdl/lib/AjitCustom.vhdl
ghdl -i --work=adm_test_lib /home/madhav/AjitProject/Git/AjitRepoV2/tools/ajit_debug_monitor_mt/test/pinger/vhdl/adm_test_lib/pinger.vhdl
ghdl -i --work=GlueModules /home/madhav/AjitProject/Git/AjitRepoV2/tools/ajit_debug_monitor_mt/test/debug_aggregator/vhdl/GlueModules/debug_aggregator_four_core.vhdl
ghdl -i --work=adm_test_lib /home/madhav/AjitProject/Git/AjitRepoV2/tools/ajit_debug_monitor_mt/test/vhdl/adm_test_lib/adm_test_setup.vhdl
ghdl -i --work=work /home/madhav/AjitProject/Git/AjitRepoV2/tools/ajit_debug_monitor_mt/test/vhdl/testbench/adm_test_setup_test_bench.vhdl
ghdl -m --work=work -Wl,-L/home/madhav/AHIR/gitHub/ahir/release/lib -Wl,-lVhpi adm_test_setup_test_bench
