#include <pthread.h>
#include <pthreadUtils.h>
#include <Pipes.h>
#include <cache_c_interface__aa_c_model.h>
FILE           *cache_c_interface____report_log_file__ = NULL;
void
cache_c_interface___set_trace_file(FILE * fp)
{
    cache_c_interface____report_log_file__ = fp;
}
bit_vector      ASI_AJIT_BRIDGE_CONFIG;
bit_vector      ASI_BLOCK_COPY;
bit_vector      ASI_BLOCK_FILL;
bit_vector      ASI_CACHE_DATA_I;
bit_vector      ASI_CACHE_DATA_I_D;
bit_vector      ASI_CACHE_TAG_I;
bit_vector      ASI_CACHE_TAG_I_D;
bit_vector      ASI_FLUSH_I_CONTEXT;
bit_vector      ASI_FLUSH_I_D_CONTEXT;
bit_vector      ASI_FLUSH_I_D_PAGE;
bit_vector      ASI_FLUSH_I_D_REGION;
bit_vector      ASI_FLUSH_I_D_SEGMENT;
bit_vector      ASI_FLUSH_I_D_USER;
bit_vector      ASI_FLUSH_I_PAGE;
bit_vector      ASI_FLUSH_I_REGION;
bit_vector      ASI_FLUSH_I_SEGMENT;
bit_vector      ASI_FLUSH_I_USER;
bit_vector      ASI_MMU_DIAGNOSTIC_I;
bit_vector      ASI_MMU_DIAGNOSTIC_IO;
bit_vector      ASI_MMU_DIAGNOSTIC_I_D;
bit_vector      ASI_MMU_FLUSH_PROBE;
bit_vector      ASI_MMU_REGISTER;
bit_vector      ASI_SUPERVISOR_DATA;
bit_vector      ASI_SUPERVISOR_INSTRUCTION;
bit_vector      ASI_USER_DATA;
bit_vector      ASI_USER_INSTRUCTION;
bit_vector      CACHE_ARRAY_NOP;
bit_vector      CACHE_ARRAY_READ_DWORD;
bit_vector      CACHE_ARRAY_WRITE_DWORD;
bit_vector      CACHE_ARRAY_WRITE_LINE;
bit_vector      CACHE_TAG_CLEAR_ALL;
bit_vector      CACHE_TAG_CLEAR_LINE;
bit_vector      CACHE_TAG_INSERT;
bit_vector      CACHE_TAG_LOOKUP;
bit_vector      CACHE_TAG_NOP;
bit_vector      DEBUG_MODE_MASK;
bit_vector      FOUR_3;
bit_vector      GDB_DBG_CONNECT;
bit_vector      GDB_DBG_CONTINUE;
bit_vector      GDB_DBG_DETACH;
bit_vector      GDB_DBG_KILL;
bit_vector      GDB_DBG_READ_CONTROL_REG;
bit_vector      GDB_DBG_READ_CPUNIT_REG;
bit_vector      GDB_DBG_READ_FPUNIT_REG;
bit_vector      GDB_DBG_READ_IUNIT_REG;
bit_vector      GDB_DBG_READ_MEM;
bit_vector      GDB_DBG_REMOVE_BREAK_POINT;
bit_vector      GDB_DBG_REMOVE_WATCH_POINT;
bit_vector      GDB_DBG_SET_BREAK_POINT;
bit_vector      GDB_DBG_SET_WATCH_POINT;
bit_vector      GDB_DBG_WRITE_CONTROL_REG;
bit_vector      GDB_DBG_WRITE_CPUNIT_REG;
bit_vector      GDB_DBG_WRITE_FPUNIT_REG;
bit_vector      GDB_DBG_WRITE_IUNIT_REG;
bit_vector      GDB_DBG_WRITE_MEM;
bit_vector      HARD_RESET_MASK;
bit_vector      KILL_STREAM_MASK;
bit_vector      KILL_THREAD_MASK;
bit_vector      LOGGER_ACTIVE_MASK;
bit_vector      MMU_PASS_THROUGH_HLIMIT;
bit_vector      MMU_PASS_THROUGH_LLIMIT;
bit_vector      MMU_READ_DWORD;
bit_vector      MMU_READ_LINE;
bit_vector      MMU_WRITE_DWORD;
bit_vector      MMU_WRITE_DWORD_NO_RESPONSE;
bit_vector      MMU_WRITE_FSR;
bit_vector      NEW_STREAM_MASK;
bit_vector      NEW_THREAD_MASK;
bit_vector      NPC_RESET_VALUE;
bit_vector      NWINDOWS;
bit_vector      NWINDOWS_MOD_MASK_32;
bit_vector      NWINDOWS_MOD_MASK_5;
bit_vector      NWINDOWSx16;
bit_vector      NWINDOWSx16_MOD_MASK_32;
bit_vector      NWINDOWSx2;
bit_vector      ONE_1;
bit_vector      ONE_10;
bit_vector      ONE_11;
bit_vector      ONE_12;
bit_vector      ONE_128;
bit_vector      ONE_13;
bit_vector      ONE_14;
bit_vector      ONE_16;
bit_vector      ONE_17;
bit_vector      ONE_18;
bit_vector      ONE_19;
bit_vector      ONE_2;
bit_vector      ONE_23;
bit_vector      ONE_24;
bit_vector      ONE_25;
bit_vector      ONE_256;
bit_vector      ONE_29;
bit_vector      ONE_3;
bit_vector      ONE_31;
bit_vector      ONE_32;
bit_vector      ONE_36;
bit_vector      ONE_4;
bit_vector      ONE_48;
bit_vector      ONE_5;
bit_vector      ONE_6;
bit_vector      ONE_64;
bit_vector      ONE_7;
bit_vector      ONE_8;
bit_vector      ONE_9;
bit_vector      PC_RESET_VALUE;
bit_vector      PROCESSOR_ERROR_MODE;
bit_vector      PROCESSOR_EXECUTE_MODE;
bit_vector      PROCESSOR_RESET_MODE;
bit_vector      PROCESSOR_UNDEFINED_MODE;
bit_vector      PSR_RESET_VALUE;
bit_vector      REQUEST_TYPE_BRIDGE_CONFIG_READ;
bit_vector      REQUEST_TYPE_BRIDGE_CONFIG_WRITE;
bit_vector      REQUEST_TYPE_CCU_CACHE_READ;
bit_vector      REQUEST_TYPE_CCU_CACHE_WRITE;
bit_vector      REQUEST_TYPE_IFETCH;
bit_vector      REQUEST_TYPE_NOP;
bit_vector      REQUEST_TYPE_READ;
bit_vector      REQUEST_TYPE_STBAR;
bit_vector      REQUEST_TYPE_WRFSRFAR;
bit_vector      REQUEST_TYPE_WRITE;
bit_vector      SINGLE_STEP_MASK;
bit_vector      THREE_2;
bit_vector      THREE_3;
bit_vector      TRACE_ON;
bit_vector      TWO_2;
bit_vector      TWO_3;
bit_vector      WIM_MASK;
bit_vector      ZERO_1;
bit_vector      ZERO_10;
bit_vector      ZERO_11;
bit_vector      ZERO_12;
bit_vector      ZERO_128;
bit_vector      ZERO_13;
bit_vector      ZERO_14;
bit_vector      ZERO_16;
bit_vector      ZERO_17;
bit_vector      ZERO_18;
bit_vector      ZERO_19;
bit_vector      ZERO_2;
bit_vector      ZERO_23;
bit_vector      ZERO_24;
bit_vector      ZERO_25;
bit_vector      ZERO_256;
bit_vector      ZERO_29;
bit_vector      ZERO_3;
bit_vector      ZERO_31;
bit_vector      ZERO_32;
bit_vector      ZERO_36;
bit_vector      ZERO_4;
bit_vector      ZERO_48;
bit_vector      ZERO_5;
bit_vector      ZERO_6;
bit_vector      ZERO_64;
bit_vector      ZERO_7;
bit_vector      ZERO_8;
bit_vector      ZERO_9;
bit_vector      default_mem_pool[1];
void
cache_c_interface____init_aa_globals__()
{
    init_static_bit_vector(&(ASI_AJIT_BRIDGE_CONFIG), 8);
    bit_vector_clear(&ASI_AJIT_BRIDGE_CONFIG);
    ASI_AJIT_BRIDGE_CONFIG.val.byte_array[0] = 48;
    init_static_bit_vector(&(ASI_BLOCK_COPY), 8);
    bit_vector_clear(&ASI_BLOCK_COPY);
    ASI_BLOCK_COPY.val.byte_array[0] = 23;
    init_static_bit_vector(&(ASI_BLOCK_FILL), 8);
    bit_vector_clear(&ASI_BLOCK_FILL);
    ASI_BLOCK_FILL.val.byte_array[0] = 31;
    init_static_bit_vector(&(ASI_CACHE_DATA_I), 8);
    bit_vector_clear(&ASI_CACHE_DATA_I);
    ASI_CACHE_DATA_I.val.byte_array[0] = 13;
    init_static_bit_vector(&(ASI_CACHE_DATA_I_D), 8);
    bit_vector_clear(&ASI_CACHE_DATA_I_D);
    ASI_CACHE_DATA_I_D.val.byte_array[0] = 15;
    init_static_bit_vector(&(ASI_CACHE_TAG_I), 8);
    bit_vector_clear(&ASI_CACHE_TAG_I);
    ASI_CACHE_TAG_I.val.byte_array[0] = 12;
    init_static_bit_vector(&(ASI_CACHE_TAG_I_D), 8);
    bit_vector_clear(&ASI_CACHE_TAG_I_D);
    ASI_CACHE_TAG_I_D.val.byte_array[0] = 14;
    init_static_bit_vector(&(ASI_FLUSH_I_CONTEXT), 8);
    bit_vector_clear(&ASI_FLUSH_I_CONTEXT);
    ASI_FLUSH_I_CONTEXT.val.byte_array[0] = 27;
    init_static_bit_vector(&(ASI_FLUSH_I_D_CONTEXT), 8);
    bit_vector_clear(&ASI_FLUSH_I_D_CONTEXT);
    ASI_FLUSH_I_D_CONTEXT.val.byte_array[0] = 19;
    init_static_bit_vector(&(ASI_FLUSH_I_D_PAGE), 8);
    bit_vector_clear(&ASI_FLUSH_I_D_PAGE);
    ASI_FLUSH_I_D_PAGE.val.byte_array[0] = 16;
    init_static_bit_vector(&(ASI_FLUSH_I_D_REGION), 8);
    bit_vector_clear(&ASI_FLUSH_I_D_REGION);
    ASI_FLUSH_I_D_REGION.val.byte_array[0] = 18;
    init_static_bit_vector(&(ASI_FLUSH_I_D_SEGMENT), 8);
    bit_vector_clear(&ASI_FLUSH_I_D_SEGMENT);
    ASI_FLUSH_I_D_SEGMENT.val.byte_array[0] = 17;
    init_static_bit_vector(&(ASI_FLUSH_I_D_USER), 8);
    bit_vector_clear(&ASI_FLUSH_I_D_USER);
    ASI_FLUSH_I_D_USER.val.byte_array[0] = 20;
    init_static_bit_vector(&(ASI_FLUSH_I_PAGE), 8);
    bit_vector_clear(&ASI_FLUSH_I_PAGE);
    ASI_FLUSH_I_PAGE.val.byte_array[0] = 24;
    init_static_bit_vector(&(ASI_FLUSH_I_REGION), 8);
    bit_vector_clear(&ASI_FLUSH_I_REGION);
    ASI_FLUSH_I_REGION.val.byte_array[0] = 26;
    init_static_bit_vector(&(ASI_FLUSH_I_SEGMENT), 8);
    bit_vector_clear(&ASI_FLUSH_I_SEGMENT);
    ASI_FLUSH_I_SEGMENT.val.byte_array[0] = 25;
    init_static_bit_vector(&(ASI_FLUSH_I_USER), 8);
    bit_vector_clear(&ASI_FLUSH_I_USER);
    ASI_FLUSH_I_USER.val.byte_array[0] = 28;
    init_static_bit_vector(&(ASI_MMU_DIAGNOSTIC_I), 8);
    bit_vector_clear(&ASI_MMU_DIAGNOSTIC_I);
    ASI_MMU_DIAGNOSTIC_I.val.byte_array[0] = 5;
    init_static_bit_vector(&(ASI_MMU_DIAGNOSTIC_IO), 8);
    bit_vector_clear(&ASI_MMU_DIAGNOSTIC_IO);
    ASI_MMU_DIAGNOSTIC_IO.val.byte_array[0] = 7;
    init_static_bit_vector(&(ASI_MMU_DIAGNOSTIC_I_D), 8);
    bit_vector_clear(&ASI_MMU_DIAGNOSTIC_I_D);
    ASI_MMU_DIAGNOSTIC_I_D.val.byte_array[0] = 6;
    init_static_bit_vector(&(ASI_MMU_FLUSH_PROBE), 8);
    bit_vector_clear(&ASI_MMU_FLUSH_PROBE);
    ASI_MMU_FLUSH_PROBE.val.byte_array[0] = 3;
    init_static_bit_vector(&(ASI_MMU_REGISTER), 8);
    bit_vector_clear(&ASI_MMU_REGISTER);
    ASI_MMU_REGISTER.val.byte_array[0] = 4;
    init_static_bit_vector(&(ASI_SUPERVISOR_DATA), 8);
    bit_vector_clear(&ASI_SUPERVISOR_DATA);
    ASI_SUPERVISOR_DATA.val.byte_array[0] = 11;
    init_static_bit_vector(&(ASI_SUPERVISOR_INSTRUCTION), 8);
    bit_vector_clear(&ASI_SUPERVISOR_INSTRUCTION);
    ASI_SUPERVISOR_INSTRUCTION.val.byte_array[0] = 9;
    init_static_bit_vector(&(ASI_USER_DATA), 8);
    bit_vector_clear(&ASI_USER_DATA);
    ASI_USER_DATA.val.byte_array[0] = 10;
    init_static_bit_vector(&(ASI_USER_INSTRUCTION), 8);
    bit_vector_clear(&ASI_USER_INSTRUCTION);
    ASI_USER_INSTRUCTION.val.byte_array[0] = 8;
    init_static_bit_vector(&(CACHE_ARRAY_NOP), 3);
    bit_vector_clear(&CACHE_ARRAY_NOP);
    CACHE_ARRAY_NOP.val.byte_array[0] = 4;
    init_static_bit_vector(&(CACHE_ARRAY_READ_DWORD), 3);
    bit_vector_clear(&CACHE_ARRAY_READ_DWORD);
    CACHE_ARRAY_READ_DWORD.val.byte_array[0] = 1;
    init_static_bit_vector(&(CACHE_ARRAY_WRITE_DWORD), 3);
    bit_vector_clear(&CACHE_ARRAY_WRITE_DWORD);
    CACHE_ARRAY_WRITE_DWORD.val.byte_array[0] = 2;
    init_static_bit_vector(&(CACHE_ARRAY_WRITE_LINE), 3);
    bit_vector_clear(&CACHE_ARRAY_WRITE_LINE);
    CACHE_ARRAY_WRITE_LINE.val.byte_array[0] = 3;
    init_static_bit_vector(&(CACHE_TAG_CLEAR_ALL), 3);
    bit_vector_clear(&CACHE_TAG_CLEAR_ALL);
    CACHE_TAG_CLEAR_ALL.val.byte_array[0] = 4;
    init_static_bit_vector(&(CACHE_TAG_CLEAR_LINE), 3);
    bit_vector_clear(&CACHE_TAG_CLEAR_LINE);
    CACHE_TAG_CLEAR_LINE.val.byte_array[0] = 3;
    init_static_bit_vector(&(CACHE_TAG_INSERT), 3);
    bit_vector_clear(&CACHE_TAG_INSERT);
    CACHE_TAG_INSERT.val.byte_array[0] = 2;
    init_static_bit_vector(&(CACHE_TAG_LOOKUP), 3);
    bit_vector_clear(&CACHE_TAG_LOOKUP);
    CACHE_TAG_LOOKUP.val.byte_array[0] = 1;
    init_static_bit_vector(&(CACHE_TAG_NOP), 3);
    bit_vector_clear(&CACHE_TAG_NOP);
    CACHE_TAG_NOP.val.byte_array[0] = 5;
    register_pipe("CPU_to_DCACHE_addr", 2, 32, 0);
    register_pipe("CPU_to_DCACHE_asi", 2, 8, 0);
    register_pipe("CPU_to_DCACHE_byte_mask", 2, 8, 0);
    register_pipe("CPU_to_DCACHE_data", 2, 64, 0);
    register_pipe("CPU_to_DCACHE_request_type", 2, 8, 0);
    register_pipe("CPU_to_ICACHE_addr", 2, 32, 0);
    register_pipe("CPU_to_ICACHE_asi", 2, 8, 0);
    register_pipe("DCACHE_to_CPU_data", 2, 64, 0);
    register_pipe("DCACHE_to_CPU_mae", 2, 8, 0);
    register_pipe("DCACHE_to_CPU_response", 18, 8, 0);
    init_static_bit_vector(&(DEBUG_MODE_MASK), 8);
    bit_vector_clear(&DEBUG_MODE_MASK);
    DEBUG_MODE_MASK.val.byte_array[0] = 2;
    init_static_bit_vector(&(FOUR_3), 3);
    bit_vector_clear(&FOUR_3);
    FOUR_3.val.byte_array[0] = 4;
    init_static_bit_vector(&(GDB_DBG_CONNECT), 8);
    bit_vector_clear(&GDB_DBG_CONNECT);
    GDB_DBG_CONNECT.val.byte_array[0] = 14;
    init_static_bit_vector(&(GDB_DBG_CONTINUE), 8);
    bit_vector_clear(&GDB_DBG_CONTINUE);
    GDB_DBG_CONTINUE.val.byte_array[0] = 16;
    init_static_bit_vector(&(GDB_DBG_DETACH), 8);
    bit_vector_clear(&GDB_DBG_DETACH);
    GDB_DBG_DETACH.val.byte_array[0] = 15;
    init_static_bit_vector(&(GDB_DBG_KILL), 8);
    bit_vector_clear(&GDB_DBG_KILL);
    GDB_DBG_KILL.val.byte_array[0] = 19;
    init_static_bit_vector(&(GDB_DBG_READ_CONTROL_REG), 8);
    bit_vector_clear(&GDB_DBG_READ_CONTROL_REG);
    GDB_DBG_READ_CONTROL_REG.val.byte_array[0] = 13;
    init_static_bit_vector(&(GDB_DBG_READ_CPUNIT_REG), 8);
    bit_vector_clear(&GDB_DBG_READ_CPUNIT_REG);
    GDB_DBG_READ_CPUNIT_REG.val.byte_array[0] = 17;
    init_static_bit_vector(&(GDB_DBG_READ_FPUNIT_REG), 8);
    bit_vector_clear(&GDB_DBG_READ_FPUNIT_REG);
    GDB_DBG_READ_FPUNIT_REG.val.byte_array[0] = 3;
    init_static_bit_vector(&(GDB_DBG_READ_IUNIT_REG), 8);
    bit_vector_clear(&GDB_DBG_READ_IUNIT_REG);
    GDB_DBG_READ_IUNIT_REG.val.byte_array[0] = 1;
    init_static_bit_vector(&(GDB_DBG_READ_MEM), 8);
    bit_vector_clear(&GDB_DBG_READ_MEM);
    GDB_DBG_READ_MEM.val.byte_array[0] = 6;
    init_static_bit_vector(&(GDB_DBG_REMOVE_BREAK_POINT), 8);
    bit_vector_clear(&GDB_DBG_REMOVE_BREAK_POINT);
    GDB_DBG_REMOVE_BREAK_POINT.val.byte_array[0] = 9;
    init_static_bit_vector(&(GDB_DBG_REMOVE_WATCH_POINT), 8);
    bit_vector_clear(&GDB_DBG_REMOVE_WATCH_POINT);
    GDB_DBG_REMOVE_WATCH_POINT.val.byte_array[0] = 11;
    init_static_bit_vector(&(GDB_DBG_SET_BREAK_POINT), 8);
    bit_vector_clear(&GDB_DBG_SET_BREAK_POINT);
    GDB_DBG_SET_BREAK_POINT.val.byte_array[0] = 8;
    init_static_bit_vector(&(GDB_DBG_SET_WATCH_POINT), 8);
    bit_vector_clear(&GDB_DBG_SET_WATCH_POINT);
    GDB_DBG_SET_WATCH_POINT.val.byte_array[0] = 10;
    init_static_bit_vector(&(GDB_DBG_WRITE_CONTROL_REG), 8);
    bit_vector_clear(&GDB_DBG_WRITE_CONTROL_REG);
    GDB_DBG_WRITE_CONTROL_REG.val.byte_array[0] = 20;
    init_static_bit_vector(&(GDB_DBG_WRITE_CPUNIT_REG), 8);
    bit_vector_clear(&GDB_DBG_WRITE_CPUNIT_REG);
    GDB_DBG_WRITE_CPUNIT_REG.val.byte_array[0] = 18;
    init_static_bit_vector(&(GDB_DBG_WRITE_FPUNIT_REG), 8);
    bit_vector_clear(&GDB_DBG_WRITE_FPUNIT_REG);
    GDB_DBG_WRITE_FPUNIT_REG.val.byte_array[0] = 4;
    init_static_bit_vector(&(GDB_DBG_WRITE_IUNIT_REG), 8);
    bit_vector_clear(&GDB_DBG_WRITE_IUNIT_REG);
    GDB_DBG_WRITE_IUNIT_REG.val.byte_array[0] = 2;
    init_static_bit_vector(&(GDB_DBG_WRITE_MEM), 8);
    bit_vector_clear(&GDB_DBG_WRITE_MEM);
    GDB_DBG_WRITE_MEM.val.byte_array[0] = 7;
    init_static_bit_vector(&(HARD_RESET_MASK), 8);
    bit_vector_clear(&HARD_RESET_MASK);
    HARD_RESET_MASK.val.byte_array[0] = 1;
    register_pipe("ICACHE_to_CPU_fsr", 2, 32, 0);
    register_pipe("ICACHE_to_CPU_instr_pair", 2, 64, 0);
    register_pipe("ICACHE_to_CPU_mae", 2, 8, 0);
    register_pipe("ICACHE_to_CPU_response", 24, 8, 0);
    init_static_bit_vector(&(KILL_STREAM_MASK), 8);
    bit_vector_clear(&KILL_STREAM_MASK);
    KILL_STREAM_MASK.val.byte_array[0] = 128;
    init_static_bit_vector(&(KILL_THREAD_MASK), 8);
    bit_vector_clear(&KILL_THREAD_MASK);
    KILL_THREAD_MASK.val.byte_array[0] = 128;
    init_static_bit_vector(&(LOGGER_ACTIVE_MASK), 8);
    bit_vector_clear(&LOGGER_ACTIVE_MASK);
    LOGGER_ACTIVE_MASK.val.byte_array[0] = 8;
    init_static_bit_vector(&(MMU_PASS_THROUGH_HLIMIT), 8);
    bit_vector_clear(&MMU_PASS_THROUGH_HLIMIT);
    MMU_PASS_THROUGH_HLIMIT.val.byte_array[0] = 47;
    init_static_bit_vector(&(MMU_PASS_THROUGH_LLIMIT), 8);
    bit_vector_clear(&MMU_PASS_THROUGH_LLIMIT);
    MMU_PASS_THROUGH_LLIMIT.val.byte_array[0] = 32;
    init_static_bit_vector(&(MMU_READ_DWORD), 8);
    bit_vector_clear(&MMU_READ_DWORD);
    MMU_READ_DWORD.val.byte_array[0] = 2;
    init_static_bit_vector(&(MMU_READ_LINE), 8);
    bit_vector_clear(&MMU_READ_LINE);
    MMU_READ_LINE.val.byte_array[0] = 3;
    init_static_bit_vector(&(MMU_WRITE_DWORD), 8);
    bit_vector_clear(&MMU_WRITE_DWORD);
    MMU_WRITE_DWORD.val.byte_array[0] = 1;
    init_static_bit_vector(&(MMU_WRITE_DWORD_NO_RESPONSE), 8);
    bit_vector_clear(&MMU_WRITE_DWORD_NO_RESPONSE);
    MMU_WRITE_DWORD_NO_RESPONSE.val.byte_array[0] = 5;
    init_static_bit_vector(&(MMU_WRITE_FSR), 8);
    bit_vector_clear(&MMU_WRITE_FSR);
    MMU_WRITE_FSR.val.byte_array[0] = 4;
    init_static_bit_vector(&(NEW_STREAM_MASK), 8);
    bit_vector_clear(&NEW_STREAM_MASK);
    NEW_STREAM_MASK.val.byte_array[0] = 128;
    init_static_bit_vector(&(NEW_THREAD_MASK), 8);
    bit_vector_clear(&NEW_THREAD_MASK);
    NEW_THREAD_MASK.val.byte_array[0] = 128;
    register_pipe("NOBLOCK_CPU_to_DCACHE_command", 32, 8, 2);
    register_pipe("NOBLOCK_CPU_to_ICACHE_command", 12, 8, 2);
    init_static_bit_vector(&(NPC_RESET_VALUE), 32);
    bit_vector_clear(&NPC_RESET_VALUE);
    NPC_RESET_VALUE.val.byte_array[0] = 4;
    init_static_bit_vector(&(NWINDOWS), 32);
    bit_vector_clear(&NWINDOWS);
    NWINDOWS.val.byte_array[0] = 8;
    init_static_bit_vector(&(NWINDOWS_MOD_MASK_32), 32);
    bit_vector_clear(&NWINDOWS_MOD_MASK_32);
    NWINDOWS_MOD_MASK_32.val.byte_array[0] = 7;
    init_static_bit_vector(&(NWINDOWS_MOD_MASK_5), 5);
    bit_vector_clear(&NWINDOWS_MOD_MASK_5);
    NWINDOWS_MOD_MASK_5.val.byte_array[0] = 7;
    init_static_bit_vector(&(NWINDOWSx16), 32);
    bit_vector_clear(&NWINDOWSx16);
    NWINDOWSx16.val.byte_array[0] = 128;
    init_static_bit_vector(&(NWINDOWSx16_MOD_MASK_32), 32);
    bit_vector_clear(&NWINDOWSx16_MOD_MASK_32);
    NWINDOWSx16_MOD_MASK_32.val.byte_array[0] = 127;
    init_static_bit_vector(&(NWINDOWSx2), 32);
    bit_vector_clear(&NWINDOWSx2);
    NWINDOWSx2.val.byte_array[0] = 16;
    init_static_bit_vector(&(ONE_1), 1);
    bit_vector_clear(&ONE_1);
    ONE_1.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_10), 10);
    bit_vector_clear(&ONE_10);
    ONE_10.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_11), 11);
    bit_vector_clear(&ONE_11);
    ONE_11.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_12), 12);
    bit_vector_clear(&ONE_12);
    ONE_12.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_128), 128);
    bit_vector_clear(&ONE_128);
    ONE_128.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_13), 13);
    bit_vector_clear(&ONE_13);
    ONE_13.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_14), 14);
    bit_vector_clear(&ONE_14);
    ONE_14.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_16), 16);
    bit_vector_clear(&ONE_16);
    ONE_16.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_17), 17);
    bit_vector_clear(&ONE_17);
    ONE_17.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_18), 18);
    bit_vector_clear(&ONE_18);
    ONE_18.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_19), 19);
    bit_vector_clear(&ONE_19);
    ONE_19.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_2), 2);
    bit_vector_clear(&ONE_2);
    ONE_2.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_23), 23);
    bit_vector_clear(&ONE_23);
    ONE_23.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_24), 24);
    bit_vector_clear(&ONE_24);
    ONE_24.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_25), 25);
    bit_vector_clear(&ONE_25);
    ONE_25.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_256), 256);
    bit_vector_clear(&ONE_256);
    ONE_256.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_29), 29);
    bit_vector_clear(&ONE_29);
    ONE_29.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_3), 3);
    bit_vector_clear(&ONE_3);
    ONE_3.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_31), 31);
    bit_vector_clear(&ONE_31);
    ONE_31.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_32), 32);
    bit_vector_clear(&ONE_32);
    ONE_32.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_36), 36);
    bit_vector_clear(&ONE_36);
    ONE_36.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_4), 4);
    bit_vector_clear(&ONE_4);
    ONE_4.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_48), 48);
    bit_vector_clear(&ONE_48);
    ONE_48.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_5), 5);
    bit_vector_clear(&ONE_5);
    ONE_5.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_6), 6);
    bit_vector_clear(&ONE_6);
    ONE_6.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_64), 64);
    bit_vector_clear(&ONE_64);
    ONE_64.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_7), 7);
    bit_vector_clear(&ONE_7);
    ONE_7.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_8), 8);
    bit_vector_clear(&ONE_8);
    ONE_8.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_9), 9);
    bit_vector_clear(&ONE_9);
    ONE_9.val.byte_array[0] = 1;
    init_static_bit_vector(&(PC_RESET_VALUE), 32);
    bit_vector_clear(&PC_RESET_VALUE);
    init_static_bit_vector(&(PROCESSOR_ERROR_MODE), 2);
    bit_vector_clear(&PROCESSOR_ERROR_MODE);
    PROCESSOR_ERROR_MODE.val.byte_array[0] = 3;
    init_static_bit_vector(&(PROCESSOR_EXECUTE_MODE), 2);
    bit_vector_clear(&PROCESSOR_EXECUTE_MODE);
    PROCESSOR_EXECUTE_MODE.val.byte_array[0] = 2;
    init_static_bit_vector(&(PROCESSOR_RESET_MODE), 2);
    bit_vector_clear(&PROCESSOR_RESET_MODE);
    PROCESSOR_RESET_MODE.val.byte_array[0] = 1;
    init_static_bit_vector(&(PROCESSOR_UNDEFINED_MODE), 2);
    bit_vector_clear(&PROCESSOR_UNDEFINED_MODE);
    init_static_bit_vector(&(PSR_RESET_VALUE), 32);
    bit_vector_clear(&PSR_RESET_VALUE);
    PSR_RESET_VALUE.val.byte_array[0] = 192;
    PSR_RESET_VALUE.val.byte_array[1] = 16;
    init_static_bit_vector(&(REQUEST_TYPE_BRIDGE_CONFIG_READ), 4);
    bit_vector_clear(&REQUEST_TYPE_BRIDGE_CONFIG_READ);
    REQUEST_TYPE_BRIDGE_CONFIG_READ.val.byte_array[0] = 9;
    init_static_bit_vector(&(REQUEST_TYPE_BRIDGE_CONFIG_WRITE), 4);
    bit_vector_clear(&REQUEST_TYPE_BRIDGE_CONFIG_WRITE);
    REQUEST_TYPE_BRIDGE_CONFIG_WRITE.val.byte_array[0] = 8;
    init_static_bit_vector(&(REQUEST_TYPE_CCU_CACHE_READ), 4);
    bit_vector_clear(&REQUEST_TYPE_CCU_CACHE_READ);
    REQUEST_TYPE_CCU_CACHE_READ.val.byte_array[0] = 5;
    init_static_bit_vector(&(REQUEST_TYPE_CCU_CACHE_WRITE), 4);
    bit_vector_clear(&REQUEST_TYPE_CCU_CACHE_WRITE);
    REQUEST_TYPE_CCU_CACHE_WRITE.val.byte_array[0] = 6;
    init_static_bit_vector(&(REQUEST_TYPE_IFETCH), 4);
    bit_vector_clear(&REQUEST_TYPE_IFETCH);
    init_static_bit_vector(&(REQUEST_TYPE_NOP), 4);
    bit_vector_clear(&REQUEST_TYPE_NOP);
    REQUEST_TYPE_NOP.val.byte_array[0] = 7;
    init_static_bit_vector(&(REQUEST_TYPE_READ), 4);
    bit_vector_clear(&REQUEST_TYPE_READ);
    REQUEST_TYPE_READ.val.byte_array[0] = 1;
    init_static_bit_vector(&(REQUEST_TYPE_STBAR), 4);
    bit_vector_clear(&REQUEST_TYPE_STBAR);
    REQUEST_TYPE_STBAR.val.byte_array[0] = 3;
    init_static_bit_vector(&(REQUEST_TYPE_WRFSRFAR), 4);
    bit_vector_clear(&REQUEST_TYPE_WRFSRFAR);
    REQUEST_TYPE_WRFSRFAR.val.byte_array[0] = 4;
    init_static_bit_vector(&(REQUEST_TYPE_WRITE), 4);
    bit_vector_clear(&REQUEST_TYPE_WRITE);
    REQUEST_TYPE_WRITE.val.byte_array[0] = 2;
    init_static_bit_vector(&(SINGLE_STEP_MASK), 8);
    bit_vector_clear(&SINGLE_STEP_MASK);
    SINGLE_STEP_MASK.val.byte_array[0] = 4;
    init_static_bit_vector(&(THREE_2), 2);
    bit_vector_clear(&THREE_2);
    THREE_2.val.byte_array[0] = 3;
    init_static_bit_vector(&(THREE_3), 3);
    bit_vector_clear(&THREE_3);
    THREE_3.val.byte_array[0] = 3;
    init_static_bit_vector(&(TRACE_ON), 1);
    bit_vector_clear(&TRACE_ON);
    TRACE_ON.val.byte_array[0] = 1;
    init_static_bit_vector(&(TWO_2), 2);
    bit_vector_clear(&TWO_2);
    TWO_2.val.byte_array[0] = 2;
    init_static_bit_vector(&(TWO_3), 3);
    bit_vector_clear(&TWO_3);
    TWO_3.val.byte_array[0] = 2;
    init_static_bit_vector(&(WIM_MASK), 32);
    bit_vector_clear(&WIM_MASK);
    WIM_MASK.val.byte_array[0] = 255;
    init_static_bit_vector(&(ZERO_1), 1);
    bit_vector_clear(&ZERO_1);
    init_static_bit_vector(&(ZERO_10), 10);
    bit_vector_clear(&ZERO_10);
    init_static_bit_vector(&(ZERO_11), 11);
    bit_vector_clear(&ZERO_11);
    init_static_bit_vector(&(ZERO_12), 12);
    bit_vector_clear(&ZERO_12);
    init_static_bit_vector(&(ZERO_128), 128);
    bit_vector_clear(&ZERO_128);
    init_static_bit_vector(&(ZERO_13), 13);
    bit_vector_clear(&ZERO_13);
    init_static_bit_vector(&(ZERO_14), 14);
    bit_vector_clear(&ZERO_14);
    init_static_bit_vector(&(ZERO_16), 16);
    bit_vector_clear(&ZERO_16);
    init_static_bit_vector(&(ZERO_17), 17);
    bit_vector_clear(&ZERO_17);
    init_static_bit_vector(&(ZERO_18), 18);
    bit_vector_clear(&ZERO_18);
    init_static_bit_vector(&(ZERO_19), 19);
    bit_vector_clear(&ZERO_19);
    init_static_bit_vector(&(ZERO_2), 2);
    bit_vector_clear(&ZERO_2);
    init_static_bit_vector(&(ZERO_23), 23);
    bit_vector_clear(&ZERO_23);
    init_static_bit_vector(&(ZERO_24), 24);
    bit_vector_clear(&ZERO_24);
    init_static_bit_vector(&(ZERO_25), 25);
    bit_vector_clear(&ZERO_25);
    init_static_bit_vector(&(ZERO_256), 256);
    bit_vector_clear(&ZERO_256);
    init_static_bit_vector(&(ZERO_29), 29);
    bit_vector_clear(&ZERO_29);
    init_static_bit_vector(&(ZERO_3), 3);
    bit_vector_clear(&ZERO_3);
    init_static_bit_vector(&(ZERO_31), 31);
    bit_vector_clear(&ZERO_31);
    init_static_bit_vector(&(ZERO_32), 32);
    bit_vector_clear(&ZERO_32);
    init_static_bit_vector(&(ZERO_36), 36);
    bit_vector_clear(&ZERO_36);
    init_static_bit_vector(&(ZERO_4), 4);
    bit_vector_clear(&ZERO_4);
    init_static_bit_vector(&(ZERO_48), 48);
    bit_vector_clear(&ZERO_48);
    init_static_bit_vector(&(ZERO_5), 5);
    bit_vector_clear(&ZERO_5);
    init_static_bit_vector(&(ZERO_6), 6);
    bit_vector_clear(&ZERO_6);
    init_static_bit_vector(&(ZERO_64), 64);
    bit_vector_clear(&ZERO_64);
    init_static_bit_vector(&(ZERO_7), 7);
    bit_vector_clear(&ZERO_7);
    init_static_bit_vector(&(ZERO_8), 8);
    bit_vector_clear(&ZERO_8);
    init_static_bit_vector(&(ZERO_9), 9);
    bit_vector_clear(&ZERO_9);
    init_static_bit_vector(&(default_mem_pool[0]), 8);
}
void
_cache_c_interface__dcache_interface_daemon_()
{
    MUTEX_DECL
	(cache_c_interface___cache_c_interface__dcache_interface_daemon_series_block_stmt_519_c_mutex_);
    MUTEX_LOCK
	(cache_c_interface___cache_c_interface__dcache_interface_daemon_series_block_stmt_519_c_mutex_);
    cache_c_interface___dcache_interface_daemon_inner_inarg_prep_macro__;
    cache_c_interface___cache_c_interface__dcache_interface_daemon_branch_block_stmt_520_c_export_decl_macro_;
    {
	// merge file ./.Aa//linked.opt.aa, line 198
	cache_c_interface___cache_c_interface__dcache_interface_daemon_merge_stmt_521_c_preamble_macro_;
	cache_c_interface___cache_c_interface__dcache_interface_daemon_merge_stmt_521_c_postamble_macro_;
	// req_type := CPU_to_DCACHE_request_type
	cache_c_interface___cache_c_interface__dcache_interface_daemon_assign_stmt_524_c_macro_;
	// asi := CPU_to_DCACHE_asi
	cache_c_interface___cache_c_interface__dcache_interface_daemon_assign_stmt_527_c_macro_;
	// byte_mask := CPU_to_DCACHE_byte_mask
	cache_c_interface___cache_c_interface__dcache_interface_daemon_assign_stmt_530_c_macro_;
	// addr := CPU_to_DCACHE_addr
	cache_c_interface___cache_c_interface__dcache_interface_daemon_assign_stmt_533_c_macro_;
	// wdata := CPU_to_DCACHE_data
	cache_c_interface___cache_c_interface__dcache_interface_daemon_assign_stmt_536_c_macro_;
	// NOBLOCK_CPU_to_DCACHE_command := (((ONE_1 && req_type) && asi)
	// && ((byte_mask && addr) && wdata))
	cache_c_interface___cache_c_interface__dcache_interface_daemon_assign_stmt_549_c_macro_;
	// rsp := DCACHE_to_CPU_response
	cache_c_interface___cache_c_interface__dcache_interface_daemon_assign_stmt_552_c_macro_;
	// mae := ( $slice rsp 71 64 ) 
	cache_c_interface___cache_c_interface__dcache_interface_daemon_assign_stmt_556_c_macro_;
	// rdata := ( $slice rsp 63 0 ) 
	cache_c_interface___cache_c_interface__dcache_interface_daemon_assign_stmt_560_c_macro_;
	// DCACHE_to_CPU_mae := mae
	cache_c_interface___cache_c_interface__dcache_interface_daemon_assign_stmt_563_c_macro_;
	// DCACHE_to_CPU_data := rdata
	cache_c_interface___cache_c_interface__dcache_interface_daemon_assign_stmt_566_c_macro_;
	/*
	 * $place[loopback] 
	 */ goto loopback_520;
	cache_c_interface___cache_c_interface__dcache_interface_daemon_branch_block_stmt_520_c_export_apply_macro_;
    }
    cache_c_interface___dcache_interface_daemon_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(cache_c_interface___cache_c_interface__dcache_interface_daemon_series_block_stmt_519_c_mutex_);
}
void
cache_c_interface__dcache_interface_daemon()
{
    cache_c_interface___dcache_interface_daemon_outer_arg_decl_macro__;
    _cache_c_interface__dcache_interface_daemon_();
    cache_c_interface___dcache_interface_daemon_outer_op_xfer_macro__;
}


void
_cache_c_interface__global_storage_initializer__()
{
    MUTEX_DECL
	(cache_c_interface___cache_c_interface__global_storage_initializer__series_block_stmt_570_c_mutex_);
    MUTEX_LOCK
	(cache_c_interface___cache_c_interface__global_storage_initializer__series_block_stmt_570_c_mutex_);
    cache_c_interface___global_storage_initializer__inner_inarg_prep_macro__;
    /*
     * null 
     */ ;
    cache_c_interface___global_storage_initializer__inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(cache_c_interface___cache_c_interface__global_storage_initializer__series_block_stmt_570_c_mutex_);
}
void
cache_c_interface__global_storage_initializer_()
{
    cache_c_interface___global_storage_initializer__outer_arg_decl_macro__;
    _cache_c_interface__global_storage_initializer__();
    cache_c_interface___global_storage_initializer__outer_op_xfer_macro__;
}


void
_cache_c_interface__icache_interface_daemon_()
{
    MUTEX_DECL
	(cache_c_interface___cache_c_interface__icache_interface_daemon_series_block_stmt_573_c_mutex_);
    MUTEX_LOCK
	(cache_c_interface___cache_c_interface__icache_interface_daemon_series_block_stmt_573_c_mutex_);
    cache_c_interface___icache_interface_daemon_inner_inarg_prep_macro__;
    cache_c_interface___cache_c_interface__icache_interface_daemon_branch_block_stmt_574_c_export_decl_macro_;
    {
	// merge file ./.Aa//linked.opt.aa, line 228
	cache_c_interface___cache_c_interface__icache_interface_daemon_merge_stmt_575_c_preamble_macro_;
	cache_c_interface___cache_c_interface__icache_interface_daemon_merge_stmt_575_c_postamble_macro_;
	// asi := CPU_to_ICACHE_asi
	cache_c_interface___cache_c_interface__icache_interface_daemon_assign_stmt_578_c_macro_;
	// addr := CPU_to_ICACHE_addr
	cache_c_interface___cache_c_interface__icache_interface_daemon_assign_stmt_581_c_macro_;
	// NOBLOCK_CPU_to_ICACHE_command := ((ONE_1 && asi) && addr)
	cache_c_interface___cache_c_interface__icache_interface_daemon_assign_stmt_588_c_macro_;
	// rsp := ICACHE_to_CPU_response
	cache_c_interface___cache_c_interface__icache_interface_daemon_assign_stmt_591_c_macro_;
	// mmu_fsr := ( $slice rsp 89 72 ) 
	cache_c_interface___cache_c_interface__icache_interface_daemon_assign_stmt_595_c_macro_;
	// mae := ( $slice rsp 71 64 ) 
	cache_c_interface___cache_c_interface__icache_interface_daemon_assign_stmt_599_c_macro_;
	// ipair := ( $slice rsp 63 0 ) 
	cache_c_interface___cache_c_interface__icache_interface_daemon_assign_stmt_603_c_macro_;
	// ICACHE_to_CPU_mae := mae
	cache_c_interface___cache_c_interface__icache_interface_daemon_assign_stmt_606_c_macro_;
	// ICACHE_to_CPU_instr_pair := ipair
	cache_c_interface___cache_c_interface__icache_interface_daemon_assign_stmt_609_c_macro_;
	// ICACHE_to_CPU_fsr := ($bitcast ($uint<32>) mmu_fsr )
	cache_c_interface___cache_c_interface__icache_interface_daemon_assign_stmt_613_c_macro_;
	/*
	 * $place[loopback] 
	 */ goto loopback_574;
	cache_c_interface___cache_c_interface__icache_interface_daemon_branch_block_stmt_574_c_export_apply_macro_;
    }
    cache_c_interface___icache_interface_daemon_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(cache_c_interface___cache_c_interface__icache_interface_daemon_series_block_stmt_573_c_mutex_);
}
void
cache_c_interface__icache_interface_daemon()
{
    cache_c_interface___icache_interface_daemon_outer_arg_decl_macro__;
    _cache_c_interface__icache_interface_daemon_();
    cache_c_interface___icache_interface_daemon_outer_op_xfer_macro__;
}


void
_cache_c_interface__mem_load___(bit_vector * __paddress,
				bit_vector * __pdata)
{
    MUTEX_DECL
	(cache_c_interface___cache_c_interface__mem_load___series_block_stmt_617_c_mutex_);
    MUTEX_LOCK
	(cache_c_interface___cache_c_interface__mem_load___series_block_stmt_617_c_mutex_);
    cache_c_interface___mem_load___inner_inarg_prep_macro__;
    // data := default_mem_pool[((address * 1 ) + 0 )]
    cache_c_interface___cache_c_interface__mem_load___assign_stmt_627_c_macro_;
    cache_c_interface___mem_load___inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(cache_c_interface___cache_c_interface__mem_load___series_block_stmt_617_c_mutex_);
}
void
cache_c_interface__mem_load__(uint32_t address, uint8_t * data)
{
    cache_c_interface___mem_load___outer_arg_decl_macro__;
    _cache_c_interface__mem_load___(&__address, &__data);
    cache_c_interface___mem_load___outer_op_xfer_macro__;
}


void
_cache_c_interface__mem_store___(bit_vector * __paddress,
				 bit_vector * __pdata)
{
    MUTEX_DECL
	(cache_c_interface___cache_c_interface__mem_store___series_block_stmt_629_c_mutex_);
    MUTEX_LOCK
	(cache_c_interface___cache_c_interface__mem_store___series_block_stmt_629_c_mutex_);
    cache_c_interface___mem_store___inner_inarg_prep_macro__;
    // default_mem_pool[((address * 1 ) + 0 )] := data
    cache_c_interface___cache_c_interface__mem_store___assign_stmt_639_c_macro_;
    cache_c_interface___mem_store___inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(cache_c_interface___cache_c_interface__mem_store___series_block_stmt_629_c_mutex_);
}
void
cache_c_interface__mem_store__(uint32_t address, uint8_t data)
{
    cache_c_interface___mem_store___outer_arg_decl_macro__;
    _cache_c_interface__mem_store___(&__address, &__data);
    cache_c_interface___mem_store___outer_op_xfer_macro__;
}


DEFINE_THREAD(cache_c_interface__dcache_interface_daemon);
PTHREAD_DECL(cache_c_interface__dcache_interface_daemon);
DEFINE_THREAD(cache_c_interface__icache_interface_daemon);
PTHREAD_DECL(cache_c_interface__icache_interface_daemon);
void
cache_c_interface__start_daemons(FILE * fp)
{
    cache_c_interface____report_log_file__ = fp;
    cache_c_interface____init_aa_globals__();
    PTHREAD_CREATE(cache_c_interface__dcache_interface_daemon);
    PTHREAD_CREATE(cache_c_interface__icache_interface_daemon);
}
void
cache_c_interface__stop_daemons()
{
    PTHREAD_CANCEL(cache_c_interface__dcache_interface_daemon);
    PTHREAD_CANCEL(cache_c_interface__icache_interface_daemon);
}
