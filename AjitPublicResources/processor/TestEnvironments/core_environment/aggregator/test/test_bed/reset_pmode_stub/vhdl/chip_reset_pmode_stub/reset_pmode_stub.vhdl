library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

--
-- from the chip reset signal, generate the reset to
-- the core.  Note that the core itself has two
-- resets, the implicit asynchronous reset and the 
-- ENV_to_AJIT_reset(0) hard reset which will release synchronously.
--
entity reset_pmode_stub is
	port ( CPU_RESET, 
		DEBUG_MODE, 
		SINGLE_STEP_MODE: in std_logic_vector(0 downto 0);
		AJIT_to_ENV_processor_mode_pipe_write_data:in std_logic_vector(7 downto 0);
		AJIT_to_ENV_processor_mode_pipe_write_req:in std_logic_vector(0 downto 0);
		AJIT_to_ENV_processor_mode_pipe_write_ack : out std_logic_vector(0 downto 0);
		ENV_to_AJIT_reset: out std_logic_vector(7 downto 0);
		CPU_MODE: out std_logic_vector(1 downto 0);
		clk: in std_logic;
		reset: in std_logic);
end entity reset_pmode_stub;


architecture Behave of reset_pmode_stub is
	signal reset_d : std_logic;
	signal CPU_RESET_D: std_logic;
	signal DEBUG_MODE_D: std_logic;
	signal SINGLE_STEP_MODE_D: std_logic;
	signal counter: unsigned (1 downto 0);
	signal pmode_reg : std_logic_vector(7 downto 0);
begin
	AJIT_to_ENV_processor_mode_pipe_write_ack(0) <= '1'; 

	CPU_MODE <= pmode_reg(1 downto 0);

	ENV_to_AJIT_reset(0)  <= (CPU_RESET_d or reset_d);
	ENV_to_AJIT_reset(1)  <= DEBUG_MODE_D;
	ENV_to_AJIT_reset(2)  <= SINGLE_STEP_MODE_D;
	ENV_to_AJIT_reset(3)  <=  '0';
	ENV_to_AJIT_reset(4)  <=  '0';
	ENV_to_AJIT_reset(5)  <=  '0';
	ENV_to_AJIT_reset(6)  <=  '0';
	ENV_to_AJIT_reset(7)  <=  '0';

	-- this is about the only place on the chip 
	-- where we will use an asynchronous reset.
	process(clk, reset)
	begin
		if(reset = '1') then
			counter <= (others => '0');
		elsif(clk'event and clk = '1') then
			counter <= counter + 1;
		end if;
	end process;

	-- reset synchronizer
	process(clk,reset)
	begin
		if(reset = '1') then
			reset_d <= '1';
			DEBUG_MODE_d <= '0';
			SINGLE_STEP_MODE_D <= '0';
			CPU_RESET_D <= '0';
			pmode_reg <= (others => '0');
		elsif (clk'event and clk ='1') then
			if(counter = "11") then
				reset_d <= reset;
				DEBUG_MODE_D <= DEBUG_MODE(0);
				SINGLE_STEP_MODE_D <= SINGLE_STEP_MODE(0);
				CPU_RESET_D <= CPU_RESET(0);
			end if;
			if(AJIT_to_ENV_processor_mode_pipe_write_req(0)  = '1') then
				pmode_reg <= AJIT_to_ENV_processor_mode_pipe_write_data;
			end if;
		end if;
	end process;

end Behave;
