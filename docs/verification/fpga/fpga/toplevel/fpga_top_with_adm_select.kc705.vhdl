library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library unisim;
use unisim.vcomponents.all; -- for 7-series FPGA's

library GenericCoreAddOnLib;
use GenericCoreAddOnLib.GenericCoreAddOnPackage.all;

library simpleI2CLib;
use simpleI2CLib.i2cBaseComponents.all;

library simpleUartLib;
use simpleUartLib.uartPackage.all;

library myUartLib;
use myUartLib.myUartPackage.all;

library SpiMasterLib;
use SpiMasterLib.SpiMasterLibComponents.all;

library AjitCustom;
use AjitCustom.AjitCustomComponents.all;

library afb_gnss_lib;
use afb_gnss_lib.afb_gnss_lib_package.all;

library ajit_sac_processor_lib;
use ajit_sac_processor_lib.ajit_sac_processor_config.all;


entity fpga_top is
port(
      DEBUG_UART_RX : in std_logic;
      DEBUG_UART_TX : out std_logic;
      --
      -- we will multi-plex the two uarts into one set of
      -- signals...
      --
      SERIAL_UART_RX : in std_logic;
      SERIAL_UART_TX : out std_logic;

      CPU_MODE_0_0 : out std_logic_vector(1 downto 0);
      CPU_MODE_1_0 : out std_logic_vector(1 downto 0);
      USE_ADM_MODE: in std_logic;
      spi_miso : in std_logic;
      spi_clk : out std_logic;
      spi_cs : out std_logic;
      spi_mosi : out std_logic;
      clk_p,clk_n, reset,reset_clk: in std_logic
	);
end entity fpga_top;

architecture structure of fpga_top is

	component ajit_sac_processor is -- 
  	port( -- 
		-------------------------------------------------------------------------
		-- set to '1' to use Ajit Debug Monitor
		-------------------------------------------------------------------------
    		USE_ADM_MODE : in std_logic_vector(0 downto 0);
		-------------------------------------------------------------------------
		-- set to '1' for debugging.
		-------------------------------------------------------------------------
    		DEBUG_MODE : in std_logic_vector(0 downto 0);
		-------------------------------------------------------------------------
		-- processor modes for thread 0 and thread 1 
		--   00 un-initialized, 01 reset, 10 run, 11 error
		-- 
		-------------------------------------------------------------------------
    		CPU_MODE_0_0 : out std_logic_vector(1 downto 0);
    		CPU_MODE_1_0 : out std_logic_vector(1 downto 0);
		-------------------------------------------------------------------------
		-- external interrupts for SAC.. map to IRL 13?
		--   note: IRL=10 used for timer, IRL=12 for serial 0
		-------------------------------------------------------------------------
    		GNSS_MAIN_INTERRUPT : in std_logic_vector(0 downto 0);      -- IRL 13
    		WATCHDOG_TIMER_INTERRUPT : in std_logic_vector(0 downto 0); -- IRL 15, NMI
		-------------------------------------------------------------------------
		--   Watch dog timer kick.
		-------------------------------------------------------------------------
    		WATCHDOG_TIMER_KICK : out std_logic_vector(0 downto 0);
		-------------------------------------------------------------------------
		--  DPRAM 0 request port (4KB)
		-------------------------------------------------------------------------
    		AFB_DPRAM_0_1_REQUEST_pipe_write_data : in std_logic_vector(73 downto 0);
    		AFB_DPRAM_0_1_REQUEST_pipe_write_req  : in std_logic_vector(0  downto 0);
    		AFB_DPRAM_0_1_REQUEST_pipe_write_ack  : out std_logic_vector(0  downto 0);
    		AFB_DPRAM_0_1_RESPONSE_pipe_read_data : out std_logic_vector(32 downto 0);
    		AFB_DPRAM_0_1_RESPONSE_pipe_read_req  : in std_logic_vector(0  downto 0);
    		AFB_DPRAM_0_1_RESPONSE_pipe_read_ack  : out std_logic_vector(0  downto 0);
		-------------------------------------------------------------------------
		--  DPRAM 1 request port (4KB)
		-------------------------------------------------------------------------
    		AFB_DPRAM_1_1_REQUEST_pipe_write_data : in std_logic_vector(73 downto 0);
    		AFB_DPRAM_1_1_REQUEST_pipe_write_req  : in std_logic_vector(0  downto 0);
    		AFB_DPRAM_1_1_REQUEST_pipe_write_ack  : out std_logic_vector(0  downto 0);
    		AFB_DPRAM_1_1_RESPONSE_pipe_read_data : out std_logic_vector(32 downto 0);
    		AFB_DPRAM_1_1_RESPONSE_pipe_read_req  : in std_logic_vector(0  downto 0);
    		AFB_DPRAM_1_1_RESPONSE_pipe_read_ack  : out std_logic_vector(0  downto 0);
		-------------------------------------------------------------------------
		-- GNSS access port
		-------------------------------------------------------------------------
		pread				: out std_logic_vector(0 downto 0);
		pwrite				: out std_logic_vector(0 downto 0);
		prdata				: in std_logic_vector(31 downto 0);
		pwdata				: out std_logic_vector(31 downto 0);
		praddr				: out std_logic_vector(15 downto 0);
		pwaddr				: out std_logic_vector(15 downto 0);
		-- NOTE: pintr from GNSS is mapped to GNSS_MAIN_INTERRUPT 
		-------------------------------------------------------------------------
		-- MIL 1553 access port (2 numbers...)
		-------------------------------------------------------------------------
		-- first instance.
    		AFB_MIL_1553_0_REQUEST_pipe_read_data : out std_logic_vector(73 downto 0);
    		AFB_MIL_1553_0_REQUEST_pipe_read_req  : in std_logic_vector(0  downto 0);
    		AFB_MIL_1553_0_REQUEST_pipe_read_ack  : out std_logic_vector(0  downto 0);
    		AFB_MIL_1553_0_RESPONSE_pipe_write_data : in std_logic_vector(32 downto 0);
    		AFB_MIL_1553_0_RESPONSE_pipe_write_req  : in std_logic_vector(0  downto 0);
    		AFB_MIL_1553_0_RESPONSE_pipe_write_ack  : out std_logic_vector(0  downto 0);
		-- second instance.
    		AFB_MIL_1553_1_REQUEST_pipe_read_data : out std_logic_vector(73 downto 0);
    		AFB_MIL_1553_1_REQUEST_pipe_read_req  : in std_logic_vector(0  downto 0);
    		AFB_MIL_1553_1_REQUEST_pipe_read_ack  : out std_logic_vector(0  downto 0);
    		AFB_MIL_1553_1_RESPONSE_pipe_write_data : in std_logic_vector(32 downto 0);
    		AFB_MIL_1553_1_RESPONSE_pipe_write_req  : in std_logic_vector(0  downto 0);
    		AFB_MIL_1553_1_RESPONSE_pipe_write_ack  : out std_logic_vector(0  downto 0);
		-------------------------------------------------------------------------
		-- SERIAL 0 (FIFO from processor to UART)
		-------------------------------------------------------------------------
		UART_0_RX: in  std_logic_vector( 0 downto 0);
		UART_0_TX: out std_logic_vector( 0 downto 0);
		-------------------------------------------------------------------------
		-- SERIAL 1 (FIFO from UART to processor)
		-------------------------------------------------------------------------
		UART_1_RX: in  std_logic_vector( 0 downto 0);
		UART_1_TX: out std_logic_vector( 0 downto 0);
		-------------------------------------------------------------------------
		-- Debug UART
		-------------------------------------------------------------------------
		DEBUG_UART_RX: in  std_logic_vector( 0 downto 0);
		DEBUG_UART_TX: out std_logic_vector( 0 downto 0);
		-------------------------------------------------------------------------
		-- GPIO
		-------------------------------------------------------------------------
    		GPIO_DIN_16         : in std_logic_vector(15 downto 0);
    		GPIO_DOUT_16        : out std_logic_vector(15 downto 0);
    		GPIO_DOUT_ENABLE_16 : out std_logic_vector(15 downto 0);
		-------------------------------------------------------------------------
		-- I2C
		-------------------------------------------------------------------------
    		I2C_SCL_IN : in std_logic_vector(0 downto 0);
    		I2C_SDA_IN : in std_logic_vector(0 downto 0);
    		I2C_SCL_PULL_DOWN : out std_logic_vector(0 downto 0);
    		I2C_SDA_PULL_DOWN : out std_logic_vector(0 downto 0);
		-------------------------------------------------------------------------
		-- SPI FLASH
		-------------------------------------------------------------------------
    		SPI_FLASH_MISO : in std_logic_vector(0 downto 0);
    		SPI_FLASH_MOSI : out std_logic_vector(0 downto 0);
    		SPI_FLASH_CLK : out std_logic_vector(0 downto 0);
    		SPI_FLASH_CS_L : out std_logic_vector(0 downto 0);
		-------------------------------------------------------------------------
		-- Set write protect = 0 if you wish to write into flash
		-------------------------------------------------------------------------
    		WRITE_PROTECT : in std_logic_vector(0 downto 0);
		-------------------------------------------------------------------------
		-- SPI master (8 slaves)
		-------------------------------------------------------------------------
    		SPI_MASTER_MISO : in std_logic_vector(0 downto 0);
    		SPI_MASTER_MOSI : out std_logic_vector(0 downto 0);
    		SPI_MASTER_CLK : out std_logic_vector(0 downto 0);
    		SPI_MASTER_CS_N : out std_logic_vector(7 downto 0);
		-------------------------------------------------------------------------
		-- SPI slave 
		-------------------------------------------------------------------------
		SPI_SLAVE_MISO : out std_logic_vector(0 downto 0);
    		SPI_SLAVE_MISO_ENABLE : out std_logic_vector(0 downto 0);
      		SPI_SLAVE_CLK : in std_logic_vector(0 downto 0);
      		SPI_SLAVE_CS_BAR : in std_logic_vector(0 downto 0);
      		SPI_SLAVE_MOSI : in std_logic_vector(0 downto 0);
		-------------------------------------------------------------------------
		-- debug signals.
		-------------------------------------------------------------------------
    		DBG_CLOCK_ENABLE_BAR_0 : out std_logic_vector(0 downto 0);
    		DBG_CLOCK_ENABLE_BAR_1 : out std_logic_vector(0 downto 0);
    		DBG_OK_TO_SUSPEND_0 : out std_logic_vector(0 downto 0);
    		DBG_OK_TO_SUSPEND_1 : out std_logic_vector(0 downto 0);
    		DBG_SOFT_RESET_0 : out std_logic_vector(0 downto 0);
    		DBG_SOFT_RESET_1 : out std_logic_vector(0 downto 0);

		-------------------------------------------------------------------------
		-- single clock, rising edge.  reset is assumed synchronous, active high.
		-------------------------------------------------------------------------
    		clk, reset: in std_logic 
    		-- 
  		);
  		--
	end component  ajit_sac_processor;

	-- control from ajit debug monitor.
        signal DEBUG_MODE : std_logic;
	signal CLOCK_GATING_IS_ON: std_logic;

	--------------------------------------------------------------
	-- SPI Master ports.
	--------------------------------------------------------------
    	signal SPI_MASTER_MISO: std_logic_vector(0 downto 0);
    	signal SPI_MASTER_CLK:  std_logic_vector(0 downto 0);
    	signal SPI_MASTER_CS_N: std_logic_vector(7 downto 0);
    	signal SPI_MASTER_MOSI: std_logic_vector(0 downto 0); 

	-- pinger..
    	signal SPI_PING_MISO: std_logic_vector(6 downto 0);
	

	--------------------------------------------------------------
	-- SPI FLASH ports.
	--------------------------------------------------------------
	signal SPI_FLASH_CLK:  std_logic;
	signal SPI_FLASH_CS_L:  std_logic;
    	signal WRITE_PROTECT : std_logic;

	--------------------------------------------------------------
	-- External interrupts.
	--------------------------------------------------------------
    	signal GNSS_MAIN_INTERRUPT : std_logic;
    	signal WATCHDOG_TIMER_INTERRUPT : std_logic;
    	signal WATCHDOG_TIMER_KICK : std_logic;
    	signal WATCHDOG_TIMER_ENABLE : std_logic;
	
	--------------------------------------------------------------
	-- AFB ports.
	--------------------------------------------------------------
    	signal AFB_DPRAM_0_1_REQUEST_pipe_write_data :std_logic_vector(73 downto 0);
    	signal AFB_DPRAM_0_1_REQUEST_pipe_write_req  :std_logic_vector(0  downto 0);
    	signal AFB_DPRAM_0_1_REQUEST_pipe_write_ack  :std_logic_vector(0  downto 0);
    	signal AFB_DPRAM_0_1_RESPONSE_pipe_read_data :std_logic_vector(32 downto 0);
    	signal AFB_DPRAM_0_1_RESPONSE_pipe_read_req  :std_logic_vector(0  downto 0);
    	signal AFB_DPRAM_0_1_RESPONSE_pipe_read_ack  :std_logic_vector(0  downto 0);
	-------------------------------------------------------------------------
	--  DPRAM 1 request port (4KB)
	-------------------------------------------------------------------------
    	signal AFB_DPRAM_1_1_REQUEST_pipe_write_data :std_logic_vector(73 downto 0);
    	signal AFB_DPRAM_1_1_REQUEST_pipe_write_req  :std_logic_vector(0  downto 0);
    	signal AFB_DPRAM_1_1_REQUEST_pipe_write_ack  :std_logic_vector(0  downto 0);
    	signal AFB_DPRAM_1_1_RESPONSE_pipe_read_data :std_logic_vector(32 downto 0);
    	signal AFB_DPRAM_1_1_RESPONSE_pipe_read_req  :std_logic_vector(0  downto 0);
    	signal AFB_DPRAM_1_1_RESPONSE_pipe_read_ack  :std_logic_vector(0  downto 0);
	-------------------------------------------------------------------------
	--  MIL-1553 ports.
	-------------------------------------------------------------------------
	-- first instance.
    	signal AFB_MIL_1553_0_REQUEST_pipe_read_data   : std_logic_vector(73 downto 0);
    	signal AFB_MIL_1553_0_REQUEST_pipe_read_req    : std_logic_vector(0  downto 0);
    	signal AFB_MIL_1553_0_REQUEST_pipe_read_ack    : std_logic_vector(0  downto 0);
    	signal AFB_MIL_1553_0_RESPONSE_pipe_write_data : std_logic_vector(32 downto 0);
    	signal AFB_MIL_1553_0_RESPONSE_pipe_write_req  : std_logic_vector(0  downto 0);
    	signal AFB_MIL_1553_0_RESPONSE_pipe_write_ack  : std_logic_vector(0  downto 0);
	-- second instance.
    	signal AFB_MIL_1553_1_REQUEST_pipe_read_data   : std_logic_vector(73 downto 0);
    	signal AFB_MIL_1553_1_REQUEST_pipe_read_req    : std_logic_vector(0  downto 0);
    	signal AFB_MIL_1553_1_REQUEST_pipe_read_ack    : std_logic_vector(0  downto 0);
    	signal AFB_MIL_1553_1_RESPONSE_pipe_write_data : std_logic_vector(32 downto 0);
    	signal AFB_MIL_1553_1_RESPONSE_pipe_write_req  : std_logic_vector(0  downto 0);
    	signal AFB_MIL_1553_1_RESPONSE_pipe_write_ack  : std_logic_vector(0  downto 0);
	-------------------------------------------------------------------------
	-- GNSS access port
	-------------------------------------------------------------------------
	signal pread				: std_logic_vector(0 downto 0);
	signal pwrite				: std_logic_vector(0 downto 0);
	signal prdata				: std_logic_vector(31 downto 0);
	signal pwdata				: std_logic_vector(31 downto 0);
	signal praddr				: std_logic_vector(15 downto 0);
	signal pwaddr				: std_logic_vector(15 downto 0);
	-------------------------------------------------------------------------
	-- MIL 1553 access port
	-------------------------------------------------------------------------
    	signal AFB_MIL_1553_REQUEST_pipe_read_data :std_logic_vector(73 downto 0);
    	signal AFB_MIL_1553_REQUEST_pipe_read_req  :std_logic_vector(0  downto 0);
    	signal AFB_MIL_1553_REQUEST_pipe_read_ack  :std_logic_vector(0  downto 0);
    	signal AFB_MIL_1553_RESPONSE_pipe_write_data :std_logic_vector(32 downto 0);
    	signal AFB_MIL_1553_RESPONSE_pipe_write_req  :std_logic_vector(0  downto 0);
    	signal AFB_MIL_1553_RESPONSE_pipe_write_ack  : std_logic_vector(0  downto 0);
	
	--------------------------------------------------------------
	-- 16-bit GPIO.
	--------------------------------------------------------------
    	signal GPIO_DIN_16 : std_logic_vector(15 downto 0);
    	signal GPIO_DOUT_16 : std_logic_vector(15 downto 0);
    	signal GPIO_DOUT_ENABLE_16 : std_logic_vector(15 downto 0);
	--------------------------------------------------------------
	-- UARTS
	--------------------------------------------------------------
	signal SERIAL_UART_0_RX: std_logic;
	signal SERIAL_UART_1_RX: std_logic;

	signal SERIAL_UART_0_TX: std_logic;
	signal SERIAL_UART_1_TX: std_logic;

	--------------------------------------------------------------
	-- I2C master connections
	--------------------------------------------------------------
    	signal I2C_SCL_PULL_DOWN : std_logic;
    	signal I2C_SDA_PULL_DOWN : std_logic;

	signal I2C_SDA_RESOLVED : std_logic;
	signal I2C_SCL_RESOLVED : std_logic;

	signal I2C_SCL_SLAVE_OUT : std_logic;
	signal I2C_SDA_SLAVE_OUT : std_logic;

	--------------------------------------------------------------
	-- SPI SLAVE master connections
	--------------------------------------------------------------
	signal SPI_SLAVE_MISO : std_logic_vector(0 downto 0);
    	signal SPI_SLAVE_MISO_ENABLE : std_logic_vector(0 downto 0);
      	signal SPI_SLAVE_CLK : std_logic_vector(0 downto 0);
      	signal SPI_SLAVE_CS_BAR : std_logic_vector(0 downto 0);
      	signal SPI_SLAVE_MOSI : std_logic_vector(0 downto 0);

	--------------------------------------------------------------
	-- Debug connections
	--------------------------------------------------------------
    	signal DBG_CLOCK_ENABLE_BAR_0 : std_logic_vector(0 downto 0);
    	signal DBG_CLOCK_ENABLE_BAR_1 : std_logic_vector(0 downto 0);
    	signal DBG_OK_TO_SUSPEND_0 : std_logic_vector(0 downto 0);
    	signal DBG_OK_TO_SUSPEND_1 : std_logic_vector(0 downto 0);
    	signal DBG_SOFT_RESET_0 : std_logic_vector(0 downto 0);
    	signal DBG_SOFT_RESET_1 : std_logic_vector(0 downto 0);


	component clk_wiz_0
  		port
   			(-- Clock in ports
    				-- Clock out ports
    				clk_out1          : out    std_logic;
    				-- Status and control signals
    				reset             : in     std_logic;
    				locked            : out    std_logic;
    				clk_in1_p         : in     std_logic;
    				clk_in1_n         : in     std_logic
   			);
	end component;

	signal spi_clk1:std_logic;
	signal reset1,reset2,reset_sync, reset_sync_n: std_logic;
	signal CLK,lock:std_logic;


	signal COUNTER: integer;

	component vio_0 is
  	Port ( 
    	  clk : in STD_LOGIC;
    	  probe_in0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    	  probe_in1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    	  probe_in2 : in STD_LOGIC_VECTOR ( 0 to 0 );
    	  probe_in3 : in STD_LOGIC_VECTOR ( 0 to 0 );
    	  probe_in4 : in STD_LOGIC_VECTOR ( 0 to 0 );
    	  probe_in5 : in STD_LOGIC_VECTOR ( 0 to 0 );
    	  probe_in6 : in STD_LOGIC_VECTOR ( 0 to 0 );
    	  probe_in7 : in STD_LOGIC_VECTOR ( 0 to 0 );
    	  probe_out0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    	  probe_out1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    	  probe_out2 : out STD_LOGIC_VECTOR ( 0 to 0 );
    	  probe_out3 : out STD_LOGIC_VECTOR ( 0 to 0 );
    	  probe_out4 : out STD_LOGIC_VECTOR ( 0 to 0 );
    	  probe_out5 : out STD_LOGIC_VECTOR ( 0 to 0 );
    	  probe_out6 : out STD_LOGIC_VECTOR ( 0 to 0 );
    	  probe_out7 : out STD_LOGIC_VECTOR ( 0 to 0 )
  	  );
	end component vio_0;

	signal reset_vio, probe_out_1: std_logic_vector(0 downto 0);
	signal probe_out_2, probe_out_3, probe_out_4, probe_out_5, probe_out_6, probe_out_7: std_logic_vector(0 downto 0);
	signal reset_merged : std_logic;
	
begin

	DEBUG_MODE <= '0';

	
	------------------------------------------------------------------------------------------
	-- SPI clock.... note Startup below..
	------------------------------------------------------------------------------------------
	spi_clk  <= SPI_FLASH_CLK;
	spi_clk1 <= SPI_FLASH_CLK; 
	spi_cs   <= SPI_FLASH_CS_L;

	clocking : clk_wiz_0
   		port map ( 
  			-- Clock out ports  
   			clk_out1 => CLK,
  			-- Status and control signals                
   			reset => reset_clk,
   			locked => lock,
   			-- Clock in ports
   			clk_in1_p => clk_p,
   			clk_in1_n => clk_n
 		);

	-- Save the push button..
	vio_inst: vio_0
	port map (
                      clk            => clk, 
                      probe_in0(0)   => lock,
                      probe_in1(0)   => DBG_CLOCK_ENABLE_BAR_0(0),
                      probe_in2(0)   => DBG_CLOCK_ENABLE_BAR_1(0),
                      probe_in3(0)   => DBG_SOFT_RESET_0(0),
                      probe_in4(0)   => DBG_SOFT_RESET_1(0),
                      probe_in5(0)   => DBG_OK_TO_SUSPEND_0(0),
                      probe_in6(0)   => DBG_OK_TO_SUSPEND_0(0),
                      probe_in7(0)   => CLOCK_GATING_IS_ON,
                      probe_out0     => reset_vio,
                      probe_out1(0)  => WATCHDOG_TIMER_ENABLE,
                      probe_out2     => probe_out_2,
                      probe_out3     => probe_out_3,
                      probe_out4     => probe_out_4,
                      probe_out5     => probe_out_5,
                      probe_out6     => probe_out_6,
                      probe_out7     => probe_out_7
                );
	CLOCK_GATING_IS_ON <= '1' when USE_CLOCK_GATING else '0';

	reset_merged <= reset_vio(0) or reset;

	
	processor_inst: ajit_sac_processor
		port map (
			-------------------------------------------------------------------------
			-- ADM mode.
			-------------------------------------------------------------------------
    			USE_ADM_MODE(0) => USE_ADM_MODE,
			-------------------------------------------------------------------------
			-- set to '1' for debugging.
			-------------------------------------------------------------------------
    			DEBUG_MODE(0) => DEBUG_MODE,
			-------------------------------------------------------------------------
			-- processor mode	
			--   00 un-initialized, 01 reset, 10 run, 11 error
			-------------------------------------------------------------------------
    			CPU_MODE_0_0 => CPU_MODE_0_0,
    			CPU_MODE_1_0 => CPU_MODE_1_0,
			-------------------------------------------------------------------------
			-- external interrupts
			-------------------------------------------------------------------------
    			GNSS_MAIN_INTERRUPT(0)      => GNSS_MAIN_INTERRUPT,
			WATCHDOG_TIMER_INTERRUPT(0) => WATCHDOG_TIMER_INTERRUPT,
			-------------------------------------------------------------------------
			-- Watch dog timer kick..
			-------------------------------------------------------------------------
			WATCHDOG_TIMER_KICK(0) => WATCHDOG_TIMER_KICK,
			-------------------------------------------------------------------------
			--  DPRAM 0 request port (4KB)
			-------------------------------------------------------------------------
    			AFB_DPRAM_0_1_REQUEST_pipe_write_data  => AFB_DPRAM_0_1_REQUEST_pipe_write_data ,
    			AFB_DPRAM_0_1_REQUEST_pipe_write_req  => AFB_DPRAM_0_1_REQUEST_pipe_write_req ,
    			AFB_DPRAM_0_1_REQUEST_pipe_write_ack   => AFB_DPRAM_0_1_REQUEST_pipe_write_ack  ,
    			AFB_DPRAM_0_1_RESPONSE_pipe_read_data  => AFB_DPRAM_0_1_RESPONSE_pipe_read_data ,
    			AFB_DPRAM_0_1_RESPONSE_pipe_read_req   => AFB_DPRAM_0_1_RESPONSE_pipe_read_req  ,
    			AFB_DPRAM_0_1_RESPONSE_pipe_read_ack   => AFB_DPRAM_0_1_RESPONSE_pipe_read_ack   ,
			-------------------------------------------------------------------------
			--  DPRAM 1 request port (4KB)
			-------------------------------------------------------------------------
    			AFB_DPRAM_1_1_REQUEST_pipe_write_data  => AFB_DPRAM_1_1_REQUEST_pipe_write_data ,
    			AFB_DPRAM_1_1_REQUEST_pipe_write_req   => AFB_DPRAM_1_1_REQUEST_pipe_write_req  ,
    			AFB_DPRAM_1_1_REQUEST_pipe_write_ack   => AFB_DPRAM_1_1_REQUEST_pipe_write_ack  ,
    			AFB_DPRAM_1_1_RESPONSE_pipe_read_data  => AFB_DPRAM_1_1_RESPONSE_pipe_read_data ,
    			AFB_DPRAM_1_1_RESPONSE_pipe_read_req   => AFB_DPRAM_1_1_RESPONSE_pipe_read_req  ,
    			AFB_DPRAM_1_1_RESPONSE_pipe_read_ack   => AFB_DPRAM_1_1_RESPONSE_pipe_read_ack  ,
			-------------------------------------------------------------------------
			-- GNSS access port
			-------------------------------------------------------------------------
			pread => pread,
			pwrite => pwrite,
			prdata => prdata,
			pwdata => pwdata,
			praddr => praddr,
			pwaddr => pwaddr,
			-------------------------------------------------------------------------
			-- MIL 1553 access ports
			-------------------------------------------------------------------------
    			AFB_MIL_1553_0_REQUEST_pipe_read_data  => AFB_MIL_1553_0_REQUEST_pipe_read_data ,
    			AFB_MIL_1553_0_REQUEST_pipe_read_req   => AFB_MIL_1553_0_REQUEST_pipe_read_req  ,
    			AFB_MIL_1553_0_REQUEST_pipe_read_ack   => AFB_MIL_1553_0_REQUEST_pipe_read_ack  ,
    			AFB_MIL_1553_0_RESPONSE_pipe_write_data  => AFB_MIL_1553_0_RESPONSE_pipe_write_data ,
    			AFB_MIL_1553_0_RESPONSE_pipe_write_req   => AFB_MIL_1553_0_RESPONSE_pipe_write_req  ,
    			AFB_MIL_1553_0_RESPONSE_pipe_write_ack   => AFB_MIL_1553_0_RESPONSE_pipe_write_ack  ,
			-- second instance.
    			AFB_MIL_1553_1_REQUEST_pipe_read_data  => AFB_MIL_1553_1_REQUEST_pipe_read_data ,
    			AFB_MIL_1553_1_REQUEST_pipe_read_req   => AFB_MIL_1553_1_REQUEST_pipe_read_req  ,
    			AFB_MIL_1553_1_REQUEST_pipe_read_ack   => AFB_MIL_1553_1_REQUEST_pipe_read_ack  ,
    			AFB_MIL_1553_1_RESPONSE_pipe_write_data  => AFB_MIL_1553_1_RESPONSE_pipe_write_data ,
    			AFB_MIL_1553_1_RESPONSE_pipe_write_req   => AFB_MIL_1553_1_RESPONSE_pipe_write_req  ,
    			AFB_MIL_1553_1_RESPONSE_pipe_write_ack   => AFB_MIL_1553_1_RESPONSE_pipe_write_ack  ,
			-------------------------------------------------------------------------
			-- SERIAL 0 (FIFO from processor to UART)
			-------------------------------------------------------------------------
			UART_0_RX(0) => SERIAL_UART_0_RX,
			UART_0_TX(0) => SERIAL_UART_0_TX,
			-------------------------------------------------------------------------
			-- SERIAL 1 (FIFO from UART to processor)
			-------------------------------------------------------------------------
			UART_1_RX(0) => SERIAL_UART_1_RX,
			UART_1_TX(0) => SERIAL_UART_1_TX,
			-------------------------------------------------------------------------
			-- Debug comand FIFO (from debug UART to processor)
			-------------------------------------------------------------------------
			DEBUG_UART_RX(0) => DEBUG_UART_RX,
			DEBUG_UART_TX(0) => DEBUG_UART_TX,
			-------------------------------------------------------------------------
			-- GPIO
			-------------------------------------------------------------------------
    			GPIO_DIN_16 => GPIO_DIN_16,
    			GPIO_DOUT_16  => GPIO_DOUT_16,
    			GPIO_DOUT_ENABLE_16  => GPIO_DOUT_ENABLE_16,
			-------------------------------------------------------------------------
			-- I2C
			-------------------------------------------------------------------------
    			I2C_SCL_IN(0) => I2C_SCL_RESOLVED ,
    			I2C_SDA_IN(0) => I2C_SDA_RESOLVED ,
    			I2C_SCL_PULL_DOWN(0) => I2C_SCL_PULL_DOWN ,
    			I2C_SDA_PULL_DOWN(0) => I2C_SDA_PULL_DOWN ,
			-------------------------------------------------------------------------
			-- SPI FLASH
			-------------------------------------------------------------------------
    			SPI_FLASH_MISO(0) => spi_miso ,
    			SPI_FLASH_MOSI(0) => spi_mosi ,
    			SPI_FLASH_CLK(0) =>  SPI_FLASH_CLK ,
    			SPI_FLASH_CS_L(0) => SPI_FLASH_CS_L ,
			-------------------------------------------------------------------------
			-- Set write protect = 0 if you wish to write into flash
			-------------------------------------------------------------------------
    			WRITE_PROTECT(0) => WRITE_PROTECT,
			-------------------------------------------------------------------------
			-- SPI master (8 slaves)
			-------------------------------------------------------------------------
    			SPI_MASTER_MISO => SPI_MASTER_MISO ,
    			SPI_MASTER_MOSI => SPI_MASTER_MOSI ,
    			SPI_MASTER_CLK  => SPI_MASTER_CLK ,
    			SPI_MASTER_CS_N => SPI_MASTER_CS_N ,
			-------------------------------------------------------------------------
			-- SPI slave 
			-------------------------------------------------------------------------
			SPI_SLAVE_MISO  => SPI_SLAVE_MISO ,
    			SPI_SLAVE_MISO_ENABLE  => SPI_SLAVE_MISO_ENABLE ,
      			SPI_SLAVE_CLK  => SPI_SLAVE_CLK ,
      			SPI_SLAVE_CS_BAR  => SPI_SLAVE_CS_BAR ,
      			SPI_SLAVE_MOSI  => SPI_SLAVE_MOSI ,
			-------------------------------------------------------------------------
			-- Debug connections
			-------------------------------------------------------------------------
    			DBG_CLOCK_ENABLE_BAR_0 => DBG_CLOCK_ENABLE_BAR_0 ,
    			DBG_CLOCK_ENABLE_BAR_1 => DBG_CLOCK_ENABLE_BAR_1 ,
    			DBG_OK_TO_SUSPEND_0 => DBG_OK_TO_SUSPEND_0 ,
    			DBG_OK_TO_SUSPEND_1 => DBG_OK_TO_SUSPEND_1 ,
    			DBG_SOFT_RESET_0 => DBG_SOFT_RESET_0 ,
    			DBG_SOFT_RESET_1  => DBG_SOFT_RESET_1 ,
			-------------------------------------------------------------------------
			-- Clock, reset.
			-------------------------------------------------------------------------
    			CLK => CLK, RESET => RESET_SYNC
		);

	-- allow writes to flash
	WRITE_PROTECT  <= '0';
	
	-----------------------------------------------------------------
	-- Six SPI pingers to check SPI master..
	-----------------------------------------------------------------
	spiPingGen: for S in 0 to 6  generate
          spi_ping_inst: 
		spi_ping port map (CS_L => SPI_MASTER_CS_N(S),
					SPI_MASTER_MISO(0) => SPI_PING_MISO(S),
					SPI_MASTER_MOSI(0) => SPI_MASTER_MOSI(0),
					SPI_MASTER_CLK(0)  => SPI_MASTER_CLK(0),
					clk => clk , reset => reset_sync);
	end generate spiPingGen;


	-- fixed code to check.
	GPIO_DIN_16 <= x"abcd";

	-----------------------------------------------------------------
	-- One  SPI slave controlled by SPI master CS(7)
	--   (note: slave is inside the processor).
	-----------------------------------------------------------------
	SPI_SLAVE_CLK(0)    <= SPI_MASTER_CLK(0);
	SPI_SLAVE_CS_BAR(0) <= SPI_MASTER_CS_N(7);
	SPI_SLAVE_MOSI(0)   <= SPI_MASTER_MOSI(0); 

	-----------------------------------------------------------------
	-- I2C slave etc.
	-----------------------------------------------------------------
	i2c_slave_mem_inst: I2CSLAVEMEM
			port map (MCLK => clk,
					nRST => reset_sync_n,
					SDA_IN => I2C_SDA_RESOLVED,
					SCL_IN => I2C_SCL_RESOLVED,
					SDA_OUT => I2C_SDA_SLAVE_OUT,
					SCL_OUT => I2C_SCL_SLAVE_OUT);

	I2C_SDA_RESOLVED <= (not I2C_SDA_PULL_DOWN) and I2C_SDA_SLAVE_OUT;
	I2C_SCL_RESOLVED <= (not I2C_SCL_PULL_DOWN) and I2C_SCL_SLAVE_OUT;

	-----------------------------------------------------------------------
	-- mimic wired OR
	-----------------------------------------------------------------------
	process (SPI_PING_MISO, SPI_SLAVE_MISO)
		variable tvar: std_logic;
	begin
		tvar := SPI_SLAVE_MISO(0);
		for I in 0 to 6 loop
			tvar := tvar or SPI_PING_MISO(I);
		end loop;
		SPI_MASTER_MISO(0) <= tvar;
	end process;

	----------------------------------------------------------------------------------
	-- UART multiplexing... On KC705, only one uart is available for serial
	--    use GPIO_DOUT_ENABLE_16(15) to select between the two uarts..
	----------------------------------------------------------------------------------
	SERIAL_UART_TX   <= SERIAL_UART_0_TX when (GPIO_DOUT_ENABLE_16(15) = '0') else SERIAL_UART_1_TX;
	SERIAL_UART_0_RX  <= SERIAL_UART_RX   when (GPIO_DOUT_ENABLE_16(15) = '0') else '1';
	SERIAL_UART_1_RX  <= SERIAL_UART_RX   when (GPIO_DOUT_ENABLE_16(15) = '1') else '1';

	-----------------------------------------------------------------
	-- Stubbing the DRAM... we will not be checking the second port...
	-----------------------------------------------------------------
	AFB_DPRAM_0_1_RESPONSE_pipe_read_req(0) <= '0';
    	AFB_DPRAM_0_1_REQUEST_pipe_write_req(0) <= '0';
    	AFB_DPRAM_0_1_REQUEST_pipe_write_data <= (others => '0');

	AFB_DPRAM_1_1_RESPONSE_pipe_read_req(0) <= '0';
    	AFB_DPRAM_1_1_REQUEST_pipe_write_req(0) <= '0';
    	AFB_DPRAM_1_1_REQUEST_pipe_write_data <= (others => '0');

	-----------------------------------------------------------------
	-- GNSS stub for now.
	-----------------------------------------------------------------
	gnss_sram_stub:
		gnss_mem
			port map 
			(
				pread => pread,
				pwrite => pwrite,
				praddr => praddr,
				pwaddr => pwaddr,
				prdata => prdata,
				pwdata => pwdata,
				pintr(0)  => GNSS_MAIN_INTERRUPT,
      				clk => clk, reset => reset_sync
			);

	mil_1553_0_sram_stub:
		afb_sram_stub
			generic map (addr_width => 8)
			port map 
			(
      				AFB_SRAM_COMMAND_PIPE_WRITE_DATA  => AFB_MIL_1553_0_REQUEST_pipe_read_data,
      				AFB_SRAM_COMMAND_PIPE_WRITE_REQ   => AFB_MIL_1553_0_REQUEST_pipe_read_ack,
      				AFB_SRAM_COMMAND_PIPE_WRITE_ACK   => AFB_MIL_1553_0_REQUEST_pipe_read_req,
      				AFB_SRAM_RESPONSE_PIPE_READ_DATA  => AFB_MIL_1553_0_RESPONSE_pipe_write_data,
      				AFB_SRAM_RESPONSE_PIPE_READ_REQ   => AFB_MIL_1553_0_RESPONSE_pipe_write_ack,
      				AFB_SRAM_RESPONSE_PIPE_READ_ACK   => AFB_MIL_1553_0_RESPONSE_pipe_write_req,
      				clk => clk, reset => reset_sync
			);

	mil_1553_1_sram_stub:
		afb_sram_stub
			generic map (addr_width => 8)
			port map 
			(
      				AFB_SRAM_COMMAND_PIPE_WRITE_DATA  => AFB_MIL_1553_1_REQUEST_pipe_read_data,
      				AFB_SRAM_COMMAND_PIPE_WRITE_REQ   => AFB_MIL_1553_1_REQUEST_pipe_read_ack,
      				AFB_SRAM_COMMAND_PIPE_WRITE_ACK   => AFB_MIL_1553_1_REQUEST_pipe_read_req,
      				AFB_SRAM_RESPONSE_PIPE_READ_DATA  => AFB_MIL_1553_1_RESPONSE_pipe_write_data,
      				AFB_SRAM_RESPONSE_PIPE_READ_REQ   => AFB_MIL_1553_1_RESPONSE_pipe_write_ack,
      				AFB_SRAM_RESPONSE_PIPE_READ_ACK   => AFB_MIL_1553_1_RESPONSE_pipe_write_req,
      				clk => clk, reset => reset_sync
			);

	-----------------------------------------------------------------
	--Watchdog timer
	-----------------------------------------------------------------
	wt_inst: watchdog_timer
		generic map (n_cycles => (1024*1024))
		port map (
				enable(0) => WATCHDOG_TIMER_ENABLE,
				intr(0)   => WATCHDOG_TIMER_INTERRUPT,
				kick(0)   => WATCHDOG_TIMER_KICK,
				clk => clk, reset => reset_sync
			);


	-----------------------------------------------------------------
	-- Xilinx hack to use flash on board.
	-----------------------------------------------------------------
	spi_connect: STARTUPE2
    		generic map(      PROG_USR => "FALSE", 
                 	SIM_CCLK_FREQ => 0.0)
    	port map (    CFGCLK => open,
                 	CFGMCLK => open,
                     	EOS => open,
                    	PREQ => open,
                     	CLK => '0',
                     	GSR => '0',
                     	GTS => '0',
               		KEYCLEARB => '0',
                    	PACK => '0',
                	USRCCLKO => spi_clk1,   -- Provide signal to output on CCLK pin 
               		USRCCLKTS => '0',       -- Enable CCLK pin  
                	USRDONEO => '1',        -- Drive DONE pin High even though tri-state
               		USRDONETS => '1' );     -- Maintain tri-state of DONE pin 

	-----------------------------------------------------------------
	-- Reset synchronizer.
	-----------------------------------------------------------------
 	process (CLK)
  	begin
    		if (CLK'event and CLK = '1') then
			reset_sync <= reset2;
			reset2 <= reset1;
			reset1 <= reset_merged;
    		end if;
       end process;
       reset_sync_n <= not reset_sync;

end structure;
