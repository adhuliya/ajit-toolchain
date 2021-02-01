library ieee;
use ieee.std_logic_1164.all;

library AjitCustom;
use AjitCustom.AjitCustomComponents.all;

entity serial_spi_stub is
	port (
		SERIAL_SPI_SLAVE_MOSI: in std_logic_vector(0 downto 0);
		SERIAL_SPI_SLAVE_MISO: out std_logic_vector(0 downto 0);
		SERIAL_SPI_SLAVE_CLK: in std_logic_vector(0 downto 0);
		SERIAL_SPI_SLAVE_SS_L: in std_logic_vector(0 downto 0);
		-- from monitor to serial.
		ADAPTER_to_SERIAL_SPI_SLAVE_pipe_write_data: in std_logic_vector(7 downto 0);
		ADAPTER_to_SERIAL_SPI_SLAVE_pipe_write_req:  in std_logic_vector(0 downto 0);
		ADAPTER_to_SERIAL_SPI_SLAVE_pipe_write_ack:  out std_logic_vector(0 downto 0);
		-- from serial to monitor
		SERIAL_SPI_SLAVE_to_ADAPTER_pipe_read_data: out std_logic_vector(7 downto 0);
		SERIAL_SPI_SLAVE_to_ADAPTER_pipe_read_req:  in std_logic_vector(0 downto 0);
		SERIAL_SPI_SLAVE_to_ADAPTER_pipe_read_ack:  out std_logic_vector(0 downto 0);
		-- clk, reset
		clk, reset: in std_logic
	    );
end entity serial_spi_stub;

architecture STUBARCH of serial_spi_stub is
begin

	bridgeInst: spi_slave_pipe_bridge
			port map (
				-- SPI interface
				spi_mosi => SERIAL_SPI_SLAVE_MOSI(0),
				spi_miso => SERIAL_SPI_SLAVE_MISO(0),
				spi_ss_bar => SERIAL_SPI_SLAVE_SS_L(0),
				spi_clk  => SERIAL_SPI_SLAVE_CLK(0),
				out_data_pipe_read_data => SERIAL_SPI_SLAVE_to_ADAPTER_pipe_read_data,
				out_data_pipe_read_req => SERIAL_SPI_SLAVE_to_ADAPTER_pipe_read_req,
				out_data_pipe_read_ack => SERIAL_SPI_SLAVE_to_ADAPTER_pipe_read_ack,
				-- input pipe	
				in_data_pipe_write_data => ADAPTER_to_SERIAL_SPI_SLAVE_pipe_write_data,
				in_data_pipe_write_req  => ADAPTER_to_SERIAL_SPI_SLAVE_pipe_write_req,
				in_data_pipe_write_ack  => ADAPTER_to_SERIAL_SPI_SLAVE_pipe_write_ack,
				-- system clock, reset.
				clk => clk,	
				reset => reset
	     );
end STUBARCH;
