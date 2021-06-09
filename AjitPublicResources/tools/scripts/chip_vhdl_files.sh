deleteAsserts.py -i $AHIR_RELEASE/vhdl/aHiR_ieee_proposed.vhdl -o ./aHiR_ieee_proposed.vhdl
deleteAsserts.py -i $AHIR_RELEASE/vhdl/ahirForAsic.vhdl -o ./ahirASIC.vhdl

cp $AJIT_PROJECT_HOME/processor/vhdl/lib/AjitCustomForAsic.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/chip_with_io.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/ccu/vhdl/cpu_ccu/ccu.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/debug_interface/vhdl/cpu_debug_interface/debug_interface.vhdl ./

cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/idecode_idispatch/vhdl/teu_idecode_idispatch/idecode_idispatch.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/iexception/vhdl/teu_iexception/iexception.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/ifetch/vhdl/teu_ifetch/ifetch.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/iretire/vhdl/teu_iretire/iretire.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/loadstore/vhdl/teu_loadstore/loadstore.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/stream_corrector/vhdl/teu_stream_corrector/stream_corrector.vhdl ./

cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/fpunit/exec/vhdl/fpunit_exec/exec.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/fpunit/registers/vhdl/fpunit_registers/registers.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/fpunit/writeback/vhdl/fpunit_writeback/writeback.vhdl ./

cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/iunit/iu_exec/vhdl/iunit_exec/iu_exec.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/iunit/iu_registers/vhdl/iunit_registers/iu_registers.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/fpunit/vhdl/teu_fpunit/fpunit.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/iunit/vhdl/teu_iunit/iunit.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/teu/vhdl/cpu_teu/teu.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/cpu/vhdl/core_cpu/cpu.vhdl ./

cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/timer/vhdl/core_timer/timer.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/spi/vhdl/core_spi/spi.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/serial/vhdl/core_serial/serial.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/mmu/vhdl/core_mmu/mmu.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/irc/vhdl/core_irc/irc.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/icache/vhdl/core_icache/icache.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/dcache/vhdl/core_dcache/dcache.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/bridge/vhdl/core_bridge/bridge.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/bootmem/vhdl/core_bootmem/bootmem.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/core/vhdl/chip_core/core.vhdl ./

cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/ahblite_controller/vhdl/chip_ahblite_controller/ahblite_controller.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/debug_spi_slave/stub/vhdl/debug_spi_slave_stub/debug_spi_stub.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/debug_spi_slave/adapter/vhdl/debug_spi_slave_adapter/debug_adapter.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/debug_spi_slave/vhdl/chip_debug_spi_slave/debug_spi_slave.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/interrupt_stub/vhdl/chip_interrupt_stub/interrupt_stub.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/logger_stub/vhdl/chip_logger_stub/logger_stub.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/reset_pmode_stub/vhdl/chip_reset_pmode_stub/reset_pmode_stub.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/serial_spi_slave/stub/vhdl/serial_spi_slave_stub/serial_spi_stub.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/serial_spi_slave/adapter/vhdl/serial_spi_slave_adapter/serial_adapter.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/serial_spi_slave/vhdl/chip_serial_spi_slave/serial_spi_slave.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/spi_master_interface/vhdl/chip_spi_master_interface/spi_master_interface.vhdl ./
cp $AJIT_PROJECT_HOME/processor/Aa_v3/sys/chip/vhdl/sys_chip/chip.vhdl ./


