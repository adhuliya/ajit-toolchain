library ieee;
use ieee.std_logic_1164.all;
library ahir;
use ahir.BaseComponents.all;
library AjitCustom;
use AjitCustom.AjitCustomComponents.all;

entity debug_stub is -- 
    port( -- 
      DEBUG_DATA_FROM_AGGREGATOR_pipe_write_data : in std_logic_vector(15 downto 0);
      DEBUG_DATA_FROM_AGGREGATOR_pipe_write_req  : in std_logic_vector(0  downto 0);
      DEBUG_DATA_FROM_AGGREGATOR_pipe_write_ack  : out std_logic_vector(0  downto 0);
      DEBUG_SPI_SLAVE_MISO : in std_logic_vector(0 downto 0);
      SYS_CLK : in std_logic_vector(0 downto 0);
      DEBUG_DATA_TO_AGGREGATOR_pipe_read_data : out std_logic_vector(7 downto 0);
      DEBUG_DATA_TO_AGGREGATOR_pipe_read_req  : in std_logic_vector(0  downto 0);
      DEBUG_DATA_TO_AGGREGATOR_pipe_read_ack  : out std_logic_vector(0  downto 0);
      DEBUG_SPI_SLAVE_CLK : out std_logic_vector(0 downto 0);
      DEBUG_SPI_SLAVE_MOSI : out std_logic_vector(0 downto 0);
      DEBUG_SPI_SLAVE_SS_L : out std_logic_vector(0 downto 0);
      clk, reset: in std_logic 
      -- 
    );
end entity;


architecture Mixed of debug_stub is
	signal spi_cs_n : std_logic_vector(7 downto 0);
begin


	spInst: spi_master_stub
			port map (
				master_in_data_pipe_write_data =>
					DEBUG_DATA_FROM_AGGREGATOR_pipe_write_data,
				master_in_data_pipe_write_req =>
					DEBUG_DATA_FROM_AGGREGATOR_pipe_write_req,
				master_in_data_pipe_write_ack =>
					DEBUG_DATA_FROM_AGGREGATOR_pipe_write_ack,
				master_out_data_pipe_read_data =>
					DEBUG_DATA_TO_AGGREGATOR_pipe_read_data,
				master_out_data_pipe_read_req =>
					DEBUG_DATA_TO_AGGREGATOR_pipe_read_req,
				master_out_data_pipe_read_ack =>
					DEBUG_DATA_TO_AGGREGATOR_pipe_read_ack,
				-- spi-master side.
				spi_miso => DEBUG_SPI_SLAVE_MISO(0),
				spi_mosi => DEBUG_SPI_SLAVE_MOSI(0),
				spi_clk => DEBUG_SPI_SLAVE_CLK(0),
				spi_cs_n => spi_cs_n,
				clk => clk,  reset => reset
				);

	
	-- lowest device is always selected...
	DEBUG_SPI_SLAVE_SS_L(0) <= spi_cs_n(0);
end Mixed;
