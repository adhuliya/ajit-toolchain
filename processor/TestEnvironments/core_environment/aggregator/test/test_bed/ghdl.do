ghdl --clean
ghdl --remove
ghdl -i --work=GhdlLink /home/madhav/AHIR/gitHub/ahir/release/vhdl/GhdlLink.vhdl
ghdl -i --work=aHiR_ieee_proposed /home/madhav/AHIR/gitHub/ahir/release/vhdl/aHiR_ieee_proposed.vhdl
ghdl -i --work=ahir /home/madhav/AHIR/gitHub/ahir/release/vhdl/ahir.vhdl
ghdl -i --work=AjitCustom /home/madhav/AjitProject/Git/AjitRepoV2/processor/vhdl/lib/AjitCustom.vhdl
ghdl -i --work=chip_reset_pmode_stub /home/madhav/AjitProject/Git/AjitRepoV2/processor/TestEnvironments/core_environment/aggregator/test/test_bed/reset_pmode_stub/vhdl/chip_reset_pmode_stub/reset_pmode_stub.vhdl
ghdl -i --work=debug_spi_slave_stub /home/madhav/AjitProject/Git/AjitRepoV2/processor/TestEnvironments/core_environment/aggregator/test/test_bed/debug_spi_slave/stub/vhdl/debug_spi_slave_stub/debug_spi_stub.vhdl
ghdl -i --work=debug_spi_slave_adapter /home/madhav/AjitProject/Git/AjitRepoV2/processor/TestEnvironments/core_environment/aggregator/test/test_bed/debug_spi_slave/adapter/vhdl/debug_spi_slave_adapter/debug_adapter.vhdl
ghdl -i --work=chip_debug_spi_slave /home/madhav/AjitProject/Git/AjitRepoV2/processor/TestEnvironments/core_environment/aggregator/test/test_bed/debug_spi_slave/vhdl/chip_debug_spi_slave/debug_spi_slave.vhdl
ghdl -i --work=sys_aggregator /home/madhav/AjitProject/Git/AjitRepoV2/processor/TestEnvironments/core_environment/aggregator/test/test_bed/aggregator/vhdl/sys_aggregator/aggregator.vhdl
ghdl -i --work=chip_interrupt_stub /home/madhav/AjitProject/Git/AjitRepoV2/processor/TestEnvironments/core_environment/aggregator/test/test_bed/interrupt_stub/vhdl/chip_interrupt_stub/interrupt_stub.vhdl
ghdl -i --work=serial_spi_slave_stub /home/madhav/AjitProject/Git/AjitRepoV2/processor/TestEnvironments/core_environment/aggregator/test/test_bed/serial_spi_slave/stub/vhdl/serial_spi_slave_stub/serial_spi_stub.vhdl
ghdl -i --work=serial_spi_slave_adapter /home/madhav/AjitProject/Git/AjitRepoV2/processor/TestEnvironments/core_environment/aggregator/test/test_bed/serial_spi_slave/adapter/vhdl/serial_spi_slave_adapter/serial_adapter.vhdl
ghdl -i --work=chip_serial_spi_slave /home/madhav/AjitProject/Git/AjitRepoV2/processor/TestEnvironments/core_environment/aggregator/test/test_bed/serial_spi_slave/vhdl/chip_serial_spi_slave/serial_spi_slave.vhdl
ghdl -i --work=sys_debug_stub /home/madhav/AjitProject/Git/AjitRepoV2/processor/TestEnvironments/core_environment/aggregator/test/test_bed/debug_stub/vhdl/sys_debug_stub/debug_stub.vhdl
ghdl -i --work=sys_chip_stub /home/madhav/AjitProject/Git/AjitRepoV2/processor/TestEnvironments/core_environment/aggregator/test/test_bed/chip_stub/vhdl/sys_chip_stub/chip_stub.vhdl
ghdl -i --work=sys_serial_stub /home/madhav/AjitProject/Git/AjitRepoV2/processor/TestEnvironments/core_environment/aggregator/test/test_bed/serial_stub/vhdl/sys_serial_stub/serial_stub.vhdl
ghdl -i --work=sys_test_bed /home/madhav/AjitProject/Git/AjitRepoV2/processor/TestEnvironments/core_environment/aggregator/test/test_bed/vhdl/sys_test_bed/test_bed.vhdl
ghdl -i --work=work /home/madhav/AjitProject/Git/AjitRepoV2/processor/TestEnvironments/core_environment/aggregator/test/test_bed/vhdl/testbench/test_bed_test_bench.vhdl
ghdl -m --work=work -Wl,-L/home/madhav/AHIR/gitHub/ahir/release/lib -Wl,-lVhpi test_bed_test_bench
