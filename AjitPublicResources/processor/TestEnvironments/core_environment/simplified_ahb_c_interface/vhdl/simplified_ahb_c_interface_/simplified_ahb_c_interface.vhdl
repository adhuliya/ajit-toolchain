-- VHDL global package produced by vc2vhdl from virtual circuit (vc) description 
library ieee;
use ieee.std_logic_1164.all;
package simplified_ahb_c_interface_global_package is -- 
  constant default_mem_pool_base_address : std_logic_vector(0 downto 0) := "0";
  component simplified_ahb_c_interface is -- 
    port (-- 
      get_simplified_ahb_command_rw : out  std_logic_vector(7 downto 0);
      get_simplified_ahb_command_transfer_size : out  std_logic_vector(7 downto 0);
      get_simplified_ahb_command_byte_address : out  std_logic_vector(63 downto 0);
      get_simplified_ahb_command_write_data : out  std_logic_vector(31 downto 0);
      get_simplified_ahb_command_tag_in: in std_logic_vector(1 downto 0);
      get_simplified_ahb_command_tag_out: out std_logic_vector(1 downto 0);
      get_simplified_ahb_command_start_req : in std_logic;
      get_simplified_ahb_command_start_ack : out std_logic;
      get_simplified_ahb_command_fin_req   : in std_logic;
      get_simplified_ahb_command_fin_ack   : out std_logic;
      send_simplified_ahb_response_err : in  std_logic_vector(7 downto 0);
      send_simplified_ahb_response_read_data : in  std_logic_vector(31 downto 0);
      send_simplified_ahb_response_tag_in: in std_logic_vector(1 downto 0);
      send_simplified_ahb_response_tag_out: out std_logic_vector(1 downto 0);
      send_simplified_ahb_response_start_req : in std_logic;
      send_simplified_ahb_response_start_ack : out std_logic;
      send_simplified_ahb_response_fin_req   : in std_logic;
      send_simplified_ahb_response_fin_ack   : out std_logic;
      clk : in std_logic;
      reset : in std_logic;
      AFB_TO_AHB_COMMAND_pipe_write_data: in std_logic_vector(72 downto 0);
      AFB_TO_AHB_COMMAND_pipe_write_req : in std_logic_vector(0 downto 0);
      AFB_TO_AHB_COMMAND_pipe_write_ack : out std_logic_vector(0 downto 0);
      AHB_TO_AFB_RESPONSE_pipe_read_data: out std_logic_vector(32 downto 0);
      AHB_TO_AFB_RESPONSE_pipe_read_req : in std_logic_vector(0 downto 0);
      AHB_TO_AFB_RESPONSE_pipe_read_ack : out std_logic_vector(0 downto 0)); -- 
    -- 
  end component;
  -- 
end package simplified_ahb_c_interface_global_package;
-- VHDL produced by vc2vhdl from virtual circuit (vc) description 
library std;
use std.standard.all;
library ieee;
use ieee.std_logic_1164.all;
library aHiR_ieee_proposed;
use aHiR_ieee_proposed.math_utility_pkg.all;
use aHiR_ieee_proposed.fixed_pkg.all;
use aHiR_ieee_proposed.float_pkg.all;
library ahir;
use ahir.memory_subsystem_package.all;
use ahir.types.all;
use ahir.subprograms.all;
use ahir.components.all;
use ahir.basecomponents.all;
use ahir.operatorpackage.all;
use ahir.floatoperatorpackage.all;
use ahir.utilities.all;
library simplified_ahb_c_interface_;
use simplified_ahb_c_interface_.simplified_ahb_c_interface_global_package.all;
entity get_simplified_ahb_command is -- 
  generic (tag_length : integer); 
  port ( -- 
    rw : out  std_logic_vector(7 downto 0);
    transfer_size : out  std_logic_vector(7 downto 0);
    byte_address : out  std_logic_vector(63 downto 0);
    write_data : out  std_logic_vector(31 downto 0);
    AFB_TO_AHB_COMMAND_pipe_read_req : out  std_logic_vector(0 downto 0);
    AFB_TO_AHB_COMMAND_pipe_read_ack : in   std_logic_vector(0 downto 0);
    AFB_TO_AHB_COMMAND_pipe_read_data : in   std_logic_vector(72 downto 0);
    tag_in: in std_logic_vector(tag_length-1 downto 0);
    tag_out: out std_logic_vector(tag_length-1 downto 0) ;
    clk : in std_logic;
    reset : in std_logic;
    start_req : in std_logic;
    start_ack : out std_logic;
    fin_req : in std_logic;
    fin_ack   : out std_logic-- 
  );
  -- 
end entity get_simplified_ahb_command;
architecture get_simplified_ahb_command_arch of get_simplified_ahb_command is -- 
  -- always true...
  signal always_true_symbol: Boolean;
  signal in_buffer_data_in, in_buffer_data_out: std_logic_vector((tag_length + 0)-1 downto 0);
  signal default_zero_sig: std_logic;
  signal in_buffer_write_req: std_logic;
  signal in_buffer_write_ack: std_logic;
  signal in_buffer_unload_req_symbol: Boolean;
  signal in_buffer_unload_ack_symbol: Boolean;
  signal out_buffer_data_in, out_buffer_data_out: std_logic_vector((tag_length + 112)-1 downto 0);
  signal out_buffer_read_req: std_logic;
  signal out_buffer_read_ack: std_logic;
  signal out_buffer_write_req_symbol: Boolean;
  signal out_buffer_write_ack_symbol: Boolean;
  signal tag_ub_out, tag_ilock_out: std_logic_vector(tag_length-1 downto 0);
  signal tag_push_req, tag_push_ack, tag_pop_req, tag_pop_ack: std_logic;
  signal tag_unload_req_symbol, tag_unload_ack_symbol, tag_write_req_symbol, tag_write_ack_symbol: Boolean;
  signal tag_ilock_write_req_symbol, tag_ilock_write_ack_symbol, tag_ilock_read_req_symbol, tag_ilock_read_ack_symbol: Boolean;
  signal start_req_sig, fin_req_sig, start_ack_sig, fin_ack_sig: std_logic; 
  signal input_sample_reenable_symbol: Boolean;
  -- input port buffer signals
  -- output port buffer signals
  signal rw_buffer :  std_logic_vector(7 downto 0);
  signal rw_update_enable: Boolean;
  signal transfer_size_buffer :  std_logic_vector(7 downto 0);
  signal transfer_size_update_enable: Boolean;
  signal byte_address_buffer :  std_logic_vector(63 downto 0);
  signal byte_address_update_enable: Boolean;
  signal write_data_buffer :  std_logic_vector(31 downto 0);
  signal write_data_update_enable: Boolean;
  signal get_simplified_ahb_command_CP_0_start: Boolean;
  signal get_simplified_ahb_command_CP_0_symbol: Boolean;
  -- volatile/operator module components. 
  -- links between control-path and data-path
  signal RPIPE_AFB_TO_AHB_COMMAND_17_inst_req_1 : boolean;
  signal RPIPE_AFB_TO_AHB_COMMAND_17_inst_req_0 : boolean;
  signal RPIPE_AFB_TO_AHB_COMMAND_17_inst_ack_0 : boolean;
  signal RPIPE_AFB_TO_AHB_COMMAND_17_inst_ack_1 : boolean;
  signal slice_26_inst_req_0 : boolean;
  signal slice_26_inst_ack_0 : boolean;
  signal slice_26_inst_req_1 : boolean;
  signal slice_26_inst_ack_1 : boolean;
  signal slice_22_inst_req_0 : boolean;
  signal slice_22_inst_ack_0 : boolean;
  signal slice_22_inst_req_1 : boolean;
  signal slice_22_inst_ack_1 : boolean;
  signal slice_31_inst_req_0 : boolean;
  signal slice_31_inst_ack_0 : boolean;
  signal slice_31_inst_req_1 : boolean;
  signal slice_31_inst_ack_1 : boolean;
  signal slice_36_inst_req_0 : boolean;
  signal slice_36_inst_ack_0 : boolean;
  signal slice_36_inst_req_1 : boolean;
  signal slice_36_inst_ack_1 : boolean;
  signal slice_40_inst_req_0 : boolean;
  signal slice_40_inst_ack_0 : boolean;
  signal slice_40_inst_req_1 : boolean;
  signal slice_40_inst_ack_1 : boolean;
  signal type_cast_44_inst_req_0 : boolean;
  signal type_cast_44_inst_ack_0 : boolean;
  signal type_cast_44_inst_req_1 : boolean;
  signal type_cast_44_inst_ack_1 : boolean;
  signal type_cast_48_inst_req_0 : boolean;
  signal type_cast_48_inst_ack_0 : boolean;
  signal type_cast_48_inst_req_1 : boolean;
  signal type_cast_48_inst_ack_1 : boolean;
  signal type_cast_52_inst_req_0 : boolean;
  signal type_cast_52_inst_ack_0 : boolean;
  signal type_cast_52_inst_req_1 : boolean;
  signal type_cast_52_inst_ack_1 : boolean;
  -- 
begin --  
  -- input handling ------------------------------------------------
  in_buffer: UnloadBuffer -- 
    generic map(name => "get_simplified_ahb_command_input_buffer", -- 
      buffer_size => 1,
      full_rate => false,
      bypass_flag => true,
      data_width => tag_length + 0) -- 
    port map(write_req => in_buffer_write_req, -- 
      write_ack => in_buffer_write_ack, 
      write_data => in_buffer_data_in,
      unload_req => in_buffer_unload_req_symbol, 
      unload_ack => in_buffer_unload_ack_symbol, 
      read_data => in_buffer_data_out,
      clk => clk, reset => reset); -- 
  in_buffer_data_in(tag_length-1 downto 0) <= tag_in;
  tag_ub_out <= in_buffer_data_out(tag_length-1 downto 0);
  in_buffer_write_req <= start_req;
  start_ack <= in_buffer_write_ack;
  in_buffer_unload_req_symbol_join: block -- 
    constant place_capacities: IntegerArray(0 to 1) := (0 => 1,1 => 1);
    constant place_markings: IntegerArray(0 to 1)  := (0 => 1,1 => 1);
    constant place_delays: IntegerArray(0 to 1) := (0 => 0,1 => 1);
    constant joinName: string(1 to 32) := "in_buffer_unload_req_symbol_join"; 
    signal preds: BooleanArray(1 to 2); -- 
  begin -- 
    preds <= in_buffer_unload_ack_symbol & input_sample_reenable_symbol;
    gj_in_buffer_unload_req_symbol_join : generic_join generic map(name => joinName, place_capacities => place_capacities, place_markings => place_markings, place_delays => place_delays) -- 
      port map(preds => preds, symbol_out => in_buffer_unload_req_symbol, clk => clk, reset => reset); --
  end block;
  -- join of all unload_ack_symbols.. used to trigger CP.
  get_simplified_ahb_command_CP_0_start <= in_buffer_unload_ack_symbol;
  -- output handling  -------------------------------------------------------
  out_buffer: ReceiveBuffer -- 
    generic map(name => "get_simplified_ahb_command_out_buffer", -- 
      buffer_size => 1,
      full_rate => false,
      data_width => tag_length + 112) --
    port map(write_req => out_buffer_write_req_symbol, -- 
      write_ack => out_buffer_write_ack_symbol, 
      write_data => out_buffer_data_in,
      read_req => out_buffer_read_req, 
      read_ack => out_buffer_read_ack, 
      read_data => out_buffer_data_out,
      clk => clk, reset => reset); -- 
  out_buffer_data_in(7 downto 0) <= rw_buffer;
  rw <= out_buffer_data_out(7 downto 0);
  out_buffer_data_in(15 downto 8) <= transfer_size_buffer;
  transfer_size <= out_buffer_data_out(15 downto 8);
  out_buffer_data_in(79 downto 16) <= byte_address_buffer;
  byte_address <= out_buffer_data_out(79 downto 16);
  out_buffer_data_in(111 downto 80) <= write_data_buffer;
  write_data <= out_buffer_data_out(111 downto 80);
  out_buffer_data_in(tag_length + 111 downto 112) <= tag_ilock_out;
  tag_out <= out_buffer_data_out(tag_length + 111 downto 112);
  out_buffer_write_req_symbol_join: block -- 
    constant place_capacities: IntegerArray(0 to 2) := (0 => 1,1 => 1,2 => 1);
    constant place_markings: IntegerArray(0 to 2)  := (0 => 0,1 => 1,2 => 0);
    constant place_delays: IntegerArray(0 to 2) := (0 => 0,1 => 1,2 => 0);
    constant joinName: string(1 to 32) := "out_buffer_write_req_symbol_join"; 
    signal preds: BooleanArray(1 to 3); -- 
  begin -- 
    preds <= get_simplified_ahb_command_CP_0_symbol & out_buffer_write_ack_symbol & tag_ilock_read_ack_symbol;
    gj_out_buffer_write_req_symbol_join : generic_join generic map(name => joinName, place_capacities => place_capacities, place_markings => place_markings, place_delays => place_delays) -- 
      port map(preds => preds, symbol_out => out_buffer_write_req_symbol, clk => clk, reset => reset); --
  end block;
  -- write-to output-buffer produces  reenable input sampling
  input_sample_reenable_symbol <= out_buffer_write_ack_symbol;
  -- fin-req/ack level protocol..
  out_buffer_read_req <= fin_req;
  fin_ack <= out_buffer_read_ack;
  ----- tag-queue --------------------------------------------------
  -- interlock buffer for TAG.. to provide required buffering.
  tagIlock: InterlockBuffer -- 
    generic map(name => "tag-interlock-buffer", -- 
      buffer_size => 1,
      bypass_flag => false,
      in_data_width => tag_length,
      out_data_width => tag_length) -- 
    port map(write_req => tag_ilock_write_req_symbol, -- 
      write_ack => tag_ilock_write_ack_symbol, 
      write_data => tag_ub_out,
      read_req => tag_ilock_read_req_symbol, 
      read_ack => tag_ilock_read_ack_symbol, 
      read_data => tag_ilock_out, 
      clk => clk, reset => reset); -- 
  -- tag ilock-buffer control logic. 
  tag_ilock_write_req_symbol_join: block -- 
    constant place_capacities: IntegerArray(0 to 1) := (0 => 1,1 => 1);
    constant place_markings: IntegerArray(0 to 1)  := (0 => 0,1 => 1);
    constant place_delays: IntegerArray(0 to 1) := (0 => 0,1 => 1);
    constant joinName: string(1 to 31) := "tag_ilock_write_req_symbol_join"; 
    signal preds: BooleanArray(1 to 2); -- 
  begin -- 
    preds <= get_simplified_ahb_command_CP_0_start & tag_ilock_write_ack_symbol;
    gj_tag_ilock_write_req_symbol_join : generic_join generic map(name => joinName, place_capacities => place_capacities, place_markings => place_markings, place_delays => place_delays) -- 
      port map(preds => preds, symbol_out => tag_ilock_write_req_symbol, clk => clk, reset => reset); --
  end block;
  tag_ilock_read_req_symbol_join: block -- 
    constant place_capacities: IntegerArray(0 to 2) := (0 => 1,1 => 1,2 => 1);
    constant place_markings: IntegerArray(0 to 2)  := (0 => 0,1 => 1,2 => 1);
    constant place_delays: IntegerArray(0 to 2) := (0 => 0,1 => 0,2 => 0);
    constant joinName: string(1 to 30) := "tag_ilock_read_req_symbol_join"; 
    signal preds: BooleanArray(1 to 3); -- 
  begin -- 
    preds <= get_simplified_ahb_command_CP_0_start & tag_ilock_read_ack_symbol & out_buffer_write_ack_symbol;
    gj_tag_ilock_read_req_symbol_join : generic_join generic map(name => joinName, place_capacities => place_capacities, place_markings => place_markings, place_delays => place_delays) -- 
      port map(preds => preds, symbol_out => tag_ilock_read_req_symbol, clk => clk, reset => reset); --
  end block;
  -- the control path --------------------------------------------------
  always_true_symbol <= true; 
  default_zero_sig <= '0';
  get_simplified_ahb_command_CP_0: Block -- control-path 
    signal get_simplified_ahb_command_CP_0_elements: BooleanArray(19 downto 0);
    -- 
  begin -- 
    get_simplified_ahb_command_CP_0_elements(0) <= get_simplified_ahb_command_CP_0_start;
    get_simplified_ahb_command_CP_0_symbol <= get_simplified_ahb_command_CP_0_elements(19);
    -- CP-element group 0:  transition  output  bypass 
    -- CP-element group 0: predecessors 
    -- CP-element group 0: successors 
    -- CP-element group 0: 	1 
    -- CP-element group 0:  members (5) 
      -- CP-element group 0: 	 $entry
      -- CP-element group 0: 	 assign_stmt_18/$entry
      -- CP-element group 0: 	 assign_stmt_18/RPIPE_AFB_TO_AHB_COMMAND_17_sample_start_
      -- CP-element group 0: 	 assign_stmt_18/RPIPE_AFB_TO_AHB_COMMAND_17_Sample/$entry
      -- CP-element group 0: 	 assign_stmt_18/RPIPE_AFB_TO_AHB_COMMAND_17_Sample/rr
      -- 
    rr_13_symbol_link_to_dp: control_delay_element -- 
      generic map(name => " rr_13_symbol_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => get_simplified_ahb_command_CP_0_elements(0), ack => RPIPE_AFB_TO_AHB_COMMAND_17_inst_req_0); -- 
    -- CP-element group 1:  transition  input  output  bypass 
    -- CP-element group 1: predecessors 
    -- CP-element group 1: 	0 
    -- CP-element group 1: successors 
    -- CP-element group 1: 	2 
    -- CP-element group 1:  members (6) 
      -- CP-element group 1: 	 assign_stmt_18/RPIPE_AFB_TO_AHB_COMMAND_17_Update/cr
      -- CP-element group 1: 	 assign_stmt_18/RPIPE_AFB_TO_AHB_COMMAND_17_sample_completed_
      -- CP-element group 1: 	 assign_stmt_18/RPIPE_AFB_TO_AHB_COMMAND_17_update_start_
      -- CP-element group 1: 	 assign_stmt_18/RPIPE_AFB_TO_AHB_COMMAND_17_Sample/$exit
      -- CP-element group 1: 	 assign_stmt_18/RPIPE_AFB_TO_AHB_COMMAND_17_Sample/ra
      -- CP-element group 1: 	 assign_stmt_18/RPIPE_AFB_TO_AHB_COMMAND_17_Update/$entry
      -- 
    ra_14_symbol_link_from_dp: control_delay_element -- 
      generic map(name => " 1_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => RPIPE_AFB_TO_AHB_COMMAND_17_inst_ack_0, ack => get_simplified_ahb_command_CP_0_elements(1)); -- 
    cr_18_symbol_link_to_dp: control_delay_element -- 
      generic map(name => " cr_18_symbol_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => get_simplified_ahb_command_CP_0_elements(1), ack => RPIPE_AFB_TO_AHB_COMMAND_17_inst_req_1); -- 
    -- CP-element group 2:  fork  transition  input  output  bypass 
    -- CP-element group 2: predecessors 
    -- CP-element group 2: 	1 
    -- CP-element group 2: successors 
    -- CP-element group 2: 	5 
    -- CP-element group 2: 	16 
    -- CP-element group 2: 	18 
    -- CP-element group 2: 	11 
    -- CP-element group 2: 	3 
    -- CP-element group 2: 	12 
    -- CP-element group 2: 	6 
    -- CP-element group 2: 	4 
    -- CP-element group 2: 	10 
    -- CP-element group 2: 	9 
    -- CP-element group 2: 	8 
    -- CP-element group 2: 	7 
    -- CP-element group 2: 	14 
    -- CP-element group 2:  members (44) 
      -- CP-element group 2: 	 assign_stmt_18/$exit
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/$entry
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_22_sample_start_
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_22_update_start_
      -- CP-element group 2: 	 assign_stmt_18/RPIPE_AFB_TO_AHB_COMMAND_17_update_completed_
      -- CP-element group 2: 	 assign_stmt_18/RPIPE_AFB_TO_AHB_COMMAND_17_Update/$exit
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_26_Sample/$entry
      -- CP-element group 2: 	 assign_stmt_18/RPIPE_AFB_TO_AHB_COMMAND_17_Update/ca
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_26_sample_start_
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_26_update_start_
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/type_cast_44_update_start_
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_26_Sample/rr
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_26_Update/$entry
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_26_Update/cr
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_22_Sample/$entry
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_22_Sample/rr
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_22_Update/$entry
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_22_Update/cr
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_31_sample_start_
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_31_update_start_
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_31_Sample/$entry
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_31_Sample/rr
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_31_Update/$entry
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_31_Update/cr
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_36_sample_start_
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_36_update_start_
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_36_Sample/$entry
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_36_Sample/rr
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_36_Update/$entry
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_36_Update/cr
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_40_sample_start_
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_40_update_start_
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_40_Sample/$entry
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_40_Sample/rr
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_40_Update/$entry
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/slice_40_Update/cr
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/type_cast_44_Update/$entry
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/type_cast_44_Update/cr
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/type_cast_48_update_start_
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/type_cast_48_Update/$entry
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/type_cast_48_Update/cr
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/type_cast_52_update_start_
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/type_cast_52_Update/$entry
      -- CP-element group 2: 	 assign_stmt_23_to_assign_stmt_53/type_cast_52_Update/cr
      -- 
    ca_19_symbol_link_from_dp: control_delay_element -- 
      generic map(name => " 2_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => RPIPE_AFB_TO_AHB_COMMAND_17_inst_ack_1, ack => get_simplified_ahb_command_CP_0_elements(2)); -- 
    cr_133_symbol_link_to_dp: control_delay_element -- 
      generic map(name => " cr_133_symbol_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => get_simplified_ahb_command_CP_0_elements(2), ack => type_cast_52_inst_req_1); -- 
    cr_35_symbol_link_to_dp: control_delay_element -- 
      generic map(name => " cr_35_symbol_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => get_simplified_ahb_command_CP_0_elements(2), ack => slice_22_inst_req_1); -- 
    cr_119_symbol_link_to_dp: control_delay_element -- 
      generic map(name => " cr_119_symbol_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => get_simplified_ahb_command_CP_0_elements(2), ack => type_cast_48_inst_req_1); -- 
    cr_63_symbol_link_to_dp: control_delay_element -- 
      generic map(name => " cr_63_symbol_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => get_simplified_ahb_command_CP_0_elements(2), ack => slice_31_inst_req_1); -- 
    rr_58_symbol_link_to_dp: control_delay_element -- 
      generic map(name => " rr_58_symbol_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => get_simplified_ahb_command_CP_0_elements(2), ack => slice_31_inst_req_0); -- 
    cr_49_symbol_link_to_dp: control_delay_element -- 
      generic map(name => " cr_49_symbol_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => get_simplified_ahb_command_CP_0_elements(2), ack => slice_26_inst_req_1); -- 
    cr_91_symbol_link_to_dp: control_delay_element -- 
      generic map(name => " cr_91_symbol_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => get_simplified_ahb_command_CP_0_elements(2), ack => slice_40_inst_req_1); -- 
    rr_86_symbol_link_to_dp: control_delay_element -- 
      generic map(name => " rr_86_symbol_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => get_simplified_ahb_command_CP_0_elements(2), ack => slice_40_inst_req_0); -- 
    cr_77_symbol_link_to_dp: control_delay_element -- 
      generic map(name => " cr_77_symbol_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => get_simplified_ahb_command_CP_0_elements(2), ack => slice_36_inst_req_1); -- 
    cr_105_symbol_link_to_dp: control_delay_element -- 
      generic map(name => " cr_105_symbol_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => get_simplified_ahb_command_CP_0_elements(2), ack => type_cast_44_inst_req_1); -- 
    rr_44_symbol_link_to_dp: control_delay_element -- 
      generic map(name => " rr_44_symbol_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => get_simplified_ahb_command_CP_0_elements(2), ack => slice_26_inst_req_0); -- 
    rr_72_symbol_link_to_dp: control_delay_element -- 
      generic map(name => " rr_72_symbol_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => get_simplified_ahb_command_CP_0_elements(2), ack => slice_36_inst_req_0); -- 
    rr_30_symbol_link_to_dp: control_delay_element -- 
      generic map(name => " rr_30_symbol_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => get_simplified_ahb_command_CP_0_elements(2), ack => slice_22_inst_req_0); -- 
    -- CP-element group 3:  transition  input  bypass 
    -- CP-element group 3: predecessors 
    -- CP-element group 3: 	2 
    -- CP-element group 3: successors 
    -- CP-element group 3:  members (3) 
      -- CP-element group 3: 	 assign_stmt_23_to_assign_stmt_53/slice_22_sample_completed_
      -- CP-element group 3: 	 assign_stmt_23_to_assign_stmt_53/slice_22_Sample/$exit
      -- CP-element group 3: 	 assign_stmt_23_to_assign_stmt_53/slice_22_Sample/ra
      -- 
    ra_31_symbol_link_from_dp: control_delay_element -- 
      generic map(name => " 3_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => slice_22_inst_ack_0, ack => get_simplified_ahb_command_CP_0_elements(3)); -- 
    -- CP-element group 4:  transition  input  bypass 
    -- CP-element group 4: predecessors 
    -- CP-element group 4: 	2 
    -- CP-element group 4: successors 
    -- CP-element group 4: 	19 
    -- CP-element group 4:  members (3) 
      -- CP-element group 4: 	 assign_stmt_23_to_assign_stmt_53/slice_22_update_completed_
      -- CP-element group 4: 	 assign_stmt_23_to_assign_stmt_53/slice_22_Update/$exit
      -- CP-element group 4: 	 assign_stmt_23_to_assign_stmt_53/slice_22_Update/ca
      -- 
    ca_36_symbol_link_from_dp: control_delay_element -- 
      generic map(name => " 4_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => slice_22_inst_ack_1, ack => get_simplified_ahb_command_CP_0_elements(4)); -- 
    -- CP-element group 5:  transition  input  bypass 
    -- CP-element group 5: predecessors 
    -- CP-element group 5: 	2 
    -- CP-element group 5: successors 
    -- CP-element group 5:  members (3) 
      -- CP-element group 5: 	 assign_stmt_23_to_assign_stmt_53/slice_26_Sample/$exit
      -- CP-element group 5: 	 assign_stmt_23_to_assign_stmt_53/slice_26_sample_completed_
      -- CP-element group 5: 	 assign_stmt_23_to_assign_stmt_53/slice_26_Sample/ra
      -- 
    ra_45_symbol_link_from_dp: control_delay_element -- 
      generic map(name => " 5_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => slice_26_inst_ack_0, ack => get_simplified_ahb_command_CP_0_elements(5)); -- 
    -- CP-element group 6:  transition  input  output  bypass 
    -- CP-element group 6: predecessors 
    -- CP-element group 6: 	2 
    -- CP-element group 6: successors 
    -- CP-element group 6: 	13 
    -- CP-element group 6:  members (6) 
      -- CP-element group 6: 	 assign_stmt_23_to_assign_stmt_53/slice_26_update_completed_
      -- CP-element group 6: 	 assign_stmt_23_to_assign_stmt_53/type_cast_44_sample_start_
      -- CP-element group 6: 	 assign_stmt_23_to_assign_stmt_53/slice_26_Update/$exit
      -- CP-element group 6: 	 assign_stmt_23_to_assign_stmt_53/slice_26_Update/ca
      -- CP-element group 6: 	 assign_stmt_23_to_assign_stmt_53/type_cast_44_Sample/$entry
      -- CP-element group 6: 	 assign_stmt_23_to_assign_stmt_53/type_cast_44_Sample/rr
      -- 
    ca_50_symbol_link_from_dp: control_delay_element -- 
      generic map(name => " 6_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => slice_26_inst_ack_1, ack => get_simplified_ahb_command_CP_0_elements(6)); -- 
    rr_100_symbol_link_to_dp: control_delay_element -- 
      generic map(name => " rr_100_symbol_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => get_simplified_ahb_command_CP_0_elements(6), ack => type_cast_44_inst_req_0); -- 
    -- CP-element group 7:  transition  input  bypass 
    -- CP-element group 7: predecessors 
    -- CP-element group 7: 	2 
    -- CP-element group 7: successors 
    -- CP-element group 7:  members (3) 
      -- CP-element group 7: 	 assign_stmt_23_to_assign_stmt_53/slice_31_sample_completed_
      -- CP-element group 7: 	 assign_stmt_23_to_assign_stmt_53/slice_31_Sample/$exit
      -- CP-element group 7: 	 assign_stmt_23_to_assign_stmt_53/slice_31_Sample/ra
      -- 
    ra_59_symbol_link_from_dp: control_delay_element -- 
      generic map(name => " 7_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => slice_31_inst_ack_0, ack => get_simplified_ahb_command_CP_0_elements(7)); -- 
    -- CP-element group 8:  transition  input  output  bypass 
    -- CP-element group 8: predecessors 
    -- CP-element group 8: 	2 
    -- CP-element group 8: successors 
    -- CP-element group 8: 	15 
    -- CP-element group 8:  members (6) 
      -- CP-element group 8: 	 assign_stmt_23_to_assign_stmt_53/slice_31_update_completed_
      -- CP-element group 8: 	 assign_stmt_23_to_assign_stmt_53/slice_31_Update/$exit
      -- CP-element group 8: 	 assign_stmt_23_to_assign_stmt_53/slice_31_Update/ca
      -- CP-element group 8: 	 assign_stmt_23_to_assign_stmt_53/type_cast_48_sample_start_
      -- CP-element group 8: 	 assign_stmt_23_to_assign_stmt_53/type_cast_48_Sample/$entry
      -- CP-element group 8: 	 assign_stmt_23_to_assign_stmt_53/type_cast_48_Sample/rr
      -- 
    ca_64_symbol_link_from_dp: control_delay_element -- 
      generic map(name => " 8_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => slice_31_inst_ack_1, ack => get_simplified_ahb_command_CP_0_elements(8)); -- 
    rr_114_symbol_link_to_dp: control_delay_element -- 
      generic map(name => " rr_114_symbol_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => get_simplified_ahb_command_CP_0_elements(8), ack => type_cast_48_inst_req_0); -- 
    -- CP-element group 9:  transition  input  bypass 
    -- CP-element group 9: predecessors 
    -- CP-element group 9: 	2 
    -- CP-element group 9: successors 
    -- CP-element group 9:  members (3) 
      -- CP-element group 9: 	 assign_stmt_23_to_assign_stmt_53/slice_36_sample_completed_
      -- CP-element group 9: 	 assign_stmt_23_to_assign_stmt_53/slice_36_Sample/$exit
      -- CP-element group 9: 	 assign_stmt_23_to_assign_stmt_53/slice_36_Sample/ra
      -- 
    ra_73_symbol_link_from_dp: control_delay_element -- 
      generic map(name => " 9_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => slice_36_inst_ack_0, ack => get_simplified_ahb_command_CP_0_elements(9)); -- 
    -- CP-element group 10:  transition  input  output  bypass 
    -- CP-element group 10: predecessors 
    -- CP-element group 10: 	2 
    -- CP-element group 10: successors 
    -- CP-element group 10: 	17 
    -- CP-element group 10:  members (6) 
      -- CP-element group 10: 	 assign_stmt_23_to_assign_stmt_53/slice_36_update_completed_
      -- CP-element group 10: 	 assign_stmt_23_to_assign_stmt_53/slice_36_Update/$exit
      -- CP-element group 10: 	 assign_stmt_23_to_assign_stmt_53/slice_36_Update/ca
      -- CP-element group 10: 	 assign_stmt_23_to_assign_stmt_53/type_cast_52_sample_start_
      -- CP-element group 10: 	 assign_stmt_23_to_assign_stmt_53/type_cast_52_Sample/$entry
      -- CP-element group 10: 	 assign_stmt_23_to_assign_stmt_53/type_cast_52_Sample/rr
      -- 
    ca_78_symbol_link_from_dp: control_delay_element -- 
      generic map(name => " 10_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => slice_36_inst_ack_1, ack => get_simplified_ahb_command_CP_0_elements(10)); -- 
    rr_128_symbol_link_to_dp: control_delay_element -- 
      generic map(name => " rr_128_symbol_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => get_simplified_ahb_command_CP_0_elements(10), ack => type_cast_52_inst_req_0); -- 
    -- CP-element group 11:  transition  input  bypass 
    -- CP-element group 11: predecessors 
    -- CP-element group 11: 	2 
    -- CP-element group 11: successors 
    -- CP-element group 11:  members (3) 
      -- CP-element group 11: 	 assign_stmt_23_to_assign_stmt_53/slice_40_sample_completed_
      -- CP-element group 11: 	 assign_stmt_23_to_assign_stmt_53/slice_40_Sample/$exit
      -- CP-element group 11: 	 assign_stmt_23_to_assign_stmt_53/slice_40_Sample/ra
      -- 
    ra_87_symbol_link_from_dp: control_delay_element -- 
      generic map(name => " 11_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => slice_40_inst_ack_0, ack => get_simplified_ahb_command_CP_0_elements(11)); -- 
    -- CP-element group 12:  transition  input  bypass 
    -- CP-element group 12: predecessors 
    -- CP-element group 12: 	2 
    -- CP-element group 12: successors 
    -- CP-element group 12: 	19 
    -- CP-element group 12:  members (3) 
      -- CP-element group 12: 	 assign_stmt_23_to_assign_stmt_53/slice_40_update_completed_
      -- CP-element group 12: 	 assign_stmt_23_to_assign_stmt_53/slice_40_Update/$exit
      -- CP-element group 12: 	 assign_stmt_23_to_assign_stmt_53/slice_40_Update/ca
      -- 
    ca_92_symbol_link_from_dp: control_delay_element -- 
      generic map(name => " 12_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => slice_40_inst_ack_1, ack => get_simplified_ahb_command_CP_0_elements(12)); -- 
    -- CP-element group 13:  transition  input  bypass 
    -- CP-element group 13: predecessors 
    -- CP-element group 13: 	6 
    -- CP-element group 13: successors 
    -- CP-element group 13:  members (3) 
      -- CP-element group 13: 	 assign_stmt_23_to_assign_stmt_53/type_cast_44_sample_completed_
      -- CP-element group 13: 	 assign_stmt_23_to_assign_stmt_53/type_cast_44_Sample/$exit
      -- CP-element group 13: 	 assign_stmt_23_to_assign_stmt_53/type_cast_44_Sample/ra
      -- 
    ra_101_symbol_link_from_dp: control_delay_element -- 
      generic map(name => " 13_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => type_cast_44_inst_ack_0, ack => get_simplified_ahb_command_CP_0_elements(13)); -- 
    -- CP-element group 14:  transition  input  bypass 
    -- CP-element group 14: predecessors 
    -- CP-element group 14: 	2 
    -- CP-element group 14: successors 
    -- CP-element group 14: 	19 
    -- CP-element group 14:  members (3) 
      -- CP-element group 14: 	 assign_stmt_23_to_assign_stmt_53/type_cast_44_update_completed_
      -- CP-element group 14: 	 assign_stmt_23_to_assign_stmt_53/type_cast_44_Update/$exit
      -- CP-element group 14: 	 assign_stmt_23_to_assign_stmt_53/type_cast_44_Update/ca
      -- 
    ca_106_symbol_link_from_dp: control_delay_element -- 
      generic map(name => " 14_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => type_cast_44_inst_ack_1, ack => get_simplified_ahb_command_CP_0_elements(14)); -- 
    -- CP-element group 15:  transition  input  bypass 
    -- CP-element group 15: predecessors 
    -- CP-element group 15: 	8 
    -- CP-element group 15: successors 
    -- CP-element group 15:  members (3) 
      -- CP-element group 15: 	 assign_stmt_23_to_assign_stmt_53/type_cast_48_sample_completed_
      -- CP-element group 15: 	 assign_stmt_23_to_assign_stmt_53/type_cast_48_Sample/$exit
      -- CP-element group 15: 	 assign_stmt_23_to_assign_stmt_53/type_cast_48_Sample/ra
      -- 
    ra_115_symbol_link_from_dp: control_delay_element -- 
      generic map(name => " 15_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => type_cast_48_inst_ack_0, ack => get_simplified_ahb_command_CP_0_elements(15)); -- 
    -- CP-element group 16:  transition  input  bypass 
    -- CP-element group 16: predecessors 
    -- CP-element group 16: 	2 
    -- CP-element group 16: successors 
    -- CP-element group 16: 	19 
    -- CP-element group 16:  members (3) 
      -- CP-element group 16: 	 assign_stmt_23_to_assign_stmt_53/type_cast_48_update_completed_
      -- CP-element group 16: 	 assign_stmt_23_to_assign_stmt_53/type_cast_48_Update/$exit
      -- CP-element group 16: 	 assign_stmt_23_to_assign_stmt_53/type_cast_48_Update/ca
      -- 
    ca_120_symbol_link_from_dp: control_delay_element -- 
      generic map(name => " 16_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => type_cast_48_inst_ack_1, ack => get_simplified_ahb_command_CP_0_elements(16)); -- 
    -- CP-element group 17:  transition  input  bypass 
    -- CP-element group 17: predecessors 
    -- CP-element group 17: 	10 
    -- CP-element group 17: successors 
    -- CP-element group 17:  members (3) 
      -- CP-element group 17: 	 assign_stmt_23_to_assign_stmt_53/type_cast_52_sample_completed_
      -- CP-element group 17: 	 assign_stmt_23_to_assign_stmt_53/type_cast_52_Sample/$exit
      -- CP-element group 17: 	 assign_stmt_23_to_assign_stmt_53/type_cast_52_Sample/ra
      -- 
    ra_129_symbol_link_from_dp: control_delay_element -- 
      generic map(name => " 17_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => type_cast_52_inst_ack_0, ack => get_simplified_ahb_command_CP_0_elements(17)); -- 
    -- CP-element group 18:  transition  input  bypass 
    -- CP-element group 18: predecessors 
    -- CP-element group 18: 	2 
    -- CP-element group 18: successors 
    -- CP-element group 18: 	19 
    -- CP-element group 18:  members (3) 
      -- CP-element group 18: 	 assign_stmt_23_to_assign_stmt_53/type_cast_52_update_completed_
      -- CP-element group 18: 	 assign_stmt_23_to_assign_stmt_53/type_cast_52_Update/$exit
      -- CP-element group 18: 	 assign_stmt_23_to_assign_stmt_53/type_cast_52_Update/ca
      -- 
    ca_134_symbol_link_from_dp: control_delay_element -- 
      generic map(name => " 18_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => type_cast_52_inst_ack_1, ack => get_simplified_ahb_command_CP_0_elements(18)); -- 
    -- CP-element group 19:  join  transition  bypass 
    -- CP-element group 19: predecessors 
    -- CP-element group 19: 	16 
    -- CP-element group 19: 	18 
    -- CP-element group 19: 	12 
    -- CP-element group 19: 	4 
    -- CP-element group 19: 	14 
    -- CP-element group 19: successors 
    -- CP-element group 19:  members (2) 
      -- CP-element group 19: 	 $exit
      -- CP-element group 19: 	 assign_stmt_23_to_assign_stmt_53/$exit
      -- 
    get_simplified_ahb_command_cp_element_group_19: block -- 
      constant place_capacities: IntegerArray(0 to 4) := (0 => 1,1 => 1,2 => 1,3 => 1,4 => 1);
      constant place_markings: IntegerArray(0 to 4)  := (0 => 0,1 => 0,2 => 0,3 => 0,4 => 0);
      constant place_delays: IntegerArray(0 to 4) := (0 => 0,1 => 0,2 => 0,3 => 0,4 => 0);
      constant joinName: string(1 to 46) := "get_simplified_ahb_command_cp_element_group_19"; 
      signal preds: BooleanArray(1 to 5); -- 
    begin -- 
      preds <= get_simplified_ahb_command_CP_0_elements(16) & get_simplified_ahb_command_CP_0_elements(18) & get_simplified_ahb_command_CP_0_elements(12) & get_simplified_ahb_command_CP_0_elements(4) & get_simplified_ahb_command_CP_0_elements(14);
      gj_get_simplified_ahb_command_cp_element_group_19 : generic_join generic map(name => joinName, place_capacities => place_capacities, place_markings => place_markings, place_delays => place_delays) -- 
        port map(preds => preds, symbol_out => get_simplified_ahb_command_CP_0_elements(19), clk => clk, reset => reset); --
    end block;
    --  hookup: inputs to control-path 
    -- hookup: output from control-path 
    -- 
  end Block; -- control-path
  -- the data path
  data_path: Block -- 
    signal addr_36_37 : std_logic_vector(35 downto 0);
    signal command_18 : std_logic_vector(72 downto 0);
    signal lock_bus_1_23 : std_logic_vector(0 downto 0);
    signal rw_1_27 : std_logic_vector(0 downto 0);
    signal transfer_size_1_32 : std_logic_vector(2 downto 0);
    -- 
  begin -- 
    slice_22_inst_block : block -- 
      signal sample_req, sample_ack, update_req, update_ack: BooleanArray(0 downto 0); 
      -- 
    begin -- 
      sample_req(0) <= slice_22_inst_req_0;
      slice_22_inst_ack_0<= sample_ack(0);
      update_req(0) <= slice_22_inst_req_1;
      slice_22_inst_ack_1<= update_ack(0);
      slice_22_inst: SliceSplitProtocol generic map(name => "slice_22_inst", in_data_width => 73, high_index => 72, low_index => 72, buffering => 1, flow_through => false,  full_rate => false) -- 
        port map( din => command_18, dout => lock_bus_1_23, sample_req => sample_req(0) , sample_ack => sample_ack(0) , update_req => update_req(0) , update_ack => update_ack(0) , clk => clk, reset => reset); -- 
      -- 
    end block;
    slice_26_inst_block : block -- 
      signal sample_req, sample_ack, update_req, update_ack: BooleanArray(0 downto 0); 
      -- 
    begin -- 
      sample_req(0) <= slice_26_inst_req_0;
      slice_26_inst_ack_0<= sample_ack(0);
      update_req(0) <= slice_26_inst_req_1;
      slice_26_inst_ack_1<= update_ack(0);
      slice_26_inst: SliceSplitProtocol generic map(name => "slice_26_inst", in_data_width => 73, high_index => 71, low_index => 71, buffering => 1, flow_through => false,  full_rate => false) -- 
        port map( din => command_18, dout => rw_1_27, sample_req => sample_req(0) , sample_ack => sample_ack(0) , update_req => update_req(0) , update_ack => update_ack(0) , clk => clk, reset => reset); -- 
      -- 
    end block;
    slice_31_inst_block : block -- 
      signal sample_req, sample_ack, update_req, update_ack: BooleanArray(0 downto 0); 
      -- 
    begin -- 
      sample_req(0) <= slice_31_inst_req_0;
      slice_31_inst_ack_0<= sample_ack(0);
      update_req(0) <= slice_31_inst_req_1;
      slice_31_inst_ack_1<= update_ack(0);
      slice_31_inst: SliceSplitProtocol generic map(name => "slice_31_inst", in_data_width => 73, high_index => 70, low_index => 68, buffering => 1, flow_through => false,  full_rate => false) -- 
        port map( din => command_18, dout => transfer_size_1_32, sample_req => sample_req(0) , sample_ack => sample_ack(0) , update_req => update_req(0) , update_ack => update_ack(0) , clk => clk, reset => reset); -- 
      -- 
    end block;
    slice_36_inst_block : block -- 
      signal sample_req, sample_ack, update_req, update_ack: BooleanArray(0 downto 0); 
      -- 
    begin -- 
      sample_req(0) <= slice_36_inst_req_0;
      slice_36_inst_ack_0<= sample_ack(0);
      update_req(0) <= slice_36_inst_req_1;
      slice_36_inst_ack_1<= update_ack(0);
      slice_36_inst: SliceSplitProtocol generic map(name => "slice_36_inst", in_data_width => 73, high_index => 67, low_index => 32, buffering => 1, flow_through => false,  full_rate => false) -- 
        port map( din => command_18, dout => addr_36_37, sample_req => sample_req(0) , sample_ack => sample_ack(0) , update_req => update_req(0) , update_ack => update_ack(0) , clk => clk, reset => reset); -- 
      -- 
    end block;
    slice_40_inst_block : block -- 
      signal sample_req, sample_ack, update_req, update_ack: BooleanArray(0 downto 0); 
      -- 
    begin -- 
      sample_req(0) <= slice_40_inst_req_0;
      slice_40_inst_ack_0<= sample_ack(0);
      update_req(0) <= slice_40_inst_req_1;
      slice_40_inst_ack_1<= update_ack(0);
      slice_40_inst: SliceSplitProtocol generic map(name => "slice_40_inst", in_data_width => 73, high_index => 31, low_index => 0, buffering => 1, flow_through => false,  full_rate => false) -- 
        port map( din => command_18, dout => write_data_buffer, sample_req => sample_req(0) , sample_ack => sample_ack(0) , update_req => update_req(0) , update_ack => update_ack(0) , clk => clk, reset => reset); -- 
      -- 
    end block;
    type_cast_44_inst_block: block -- 
      signal wreq, wack, rreq, rack: BooleanArray(0 downto 0); 
      -- 
    begin -- 
      wreq(0) <= type_cast_44_inst_req_0;
      type_cast_44_inst_ack_0<= wack(0);
      rreq(0) <= type_cast_44_inst_req_1;
      type_cast_44_inst_ack_1<= rack(0);
      type_cast_44_inst : InterlockBuffer generic map ( -- 
        name => "type_cast_44_inst",
        buffer_size => 1,
        flow_through =>  false ,
        full_rate =>  false ,
        in_data_width => 1,
        out_data_width => 8,
        bypass_flag => true 
        -- 
      )port map ( -- 
        write_req => wreq(0), 
        write_ack => wack(0), 
        write_data => rw_1_27,
        read_req => rreq(0),  
        read_ack => rack(0), 
        read_data => rw_buffer,
        clk => clk, reset => reset
        -- 
      );
      end block; -- 
    type_cast_48_inst_block: block -- 
      signal wreq, wack, rreq, rack: BooleanArray(0 downto 0); 
      -- 
    begin -- 
      wreq(0) <= type_cast_48_inst_req_0;
      type_cast_48_inst_ack_0<= wack(0);
      rreq(0) <= type_cast_48_inst_req_1;
      type_cast_48_inst_ack_1<= rack(0);
      type_cast_48_inst : InterlockBuffer generic map ( -- 
        name => "type_cast_48_inst",
        buffer_size => 1,
        flow_through =>  false ,
        full_rate =>  false ,
        in_data_width => 3,
        out_data_width => 8,
        bypass_flag => true 
        -- 
      )port map ( -- 
        write_req => wreq(0), 
        write_ack => wack(0), 
        write_data => transfer_size_1_32,
        read_req => rreq(0),  
        read_ack => rack(0), 
        read_data => transfer_size_buffer,
        clk => clk, reset => reset
        -- 
      );
      end block; -- 
    type_cast_52_inst_block: block -- 
      signal wreq, wack, rreq, rack: BooleanArray(0 downto 0); 
      -- 
    begin -- 
      wreq(0) <= type_cast_52_inst_req_0;
      type_cast_52_inst_ack_0<= wack(0);
      rreq(0) <= type_cast_52_inst_req_1;
      type_cast_52_inst_ack_1<= rack(0);
      type_cast_52_inst : InterlockBuffer generic map ( -- 
        name => "type_cast_52_inst",
        buffer_size => 1,
        flow_through =>  false ,
        full_rate =>  false ,
        in_data_width => 36,
        out_data_width => 64,
        bypass_flag => true 
        -- 
      )port map ( -- 
        write_req => wreq(0), 
        write_ack => wack(0), 
        write_data => addr_36_37,
        read_req => rreq(0),  
        read_ack => rack(0), 
        read_data => byte_address_buffer,
        clk => clk, reset => reset
        -- 
      );
      end block; -- 
    -- shared inport operator group (0) : RPIPE_AFB_TO_AHB_COMMAND_17_inst 
    InportGroup_0: Block -- 
      signal data_out: std_logic_vector(72 downto 0);
      signal reqL, ackL, reqR, ackR : BooleanArray( 0 downto 0);
      signal reqL_unguarded, ackL_unguarded : BooleanArray( 0 downto 0);
      signal reqR_unguarded, ackR_unguarded : BooleanArray( 0 downto 0);
      signal guard_vector : std_logic_vector( 0 downto 0);
      constant outBUFs : IntegerArray(0 downto 0) := (0 => 1);
      constant guardFlags : BooleanArray(0 downto 0) := (0 => false);
      constant guardBuffering: IntegerArray(0 downto 0)  := (0 => 2);
      -- 
    begin -- 
      reqL_unguarded(0) <= RPIPE_AFB_TO_AHB_COMMAND_17_inst_req_0;
      RPIPE_AFB_TO_AHB_COMMAND_17_inst_ack_0 <= ackL_unguarded(0);
      reqR_unguarded(0) <= RPIPE_AFB_TO_AHB_COMMAND_17_inst_req_1;
      RPIPE_AFB_TO_AHB_COMMAND_17_inst_ack_1 <= ackR_unguarded(0);
      guard_vector(0)  <=  '1';
      command_18 <= data_out(72 downto 0);
      AFB_TO_AHB_COMMAND_read_0_gI: SplitGuardInterface generic map(name => "AFB_TO_AHB_COMMAND_read_0_gI", nreqs => 1, buffering => guardBuffering, use_guards => guardFlags,  sample_only => false,  update_only => true) -- 
        port map(clk => clk, reset => reset,
        sr_in => reqL_unguarded,
        sr_out => reqL,
        sa_in => ackL,
        sa_out => ackL_unguarded,
        cr_in => reqR_unguarded,
        cr_out => reqR,
        ca_in => ackR,
        ca_out => ackR_unguarded,
        guards => guard_vector); -- 
      AFB_TO_AHB_COMMAND_read_0: InputPort_P2P -- 
        generic map ( name => "AFB_TO_AHB_COMMAND_read_0", data_width => 73,   	nonblocking_read_flag => False,  queue_depth =>  2)
        port map (-- 
          sample_req => reqL(0) , 
          sample_ack => ackL(0), 
          update_req => reqR(0), 
          update_ack => ackR(0), 
          data => data_out, 
          oreq => AFB_TO_AHB_COMMAND_pipe_read_req(0),
          oack => AFB_TO_AHB_COMMAND_pipe_read_ack(0),
          odata => AFB_TO_AHB_COMMAND_pipe_read_data(72 downto 0),
          clk => clk, reset => reset -- 
        ); -- 
      -- 
    end Block; -- inport group 0
    -- 
  end Block; -- data_path
  -- 
end get_simplified_ahb_command_arch;
library std;
use std.standard.all;
library ieee;
use ieee.std_logic_1164.all;
library aHiR_ieee_proposed;
use aHiR_ieee_proposed.math_utility_pkg.all;
use aHiR_ieee_proposed.fixed_pkg.all;
use aHiR_ieee_proposed.float_pkg.all;
library ahir;
use ahir.memory_subsystem_package.all;
use ahir.types.all;
use ahir.subprograms.all;
use ahir.components.all;
use ahir.basecomponents.all;
use ahir.operatorpackage.all;
use ahir.floatoperatorpackage.all;
use ahir.utilities.all;
library simplified_ahb_c_interface_;
use simplified_ahb_c_interface_.simplified_ahb_c_interface_global_package.all;
entity send_simplified_ahb_response is -- 
  generic (tag_length : integer); 
  port ( -- 
    err : in  std_logic_vector(7 downto 0);
    read_data : in  std_logic_vector(31 downto 0);
    AHB_TO_AFB_RESPONSE_pipe_write_req : out  std_logic_vector(0 downto 0);
    AHB_TO_AFB_RESPONSE_pipe_write_ack : in   std_logic_vector(0 downto 0);
    AHB_TO_AFB_RESPONSE_pipe_write_data : out  std_logic_vector(32 downto 0);
    tag_in: in std_logic_vector(tag_length-1 downto 0);
    tag_out: out std_logic_vector(tag_length-1 downto 0) ;
    clk : in std_logic;
    reset : in std_logic;
    start_req : in std_logic;
    start_ack : out std_logic;
    fin_req : in std_logic;
    fin_ack   : out std_logic-- 
  );
  -- 
end entity send_simplified_ahb_response;
architecture send_simplified_ahb_response_arch of send_simplified_ahb_response is -- 
  -- always true...
  signal always_true_symbol: Boolean;
  signal in_buffer_data_in, in_buffer_data_out: std_logic_vector((tag_length + 40)-1 downto 0);
  signal default_zero_sig: std_logic;
  signal in_buffer_write_req: std_logic;
  signal in_buffer_write_ack: std_logic;
  signal in_buffer_unload_req_symbol: Boolean;
  signal in_buffer_unload_ack_symbol: Boolean;
  signal out_buffer_data_in, out_buffer_data_out: std_logic_vector((tag_length + 0)-1 downto 0);
  signal out_buffer_read_req: std_logic;
  signal out_buffer_read_ack: std_logic;
  signal out_buffer_write_req_symbol: Boolean;
  signal out_buffer_write_ack_symbol: Boolean;
  signal tag_ub_out, tag_ilock_out: std_logic_vector(tag_length-1 downto 0);
  signal tag_push_req, tag_push_ack, tag_pop_req, tag_pop_ack: std_logic;
  signal tag_unload_req_symbol, tag_unload_ack_symbol, tag_write_req_symbol, tag_write_ack_symbol: Boolean;
  signal tag_ilock_write_req_symbol, tag_ilock_write_ack_symbol, tag_ilock_read_req_symbol, tag_ilock_read_ack_symbol: Boolean;
  signal start_req_sig, fin_req_sig, start_ack_sig, fin_ack_sig: std_logic; 
  signal input_sample_reenable_symbol: Boolean;
  -- input port buffer signals
  signal err_buffer :  std_logic_vector(7 downto 0);
  signal err_update_enable: Boolean;
  signal read_data_buffer :  std_logic_vector(31 downto 0);
  signal read_data_update_enable: Boolean;
  -- output port buffer signals
  signal send_simplified_ahb_response_CP_275_start: Boolean;
  signal send_simplified_ahb_response_CP_275_symbol: Boolean;
  -- volatile/operator module components. 
  -- links between control-path and data-path
  signal CONCAT_u1_u33_94_inst_req_0 : boolean;
  signal CONCAT_u1_u33_94_inst_ack_0 : boolean;
  signal CONCAT_u1_u33_94_inst_req_1 : boolean;
  signal CONCAT_u1_u33_94_inst_ack_1 : boolean;
  signal WPIPE_AHB_TO_AFB_RESPONSE_96_inst_req_0 : boolean;
  signal WPIPE_AHB_TO_AFB_RESPONSE_96_inst_ack_0 : boolean;
  signal WPIPE_AHB_TO_AFB_RESPONSE_96_inst_req_1 : boolean;
  signal WPIPE_AHB_TO_AFB_RESPONSE_96_inst_ack_1 : boolean;
  -- 
begin --  
  -- input handling ------------------------------------------------
  in_buffer: UnloadBuffer -- 
    generic map(name => "send_simplified_ahb_response_input_buffer", -- 
      buffer_size => 1,
      full_rate => false,
      bypass_flag => true,
      data_width => tag_length + 40) -- 
    port map(write_req => in_buffer_write_req, -- 
      write_ack => in_buffer_write_ack, 
      write_data => in_buffer_data_in,
      unload_req => in_buffer_unload_req_symbol, 
      unload_ack => in_buffer_unload_ack_symbol, 
      read_data => in_buffer_data_out,
      clk => clk, reset => reset); -- 
  in_buffer_data_in(7 downto 0) <= err;
  err_buffer <= in_buffer_data_out(7 downto 0);
  in_buffer_data_in(39 downto 8) <= read_data;
  read_data_buffer <= in_buffer_data_out(39 downto 8);
  in_buffer_data_in(tag_length + 39 downto 40) <= tag_in;
  tag_ub_out <= in_buffer_data_out(tag_length + 39 downto 40);
  in_buffer_write_req <= start_req;
  start_ack <= in_buffer_write_ack;
  in_buffer_unload_req_symbol_join: block -- 
    constant place_capacities: IntegerArray(0 to 1) := (0 => 1,1 => 1);
    constant place_markings: IntegerArray(0 to 1)  := (0 => 1,1 => 1);
    constant place_delays: IntegerArray(0 to 1) := (0 => 0,1 => 1);
    constant joinName: string(1 to 32) := "in_buffer_unload_req_symbol_join"; 
    signal preds: BooleanArray(1 to 2); -- 
  begin -- 
    preds <= in_buffer_unload_ack_symbol & input_sample_reenable_symbol;
    gj_in_buffer_unload_req_symbol_join : generic_join generic map(name => joinName, place_capacities => place_capacities, place_markings => place_markings, place_delays => place_delays) -- 
      port map(preds => preds, symbol_out => in_buffer_unload_req_symbol, clk => clk, reset => reset); --
  end block;
  -- join of all unload_ack_symbols.. used to trigger CP.
  send_simplified_ahb_response_CP_275_start <= in_buffer_unload_ack_symbol;
  -- output handling  -------------------------------------------------------
  out_buffer: ReceiveBuffer -- 
    generic map(name => "send_simplified_ahb_response_out_buffer", -- 
      buffer_size => 1,
      full_rate => false,
      data_width => tag_length + 0) --
    port map(write_req => out_buffer_write_req_symbol, -- 
      write_ack => out_buffer_write_ack_symbol, 
      write_data => out_buffer_data_in,
      read_req => out_buffer_read_req, 
      read_ack => out_buffer_read_ack, 
      read_data => out_buffer_data_out,
      clk => clk, reset => reset); -- 
  out_buffer_data_in(tag_length-1 downto 0) <= tag_ilock_out;
  tag_out <= out_buffer_data_out(tag_length-1 downto 0);
  out_buffer_write_req_symbol_join: block -- 
    constant place_capacities: IntegerArray(0 to 2) := (0 => 1,1 => 1,2 => 1);
    constant place_markings: IntegerArray(0 to 2)  := (0 => 0,1 => 1,2 => 0);
    constant place_delays: IntegerArray(0 to 2) := (0 => 0,1 => 1,2 => 0);
    constant joinName: string(1 to 32) := "out_buffer_write_req_symbol_join"; 
    signal preds: BooleanArray(1 to 3); -- 
  begin -- 
    preds <= send_simplified_ahb_response_CP_275_symbol & out_buffer_write_ack_symbol & tag_ilock_read_ack_symbol;
    gj_out_buffer_write_req_symbol_join : generic_join generic map(name => joinName, place_capacities => place_capacities, place_markings => place_markings, place_delays => place_delays) -- 
      port map(preds => preds, symbol_out => out_buffer_write_req_symbol, clk => clk, reset => reset); --
  end block;
  -- write-to output-buffer produces  reenable input sampling
  input_sample_reenable_symbol <= out_buffer_write_ack_symbol;
  -- fin-req/ack level protocol..
  out_buffer_read_req <= fin_req;
  fin_ack <= out_buffer_read_ack;
  ----- tag-queue --------------------------------------------------
  -- interlock buffer for TAG.. to provide required buffering.
  tagIlock: InterlockBuffer -- 
    generic map(name => "tag-interlock-buffer", -- 
      buffer_size => 1,
      bypass_flag => false,
      in_data_width => tag_length,
      out_data_width => tag_length) -- 
    port map(write_req => tag_ilock_write_req_symbol, -- 
      write_ack => tag_ilock_write_ack_symbol, 
      write_data => tag_ub_out,
      read_req => tag_ilock_read_req_symbol, 
      read_ack => tag_ilock_read_ack_symbol, 
      read_data => tag_ilock_out, 
      clk => clk, reset => reset); -- 
  -- tag ilock-buffer control logic. 
  tag_ilock_write_req_symbol_join: block -- 
    constant place_capacities: IntegerArray(0 to 1) := (0 => 1,1 => 1);
    constant place_markings: IntegerArray(0 to 1)  := (0 => 0,1 => 1);
    constant place_delays: IntegerArray(0 to 1) := (0 => 0,1 => 1);
    constant joinName: string(1 to 31) := "tag_ilock_write_req_symbol_join"; 
    signal preds: BooleanArray(1 to 2); -- 
  begin -- 
    preds <= send_simplified_ahb_response_CP_275_start & tag_ilock_write_ack_symbol;
    gj_tag_ilock_write_req_symbol_join : generic_join generic map(name => joinName, place_capacities => place_capacities, place_markings => place_markings, place_delays => place_delays) -- 
      port map(preds => preds, symbol_out => tag_ilock_write_req_symbol, clk => clk, reset => reset); --
  end block;
  tag_ilock_read_req_symbol_join: block -- 
    constant place_capacities: IntegerArray(0 to 2) := (0 => 1,1 => 1,2 => 1);
    constant place_markings: IntegerArray(0 to 2)  := (0 => 0,1 => 1,2 => 1);
    constant place_delays: IntegerArray(0 to 2) := (0 => 0,1 => 0,2 => 0);
    constant joinName: string(1 to 30) := "tag_ilock_read_req_symbol_join"; 
    signal preds: BooleanArray(1 to 3); -- 
  begin -- 
    preds <= send_simplified_ahb_response_CP_275_start & tag_ilock_read_ack_symbol & out_buffer_write_ack_symbol;
    gj_tag_ilock_read_req_symbol_join : generic_join generic map(name => joinName, place_capacities => place_capacities, place_markings => place_markings, place_delays => place_delays) -- 
      port map(preds => preds, symbol_out => tag_ilock_read_req_symbol, clk => clk, reset => reset); --
  end block;
  -- the control path --------------------------------------------------
  always_true_symbol <= true; 
  default_zero_sig <= '0';
  send_simplified_ahb_response_CP_275: Block -- control-path 
    signal send_simplified_ahb_response_CP_275_elements: BooleanArray(4 downto 0);
    -- 
  begin -- 
    send_simplified_ahb_response_CP_275_elements(0) <= send_simplified_ahb_response_CP_275_start;
    send_simplified_ahb_response_CP_275_symbol <= send_simplified_ahb_response_CP_275_elements(4);
    -- CP-element group 0:  fork  transition  output  bypass 
    -- CP-element group 0: predecessors 
    -- CP-element group 0: successors 
    -- CP-element group 0: 	1 
    -- CP-element group 0: 	2 
    -- CP-element group 0:  members (8) 
      -- CP-element group 0: 	 $entry
      -- CP-element group 0: 	 assign_stmt_95/$entry
      -- CP-element group 0: 	 assign_stmt_95/CONCAT_u1_u33_94_sample_start_
      -- CP-element group 0: 	 assign_stmt_95/CONCAT_u1_u33_94_update_start_
      -- CP-element group 0: 	 assign_stmt_95/CONCAT_u1_u33_94_Sample/$entry
      -- CP-element group 0: 	 assign_stmt_95/CONCAT_u1_u33_94_Sample/rr
      -- CP-element group 0: 	 assign_stmt_95/CONCAT_u1_u33_94_Update/$entry
      -- CP-element group 0: 	 assign_stmt_95/CONCAT_u1_u33_94_Update/cr
      -- 
    cr_293_symbol_link_to_dp: control_delay_element -- 
      generic map(name => " cr_293_symbol_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => send_simplified_ahb_response_CP_275_elements(0), ack => CONCAT_u1_u33_94_inst_req_1); -- 
    rr_288_symbol_link_to_dp: control_delay_element -- 
      generic map(name => " rr_288_symbol_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => send_simplified_ahb_response_CP_275_elements(0), ack => CONCAT_u1_u33_94_inst_req_0); -- 
    -- CP-element group 1:  transition  input  bypass 
    -- CP-element group 1: predecessors 
    -- CP-element group 1: 	0 
    -- CP-element group 1: successors 
    -- CP-element group 1:  members (3) 
      -- CP-element group 1: 	 assign_stmt_95/CONCAT_u1_u33_94_sample_completed_
      -- CP-element group 1: 	 assign_stmt_95/CONCAT_u1_u33_94_Sample/$exit
      -- CP-element group 1: 	 assign_stmt_95/CONCAT_u1_u33_94_Sample/ra
      -- 
    ra_289_symbol_link_from_dp: control_delay_element -- 
      generic map(name => " 1_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => CONCAT_u1_u33_94_inst_ack_0, ack => send_simplified_ahb_response_CP_275_elements(1)); -- 
    -- CP-element group 2:  transition  input  output  bypass 
    -- CP-element group 2: predecessors 
    -- CP-element group 2: 	0 
    -- CP-element group 2: successors 
    -- CP-element group 2: 	3 
    -- CP-element group 2:  members (8) 
      -- CP-element group 2: 	 assign_stmt_95/$exit
      -- CP-element group 2: 	 assign_stmt_95/CONCAT_u1_u33_94_update_completed_
      -- CP-element group 2: 	 assign_stmt_95/CONCAT_u1_u33_94_Update/$exit
      -- CP-element group 2: 	 assign_stmt_95/CONCAT_u1_u33_94_Update/ca
      -- CP-element group 2: 	 assign_stmt_98/$entry
      -- CP-element group 2: 	 assign_stmt_98/WPIPE_AHB_TO_AFB_RESPONSE_96_sample_start_
      -- CP-element group 2: 	 assign_stmt_98/WPIPE_AHB_TO_AFB_RESPONSE_96_Sample/$entry
      -- CP-element group 2: 	 assign_stmt_98/WPIPE_AHB_TO_AFB_RESPONSE_96_Sample/req
      -- 
    ca_294_symbol_link_from_dp: control_delay_element -- 
      generic map(name => " 2_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => CONCAT_u1_u33_94_inst_ack_1, ack => send_simplified_ahb_response_CP_275_elements(2)); -- 
    req_305_symbol_link_to_dp: control_delay_element -- 
      generic map(name => " req_305_symbol_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => send_simplified_ahb_response_CP_275_elements(2), ack => WPIPE_AHB_TO_AFB_RESPONSE_96_inst_req_0); -- 
    -- CP-element group 3:  transition  input  output  bypass 
    -- CP-element group 3: predecessors 
    -- CP-element group 3: 	2 
    -- CP-element group 3: successors 
    -- CP-element group 3: 	4 
    -- CP-element group 3:  members (6) 
      -- CP-element group 3: 	 assign_stmt_98/WPIPE_AHB_TO_AFB_RESPONSE_96_sample_completed_
      -- CP-element group 3: 	 assign_stmt_98/WPIPE_AHB_TO_AFB_RESPONSE_96_update_start_
      -- CP-element group 3: 	 assign_stmt_98/WPIPE_AHB_TO_AFB_RESPONSE_96_Sample/$exit
      -- CP-element group 3: 	 assign_stmt_98/WPIPE_AHB_TO_AFB_RESPONSE_96_Sample/ack
      -- CP-element group 3: 	 assign_stmt_98/WPIPE_AHB_TO_AFB_RESPONSE_96_Update/$entry
      -- CP-element group 3: 	 assign_stmt_98/WPIPE_AHB_TO_AFB_RESPONSE_96_Update/req
      -- 
    ack_306_symbol_link_from_dp: control_delay_element -- 
      generic map(name => " 3_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => WPIPE_AHB_TO_AFB_RESPONSE_96_inst_ack_0, ack => send_simplified_ahb_response_CP_275_elements(3)); -- 
    req_310_symbol_link_to_dp: control_delay_element -- 
      generic map(name => " req_310_symbol_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => send_simplified_ahb_response_CP_275_elements(3), ack => WPIPE_AHB_TO_AFB_RESPONSE_96_inst_req_1); -- 
    -- CP-element group 4:  transition  input  bypass 
    -- CP-element group 4: predecessors 
    -- CP-element group 4: 	3 
    -- CP-element group 4: successors 
    -- CP-element group 4:  members (5) 
      -- CP-element group 4: 	 $exit
      -- CP-element group 4: 	 assign_stmt_98/$exit
      -- CP-element group 4: 	 assign_stmt_98/WPIPE_AHB_TO_AFB_RESPONSE_96_update_completed_
      -- CP-element group 4: 	 assign_stmt_98/WPIPE_AHB_TO_AFB_RESPONSE_96_Update/$exit
      -- CP-element group 4: 	 assign_stmt_98/WPIPE_AHB_TO_AFB_RESPONSE_96_Update/ack
      -- 
    ack_311_symbol_link_from_dp: control_delay_element -- 
      generic map(name => " 4_delay",delay_value => 0)
      port map(clk => clk, reset => reset, req => WPIPE_AHB_TO_AFB_RESPONSE_96_inst_ack_1, ack => send_simplified_ahb_response_CP_275_elements(4)); -- 
    --  hookup: inputs to control-path 
    -- hookup: output from control-path 
    -- 
  end Block; -- control-path
  -- the data path
  data_path: Block -- 
    signal MUX_92_wire : std_logic_vector(0 downto 0);
    signal NEQ_u8_u1_88_wire : std_logic_vector(0 downto 0);
    signal konst_87_wire_constant : std_logic_vector(7 downto 0);
    signal konst_91_wire_constant : std_logic_vector(0 downto 0);
    signal to_pipe_95 : std_logic_vector(32 downto 0);
    signal type_cast_90_wire_constant : std_logic_vector(0 downto 0);
    -- 
  begin -- 
    konst_87_wire_constant <= "00000000";
    konst_91_wire_constant <= "0";
    type_cast_90_wire_constant <= "1";
    -- flow-through select operator MUX_92_inst
    MUX_92_wire <= type_cast_90_wire_constant when (NEQ_u8_u1_88_wire(0) /=  '0') else konst_91_wire_constant;
    -- shared split operator group (0) : CONCAT_u1_u33_94_inst 
    ApConcat_group_0: Block -- 
      signal data_in: std_logic_vector(32 downto 0);
      signal data_out: std_logic_vector(32 downto 0);
      signal reqR, ackR, reqL, ackL : BooleanArray( 0 downto 0);
      signal reqR_unguarded, ackR_unguarded, reqL_unguarded, ackL_unguarded : BooleanArray( 0 downto 0);
      signal guard_vector : std_logic_vector( 0 downto 0);
      constant inBUFs : IntegerArray(0 downto 0) := (0 => 0);
      constant outBUFs : IntegerArray(0 downto 0) := (0 => 1);
      constant guardFlags : BooleanArray(0 downto 0) := (0 => false);
      constant guardBuffering: IntegerArray(0 downto 0)  := (0 => 2);
      -- 
    begin -- 
      data_in <= MUX_92_wire & read_data_buffer;
      to_pipe_95 <= data_out(32 downto 0);
      guard_vector(0)  <=  '1';
      reqL_unguarded(0) <= CONCAT_u1_u33_94_inst_req_0;
      CONCAT_u1_u33_94_inst_ack_0 <= ackL_unguarded(0);
      reqR_unguarded(0) <= CONCAT_u1_u33_94_inst_req_1;
      CONCAT_u1_u33_94_inst_ack_1 <= ackR_unguarded(0);
      ApConcat_group_0_gI: SplitGuardInterface generic map(name => "ApConcat_group_0_gI", nreqs => 1, buffering => guardBuffering, use_guards => guardFlags,  sample_only => false,  update_only => false) -- 
        port map(clk => clk, reset => reset,
        sr_in => reqL_unguarded,
        sr_out => reqL,
        sa_in => ackL,
        sa_out => ackL_unguarded,
        cr_in => reqR_unguarded,
        cr_out => reqR,
        ca_in => ackR,
        ca_out => ackR_unguarded,
        guards => guard_vector); -- 
      UnsharedOperator: UnsharedOperatorWithBuffering -- 
        generic map ( -- 
          operator_id => "ApConcat",
          name => "ApConcat_group_0",
          input1_is_int => true, 
          input1_characteristic_width => 0, 
          input1_mantissa_width    => 0, 
          iwidth_1  => 1,
          input2_is_int => true, 
          input2_characteristic_width => 0, 
          input2_mantissa_width => 0, 
          iwidth_2      => 32, 
          num_inputs    => 2,
          output_is_int => true,
          output_characteristic_width  => 0, 
          output_mantissa_width => 0, 
          owidth => 33,
          constant_operand => "0",
          constant_width => 1,
          buffering  => 1,
          flow_through => false,
          full_rate  => false,
          use_constant  => false
          --
        ) 
        port map ( -- 
          reqL => reqL(0),
          ackL => ackL(0),
          reqR => reqR(0),
          ackR => ackR(0),
          dataL => data_in, 
          dataR => data_out,
          clk => clk,
          reset => reset); -- 
      -- 
    end Block; -- split operator group 0
    -- binary operator NEQ_u8_u1_88_inst
    process(err_buffer) -- 
      variable tmp_var : std_logic_vector(0 downto 0); -- 
    begin -- 
      ApIntNe_proc(err_buffer, konst_87_wire_constant, tmp_var);
      NEQ_u8_u1_88_wire <= tmp_var; -- 
    end process;
    -- shared outport operator group (0) : WPIPE_AHB_TO_AFB_RESPONSE_96_inst 
    OutportGroup_0: Block -- 
      signal data_in: std_logic_vector(32 downto 0);
      signal sample_req, sample_ack : BooleanArray( 0 downto 0);
      signal update_req, update_ack : BooleanArray( 0 downto 0);
      signal sample_req_unguarded, sample_ack_unguarded : BooleanArray( 0 downto 0);
      signal update_req_unguarded, update_ack_unguarded : BooleanArray( 0 downto 0);
      signal guard_vector : std_logic_vector( 0 downto 0);
      constant inBUFs : IntegerArray(0 downto 0) := (0 => 0);
      constant guardFlags : BooleanArray(0 downto 0) := (0 => false);
      constant guardBuffering: IntegerArray(0 downto 0)  := (0 => 2);
      -- 
    begin -- 
      sample_req_unguarded(0) <= WPIPE_AHB_TO_AFB_RESPONSE_96_inst_req_0;
      WPIPE_AHB_TO_AFB_RESPONSE_96_inst_ack_0 <= sample_ack_unguarded(0);
      update_req_unguarded(0) <= WPIPE_AHB_TO_AFB_RESPONSE_96_inst_req_1;
      WPIPE_AHB_TO_AFB_RESPONSE_96_inst_ack_1 <= update_ack_unguarded(0);
      guard_vector(0)  <=  '1';
      data_in <= to_pipe_95;
      AHB_TO_AFB_RESPONSE_write_0_gI: SplitGuardInterface generic map(name => "AHB_TO_AFB_RESPONSE_write_0_gI", nreqs => 1, buffering => guardBuffering, use_guards => guardFlags,  sample_only => true,  update_only => false) -- 
        port map(clk => clk, reset => reset,
        sr_in => sample_req_unguarded,
        sr_out => sample_req,
        sa_in => sample_ack,
        sa_out => sample_ack_unguarded,
        cr_in => update_req_unguarded,
        cr_out => update_req,
        ca_in => update_ack,
        ca_out => update_ack_unguarded,
        guards => guard_vector); -- 
      AHB_TO_AFB_RESPONSE_write_0: OutputPortRevised -- 
        generic map ( name => "AHB_TO_AFB_RESPONSE", data_width => 33, num_reqs => 1, input_buffering => inBUFs, full_rate => false,
        no_arbitration => false)
        port map (--
          sample_req => sample_req , 
          sample_ack => sample_ack , 
          update_req => update_req , 
          update_ack => update_ack , 
          data => data_in, 
          oreq => AHB_TO_AFB_RESPONSE_pipe_write_req(0),
          oack => AHB_TO_AFB_RESPONSE_pipe_write_ack(0),
          odata => AHB_TO_AFB_RESPONSE_pipe_write_data(32 downto 0),
          clk => clk, reset => reset -- 
        );-- 
      -- 
    end Block; -- outport group 0
    -- 
  end Block; -- data_path
  -- 
end send_simplified_ahb_response_arch;
library std;
use std.standard.all;
library ieee;
use ieee.std_logic_1164.all;
library aHiR_ieee_proposed;
use aHiR_ieee_proposed.math_utility_pkg.all;
use aHiR_ieee_proposed.fixed_pkg.all;
use aHiR_ieee_proposed.float_pkg.all;
library ahir;
use ahir.memory_subsystem_package.all;
use ahir.types.all;
use ahir.subprograms.all;
use ahir.components.all;
use ahir.basecomponents.all;
use ahir.operatorpackage.all;
use ahir.floatoperatorpackage.all;
use ahir.utilities.all;
library simplified_ahb_c_interface_;
use simplified_ahb_c_interface_.simplified_ahb_c_interface_global_package.all;
entity simplified_ahb_c_interface is  -- system 
  port (-- 
    get_simplified_ahb_command_rw : out  std_logic_vector(7 downto 0);
    get_simplified_ahb_command_transfer_size : out  std_logic_vector(7 downto 0);
    get_simplified_ahb_command_byte_address : out  std_logic_vector(63 downto 0);
    get_simplified_ahb_command_write_data : out  std_logic_vector(31 downto 0);
    get_simplified_ahb_command_tag_in: in std_logic_vector(1 downto 0);
    get_simplified_ahb_command_tag_out: out std_logic_vector(1 downto 0);
    get_simplified_ahb_command_start_req : in std_logic;
    get_simplified_ahb_command_start_ack : out std_logic;
    get_simplified_ahb_command_fin_req   : in std_logic;
    get_simplified_ahb_command_fin_ack   : out std_logic;
    send_simplified_ahb_response_err : in  std_logic_vector(7 downto 0);
    send_simplified_ahb_response_read_data : in  std_logic_vector(31 downto 0);
    send_simplified_ahb_response_tag_in: in std_logic_vector(1 downto 0);
    send_simplified_ahb_response_tag_out: out std_logic_vector(1 downto 0);
    send_simplified_ahb_response_start_req : in std_logic;
    send_simplified_ahb_response_start_ack : out std_logic;
    send_simplified_ahb_response_fin_req   : in std_logic;
    send_simplified_ahb_response_fin_ack   : out std_logic;
    clk : in std_logic;
    reset : in std_logic;
    AFB_TO_AHB_COMMAND_pipe_write_data: in std_logic_vector(72 downto 0);
    AFB_TO_AHB_COMMAND_pipe_write_req : in std_logic_vector(0 downto 0);
    AFB_TO_AHB_COMMAND_pipe_write_ack : out std_logic_vector(0 downto 0);
    AHB_TO_AFB_RESPONSE_pipe_read_data: out std_logic_vector(32 downto 0);
    AHB_TO_AFB_RESPONSE_pipe_read_req : in std_logic_vector(0 downto 0);
    AHB_TO_AFB_RESPONSE_pipe_read_ack : out std_logic_vector(0 downto 0)); -- 
  -- 
end entity; 
architecture simplified_ahb_c_interface_arch  of simplified_ahb_c_interface is -- system-architecture 
  -- interface signals to connect to memory space memory_space_1
  -- declarations related to module get_simplified_ahb_command
  component get_simplified_ahb_command is -- 
    generic (tag_length : integer); 
    port ( -- 
      rw : out  std_logic_vector(7 downto 0);
      transfer_size : out  std_logic_vector(7 downto 0);
      byte_address : out  std_logic_vector(63 downto 0);
      write_data : out  std_logic_vector(31 downto 0);
      AFB_TO_AHB_COMMAND_pipe_read_req : out  std_logic_vector(0 downto 0);
      AFB_TO_AHB_COMMAND_pipe_read_ack : in   std_logic_vector(0 downto 0);
      AFB_TO_AHB_COMMAND_pipe_read_data : in   std_logic_vector(72 downto 0);
      tag_in: in std_logic_vector(tag_length-1 downto 0);
      tag_out: out std_logic_vector(tag_length-1 downto 0) ;
      clk : in std_logic;
      reset : in std_logic;
      start_req : in std_logic;
      start_ack : out std_logic;
      fin_req : in std_logic;
      fin_ack   : out std_logic-- 
    );
    -- 
  end component;
  -- declarations related to module send_simplified_ahb_response
  component send_simplified_ahb_response is -- 
    generic (tag_length : integer); 
    port ( -- 
      err : in  std_logic_vector(7 downto 0);
      read_data : in  std_logic_vector(31 downto 0);
      AHB_TO_AFB_RESPONSE_pipe_write_req : out  std_logic_vector(0 downto 0);
      AHB_TO_AFB_RESPONSE_pipe_write_ack : in   std_logic_vector(0 downto 0);
      AHB_TO_AFB_RESPONSE_pipe_write_data : out  std_logic_vector(32 downto 0);
      tag_in: in std_logic_vector(tag_length-1 downto 0);
      tag_out: out std_logic_vector(tag_length-1 downto 0) ;
      clk : in std_logic;
      reset : in std_logic;
      start_req : in std_logic;
      start_ack : out std_logic;
      fin_req : in std_logic;
      fin_ack   : out std_logic-- 
    );
    -- 
  end component;
  -- aggregate signals for read from pipe AFB_TO_AHB_COMMAND
  signal AFB_TO_AHB_COMMAND_pipe_read_data: std_logic_vector(72 downto 0);
  signal AFB_TO_AHB_COMMAND_pipe_read_req: std_logic_vector(0 downto 0);
  signal AFB_TO_AHB_COMMAND_pipe_read_ack: std_logic_vector(0 downto 0);
  -- aggregate signals for write to pipe AHB_TO_AFB_RESPONSE
  signal AHB_TO_AFB_RESPONSE_pipe_write_data: std_logic_vector(32 downto 0);
  signal AHB_TO_AFB_RESPONSE_pipe_write_req: std_logic_vector(0 downto 0);
  signal AHB_TO_AFB_RESPONSE_pipe_write_ack: std_logic_vector(0 downto 0);
  -- 
begin -- 
  -- module get_simplified_ahb_command
  get_simplified_ahb_command_instance:get_simplified_ahb_command-- 
    generic map(tag_length => 2)
    port map(-- 
      rw => get_simplified_ahb_command_rw,
      transfer_size => get_simplified_ahb_command_transfer_size,
      byte_address => get_simplified_ahb_command_byte_address,
      write_data => get_simplified_ahb_command_write_data,
      start_req => get_simplified_ahb_command_start_req,
      start_ack => get_simplified_ahb_command_start_ack,
      fin_req => get_simplified_ahb_command_fin_req,
      fin_ack => get_simplified_ahb_command_fin_ack,
      clk => clk,
      reset => reset,
      AFB_TO_AHB_COMMAND_pipe_read_req => AFB_TO_AHB_COMMAND_pipe_read_req(0 downto 0),
      AFB_TO_AHB_COMMAND_pipe_read_ack => AFB_TO_AHB_COMMAND_pipe_read_ack(0 downto 0),
      AFB_TO_AHB_COMMAND_pipe_read_data => AFB_TO_AHB_COMMAND_pipe_read_data(72 downto 0),
      tag_in => get_simplified_ahb_command_tag_in,
      tag_out => get_simplified_ahb_command_tag_out-- 
    ); -- 
  -- module send_simplified_ahb_response
  send_simplified_ahb_response_instance:send_simplified_ahb_response-- 
    generic map(tag_length => 2)
    port map(-- 
      err => send_simplified_ahb_response_err,
      read_data => send_simplified_ahb_response_read_data,
      start_req => send_simplified_ahb_response_start_req,
      start_ack => send_simplified_ahb_response_start_ack,
      fin_req => send_simplified_ahb_response_fin_req,
      fin_ack => send_simplified_ahb_response_fin_ack,
      clk => clk,
      reset => reset,
      AHB_TO_AFB_RESPONSE_pipe_write_req => AHB_TO_AFB_RESPONSE_pipe_write_req(0 downto 0),
      AHB_TO_AFB_RESPONSE_pipe_write_ack => AHB_TO_AFB_RESPONSE_pipe_write_ack(0 downto 0),
      AHB_TO_AFB_RESPONSE_pipe_write_data => AHB_TO_AFB_RESPONSE_pipe_write_data(32 downto 0),
      tag_in => send_simplified_ahb_response_tag_in,
      tag_out => send_simplified_ahb_response_tag_out-- 
    ); -- 
  AFB_TO_AHB_COMMAND_Pipe: PipeBase -- 
    generic map( -- 
      name => "pipe AFB_TO_AHB_COMMAND",
      num_reads => 1,
      num_writes => 1,
      data_width => 73,
      lifo_mode => false,
      full_rate => false,
      shift_register_mode => false,
      depth => 0 --
    )
    port map( -- 
      read_req => AFB_TO_AHB_COMMAND_pipe_read_req,
      read_ack => AFB_TO_AHB_COMMAND_pipe_read_ack,
      read_data => AFB_TO_AHB_COMMAND_pipe_read_data,
      write_req => AFB_TO_AHB_COMMAND_pipe_write_req,
      write_ack => AFB_TO_AHB_COMMAND_pipe_write_ack,
      write_data => AFB_TO_AHB_COMMAND_pipe_write_data,
      clk => clk,reset => reset -- 
    ); -- 
  AHB_TO_AFB_RESPONSE_Pipe: PipeBase -- 
    generic map( -- 
      name => "pipe AHB_TO_AFB_RESPONSE",
      num_reads => 1,
      num_writes => 1,
      data_width => 33,
      lifo_mode => false,
      full_rate => false,
      shift_register_mode => false,
      depth => 0 --
    )
    port map( -- 
      read_req => AHB_TO_AFB_RESPONSE_pipe_read_req,
      read_ack => AHB_TO_AFB_RESPONSE_pipe_read_ack,
      read_data => AHB_TO_AFB_RESPONSE_pipe_read_data,
      write_req => AHB_TO_AFB_RESPONSE_pipe_write_req,
      write_ack => AHB_TO_AFB_RESPONSE_pipe_write_ack,
      write_data => AHB_TO_AFB_RESPONSE_pipe_write_data,
      clk => clk,reset => reset -- 
    ); -- 
  -- 
end simplified_ahb_c_interface_arch;
