set AHIR_RELEASE $::env(AHIR_RELEASE)
set AJIT_PROJECT_HOME $::env(AJIT_PROJECT_HOME)
setenv LD_LIBRARY_PATH $AJIT_PROJECT_HOME/processor/Aa/modelsim/lib 

vlib ModelsimLink
vmap ModelsimLink ModelsimLink
vcom -work ModelsimLink $AHIR_RELEASE/vhdl/ModelsimLink.vhdl 


vlib aHiR_ieee_proposed
vmap aHiR_ieee_proposed aHiR_ieee_proposed
vcom -work aHiR_ieee_proposed $AHIR_RELEASE/vhdl/aHiR_ieee_proposed.vhdl 

vlib ahir
vmap ahir ahir
vcom -work ahir $AHIR_RELEASE/vhdl/ahir.vhdl 

vlib AjitCustom
vmap AjitCustom AjitCustom
vcom -work AjitCustom  InitValPackage.vhdl
vcom -work AjitCustom  $AJIT_PROJECT_HOME/processor/vhdl/lib/AjitCustomForVhdlSim.vhdl

vlib sys_aggregator
vmap sys_aggregator sys_aggregator
vcom -work sys_aggregator $AJIT_PROJECT_HOME/processor/Aa_v3/sys/aggregator/vhdl/sys_aggregator/aggregator.vhdl

vlib sys_spi_slave_periph_cluster
vmap sys_spi_slave_periph_cluster sys_spi_slave_periph_cluster
vcom -work sys_spi_slave_periph_cluster $AJIT_PROJECT_HOME/processor/Aa_v3/sys/spi_slave_periph_cluster/vhdl/sys_spi_slave_periph_cluster/spi_slave_periph_cluster.vhdl

vlib sys_serial_stub
vmap sys_serial_stub sys_serial_stub
vcom -work sys_serial_stub $AJIT_PROJECT_HOME/processor/Aa_v3/sys/serial_stub/vhdl/sys_serial_stub/serial_stub.vhdl

vlib sys_debug_stub
vmap sys_debug_stub sys_debug_stub
vcom -work sys_debug_stub $AJIT_PROJECT_HOME/processor/Aa_v3/sys/debug_stub/vhdl/sys_debug_stub/debug_stub.vhdl

vlib chip_interrupt_stub
vmap chip_interrupt_stub chip_interrupt_stub
vcom -work chip_interrupt_stub $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/interrupt_stub/vhdl/chip_interrupt_stub/interrupt_stub.vhdl

vlib debug_spi_slave_stub
vmap debug_spi_slave_stub debug_spi_slave_stub
vcom -work debug_spi_slave_stub $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/debug_spi_slave/stub/vhdl/debug_spi_slave_stub/debug_spi_stub.vhdl

vlib debug_spi_slave_adapter
vmap debug_spi_slave_adapter debug_spi_slave_adapter
vcom -work debug_spi_slave_adapter $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/debug_spi_slave/adapter/vhdl/debug_spi_slave_adapter/debug_adapter.vhdl

vlib chip_debug_spi_slave
vmap chip_debug_spi_slave chip_debug_spi_slave
vcom -work chip_debug_spi_slave $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/debug_spi_slave/vhdl/chip_debug_spi_slave/debug_spi_slave.vhdl

vlib chip_reset_pmode_stub
vmap chip_reset_pmode_stub chip_reset_pmode_stub
vcom -work chip_reset_pmode_stub $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/reset_pmode_stub/vhdl/chip_reset_pmode_stub/reset_pmode_stub.vhdl

vlib chip_logger_stub
vmap chip_logger_stub chip_logger_stub
vcom -work chip_logger_stub $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/logger_stub/vhdl/chip_logger_stub/logger_stub.vhdl

vlib core_mmu
vmap core_mmu core_mmu
vcom -work core_mmu $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/mmu/vhdl/core_mmu/mmu.vhdl

vlib core_icache
vmap core_icache core_icache
vcom -work core_icache $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/icache/vhdl/core_icache/icache.vhdl

vlib core_bridge
vmap core_bridge core_bridge
vcom -work core_bridge $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/bridge/vhdl/core_bridge/bridge.vhdl

vlib core_bootmem
vmap core_bootmem core_bootmem
vcom -work core_bootmem $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/bootmem/vhdl/core_bootmem/bootmem.vhdl

vlib core_timer
vmap core_timer core_timer
vcom -work core_timer $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/timer/vhdl/core_timer/timer.vhdl

vlib core_serial
vmap core_serial core_serial
vcom -work core_serial $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/serial/vhdl/core_serial/serial.vhdl

vlib cpu_debug_interface
vmap cpu_debug_interface cpu_debug_interface
vcom -work cpu_debug_interface $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/debug_interface/vhdl/cpu_debug_interface/debug_interface.vhdl

vlib teu_loadstore
vmap teu_loadstore teu_loadstore
vcom -work teu_loadstore $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/loadstore/vhdl/teu_loadstore/loadstore.vhdl

vlib teu_iexception
vmap teu_iexception teu_iexception
vcom -work teu_iexception $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/iexception/vhdl/teu_iexception/iexception.vhdl

vlib teu_idecode_idispatch
vmap teu_idecode_idispatch teu_idecode_idispatch
vcom -work teu_idecode_idispatch $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/idecode_idispatch/vhdl/teu_idecode_idispatch/idecode_idispatch.vhdl

vlib teu_stream_corrector
vmap teu_stream_corrector teu_stream_corrector
vcom -work teu_stream_corrector $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/stream_corrector/vhdl/teu_stream_corrector/stream_corrector.vhdl

vlib teu_iretire
vmap teu_iretire teu_iretire
vcom -work teu_iretire $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/iretire/vhdl/teu_iretire/iretire.vhdl

vlib iunit_exec
vmap iunit_exec iunit_exec
vcom -work iunit_exec $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/iunit/iu_exec/vhdl/iunit_exec/iu_exec.vhdl

vlib iunit_registers
vmap iunit_registers iunit_registers
vcom -work iunit_registers $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/iunit/iu_registers/vhdl/iunit_registers/iu_registers.vhdl

vlib teu_iunit
vmap teu_iunit teu_iunit
vcom -work teu_iunit $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/iunit/vhdl/teu_iunit/iunit.vhdl

vlib teu_ifetch
vmap teu_ifetch teu_ifetch
vcom -work teu_ifetch $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/ifetch/vhdl/teu_ifetch/ifetch.vhdl

vlib fpunit_registers
vmap fpunit_registers fpunit_registers
vcom -work fpunit_registers $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/fpunit/registers/vhdl/fpunit_registers/registers.vhdl

vlib fpunit_writeback
vmap fpunit_writeback fpunit_writeback
vcom -work fpunit_writeback $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/fpunit/writeback/vhdl/fpunit_writeback/writeback.vhdl

vlib fpunit_exec
vmap fpunit_exec fpunit_exec
vcom -work fpunit_exec $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/fpunit/exec/vhdl/fpunit_exec/exec.vhdl

vlib teu_fpunit
vmap teu_fpunit teu_fpunit
vcom -work teu_fpunit $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/fpunit/vhdl/teu_fpunit/fpunit.vhdl

vlib cpu_teu
vmap cpu_teu cpu_teu
vcom -work cpu_teu $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/vhdl/cpu_teu/teu.vhdl

vlib cpu_ccu
vmap cpu_ccu cpu_ccu
vcom -work cpu_ccu $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/ccu/vhdl/cpu_ccu/ccu.vhdl

vlib core_cpu
vmap core_cpu core_cpu
vcom -work core_cpu $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/vhdl/core_cpu/cpu.vhdl

vlib core_dcache
vmap core_dcache core_dcache
vcom -work core_dcache $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/dcache/vhdl/core_dcache/dcache.vhdl

vlib core_irc
vmap core_irc core_irc
vcom -work core_irc $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/irc/vhdl/core_irc/irc.vhdl

vlib core_spi
vmap core_spi core_spi
vcom -work core_spi $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/spi/vhdl/core_spi/spi.vhdl

vlib chip_core
vmap chip_core chip_core
vcom -work chip_core $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/vhdl/chip_core/core.vhdl

vlib serial_spi_slave_stub
vmap serial_spi_slave_stub serial_spi_slave_stub
vcom -work serial_spi_slave_stub $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/serial_spi_slave/stub/vhdl/serial_spi_slave_stub/serial_spi_stub.vhdl

vlib serial_spi_slave_adapter
vmap serial_spi_slave_adapter serial_spi_slave_adapter
vcom -work serial_spi_slave_adapter $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/serial_spi_slave/adapter/vhdl/serial_spi_slave_adapter/serial_adapter.vhdl

vlib chip_serial_spi_slave
vmap chip_serial_spi_slave chip_serial_spi_slave
vcom -work chip_serial_spi_slave $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/serial_spi_slave/vhdl/chip_serial_spi_slave/serial_spi_slave.vhdl

vlib chip_spi_master_interface
vmap chip_spi_master_interface chip_spi_master_interface
vcom -work chip_spi_master_interface $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/spi_master_interface/vhdl/chip_spi_master_interface/spi_master_interface.vhdl

vlib chip_ahblite_controller
vmap chip_ahblite_controller chip_ahblite_controller
vcom -work chip_ahblite_controller $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/ahblite_controller/vhdl/chip_ahblite_controller/ahblite_controller.vhdl

vlib sys_chip
vmap sys_chip sys_chip
vcom -work sys_chip $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/vhdl/sys_chip/chip.vhdl

vlib sys_sram_stub
vmap sys_sram_stub sys_sram_stub
vcom -work sys_sram_stub $AJIT_PROJECT_HOME/processor/Aa_v3/sys/sram_stub/vhdlsim/sram_stub.vhdl

vlib sys_sys
vmap sys_sys sys_sys
vcom -work sys_sys $AJIT_PROJECT_HOME/processor/Aa_v3/sys/vhdl/sys_sys/sys.vhdl

vlib work
vmap work work
vcom -work work $AJIT_PROJECT_HOME/processor/Aa_v3/sys/vhdl/testbench/sys_test_bench.vhdl

vsim -novopt -t ps -foreign "initForeign libFli.so" work.sys_test_bench

#add wave -r sim:/sys_test_bench/dut/chip_inst/core_inst/icache_inst/*
#add wave -r sim:/sys_test_bench/dut/chip_inst/core_inst/dcache_inst/*
#add wave -r sim:/sys_test_bench/dut/chip_inst/core_inst/cpu_inst/teu_inst/*
#add wave -r sim:/sys_test_bench/dut/chip_inst/core_inst/mmu_inst/*

#Ignore integer warnings at time 0 

set StdArithNoWarnings 1 

set StdArithNoWarnings 0 


run ---ns
#run -all
quit
