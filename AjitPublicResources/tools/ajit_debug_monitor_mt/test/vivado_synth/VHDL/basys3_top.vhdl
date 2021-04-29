library ieee;
use ieee.std_logic_1164.all;

library simpleUartLib;
use simpleUartLib.all;

entity basys3_top is
	port (CLK100MHZ: in std_logic;
		-- this is the reset (btnC)
		btnC: in std_logic;
		-- LEDS to be driven from AHIR system.
		LEDS: out std_logic_vector(0 to 7);
		-- UART signals, UART configured to 115200 
		-- baud.
		RsRx: in std_logic;
		RsTx: out std_logic
		);
end entity basys3_top;


architecture Struct of basys3_top is

	signal btnC_registered, btnC_synched: std_logic;

	component  adm_test_setup is -- 
  	port( -- 
    		SOC_MONITOR_to_DEBUG_pipe_write_data : in std_logic_vector(7 downto 0);
    		SOC_MONITOR_to_DEBUG_pipe_write_req  : in std_logic_vector(0  downto 0);
    		SOC_MONITOR_to_DEBUG_pipe_write_ack  : out std_logic_vector(0  downto 0);
    		SOC_DEBUG_to_MONITOR_pipe_read_data : out std_logic_vector(7 downto 0);
    		SOC_DEBUG_to_MONITOR_pipe_read_req  : in std_logic_vector(0  downto 0);
    		SOC_DEBUG_to_MONITOR_pipe_read_ack  : out std_logic_vector(0  downto 0);
    		clk, reset: in std_logic 
    		-- 
  		);
	end component adm_test_setup;

    	signal SOC_MONITOR_to_DEBUG_pipe_write_data : std_logic_vector(7 downto 0);
    	signal SOC_MONITOR_to_DEBUG_pipe_write_req  : std_logic_vector(0  downto 0);
    	signal SOC_MONITOR_to_DEBUG_pipe_write_ack  : std_logic_vector(0  downto 0);
    	signal SOC_DEBUG_to_MONITOR_pipe_read_data : std_logic_vector(7 downto 0);
    	signal SOC_DEBUG_to_MONITOR_pipe_read_req  : std_logic_vector(0  downto 0);
    	signal SOC_DEBUG_to_MONITOR_pipe_read_ack  : std_logic_vector(0  downto 0);

	component serial_uart is
		generic (baud_rate, clock_frequency: integer);
		port (clk, reset: in std_logic;
			SERIAL_RX: in std_logic_vector(0 downto 0);	
			SERIAL_TX: out std_logic_vector(0 downto 0);	
	
			SERIAL_TO_CORE_pipe_read_data: out std_logic_vector(7 downto 0);
			SERIAL_TO_CORE_pipe_read_req:  in std_logic_vector(0 downto 0);
			SERIAL_TO_CORE_pipe_read_ack:  out std_logic_vector(0 downto 0);
	
			CORE_TO_SERIAL_pipe_write_data : in std_logic_vector(7 downto 0);
			CORE_TO_SERIAL_pipe_write_req :  in std_logic_vector(0 downto 0);
			CORE_TO_SERIAL_pipe_write_ack :  out std_logic_vector(0 downto 0)
		);
	end component;
begin


	-------------------------------------------------------
	-- synch the switches.
	-------------------------------------------------------
	process(CLK100MHZ)
	begin
		if(CLK100MHZ'event and CLK100MHZ='1') then
			btnC_registered <= btnC;
			btnC_synched    <= btnC_registered;
			if(btnC_synched = '1') then
				LEDS <= "01010101";
			else
				LEDS <= "10101010";
			end if;
		end if;
	end process;

	-------------------------------------------------------
	-- the test structure
	-------------------------------------------------------
	tb_inst:adm_test_setup
  		port map( -- 
    				SOC_MONITOR_to_DEBUG_pipe_write_data,
    				SOC_MONITOR_to_DEBUG_pipe_write_req ,
    				SOC_MONITOR_to_DEBUG_pipe_write_ack ,
    				SOC_DEBUG_to_MONITOR_pipe_read_data ,
    				SOC_DEBUG_to_MONITOR_pipe_read_req  ,
    				SOC_DEBUG_to_MONITOR_pipe_read_ack  ,
    				CLK100MHZ, 
				btnC_synched
    				-- 
  				);

	-------------------------------------------------------
	-- the UART
	-------------------------------------------------------
	uart_inst: serial_uart
		generic map (baud_rate => 115200, clock_frequency => 100000000)
		port map (clk => CLK100MHZ, reset => btnC_synched,
			SERIAL_RX(0)  => RsRx,
			SERIAL_TX(0)  => RsTx,
	
			SERIAL_TO_CORE_pipe_read_data => SOC_MONITOR_TO_DEBUG_pipe_write_data,
			SERIAL_TO_CORE_pipe_read_req  => SOC_MONITOR_TO_DEBUG_pipe_write_ack,
			SERIAL_TO_CORE_pipe_read_ack  => SOC_MONITOR_TO_DEBUG_pipe_write_req,
	
			CORE_TO_SERIAL_pipe_write_data => SOC_DEBUG_TO_MONITOR_pipe_read_data,
			CORE_TO_SERIAL_pipe_write_req => SOC_DEBUG_TO_MONITOR_pipe_read_ack,
			CORE_TO_SERIAL_pipe_write_ack => SOC_DEBUG_TO_MONITOR_pipe_read_req
		);

end Struct;
