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
library ModelsimLink;
use ModelsimLink.Utility_Package.all;
use ModelsimLink.Modelsim_FLI_Foreign.all;
entity simplified_ahb_c_interface_Test_Bench is -- 
  -- 
end entity;
architecture VhpiLink of simplified_ahb_c_interface_Test_Bench is -- 
  signal clk: std_logic := '0';
  signal reset: std_logic := '1';
  signal get_simplified_ahb_command_rw :   std_logic_vector(7 downto 0);
  signal get_simplified_ahb_command_transfer_size :   std_logic_vector(7 downto 0);
  signal get_simplified_ahb_command_byte_address :   std_logic_vector(63 downto 0);
  signal get_simplified_ahb_command_write_data :   std_logic_vector(31 downto 0);
  signal get_simplified_ahb_command_tag_in: std_logic_vector(1 downto 0);
  signal get_simplified_ahb_command_tag_out: std_logic_vector(1 downto 0);
  signal get_simplified_ahb_command_start_req : std_logic := '0';
  signal get_simplified_ahb_command_start_ack : std_logic := '0';
  signal get_simplified_ahb_command_fin_req   : std_logic := '0';
  signal get_simplified_ahb_command_fin_ack   : std_logic := '0';
  signal send_simplified_ahb_response_err :  std_logic_vector(7 downto 0) := (others => '0');
  signal send_simplified_ahb_response_read_data :  std_logic_vector(31 downto 0) := (others => '0');
  signal send_simplified_ahb_response_tag_in: std_logic_vector(1 downto 0);
  signal send_simplified_ahb_response_tag_out: std_logic_vector(1 downto 0);
  signal send_simplified_ahb_response_start_req : std_logic := '0';
  signal send_simplified_ahb_response_start_ack : std_logic := '0';
  signal send_simplified_ahb_response_fin_req   : std_logic := '0';
  signal send_simplified_ahb_response_fin_ack   : std_logic := '0';
  -- write to pipe AFB_TO_AHB_COMMAND
  signal AFB_TO_AHB_COMMAND_pipe_write_data: std_logic_vector(72 downto 0);
  signal AFB_TO_AHB_COMMAND_pipe_write_req : std_logic_vector(0 downto 0) := (others => '0');
  signal AFB_TO_AHB_COMMAND_pipe_write_ack : std_logic_vector(0 downto 0);
  -- read from pipe AHB_TO_AFB_RESPONSE
  signal AHB_TO_AFB_RESPONSE_pipe_read_data: std_logic_vector(32 downto 0);
  signal AHB_TO_AFB_RESPONSE_pipe_read_req : std_logic_vector(0 downto 0) := (others => '0');
  signal AHB_TO_AFB_RESPONSE_pipe_read_ack : std_logic_vector(0 downto 0);
  -- 
begin --
  -- clock/reset generation 
  clk <= not clk after 5 ns;
  process
  begin --
    Modelsim_FLI_Initialize;
    wait until clk = '1';
    reset <= '0';
    while true loop --
      wait until clk = '0';
      Modelsim_FLI_Listen;
      Modelsim_FLI_Send;
      --
    end loop;
    wait;
    --
  end process;
  -- connect all the top-level modules to Vhpi
  process
  variable val_string, obj_ref: VhpiString;
  begin --
    wait until reset = '0';
    while true loop -- 
      wait until clk = '0';
      wait for 1 ns;
      obj_ref := Pack_String_To_VHPI_String("get_simplified_ahb_command req");
      Modelsim_FLI_Get_Port_Value(obj_ref,val_string,1);
      get_simplified_ahb_command_start_req <= To_Std_Logic(val_string);
      wait for 0 ns;
      if get_simplified_ahb_command_start_req = '1' then -- 
        while true loop --
          wait until clk = '1';
          if get_simplified_ahb_command_start_ack = '1' then exit; end if;--
        end loop; 
        get_simplified_ahb_command_start_req <= '0';
        get_simplified_ahb_command_fin_req <= '1';
        while true loop -- 
          wait until clk = '1';
          if get_simplified_ahb_command_fin_ack = '1' then exit; end if; --  
        end loop; 
        get_simplified_ahb_command_fin_req <= '0';
        -- 
      end if; 
      obj_ref := Pack_String_To_Vhpi_String("get_simplified_ahb_command ack");
      val_string := To_String(get_simplified_ahb_command_fin_ack);
      Modelsim_FLI_Set_Port_Value(obj_ref,val_string,1);
      obj_ref := Pack_String_To_Vhpi_String("get_simplified_ahb_command 0");
      val_string := Pack_SLV_To_Vhpi_String(get_simplified_ahb_command_rw);
      Modelsim_FLI_Set_Port_Value(obj_ref,val_string,8);
      obj_ref := Pack_String_To_Vhpi_String("get_simplified_ahb_command 1");
      val_string := Pack_SLV_To_Vhpi_String(get_simplified_ahb_command_transfer_size);
      Modelsim_FLI_Set_Port_Value(obj_ref,val_string,8);
      obj_ref := Pack_String_To_Vhpi_String("get_simplified_ahb_command 2");
      val_string := Pack_SLV_To_Vhpi_String(get_simplified_ahb_command_byte_address);
      Modelsim_FLI_Set_Port_Value(obj_ref,val_string,64);
      obj_ref := Pack_String_To_Vhpi_String("get_simplified_ahb_command 3");
      val_string := Pack_SLV_To_Vhpi_String(get_simplified_ahb_command_write_data);
      Modelsim_FLI_Set_Port_Value(obj_ref,val_string,32);
      -- 
    end loop;
    --
  end process;
  process
  variable val_string, obj_ref: VhpiString;
  begin --
    wait until reset = '0';
    while true loop -- 
      wait until clk = '0';
      wait for 1 ns;
      obj_ref := Pack_String_To_VHPI_String("send_simplified_ahb_response req");
      Modelsim_FLI_Get_Port_Value(obj_ref,val_string,1);
      send_simplified_ahb_response_start_req <= To_Std_Logic(val_string);
      obj_ref := Pack_String_To_Vhpi_String("send_simplified_ahb_response 0");
      Modelsim_FLI_Get_Port_Value(obj_ref,val_string, 8);
      send_simplified_ahb_response_err <= Unpack_String(val_string,8);
      obj_ref := Pack_String_To_Vhpi_String("send_simplified_ahb_response 1");
      Modelsim_FLI_Get_Port_Value(obj_ref,val_string, 32);
      send_simplified_ahb_response_read_data <= Unpack_String(val_string,32);
      wait for 0 ns;
      if send_simplified_ahb_response_start_req = '1' then -- 
        while true loop --
          wait until clk = '1';
          if send_simplified_ahb_response_start_ack = '1' then exit; end if;--
        end loop; 
        send_simplified_ahb_response_start_req <= '0';
        send_simplified_ahb_response_fin_req <= '1';
        while true loop -- 
          wait until clk = '1';
          if send_simplified_ahb_response_fin_ack = '1' then exit; end if; --  
        end loop; 
        send_simplified_ahb_response_fin_req <= '0';
        -- 
      end if; 
      obj_ref := Pack_String_To_Vhpi_String("send_simplified_ahb_response ack");
      val_string := To_String(send_simplified_ahb_response_fin_ack);
      Modelsim_FLI_Set_Port_Value(obj_ref,val_string,1);
      -- 
    end loop;
    --
  end process;
  process
  variable port_val_string, req_val_string, ack_val_string,  obj_ref: VhpiString;
  begin --
    wait until reset = '0';
    while true loop -- 
      wait until clk = '0';
      wait for 1 ns; 
      obj_ref := Pack_String_To_Vhpi_String("AFB_TO_AHB_COMMAND req");
      Modelsim_FLI_Get_Port_Value(obj_ref,req_val_string,1);
      AFB_TO_AHB_COMMAND_pipe_write_req <= Unpack_String(req_val_string,1);
      obj_ref := Pack_String_To_Vhpi_String("AFB_TO_AHB_COMMAND 0");
      Modelsim_FLI_Get_Port_Value(obj_ref,port_val_string,73);
      AFB_TO_AHB_COMMAND_pipe_write_data <= Unpack_String(port_val_string,73);
      wait until clk = '1';
      obj_ref := Pack_String_To_Vhpi_String("AFB_TO_AHB_COMMAND ack");
      ack_val_string := Pack_SLV_To_Vhpi_String(AFB_TO_AHB_COMMAND_pipe_write_ack);
      Modelsim_FLI_Set_Port_Value(obj_ref,ack_val_string,1);
      -- 
    end loop;
    --
  end process;
  process
  variable port_val_string, req_val_string, ack_val_string,  obj_ref: VhpiString;
  begin --
    wait until reset = '0';
    while true loop -- 
      wait until clk = '0';
      wait for 1 ns; 
      obj_ref := Pack_String_To_Vhpi_String("AHB_TO_AFB_RESPONSE req");
      Modelsim_FLI_Get_Port_Value(obj_ref,req_val_string,1);
      AHB_TO_AFB_RESPONSE_pipe_read_req <= Unpack_String(req_val_string,1);
      wait until clk = '1';
      obj_ref := Pack_String_To_Vhpi_String("AHB_TO_AFB_RESPONSE ack");
      ack_val_string := Pack_SLV_To_Vhpi_String(AHB_TO_AFB_RESPONSE_pipe_read_ack);
      Modelsim_FLI_Set_Port_Value(obj_ref,ack_val_string,1);
      obj_ref := Pack_String_To_Vhpi_String("AHB_TO_AFB_RESPONSE 0");
      port_val_string := Pack_SLV_To_Vhpi_String(AHB_TO_AFB_RESPONSE_pipe_read_data);
      Modelsim_FLI_Set_Port_Value(obj_ref,port_val_string,33);
      -- 
    end loop;
    --
  end process;
  simplified_ahb_c_interface_instance: simplified_ahb_c_interface -- 
    port map ( -- 
      get_simplified_ahb_command_rw => get_simplified_ahb_command_rw,
      get_simplified_ahb_command_transfer_size => get_simplified_ahb_command_transfer_size,
      get_simplified_ahb_command_byte_address => get_simplified_ahb_command_byte_address,
      get_simplified_ahb_command_write_data => get_simplified_ahb_command_write_data,
      get_simplified_ahb_command_tag_in => get_simplified_ahb_command_tag_in,
      get_simplified_ahb_command_tag_out => get_simplified_ahb_command_tag_out,
      get_simplified_ahb_command_start_req => get_simplified_ahb_command_start_req,
      get_simplified_ahb_command_start_ack => get_simplified_ahb_command_start_ack,
      get_simplified_ahb_command_fin_req  => get_simplified_ahb_command_fin_req, 
      get_simplified_ahb_command_fin_ack  => get_simplified_ahb_command_fin_ack ,
      send_simplified_ahb_response_err => send_simplified_ahb_response_err,
      send_simplified_ahb_response_read_data => send_simplified_ahb_response_read_data,
      send_simplified_ahb_response_tag_in => send_simplified_ahb_response_tag_in,
      send_simplified_ahb_response_tag_out => send_simplified_ahb_response_tag_out,
      send_simplified_ahb_response_start_req => send_simplified_ahb_response_start_req,
      send_simplified_ahb_response_start_ack => send_simplified_ahb_response_start_ack,
      send_simplified_ahb_response_fin_req  => send_simplified_ahb_response_fin_req, 
      send_simplified_ahb_response_fin_ack  => send_simplified_ahb_response_fin_ack ,
      clk => clk,
      reset => reset,
      AFB_TO_AHB_COMMAND_pipe_write_data  => AFB_TO_AHB_COMMAND_pipe_write_data, 
      AFB_TO_AHB_COMMAND_pipe_write_req  => AFB_TO_AHB_COMMAND_pipe_write_req, 
      AFB_TO_AHB_COMMAND_pipe_write_ack  => AFB_TO_AHB_COMMAND_pipe_write_ack,
      AHB_TO_AFB_RESPONSE_pipe_read_data  => AHB_TO_AFB_RESPONSE_pipe_read_data, 
      AHB_TO_AFB_RESPONSE_pipe_read_req  => AHB_TO_AFB_RESPONSE_pipe_read_req, 
      AHB_TO_AFB_RESPONSE_pipe_read_ack  => AHB_TO_AFB_RESPONSE_pipe_read_ack ); -- 
  -- 
end VhpiLink;
