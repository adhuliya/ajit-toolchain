library ieee;
use ieee.std_logic_1164.all;

library AjitCustom;
use AjitCustom.AjitCustomComponents.all;

entity debug_spi_stub is
	port (
		DEBUG_SPI_SLAVE_MOSI: in std_logic_vector(0 downto 0);
		DEBUG_SPI_SLAVE_MISO: out std_logic_vector(0 downto 0);
		DEBUG_SPI_SLAVE_CLK: in std_logic_vector(0 downto 0);
		DEBUG_SPI_SLAVE_SS_L: in std_logic_vector(0 downto 0);
		-- from monitor to debug.
		MONITOR_to_DEBUG_pipe_read_data: out std_logic_vector(7 downto 0);
		MONITOR_to_DEBUG_pipe_read_req:  in std_logic_vector(0 downto 0);
		MONITOR_to_DEBUG_pipe_read_ack:  out std_logic_vector(0 downto 0);
		-- from debug to monitor
		DEBUG_to_MONITOR_pipe_write_data: in std_logic_vector(7 downto 0);
		DEBUG_to_MONITOR_pipe_write_req:  in std_logic_vector(0 downto 0);
		DEBUG_to_MONITOR_pipe_write_ack:  out std_logic_vector(0 downto 0);
		-- clk, reset
		clk, reset: in std_logic
	    );
end entity debug_spi_stub;

architecture STUBARCH of debug_spi_stub is
begin

	bridgeInst: spi_slave_pipe_bridge
			port map (
				-- SPI interface
				spi_mosi => DEBUG_SPI_SLAVE_MOSI(0),
				spi_miso => DEBUG_SPI_SLAVE_MISO(0),
				spi_ss_bar => DEBUG_SPI_SLAVE_SS_L(0),
				spi_clk  => DEBUG_SPI_SLAVE_CLK(0),
				out_data_pipe_read_data => MONITOR_to_DEBUG_pipe_read_data,
				out_data_pipe_read_req => MONITOR_to_DEBUG_pipe_read_req,
				out_data_pipe_read_ack => MONITOR_to_DEBUG_pipe_read_ack,
				-- input pipe	
				in_data_pipe_write_data => DEBUG_to_MONITOR_pipe_write_data,
				in_data_pipe_write_req  => DEBUG_to_MONITOR_pipe_write_req,
				in_data_pipe_write_ack  => DEBUG_to_MONITOR_pipe_write_ack,
				-- system clock, reset.
				clk => clk,	
				reset => reset
	     );
end STUBARCH;
