library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- synchronize the interrupt and so on..
-- BUS interrupt is mapped to irl 13.
entity interrupt_stub is
	port (INTR: in std_logic_vector(0 downto 0);
		ENV_to_AJIT_irl: out std_logic_vector(7 downto 0);
		clk: in std_logic;
		reset: in std_logic);
end entity interrupt_stub;


architecture Behave of interrupt_stub is
	signal INTR_d, INTR_dd : std_logic;
	signal counter: unsigned (1 downto 0);
begin

	ENV_to_AJIT_irl <= "00001101" when INTR_dd = '1' else (others => '0');
	
	process(clk, reset)
	begin
		if(clk'event and clk = '1') then
			if(reset = '1') then
				counter <= (others => '0');
			else 
				counter <= counter + 1;
			end if;
		end if;
	end process;

	process(clk, reset, counter)
	begin
		if(clk'event and clk = '1') then
		   if(reset = '1') then
			INTR_d <= '0';
			INTR_dd <= '0';
		   elsif (counter = "11") then
			INTR_d <= INTR(0);
			INTR_dd <= INTR_d;
		   end if;
		end if;
	end process;

end Behave;
