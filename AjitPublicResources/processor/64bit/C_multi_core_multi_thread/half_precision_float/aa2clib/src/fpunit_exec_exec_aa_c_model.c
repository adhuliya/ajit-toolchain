#include <pthread.h>
#include <pthreadUtils.h>
#include <Pipes.h>
#include <fpunit_exec_exec_aa_c_model_internal.h>
#include <fpunit_exec_exec_aa_c_model.h>
FILE           *fpunit_exec_exec___report_log_file__ = NULL;
int             fpunit_exec_exec___trace_on__ = 0;
void
fpunit_exec_exec__set_trace_file(FILE * fp)
{
    fpunit_exec_exec___report_log_file__ = fp;
}
bit_vector      fpunit_exec_exec__ACCESS_ASR;
#define ACCESS_ASR (fpunit_exec_exec__ACCESS_ASR)

bit_vector      fpunit_exec_exec__ACCESS_PSR;
#define ACCESS_PSR (fpunit_exec_exec__ACCESS_PSR)

bit_vector      fpunit_exec_exec__ACCESS_REG;
#define ACCESS_REG (fpunit_exec_exec__ACCESS_REG)

bit_vector      fpunit_exec_exec__ACCESS_TBR;
#define ACCESS_TBR (fpunit_exec_exec__ACCESS_TBR)

bit_vector      fpunit_exec_exec__ACCESS_WIM;
#define ACCESS_WIM (fpunit_exec_exec__ACCESS_WIM)

bit_vector      fpunit_exec_exec__ACCESS_Y;
#define ACCESS_Y (fpunit_exec_exec__ACCESS_Y)

bit_vector      fpunit_exec_exec__ALL_ONE_11;
#define ALL_ONE_11 (fpunit_exec_exec__ALL_ONE_11)

bit_vector      fpunit_exec_exec__ALL_ONE_13;
#define ALL_ONE_13 (fpunit_exec_exec__ALL_ONE_13)

bit_vector      fpunit_exec_exec__ALL_ONE_8;
#define ALL_ONE_8 (fpunit_exec_exec__ALL_ONE_8)

bit_vector      fpunit_exec_exec__ALU_INSTR;
#define ALU_INSTR (fpunit_exec_exec__ALU_INSTR)

bit_vector      fpunit_exec_exec__ANNUL_TRAP_BIT_VEC;
#define ANNUL_TRAP_BIT_VEC (fpunit_exec_exec__ANNUL_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__ANNUL_TRAP_INDEX;
#define ANNUL_TRAP_INDEX (fpunit_exec_exec__ANNUL_TRAP_INDEX)

bit_vector      fpunit_exec_exec__ASI_AJIT_BRIDGE_CONFIG;
#define ASI_AJIT_BRIDGE_CONFIG (fpunit_exec_exec__ASI_AJIT_BRIDGE_CONFIG)

bit_vector      fpunit_exec_exec__ASI_BLOCK_COPY;
#define ASI_BLOCK_COPY (fpunit_exec_exec__ASI_BLOCK_COPY)

bit_vector      fpunit_exec_exec__ASI_BLOCK_FILL;
#define ASI_BLOCK_FILL (fpunit_exec_exec__ASI_BLOCK_FILL)

bit_vector      fpunit_exec_exec__ASI_CACHE_DATA_I;
#define ASI_CACHE_DATA_I (fpunit_exec_exec__ASI_CACHE_DATA_I)

bit_vector      fpunit_exec_exec__ASI_CACHE_DATA_I_D;
#define ASI_CACHE_DATA_I_D (fpunit_exec_exec__ASI_CACHE_DATA_I_D)

bit_vector      fpunit_exec_exec__ASI_CACHE_TAG_I;
#define ASI_CACHE_TAG_I (fpunit_exec_exec__ASI_CACHE_TAG_I)

bit_vector      fpunit_exec_exec__ASI_CACHE_TAG_I_D;
#define ASI_CACHE_TAG_I_D (fpunit_exec_exec__ASI_CACHE_TAG_I_D)

bit_vector      fpunit_exec_exec__ASI_FLUSH_I_CONTEXT;
#define ASI_FLUSH_I_CONTEXT (fpunit_exec_exec__ASI_FLUSH_I_CONTEXT)

bit_vector      fpunit_exec_exec__ASI_FLUSH_I_D_CONTEXT;
#define ASI_FLUSH_I_D_CONTEXT (fpunit_exec_exec__ASI_FLUSH_I_D_CONTEXT)

bit_vector      fpunit_exec_exec__ASI_FLUSH_I_D_PAGE;
#define ASI_FLUSH_I_D_PAGE (fpunit_exec_exec__ASI_FLUSH_I_D_PAGE)

bit_vector      fpunit_exec_exec__ASI_FLUSH_I_D_REGION;
#define ASI_FLUSH_I_D_REGION (fpunit_exec_exec__ASI_FLUSH_I_D_REGION)

bit_vector      fpunit_exec_exec__ASI_FLUSH_I_D_SEGMENT;
#define ASI_FLUSH_I_D_SEGMENT (fpunit_exec_exec__ASI_FLUSH_I_D_SEGMENT)

bit_vector      fpunit_exec_exec__ASI_FLUSH_I_D_USER;
#define ASI_FLUSH_I_D_USER (fpunit_exec_exec__ASI_FLUSH_I_D_USER)

bit_vector      fpunit_exec_exec__ASI_FLUSH_I_PAGE;
#define ASI_FLUSH_I_PAGE (fpunit_exec_exec__ASI_FLUSH_I_PAGE)

bit_vector      fpunit_exec_exec__ASI_FLUSH_I_REGION;
#define ASI_FLUSH_I_REGION (fpunit_exec_exec__ASI_FLUSH_I_REGION)

bit_vector      fpunit_exec_exec__ASI_FLUSH_I_SEGMENT;
#define ASI_FLUSH_I_SEGMENT (fpunit_exec_exec__ASI_FLUSH_I_SEGMENT)

bit_vector      fpunit_exec_exec__ASI_FLUSH_I_USER;
#define ASI_FLUSH_I_USER (fpunit_exec_exec__ASI_FLUSH_I_USER)

bit_vector      fpunit_exec_exec__ASI_MMU_DIAGNOSTIC_I;
#define ASI_MMU_DIAGNOSTIC_I (fpunit_exec_exec__ASI_MMU_DIAGNOSTIC_I)

bit_vector      fpunit_exec_exec__ASI_MMU_DIAGNOSTIC_IO;
#define ASI_MMU_DIAGNOSTIC_IO (fpunit_exec_exec__ASI_MMU_DIAGNOSTIC_IO)

bit_vector      fpunit_exec_exec__ASI_MMU_DIAGNOSTIC_I_D;
#define ASI_MMU_DIAGNOSTIC_I_D (fpunit_exec_exec__ASI_MMU_DIAGNOSTIC_I_D)

bit_vector      fpunit_exec_exec__ASI_MMU_FLUSH_PROBE;
#define ASI_MMU_FLUSH_PROBE (fpunit_exec_exec__ASI_MMU_FLUSH_PROBE)

bit_vector      fpunit_exec_exec__ASI_MMU_REGISTER;
#define ASI_MMU_REGISTER (fpunit_exec_exec__ASI_MMU_REGISTER)

bit_vector      fpunit_exec_exec__ASI_SUPERVISOR_DATA;
#define ASI_SUPERVISOR_DATA (fpunit_exec_exec__ASI_SUPERVISOR_DATA)

bit_vector      fpunit_exec_exec__ASI_SUPERVISOR_INSTRUCTION;
#define ASI_SUPERVISOR_INSTRUCTION (fpunit_exec_exec__ASI_SUPERVISOR_INSTRUCTION)

bit_vector      fpunit_exec_exec__ASI_USER_DATA;
#define ASI_USER_DATA (fpunit_exec_exec__ASI_USER_DATA)

bit_vector      fpunit_exec_exec__ASI_USER_INSTRUCTION;
#define ASI_USER_INSTRUCTION (fpunit_exec_exec__ASI_USER_INSTRUCTION)

bit_vector      fpunit_exec_exec__BLOCK_READ;
#define BLOCK_READ (fpunit_exec_exec__BLOCK_READ)

bit_vector      fpunit_exec_exec__CACHE_ARRAY_NOP;
#define CACHE_ARRAY_NOP (fpunit_exec_exec__CACHE_ARRAY_NOP)

bit_vector      fpunit_exec_exec__CACHE_ARRAY_READ_DWORD;
#define CACHE_ARRAY_READ_DWORD (fpunit_exec_exec__CACHE_ARRAY_READ_DWORD)

bit_vector      fpunit_exec_exec__CACHE_ARRAY_WRITE_DWORD;
#define CACHE_ARRAY_WRITE_DWORD (fpunit_exec_exec__CACHE_ARRAY_WRITE_DWORD)

bit_vector      fpunit_exec_exec__CACHE_TAG_CLEAR_ALL;
#define CACHE_TAG_CLEAR_ALL (fpunit_exec_exec__CACHE_TAG_CLEAR_ALL)

bit_vector      fpunit_exec_exec__CACHE_TAG_CLEAR_LINE;
#define CACHE_TAG_CLEAR_LINE (fpunit_exec_exec__CACHE_TAG_CLEAR_LINE)

bit_vector      fpunit_exec_exec__CACHE_TAG_INSERT;
#define CACHE_TAG_INSERT (fpunit_exec_exec__CACHE_TAG_INSERT)

bit_vector      fpunit_exec_exec__CACHE_TAG_LOOKUP;
#define CACHE_TAG_LOOKUP (fpunit_exec_exec__CACHE_TAG_LOOKUP)

bit_vector      fpunit_exec_exec__CACHE_TAG_NOP;
#define CACHE_TAG_NOP (fpunit_exec_exec__CACHE_TAG_NOP)

bit_vector      fpunit_exec_exec__CCU_DBG_BP_HIT;
#define CCU_DBG_BP_HIT (fpunit_exec_exec__CCU_DBG_BP_HIT)

bit_vector      fpunit_exec_exec__CCU_DBG_CONNECT_RQST;
#define CCU_DBG_CONNECT_RQST (fpunit_exec_exec__CCU_DBG_CONNECT_RQST)

bit_vector      fpunit_exec_exec__CCU_DBG_ERROR;
#define CCU_DBG_ERROR (fpunit_exec_exec__CCU_DBG_ERROR)

bit_vector      fpunit_exec_exec__CCU_DBG_ERROR_MODE;
#define CCU_DBG_ERROR_MODE (fpunit_exec_exec__CCU_DBG_ERROR_MODE)

bit_vector      fpunit_exec_exec__CCU_DBG_OK;
#define CCU_DBG_OK (fpunit_exec_exec__CCU_DBG_OK)

bit_vector      fpunit_exec_exec__CCU_DBG_READ_RESPONSE;
#define CCU_DBG_READ_RESPONSE (fpunit_exec_exec__CCU_DBG_READ_RESPONSE)

bit_vector      fpunit_exec_exec__CCU_DBG_READ_WP_HIT;
#define CCU_DBG_READ_WP_HIT (fpunit_exec_exec__CCU_DBG_READ_WP_HIT)

bit_vector      fpunit_exec_exec__CCU_DBG_THREAD_FINISH;
#define CCU_DBG_THREAD_FINISH (fpunit_exec_exec__CCU_DBG_THREAD_FINISH)

bit_vector      fpunit_exec_exec__CCU_DBG_WRITE_WP_HIT;
#define CCU_DBG_WRITE_WP_HIT (fpunit_exec_exec__CCU_DBG_WRITE_WP_HIT)

bit_vector      fpunit_exec_exec__CCU_TEU_CLEAR_BP;
#define CCU_TEU_CLEAR_BP (fpunit_exec_exec__CCU_TEU_CLEAR_BP)

bit_vector      fpunit_exec_exec__CCU_TEU_CLEAR_WP;
#define CCU_TEU_CLEAR_WP (fpunit_exec_exec__CCU_TEU_CLEAR_WP)

bit_vector      fpunit_exec_exec__CCU_TEU_INTR;
#define CCU_TEU_INTR (fpunit_exec_exec__CCU_TEU_INTR)

bit_vector      fpunit_exec_exec__CCU_TEU_SET_BP;
#define CCU_TEU_SET_BP (fpunit_exec_exec__CCU_TEU_SET_BP)

bit_vector      fpunit_exec_exec__CCU_TEU_SET_WP;
#define CCU_TEU_SET_WP (fpunit_exec_exec__CCU_TEU_SET_WP)

bit_vector      fpunit_exec_exec__CONTINUES_MISPREDICTED_STREAM;
#define CONTINUES_MISPREDICTED_STREAM (fpunit_exec_exec__CONTINUES_MISPREDICTED_STREAM)

bit_vector      fpunit_exec_exec__CONTINUES_TRAPPED_STREAM;
#define CONTINUES_TRAPPED_STREAM (fpunit_exec_exec__CONTINUES_TRAPPED_STREAM)

bit_vector      fpunit_exec_exec__CONTROL_TRANSFER_INSTR;
#define CONTROL_TRANSFER_INSTR (fpunit_exec_exec__CONTROL_TRANSFER_INSTR)

bit_vector      fpunit_exec_exec__CP_DISABLED_TRAP_BIT_VEC;
#define CP_DISABLED_TRAP_BIT_VEC (fpunit_exec_exec__CP_DISABLED_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__CP_DISABLED_TRAP_INDEX;
#define CP_DISABLED_TRAP_INDEX (fpunit_exec_exec__CP_DISABLED_TRAP_INDEX)

bit_vector      fpunit_exec_exec__CP_EXCEPTION_TRAP_BIT_VEC;
#define CP_EXCEPTION_TRAP_BIT_VEC (fpunit_exec_exec__CP_EXCEPTION_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__CP_EXCEPTION_TRAP_INDEX;
#define CP_EXCEPTION_TRAP_INDEX (fpunit_exec_exec__CP_EXCEPTION_TRAP_INDEX)

bit_vector      fpunit_exec_exec__CP_INSTR;
#define CP_INSTR (fpunit_exec_exec__CP_INSTR)

bit_vector      fpunit_exec_exec__DATA_ACCESS_ERROR_TRAP_BIT_VEC;
#define DATA_ACCESS_ERROR_TRAP_BIT_VEC (fpunit_exec_exec__DATA_ACCESS_ERROR_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__DATA_ACCESS_ERROR_TRAP_INDEX;
#define DATA_ACCESS_ERROR_TRAP_INDEX (fpunit_exec_exec__DATA_ACCESS_ERROR_TRAP_INDEX)

bit_vector      fpunit_exec_exec__DATA_ACCESS_EXCEPTION_TRAP_BIT_VEC;
#define DATA_ACCESS_EXCEPTION_TRAP_BIT_VEC (fpunit_exec_exec__DATA_ACCESS_EXCEPTION_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__DATA_ACCESS_EXCEPTION_TRAP_INDEX;
#define DATA_ACCESS_EXCEPTION_TRAP_INDEX (fpunit_exec_exec__DATA_ACCESS_EXCEPTION_TRAP_INDEX)

bit_vector      fpunit_exec_exec__DATA_STORE_ERROR_TRAP_BIT_VEC;
#define DATA_STORE_ERROR_TRAP_BIT_VEC (fpunit_exec_exec__DATA_STORE_ERROR_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__DATA_STORE_ERROR_TRAP_INDEX;
#define DATA_STORE_ERROR_TRAP_INDEX (fpunit_exec_exec__DATA_STORE_ERROR_TRAP_INDEX)

bit_vector      fpunit_exec_exec__DATA_TRANSFER_INSTR;
#define DATA_TRANSFER_INSTR (fpunit_exec_exec__DATA_TRANSFER_INSTR)

bit_vector      fpunit_exec_exec__DEBUG_MODE_MASK;
#define DEBUG_MODE_MASK (fpunit_exec_exec__DEBUG_MODE_MASK)

bit_vector      fpunit_exec_exec__DENORM;
#define DENORM (fpunit_exec_exec__DENORM)

bit_vector      fpunit_exec_exec__DIVISION_BY_ZERO_TRAP_BIT_VEC;
#define DIVISION_BY_ZERO_TRAP_BIT_VEC (fpunit_exec_exec__DIVISION_BY_ZERO_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__DIVISION_BY_ZERO_TRAP_INDEX;
#define DIVISION_BY_ZERO_TRAP_INDEX (fpunit_exec_exec__DIVISION_BY_ZERO_TRAP_INDEX)

bit_vector      fpunit_exec_exec__DP_round_mid;
#define DP_round_mid (fpunit_exec_exec__DP_round_mid)

bit_vector      fpunit_exec_exec__EXCEPTION_FOUND;
#define EXCEPTION_FOUND (fpunit_exec_exec__EXCEPTION_FOUND)

bit_vector      fpunit_exec_exec__FOUR_3;
#define FOUR_3 (fpunit_exec_exec__FOUR_3)

bit_vector      fpunit_exec_exec__FP_DISABLED_TRAP_BIT_VEC;
#define FP_DISABLED_TRAP_BIT_VEC (fpunit_exec_exec__FP_DISABLED_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__FP_DISABLED_TRAP_INDEX;
#define FP_DISABLED_TRAP_INDEX (fpunit_exec_exec__FP_DISABLED_TRAP_INDEX)

bit_vector      fpunit_exec_exec__FP_EXCEPTION_TRAP_BIT_VEC;
#define FP_EXCEPTION_TRAP_BIT_VEC (fpunit_exec_exec__FP_EXCEPTION_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__FP_EXCEPTION_TRAP_INDEX;
#define FP_EXCEPTION_TRAP_INDEX (fpunit_exec_exec__FP_EXCEPTION_TRAP_INDEX)

bit_vector      fpunit_exec_exec__FP_INSTR;
#define FP_INSTR (fpunit_exec_exec__FP_INSTR)

bit_vector      fpunit_exec_exec__FRACTION_WIDTH_23;
#define FRACTION_WIDTH_23 (fpunit_exec_exec__FRACTION_WIDTH_23)

bit_vector      fpunit_exec_exec__FRACTION_WIDTH_52;
#define FRACTION_WIDTH_52 (fpunit_exec_exec__FRACTION_WIDTH_52)

bit_vector      fpunit_exec_exec__GDB_DBG_CONNECT;
#define GDB_DBG_CONNECT (fpunit_exec_exec__GDB_DBG_CONNECT)

bit_vector      fpunit_exec_exec__GDB_DBG_CONTINUE;
#define GDB_DBG_CONTINUE (fpunit_exec_exec__GDB_DBG_CONTINUE)

bit_vector      fpunit_exec_exec__GDB_DBG_DETACH;
#define GDB_DBG_DETACH (fpunit_exec_exec__GDB_DBG_DETACH)

bit_vector      fpunit_exec_exec__GDB_DBG_KILL;
#define GDB_DBG_KILL (fpunit_exec_exec__GDB_DBG_KILL)

bit_vector      fpunit_exec_exec__GDB_DBG_READ_CONTROL_REG;
#define GDB_DBG_READ_CONTROL_REG (fpunit_exec_exec__GDB_DBG_READ_CONTROL_REG)

bit_vector      fpunit_exec_exec__GDB_DBG_READ_CPUNIT_REG;
#define GDB_DBG_READ_CPUNIT_REG (fpunit_exec_exec__GDB_DBG_READ_CPUNIT_REG)

bit_vector      fpunit_exec_exec__GDB_DBG_READ_FPUNIT_REG;
#define GDB_DBG_READ_FPUNIT_REG (fpunit_exec_exec__GDB_DBG_READ_FPUNIT_REG)

bit_vector      fpunit_exec_exec__GDB_DBG_READ_INIT_NPC;
#define GDB_DBG_READ_INIT_NPC (fpunit_exec_exec__GDB_DBG_READ_INIT_NPC)

bit_vector      fpunit_exec_exec__GDB_DBG_READ_INIT_PC;
#define GDB_DBG_READ_INIT_PC (fpunit_exec_exec__GDB_DBG_READ_INIT_PC)

bit_vector      fpunit_exec_exec__GDB_DBG_READ_INIT_PSR;
#define GDB_DBG_READ_INIT_PSR (fpunit_exec_exec__GDB_DBG_READ_INIT_PSR)

bit_vector      fpunit_exec_exec__GDB_DBG_READ_IUNIT_REG;
#define GDB_DBG_READ_IUNIT_REG (fpunit_exec_exec__GDB_DBG_READ_IUNIT_REG)

bit_vector      fpunit_exec_exec__GDB_DBG_READ_MEM;
#define GDB_DBG_READ_MEM (fpunit_exec_exec__GDB_DBG_READ_MEM)

bit_vector      fpunit_exec_exec__GDB_DBG_READ_MODE;
#define GDB_DBG_READ_MODE (fpunit_exec_exec__GDB_DBG_READ_MODE)

bit_vector      fpunit_exec_exec__GDB_DBG_REMOVE_BREAK_POINT;
#define GDB_DBG_REMOVE_BREAK_POINT (fpunit_exec_exec__GDB_DBG_REMOVE_BREAK_POINT)

bit_vector      fpunit_exec_exec__GDB_DBG_REMOVE_WATCH_POINT;
#define GDB_DBG_REMOVE_WATCH_POINT (fpunit_exec_exec__GDB_DBG_REMOVE_WATCH_POINT)

bit_vector      fpunit_exec_exec__GDB_DBG_SET_BREAK_POINT;
#define GDB_DBG_SET_BREAK_POINT (fpunit_exec_exec__GDB_DBG_SET_BREAK_POINT)

bit_vector      fpunit_exec_exec__GDB_DBG_SET_WATCH_POINT;
#define GDB_DBG_SET_WATCH_POINT (fpunit_exec_exec__GDB_DBG_SET_WATCH_POINT)

bit_vector      fpunit_exec_exec__GDB_DBG_WRITE_CONTROL_REG;
#define GDB_DBG_WRITE_CONTROL_REG (fpunit_exec_exec__GDB_DBG_WRITE_CONTROL_REG)

bit_vector      fpunit_exec_exec__GDB_DBG_WRITE_CPUNIT_REG;
#define GDB_DBG_WRITE_CPUNIT_REG (fpunit_exec_exec__GDB_DBG_WRITE_CPUNIT_REG)

bit_vector      fpunit_exec_exec__GDB_DBG_WRITE_FPUNIT_REG;
#define GDB_DBG_WRITE_FPUNIT_REG (fpunit_exec_exec__GDB_DBG_WRITE_FPUNIT_REG)

bit_vector      fpunit_exec_exec__GDB_DBG_WRITE_INIT_NPC;
#define GDB_DBG_WRITE_INIT_NPC (fpunit_exec_exec__GDB_DBG_WRITE_INIT_NPC)

bit_vector      fpunit_exec_exec__GDB_DBG_WRITE_INIT_PC;
#define GDB_DBG_WRITE_INIT_PC (fpunit_exec_exec__GDB_DBG_WRITE_INIT_PC)

bit_vector      fpunit_exec_exec__GDB_DBG_WRITE_INIT_PSR;
#define GDB_DBG_WRITE_INIT_PSR (fpunit_exec_exec__GDB_DBG_WRITE_INIT_PSR)

bit_vector      fpunit_exec_exec__GDB_DBG_WRITE_IUNIT_REG;
#define GDB_DBG_WRITE_IUNIT_REG (fpunit_exec_exec__GDB_DBG_WRITE_IUNIT_REG)

bit_vector      fpunit_exec_exec__GDB_DBG_WRITE_MEM;
#define GDB_DBG_WRITE_MEM (fpunit_exec_exec__GDB_DBG_WRITE_MEM)

bit_vector      fpunit_exec_exec__GDB_DBG_WRITE_RESET;
#define GDB_DBG_WRITE_RESET (fpunit_exec_exec__GDB_DBG_WRITE_RESET)

bit_vector      fpunit_exec_exec__HARDWARE_ERROR_TRAP_BIT_VEC;
#define HARDWARE_ERROR_TRAP_BIT_VEC (fpunit_exec_exec__HARDWARE_ERROR_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__HARDWARE_ERROR_TRAP_INDEX;
#define HARDWARE_ERROR_TRAP_INDEX (fpunit_exec_exec__HARDWARE_ERROR_TRAP_INDEX)

bit_vector      fpunit_exec_exec__HARD_RESET_MASK;
#define HARD_RESET_MASK (fpunit_exec_exec__HARD_RESET_MASK)

bit_vector      fpunit_exec_exec__IEEE_754_EXCEPTION_TRAP_BIT_VEC;
#define IEEE_754_EXCEPTION_TRAP_BIT_VEC (fpunit_exec_exec__IEEE_754_EXCEPTION_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__IEEE_754_EXCEPTION_TRAP_INDEX;
#define IEEE_754_EXCEPTION_TRAP_INDEX (fpunit_exec_exec__IEEE_754_EXCEPTION_TRAP_INDEX)

bit_vector      fpunit_exec_exec__ILLEGAL_INSTR;
#define ILLEGAL_INSTR (fpunit_exec_exec__ILLEGAL_INSTR)

bit_vector      fpunit_exec_exec__ILLEGAL_INSTRUCTION_TRAP_BIT_VEC;
#define ILLEGAL_INSTRUCTION_TRAP_BIT_VEC (fpunit_exec_exec__ILLEGAL_INSTRUCTION_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__ILLEGAL_INSTRUCTION_TRAP_INDEX;
#define ILLEGAL_INSTRUCTION_TRAP_INDEX (fpunit_exec_exec__ILLEGAL_INSTRUCTION_TRAP_INDEX)

bit_vector      fpunit_exec_exec__ILLEGAL_IU_INSTRUCTION_TRAP_BIT_VEC;
#define ILLEGAL_IU_INSTRUCTION_TRAP_BIT_VEC (fpunit_exec_exec__ILLEGAL_IU_INSTRUCTION_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__ILLEGAL_IU_INSTRUCTION_TRAP_INDEX;
#define ILLEGAL_IU_INSTRUCTION_TRAP_INDEX (fpunit_exec_exec__ILLEGAL_IU_INSTRUCTION_TRAP_INDEX)

bit_vector      fpunit_exec_exec__INIT_ASR_AND_WINDOW_REGS;
#define INIT_ASR_AND_WINDOW_REGS (fpunit_exec_exec__INIT_ASR_AND_WINDOW_REGS)

bit_vector      fpunit_exec_exec__INSTRUCTION_ACCESS_ERROR_TRAP_BIT_VEC;
#define INSTRUCTION_ACCESS_ERROR_TRAP_BIT_VEC (fpunit_exec_exec__INSTRUCTION_ACCESS_ERROR_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__INSTRUCTION_ACCESS_ERROR_TRAP_INDEX;
#define INSTRUCTION_ACCESS_ERROR_TRAP_INDEX (fpunit_exec_exec__INSTRUCTION_ACCESS_ERROR_TRAP_INDEX)

bit_vector     
    fpunit_exec_exec__INSTRUCTION_ACCESS_EXCEPTION_TRAP_BIT_VEC;
#define INSTRUCTION_ACCESS_EXCEPTION_TRAP_BIT_VEC (fpunit_exec_exec__INSTRUCTION_ACCESS_EXCEPTION_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__INSTRUCTION_ACCESS_EXCEPTION_TRAP_INDEX;
#define INSTRUCTION_ACCESS_EXCEPTION_TRAP_INDEX (fpunit_exec_exec__INSTRUCTION_ACCESS_EXCEPTION_TRAP_INDEX)

bit_vector      fpunit_exec_exec__INTERRUPT_FOUND;
#define INTERRUPT_FOUND (fpunit_exec_exec__INTERRUPT_FOUND)

bit_vector      fpunit_exec_exec__INVALID_FP_REGISTER_TRAP_BIT_VEC;
#define INVALID_FP_REGISTER_TRAP_BIT_VEC (fpunit_exec_exec__INVALID_FP_REGISTER_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__INVALID_FP_REGISTER_TRAP_INDEX;
#define INVALID_FP_REGISTER_TRAP_INDEX (fpunit_exec_exec__INVALID_FP_REGISTER_TRAP_INDEX)

bit_vector      fpunit_exec_exec__IN_LIVE_STREAM_ANNULLED;
#define IN_LIVE_STREAM_ANNULLED (fpunit_exec_exec__IN_LIVE_STREAM_ANNULLED)

bit_vector      fpunit_exec_exec__IN_LIVE_STREAM_NOT_ANNULLED;
#define IN_LIVE_STREAM_NOT_ANNULLED (fpunit_exec_exec__IN_LIVE_STREAM_NOT_ANNULLED)

bit_vector      fpunit_exec_exec__KILL_STREAM_MASK;
#define KILL_STREAM_MASK (fpunit_exec_exec__KILL_STREAM_MASK)

bit_vector      fpunit_exec_exec__KILL_THREAD_MASK;
#define KILL_THREAD_MASK (fpunit_exec_exec__KILL_THREAD_MASK)

bit_vector      fpunit_exec_exec__LOGGER_ACTIVE_MASK;
#define LOGGER_ACTIVE_MASK (fpunit_exec_exec__LOGGER_ACTIVE_MASK)

bit_vector      fpunit_exec_exec__MACHINE_ERROR;
#define MACHINE_ERROR (fpunit_exec_exec__MACHINE_ERROR)

bit_vector      fpunit_exec_exec__MAE_TRAP_BIT_VEC;
#define MAE_TRAP_BIT_VEC (fpunit_exec_exec__MAE_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__MAE_TRAP_INDEX;
#define MAE_TRAP_INDEX (fpunit_exec_exec__MAE_TRAP_INDEX)

bit_vector      fpunit_exec_exec__MEM_ADDRESS_NOT_ALIGNED_TRAP_BIT_VEC;
#define MEM_ADDRESS_NOT_ALIGNED_TRAP_BIT_VEC (fpunit_exec_exec__MEM_ADDRESS_NOT_ALIGNED_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__MEM_ADDRESS_NOT_ALIGNED_TRAP_INDEX;
#define MEM_ADDRESS_NOT_ALIGNED_TRAP_INDEX (fpunit_exec_exec__MEM_ADDRESS_NOT_ALIGNED_TRAP_INDEX)

bit_vector      fpunit_exec_exec__MISC_INSTR;
#define MISC_INSTR (fpunit_exec_exec__MISC_INSTR)

bit_vector      fpunit_exec_exec__MMU_PASS_THROUGH_HLIMIT;
#define MMU_PASS_THROUGH_HLIMIT (fpunit_exec_exec__MMU_PASS_THROUGH_HLIMIT)

bit_vector      fpunit_exec_exec__MMU_PASS_THROUGH_LLIMIT;
#define MMU_PASS_THROUGH_LLIMIT (fpunit_exec_exec__MMU_PASS_THROUGH_LLIMIT)

bit_vector      fpunit_exec_exec__MMU_READ_DWORD;
#define MMU_READ_DWORD (fpunit_exec_exec__MMU_READ_DWORD)

bit_vector      fpunit_exec_exec__MMU_READ_LINE;
#define MMU_READ_LINE (fpunit_exec_exec__MMU_READ_LINE)

bit_vector      fpunit_exec_exec__MMU_WRITE_DWORD;
#define MMU_WRITE_DWORD (fpunit_exec_exec__MMU_WRITE_DWORD)

bit_vector      fpunit_exec_exec__MMU_WRITE_DWORD_NO_RESPONSE;
#define MMU_WRITE_DWORD_NO_RESPONSE (fpunit_exec_exec__MMU_WRITE_DWORD_NO_RESPONSE)

bit_vector      fpunit_exec_exec__MMU_WRITE_FSR;
#define MMU_WRITE_FSR (fpunit_exec_exec__MMU_WRITE_FSR)

bit_vector      fpunit_exec_exec__NEW_STREAM_MASK;
#define NEW_STREAM_MASK (fpunit_exec_exec__NEW_STREAM_MASK)

bit_vector      fpunit_exec_exec__NEW_THREAD_MASK;
#define NEW_THREAD_MASK (fpunit_exec_exec__NEW_THREAD_MASK)

bit_vector      fpunit_exec_exec__NONE_TRAP_BIT_VEC;
#define NONE_TRAP_BIT_VEC (fpunit_exec_exec__NONE_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__NONE_TRAP_INDEX;
#define NONE_TRAP_INDEX (fpunit_exec_exec__NONE_TRAP_INDEX)

bit_vector      fpunit_exec_exec__NOP_INSTRUCTION;
#define NOP_INSTRUCTION (fpunit_exec_exec__NOP_INSTRUCTION)

bit_vector      fpunit_exec_exec__NO_BLOCK_READ;
#define NO_BLOCK_READ (fpunit_exec_exec__NO_BLOCK_READ)

bit_vector      fpunit_exec_exec__NPC_RESET_VALUE;
#define NPC_RESET_VALUE (fpunit_exec_exec__NPC_RESET_VALUE)

bit_vector      fpunit_exec_exec__NWINDOWS;
#define NWINDOWS (fpunit_exec_exec__NWINDOWS)

bit_vector      fpunit_exec_exec__NWINDOWS_MOD_MASK_32;
#define NWINDOWS_MOD_MASK_32 (fpunit_exec_exec__NWINDOWS_MOD_MASK_32)

bit_vector      fpunit_exec_exec__NWINDOWS_MOD_MASK_5;
#define NWINDOWS_MOD_MASK_5 (fpunit_exec_exec__NWINDOWS_MOD_MASK_5)

bit_vector      fpunit_exec_exec__NWINDOWSx16;
#define NWINDOWSx16 (fpunit_exec_exec__NWINDOWSx16)

bit_vector      fpunit_exec_exec__NWINDOWSx16_MOD_MASK_32;
#define NWINDOWSx16_MOD_MASK_32 (fpunit_exec_exec__NWINDOWSx16_MOD_MASK_32)

bit_vector      fpunit_exec_exec__NWINDOWSx2;
#define NWINDOWSx2 (fpunit_exec_exec__NWINDOWSx2)

bit_vector      fpunit_exec_exec__ONE_1;
#define ONE_1 (fpunit_exec_exec__ONE_1)

bit_vector      fpunit_exec_exec__ONE_10;
#define ONE_10 (fpunit_exec_exec__ONE_10)

bit_vector      fpunit_exec_exec__ONE_11;
#define ONE_11 (fpunit_exec_exec__ONE_11)

bit_vector      fpunit_exec_exec__ONE_11_S;
#define ONE_11_S (fpunit_exec_exec__ONE_11_S)

bit_vector      fpunit_exec_exec__ONE_12;
#define ONE_12 (fpunit_exec_exec__ONE_12)

bit_vector      fpunit_exec_exec__ONE_128;
#define ONE_128 (fpunit_exec_exec__ONE_128)

bit_vector      fpunit_exec_exec__ONE_13;
#define ONE_13 (fpunit_exec_exec__ONE_13)

bit_vector      fpunit_exec_exec__ONE_14;
#define ONE_14 (fpunit_exec_exec__ONE_14)

bit_vector      fpunit_exec_exec__ONE_15;
#define ONE_15 (fpunit_exec_exec__ONE_15)

bit_vector      fpunit_exec_exec__ONE_16;
#define ONE_16 (fpunit_exec_exec__ONE_16)

bit_vector      fpunit_exec_exec__ONE_17;
#define ONE_17 (fpunit_exec_exec__ONE_17)

bit_vector      fpunit_exec_exec__ONE_18;
#define ONE_18 (fpunit_exec_exec__ONE_18)

bit_vector      fpunit_exec_exec__ONE_19;
#define ONE_19 (fpunit_exec_exec__ONE_19)

bit_vector      fpunit_exec_exec__ONE_2;
#define ONE_2 (fpunit_exec_exec__ONE_2)

bit_vector      fpunit_exec_exec__ONE_20;
#define ONE_20 (fpunit_exec_exec__ONE_20)

bit_vector      fpunit_exec_exec__ONE_23;
#define ONE_23 (fpunit_exec_exec__ONE_23)

bit_vector      fpunit_exec_exec__ONE_24;
#define ONE_24 (fpunit_exec_exec__ONE_24)

bit_vector      fpunit_exec_exec__ONE_25;
#define ONE_25 (fpunit_exec_exec__ONE_25)

bit_vector      fpunit_exec_exec__ONE_256;
#define ONE_256 (fpunit_exec_exec__ONE_256)

bit_vector      fpunit_exec_exec__ONE_29;
#define ONE_29 (fpunit_exec_exec__ONE_29)

bit_vector      fpunit_exec_exec__ONE_3;
#define ONE_3 (fpunit_exec_exec__ONE_3)

bit_vector      fpunit_exec_exec__ONE_31;
#define ONE_31 (fpunit_exec_exec__ONE_31)

bit_vector      fpunit_exec_exec__ONE_32;
#define ONE_32 (fpunit_exec_exec__ONE_32)

bit_vector      fpunit_exec_exec__ONE_36;
#define ONE_36 (fpunit_exec_exec__ONE_36)

bit_vector      fpunit_exec_exec__ONE_4;
#define ONE_4 (fpunit_exec_exec__ONE_4)

bit_vector      fpunit_exec_exec__ONE_48;
#define ONE_48 (fpunit_exec_exec__ONE_48)

bit_vector      fpunit_exec_exec__ONE_5;
#define ONE_5 (fpunit_exec_exec__ONE_5)

bit_vector      fpunit_exec_exec__ONE_52;
#define ONE_52 (fpunit_exec_exec__ONE_52)

bit_vector      fpunit_exec_exec__ONE_54;
#define ONE_54 (fpunit_exec_exec__ONE_54)

bit_vector      fpunit_exec_exec__ONE_6;
#define ONE_6 (fpunit_exec_exec__ONE_6)

bit_vector      fpunit_exec_exec__ONE_60;
#define ONE_60 (fpunit_exec_exec__ONE_60)

bit_vector      fpunit_exec_exec__ONE_62;
#define ONE_62 (fpunit_exec_exec__ONE_62)

bit_vector      fpunit_exec_exec__ONE_63;
#define ONE_63 (fpunit_exec_exec__ONE_63)

bit_vector      fpunit_exec_exec__ONE_64;
#define ONE_64 (fpunit_exec_exec__ONE_64)

bit_vector      fpunit_exec_exec__ONE_65;
#define ONE_65 (fpunit_exec_exec__ONE_65)

bit_vector      fpunit_exec_exec__ONE_7;
#define ONE_7 (fpunit_exec_exec__ONE_7)

bit_vector      fpunit_exec_exec__ONE_8;
#define ONE_8 (fpunit_exec_exec__ONE_8)

bit_vector      fpunit_exec_exec__ONE_9;
#define ONE_9 (fpunit_exec_exec__ONE_9)

bit_vector      fpunit_exec_exec__PC_RESET_VALUE;
#define PC_RESET_VALUE (fpunit_exec_exec__PC_RESET_VALUE)

bit_vector      fpunit_exec_exec__PRIVILEGED_INSTRUCTION_TRAP_BIT_VEC;
#define PRIVILEGED_INSTRUCTION_TRAP_BIT_VEC (fpunit_exec_exec__PRIVILEGED_INSTRUCTION_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__PRIVILEGED_INSTRUCTION_TRAP_INDEX;
#define PRIVILEGED_INSTRUCTION_TRAP_INDEX (fpunit_exec_exec__PRIVILEGED_INSTRUCTION_TRAP_INDEX)

bit_vector      fpunit_exec_exec__PROCESSOR_ERROR_MODE;
#define PROCESSOR_ERROR_MODE (fpunit_exec_exec__PROCESSOR_ERROR_MODE)

bit_vector      fpunit_exec_exec__PROCESSOR_EXECUTE_MODE;
#define PROCESSOR_EXECUTE_MODE (fpunit_exec_exec__PROCESSOR_EXECUTE_MODE)

bit_vector      fpunit_exec_exec__PROCESSOR_RESET_MODE;
#define PROCESSOR_RESET_MODE (fpunit_exec_exec__PROCESSOR_RESET_MODE)

bit_vector      fpunit_exec_exec__PROCESSOR_UNDEFINED_MODE;
#define PROCESSOR_UNDEFINED_MODE (fpunit_exec_exec__PROCESSOR_UNDEFINED_MODE)

bit_vector      fpunit_exec_exec__PSR_RESET_VALUE;
#define PSR_RESET_VALUE (fpunit_exec_exec__PSR_RESET_VALUE)

bit_vector      fpunit_exec_exec__REQUEST_TYPE_BRIDGE_CONFIG_READ;
#define REQUEST_TYPE_BRIDGE_CONFIG_READ (fpunit_exec_exec__REQUEST_TYPE_BRIDGE_CONFIG_READ)

bit_vector      fpunit_exec_exec__REQUEST_TYPE_BRIDGE_CONFIG_WRITE;
#define REQUEST_TYPE_BRIDGE_CONFIG_WRITE (fpunit_exec_exec__REQUEST_TYPE_BRIDGE_CONFIG_WRITE)

bit_vector      fpunit_exec_exec__REQUEST_TYPE_CCU_CACHE_READ;
#define REQUEST_TYPE_CCU_CACHE_READ (fpunit_exec_exec__REQUEST_TYPE_CCU_CACHE_READ)

bit_vector      fpunit_exec_exec__REQUEST_TYPE_CCU_CACHE_WRITE;
#define REQUEST_TYPE_CCU_CACHE_WRITE (fpunit_exec_exec__REQUEST_TYPE_CCU_CACHE_WRITE)

bit_vector      fpunit_exec_exec__REQUEST_TYPE_IFETCH;
#define REQUEST_TYPE_IFETCH (fpunit_exec_exec__REQUEST_TYPE_IFETCH)

bit_vector      fpunit_exec_exec__REQUEST_TYPE_NOP;
#define REQUEST_TYPE_NOP (fpunit_exec_exec__REQUEST_TYPE_NOP)

bit_vector      fpunit_exec_exec__REQUEST_TYPE_READ;
#define REQUEST_TYPE_READ (fpunit_exec_exec__REQUEST_TYPE_READ)

bit_vector      fpunit_exec_exec__REQUEST_TYPE_STBAR;
#define REQUEST_TYPE_STBAR (fpunit_exec_exec__REQUEST_TYPE_STBAR)

bit_vector      fpunit_exec_exec__REQUEST_TYPE_WRFSRFAR;
#define REQUEST_TYPE_WRFSRFAR (fpunit_exec_exec__REQUEST_TYPE_WRFSRFAR)

bit_vector      fpunit_exec_exec__REQUEST_TYPE_WRITE;
#define REQUEST_TYPE_WRITE (fpunit_exec_exec__REQUEST_TYPE_WRITE)

bit_vector      fpunit_exec_exec__RESERVED_TRAP_BIT_VEC;
#define RESERVED_TRAP_BIT_VEC (fpunit_exec_exec__RESERVED_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__RESERVED_TRAP_INDEX;
#define RESERVED_TRAP_INDEX (fpunit_exec_exec__RESERVED_TRAP_INDEX)

bit_vector      fpunit_exec_exec__RESET_TRAP_TRAP_BIT_VEC;
#define RESET_TRAP_TRAP_BIT_VEC (fpunit_exec_exec__RESET_TRAP_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__RESET_TRAP_TRAP_INDEX;
#define RESET_TRAP_TRAP_INDEX (fpunit_exec_exec__RESET_TRAP_TRAP_INDEX)

bit_vector      fpunit_exec_exec__R_REGISTER_ACCESS_ERROR_TRAP_BIT_VEC;
#define R_REGISTER_ACCESS_ERROR_TRAP_BIT_VEC (fpunit_exec_exec__R_REGISTER_ACCESS_ERROR_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__R_REGISTER_ACCESS_ERROR_TRAP_INDEX;
#define R_REGISTER_ACCESS_ERROR_TRAP_INDEX (fpunit_exec_exec__R_REGISTER_ACCESS_ERROR_TRAP_INDEX)

bit_vector      fpunit_exec_exec__SEQUENCE_ERROR_TRAP_BIT_VEC;
#define SEQUENCE_ERROR_TRAP_BIT_VEC (fpunit_exec_exec__SEQUENCE_ERROR_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__SEQUENCE_ERROR_TRAP_INDEX;
#define SEQUENCE_ERROR_TRAP_INDEX (fpunit_exec_exec__SEQUENCE_ERROR_TRAP_INDEX)

bit_vector      fpunit_exec_exec__SINGLE_STEP_MASK;
#define SINGLE_STEP_MASK (fpunit_exec_exec__SINGLE_STEP_MASK)

bit_vector      fpunit_exec_exec__SP_round_mid;
#define SP_round_mid (fpunit_exec_exec__SP_round_mid)

bit_vector      fpunit_exec_exec__TAG_OVERFLOW_TRAP_BIT_VEC;
#define TAG_OVERFLOW_TRAP_BIT_VEC (fpunit_exec_exec__TAG_OVERFLOW_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__TAG_OVERFLOW_TRAP_INDEX;
#define TAG_OVERFLOW_TRAP_INDEX (fpunit_exec_exec__TAG_OVERFLOW_TRAP_INDEX)

bit_vector      fpunit_exec_exec__TERMINATES_STREAM;
#define TERMINATES_STREAM (fpunit_exec_exec__TERMINATES_STREAM)

bit_vector      fpunit_exec_exec__TERMINATES_THREAD;
#define TERMINATES_THREAD (fpunit_exec_exec__TERMINATES_THREAD)

bit_vector      fpunit_exec_exec__TEU_ANNUL_NEXT_INDEX;
#define TEU_ANNUL_NEXT_INDEX (fpunit_exec_exec__TEU_ANNUL_NEXT_INDEX)

bit_vector      fpunit_exec_exec__TEU_DBG_BREAK_POINT_INDEX;
#define TEU_DBG_BREAK_POINT_INDEX (fpunit_exec_exec__TEU_DBG_BREAK_POINT_INDEX)

bit_vector      fpunit_exec_exec__TEU_DBG_WATCH_POINT_INDEX;
#define TEU_DBG_WATCH_POINT_INDEX (fpunit_exec_exec__TEU_DBG_WATCH_POINT_INDEX)

bit_vector      fpunit_exec_exec__TEU_EXCEPTION_INDEX;
#define TEU_EXCEPTION_INDEX (fpunit_exec_exec__TEU_EXCEPTION_INDEX)

bit_vector      fpunit_exec_exec__TEU_FETCH_IS_SPINNING;
#define TEU_FETCH_IS_SPINNING (fpunit_exec_exec__TEU_FETCH_IS_SPINNING)

bit_vector      fpunit_exec_exec__TEU_INTERRUPT_INDEX;
#define TEU_INTERRUPT_INDEX (fpunit_exec_exec__TEU_INTERRUPT_INDEX)

bit_vector      fpunit_exec_exec__TEU_MACHINE_ERROR_INDEX;
#define TEU_MACHINE_ERROR_INDEX (fpunit_exec_exec__TEU_MACHINE_ERROR_INDEX)

bit_vector      fpunit_exec_exec__TEU_SINGLE_STEP_INDEX;
#define TEU_SINGLE_STEP_INDEX (fpunit_exec_exec__TEU_SINGLE_STEP_INDEX)

bit_vector      fpunit_exec_exec__THREE_2;
#define THREE_2 (fpunit_exec_exec__THREE_2)

bit_vector      fpunit_exec_exec__THREE_3;
#define THREE_3 (fpunit_exec_exec__THREE_3)

bit_vector      fpunit_exec_exec__TRACE_ON;
#define TRACE_ON (fpunit_exec_exec__TRACE_ON)

bit_vector      fpunit_exec_exec__TRAP_INSTRUCTION_TRAP_BIT_VEC;
#define TRAP_INSTRUCTION_TRAP_BIT_VEC (fpunit_exec_exec__TRAP_INSTRUCTION_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__TRAP_INSTRUCTION_TRAP_INDEX;
#define TRAP_INSTRUCTION_TRAP_INDEX (fpunit_exec_exec__TRAP_INSTRUCTION_TRAP_INDEX)

bit_vector      fpunit_exec_exec__TRAP_TRAP_BIT_VEC;
#define TRAP_TRAP_BIT_VEC (fpunit_exec_exec__TRAP_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__TRAP_TRAP_INDEX;
#define TRAP_TRAP_INDEX (fpunit_exec_exec__TRAP_TRAP_INDEX)

bit_vector      fpunit_exec_exec__TT_MASK;
#define TT_MASK (fpunit_exec_exec__TT_MASK)

bit_vector      fpunit_exec_exec__TWO_2;
#define TWO_2 (fpunit_exec_exec__TWO_2)

bit_vector      fpunit_exec_exec__TWO_3;
#define TWO_3 (fpunit_exec_exec__TWO_3)

bit_vector      fpunit_exec_exec__UNFINISHED_FPOP_TRAP_BIT_VEC;
#define UNFINISHED_FPOP_TRAP_BIT_VEC (fpunit_exec_exec__UNFINISHED_FPOP_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__UNFINISHED_FPOP_TRAP_INDEX;
#define UNFINISHED_FPOP_TRAP_INDEX (fpunit_exec_exec__UNFINISHED_FPOP_TRAP_INDEX)

bit_vector      fpunit_exec_exec__UNIMPLEMENTED_FLUSH_TRAP_BIT_VEC;
#define UNIMPLEMENTED_FLUSH_TRAP_BIT_VEC (fpunit_exec_exec__UNIMPLEMENTED_FLUSH_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__UNIMPLEMENTED_FLUSH_TRAP_INDEX;
#define UNIMPLEMENTED_FLUSH_TRAP_INDEX (fpunit_exec_exec__UNIMPLEMENTED_FLUSH_TRAP_INDEX)

bit_vector      fpunit_exec_exec__UNIMPLEMENTED_FPOP_TRAP_BIT_VEC;
#define UNIMPLEMENTED_FPOP_TRAP_BIT_VEC (fpunit_exec_exec__UNIMPLEMENTED_FPOP_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__UNIMPLEMENTED_FPOP_TRAP_INDEX;
#define UNIMPLEMENTED_FPOP_TRAP_INDEX (fpunit_exec_exec__UNIMPLEMENTED_FPOP_TRAP_INDEX)

bit_vector      fpunit_exec_exec__WB_MISPREDICTED_STREAM;
#define WB_MISPREDICTED_STREAM (fpunit_exec_exec__WB_MISPREDICTED_STREAM)

bit_vector      fpunit_exec_exec__WB_NORMAL;
#define WB_NORMAL (fpunit_exec_exec__WB_NORMAL)

bit_vector      fpunit_exec_exec__WB_RESET;
#define WB_RESET (fpunit_exec_exec__WB_RESET)

bit_vector      fpunit_exec_exec__WB_TRAPPED;
#define WB_TRAPPED (fpunit_exec_exec__WB_TRAPPED)

bit_vector      fpunit_exec_exec__WIM_MASK;
#define WIM_MASK (fpunit_exec_exec__WIM_MASK)

bit_vector      fpunit_exec_exec__WINDOW_OVERFLOW_TRAP_BIT_VEC;
#define WINDOW_OVERFLOW_TRAP_BIT_VEC (fpunit_exec_exec__WINDOW_OVERFLOW_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__WINDOW_OVERFLOW_TRAP_INDEX;
#define WINDOW_OVERFLOW_TRAP_INDEX (fpunit_exec_exec__WINDOW_OVERFLOW_TRAP_INDEX)

bit_vector      fpunit_exec_exec__WINDOW_UNDERFLOW_TRAP_BIT_VEC;
#define WINDOW_UNDERFLOW_TRAP_BIT_VEC (fpunit_exec_exec__WINDOW_UNDERFLOW_TRAP_BIT_VEC)

bit_vector      fpunit_exec_exec__WINDOW_UNDERFLOW_TRAP_INDEX;
#define WINDOW_UNDERFLOW_TRAP_INDEX (fpunit_exec_exec__WINDOW_UNDERFLOW_TRAP_INDEX)

bit_vector      fpunit_exec_exec__ZERO_1;
#define ZERO_1 (fpunit_exec_exec__ZERO_1)

bit_vector      fpunit_exec_exec__ZERO_10;
#define ZERO_10 (fpunit_exec_exec__ZERO_10)

bit_vector      fpunit_exec_exec__ZERO_104;
#define ZERO_104 (fpunit_exec_exec__ZERO_104)

bit_vector      fpunit_exec_exec__ZERO_106;
#define ZERO_106 (fpunit_exec_exec__ZERO_106)

bit_vector      fpunit_exec_exec__ZERO_11;
#define ZERO_11 (fpunit_exec_exec__ZERO_11)

bit_vector      fpunit_exec_exec__ZERO_12;
#define ZERO_12 (fpunit_exec_exec__ZERO_12)

bit_vector      fpunit_exec_exec__ZERO_128;
#define ZERO_128 (fpunit_exec_exec__ZERO_128)

bit_vector      fpunit_exec_exec__ZERO_13;
#define ZERO_13 (fpunit_exec_exec__ZERO_13)

bit_vector      fpunit_exec_exec__ZERO_14;
#define ZERO_14 (fpunit_exec_exec__ZERO_14)

bit_vector      fpunit_exec_exec__ZERO_15;
#define ZERO_15 (fpunit_exec_exec__ZERO_15)

bit_vector      fpunit_exec_exec__ZERO_16;
#define ZERO_16 (fpunit_exec_exec__ZERO_16)

bit_vector      fpunit_exec_exec__ZERO_17;
#define ZERO_17 (fpunit_exec_exec__ZERO_17)

bit_vector      fpunit_exec_exec__ZERO_18;
#define ZERO_18 (fpunit_exec_exec__ZERO_18)

bit_vector      fpunit_exec_exec__ZERO_19;
#define ZERO_19 (fpunit_exec_exec__ZERO_19)

bit_vector      fpunit_exec_exec__ZERO_2;
#define ZERO_2 (fpunit_exec_exec__ZERO_2)

bit_vector      fpunit_exec_exec__ZERO_20;
#define ZERO_20 (fpunit_exec_exec__ZERO_20)

bit_vector      fpunit_exec_exec__ZERO_22;
#define ZERO_22 (fpunit_exec_exec__ZERO_22)

bit_vector      fpunit_exec_exec__ZERO_23;
#define ZERO_23 (fpunit_exec_exec__ZERO_23)

bit_vector      fpunit_exec_exec__ZERO_24;
#define ZERO_24 (fpunit_exec_exec__ZERO_24)

bit_vector      fpunit_exec_exec__ZERO_25;
#define ZERO_25 (fpunit_exec_exec__ZERO_25)

bit_vector      fpunit_exec_exec__ZERO_256;
#define ZERO_256 (fpunit_exec_exec__ZERO_256)

bit_vector      fpunit_exec_exec__ZERO_26;
#define ZERO_26 (fpunit_exec_exec__ZERO_26)

bit_vector      fpunit_exec_exec__ZERO_28;
#define ZERO_28 (fpunit_exec_exec__ZERO_28)

bit_vector      fpunit_exec_exec__ZERO_29;
#define ZERO_29 (fpunit_exec_exec__ZERO_29)

bit_vector      fpunit_exec_exec__ZERO_3;
#define ZERO_3 (fpunit_exec_exec__ZERO_3)

bit_vector      fpunit_exec_exec__ZERO_31;
#define ZERO_31 (fpunit_exec_exec__ZERO_31)

bit_vector      fpunit_exec_exec__ZERO_32;
#define ZERO_32 (fpunit_exec_exec__ZERO_32)

bit_vector      fpunit_exec_exec__ZERO_36;
#define ZERO_36 (fpunit_exec_exec__ZERO_36)

bit_vector      fpunit_exec_exec__ZERO_4;
#define ZERO_4 (fpunit_exec_exec__ZERO_4)

bit_vector      fpunit_exec_exec__ZERO_42;
#define ZERO_42 (fpunit_exec_exec__ZERO_42)

bit_vector      fpunit_exec_exec__ZERO_48;
#define ZERO_48 (fpunit_exec_exec__ZERO_48)

bit_vector      fpunit_exec_exec__ZERO_5;
#define ZERO_5 (fpunit_exec_exec__ZERO_5)

bit_vector      fpunit_exec_exec__ZERO_51;
#define ZERO_51 (fpunit_exec_exec__ZERO_51)

bit_vector      fpunit_exec_exec__ZERO_52;
#define ZERO_52 (fpunit_exec_exec__ZERO_52)

bit_vector      fpunit_exec_exec__ZERO_54;
#define ZERO_54 (fpunit_exec_exec__ZERO_54)

bit_vector      fpunit_exec_exec__ZERO_55;
#define ZERO_55 (fpunit_exec_exec__ZERO_55)

bit_vector      fpunit_exec_exec__ZERO_6;
#define ZERO_6 (fpunit_exec_exec__ZERO_6)

bit_vector      fpunit_exec_exec__ZERO_60;
#define ZERO_60 (fpunit_exec_exec__ZERO_60)

bit_vector      fpunit_exec_exec__ZERO_61;
#define ZERO_61 (fpunit_exec_exec__ZERO_61)

bit_vector      fpunit_exec_exec__ZERO_62;
#define ZERO_62 (fpunit_exec_exec__ZERO_62)

bit_vector      fpunit_exec_exec__ZERO_63;
#define ZERO_63 (fpunit_exec_exec__ZERO_63)

bit_vector      fpunit_exec_exec__ZERO_64;
#define ZERO_64 (fpunit_exec_exec__ZERO_64)

bit_vector      fpunit_exec_exec__ZERO_7;
#define ZERO_7 (fpunit_exec_exec__ZERO_7)

bit_vector      fpunit_exec_exec__ZERO_8;
#define ZERO_8 (fpunit_exec_exec__ZERO_8)

bit_vector      fpunit_exec_exec__ZERO_9;
#define ZERO_9 (fpunit_exec_exec__ZERO_9)

bit_vector      fpunit_exec_exec__default_mem_pool[1];
#define default_mem_pool (fpunit_exec_exec__default_mem_pool)

bit_vector      fpunit_exec_exec__exp_base_0;
#define exp_base_0 (fpunit_exec_exec__exp_base_0)

bit_vector      fpunit_exec_exec__exp_base_1;
#define exp_base_1 (fpunit_exec_exec__exp_base_1)

bit_vector      fpunit_exec_exec__exp_base_1022;
#define exp_base_1022 (fpunit_exec_exec__exp_base_1022)

bit_vector      fpunit_exec_exec__exp_base_1023;
#define exp_base_1023 (fpunit_exec_exec__exp_base_1023)

bit_vector      fpunit_exec_exec__exp_base_126;
#define exp_base_126 (fpunit_exec_exec__exp_base_126)

bit_vector      fpunit_exec_exec__exp_base_127;
#define exp_base_127 (fpunit_exec_exec__exp_base_127)

bit_vector      fpunit_exec_exec__exp_base_24;
#define exp_base_24 (fpunit_exec_exec__exp_base_24)

bit_vector      fpunit_exec_exec__exp_base_254;
#define exp_base_254 (fpunit_exec_exec__exp_base_254)

bit_vector      fpunit_exec_exec__exp_base_53;
#define exp_base_53 (fpunit_exec_exec__exp_base_53)

bit_vector      fpunit_exec_exec__exp_base_neg_1022;
#define exp_base_neg_1022 (fpunit_exec_exec__exp_base_neg_1022)

bit_vector      fpunit_exec_exec__exp_base_neg_126;
#define exp_base_neg_126 (fpunit_exec_exec__exp_base_neg_126)

bit_vector      fpunit_exec_exec__expbase_1022;
#define expbase_1022 (fpunit_exec_exec__expbase_1022)

bit_vector      fpunit_exec_exec__expbase_1023;
#define expbase_1023 (fpunit_exec_exec__expbase_1023)

bit_vector      fpunit_exec_exec__expbase_126;
#define expbase_126 (fpunit_exec_exec__expbase_126)

bit_vector      fpunit_exec_exec__expbase_127;
#define expbase_127 (fpunit_exec_exec__expbase_127)

bit_vector      fpunit_exec_exec__value_24;
#define value_24 (fpunit_exec_exec__value_24)

bit_vector      fpunit_exec_exec__value_38;
#define value_38 (fpunit_exec_exec__value_38)

bit_vector      fpunit_exec_exec__value_53;
#define value_53 (fpunit_exec_exec__value_53)

bit_vector      fpunit_exec_exec__value_62;
#define value_62 (fpunit_exec_exec__value_62)

bit_vector      fpunit_exec_exec__value_9;
#define value_9 (fpunit_exec_exec__value_9)

void
fpunit_exec_exec___init_aa_globals__()
{
    init_static_bit_vector(&(ACCESS_ASR), 3);
    bit_vector_clear(&ACCESS_ASR);
    ACCESS_ASR.val.byte_array[0] = 5;
    init_static_bit_vector(&(ACCESS_PSR), 3);
    bit_vector_clear(&ACCESS_PSR);
    ACCESS_PSR.val.byte_array[0] = 1;
    init_static_bit_vector(&(ACCESS_REG), 3);
    bit_vector_clear(&ACCESS_REG);
    ACCESS_REG.val.byte_array[0] = 6;
    init_static_bit_vector(&(ACCESS_TBR), 3);
    bit_vector_clear(&ACCESS_TBR);
    ACCESS_TBR.val.byte_array[0] = 2;
    init_static_bit_vector(&(ACCESS_WIM), 3);
    bit_vector_clear(&ACCESS_WIM);
    ACCESS_WIM.val.byte_array[0] = 3;
    init_static_bit_vector(&(ACCESS_Y), 3);
    bit_vector_clear(&ACCESS_Y);
    ACCESS_Y.val.byte_array[0] = 4;
    register_pipe("AFB_BUS_REQUEST", 18, 8, 0);
    register_pipe("AFB_BUS_RESPONSE", 10, 8, 0);
    register_pipe("AJIT_to_ENV_addr", 2, 64, 0);
    register_pipe("AJIT_to_ENV_byte_mask", 2, 8, 0);
    register_pipe("AJIT_to_ENV_data", 2, 64, 0);
    register_pipe("AJIT_to_ENV_debug_response", 1, 32, 0);
    register_pipe("AJIT_to_ENV_logger", 3, 32, 0);
    register_pipe("AJIT_to_ENV_logger_0", 3, 32, 0);
    register_pipe("AJIT_to_ENV_logger_1", 3, 32, 0);
    register_pipe("AJIT_to_ENV_logger_2", 3, 32, 0);
    register_pipe("AJIT_to_ENV_logger_3", 3, 32, 0);
    register_pipe("AJIT_to_ENV_processor_mode", 1, 8, 0);
    register_pipe("AJIT_to_ENV_processor_mode_0", 1, 8, 0);
    register_pipe("AJIT_to_ENV_processor_mode_1", 1, 8, 0);
    register_pipe("AJIT_to_ENV_processor_mode_2", 1, 8, 0);
    register_pipe("AJIT_to_ENV_processor_mode_3", 1, 8, 0);
    register_pipe("AJIT_to_ENV_request_type", 2, 8, 0);
    init_static_bit_vector(&(ALL_ONE_11), 11);
    bit_vector_clear(&ALL_ONE_11);
    ALL_ONE_11.val.byte_array[0] = 255;
    ALL_ONE_11.val.byte_array[1] = 7;
    init_static_bit_vector(&(ALL_ONE_13), 13);
    bit_vector_clear(&ALL_ONE_13);
    ALL_ONE_13.val.byte_array[0] = 255;
    ALL_ONE_13.val.byte_array[1] = 7;
    init_static_bit_vector(&(ALL_ONE_8), 8);
    bit_vector_clear(&ALL_ONE_8);
    ALL_ONE_8.val.byte_array[0] = 255;
    init_static_bit_vector(&(ALU_INSTR), 3);
    bit_vector_clear(&ALU_INSTR);
    ALU_INSTR.val.byte_array[0] = 2;
    init_static_bit_vector(&(ANNUL_TRAP_BIT_VEC), 32);
    bit_vector_clear(&ANNUL_TRAP_BIT_VEC);
    ANNUL_TRAP_BIT_VEC.val.byte_array[0] = 8;
    init_static_bit_vector(&(ANNUL_TRAP_INDEX), 32);
    bit_vector_clear(&ANNUL_TRAP_INDEX);
    ANNUL_TRAP_INDEX.val.byte_array[0] = 3;
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
    register_pipe("BIU_to_RLUT", 2, 32, 0);
    init_static_bit_vector(&(BLOCK_READ), 1);
    bit_vector_clear(&BLOCK_READ);
    BLOCK_READ.val.byte_array[0] = 1;
    register_pipe("BRIDGE_to_FLASH_COMMAND", 14, 8, 0);
    register_pipe("BRIDGE_to_GPIO_COMMAND", 14, 8, 0);
    register_pipe("BRIDGE_to_IRC_COMMAND", 14, 8, 0);
    register_pipe("BRIDGE_to_SERIAL_COMMAND", 14, 8, 0);
    register_pipe("BRIDGE_to_SPI_COMMAND", 14, 8, 0);
    register_pipe("BRIDGE_to_TIMER_COMMAND", 14, 8, 0);
    init_static_bit_vector(&(CACHE_ARRAY_NOP), 3);
    bit_vector_clear(&CACHE_ARRAY_NOP);
    CACHE_ARRAY_NOP.val.byte_array[0] = 3;
    init_static_bit_vector(&(CACHE_ARRAY_READ_DWORD), 3);
    bit_vector_clear(&CACHE_ARRAY_READ_DWORD);
    CACHE_ARRAY_READ_DWORD.val.byte_array[0] = 1;
    init_static_bit_vector(&(CACHE_ARRAY_WRITE_DWORD), 3);
    bit_vector_clear(&CACHE_ARRAY_WRITE_DWORD);
    CACHE_ARRAY_WRITE_DWORD.val.byte_array[0] = 2;
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
    init_static_bit_vector(&(CCU_DBG_BP_HIT), 8);
    bit_vector_clear(&CCU_DBG_BP_HIT);
    CCU_DBG_BP_HIT.val.byte_array[0] = 2;
    init_static_bit_vector(&(CCU_DBG_CONNECT_RQST), 8);
    bit_vector_clear(&CCU_DBG_CONNECT_RQST);
    CCU_DBG_CONNECT_RQST.val.byte_array[0] = 1;
    init_static_bit_vector(&(CCU_DBG_ERROR), 8);
    bit_vector_clear(&CCU_DBG_ERROR);
    CCU_DBG_ERROR.val.byte_array[0] = 7;
    init_static_bit_vector(&(CCU_DBG_ERROR_MODE), 8);
    bit_vector_clear(&CCU_DBG_ERROR_MODE);
    CCU_DBG_ERROR_MODE.val.byte_array[0] = 6;
    init_static_bit_vector(&(CCU_DBG_OK), 8);
    bit_vector_clear(&CCU_DBG_OK);
    CCU_DBG_OK.val.byte_array[0] = 8;
    init_static_bit_vector(&(CCU_DBG_READ_RESPONSE), 8);
    bit_vector_clear(&CCU_DBG_READ_RESPONSE);
    CCU_DBG_READ_RESPONSE.val.byte_array[0] = 9;
    init_static_bit_vector(&(CCU_DBG_READ_WP_HIT), 8);
    bit_vector_clear(&CCU_DBG_READ_WP_HIT);
    CCU_DBG_READ_WP_HIT.val.byte_array[0] = 3;
    init_static_bit_vector(&(CCU_DBG_THREAD_FINISH), 8);
    bit_vector_clear(&CCU_DBG_THREAD_FINISH);
    CCU_DBG_THREAD_FINISH.val.byte_array[0] = 5;
    init_static_bit_vector(&(CCU_DBG_WRITE_WP_HIT), 8);
    bit_vector_clear(&CCU_DBG_WRITE_WP_HIT);
    CCU_DBG_WRITE_WP_HIT.val.byte_array[0] = 4;
    init_static_bit_vector(&(CCU_TEU_CLEAR_BP), 3);
    bit_vector_clear(&CCU_TEU_CLEAR_BP);
    CCU_TEU_CLEAR_BP.val.byte_array[0] = 2;
    init_static_bit_vector(&(CCU_TEU_CLEAR_WP), 3);
    bit_vector_clear(&CCU_TEU_CLEAR_WP);
    CCU_TEU_CLEAR_WP.val.byte_array[0] = 4;
    init_static_bit_vector(&(CCU_TEU_INTR), 3);
    bit_vector_clear(&CCU_TEU_INTR);
    CCU_TEU_INTR.val.byte_array[0] = 5;
    init_static_bit_vector(&(CCU_TEU_SET_BP), 3);
    bit_vector_clear(&CCU_TEU_SET_BP);
    CCU_TEU_SET_BP.val.byte_array[0] = 1;
    init_static_bit_vector(&(CCU_TEU_SET_WP), 3);
    bit_vector_clear(&CCU_TEU_SET_WP);
    CCU_TEU_SET_WP.val.byte_array[0] = 3;
    register_pipe("CONSOLE_to_SERIAL_RX", 2, 8, 0);
    init_static_bit_vector(&(CONTINUES_MISPREDICTED_STREAM), 3);
    bit_vector_clear(&CONTINUES_MISPREDICTED_STREAM);
    CONTINUES_MISPREDICTED_STREAM.val.byte_array[0] = 4;
    init_static_bit_vector(&(CONTINUES_TRAPPED_STREAM), 3);
    bit_vector_clear(&CONTINUES_TRAPPED_STREAM);
    CONTINUES_TRAPPED_STREAM.val.byte_array[0] = 6;
    init_static_bit_vector(&(CONTROL_TRANSFER_INSTR), 3);
    bit_vector_clear(&CONTROL_TRANSFER_INSTR);
    CONTROL_TRANSFER_INSTR.val.byte_array[0] = 3;
    register_pipe("CORE_0_BUS_RESPONSE", 18, 8, 0);
    register_pipe("CORE_0_to_ENV_debug_response", 1, 32, 0);
    register_pipe("CORE_1_BUS_RESPONSE", 18, 8, 0);
    register_pipe("CORE_1_to_ENV_debug_response", 1, 32, 0);
    register_pipe("CORE_2_BUS_RESPONSE", 18, 8, 0);
    register_pipe("CORE_2_to_ENV_debug_response", 1, 32, 0);
    register_pipe("CORE_3_BUS_RESPONSE", 18, 8, 0);
    register_pipe("CORE_3_to_ENV_debug_response", 1, 32, 0);
    register_pipe("CORE_BUS_REQUEST", 28, 8, 0);
    register_pipe("CORE_BUS_RESPONSE", 18, 8, 0);
    register_signal("CORE_ID", 2);
    register_signal("CORE_ID_0", 2);
    register_signal("CORE_ID_1", 2);
    register_signal("CORE_ID_2", 2);
    register_signal("CORE_ID_3", 2);
    register_pipe("CORE_PERIPHERAL_BUS_REQUEST", 28, 8, 0);
    register_pipe("CORE_PERIPHERAL_BUS_RESPONSE", 18, 8, 0);
    register_pipe("CORE_to_ENV_debug_response", 1, 32, 0);
    register_pipe("CORE_to_ENV_logger", 3, 32, 0);
    register_pipe("CORE_to_ENV_processor_mode", 1, 8, 0);
    register_signal("CPU_ID", 2);
    init_static_bit_vector(&(CP_DISABLED_TRAP_BIT_VEC), 32);
    bit_vector_clear(&CP_DISABLED_TRAP_BIT_VEC);
    CP_DISABLED_TRAP_BIT_VEC.val.byte_array[1] = 32;
    init_static_bit_vector(&(CP_DISABLED_TRAP_INDEX), 32);
    bit_vector_clear(&CP_DISABLED_TRAP_INDEX);
    CP_DISABLED_TRAP_INDEX.val.byte_array[0] = 12;
    init_static_bit_vector(&(CP_EXCEPTION_TRAP_BIT_VEC), 32);
    bit_vector_clear(&CP_EXCEPTION_TRAP_BIT_VEC);
    CP_EXCEPTION_TRAP_BIT_VEC.val.byte_array[2] = 8;
    init_static_bit_vector(&(CP_EXCEPTION_TRAP_INDEX), 32);
    bit_vector_clear(&CP_EXCEPTION_TRAP_INDEX);
    CP_EXCEPTION_TRAP_INDEX.val.byte_array[0] = 18;
    init_static_bit_vector(&(CP_INSTR), 3);
    bit_vector_clear(&CP_INSTR);
    CP_INSTR.val.byte_array[0] = 6;
    init_static_bit_vector(&(DATA_ACCESS_ERROR_TRAP_BIT_VEC), 32);
    bit_vector_clear(&DATA_ACCESS_ERROR_TRAP_BIT_VEC);
    DATA_ACCESS_ERROR_TRAP_BIT_VEC.val.byte_array[2] = 16;
    init_static_bit_vector(&(DATA_ACCESS_ERROR_TRAP_INDEX), 32);
    bit_vector_clear(&DATA_ACCESS_ERROR_TRAP_INDEX);
    DATA_ACCESS_ERROR_TRAP_INDEX.val.byte_array[0] = 19;
    init_static_bit_vector(&(DATA_ACCESS_EXCEPTION_TRAP_BIT_VEC), 32);
    bit_vector_clear(&DATA_ACCESS_EXCEPTION_TRAP_BIT_VEC);
    DATA_ACCESS_EXCEPTION_TRAP_BIT_VEC.val.byte_array[2] = 32;
    init_static_bit_vector(&(DATA_ACCESS_EXCEPTION_TRAP_INDEX), 32);
    bit_vector_clear(&DATA_ACCESS_EXCEPTION_TRAP_INDEX);
    DATA_ACCESS_EXCEPTION_TRAP_INDEX.val.byte_array[0] = 20;
    init_static_bit_vector(&(DATA_STORE_ERROR_TRAP_BIT_VEC), 32);
    bit_vector_clear(&DATA_STORE_ERROR_TRAP_BIT_VEC);
    DATA_STORE_ERROR_TRAP_BIT_VEC.val.byte_array[0] = 32;
    init_static_bit_vector(&(DATA_STORE_ERROR_TRAP_INDEX), 32);
    bit_vector_clear(&DATA_STORE_ERROR_TRAP_INDEX);
    DATA_STORE_ERROR_TRAP_INDEX.val.byte_array[0] = 5;
    init_static_bit_vector(&(DATA_TRANSFER_INSTR), 3);
    bit_vector_clear(&DATA_TRANSFER_INSTR);
    DATA_TRANSFER_INSTR.val.byte_array[0] = 1;
    register_pipe("DCACHE_to_CPU_reset_ack", 2, 8, 0);
    register_pipe("DCACHE_to_CPU_response", 18, 8, 0);
    register_pipe("DCACHE_to_CPU_slow_response", 18, 8, 0);
    register_pipe("DCACHE_to_MMU_addr", 2, 32, 0);
    register_pipe("DCACHE_to_MMU_asi", 2, 8, 0);
    register_pipe("DCACHE_to_MMU_byte_mask", 2, 8, 0);
    register_pipe("DCACHE_to_MMU_data", 2, 64, 0);
    register_pipe("DCACHE_to_MMU_request", 30, 8, 0);
    register_pipe("DCACHE_to_MMU_request_type", 2, 8, 0);
    register_pipe("DCACHE_to_RLUT", 2, 8, 0);
    init_static_bit_vector(&(DEBUG_MODE_MASK), 8);
    bit_vector_clear(&DEBUG_MODE_MASK);
    DEBUG_MODE_MASK.val.byte_array[0] = 2;
    register_signal("DEBUG_UART_RX", 1);
    register_signal("DEBUG_UART_TX", 1);
    register_pipe("DEBUG_to_MONITOR", 4, 8, 0);
    register_pipe("DEBUG_to_MONITOR_0", 4, 8, 0);
    register_pipe("DEBUG_to_MONITOR_1", 4, 8, 0);
    register_pipe("DEBUG_to_MONITOR_2", 4, 8, 0);
    register_pipe("DEBUG_to_MONITOR_3", 4, 8, 0);
    init_static_bit_vector(&(DENORM), 1);
    bit_vector_clear(&DENORM);
    DENORM.val.byte_array[0] = 1;
    init_static_bit_vector(&(DIVISION_BY_ZERO_TRAP_BIT_VEC), 32);
    bit_vector_clear(&DIVISION_BY_ZERO_TRAP_BIT_VEC);
    DIVISION_BY_ZERO_TRAP_BIT_VEC.val.byte_array[2] = 128;
    init_static_bit_vector(&(DIVISION_BY_ZERO_TRAP_INDEX), 32);
    bit_vector_clear(&DIVISION_BY_ZERO_TRAP_INDEX);
    DIVISION_BY_ZERO_TRAP_INDEX.val.byte_array[0] = 22;
    init_static_bit_vector(&(DP_round_mid), 10);
    bit_vector_clear(&DP_round_mid);
    DP_round_mid.val.byte_array[1] = 2;
    register_pipe("ENV_to_AJIT_access_error", 2, 8, 0);
    register_pipe("ENV_to_AJIT_data", 2, 64, 0);
    register_pipe("ENV_to_AJIT_debug_command", 1, 32, 0);
    register_signal("ENV_to_AJIT_irl", 4);
    register_signal("ENV_to_AJIT_reset", 8);
    register_signal("ENV_to_AJIT_reset_0", 8);
    register_signal("ENV_to_AJIT_reset_1", 8);
    register_signal("ENV_to_AJIT_reset_2", 8);
    register_signal("ENV_to_AJIT_reset_3", 8);
    register_pipe("ENV_to_CORE_0_debug_command", 1, 32, 0);
    register_pipe("ENV_to_CORE_1_debug_command", 1, 32, 0);
    register_pipe("ENV_to_CORE_2_debug_command", 1, 32, 0);
    register_pipe("ENV_to_CORE_3_debug_command", 1, 32, 0);
    register_pipe("ENV_to_CORE_debug_command", 1, 32, 0);
    register_signal("ENV_to_CORE_irl", 4);
    register_signal("ENV_to_CORE_reset", 8);
    register_signal("ENV_to_CPU_irl", 4);
    init_static_bit_vector(&(EXCEPTION_FOUND), 8);
    bit_vector_clear(&EXCEPTION_FOUND);
    EXCEPTION_FOUND.val.byte_array[0] = 2;
    register_signal("EXTERNAL_INTERRUPT", 1);
    register_pipe("FLASH_to_BRIDGE_RESPONSE", 2, 32, 0);
    init_static_bit_vector(&(FOUR_3), 3);
    bit_vector_clear(&FOUR_3);
    FOUR_3.val.byte_array[0] = 4;
    init_static_bit_vector(&(FP_DISABLED_TRAP_BIT_VEC), 32);
    bit_vector_clear(&FP_DISABLED_TRAP_BIT_VEC);
    FP_DISABLED_TRAP_BIT_VEC.val.byte_array[1] = 16;
    init_static_bit_vector(&(FP_DISABLED_TRAP_INDEX), 32);
    bit_vector_clear(&FP_DISABLED_TRAP_INDEX);
    FP_DISABLED_TRAP_INDEX.val.byte_array[0] = 11;
    init_static_bit_vector(&(FP_EXCEPTION_TRAP_BIT_VEC), 32);
    bit_vector_clear(&FP_EXCEPTION_TRAP_BIT_VEC);
    FP_EXCEPTION_TRAP_BIT_VEC.val.byte_array[2] = 4;
    init_static_bit_vector(&(FP_EXCEPTION_TRAP_INDEX), 32);
    bit_vector_clear(&FP_EXCEPTION_TRAP_INDEX);
    FP_EXCEPTION_TRAP_INDEX.val.byte_array[0] = 17;
    init_static_bit_vector(&(FP_INSTR), 3);
    bit_vector_clear(&FP_INSTR);
    FP_INSTR.val.byte_array[0] = 5;
    init_static_bit_vector(&(FRACTION_WIDTH_23), 6);
    bit_vector_clear(&FRACTION_WIDTH_23);
    FRACTION_WIDTH_23.val.byte_array[0] = 23;
    init_static_bit_vector(&(FRACTION_WIDTH_52), 6);
    bit_vector_clear(&FRACTION_WIDTH_52);
    FRACTION_WIDTH_52.val.byte_array[0] = 52;
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
    init_static_bit_vector(&(GDB_DBG_READ_INIT_NPC), 8);
    bit_vector_clear(&GDB_DBG_READ_INIT_NPC);
    GDB_DBG_READ_INIT_NPC.val.byte_array[0] = 29;
    init_static_bit_vector(&(GDB_DBG_READ_INIT_PC), 8);
    bit_vector_clear(&GDB_DBG_READ_INIT_PC);
    GDB_DBG_READ_INIT_PC.val.byte_array[0] = 28;
    init_static_bit_vector(&(GDB_DBG_READ_INIT_PSR), 8);
    bit_vector_clear(&GDB_DBG_READ_INIT_PSR);
    GDB_DBG_READ_INIT_PSR.val.byte_array[0] = 30;
    init_static_bit_vector(&(GDB_DBG_READ_IUNIT_REG), 8);
    bit_vector_clear(&GDB_DBG_READ_IUNIT_REG);
    GDB_DBG_READ_IUNIT_REG.val.byte_array[0] = 1;
    init_static_bit_vector(&(GDB_DBG_READ_MEM), 8);
    bit_vector_clear(&GDB_DBG_READ_MEM);
    GDB_DBG_READ_MEM.val.byte_array[0] = 6;
    init_static_bit_vector(&(GDB_DBG_READ_MODE), 8);
    bit_vector_clear(&GDB_DBG_READ_MODE);
    GDB_DBG_READ_MODE.val.byte_array[0] = 31;
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
    init_static_bit_vector(&(GDB_DBG_WRITE_INIT_NPC), 8);
    bit_vector_clear(&GDB_DBG_WRITE_INIT_NPC);
    GDB_DBG_WRITE_INIT_NPC.val.byte_array[0] = 26;
    init_static_bit_vector(&(GDB_DBG_WRITE_INIT_PC), 8);
    bit_vector_clear(&GDB_DBG_WRITE_INIT_PC);
    GDB_DBG_WRITE_INIT_PC.val.byte_array[0] = 25;
    init_static_bit_vector(&(GDB_DBG_WRITE_INIT_PSR), 8);
    bit_vector_clear(&GDB_DBG_WRITE_INIT_PSR);
    GDB_DBG_WRITE_INIT_PSR.val.byte_array[0] = 27;
    init_static_bit_vector(&(GDB_DBG_WRITE_IUNIT_REG), 8);
    bit_vector_clear(&GDB_DBG_WRITE_IUNIT_REG);
    GDB_DBG_WRITE_IUNIT_REG.val.byte_array[0] = 2;
    init_static_bit_vector(&(GDB_DBG_WRITE_MEM), 8);
    bit_vector_clear(&GDB_DBG_WRITE_MEM);
    GDB_DBG_WRITE_MEM.val.byte_array[0] = 7;
    init_static_bit_vector(&(GDB_DBG_WRITE_RESET), 8);
    bit_vector_clear(&GDB_DBG_WRITE_RESET);
    GDB_DBG_WRITE_RESET.val.byte_array[0] = 24;
    register_signal("GPIO_DIN", 8);
    register_signal("GPIO_DOUT", 8);
    register_pipe("GPIO_to_BRIDGE_RESPONSE", 2, 32, 0);
    init_static_bit_vector(&(HARDWARE_ERROR_TRAP_BIT_VEC), 8);
    bit_vector_clear(&HARDWARE_ERROR_TRAP_BIT_VEC);
    HARDWARE_ERROR_TRAP_BIT_VEC.val.byte_array[0] = 32;
    init_static_bit_vector(&(HARDWARE_ERROR_TRAP_INDEX), 8);
    bit_vector_clear(&HARDWARE_ERROR_TRAP_INDEX);
    HARDWARE_ERROR_TRAP_INDEX.val.byte_array[0] = 5;
    init_static_bit_vector(&(HARD_RESET_MASK), 8);
    bit_vector_clear(&HARD_RESET_MASK);
    HARD_RESET_MASK.val.byte_array[0] = 1;
    register_pipe("ICACHE_to_CPU_LOADSTORE_response", 2, 8, 0);
    register_pipe("ICACHE_to_CPU_reset_ack", 2, 8, 0);
    register_pipe("ICACHE_to_CPU_response", 24, 8, 0);
    register_pipe("ICACHE_to_MMU_addr", 2, 32, 0);
    register_pipe("ICACHE_to_MMU_asi", 2, 8, 0);
    register_pipe("ICACHE_to_MMU_request", 12, 8, 0);
    register_pipe("ICACHE_to_MMU_request_type", 2, 8, 0);
    register_pipe("ICACHE_to_RLUT", 2, 8, 0);
    init_static_bit_vector(&(IEEE_754_EXCEPTION_TRAP_BIT_VEC), 8);
    bit_vector_clear(&IEEE_754_EXCEPTION_TRAP_BIT_VEC);
    IEEE_754_EXCEPTION_TRAP_BIT_VEC.val.byte_array[0] = 2;
    init_static_bit_vector(&(IEEE_754_EXCEPTION_TRAP_INDEX), 8);
    bit_vector_clear(&IEEE_754_EXCEPTION_TRAP_INDEX);
    IEEE_754_EXCEPTION_TRAP_INDEX.val.byte_array[0] = 1;
    init_static_bit_vector(&(ILLEGAL_INSTR), 3);
    bit_vector_clear(&ILLEGAL_INSTR);
    ILLEGAL_INSTR.val.byte_array[0] = 7;
    init_static_bit_vector(&(ILLEGAL_INSTRUCTION_TRAP_BIT_VEC), 32);
    bit_vector_clear(&ILLEGAL_INSTRUCTION_TRAP_BIT_VEC);
    ILLEGAL_INSTRUCTION_TRAP_BIT_VEC.val.byte_array[1] = 4;
    init_static_bit_vector(&(ILLEGAL_INSTRUCTION_TRAP_INDEX), 32);
    bit_vector_clear(&ILLEGAL_INSTRUCTION_TRAP_INDEX);
    ILLEGAL_INSTRUCTION_TRAP_INDEX.val.byte_array[0] = 9;
    init_static_bit_vector(&(ILLEGAL_IU_INSTRUCTION_TRAP_BIT_VEC), 32);
    bit_vector_clear(&ILLEGAL_IU_INSTRUCTION_TRAP_BIT_VEC);
    ILLEGAL_IU_INSTRUCTION_TRAP_BIT_VEC.val.byte_array[1] = 8;
    init_static_bit_vector(&(ILLEGAL_IU_INSTRUCTION_TRAP_INDEX), 32);
    bit_vector_clear(&ILLEGAL_IU_INSTRUCTION_TRAP_INDEX);
    ILLEGAL_IU_INSTRUCTION_TRAP_INDEX.val.byte_array[0] = 10;
    init_static_bit_vector(&(INIT_ASR_AND_WINDOW_REGS), 3);
    bit_vector_clear(&INIT_ASR_AND_WINDOW_REGS);
    INIT_ASR_AND_WINDOW_REGS.val.byte_array[0] = 7;
    init_static_bit_vector(&(INSTRUCTION_ACCESS_ERROR_TRAP_BIT_VEC), 32);
    bit_vector_clear(&INSTRUCTION_ACCESS_ERROR_TRAP_BIT_VEC);
    INSTRUCTION_ACCESS_ERROR_TRAP_BIT_VEC.val.byte_array[0] = 128;
    init_static_bit_vector(&(INSTRUCTION_ACCESS_ERROR_TRAP_INDEX), 32);
    bit_vector_clear(&INSTRUCTION_ACCESS_ERROR_TRAP_INDEX);
    INSTRUCTION_ACCESS_ERROR_TRAP_INDEX.val.byte_array[0] = 6;
    init_static_bit_vector(&(INSTRUCTION_ACCESS_EXCEPTION_TRAP_BIT_VEC),
			   32);
    bit_vector_clear(&INSTRUCTION_ACCESS_EXCEPTION_TRAP_BIT_VEC);
    INSTRUCTION_ACCESS_EXCEPTION_TRAP_BIT_VEC.val.byte_array[0] = 16;
    init_static_bit_vector(&(INSTRUCTION_ACCESS_EXCEPTION_TRAP_INDEX), 32);
    bit_vector_clear(&INSTRUCTION_ACCESS_EXCEPTION_TRAP_INDEX);
    INSTRUCTION_ACCESS_EXCEPTION_TRAP_INDEX.val.byte_array[0] = 4;
    init_static_bit_vector(&(INTERRUPT_FOUND), 8);
    bit_vector_clear(&INTERRUPT_FOUND);
    INTERRUPT_FOUND.val.byte_array[0] = 1;
    register_signal("INTR_LEVEL", 4);
    register_signal("INTR_LEVEL_0", 4);
    register_signal("INTR_LEVEL_1", 4);
    register_signal("INTR_LEVEL_2", 4);
    register_signal("INTR_LEVEL_3", 4);
    init_static_bit_vector(&(INVALID_FP_REGISTER_TRAP_BIT_VEC), 8);
    bit_vector_clear(&INVALID_FP_REGISTER_TRAP_BIT_VEC);
    INVALID_FP_REGISTER_TRAP_BIT_VEC.val.byte_array[0] = 64;
    init_static_bit_vector(&(INVALID_FP_REGISTER_TRAP_INDEX), 8);
    bit_vector_clear(&INVALID_FP_REGISTER_TRAP_INDEX);
    INVALID_FP_REGISTER_TRAP_INDEX.val.byte_array[0] = 6;
    init_static_bit_vector(&(IN_LIVE_STREAM_ANNULLED), 3);
    bit_vector_clear(&IN_LIVE_STREAM_ANNULLED);
    IN_LIVE_STREAM_ANNULLED.val.byte_array[0] = 1;
    init_static_bit_vector(&(IN_LIVE_STREAM_NOT_ANNULLED), 3);
    bit_vector_clear(&IN_LIVE_STREAM_NOT_ANNULLED);
    register_pipe("IRC_to_BRIDGE_RESPONSE", 2, 32, 0);
    init_static_bit_vector(&(KILL_STREAM_MASK), 8);
    bit_vector_clear(&KILL_STREAM_MASK);
    KILL_STREAM_MASK.val.byte_array[0] = 128;
    init_static_bit_vector(&(KILL_THREAD_MASK), 8);
    bit_vector_clear(&KILL_THREAD_MASK);
    KILL_THREAD_MASK.val.byte_array[0] = 128;
    register_pipe("L2_REQUEST", 28, 8, 0);
    register_pipe("L2_RESPONSE", 2, 64, 0);
    init_static_bit_vector(&(LOGGER_ACTIVE_MASK), 8);
    bit_vector_clear(&LOGGER_ACTIVE_MASK);
    LOGGER_ACTIVE_MASK.val.byte_array[0] = 8;
    init_static_bit_vector(&(MACHINE_ERROR), 8);
    bit_vector_clear(&MACHINE_ERROR);
    MACHINE_ERROR.val.byte_array[0] = 3;
    init_static_bit_vector(&(MAE_TRAP_BIT_VEC), 32);
    bit_vector_clear(&MAE_TRAP_BIT_VEC);
    MAE_TRAP_BIT_VEC.val.byte_array[0] = 4;
    init_static_bit_vector(&(MAE_TRAP_INDEX), 32);
    bit_vector_clear(&MAE_TRAP_INDEX);
    MAE_TRAP_INDEX.val.byte_array[0] = 2;
    register_signal("MCORE_CORE_0_CPU_MODE", 4);
    register_signal("MCORE_CORE_0_RESET", 8);
    register_signal("MCORE_CORE_1_CPU_MODE", 4);
    register_signal("MCORE_CORE_1_RESET", 8);
    register_signal("MCORE_CORE_2_CPU_MODE", 4);
    register_signal("MCORE_CORE_2_RESET", 8);
    register_signal("MCORE_CORE_3_CPU_MODE", 4);
    register_signal("MCORE_CORE_3_RESET", 8);
    register_pipe("MCORE_SYS_BUS_REQUEST", 28, 8, 0);
    register_pipe("MCORE_SYS_BUS_RESPONSE", 2, 64, 0);
    init_static_bit_vector(&(MEM_ADDRESS_NOT_ALIGNED_TRAP_BIT_VEC), 32);
    bit_vector_clear(&MEM_ADDRESS_NOT_ALIGNED_TRAP_BIT_VEC);
    MEM_ADDRESS_NOT_ALIGNED_TRAP_BIT_VEC.val.byte_array[2] = 2;
    init_static_bit_vector(&(MEM_ADDRESS_NOT_ALIGNED_TRAP_INDEX), 32);
    bit_vector_clear(&MEM_ADDRESS_NOT_ALIGNED_TRAP_INDEX);
    MEM_ADDRESS_NOT_ALIGNED_TRAP_INDEX.val.byte_array[0] = 16;
    init_static_bit_vector(&(MISC_INSTR), 3);
    bit_vector_clear(&MISC_INSTR);
    MISC_INSTR.val.byte_array[0] = 4;
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
    register_pipe("MMU_to_CPU_reset_ack", 2, 8, 0);
    register_pipe("MMU_to_DCACHE_data", 8, 64, 0);
    register_pipe("MMU_to_DCACHE_flags", 2, 16, 0);
    register_pipe("MMU_to_DCACHE_response", 20, 8, 0);
    register_pipe("MMU_to_ICACHE_data", 2, 64, 0);
    register_pipe("MMU_to_ICACHE_flags", 2, 16, 0);
    register_pipe("MMU_to_ICACHE_fsr", 2, 32, 0);
    register_pipe("MMU_to_ICACHE_response", 24, 8, 0);
    register_pipe("MMU_to_RLUT", 2, 64, 0);
    register_pipe("MONITOR_to_DEBUG", 4, 8, 0);
    register_pipe("MONITOR_to_DEBUG_0", 4, 8, 0);
    register_pipe("MONITOR_to_DEBUG_1", 4, 8, 0);
    register_pipe("MONITOR_to_DEBUG_2", 4, 8, 0);
    register_pipe("MONITOR_to_DEBUG_3", 4, 8, 0);
    init_static_bit_vector(&(NEW_STREAM_MASK), 8);
    bit_vector_clear(&NEW_STREAM_MASK);
    NEW_STREAM_MASK.val.byte_array[0] = 128;
    init_static_bit_vector(&(NEW_THREAD_MASK), 8);
    bit_vector_clear(&NEW_THREAD_MASK);
    NEW_THREAD_MASK.val.byte_array[0] = 128;
    register_pipe("NOBLOCK_CPU_LOADSTORE_to_ICACHE_command", 12, 8, 2);
    register_pipe("NOBLOCK_CPU_to_DCACHE_command", 16, 8, 2);
    register_pipe("NOBLOCK_CPU_to_DCACHE_reset", 2, 8, 2);
    register_pipe("NOBLOCK_CPU_to_DCACHE_slow_command", 16, 8, 2);
    register_pipe("NOBLOCK_CPU_to_ICACHE_command", 6, 8, 2);
    register_pipe("NOBLOCK_CPU_to_ICACHE_reset", 2, 8, 2);
    register_pipe("NOBLOCK_CPU_to_MMU_reset", 2, 8, 2);
    register_pipe("NOBLOCK_RLUT_to_DCACHE", 16, 32, 0);
    register_pipe("NOBLOCK_RLUT_to_ICACHE", 16, 32, 0);
    init_static_bit_vector(&(NONE_TRAP_BIT_VEC), 8);
    bit_vector_clear(&NONE_TRAP_BIT_VEC);
    NONE_TRAP_BIT_VEC.val.byte_array[0] = 1;
    init_static_bit_vector(&(NONE_TRAP_INDEX), 8);
    bit_vector_clear(&NONE_TRAP_INDEX);
    init_static_bit_vector(&(NOP_INSTRUCTION), 32);
    bit_vector_clear(&NOP_INSTRUCTION);
    NOP_INSTRUCTION.val.byte_array[3] = 1;
    init_static_bit_vector(&(NO_BLOCK_READ), 1);
    bit_vector_clear(&NO_BLOCK_READ);
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
    init_static_bit_vector(&(ONE_11_S), 11);
    bit_vector_clear(&ONE_11_S);
    ONE_11_S.val.byte_array[0] = 255;
    ONE_11_S.val.byte_array[1] = 255;
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
    init_static_bit_vector(&(ONE_15), 15);
    bit_vector_clear(&ONE_15);
    ONE_15.val.byte_array[0] = 1;
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
    init_static_bit_vector(&(ONE_20), 20);
    bit_vector_clear(&ONE_20);
    ONE_20.val.byte_array[0] = 1;
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
    init_static_bit_vector(&(ONE_52), 52);
    bit_vector_clear(&ONE_52);
    ONE_52.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_54), 54);
    bit_vector_clear(&ONE_54);
    ONE_54.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_6), 6);
    bit_vector_clear(&ONE_6);
    ONE_6.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_60), 60);
    bit_vector_clear(&ONE_60);
    ONE_60.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_62), 62);
    bit_vector_clear(&ONE_62);
    ONE_62.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_63), 63);
    bit_vector_clear(&ONE_63);
    ONE_63.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_64), 64);
    bit_vector_clear(&ONE_64);
    ONE_64.val.byte_array[0] = 1;
    init_static_bit_vector(&(ONE_65), 65);
    bit_vector_clear(&ONE_65);
    ONE_65.val.byte_array[0] = 1;
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
    register_pipe("PERIPHERAL_AFB_BUS_REQUEST", 18, 8, 0);
    register_pipe("PERIPHERAL_AFB_BUS_RESPONSE", 10, 8, 0);
    init_static_bit_vector(&(PRIVILEGED_INSTRUCTION_TRAP_BIT_VEC), 32);
    bit_vector_clear(&PRIVILEGED_INSTRUCTION_TRAP_BIT_VEC);
    PRIVILEGED_INSTRUCTION_TRAP_BIT_VEC.val.byte_array[1] = 2;
    init_static_bit_vector(&(PRIVILEGED_INSTRUCTION_TRAP_INDEX), 32);
    bit_vector_clear(&PRIVILEGED_INSTRUCTION_TRAP_INDEX);
    PRIVILEGED_INSTRUCTION_TRAP_INDEX.val.byte_array[0] = 8;
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
    init_static_bit_vector(&(RESERVED_TRAP_BIT_VEC), 8);
    bit_vector_clear(&RESERVED_TRAP_BIT_VEC);
    RESERVED_TRAP_BIT_VEC.val.byte_array[0] = 128;
    init_static_bit_vector(&(RESERVED_TRAP_INDEX), 8);
    bit_vector_clear(&RESERVED_TRAP_INDEX);
    RESERVED_TRAP_INDEX.val.byte_array[0] = 7;
    init_static_bit_vector(&(RESET_TRAP_TRAP_BIT_VEC), 32);
    bit_vector_clear(&RESET_TRAP_TRAP_BIT_VEC);
    RESET_TRAP_TRAP_BIT_VEC.val.byte_array[0] = 2;
    init_static_bit_vector(&(RESET_TRAP_TRAP_INDEX), 32);
    bit_vector_clear(&RESET_TRAP_TRAP_INDEX);
    RESET_TRAP_TRAP_INDEX.val.byte_array[0] = 1;
    init_static_bit_vector(&(R_REGISTER_ACCESS_ERROR_TRAP_BIT_VEC), 32);
    bit_vector_clear(&R_REGISTER_ACCESS_ERROR_TRAP_BIT_VEC);
    R_REGISTER_ACCESS_ERROR_TRAP_BIT_VEC.val.byte_array[1] = 1;
    init_static_bit_vector(&(R_REGISTER_ACCESS_ERROR_TRAP_INDEX), 32);
    bit_vector_clear(&R_REGISTER_ACCESS_ERROR_TRAP_INDEX);
    R_REGISTER_ACCESS_ERROR_TRAP_INDEX.val.byte_array[0] = 7;
    init_static_bit_vector(&(SEQUENCE_ERROR_TRAP_BIT_VEC), 8);
    bit_vector_clear(&SEQUENCE_ERROR_TRAP_BIT_VEC);
    SEQUENCE_ERROR_TRAP_BIT_VEC.val.byte_array[0] = 16;
    init_static_bit_vector(&(SEQUENCE_ERROR_TRAP_INDEX), 8);
    bit_vector_clear(&SEQUENCE_ERROR_TRAP_INDEX);
    SEQUENCE_ERROR_TRAP_INDEX.val.byte_array[0] = 4;
    register_pipe("SERIAL_TX_to_CONSOLE", 2, 8, 0);
    register_signal("SERIAL_UART_BAUD_FREQ", 12);
    register_signal("SERIAL_UART_BAUD_LIMIT", 16);
    register_signal("SERIAL_UART_RX", 1);
    register_signal("SERIAL_UART_SOFT_RESET", 1);
    register_signal("SERIAL_UART_TX", 1);
    register_pipe("SERIAL_to_BRIDGE_RESPONSE", 2, 32, 0);
    register_signal("SERIAL_to_IRC_INTERRUPT_LINE", 1);
    init_static_bit_vector(&(SINGLE_STEP_MASK), 8);
    bit_vector_clear(&SINGLE_STEP_MASK);
    SINGLE_STEP_MASK.val.byte_array[0] = 4;
    register_pipe("SPI_to_BRIDGE_RESPONSE", 2, 32, 0);
    init_static_bit_vector(&(SP_round_mid), 39);
    bit_vector_clear(&SP_round_mid);
    SP_round_mid.val.byte_array[4] = 64;
    register_pipe("SYS_AFB_BUS_REQUEST", 18, 8, 0);
    register_pipe("SYS_AFB_BUS_RESPONSE", 10, 8, 0);
    init_static_bit_vector(&(TAG_OVERFLOW_TRAP_BIT_VEC), 32);
    bit_vector_clear(&TAG_OVERFLOW_TRAP_BIT_VEC);
    TAG_OVERFLOW_TRAP_BIT_VEC.val.byte_array[2] = 64;
    init_static_bit_vector(&(TAG_OVERFLOW_TRAP_INDEX), 32);
    bit_vector_clear(&TAG_OVERFLOW_TRAP_INDEX);
    TAG_OVERFLOW_TRAP_INDEX.val.byte_array[0] = 21;
    init_static_bit_vector(&(TERMINATES_STREAM), 3);
    bit_vector_clear(&TERMINATES_STREAM);
    TERMINATES_STREAM.val.byte_array[0] = 3;
    init_static_bit_vector(&(TERMINATES_THREAD), 3);
    bit_vector_clear(&TERMINATES_THREAD);
    TERMINATES_THREAD.val.byte_array[0] = 7;
    init_static_bit_vector(&(TEU_ANNUL_NEXT_INDEX), 8);
    bit_vector_clear(&TEU_ANNUL_NEXT_INDEX);
    TEU_ANNUL_NEXT_INDEX.val.byte_array[0] = 6;
    init_static_bit_vector(&(TEU_DBG_BREAK_POINT_INDEX), 8);
    bit_vector_clear(&TEU_DBG_BREAK_POINT_INDEX);
    TEU_DBG_BREAK_POINT_INDEX.val.byte_array[0] = 3;
    init_static_bit_vector(&(TEU_DBG_WATCH_POINT_INDEX), 8);
    bit_vector_clear(&TEU_DBG_WATCH_POINT_INDEX);
    TEU_DBG_WATCH_POINT_INDEX.val.byte_array[0] = 4;
    init_static_bit_vector(&(TEU_EXCEPTION_INDEX), 8);
    bit_vector_clear(&TEU_EXCEPTION_INDEX);
    TEU_EXCEPTION_INDEX.val.byte_array[0] = 2;
    init_static_bit_vector(&(TEU_FETCH_IS_SPINNING), 8);
    bit_vector_clear(&TEU_FETCH_IS_SPINNING);
    TEU_FETCH_IS_SPINNING.val.byte_array[0] = 7;
    init_static_bit_vector(&(TEU_INTERRUPT_INDEX), 8);
    bit_vector_clear(&TEU_INTERRUPT_INDEX);
    TEU_INTERRUPT_INDEX.val.byte_array[0] = 1;
    init_static_bit_vector(&(TEU_MACHINE_ERROR_INDEX), 8);
    bit_vector_clear(&TEU_MACHINE_ERROR_INDEX);
    init_static_bit_vector(&(TEU_SINGLE_STEP_INDEX), 8);
    bit_vector_clear(&TEU_SINGLE_STEP_INDEX);
    TEU_SINGLE_STEP_INDEX.val.byte_array[0] = 5;
    init_static_bit_vector(&(THREE_2), 2);
    bit_vector_clear(&THREE_2);
    THREE_2.val.byte_array[0] = 3;
    init_static_bit_vector(&(THREE_3), 3);
    bit_vector_clear(&THREE_3);
    THREE_3.val.byte_array[0] = 3;
    register_pipe("TIMER_to_BRIDGE_RESPONSE", 2, 32, 0);
    register_signal("TIMER_to_IRC_INTERRUPT_LINE", 1);
    init_static_bit_vector(&(TRACE_ON), 1);
    bit_vector_clear(&TRACE_ON);
    TRACE_ON.val.byte_array[0] = 1;
    init_static_bit_vector(&(TRAP_INSTRUCTION_TRAP_BIT_VEC), 32);
    bit_vector_clear(&TRAP_INSTRUCTION_TRAP_BIT_VEC);
    TRAP_INSTRUCTION_TRAP_BIT_VEC.val.byte_array[3] = 1;
    init_static_bit_vector(&(TRAP_INSTRUCTION_TRAP_INDEX), 32);
    bit_vector_clear(&TRAP_INSTRUCTION_TRAP_INDEX);
    TRAP_INSTRUCTION_TRAP_INDEX.val.byte_array[0] = 23;
    init_static_bit_vector(&(TRAP_TRAP_BIT_VEC), 32);
    bit_vector_clear(&TRAP_TRAP_BIT_VEC);
    TRAP_TRAP_BIT_VEC.val.byte_array[0] = 1;
    init_static_bit_vector(&(TRAP_TRAP_INDEX), 32);
    bit_vector_clear(&TRAP_TRAP_INDEX);
    init_static_bit_vector(&(TT_MASK), 32);
    bit_vector_clear(&TT_MASK);
    TT_MASK.val.byte_array[0] = 15;
    TT_MASK.val.byte_array[1] = 240;
    TT_MASK.val.byte_array[2] = 255;
    TT_MASK.val.byte_array[3] = 255;
    init_static_bit_vector(&(TWO_2), 2);
    bit_vector_clear(&TWO_2);
    TWO_2.val.byte_array[0] = 2;
    init_static_bit_vector(&(TWO_3), 3);
    bit_vector_clear(&TWO_3);
    TWO_3.val.byte_array[0] = 2;
    init_static_bit_vector(&(UNFINISHED_FPOP_TRAP_BIT_VEC), 8);
    bit_vector_clear(&UNFINISHED_FPOP_TRAP_BIT_VEC);
    UNFINISHED_FPOP_TRAP_BIT_VEC.val.byte_array[0] = 4;
    init_static_bit_vector(&(UNFINISHED_FPOP_TRAP_INDEX), 8);
    bit_vector_clear(&UNFINISHED_FPOP_TRAP_INDEX);
    UNFINISHED_FPOP_TRAP_INDEX.val.byte_array[0] = 2;
    init_static_bit_vector(&(UNIMPLEMENTED_FLUSH_TRAP_BIT_VEC), 32);
    bit_vector_clear(&UNIMPLEMENTED_FLUSH_TRAP_BIT_VEC);
    UNIMPLEMENTED_FLUSH_TRAP_BIT_VEC.val.byte_array[1] = 64;
    init_static_bit_vector(&(UNIMPLEMENTED_FLUSH_TRAP_INDEX), 32);
    bit_vector_clear(&UNIMPLEMENTED_FLUSH_TRAP_INDEX);
    UNIMPLEMENTED_FLUSH_TRAP_INDEX.val.byte_array[0] = 13;
    init_static_bit_vector(&(UNIMPLEMENTED_FPOP_TRAP_BIT_VEC), 8);
    bit_vector_clear(&UNIMPLEMENTED_FPOP_TRAP_BIT_VEC);
    UNIMPLEMENTED_FPOP_TRAP_BIT_VEC.val.byte_array[0] = 8;
    init_static_bit_vector(&(UNIMPLEMENTED_FPOP_TRAP_INDEX), 8);
    bit_vector_clear(&UNIMPLEMENTED_FPOP_TRAP_INDEX);
    UNIMPLEMENTED_FPOP_TRAP_INDEX.val.byte_array[0] = 3;
    init_static_bit_vector(&(WB_MISPREDICTED_STREAM), 2);
    bit_vector_clear(&WB_MISPREDICTED_STREAM);
    WB_MISPREDICTED_STREAM.val.byte_array[0] = 2;
    init_static_bit_vector(&(WB_NORMAL), 2);
    bit_vector_clear(&WB_NORMAL);
    WB_NORMAL.val.byte_array[0] = 1;
    init_static_bit_vector(&(WB_RESET), 2);
    bit_vector_clear(&WB_RESET);
    init_static_bit_vector(&(WB_TRAPPED), 2);
    bit_vector_clear(&WB_TRAPPED);
    WB_TRAPPED.val.byte_array[0] = 3;
    init_static_bit_vector(&(WIM_MASK), 32);
    bit_vector_clear(&WIM_MASK);
    WIM_MASK.val.byte_array[0] = 255;
    init_static_bit_vector(&(WINDOW_OVERFLOW_TRAP_BIT_VEC), 32);
    bit_vector_clear(&WINDOW_OVERFLOW_TRAP_BIT_VEC);
    WINDOW_OVERFLOW_TRAP_BIT_VEC.val.byte_array[1] = 128;
    init_static_bit_vector(&(WINDOW_OVERFLOW_TRAP_INDEX), 32);
    bit_vector_clear(&WINDOW_OVERFLOW_TRAP_INDEX);
    WINDOW_OVERFLOW_TRAP_INDEX.val.byte_array[0] = 14;
    init_static_bit_vector(&(WINDOW_UNDERFLOW_TRAP_BIT_VEC), 32);
    bit_vector_clear(&WINDOW_UNDERFLOW_TRAP_BIT_VEC);
    WINDOW_UNDERFLOW_TRAP_BIT_VEC.val.byte_array[2] = 1;
    init_static_bit_vector(&(WINDOW_UNDERFLOW_TRAP_INDEX), 32);
    bit_vector_clear(&WINDOW_UNDERFLOW_TRAP_INDEX);
    WINDOW_UNDERFLOW_TRAP_INDEX.val.byte_array[0] = 15;
    init_static_bit_vector(&(ZERO_1), 1);
    bit_vector_clear(&ZERO_1);
    init_static_bit_vector(&(ZERO_10), 10);
    bit_vector_clear(&ZERO_10);
    init_static_bit_vector(&(ZERO_104), 104);
    bit_vector_clear(&ZERO_104);
    init_static_bit_vector(&(ZERO_106), 106);
    bit_vector_clear(&ZERO_106);
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
    init_static_bit_vector(&(ZERO_15), 15);
    bit_vector_clear(&ZERO_15);
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
    init_static_bit_vector(&(ZERO_20), 20);
    bit_vector_clear(&ZERO_20);
    init_static_bit_vector(&(ZERO_22), 22);
    bit_vector_clear(&ZERO_22);
    init_static_bit_vector(&(ZERO_23), 23);
    bit_vector_clear(&ZERO_23);
    init_static_bit_vector(&(ZERO_24), 24);
    bit_vector_clear(&ZERO_24);
    init_static_bit_vector(&(ZERO_25), 25);
    bit_vector_clear(&ZERO_25);
    init_static_bit_vector(&(ZERO_256), 256);
    bit_vector_clear(&ZERO_256);
    init_static_bit_vector(&(ZERO_26), 26);
    bit_vector_clear(&ZERO_26);
    init_static_bit_vector(&(ZERO_28), 28);
    bit_vector_clear(&ZERO_28);
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
    init_static_bit_vector(&(ZERO_42), 42);
    bit_vector_clear(&ZERO_42);
    init_static_bit_vector(&(ZERO_48), 48);
    bit_vector_clear(&ZERO_48);
    init_static_bit_vector(&(ZERO_5), 5);
    bit_vector_clear(&ZERO_5);
    init_static_bit_vector(&(ZERO_51), 51);
    bit_vector_clear(&ZERO_51);
    init_static_bit_vector(&(ZERO_52), 52);
    bit_vector_clear(&ZERO_52);
    init_static_bit_vector(&(ZERO_54), 54);
    bit_vector_clear(&ZERO_54);
    init_static_bit_vector(&(ZERO_55), 55);
    bit_vector_clear(&ZERO_55);
    init_static_bit_vector(&(ZERO_6), 6);
    bit_vector_clear(&ZERO_6);
    init_static_bit_vector(&(ZERO_60), 60);
    bit_vector_clear(&ZERO_60);
    init_static_bit_vector(&(ZERO_61), 61);
    bit_vector_clear(&ZERO_61);
    init_static_bit_vector(&(ZERO_62), 62);
    bit_vector_clear(&ZERO_62);
    init_static_bit_vector(&(ZERO_63), 63);
    bit_vector_clear(&ZERO_63);
    init_static_bit_vector(&(ZERO_64), 64);
    bit_vector_clear(&ZERO_64);
    init_static_bit_vector(&(ZERO_7), 7);
    bit_vector_clear(&ZERO_7);
    init_static_bit_vector(&(ZERO_8), 8);
    bit_vector_clear(&ZERO_8);
    init_static_bit_vector(&(ZERO_9), 9);
    bit_vector_clear(&ZERO_9);
    register_pipe("ccu_to_debug_interface", 20, 8, 2);
    register_pipe("ccu_to_teu", 28, 8, 2);
    register_pipe("ccu_to_teu_debug_command", 2, 8, 0);
    register_pipe("ccu_to_teu_fpunit_register_access_command", 10, 8, 2);
    register_pipe("ccu_to_teu_iunit_register_access_command", 12, 8, 2);
    register_pipe("ccu_to_teu_load_store_command", 20, 8, 0);
    register_signal("debug_bp_0", 32);
    register_signal("debug_bp_1", 32);
    register_signal("debug_bp_2", 32);
    register_signal("debug_bp_3", 32);
    register_signal("debug_dbg_interrupt", 1);
    register_pipe("debug_interface_to_ccu", 20, 8, 2);
    register_signal("debug_wp_0", 32);
    register_signal("debug_wp_1", 32);
    register_signal("debug_wp_2", 32);
    register_signal("debug_wp_3", 32);
    init_static_bit_vector(&(default_mem_pool[0]), 8);
    init_static_bit_vector(&(exp_base_0), 13);
    bit_vector_clear(&exp_base_0);
    init_static_bit_vector(&(exp_base_1), 13);
    bit_vector_clear(&exp_base_1);
    exp_base_1.val.byte_array[0] = 1;
    init_static_bit_vector(&(exp_base_1022), 13);
    bit_vector_clear(&exp_base_1022);
    exp_base_1022.val.byte_array[0] = 254;
    exp_base_1022.val.byte_array[1] = 3;
    init_static_bit_vector(&(exp_base_1023), 13);
    bit_vector_clear(&exp_base_1023);
    exp_base_1023.val.byte_array[0] = 255;
    exp_base_1023.val.byte_array[1] = 3;
    init_static_bit_vector(&(exp_base_126), 13);
    bit_vector_clear(&exp_base_126);
    exp_base_126.val.byte_array[0] = 126;
    init_static_bit_vector(&(exp_base_127), 13);
    bit_vector_clear(&exp_base_127);
    exp_base_127.val.byte_array[0] = 127;
    init_static_bit_vector(&(exp_base_24), 13);
    bit_vector_clear(&exp_base_24);
    exp_base_24.val.byte_array[0] = 24;
    init_static_bit_vector(&(exp_base_254), 13);
    bit_vector_clear(&exp_base_254);
    exp_base_254.val.byte_array[0] = 254;
    init_static_bit_vector(&(exp_base_53), 13);
    bit_vector_clear(&exp_base_53);
    exp_base_53.val.byte_array[0] = 53;
    init_static_bit_vector(&(exp_base_neg_1022), 13);
    bit_vector_clear(&exp_base_neg_1022);
    exp_base_neg_1022.val.byte_array[0] = 2;
    exp_base_neg_1022.val.byte_array[1] = 252;
    init_static_bit_vector(&(exp_base_neg_126), 13);
    bit_vector_clear(&exp_base_neg_126);
    exp_base_neg_126.val.byte_array[0] = 130;
    exp_base_neg_126.val.byte_array[1] = 255;
    init_static_bit_vector(&(expbase_1022), 13);
    bit_vector_clear(&expbase_1022);
    expbase_1022.val.byte_array[0] = 254;
    expbase_1022.val.byte_array[1] = 3;
    init_static_bit_vector(&(expbase_1023), 13);
    bit_vector_clear(&expbase_1023);
    expbase_1023.val.byte_array[0] = 255;
    expbase_1023.val.byte_array[1] = 3;
    init_static_bit_vector(&(expbase_126), 10);
    bit_vector_clear(&expbase_126);
    expbase_126.val.byte_array[0] = 126;
    init_static_bit_vector(&(expbase_127), 10);
    bit_vector_clear(&expbase_127);
    expbase_127.val.byte_array[0] = 127;
    register_pipe("fpunit_exec_to_writeback", 24, 8, 0);
    register_pipe("fpunit_exec_to_writeback_fast", 24, 8, 0);
    register_pipe("fpunit_exec_to_writeback_slow", 24, 8, 0);
    register_pipe("fpunit_register_file_read_access_response", 88, 8, 0);
    register_pipe("fpunit_register_file_write_access_command", 18, 8, 2);
    register_pipe("fpunit_register_file_write_access_response", 6, 8, 0);
    register_pipe("noblock_CORE_0_BUS_REQUEST", 28, 8, 2);
    register_pipe("noblock_CORE_1_BUS_REQUEST", 28, 8, 2);
    register_pipe("noblock_CORE_2_BUS_REQUEST", 28, 8, 2);
    register_pipe("noblock_CORE_3_BUS_REQUEST", 28, 8, 2);
    register_pipe("noblock_CORE_BUS_REQUEST", 28, 8, 2);
    register_pipe("noblock_fpunit_exec_bypass_signal_to_register_file", 12,
		  8, 2);
    register_pipe("noblock_fpunit_exec_to_regfile_credit_return", 2, 8, 2);
    register_pipe("noblock_teu_idispatch_sstream_correction_to_ifetch", 26,
		  8, 2);
    register_pipe
	("noblock_teu_idispatch_to_fpunit_register_file_read_access_command",
	 12, 8, 2);
    register_pipe("noblock_teu_idispatch_to_fpunit_writeback", 48, 8, 2);
    register_pipe("noblock_teu_idispatch_to_ifetch", 19, 8, 2);
    register_pipe
	("noblock_teu_idispatch_to_iunit_register_file_read_access_command",
	 16, 8, 2);
    register_pipe("noblock_teu_idispatch_to_iunit_writeback", 66, 8, 2);
    register_pipe("noblock_teu_idispatch_to_loadstore", 64, 8, 2);
    register_pipe("noblock_teu_loadstore_to_fpunit_regfile_credit_return",
		  2, 8, 2);
    register_pipe("noblock_teu_loadstore_to_iunit_regfile_credit_return",
		  2, 8, 2);
    register_pipe
	("noblock_teu_stream_corrector_to_fpunit_regfile_credit_return", 2,
	 8, 2);
    register_pipe("noblock_teu_stream_corrector_to_idispatch", 19, 8, 2);
    register_pipe("noblock_teu_stream_corrector_to_iretire", 152, 8, 2);
    register_pipe
	("noblock_teu_stream_corrector_to_iunit_regfile_credit_return", 2,
	 8, 2);
    register_pipe("teu_debug_to_ccu_response", 2, 8, 0);
    register_pipe("teu_fpunit_cc_to_stream_corrector", 4, 8, 0);
    register_pipe("teu_fpunit_register_file_to_loadstore", 20, 8, 0);
    register_pipe("teu_fpunit_to_iretire", 28, 8, 0);
    register_pipe("teu_fpunit_trap_to_iunit", 4, 8, 0);
    register_pipe("teu_fpunit_trap_to_loadstore", 4, 8, 0);
    register_pipe("teu_idispatch_to_fpunit_exec", 80, 8, 0);
    register_pipe("teu_idispatch_to_iunit_exec", 40, 8, 0);
    register_pipe("teu_idispatch_to_stream_corrector", 26, 8, 0);
    register_pipe("teu_ifetch_to_idecode", 24, 8, 0);
    register_pipe("teu_iretire_to_idispatch", 1, 8, 0);
    register_pipe("teu_iretire_to_iexception", 27, 8, 0);
    register_pipe("teu_iunit_cc_to_stream_corrector", 6, 8, 0);
    register_pipe("teu_iunit_register_file_to_loadstore", 36, 8, 0);
    register_pipe("teu_iunit_to_iretire", 48, 8, 0);
    register_pipe("teu_iunit_to_stream_corrector", 12, 8, 0);
    register_pipe("teu_iunit_trap_to_fpunit", 4, 8, 0);
    register_pipe("teu_iunit_trap_to_loadstore", 2, 8, 0);
    register_pipe("teu_loadstore_to_fpunit", 20, 8, 0);
    register_pipe("teu_loadstore_to_iretire", 28, 8, 0);
    register_pipe("teu_loadstore_to_iunit", 10, 8, 0);
    register_pipe("teu_stream_corrector_to_fpunit", 6, 8, 0);
    register_pipe("teu_stream_corrector_to_iunit", 6, 8, 0);
    register_pipe("teu_stream_corrector_to_loadstore", 6, 8, 0);
    register_pipe("teu_to_ccu", 58, 8, 0);
    register_pipe("teu_to_ccu_fpunit_register_access_response", 10, 8, 0);
    register_pipe("teu_to_ccu_iunit_register_access_response", 2, 32, 0);
    register_pipe("teu_to_ccu_load_store_response", 10, 8, 0);
    init_static_bit_vector(&(value_24), 7);
    bit_vector_clear(&value_24);
    value_24.val.byte_array[0] = 24;
    init_static_bit_vector(&(value_38), 6);
    bit_vector_clear(&value_38);
    value_38.val.byte_array[0] = 38;
    init_static_bit_vector(&(value_53), 7);
    bit_vector_clear(&value_53);
    value_53.val.byte_array[0] = 53;
    init_static_bit_vector(&(value_62), 6);
    bit_vector_clear(&value_62);
    value_62.val.byte_array[0] = 62;
    init_static_bit_vector(&(value_9), 6);
    bit_vector_clear(&value_9);
    value_9.val.byte_array[0] = 9;
}
void
_fpunit_exec_exec_DoubleToExtendedFp_(bit_vector * __puf1_d,
				      bit_vector * __pf1_d_class,
				      bit_vector * __presult)
{
    MUTEX_DECL
	(fpunit_exec_exec__DoubleToExtendedFp_series_block_stmt_1309_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__DoubleToExtendedFp_series_block_stmt_1309_c_mutex_);
    fpunit_exec_exec__DoubleToExtendedFp_inner_inarg_prep_macro__;
    // sign_d := (uf1_d [] 63 ) $buffering 1
    fpunit_exec_exec__DoubleToExtendedFp_assign_stmt_1318_c_macro_;
    // exp_d := ( $slice uf1_d 62 52 ) $buffering 1
    fpunit_exec_exec__DoubleToExtendedFp_assign_stmt_1322_c_macro_;
    // mant_d := ( $slice uf1_d 51 0 ) $buffering 1
    fpunit_exec_exec__DoubleToExtendedFp_assign_stmt_1326_c_macro_;
    // f1_pos_normal := ( $slice f1_d_class 9 9 ) $buffering 1
    fpunit_exec_exec__DoubleToExtendedFp_assign_stmt_1330_c_macro_;
    // f1_neg_normal := ( $slice f1_d_class 8 8 ) $buffering 1
    fpunit_exec_exec__DoubleToExtendedFp_assign_stmt_1334_c_macro_;
    // f1_pos_denormal := ( $slice f1_d_class 7 7 ) $buffering 1
    fpunit_exec_exec__DoubleToExtendedFp_assign_stmt_1338_c_macro_;
    // f1_neg_denormal := ( $slice f1_d_class 6 6 ) $buffering 1
    fpunit_exec_exec__DoubleToExtendedFp_assign_stmt_1342_c_macro_;
    // f1_qnan := ( $slice f1_d_class 5 5 ) $buffering 1
    fpunit_exec_exec__DoubleToExtendedFp_assign_stmt_1346_c_macro_;
    // f1_snan := ( $slice f1_d_class 4 4 ) $buffering 1
    fpunit_exec_exec__DoubleToExtendedFp_assign_stmt_1350_c_macro_;
    // f1_pos_inf := ( $slice f1_d_class 3 3 ) $buffering 1
    fpunit_exec_exec__DoubleToExtendedFp_assign_stmt_1354_c_macro_;
    // f1_neg_inf := ( $slice f1_d_class 2 2 ) $buffering 1
    fpunit_exec_exec__DoubleToExtendedFp_assign_stmt_1358_c_macro_;
    // f1_pos_zero := ( $slice f1_d_class 1 1 ) $buffering 1
    fpunit_exec_exec__DoubleToExtendedFp_assign_stmt_1362_c_macro_;
    // f1_neg_zero := ( $slice f1_d_class 0 0 ) $buffering 1
    fpunit_exec_exec__DoubleToExtendedFp_assign_stmt_1366_c_macro_;
    // f1_denormal := (f1_pos_denormal | f1_neg_denormal) $buffering 1
    fpunit_exec_exec__DoubleToExtendedFp_assign_stmt_1371_c_macro_;
    // f1_zero := (f1_pos_zero | f1_neg_zero) $buffering 1
    fpunit_exec_exec__DoubleToExtendedFp_assign_stmt_1376_c_macro_;
    // bias := ( $mux f1_denormal exp_base_1022 exp_base_1023 ) $buffering 
    // 1
    fpunit_exec_exec__DoubleToExtendedFp_assign_stmt_1382_c_macro_;
    // exp_a := ($bitcast ($uint<13>) (($bitcast ($int<13>) exp_d ) -
    // bias) ) $buffering 1
    fpunit_exec_exec__DoubleToExtendedFp_assign_stmt_1389_c_macro_;
    // man_52 := mant_d $buffering 1
    fpunit_exec_exec__DoubleToExtendedFp_assign_stmt_1392_c_macro_;
    // top_bit := (( ~ f1_denormal ) & ( ~ f1_zero )) $buffering 1
    fpunit_exec_exec__DoubleToExtendedFp_assign_stmt_1399_c_macro_;
    // result := ((sign_d && exp_a) && (top_bit && man_52)) $buffering 1
    fpunit_exec_exec__DoubleToExtendedFp_assign_stmt_1408_c_macro_;
    fpunit_exec_exec__DoubleToExtendedFp_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__DoubleToExtendedFp_series_block_stmt_1309_c_mutex_);
}
void
_fpunit_exec_exec_DoubleToSingle_(double *__pf1_d,
				  bit_vector * __pneeds_norm,
				  bit_vector * __pextn_result)
{
    MUTEX_DECL
	(fpunit_exec_exec__DoubleToSingle_series_block_stmt_1924_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__DoubleToSingle_series_block_stmt_1924_c_mutex_);
    fpunit_exec_exec__DoubleToSingle_inner_inarg_prep_macro__;
    // $volatile uf1_d := ($bitcast ($uint<64>) f1_d ) $buffering 1
    fpunit_exec_exec__DoubleToSingle_assign_stmt_1932_c_macro_;
    // $volatile sign_d := (uf1_d [] 63 ) $buffering 1
    fpunit_exec_exec__DoubleToSingle_assign_stmt_1937_c_macro_;
    // $volatile exp_d := ( $slice uf1_d 62 52 ) $buffering 1
    fpunit_exec_exec__DoubleToSingle_assign_stmt_1941_c_macro_;
    // $volatile mant_d := ( $slice uf1_d 51 0 ) $buffering 1
    fpunit_exec_exec__DoubleToSingle_assign_stmt_1945_c_macro_;
    // $volatile $call classify_64 (f1_d ) (f1_zero f1_normal f1_denormal
    // f1_inf f1_nan ) 
    fpunit_exec_exec__DoubleToSingle_call_stmt_1952_c_macro_;
    // $volatile bias := ( $mux f1_denormal exp_base_1022 exp_base_1023 )
    // $buffering 1
    fpunit_exec_exec__DoubleToSingle_assign_stmt_1958_c_macro_;
    // $volatile exp_without_bias := (($bitcast ($int<13>) exp_d ) - bias) 
    // $buffering 1
    fpunit_exec_exec__DoubleToSingle_assign_stmt_1964_c_macro_;
    // $volatile mantissa_msb := ( $mux f1_denormal ZERO_1 ONE_1 )
    // $buffering 1
    fpunit_exec_exec__DoubleToSingle_assign_stmt_1970_c_macro_;
    // $volatile mantissa_53_bits := (mantissa_msb && mant_d) $buffering 1
    fpunit_exec_exec__DoubleToSingle_assign_stmt_1975_c_macro_;
    // $volatile $call find_left_53 (mantissa_53_bits ) (top_bit_pos
    // top_bit_found ) 
    fpunit_exec_exec__DoubleToSingle_call_stmt_1979_c_macro_;
    // shift_amount := (52 - top_bit_pos) $buffering 1// bits of buffering 
    // = 6. 
    fpunit_exec_exec__DoubleToSingle_assign_stmt_1984_c_macro_;
    // $volatile $call i53_sll (mantissa_53_bits shift_amount )
    // (mantissa_53_aligned ) 
    fpunit_exec_exec__DoubleToSingle_call_stmt_1988_c_macro_;
    // $volatile exp_without_bias_adjusted := (exp_without_bias -
    // ($bitcast ($int<13>) shift_amount )) $buffering 1
    fpunit_exec_exec__DoubleToSingle_assign_stmt_1994_c_macro_;
    // $volatile overflow := (exp_without_bias_adjusted > 127 ) $buffering 
    // 1
    fpunit_exec_exec__DoubleToSingle_assign_stmt_1999_c_macro_;
    // $volatile underflow := (exp_without_bias_adjusted < (0 - 126 ))
    // $buffering 1
    fpunit_exec_exec__DoubleToSingle_assign_stmt_2006_c_macro_;
    // $volatile mantissa_62 := (( $slice mantissa_53_aligned 51 0 ) &&
    // ZERO_10) $buffering 1
    fpunit_exec_exec__DoubleToSingle_assign_stmt_2012_c_macro_;
    // $volatile exponent_to_be_passed := ((( $mux f1_nan ALL_ONE_13 _b0 ) 
    // | ( $mux (f1_inf | overflow) ALL_ONE_13 _b0 ) ) | (( $mux f1_zero
    // ($bitcast ($int<13>) ZERO_13 ) _b0 ) | ( $mux (( ~ overflow ) &
    // (f1_normal | f1_denormal)) exp_without_bias_adjusted _b0 ) ))
    // $buffering 1
    fpunit_exec_exec__DoubleToSingle_assign_stmt_2041_c_macro_;
    // $volatile mantissa_to_be_passed := ((( $mux f1_nan (ONE_1 &&
    // ZERO_61) _b0 ) | ( $mux (f1_inf | overflow) ZERO_62 _b0 ) ) | ((
    // $mux f1_zero ZERO_62 _b0 ) | ( $mux (( ~ overflow ) & (f1_normal |
    // f1_denormal)) mantissa_62 _b0 ) )) $buffering 1
    fpunit_exec_exec__DoubleToSingle_assign_stmt_2071_c_macro_;
    // needs_norm := (((underflow & ( ~ f1_nan )) & ( ~ f1_inf )) & (( ~
    // f1_zero ) & ( ~ overflow ))) $buffering 1// bits of buffering = 1. 
    fpunit_exec_exec__DoubleToSingle_assign_stmt_2086_c_macro_;
    // extn_result := (((ZERO_1 && ZERO_1) && (sign_d && f1_nan)) &&
    // (((f1_inf | overflow) && f1_zero) && (($bitcast ($uint<13>)
    // exponent_to_be_passed ) && mantissa_to_be_passed))) $buffering 1//
    // bits of buffering = 81. 
    fpunit_exec_exec__DoubleToSingle_assign_stmt_2106_c_macro_;
    fpunit_exec_exec__DoubleToSingle_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__DoubleToSingle_series_block_stmt_1924_c_mutex_);
}
void
_fpunit_exec_exec_SingleToDouble_(float *__pf1_s, double *__pf1_d)
{
    MUTEX_DECL
	(fpunit_exec_exec__SingleToDouble_series_block_stmt_2292_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__SingleToDouble_series_block_stmt_2292_c_mutex_);
    fpunit_exec_exec__SingleToDouble_inner_inarg_prep_macro__;
    // $volatile uf1_s := ($bitcast ($uint<32>) f1_s ) $buffering 1
    fpunit_exec_exec__SingleToDouble_assign_stmt_2298_c_macro_;
    // $volatile sign_s := (uf1_s [] 31 ) $buffering 1
    fpunit_exec_exec__SingleToDouble_assign_stmt_2303_c_macro_;
    // $volatile exp_s := ( $slice uf1_s 30 23 ) $buffering 1
    fpunit_exec_exec__SingleToDouble_assign_stmt_2307_c_macro_;
    // $volatile mant_s := ( $slice uf1_s 22 0 ) $buffering 1
    fpunit_exec_exec__SingleToDouble_assign_stmt_2311_c_macro_;
    // $volatile $call classify_32 (f1_s ) (f1_zero f1_normal f1_denormal
    // f1_inf f1_nan ) 
    fpunit_exec_exec__SingleToDouble_call_stmt_2318_c_macro_;
    // $volatile mantissa_msb := ( $mux f1_denormal ZERO_1 ONE_1 )
    // $buffering 1
    fpunit_exec_exec__SingleToDouble_assign_stmt_2324_c_macro_;
    // $volatile frac := (mantissa_msb && mant_s) $buffering 1
    fpunit_exec_exec__SingleToDouble_assign_stmt_2329_c_macro_;
    // $volatile bias := ( $mux f1_denormal exp_base_126 exp_base_127 )
    // $buffering 1
    fpunit_exec_exec__SingleToDouble_assign_stmt_2335_c_macro_;
    // $volatile exp_a := (($bitcast ($int<13>) exp_s ) - bias) $buffering 
    // 1
    fpunit_exec_exec__SingleToDouble_assign_stmt_2341_c_macro_;
    // $volatile $call find_left_24 (frac ) (position found ) 
    fpunit_exec_exec__SingleToDouble_call_stmt_2345_c_macro_;
    // $volatile left_shifts_required := (23 - position) $buffering 1
    fpunit_exec_exec__SingleToDouble_assign_stmt_2350_c_macro_;
    // $volatile $call i24_sll (frac left_shifts_required ) (frac_shifted
    // ) 
    fpunit_exec_exec__SingleToDouble_call_stmt_2354_c_macro_;
    // $volatile expon_normalized := (exp_a - ($bitcast ($int<13>)
    // left_shifts_required )) $buffering 1
    fpunit_exec_exec__SingleToDouble_assign_stmt_2360_c_macro_;
    // $volatile exp_11 := ($bitcast ($uint<11>) (expon_normalized +
    // exp_base_1023) ) $buffering 1
    fpunit_exec_exec__SingleToDouble_assign_stmt_2366_c_macro_;
    // $volatile man_52 := (( $slice frac_shifted 22 0 ) && ZERO_29)
    // $buffering 1
    fpunit_exec_exec__SingleToDouble_assign_stmt_2372_c_macro_;
    // $volatile result_norm_denorm := ((sign_s && exp_11) && man_52)
    // $buffering 1
    fpunit_exec_exec__SingleToDouble_assign_stmt_2379_c_macro_;
    // $volatile result_qnan := ((ZERO_1 && ALL_ONE_11) && (ONE_1 &&
    // ZERO_51)) $buffering 1
    fpunit_exec_exec__SingleToDouble_assign_stmt_2388_c_macro_;
    // $volatile result_zero := (sign_s && ZERO_63) $buffering 1
    fpunit_exec_exec__SingleToDouble_assign_stmt_2393_c_macro_;
    // $volatile result_infinity := ((sign_s && ALL_ONE_11) && ZERO_52)
    // $buffering 1
    fpunit_exec_exec__SingleToDouble_assign_stmt_2400_c_macro_;
    // $volatile result := ((( $mux (f1_normal | f1_denormal)
    // result_norm_denorm _b0 ) | ( $mux f1_nan result_qnan _b0 ) ) | ((
    // $mux f1_zero result_zero _b0 ) | ( $mux f1_inf result_infinity _b0
    // ) )) $buffering 1
    fpunit_exec_exec__SingleToDouble_assign_stmt_2423_c_macro_;
    // $volatile f1_d := ($bitcast ($float<11,52>) result ) $buffering 1
    fpunit_exec_exec__SingleToDouble_assign_stmt_2427_c_macro_;
    fpunit_exec_exec__SingleToDouble_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__SingleToDouble_series_block_stmt_2292_c_mutex_);
}
void
fpunit_exec_exec_SingleToDouble(float f1_s, double *f1_d)
{
    double          __f1_d;
    fpunit_exec_exec__SingleToDouble_outer_arg_decl_macro__;
    _fpunit_exec_exec_SingleToDouble_(&__f1_s, &__f1_d);
    fpunit_exec_exec__SingleToDouble_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_SingleToExtendedFp_(bit_vector * __puf1_s,
				      bit_vector * __pf1_s_class,
				      bit_vector * __presult)
{
    MUTEX_DECL
	(fpunit_exec_exec__SingleToExtendedFp_series_block_stmt_2429_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__SingleToExtendedFp_series_block_stmt_2429_c_mutex_);
    fpunit_exec_exec__SingleToExtendedFp_inner_inarg_prep_macro__;
    // $report (fpunit_exec SingleToExtendedFp_in_args uf1_s uf1_s
    // f1_s_class f1_s_class )
    fpunit_exec_exec__SingleToExtendedFp_stmt_2435_c_macro_;
    // sign_s := (uf1_s [] 31 ) $buffering 1
    fpunit_exec_exec__SingleToExtendedFp_assign_stmt_2440_c_macro_;
    // exp_s := ( $slice uf1_s 30 23 ) $buffering 1
    fpunit_exec_exec__SingleToExtendedFp_assign_stmt_2444_c_macro_;
    // mant_s := ( $slice uf1_s 22 0 ) $buffering 1
    fpunit_exec_exec__SingleToExtendedFp_assign_stmt_2448_c_macro_;
    // f1_pos_normal := ( $slice f1_s_class 9 9 ) $buffering 1
    fpunit_exec_exec__SingleToExtendedFp_assign_stmt_2452_c_macro_;
    // f1_neg_normal := ( $slice f1_s_class 8 8 ) $buffering 1
    fpunit_exec_exec__SingleToExtendedFp_assign_stmt_2456_c_macro_;
    // f1_pos_denormal := ( $slice f1_s_class 7 7 ) $buffering 1
    fpunit_exec_exec__SingleToExtendedFp_assign_stmt_2460_c_macro_;
    // f1_neg_denormal := ( $slice f1_s_class 6 6 ) $buffering 1
    fpunit_exec_exec__SingleToExtendedFp_assign_stmt_2464_c_macro_;
    // f1_qnan := ( $slice f1_s_class 5 5 ) $buffering 1
    fpunit_exec_exec__SingleToExtendedFp_assign_stmt_2468_c_macro_;
    // f1_snan := ( $slice f1_s_class 4 4 ) $buffering 1
    fpunit_exec_exec__SingleToExtendedFp_assign_stmt_2472_c_macro_;
    // f1_pos_inf := ( $slice f1_s_class 3 3 ) $buffering 1
    fpunit_exec_exec__SingleToExtendedFp_assign_stmt_2476_c_macro_;
    // f1_neg_inf := ( $slice f1_s_class 2 2 ) $buffering 1
    fpunit_exec_exec__SingleToExtendedFp_assign_stmt_2480_c_macro_;
    // f1_pos_zero := ( $slice f1_s_class 1 1 ) $buffering 1
    fpunit_exec_exec__SingleToExtendedFp_assign_stmt_2484_c_macro_;
    // f1_neg_zero := ( $slice f1_s_class 0 0 ) $buffering 1
    fpunit_exec_exec__SingleToExtendedFp_assign_stmt_2488_c_macro_;
    // f1_denormal := (f1_pos_denormal | f1_neg_denormal) $buffering 1
    fpunit_exec_exec__SingleToExtendedFp_assign_stmt_2493_c_macro_;
    // f1_zero := (f1_pos_zero | f1_neg_zero) $buffering 1
    fpunit_exec_exec__SingleToExtendedFp_assign_stmt_2498_c_macro_;
    // bias := ( $mux f1_denormal exp_base_126 exp_base_127 ) $buffering 1
    fpunit_exec_exec__SingleToExtendedFp_assign_stmt_2504_c_macro_;
    // $report (fpunit_exec SingleToExtendedFp_bias f1_denormal
    // f1_denormal exp_base_126 exp_base_126 exp_base_127 exp_base_127
    // bias bias )
    fpunit_exec_exec__SingleToExtendedFp_stmt_2509_c_macro_;
    // top_bit := (( ~ f1_denormal ) & ( ~ f1_zero )) $buffering 1
    fpunit_exec_exec__SingleToExtendedFp_assign_stmt_2516_c_macro_;
    // exp_a := ($bitcast ($uint<13>) (($bitcast ($int<13>) exp_s ) -
    // bias) ) $buffering 1
    fpunit_exec_exec__SingleToExtendedFp_assign_stmt_2523_c_macro_;
    // man_52 := (mant_s && ZERO_29) $buffering 1
    fpunit_exec_exec__SingleToExtendedFp_assign_stmt_2528_c_macro_;
    // $report (fpunit_exec SingleToExtendedFp_extended_result exp_s exp_s 
    // bias bias exp_a exp_a man_52 man_52 )
    fpunit_exec_exec__SingleToExtendedFp_stmt_2533_c_macro_;
    // result := ((sign_s && exp_a) && (top_bit && man_52)) $buffering 1
    fpunit_exec_exec__SingleToExtendedFp_assign_stmt_2542_c_macro_;
    fpunit_exec_exec__SingleToExtendedFp_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__SingleToExtendedFp_series_block_stmt_2429_c_mutex_);
}
void
_fpunit_exec_exec_absVal_(bit_vector * __pa, bit_vector * __pret_val)
{
    MUTEX_DECL(fpunit_exec_exec__absVal_series_block_stmt_2544_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__absVal_series_block_stmt_2544_c_mutex_);
    fpunit_exec_exec__absVal_inner_inarg_prep_macro__;
    // ret_val := (ZERO_1 && ( $slice a 14 0 ) ) $buffering 1
    fpunit_exec_exec__absVal_assign_stmt_2552_c_macro_;
    fpunit_exec_exec__absVal_inner_outarg_prep_macro__;
    MUTEX_UNLOCK(fpunit_exec_exec__absVal_series_block_stmt_2544_c_mutex_);
}
void
fpunit_exec_exec_absVal(uint16_t a, uint16_t * ret_val)
{
    fpunit_exec_exec__absVal_outer_arg_decl_macro__;
    _fpunit_exec_exec_absVal_(&__a, &__ret_val);
    fpunit_exec_exec__absVal_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_adder_11_(bit_vector * __pA, bit_vector * __pB,
			    bit_vector * __pCIN, bit_vector * __pSUM,
			    bit_vector * __pCOUT)
{
    MUTEX_DECL(fpunit_exec_exec__adder_11_series_block_stmt_2554_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__adder_11_series_block_stmt_2554_c_mutex_);
    fpunit_exec_exec__adder_11_inner_inarg_prep_macro__;
    // $volatile operand_A := ((ZERO_1 && A) && CIN) $buffering 1
    fpunit_exec_exec__adder_11_assign_stmt_2566_c_macro_;
    // $volatile operand_B := ((ZERO_1 && B) && CIN) $buffering 1
    fpunit_exec_exec__adder_11_assign_stmt_2573_c_macro_;
    // $volatile add_result := (operand_A + operand_B) $buffering 1
    fpunit_exec_exec__adder_11_assign_stmt_2578_c_macro_;
    // $volatile SUM := ( $slice add_result 10 1 ) $buffering 1
    fpunit_exec_exec__adder_11_assign_stmt_2582_c_macro_;
    // $volatile COUT := (add_result [] 11 ) $buffering 1
    fpunit_exec_exec__adder_11_assign_stmt_2587_c_macro_;
    fpunit_exec_exec__adder_11_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__adder_11_series_block_stmt_2554_c_mutex_);
}
void
_fpunit_exec_exec_adder_18_(bit_vector * __pA, bit_vector * __pB,
			    bit_vector * __pCIN, bit_vector * __pSUM,
			    bit_vector * __pCOUT)
{
    MUTEX_DECL(fpunit_exec_exec__adder_18_series_block_stmt_2589_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__adder_18_series_block_stmt_2589_c_mutex_);
    fpunit_exec_exec__adder_18_inner_inarg_prep_macro__;
    // $volatile operand_A := ((ZERO_1 && A) && CIN) $buffering 1
    fpunit_exec_exec__adder_18_assign_stmt_2601_c_macro_;
    // $volatile operand_B := ((ZERO_1 && B) && CIN) $buffering 1
    fpunit_exec_exec__adder_18_assign_stmt_2608_c_macro_;
    // $volatile add_result := (operand_A + operand_B) $buffering 1
    fpunit_exec_exec__adder_18_assign_stmt_2613_c_macro_;
    // $volatile SUM := ( $slice add_result 16 1 ) $buffering 1
    fpunit_exec_exec__adder_18_assign_stmt_2617_c_macro_;
    // $volatile COUT := (add_result [] 17 ) $buffering 1
    fpunit_exec_exec__adder_18_assign_stmt_2622_c_macro_;
    fpunit_exec_exec__adder_18_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__adder_18_series_block_stmt_2589_c_mutex_);
}
void
_fpunit_exec_exec_adder_19_(bit_vector * __pA, bit_vector * __pB,
			    bit_vector * __pCIN, bit_vector * __pSUM,
			    bit_vector * __pCOUT)
{
    MUTEX_DECL(fpunit_exec_exec__adder_19_series_block_stmt_2624_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__adder_19_series_block_stmt_2624_c_mutex_);
    fpunit_exec_exec__adder_19_inner_inarg_prep_macro__;
    // $volatile operand_A := ((ZERO_1 && A) && CIN) $buffering 1
    fpunit_exec_exec__adder_19_assign_stmt_2636_c_macro_;
    // $volatile operand_B := ((ZERO_1 && B) && CIN) $buffering 1
    fpunit_exec_exec__adder_19_assign_stmt_2643_c_macro_;
    // $volatile add_result := (operand_A + operand_B) $buffering 1
    fpunit_exec_exec__adder_19_assign_stmt_2648_c_macro_;
    // $volatile SUM := ( $slice add_result 17 1 ) $buffering 1
    fpunit_exec_exec__adder_19_assign_stmt_2652_c_macro_;
    // $volatile COUT := (add_result [] 18 ) $buffering 1
    fpunit_exec_exec__adder_19_assign_stmt_2657_c_macro_;
    fpunit_exec_exec__adder_19_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__adder_19_series_block_stmt_2624_c_mutex_);
}
void
_fpunit_exec_exec_adder_35_with_carry_(bit_vector * __pA,
				       bit_vector * __pB,
				       bit_vector * __pCIN,
				       bit_vector * __pSUM,
				       bit_vector * __pCOUT)
{
    MUTEX_DECL
	(fpunit_exec_exec__adder_35_with_carry_series_block_stmt_2659_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__adder_35_with_carry_series_block_stmt_2659_c_mutex_);
    fpunit_exec_exec__adder_35_with_carry_inner_inarg_prep_macro__;
    // S37 := (((ZERO_1 && A) && CIN) + ((ZERO_1 && B) && CIN)) $buffering 
    // 1
    fpunit_exec_exec__adder_35_with_carry_assign_stmt_2678_c_macro_;
    // SUM := ( $slice S37 35 1 ) $buffering 1
    fpunit_exec_exec__adder_35_with_carry_assign_stmt_2682_c_macro_;
    // COUT := (S37 [] 36 ) $buffering 1
    fpunit_exec_exec__adder_35_with_carry_assign_stmt_2687_c_macro_;
    fpunit_exec_exec__adder_35_with_carry_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__adder_35_with_carry_series_block_stmt_2659_c_mutex_);
}
void
_fpunit_exec_exec_adder_58_with_carry_(bit_vector * __pA,
				       bit_vector * __pB,
				       bit_vector * __pCIN,
				       bit_vector * __pSUM,
				       bit_vector * __pCOUT)
{
    MUTEX_DECL
	(fpunit_exec_exec__adder_58_with_carry_series_block_stmt_2689_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__adder_58_with_carry_series_block_stmt_2689_c_mutex_);
    fpunit_exec_exec__adder_58_with_carry_inner_inarg_prep_macro__;
    // $volatile A0 := ( $slice A 15 0 ) $buffering 1
    fpunit_exec_exec__adder_58_with_carry_assign_stmt_2698_c_macro_;
    // $volatile A1 := ( $slice A 31 16 ) $buffering 1
    fpunit_exec_exec__adder_58_with_carry_assign_stmt_2702_c_macro_;
    // $volatile A2 := ( $slice A 47 32 ) $buffering 1
    fpunit_exec_exec__adder_58_with_carry_assign_stmt_2706_c_macro_;
    // $volatile A3 := ( $slice A 57 48 ) $buffering 1
    fpunit_exec_exec__adder_58_with_carry_assign_stmt_2710_c_macro_;
    // $volatile B0 := ( $slice B 15 0 ) $buffering 1
    fpunit_exec_exec__adder_58_with_carry_assign_stmt_2714_c_macro_;
    // $volatile B1 := ( $slice B 31 16 ) $buffering 1
    fpunit_exec_exec__adder_58_with_carry_assign_stmt_2718_c_macro_;
    // $volatile B2 := ( $slice B 47 32 ) $buffering 1
    fpunit_exec_exec__adder_58_with_carry_assign_stmt_2722_c_macro_;
    // $volatile B3 := ( $slice B 57 48 ) $buffering 1
    fpunit_exec_exec__adder_58_with_carry_assign_stmt_2726_c_macro_;
    // $volatile $call adder_18 (A0 B0 CIN ) (CIN0_S0 CIN0_C0 ) 
    fpunit_exec_exec__adder_58_with_carry_call_stmt_2732_c_macro_;
    // $volatile $call adder_18 (A1 B1 ZERO_1 ) (CIN0_S1 CIN0_C1 ) 
    fpunit_exec_exec__adder_58_with_carry_call_stmt_2738_c_macro_;
    // $volatile $call adder_18 (A1 B1 ONE_1 ) (CIN1_S1 CIN1_C1 ) 
    fpunit_exec_exec__adder_58_with_carry_call_stmt_2744_c_macro_;
    // $volatile $call adder_18 (A2 B2 ZERO_1 ) (CIN0_S2 CIN0_C2 ) 
    fpunit_exec_exec__adder_58_with_carry_call_stmt_2750_c_macro_;
    // $volatile $call adder_18 (A2 B2 ONE_1 ) (CIN1_S2 CIN1_C2 ) 
    fpunit_exec_exec__adder_58_with_carry_call_stmt_2756_c_macro_;
    // $volatile $call adder_11 (A3 B3 ZERO_1 ) (CIN0_S3 CIN0_C3 ) 
    fpunit_exec_exec__adder_58_with_carry_call_stmt_2762_c_macro_;
    // $volatile $call adder_11 (A3 B3 ONE_1 ) (CIN1_S3 CIN1_C3 ) 
    fpunit_exec_exec__adder_58_with_carry_call_stmt_2768_c_macro_;
    // $volatile sum_0 := CIN0_S0 $buffering 1
    fpunit_exec_exec__adder_58_with_carry_assign_stmt_2771_c_macro_;
    // $volatile carry_0 := CIN0_C0 $buffering 1
    fpunit_exec_exec__adder_58_with_carry_assign_stmt_2774_c_macro_;
    // $volatile sum_1 := ( $mux carry_0 CIN1_S1 CIN0_S1 ) $buffering 1
    fpunit_exec_exec__adder_58_with_carry_assign_stmt_2780_c_macro_;
    // $volatile carry_1 := ( $mux carry_0 CIN1_C1 CIN0_C1 ) $buffering 1
    fpunit_exec_exec__adder_58_with_carry_assign_stmt_2786_c_macro_;
    // $volatile sum_2 := ( $mux carry_1 CIN1_S2 CIN0_S2 ) $buffering 1
    fpunit_exec_exec__adder_58_with_carry_assign_stmt_2792_c_macro_;
    // $volatile carry_2 := ( $mux carry_1 CIN1_C2 CIN0_C2 ) $buffering 1
    fpunit_exec_exec__adder_58_with_carry_assign_stmt_2798_c_macro_;
    // $volatile sum_3 := ( $mux carry_2 CIN1_S3 CIN0_S3 ) $buffering 1
    fpunit_exec_exec__adder_58_with_carry_assign_stmt_2804_c_macro_;
    // $volatile carry_3 := ( $mux carry_2 CIN1_C3 CIN0_C3 ) $buffering 1
    fpunit_exec_exec__adder_58_with_carry_assign_stmt_2810_c_macro_;
    // SUM := ((sum_3 && sum_2) && (sum_1 && sum_0)) $buffering 1
    fpunit_exec_exec__adder_58_with_carry_assign_stmt_2819_c_macro_;
    // COUT := carry_3 $buffering 1
    fpunit_exec_exec__adder_58_with_carry_assign_stmt_2822_c_macro_;
    fpunit_exec_exec__adder_58_with_carry_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__adder_58_with_carry_series_block_stmt_2689_c_mutex_);
}
void
_fpunit_exec_exec_adder_64_with_carry_(bit_vector * __pA,
				       bit_vector * __pB,
				       bit_vector * __pCIN,
				       bit_vector * __pSUM,
				       bit_vector * __pCOUT)
{
    MUTEX_DECL
	(fpunit_exec_exec__adder_64_with_carry_series_block_stmt_2824_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__adder_64_with_carry_series_block_stmt_2824_c_mutex_);
    fpunit_exec_exec__adder_64_with_carry_inner_inarg_prep_macro__;
    // $volatile A0 := ( $slice A 15 0 ) $buffering 1
    fpunit_exec_exec__adder_64_with_carry_assign_stmt_2833_c_macro_;
    // $volatile A1 := ( $slice A 31 16 ) $buffering 1
    fpunit_exec_exec__adder_64_with_carry_assign_stmt_2837_c_macro_;
    // $volatile A2 := ( $slice A 47 32 ) $buffering 1
    fpunit_exec_exec__adder_64_with_carry_assign_stmt_2841_c_macro_;
    // $volatile A3 := ( $slice A 63 48 ) $buffering 1
    fpunit_exec_exec__adder_64_with_carry_assign_stmt_2845_c_macro_;
    // $volatile B0 := ( $slice B 15 0 ) $buffering 1
    fpunit_exec_exec__adder_64_with_carry_assign_stmt_2849_c_macro_;
    // $volatile B1 := ( $slice B 31 16 ) $buffering 1
    fpunit_exec_exec__adder_64_with_carry_assign_stmt_2853_c_macro_;
    // $volatile B2 := ( $slice B 47 32 ) $buffering 1
    fpunit_exec_exec__adder_64_with_carry_assign_stmt_2857_c_macro_;
    // $volatile B3 := ( $slice B 63 48 ) $buffering 1
    fpunit_exec_exec__adder_64_with_carry_assign_stmt_2861_c_macro_;
    // $volatile $call adder_18 (A0 B0 CIN ) (CIN0_S0 CIN0_C0 ) 
    fpunit_exec_exec__adder_64_with_carry_call_stmt_2867_c_macro_;
    // $volatile $call adder_18 (A1 B1 ZERO_1 ) (CIN0_S1 CIN0_C1 ) 
    fpunit_exec_exec__adder_64_with_carry_call_stmt_2873_c_macro_;
    // $volatile $call adder_18 (A1 B1 ONE_1 ) (CIN1_S1 CIN1_C1 ) 
    fpunit_exec_exec__adder_64_with_carry_call_stmt_2879_c_macro_;
    // $volatile $call adder_18 (A2 B2 ZERO_1 ) (CIN0_S2 CIN0_C2 ) 
    fpunit_exec_exec__adder_64_with_carry_call_stmt_2885_c_macro_;
    // $volatile $call adder_18 (A2 B2 ONE_1 ) (CIN1_S2 CIN1_C2 ) 
    fpunit_exec_exec__adder_64_with_carry_call_stmt_2891_c_macro_;
    // $volatile $call adder_18 (A3 B3 ZERO_1 ) (CIN0_S3 CIN0_C3 ) 
    fpunit_exec_exec__adder_64_with_carry_call_stmt_2897_c_macro_;
    // $volatile $call adder_18 (A3 B3 ONE_1 ) (CIN1_S3 CIN1_C3 ) 
    fpunit_exec_exec__adder_64_with_carry_call_stmt_2903_c_macro_;
    // $volatile sum_0 := CIN0_S0 $buffering 1
    fpunit_exec_exec__adder_64_with_carry_assign_stmt_2906_c_macro_;
    // $volatile carry_0 := CIN0_C0 $buffering 1
    fpunit_exec_exec__adder_64_with_carry_assign_stmt_2909_c_macro_;
    // $volatile sum_1 := ( $mux carry_0 CIN1_S1 CIN0_S1 ) $buffering 1
    fpunit_exec_exec__adder_64_with_carry_assign_stmt_2915_c_macro_;
    // $volatile carry_1 := ( $mux carry_0 CIN1_C1 CIN0_C1 ) $buffering 1
    fpunit_exec_exec__adder_64_with_carry_assign_stmt_2921_c_macro_;
    // $volatile sum_2 := ( $mux carry_1 CIN1_S2 CIN0_S2 ) $buffering 1
    fpunit_exec_exec__adder_64_with_carry_assign_stmt_2927_c_macro_;
    // $volatile carry_2 := ( $mux carry_1 CIN1_C2 CIN0_C2 ) $buffering 1
    fpunit_exec_exec__adder_64_with_carry_assign_stmt_2933_c_macro_;
    // $volatile sum_3 := ( $mux carry_2 CIN1_S3 CIN0_S3 ) $buffering 1
    fpunit_exec_exec__adder_64_with_carry_assign_stmt_2939_c_macro_;
    // $volatile carry_3 := ( $mux carry_2 CIN1_C3 CIN0_C3 ) $buffering 1
    fpunit_exec_exec__adder_64_with_carry_assign_stmt_2945_c_macro_;
    // SUM := ((sum_3 && sum_2) && (sum_1 && sum_0)) $buffering 1
    fpunit_exec_exec__adder_64_with_carry_assign_stmt_2954_c_macro_;
    // COUT := carry_3 $buffering 1
    fpunit_exec_exec__adder_64_with_carry_assign_stmt_2957_c_macro_;
    fpunit_exec_exec__adder_64_with_carry_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__adder_64_with_carry_series_block_stmt_2824_c_mutex_);
}
void
_fpunit_exec_exec_adder_65_(bit_vector * __pA, bit_vector * __pB,
			    bit_vector * __pSUM)
{
    MUTEX_DECL(fpunit_exec_exec__adder_65_series_block_stmt_2959_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__adder_65_series_block_stmt_2959_c_mutex_);
    fpunit_exec_exec__adder_65_inner_inarg_prep_macro__;
    // $volatile A0 := ( $slice A 15 0 ) $buffering 1
    fpunit_exec_exec__adder_65_assign_stmt_2966_c_macro_;
    // $volatile A1 := ( $slice A 31 16 ) $buffering 1
    fpunit_exec_exec__adder_65_assign_stmt_2970_c_macro_;
    // $volatile A2 := ( $slice A 47 32 ) $buffering 1
    fpunit_exec_exec__adder_65_assign_stmt_2974_c_macro_;
    // $volatile A3 := ( $slice A 64 48 ) $buffering 1
    fpunit_exec_exec__adder_65_assign_stmt_2978_c_macro_;
    // $volatile B0 := ( $slice B 15 0 ) $buffering 1
    fpunit_exec_exec__adder_65_assign_stmt_2982_c_macro_;
    // $volatile B1 := ( $slice B 31 16 ) $buffering 1
    fpunit_exec_exec__adder_65_assign_stmt_2986_c_macro_;
    // $volatile B2 := ( $slice B 47 32 ) $buffering 1
    fpunit_exec_exec__adder_65_assign_stmt_2990_c_macro_;
    // $volatile B3 := ( $slice B 64 48 ) $buffering 1
    fpunit_exec_exec__adder_65_assign_stmt_2994_c_macro_;
    // $volatile $call adder_18 (A0 B0 ZERO_1 ) (CIN0_S0 CIN0_C0 ) 
    fpunit_exec_exec__adder_65_call_stmt_3000_c_macro_;
    // $volatile $call adder_18 (A1 B1 ZERO_1 ) (CIN0_S1 CIN0_C1 ) 
    fpunit_exec_exec__adder_65_call_stmt_3006_c_macro_;
    // $volatile $call adder_18 (A1 B1 ONE_1 ) (CIN1_S1 CIN1_C1 ) 
    fpunit_exec_exec__adder_65_call_stmt_3012_c_macro_;
    // $volatile $call adder_18 (A2 B2 ZERO_1 ) (CIN0_S2 CIN0_C2 ) 
    fpunit_exec_exec__adder_65_call_stmt_3018_c_macro_;
    // $volatile $call adder_18 (A2 B2 ONE_1 ) (CIN1_S2 CIN1_C2 ) 
    fpunit_exec_exec__adder_65_call_stmt_3024_c_macro_;
    // $volatile $call adder_19 (A3 B3 ZERO_1 ) (CIN0_S3 CIN0_C3 ) 
    fpunit_exec_exec__adder_65_call_stmt_3030_c_macro_;
    // $volatile $call adder_19 (A3 B3 ONE_1 ) (CIN1_S3 CIN1_C3 ) 
    fpunit_exec_exec__adder_65_call_stmt_3036_c_macro_;
    // $volatile sum_0 := CIN0_S0 $buffering 1
    fpunit_exec_exec__adder_65_assign_stmt_3039_c_macro_;
    // $volatile carry_0 := CIN0_C0 $buffering 1
    fpunit_exec_exec__adder_65_assign_stmt_3042_c_macro_;
    // $volatile sum_1 := ( $mux carry_0 CIN1_S1 CIN0_S1 ) $buffering 1
    fpunit_exec_exec__adder_65_assign_stmt_3048_c_macro_;
    // $volatile carry_1 := ( $mux carry_0 CIN1_C1 CIN0_C1 ) $buffering 1
    fpunit_exec_exec__adder_65_assign_stmt_3054_c_macro_;
    // $volatile sum_2 := ( $mux carry_1 CIN1_S2 CIN0_S2 ) $buffering 1
    fpunit_exec_exec__adder_65_assign_stmt_3060_c_macro_;
    // $volatile carry_2 := ( $mux carry_1 CIN1_C2 CIN0_C2 ) $buffering 1
    fpunit_exec_exec__adder_65_assign_stmt_3066_c_macro_;
    // $volatile sum_3 := ( $mux carry_2 CIN1_S3 CIN0_S3 ) $buffering 1
    fpunit_exec_exec__adder_65_assign_stmt_3072_c_macro_;
    // SUM := ((sum_3 && sum_2) && (sum_1 && sum_0)) $buffering 1
    fpunit_exec_exec__adder_65_assign_stmt_3081_c_macro_;
    fpunit_exec_exec__adder_65_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__adder_65_series_block_stmt_2959_c_mutex_);
}
void
_fpunit_exec_exec_alignDivisorToDividend_(bit_vector * __pDIVIDEND,
					  bit_vector * __pudivisor,
					  bit_vector * __pSSD,
					  bit_vector * __pCCQ)
{
    MUTEX_DECL
	(fpunit_exec_exec__alignDivisorToDividend_series_block_stmt_3388_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__alignDivisorToDividend_series_block_stmt_3388_c_mutex_);
    fpunit_exec_exec__alignDivisorToDividend_inner_inarg_prep_macro__;
    // $volatile $call find_leftmost_64 (DIVIDEND ) (l_DIVIDEND z_DIVIDEND 
    // ) 
    fpunit_exec_exec__alignDivisorToDividend_call_stmt_3396_c_macro_;
    // $volatile $call find_leftmost_64 (udivisor ) (l_udivisor z_udivisor 
    // ) 
    fpunit_exec_exec__alignDivisorToDividend_call_stmt_3400_c_macro_;
    // $assert (udivisor > 0 ) $report (iu_exec
    // alignDivisorToDividend__udivisor_Is_Zero )
    fpunit_exec_exec__alignDivisorToDividend_stmt_3404_c_macro_;
    // $volatile shift_amount := (l_DIVIDEND - l_udivisor) $buffering 1
    fpunit_exec_exec__alignDivisorToDividend_assign_stmt_3409_c_macro_;
    // shifted_udivisor := (udivisor << ($bitcast ($uint<64>) shift_amount 
    // )) $buffering 1// bits of buffering = 64. 
    fpunit_exec_exec__alignDivisorToDividend_assign_stmt_3415_c_macro_;
    // DIVIDEND_3479_delayed_1_0 := DIVIDEND $buffering 1 $cut_through //
    // bits of buffering = 64. 
    fpunit_exec_exec__alignDivisorToDividend_assign_stmt_3418_c_macro_;
    // $volatile $call u_cmp_64 (shifted_udivisor
    // DIVIDEND_3479_delayed_1_0 ) (l g e ) 
    fpunit_exec_exec__alignDivisorToDividend_call_stmt_3424_c_macro_;
    // $volatile shift_ok := (l | e) $buffering 1
    fpunit_exec_exec__alignDivisorToDividend_assign_stmt_3429_c_macro_;
    // type_cast_3492_3492_delayed_1_0 := ($bitcast ($uint<6>)
    // shift_amount ) $buffering 1 $cut_through // bits of buffering = 6. 
    fpunit_exec_exec__alignDivisorToDividend_assign_stmt_3433_c_macro_;
    // type_cast_3496_3496_delayed_1_0 := ($bitcast ($uint<6>)
    // (shift_amount - 1 ) ) $buffering 1 $cut_through // bits of
    // buffering = 6. 
    fpunit_exec_exec__alignDivisorToDividend_assign_stmt_3439_c_macro_;
    // $volatile ccq_shift_amount := ( $mux shift_ok
    // type_cast_3492_3492_delayed_1_0 type_cast_3496_3496_delayed_1_0 )
    // $buffering 1
    fpunit_exec_exec__alignDivisorToDividend_assign_stmt_3445_c_macro_;
    // $volatile $call u_set_index_64 (ccq_shift_amount ) (ccq_v ) 
    fpunit_exec_exec__alignDivisorToDividend_call_stmt_3448_c_macro_;
    // CCQ := ccq_v $buffering 1// bits of buffering = 64. 
    fpunit_exec_exec__alignDivisorToDividend_assign_stmt_3451_c_macro_;
    // SSD := ( $mux shift_ok shifted_udivisor (ZERO_1 && ( $slice
    // shifted_udivisor 63 1 ) ) ) $buffering 1// bits of buffering = 64. 
    fpunit_exec_exec__alignDivisorToDividend_assign_stmt_3460_c_macro_;
    fpunit_exec_exec__alignDivisorToDividend_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__alignDivisorToDividend_series_block_stmt_3388_c_mutex_);
}
void
fpunit_exec_exec_alignDivisorToDividend(uint64_t DIVIDEND,
					uint64_t udivisor, uint64_t * SSD,
					uint64_t * CCQ)
{
    fpunit_exec_exec__alignDivisorToDividend_outer_arg_decl_macro__;
    _fpunit_exec_exec_alignDivisorToDividend_(&__DIVIDEND, &__udivisor,
					      &__SSD, &__CCQ);
    fpunit_exec_exec__alignDivisorToDividend_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_break_number_32_(bit_vector * __pfp,
				   bit_vector * __pnormal,
				   bit_vector * __pdenormal,
				   bit_vector * __pqnan,
				   bit_vector * __psnan,
				   bit_vector * __pinf,
				   bit_vector * __pzero,
				   bit_vector * __pdenormalize,
				   bit_vector * __pfract,
				   bit_vector * __pexpon)
{
    MUTEX_DECL
	(fpunit_exec_exec__break_number_32_series_block_stmt_3462_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__break_number_32_series_block_stmt_3462_c_mutex_);
    fpunit_exec_exec__break_number_32_inner_inarg_prep_macro__;
    // $volatile fraction := ( $slice fp 22 0 ) $buffering 1
    fpunit_exec_exec__break_number_32_assign_stmt_3476_c_macro_;
    // $volatile exponent := ( $slice fp 30 23 ) $buffering 1
    fpunit_exec_exec__break_number_32_assign_stmt_3480_c_macro_;
    // $volatile exponent_signed := ($bitcast ($int<10>) exponent )
    // $buffering 1
    fpunit_exec_exec__break_number_32_assign_stmt_3484_c_macro_;
    // $volatile fract_temp := (( $mux (zero | (denormal & denormalize))
    // (ZERO_1 && fraction) _b0 ) | ( $mux ((((denormal & ( ~ denormalize
    // )) | normal) | inf) | (qnan | snan)) (ONE_1 && fraction) _b0 ) )
    // $buffering 1
    fpunit_exec_exec__break_number_32_assign_stmt_3514_c_macro_;
    // $volatile expo_base := ((( $mux (denormal & denormalize)
    // expbase_126 _b0 ) | ( $mux ((((denormal & ( ~ denormalize )) |
    // normal) | inf) | (qnan | snan)) expbase_127 _b0 ) ) | ( $mux zero
    // exponent_signed _b0 ) ) $buffering 1
    fpunit_exec_exec__break_number_32_assign_stmt_3543_c_macro_;
    // expon := (exponent_signed - expo_base) $buffering 1
    fpunit_exec_exec__break_number_32_assign_stmt_3548_c_macro_;
    // fract := fract_temp $buffering 1
    fpunit_exec_exec__break_number_32_assign_stmt_3551_c_macro_;
    fpunit_exec_exec__break_number_32_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__break_number_32_series_block_stmt_3462_c_mutex_);
}
void
_fpunit_exec_exec_break_number_64_(bit_vector * __pfp,
				   bit_vector * __pnormal,
				   bit_vector * __pdenormal,
				   bit_vector * __pqnan,
				   bit_vector * __psnan,
				   bit_vector * __pinf,
				   bit_vector * __pzero,
				   bit_vector * __pdenormalize,
				   bit_vector * __pfract,
				   bit_vector * __pexpon)
{
    MUTEX_DECL
	(fpunit_exec_exec__break_number_64_series_block_stmt_3553_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__break_number_64_series_block_stmt_3553_c_mutex_);
    fpunit_exec_exec__break_number_64_inner_inarg_prep_macro__;
    // $volatile fraction := ( $slice fp 51 0 ) $buffering 1
    fpunit_exec_exec__break_number_64_assign_stmt_3567_c_macro_;
    // $volatile exponent := ( $slice fp 62 52 ) $buffering 1
    fpunit_exec_exec__break_number_64_assign_stmt_3571_c_macro_;
    // $volatile exponent_signed := ($bitcast ($int<13>) exponent )
    // $buffering 1
    fpunit_exec_exec__break_number_64_assign_stmt_3575_c_macro_;
    // $volatile fract_temp := (( $mux (zero | (denormal & denormalize))
    // (ZERO_1 && fraction) _b0 ) | ( $mux ((((denormal & ( ~ denormalize
    // )) | normal) | inf) | (qnan | snan)) (ONE_1 && fraction) _b0 ) )
    // $buffering 1
    fpunit_exec_exec__break_number_64_assign_stmt_3605_c_macro_;
    // $volatile expo_base := ((( $mux (denormal & denormalize)
    // expbase_1022 _b0 ) | ( $mux ((((denormal & ( ~ denormalize )) |
    // normal) | inf) | (qnan | snan)) expbase_1023 _b0 ) ) | ( $mux zero
    // exponent_signed _b0 ) ) $buffering 1
    fpunit_exec_exec__break_number_64_assign_stmt_3634_c_macro_;
    // expon := (exponent_signed - expo_base) $buffering 1
    fpunit_exec_exec__break_number_64_assign_stmt_3639_c_macro_;
    // fract := fract_temp $buffering 1
    fpunit_exec_exec__break_number_64_assign_stmt_3642_c_macro_;
    fpunit_exec_exec__break_number_64_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__break_number_64_series_block_stmt_3553_c_mutex_);
}
void
_fpunit_exec_exec_calculate_imm_offset_for_dti_(bit_vector * __pinstr,
						bit_vector * __pimm_offset)
{
    MUTEX_DECL
	(fpunit_exec_exec__calculate_imm_offset_for_dti_series_block_stmt_3644_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__calculate_imm_offset_for_dti_series_block_stmt_3644_c_mutex_);
    fpunit_exec_exec__calculate_imm_offset_for_dti_inner_inarg_prep_macro__;
    // imm_offset := ($bitcast ($uint<32>) ($cast ($int<32>) ($bitcast
    // ($int<13>) ( $slice instr 12 0 ) ) ) ) $buffering 1
    fpunit_exec_exec__calculate_imm_offset_for_dti_assign_stmt_3654_c_macro_;
    fpunit_exec_exec__calculate_imm_offset_for_dti_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__calculate_imm_offset_for_dti_series_block_stmt_3644_c_mutex_);
}
void
fpunit_exec_exec_calculate_imm_offset_for_dti(uint32_t instr,
					      uint32_t * imm_offset)
{
    fpunit_exec_exec__calculate_imm_offset_for_dti_outer_arg_decl_macro__;
    _fpunit_exec_exec_calculate_imm_offset_for_dti_(&__instr,
						    &__imm_offset);
    fpunit_exec_exec__calculate_imm_offset_for_dti_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_check_fh_exponent_overflow_(bit_vector * __pexp_ab,
					      bit_vector * __poverflow,
					      bit_vector * __punderflow)
{
    MUTEX_DECL
	(fpunit_exec_exec__check_fh_exponent_overflow_series_block_stmt_3656_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__check_fh_exponent_overflow_series_block_stmt_3656_c_mutex_);
    fpunit_exec_exec__check_fh_exponent_overflow_inner_inarg_prep_macro__;
    // overflow := (exp_ab > 16 ) $buffering 1
    fpunit_exec_exec__check_fh_exponent_overflow_assign_stmt_3665_c_macro_;
    // underflow := (exp_ab < -15 ) $buffering 1
    fpunit_exec_exec__check_fh_exponent_overflow_assign_stmt_3670_c_macro_;
    fpunit_exec_exec__check_fh_exponent_overflow_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__check_fh_exponent_overflow_series_block_stmt_3656_c_mutex_);
}
void
_fpunit_exec_exec_classFp32_(float *__pa, bit_vector * __ppos_normal,
			     bit_vector * __pneg_normal,
			     bit_vector * __ppos_denormal,
			     bit_vector * __pneg_denormal,
			     bit_vector * __pqnan, bit_vector * __psnan,
			     bit_vector * __ppos_inf,
			     bit_vector * __pneg_inf,
			     bit_vector * __ppos_zero,
			     bit_vector * __pneg_zero)
{
    MUTEX_DECL
	(fpunit_exec_exec__classFp32_series_block_stmt_2108_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__classFp32_series_block_stmt_2108_c_mutex_);
    fpunit_exec_exec__classFp32_inner_inarg_prep_macro__;
    // ua := ($bitcast ($uint<32>) a ) $buffering 1
    fpunit_exec_exec__classFp32_assign_stmt_2124_c_macro_;
    // sign := (ua [] 31 ) $buffering 1
    fpunit_exec_exec__classFp32_assign_stmt_2129_c_macro_;
    // exp_a := ( $slice ua 30 23 ) $buffering 1
    fpunit_exec_exec__classFp32_assign_stmt_2133_c_macro_;
    // mant_a := ( $slice ua 22 0 ) $buffering 1
    fpunit_exec_exec__classFp32_assign_stmt_2137_c_macro_;
    // exp_all_ones := (exp_a == ( ~ 0 )) $buffering 1
    fpunit_exec_exec__classFp32_assign_stmt_2143_c_macro_;
    // exp_all_zeros := (exp_a == 0 ) $buffering 1
    fpunit_exec_exec__classFp32_assign_stmt_2148_c_macro_;
    // mant_a_zero := (mant_a == 0 ) $buffering 1
    fpunit_exec_exec__classFp32_assign_stmt_2153_c_macro_;
    // mant_top_bit := (mant_a [] 22 ) $buffering 1
    fpunit_exec_exec__classFp32_assign_stmt_2158_c_macro_;
    // $volatile $call classFpBase (sign exp_all_ones exp_all_zeros
    // mant_a_zero mant_top_bit ) (pos_normal neg_normal pos_denormal
    // neg_denormal qnan snan pos_inf neg_inf pos_zero neg_zero ) 
    fpunit_exec_exec__classFp32_call_stmt_2174_c_macro_;
    // $report (fpunit_exec classFp32_trace__ ua ua sign sign exp_a exp_a
    // mant_a mant_a exp_all_ones exp_all_ones exp_all_zeros exp_all_zeros 
    // mant_a_zero mant_a_zero mant_top_bit mant_top_bit qnan qnan snan
    // snan )
    fpunit_exec_exec__classFp32_stmt_2185_c_macro_;
    fpunit_exec_exec__classFp32_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__classFp32_series_block_stmt_2108_c_mutex_);
}
void
_fpunit_exec_exec_classFp32IntoClassWord_(float *__pf1_s,
					  bit_vector *
					  __pf1_s_classification)
{
    MUTEX_DECL
	(fpunit_exec_exec__classFp32IntoClassWord_series_block_stmt_3672_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__classFp32IntoClassWord_series_block_stmt_3672_c_mutex_);
    fpunit_exec_exec__classFp32IntoClassWord_inner_inarg_prep_macro__;
    // $volatile $call classFp32 (f1_s ) (f1_s_pos_normal f1_s_neg_normal
    // f1_s_pos_denormal f1_s_neg_denormal f1_s_qnan f1_s_snan
    // f1_s_pos_inf f1_s_neg_inf f1_s_pos_zero f1_s_neg_zero ) 
    fpunit_exec_exec__classFp32IntoClassWord_call_stmt_3686_c_macro_;
    // f1_s_classification := ((((f1_s_pos_normal && f1_s_neg_normal) &&
    // f1_s_pos_denormal) && (f1_s_neg_denormal && f1_s_qnan)) &&
    // (((f1_s_snan && f1_s_pos_inf) && f1_s_neg_inf) && (f1_s_pos_zero && 
    // f1_s_neg_zero))) $buffering 1
    fpunit_exec_exec__classFp32IntoClassWord_assign_stmt_3707_c_macro_;
    fpunit_exec_exec__classFp32IntoClassWord_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__classFp32IntoClassWord_series_block_stmt_3672_c_mutex_);
}
void
_fpunit_exec_exec_classFp64_(double *__pa, bit_vector * __ppos_normal,
			     bit_vector * __pneg_normal,
			     bit_vector * __ppos_denormal,
			     bit_vector * __pneg_denormal,
			     bit_vector * __pqnan, bit_vector * __psnan,
			     bit_vector * __ppos_inf,
			     bit_vector * __pneg_inf,
			     bit_vector * __ppos_zero,
			     bit_vector * __pneg_zero)
{
    MUTEX_DECL
	(fpunit_exec_exec__classFp64_series_block_stmt_1510_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__classFp64_series_block_stmt_1510_c_mutex_);
    fpunit_exec_exec__classFp64_inner_inarg_prep_macro__;
    // $report (fpunit_exec classFp64_input__ a a )
    fpunit_exec_exec__classFp64_stmt_1524_c_macro_;
    // ua := ($bitcast ($uint<64>) a ) $buffering 1
    fpunit_exec_exec__classFp64_assign_stmt_1528_c_macro_;
    // $report (fpunit_exec classFp64_trace__ ua ua )
    fpunit_exec_exec__classFp64_stmt_1530_c_macro_;
    // sign := (ua [] 63 ) $buffering 1
    fpunit_exec_exec__classFp64_assign_stmt_1535_c_macro_;
    // $report (fpunit_exec classFp64_trace__ sign sign )
    fpunit_exec_exec__classFp64_stmt_1537_c_macro_;
    // exp_a := ( $slice ua 62 52 ) $buffering 1
    fpunit_exec_exec__classFp64_assign_stmt_1541_c_macro_;
    // mant_a := ( $slice ua 51 0 ) $buffering 1
    fpunit_exec_exec__classFp64_assign_stmt_1545_c_macro_;
    // $report (fpunit_exec classFp64_trace__ exp_a exp_a mant_a mant_a )
    fpunit_exec_exec__classFp64_stmt_1548_c_macro_;
    // exp_all_ones := (exp_a == ( ~ 0 )) $buffering 1
    fpunit_exec_exec__classFp64_assign_stmt_1554_c_macro_;
    // exp_all_zeros := (exp_a == 0 ) $buffering 1
    fpunit_exec_exec__classFp64_assign_stmt_1559_c_macro_;
    // $report (fpunit_exec classFp64_trace__ exp_all_ones exp_all_ones
    // exp_all_zeros exp_all_zeros )
    fpunit_exec_exec__classFp64_stmt_1562_c_macro_;
    // mant_a_zero := (mant_a == 0 ) $buffering 1
    fpunit_exec_exec__classFp64_assign_stmt_1567_c_macro_;
    // mant_top_bit := (mant_a [] 51 ) $buffering 1
    fpunit_exec_exec__classFp64_assign_stmt_1572_c_macro_;
    // $report (fpunit_exec classFp64_trace__ mant_a_zero mant_a_zero
    // mant_top_bit mant_top_bit )
    fpunit_exec_exec__classFp64_stmt_1575_c_macro_;
    // $volatile $call classFpBase (sign exp_all_ones exp_all_zeros
    // mant_a_zero mant_top_bit ) (pos_normal neg_normal pos_denormal
    // neg_denormal qnan snan pos_inf neg_inf pos_zero neg_zero ) 
    fpunit_exec_exec__classFp64_call_stmt_1591_c_macro_;
    fpunit_exec_exec__classFp64_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__classFp64_series_block_stmt_1510_c_mutex_);
}
void
_fpunit_exec_exec_classFpBase_(bit_vector * __psign,
			       bit_vector * __pexp_all_ones,
			       bit_vector * __pexp_all_zeros,
			       bit_vector * __pmant_a_zero,
			       bit_vector * __pmant_top_bit,
			       bit_vector * __ppos_normal,
			       bit_vector * __pneg_normal,
			       bit_vector * __ppos_denormal,
			       bit_vector * __pneg_denormal,
			       bit_vector * __pqnan, bit_vector * __psnan,
			       bit_vector * __ppos_inf,
			       bit_vector * __pneg_inf,
			       bit_vector * __ppos_zero,
			       bit_vector * __pneg_zero)
{
    MUTEX_DECL
	(fpunit_exec_exec__classFpBase_series_block_stmt_1410_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__classFpBase_series_block_stmt_1410_c_mutex_);
    fpunit_exec_exec__classFpBase_inner_inarg_prep_macro__;
    // snan := ((exp_all_ones & ( ~ mant_a_zero )) & ( ~ mant_top_bit ))
    // $buffering 1
    fpunit_exec_exec__classFpBase_assign_stmt_1434_c_macro_;
    // qnan := ((exp_all_ones & ( ~ mant_a_zero )) & mant_top_bit)
    // $buffering 1
    fpunit_exec_exec__classFpBase_assign_stmt_1442_c_macro_;
    // pos_inf := ((exp_all_ones & mant_a_zero) & ( ~ sign )) $buffering 1
    fpunit_exec_exec__classFpBase_assign_stmt_1450_c_macro_;
    // neg_inf := ((exp_all_ones & mant_a_zero) & sign) $buffering 1
    fpunit_exec_exec__classFpBase_assign_stmt_1457_c_macro_;
    // pos_zero := ((exp_all_zeros & mant_a_zero) & ( ~ sign )) $buffering 
    // 1
    fpunit_exec_exec__classFpBase_assign_stmt_1465_c_macro_;
    // neg_zero := ((exp_all_zeros & mant_a_zero) & sign) $buffering 1
    fpunit_exec_exec__classFpBase_assign_stmt_1472_c_macro_;
    // pos_denormal := ((exp_all_zeros & ( ~ mant_a_zero )) & ( ~ sign ))
    // $buffering 1
    fpunit_exec_exec__classFpBase_assign_stmt_1481_c_macro_;
    // neg_denormal := ((exp_all_zeros & ( ~ mant_a_zero )) & sign)
    // $buffering 1
    fpunit_exec_exec__classFpBase_assign_stmt_1489_c_macro_;
    // pos_normal := ((( ~ exp_all_zeros ) & ( ~ exp_all_ones )) & ( ~
    // sign )) $buffering 1
    fpunit_exec_exec__classFpBase_assign_stmt_1499_c_macro_;
    // neg_normal := ((( ~ exp_all_zeros ) & ( ~ exp_all_ones )) & sign)
    // $buffering 1
    fpunit_exec_exec__classFpBase_assign_stmt_1508_c_macro_;
    fpunit_exec_exec__classFpBase_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__classFpBase_series_block_stmt_1410_c_mutex_);
}
void
_fpunit_exec_exec_classifyFp16_(bit_vector * __pua, bit_vector * __pzero,
				bit_vector * __pnormal,
				bit_vector * __pnan, bit_vector * __pinf)
{
    MUTEX_DECL
	(fpunit_exec_exec__classifyFp16_series_block_stmt_3728_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__classifyFp16_series_block_stmt_3728_c_mutex_);
    fpunit_exec_exec__classifyFp16_inner_inarg_prep_macro__;
    // $volatile $call splitFp16 (ua ) (sign exponent mantissa ) 
    fpunit_exec_exec__classifyFp16_call_stmt_3738_c_macro_;
    // exp_all_ones := (exponent == ( ~ ($bitcast ($uint<5>) 0 ) ))
    // $buffering 1
    fpunit_exec_exec__classifyFp16_assign_stmt_3745_c_macro_;
    // exp_all_zeros := (exponent == 0 ) $buffering 1
    fpunit_exec_exec__classifyFp16_assign_stmt_3750_c_macro_;
    // mant_a_zero := (mantissa == 0 ) $buffering 1
    fpunit_exec_exec__classifyFp16_assign_stmt_3755_c_macro_;
    // mant_top_bit := (mantissa [] 9 ) $buffering 1
    fpunit_exec_exec__classifyFp16_assign_stmt_3760_c_macro_;
    // $volatile $call classFpBase (sign exp_all_ones exp_all_zeros
    // mant_a_zero mant_top_bit ) (pos_normal neg_normal pos_denormal
    // neg_denormal qnan snan pos_inf neg_inf pos_zero neg_zero ) 
    fpunit_exec_exec__classifyFp16_call_stmt_3776_c_macro_;
    // $report (fpunit_exec classifyFp16 ua ua sign sign mantissa mantissa 
    // exponent exponent exp_all_ones exp_all_ones exp_all_ones
    // exp_all_ones exp_all_zeros exp_all_zeros exp_all_zeros
    // exp_all_zeros mant_a_zero mant_a_zero mant_a_zero mant_a_zero
    // mant_top_bit mant_top_bit mant_top_bit mant_top_bit qnan qnan qnan
    // qnan snan snan snan snan )
    fpunit_exec_exec__classifyFp16_stmt_3793_c_macro_;
    // zero := ((pos_zero | neg_zero) | (pos_denormal | neg_denormal))
    // $buffering 1
    fpunit_exec_exec__classifyFp16_assign_stmt_3802_c_macro_;
    // normal := (pos_normal | neg_normal) $buffering 1
    fpunit_exec_exec__classifyFp16_assign_stmt_3807_c_macro_;
    // nan := (qnan | snan) $buffering 1
    fpunit_exec_exec__classifyFp16_assign_stmt_3812_c_macro_;
    // inf := (pos_inf | neg_inf) $buffering 1
    fpunit_exec_exec__classifyFp16_assign_stmt_3817_c_macro_;
    fpunit_exec_exec__classifyFp16_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__classifyFp16_series_block_stmt_3728_c_mutex_);
}
void
_fpunit_exec_exec_classify_32_(float *__pf1_s, bit_vector * __pf1_zero,
			       bit_vector * __pf1_normal,
			       bit_vector * __pf1_denormal,
			       bit_vector * __pf1_inf,
			       bit_vector * __pf1_nan)
{
    MUTEX_DECL
	(fpunit_exec_exec__classify_32_series_block_stmt_2187_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__classify_32_series_block_stmt_2187_c_mutex_);
    fpunit_exec_exec__classify_32_inner_inarg_prep_macro__;
    // $volatile $call classFp32 (f1_s ) (f1_s_pos_normal f1_s_neg_normal
    // f1_s_pos_denormal f1_s_neg_denormal f1_s_qnan f1_s_snan
    // f1_s_pos_inf f1_s_neg_inf f1_s_pos_zero f1_s_neg_zero ) 
    fpunit_exec_exec__classify_32_call_stmt_2205_c_macro_;
    // $volatile f1_zero := (f1_s_pos_zero | f1_s_neg_zero) $buffering 1
    fpunit_exec_exec__classify_32_assign_stmt_2210_c_macro_;
    // $volatile f1_normal := (f1_s_pos_normal | f1_s_neg_normal)
    // $buffering 1
    fpunit_exec_exec__classify_32_assign_stmt_2215_c_macro_;
    // $volatile f1_denormal := (f1_s_pos_denormal | f1_s_neg_denormal)
    // $buffering 1
    fpunit_exec_exec__classify_32_assign_stmt_2220_c_macro_;
    // $volatile f1_inf := (f1_s_pos_inf | f1_s_neg_inf) $buffering 1
    fpunit_exec_exec__classify_32_assign_stmt_2225_c_macro_;
    // $volatile f1_nan := (f1_s_snan | f1_s_qnan) $buffering 1
    fpunit_exec_exec__classify_32_assign_stmt_2230_c_macro_;
    fpunit_exec_exec__classify_32_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__classify_32_series_block_stmt_2187_c_mutex_);
}
void
_fpunit_exec_exec_classify_64_(double *__pf1_d, bit_vector * __pf1_zero,
			       bit_vector * __pf1_normal,
			       bit_vector * __pf1_denormal,
			       bit_vector * __pf1_inf,
			       bit_vector * __pf1_nan)
{
    MUTEX_DECL
	(fpunit_exec_exec__classify_64_series_block_stmt_1593_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__classify_64_series_block_stmt_1593_c_mutex_);
    fpunit_exec_exec__classify_64_inner_inarg_prep_macro__;
    // $volatile $call classFp64 (f1_d ) (f1_d_pos_normal f1_d_neg_normal
    // f1_d_pos_denormal f1_d_neg_denormal f1_d_qnan f1_d_snan
    // f1_d_pos_inf f1_d_neg_inf f1_d_pos_zero f1_d_neg_zero ) 
    fpunit_exec_exec__classify_64_call_stmt_1611_c_macro_;
    // $volatile f1_zero := (f1_d_pos_zero | f1_d_neg_zero) $buffering 1
    fpunit_exec_exec__classify_64_assign_stmt_1616_c_macro_;
    // $volatile f1_normal := (f1_d_pos_normal | f1_d_neg_normal)
    // $buffering 1
    fpunit_exec_exec__classify_64_assign_stmt_1621_c_macro_;
    // $volatile f1_denormal := (f1_d_pos_denormal | f1_d_neg_denormal)
    // $buffering 1
    fpunit_exec_exec__classify_64_assign_stmt_1626_c_macro_;
    // $volatile f1_inf := (f1_d_pos_inf | f1_d_neg_inf) $buffering 1
    fpunit_exec_exec__classify_64_assign_stmt_1631_c_macro_;
    // $volatile f1_nan := (f1_d_snan | f1_d_qnan) $buffering 1
    fpunit_exec_exec__classify_64_assign_stmt_1636_c_macro_;
    fpunit_exec_exec__classify_64_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__classify_64_series_block_stmt_1593_c_mutex_);
}
void
_fpunit_exec_exec_classify_and_prepare_32_(float *__pa,
					   bit_vector *
					   __pextended_exponent,
					   bit_vector *
					   __pextended_mantissa,
					   bit_vector * __pspecial_case,
					   float *__pspecial_case_result)
{
    MUTEX_DECL
	(fpunit_exec_exec__classify_and_prepare_32_series_block_stmt_3819_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__classify_and_prepare_32_series_block_stmt_3819_c_mutex_);
    fpunit_exec_exec__classify_and_prepare_32_inner_inarg_prep_macro__;
    // $volatile ua := ($bitcast ($uint<32>) a ) $buffering 1
    fpunit_exec_exec__classify_and_prepare_32_assign_stmt_3828_c_macro_;
    // $report (fpdiv32bitwise classify_and_prepare_32_in_args__ a a ua ua 
    // )
    fpunit_exec_exec__classify_and_prepare_32_stmt_3831_c_macro_;
    // $volatile $call classify_32 (a ) (z norm dnorm inf nan ) 
    fpunit_exec_exec__classify_and_prepare_32_call_stmt_3838_c_macro_;
    // $report (fpdiv32bitwise classify_and_prepare_32_class z z norm norm 
    // dnorm dnorm inf inf nan nan )
    fpunit_exec_exec__classify_and_prepare_32_stmt_3844_c_macro_;
    // $volatile sa := (ua [] 31 ) $buffering 1
    fpunit_exec_exec__classify_and_prepare_32_assign_stmt_3849_c_macro_;
    // special_case := ((z | inf) | nan) $buffering 1
    fpunit_exec_exec__classify_and_prepare_32_assign_stmt_3856_c_macro_;
    // uspecial_case_result := ((( $mux z ( $mux sa (1 << 31 ) ZERO_32 )
    // _b0 ) | ( $mux nan ((ZERO_1 && ( ~ ZERO_8 )) && (ONE_1 && ZERO_22)) 
    // _b0 ) ) | ( $mux inf ((ZERO_1 && ( ~ ZERO_8 )) && ZERO_23) _b0 ) )
    // $buffering 1
    fpunit_exec_exec__classify_and_prepare_32_assign_stmt_3889_c_macro_;
    // special_case_result := ($bitcast ($float<8,23>)
    // uspecial_case_result ) $buffering 1
    fpunit_exec_exec__classify_and_prepare_32_assign_stmt_3893_c_macro_;
    // m := ( $slice ua 22 0 ) $buffering 1
    fpunit_exec_exec__classify_and_prepare_32_assign_stmt_3897_c_macro_;
    // frac := (( $mux dnorm ZERO_1 ONE_1 ) && m) $buffering 1
    fpunit_exec_exec__classify_and_prepare_32_assign_stmt_3905_c_macro_;
    // $volatile $call find_left_24 (frac ) (left_1_index found_1 ) 
    fpunit_exec_exec__classify_and_prepare_32_call_stmt_3909_c_macro_;
    // left_shifts_required := (23 - left_1_index) $buffering 1
    fpunit_exec_exec__classify_and_prepare_32_assign_stmt_3914_c_macro_;
    // $volatile $call i24_sll (frac left_shifts_required ) (frac_shifted
    // ) 
    fpunit_exec_exec__classify_and_prepare_32_call_stmt_3918_c_macro_;
    // exp := ( $slice ua 30 23 ) $buffering 1
    fpunit_exec_exec__classify_and_prepare_32_assign_stmt_3922_c_macro_;
    // exp_bias := ( $mux dnorm exp_base_126 exp_base_127 ) $buffering 1
    fpunit_exec_exec__classify_and_prepare_32_assign_stmt_3928_c_macro_;
    // exp_base := (($bitcast ($int<13>) exp ) - exp_bias) $buffering 1
    fpunit_exec_exec__classify_and_prepare_32_assign_stmt_3934_c_macro_;
    // ie_13 := (exp_base - ($bitcast ($int<13>) left_shifts_required ))
    // $buffering 1
    fpunit_exec_exec__classify_and_prepare_32_assign_stmt_3940_c_macro_;
    // extended_exponent := ( $mux (ie_13 [] 0 ) (ie_13 - 1 ) ie_13 )
    // $buffering 1
    fpunit_exec_exec__classify_and_prepare_32_assign_stmt_3950_c_macro_;
    // m_base := ( $slice frac_shifted 22 0 ) $buffering 1
    fpunit_exec_exec__classify_and_prepare_32_assign_stmt_3954_c_macro_;
    // extended_mantissa := ( $mux (ie_13 [] 0 ) ((ONE_1 && m_base) &&
    // (ZERO_1 && ZERO_7)) ((ZERO_1 && ONE_1) && (m_base && ZERO_7)) )
    // $buffering 1
    fpunit_exec_exec__classify_and_prepare_32_assign_stmt_3974_c_macro_;
    // $report (fpdiv32bitwise classify_and_prepare_32_out_args
    // special_case special_case special_case_result special_case_result
    // extended_exponent extended_exponent extended_mantissa
    // extended_mantissa )
    fpunit_exec_exec__classify_and_prepare_32_stmt_3979_c_macro_;
    fpunit_exec_exec__classify_and_prepare_32_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__classify_and_prepare_32_series_block_stmt_3819_c_mutex_);
}
void
_fpunit_exec_exec_classify_and_prepare_64_(double *__pa,
					   bit_vector *
					   __pextended_exponent,
					   bit_vector *
					   __pextended_mantissa,
					   bit_vector * __pspecial_case,
					   double *__pspecial_case_result)
{
    MUTEX_DECL
	(fpunit_exec_exec__classify_and_prepare_64_series_block_stmt_3981_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__classify_and_prepare_64_series_block_stmt_3981_c_mutex_);
    fpunit_exec_exec__classify_and_prepare_64_inner_inarg_prep_macro__;
    // $volatile ua := ($bitcast ($uint<64>) a ) $buffering 1
    fpunit_exec_exec__classify_and_prepare_64_assign_stmt_3991_c_macro_;
    // $volatile sa := (ua [] 63 ) $buffering 1
    fpunit_exec_exec__classify_and_prepare_64_assign_stmt_3996_c_macro_;
    // $report (fpdiv64bitwise classify_and_prepare_64_in_args__ a a ua ua 
    // )
    fpunit_exec_exec__classify_and_prepare_64_stmt_3999_c_macro_;
    // $volatile $call classify_64 (a ) (z norm dnorm inf nan ) 
    fpunit_exec_exec__classify_and_prepare_64_call_stmt_4006_c_macro_;
    // $report (fpdiv364itwise classify_and_prepare_64_class z z norm norm 
    // dnorm dnorm inf inf nan nan )
    fpunit_exec_exec__classify_and_prepare_64_stmt_4012_c_macro_;
    // special_case := ((z | inf) | nan) $buffering 1
    fpunit_exec_exec__classify_and_prepare_64_assign_stmt_4019_c_macro_;
    // uspecial_case_result := ((( $mux z ( $mux sa (1 << 63 ) ZERO_64 )
    // _b0 ) | ( $mux nan ((ZERO_1 && ( ~ ZERO_11 )) && (ONE_1 &&
    // ZERO_51)) _b0 ) ) | ( $mux inf ((ZERO_1 && ( ~ ZERO_11 )) &&
    // ZERO_52) _b0 ) ) $buffering 1
    fpunit_exec_exec__classify_and_prepare_64_assign_stmt_4052_c_macro_;
    // special_case_result := ($bitcast ($float<11,52>)
    // uspecial_case_result ) $buffering 1
    fpunit_exec_exec__classify_and_prepare_64_assign_stmt_4056_c_macro_;
    // m := ( $slice ua 51 0 ) $buffering 1
    fpunit_exec_exec__classify_and_prepare_64_assign_stmt_4060_c_macro_;
    // frac := (( $mux dnorm ZERO_1 ONE_1 ) && m) $buffering 1
    fpunit_exec_exec__classify_and_prepare_64_assign_stmt_4068_c_macro_;
    // $volatile $call find_left_53 (frac ) (left_1_index found_1 ) 
    fpunit_exec_exec__classify_and_prepare_64_call_stmt_4072_c_macro_;
    // left_shifts_required := (52 - left_1_index) $buffering 1
    fpunit_exec_exec__classify_and_prepare_64_assign_stmt_4077_c_macro_;
    // $volatile $call i53_sll (frac left_shifts_required ) (frac_shifted
    // ) 
    fpunit_exec_exec__classify_and_prepare_64_call_stmt_4081_c_macro_;
    // exp := ( $slice ua 62 52 ) $buffering 1
    fpunit_exec_exec__classify_and_prepare_64_assign_stmt_4085_c_macro_;
    // exp_bias := ( $mux dnorm exp_base_1022 exp_base_1023 ) $buffering 1
    fpunit_exec_exec__classify_and_prepare_64_assign_stmt_4091_c_macro_;
    // exp_base := (($bitcast ($int<13>) exp ) - exp_bias) $buffering 1
    fpunit_exec_exec__classify_and_prepare_64_assign_stmt_4097_c_macro_;
    // ie_13 := (exp_base - ($bitcast ($int<13>) left_shifts_required ))
    // $buffering 1
    fpunit_exec_exec__classify_and_prepare_64_assign_stmt_4103_c_macro_;
    // extended_exponent := ( $mux (ie_13 [] 0 ) (ie_13 - 1 ) ie_13 )
    // $buffering 1
    fpunit_exec_exec__classify_and_prepare_64_assign_stmt_4113_c_macro_;
    // m_base := ( $slice frac_shifted 51 0 ) $buffering 1
    fpunit_exec_exec__classify_and_prepare_64_assign_stmt_4117_c_macro_;
    // extended_mantissa := ( $mux (ie_13 [] 0 ) ((ONE_1 && m_base) &&
    // ZERO_3) ((ZERO_1 && ONE_1) && (m_base && ZERO_2)) ) $buffering 1
    fpunit_exec_exec__classify_and_prepare_64_assign_stmt_4135_c_macro_;
    // $report (fpdiv64bitwise classify_and_prepare_64_out_args
    // special_case special_case special_case_result special_case_result
    // extended_exponent extended_exponent extended_mantissa
    // extended_mantissa )
    fpunit_exec_exec__classify_and_prepare_64_stmt_4140_c_macro_;
    fpunit_exec_exec__classify_and_prepare_64_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__classify_and_prepare_64_series_block_stmt_3981_c_mutex_);
}
void
_fpunit_exec_exec_classify_utility_(bit_vector *
				    __puse_single_precision_inputs,
				    bit_vector * __pf1_s_class,
				    bit_vector * __pf1_d_class,
				    bit_vector * __pf1_zero,
				    bit_vector * __pf1_normal,
				    bit_vector * __pf1_denormal,
				    bit_vector * __pf1_nan,
				    bit_vector * __pf1_inf,
				    bit_vector * __pf1_pos_inf,
				    bit_vector * __pf1_neg_inf)
{
    MUTEX_DECL
	(fpunit_exec_exec__classify_utility_series_block_stmt_4142_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__classify_utility_series_block_stmt_4142_c_mutex_);
    fpunit_exec_exec__classify_utility_inner_inarg_prep_macro__;
    // $volatile f1_s_pos_normal := ( $slice f1_s_class 9 9 ) $buffering 1
    fpunit_exec_exec__classify_utility_assign_stmt_4156_c_macro_;
    // $volatile f1_s_neg_normal := ( $slice f1_s_class 8 8 ) $buffering 1
    fpunit_exec_exec__classify_utility_assign_stmt_4160_c_macro_;
    // $volatile f1_s_pos_denormal := ( $slice f1_s_class 7 7 ) $buffering 
    // 1
    fpunit_exec_exec__classify_utility_assign_stmt_4164_c_macro_;
    // $volatile f1_s_neg_denormal := ( $slice f1_s_class 6 6 ) $buffering 
    // 1
    fpunit_exec_exec__classify_utility_assign_stmt_4168_c_macro_;
    // $volatile f1_s_qnan := ( $slice f1_s_class 5 5 ) $buffering 1
    fpunit_exec_exec__classify_utility_assign_stmt_4172_c_macro_;
    // $volatile f1_s_snan := ( $slice f1_s_class 4 4 ) $buffering 1
    fpunit_exec_exec__classify_utility_assign_stmt_4176_c_macro_;
    // $volatile f1_s_pos_inf := ( $slice f1_s_class 3 3 ) $buffering 1
    fpunit_exec_exec__classify_utility_assign_stmt_4180_c_macro_;
    // $volatile f1_s_neg_inf := ( $slice f1_s_class 2 2 ) $buffering 1
    fpunit_exec_exec__classify_utility_assign_stmt_4184_c_macro_;
    // $volatile f1_s_pos_zero := ( $slice f1_s_class 1 1 ) $buffering 1
    fpunit_exec_exec__classify_utility_assign_stmt_4188_c_macro_;
    // $volatile f1_s_neg_zero := ( $slice f1_s_class 0 0 ) $buffering 1
    fpunit_exec_exec__classify_utility_assign_stmt_4192_c_macro_;
    // $volatile f1_d_pos_normal := ( $slice f1_d_class 9 9 ) $buffering 1
    fpunit_exec_exec__classify_utility_assign_stmt_4196_c_macro_;
    // $volatile f1_d_neg_normal := ( $slice f1_d_class 8 8 ) $buffering 1
    fpunit_exec_exec__classify_utility_assign_stmt_4200_c_macro_;
    // $volatile f1_d_pos_denormal := ( $slice f1_d_class 7 7 ) $buffering 
    // 1
    fpunit_exec_exec__classify_utility_assign_stmt_4204_c_macro_;
    // $volatile f1_d_neg_denormal := ( $slice f1_d_class 6 6 ) $buffering 
    // 1
    fpunit_exec_exec__classify_utility_assign_stmt_4208_c_macro_;
    // $volatile f1_d_qnan := ( $slice f1_d_class 5 5 ) $buffering 1
    fpunit_exec_exec__classify_utility_assign_stmt_4212_c_macro_;
    // $volatile f1_d_snan := ( $slice f1_d_class 4 4 ) $buffering 1
    fpunit_exec_exec__classify_utility_assign_stmt_4216_c_macro_;
    // $volatile f1_d_pos_inf := ( $slice f1_d_class 3 3 ) $buffering 1
    fpunit_exec_exec__classify_utility_assign_stmt_4220_c_macro_;
    // $volatile f1_d_neg_inf := ( $slice f1_d_class 2 2 ) $buffering 1
    fpunit_exec_exec__classify_utility_assign_stmt_4224_c_macro_;
    // $volatile f1_d_pos_zero := ( $slice f1_d_class 1 1 ) $buffering 1
    fpunit_exec_exec__classify_utility_assign_stmt_4228_c_macro_;
    // $volatile f1_d_neg_zero := ( $slice f1_d_class 0 0 ) $buffering 1
    fpunit_exec_exec__classify_utility_assign_stmt_4232_c_macro_;
    // $volatile f1_zero := ( $mux use_single_precision_inputs
    // (f1_s_pos_zero | f1_s_neg_zero) (f1_d_pos_zero | f1_d_neg_zero) )
    // $buffering 1
    fpunit_exec_exec__classify_utility_assign_stmt_4242_c_macro_;
    // $volatile f1_normal := ( $mux use_single_precision_inputs
    // ((f1_s_pos_normal | f1_s_pos_denormal) | (f1_s_neg_normal |
    // f1_s_neg_denormal)) (f1_d_pos_normal | f1_d_neg_normal) )
    // $buffering 1
    fpunit_exec_exec__classify_utility_assign_stmt_4256_c_macro_;
    // $volatile f1_denormal := ( $mux use_single_precision_inputs ZERO_1
    // (f1_d_pos_denormal | f1_d_neg_denormal) ) $buffering 1
    fpunit_exec_exec__classify_utility_assign_stmt_4264_c_macro_;
    // $volatile f1_inf := ( $mux use_single_precision_inputs
    // (f1_s_pos_inf | f1_s_neg_inf) (f1_d_pos_inf | f1_d_neg_inf) )
    // $buffering 1
    fpunit_exec_exec__classify_utility_assign_stmt_4274_c_macro_;
    // $volatile f1_nan := ( $mux use_single_precision_inputs (f1_s_qnan | 
    // f1_s_snan) (f1_d_snan | f1_d_qnan) ) $buffering 1
    fpunit_exec_exec__classify_utility_assign_stmt_4284_c_macro_;
    // $volatile f1_pos_inf := ( $mux use_single_precision_inputs
    // f1_s_pos_inf f1_d_pos_inf ) $buffering 1
    fpunit_exec_exec__classify_utility_assign_stmt_4290_c_macro_;
    // $volatile f1_neg_inf := ( $mux use_single_precision_inputs
    // f1_s_neg_inf f1_d_neg_inf ) $buffering 1
    fpunit_exec_exec__classify_utility_assign_stmt_4296_c_macro_;
    fpunit_exec_exec__classify_utility_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__classify_utility_series_block_stmt_4142_c_mutex_);
}
void
_fpunit_exec_exec_compare11_(bit_vector * __pX, bit_vector * __pY,
			     bit_vector * __pG, bit_vector * __pE)
{
    MUTEX_DECL
	(fpunit_exec_exec__compare11_series_block_stmt_4454_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__compare11_series_block_stmt_4454_c_mutex_);
    fpunit_exec_exec__compare11_inner_inarg_prep_macro__;
    // XH := ( $slice X 10 8 ) $buffering 1
    fpunit_exec_exec__compare11_assign_stmt_4462_c_macro_;
    // XL := ( $slice X 7 0 ) $buffering 1
    fpunit_exec_exec__compare11_assign_stmt_4466_c_macro_;
    // YH := ( $slice Y 10 8 ) $buffering 1
    fpunit_exec_exec__compare11_assign_stmt_4470_c_macro_;
    // YL := ( $slice Y 7 0 ) $buffering 1
    fpunit_exec_exec__compare11_assign_stmt_4474_c_macro_;
    // GH := (XH > YH) $buffering 1
    fpunit_exec_exec__compare11_assign_stmt_4479_c_macro_;
    // EH := (XH == YH) $buffering 1
    fpunit_exec_exec__compare11_assign_stmt_4484_c_macro_;
    // $volatile $call compare8 (XL YL ) (GL EL ) 
    fpunit_exec_exec__compare11_call_stmt_4489_c_macro_;
    // G := (GH | (EH & GL)) $buffering 1
    fpunit_exec_exec__compare11_assign_stmt_4496_c_macro_;
    // E := (EH & EL) $buffering 1
    fpunit_exec_exec__compare11_assign_stmt_4501_c_macro_;
    fpunit_exec_exec__compare11_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__compare11_series_block_stmt_4454_c_mutex_);
}
void
_fpunit_exec_exec_compare16_(bit_vector * __pX, bit_vector * __pY,
			     bit_vector * __pG, bit_vector * __pE)
{
    MUTEX_DECL
	(fpunit_exec_exec__compare16_series_block_stmt_4503_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__compare16_series_block_stmt_4503_c_mutex_);
    fpunit_exec_exec__compare16_inner_inarg_prep_macro__;
    // XH := ( $slice X 15 8 ) $buffering 1
    fpunit_exec_exec__compare16_assign_stmt_4511_c_macro_;
    // XL := ( $slice X 7 0 ) $buffering 1
    fpunit_exec_exec__compare16_assign_stmt_4515_c_macro_;
    // YH := ( $slice Y 15 8 ) $buffering 1
    fpunit_exec_exec__compare16_assign_stmt_4519_c_macro_;
    // YL := ( $slice Y 7 0 ) $buffering 1
    fpunit_exec_exec__compare16_assign_stmt_4523_c_macro_;
    // $volatile $call compare8 (XH YH ) (GH EH ) 
    fpunit_exec_exec__compare16_call_stmt_4528_c_macro_;
    // $volatile $call compare8 (XL YL ) (GL EL ) 
    fpunit_exec_exec__compare16_call_stmt_4533_c_macro_;
    // G := (GH | (EH & GL)) $buffering 1
    fpunit_exec_exec__compare16_assign_stmt_4540_c_macro_;
    // E := (EH & EL) $buffering 1
    fpunit_exec_exec__compare16_assign_stmt_4545_c_macro_;
    fpunit_exec_exec__compare16_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__compare16_series_block_stmt_4503_c_mutex_);
}
void
_fpunit_exec_exec_compare24_(bit_vector * __pX, bit_vector * __pY,
			     bit_vector * __pG, bit_vector * __pE)
{
    MUTEX_DECL
	(fpunit_exec_exec__compare24_series_block_stmt_4547_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__compare24_series_block_stmt_4547_c_mutex_);
    fpunit_exec_exec__compare24_inner_inarg_prep_macro__;
    // XH := ( $slice X 23 16 ) $buffering 1
    fpunit_exec_exec__compare24_assign_stmt_4555_c_macro_;
    // XL := ( $slice X 15 0 ) $buffering 1
    fpunit_exec_exec__compare24_assign_stmt_4559_c_macro_;
    // YH := ( $slice Y 23 16 ) $buffering 1
    fpunit_exec_exec__compare24_assign_stmt_4563_c_macro_;
    // YL := ( $slice Y 15 0 ) $buffering 1
    fpunit_exec_exec__compare24_assign_stmt_4567_c_macro_;
    // $volatile $call compare8 (XH YH ) (GH EH ) 
    fpunit_exec_exec__compare24_call_stmt_4572_c_macro_;
    // $volatile $call compare16 (XL YL ) (GL EL ) 
    fpunit_exec_exec__compare24_call_stmt_4577_c_macro_;
    // G := (GH | (EH & GL)) $buffering 1
    fpunit_exec_exec__compare24_assign_stmt_4584_c_macro_;
    // E := (EH & EL) $buffering 1
    fpunit_exec_exec__compare24_assign_stmt_4589_c_macro_;
    fpunit_exec_exec__compare24_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__compare24_series_block_stmt_4547_c_mutex_);
}
void
_fpunit_exec_exec_compare32_(bit_vector * __pX, bit_vector * __pY,
			     bit_vector * __pG, bit_vector * __pE)
{
    MUTEX_DECL
	(fpunit_exec_exec__compare32_series_block_stmt_4591_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__compare32_series_block_stmt_4591_c_mutex_);
    fpunit_exec_exec__compare32_inner_inarg_prep_macro__;
    // XH := ( $slice X 31 16 ) $buffering 1
    fpunit_exec_exec__compare32_assign_stmt_4599_c_macro_;
    // XL := ( $slice X 15 0 ) $buffering 1
    fpunit_exec_exec__compare32_assign_stmt_4603_c_macro_;
    // YH := ( $slice Y 31 16 ) $buffering 1
    fpunit_exec_exec__compare32_assign_stmt_4607_c_macro_;
    // YL := ( $slice Y 15 0 ) $buffering 1
    fpunit_exec_exec__compare32_assign_stmt_4611_c_macro_;
    // $volatile $call compare16 (XH YH ) (GH EH ) 
    fpunit_exec_exec__compare32_call_stmt_4616_c_macro_;
    // $volatile $call compare16 (XL YL ) (GL EL ) 
    fpunit_exec_exec__compare32_call_stmt_4621_c_macro_;
    // G := (GH | (EH & GL)) $buffering 1
    fpunit_exec_exec__compare32_assign_stmt_4628_c_macro_;
    // E := (EH & EL) $buffering 1
    fpunit_exec_exec__compare32_assign_stmt_4633_c_macro_;
    fpunit_exec_exec__compare32_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__compare32_series_block_stmt_4591_c_mutex_);
}
void
_fpunit_exec_exec_compare35_(bit_vector * __pX, bit_vector * __pY,
			     bit_vector * __pG, bit_vector * __pE)
{
    MUTEX_DECL
	(fpunit_exec_exec__compare35_series_block_stmt_4635_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__compare35_series_block_stmt_4635_c_mutex_);
    fpunit_exec_exec__compare35_inner_inarg_prep_macro__;
    // XH := ( $slice X 34 32 ) $buffering 1
    fpunit_exec_exec__compare35_assign_stmt_4643_c_macro_;
    // XL := ( $slice X 31 0 ) $buffering 1
    fpunit_exec_exec__compare35_assign_stmt_4647_c_macro_;
    // YH := ( $slice Y 34 32 ) $buffering 1
    fpunit_exec_exec__compare35_assign_stmt_4651_c_macro_;
    // YL := ( $slice Y 31 0 ) $buffering 1
    fpunit_exec_exec__compare35_assign_stmt_4655_c_macro_;
    // GH := (XH > YH) $buffering 1
    fpunit_exec_exec__compare35_assign_stmt_4660_c_macro_;
    // EH := (XH == YH) $buffering 1
    fpunit_exec_exec__compare35_assign_stmt_4665_c_macro_;
    // $volatile $call compare32 (XL YL ) (GL EL ) 
    fpunit_exec_exec__compare35_call_stmt_4670_c_macro_;
    // G := (GH | (EH & GL)) $buffering 1
    fpunit_exec_exec__compare35_assign_stmt_4677_c_macro_;
    // E := (EH & EL) $buffering 1
    fpunit_exec_exec__compare35_assign_stmt_4682_c_macro_;
    fpunit_exec_exec__compare35_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__compare35_series_block_stmt_4635_c_mutex_);
}
void
_fpunit_exec_exec_compare4_(bit_vector * __pX, bit_vector * __pY,
			    bit_vector * __pG, bit_vector * __pE)
{
    MUTEX_DECL(fpunit_exec_exec__compare4_series_block_stmt_4298_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__compare4_series_block_stmt_4298_c_mutex_);
    fpunit_exec_exec__compare4_inner_inarg_prep_macro__;
    // X3 := ( $slice X 3 3 ) $buffering 1
    fpunit_exec_exec__compare4_assign_stmt_4306_c_macro_;
    // X2 := ( $slice X 2 2 ) $buffering 1
    fpunit_exec_exec__compare4_assign_stmt_4310_c_macro_;
    // X1 := ( $slice X 1 1 ) $buffering 1
    fpunit_exec_exec__compare4_assign_stmt_4314_c_macro_;
    // X0 := ( $slice X 0 0 ) $buffering 1
    fpunit_exec_exec__compare4_assign_stmt_4318_c_macro_;
    // Y3 := ( $slice Y 3 3 ) $buffering 1
    fpunit_exec_exec__compare4_assign_stmt_4322_c_macro_;
    // Y2 := ( $slice Y 2 2 ) $buffering 1
    fpunit_exec_exec__compare4_assign_stmt_4326_c_macro_;
    // Y1 := ( $slice Y 1 1 ) $buffering 1
    fpunit_exec_exec__compare4_assign_stmt_4330_c_macro_;
    // Y0 := ( $slice Y 0 0 ) $buffering 1
    fpunit_exec_exec__compare4_assign_stmt_4334_c_macro_;
    // G3 := (X3 & ( ~ Y3 )) $buffering 1
    fpunit_exec_exec__compare4_assign_stmt_4340_c_macro_;
    // E3 := (X3 == Y3) $buffering 1
    fpunit_exec_exec__compare4_assign_stmt_4345_c_macro_;
    // G2 := (X2 & ( ~ Y2 )) $buffering 1
    fpunit_exec_exec__compare4_assign_stmt_4351_c_macro_;
    // E2 := (X2 == Y2) $buffering 1
    fpunit_exec_exec__compare4_assign_stmt_4356_c_macro_;
    // G1 := (X1 & ( ~ Y1 )) $buffering 1
    fpunit_exec_exec__compare4_assign_stmt_4362_c_macro_;
    // E1 := (X1 == Y1) $buffering 1
    fpunit_exec_exec__compare4_assign_stmt_4367_c_macro_;
    // G0 := (X0 & ( ~ Y0 )) $buffering 1
    fpunit_exec_exec__compare4_assign_stmt_4373_c_macro_;
    // E0 := (X0 == Y0) $buffering 1
    fpunit_exec_exec__compare4_assign_stmt_4378_c_macro_;
    // G := ((G3 | (E3 & G2)) | (((E3 & E2) & G1) | ((E3 & E2) & (E1 &
    // G0)))) $buffering 1
    fpunit_exec_exec__compare4_assign_stmt_4399_c_macro_;
    // E := ((E3 & E2) & (E1 & E0)) $buffering 1
    fpunit_exec_exec__compare4_assign_stmt_4408_c_macro_;
    fpunit_exec_exec__compare4_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__compare4_series_block_stmt_4298_c_mutex_);
}
void
_fpunit_exec_exec_compare53_(bit_vector * __pX, bit_vector * __pY,
			     bit_vector * __pG, bit_vector * __pE)
{
    MUTEX_DECL
	(fpunit_exec_exec__compare53_series_block_stmt_4684_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__compare53_series_block_stmt_4684_c_mutex_);
    fpunit_exec_exec__compare53_inner_inarg_prep_macro__;
    // XHH := ( $slice X 52 48 ) $buffering 1
    fpunit_exec_exec__compare53_assign_stmt_4692_c_macro_;
    // XH := ( $slice X 47 32 ) $buffering 1
    fpunit_exec_exec__compare53_assign_stmt_4696_c_macro_;
    // XL := ( $slice X 31 0 ) $buffering 1
    fpunit_exec_exec__compare53_assign_stmt_4700_c_macro_;
    // YHH := ( $slice Y 52 48 ) $buffering 1
    fpunit_exec_exec__compare53_assign_stmt_4704_c_macro_;
    // YH := ( $slice Y 47 32 ) $buffering 1
    fpunit_exec_exec__compare53_assign_stmt_4708_c_macro_;
    // YL := ( $slice Y 31 0 ) $buffering 1
    fpunit_exec_exec__compare53_assign_stmt_4712_c_macro_;
    // GHH := (XHH > YHH) $buffering 1
    fpunit_exec_exec__compare53_assign_stmt_4717_c_macro_;
    // EHH := (XHH == YHH) $buffering 1
    fpunit_exec_exec__compare53_assign_stmt_4722_c_macro_;
    // $volatile $call compare16 (XH YH ) (GH EH ) 
    fpunit_exec_exec__compare53_call_stmt_4727_c_macro_;
    // $volatile $call compare32 (XL YL ) (GL EL ) 
    fpunit_exec_exec__compare53_call_stmt_4732_c_macro_;
    // G := (GHH | (EHH & (GH | (EH & GL)))) $buffering 1
    fpunit_exec_exec__compare53_assign_stmt_4743_c_macro_;
    // E := ((EHH & EH) & EL) $buffering 1
    fpunit_exec_exec__compare53_assign_stmt_4750_c_macro_;
    fpunit_exec_exec__compare53_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__compare53_series_block_stmt_4684_c_mutex_);
}
void
_fpunit_exec_exec_compare64_(bit_vector * __pX, bit_vector * __pY,
			     bit_vector * __pG, bit_vector * __pE)
{
    MUTEX_DECL
	(fpunit_exec_exec__compare64_series_block_stmt_4752_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__compare64_series_block_stmt_4752_c_mutex_);
    fpunit_exec_exec__compare64_inner_inarg_prep_macro__;
    // XH := ( $slice X 63 32 ) $buffering 1
    fpunit_exec_exec__compare64_assign_stmt_4760_c_macro_;
    // XL := ( $slice X 31 0 ) $buffering 1
    fpunit_exec_exec__compare64_assign_stmt_4764_c_macro_;
    // YH := ( $slice Y 63 32 ) $buffering 1
    fpunit_exec_exec__compare64_assign_stmt_4768_c_macro_;
    // YL := ( $slice Y 31 0 ) $buffering 1
    fpunit_exec_exec__compare64_assign_stmt_4772_c_macro_;
    // $volatile $call compare32 (XH YH ) (GH EH ) 
    fpunit_exec_exec__compare64_call_stmt_4777_c_macro_;
    // $volatile $call compare32 (XL YL ) (GL EL ) 
    fpunit_exec_exec__compare64_call_stmt_4782_c_macro_;
    // G := (GH | (EH & GL)) $buffering 1
    fpunit_exec_exec__compare64_assign_stmt_4789_c_macro_;
    // E := (EH & EL) $buffering 1
    fpunit_exec_exec__compare64_assign_stmt_4794_c_macro_;
    fpunit_exec_exec__compare64_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__compare64_series_block_stmt_4752_c_mutex_);
}
void
_fpunit_exec_exec_compare8_(bit_vector * __pX, bit_vector * __pY,
			    bit_vector * __pG, bit_vector * __pE)
{
    MUTEX_DECL(fpunit_exec_exec__compare8_series_block_stmt_4410_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__compare8_series_block_stmt_4410_c_mutex_);
    fpunit_exec_exec__compare8_inner_inarg_prep_macro__;
    // XH := ( $slice X 7 4 ) $buffering 1
    fpunit_exec_exec__compare8_assign_stmt_4418_c_macro_;
    // XL := ( $slice X 3 0 ) $buffering 1
    fpunit_exec_exec__compare8_assign_stmt_4422_c_macro_;
    // YH := ( $slice Y 7 4 ) $buffering 1
    fpunit_exec_exec__compare8_assign_stmt_4426_c_macro_;
    // YL := ( $slice Y 3 0 ) $buffering 1
    fpunit_exec_exec__compare8_assign_stmt_4430_c_macro_;
    // $volatile $call compare4 (XH YH ) (GH EH ) 
    fpunit_exec_exec__compare8_call_stmt_4435_c_macro_;
    // $volatile $call compare4 (XL YL ) (GL EL ) 
    fpunit_exec_exec__compare8_call_stmt_4440_c_macro_;
    // G := (GH | (EH & GL)) $buffering 1
    fpunit_exec_exec__compare8_assign_stmt_4447_c_macro_;
    // E := (EH & EL) $buffering 1
    fpunit_exec_exec__compare8_assign_stmt_4452_c_macro_;
    fpunit_exec_exec__compare8_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__compare8_series_block_stmt_4410_c_mutex_);
}
void
_fpunit_exec_exec_comparison_greater_equal_less_26_(bit_vector *
						    __poperand1,
						    bit_vector *
						    __poperand2,
						    bit_vector *
						    __pgreater_or_equal,
						    bit_vector * __plesser)
{
    MUTEX_DECL
	(fpunit_exec_exec__comparison_greater_equal_less_26_series_block_stmt_4796_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__comparison_greater_equal_less_26_series_block_stmt_4796_c_mutex_);
    fpunit_exec_exec__comparison_greater_equal_less_26_inner_inarg_prep_macro__;
    // lesser := (operand1 < operand2) $buffering 1
    fpunit_exec_exec__comparison_greater_equal_less_26_assign_stmt_4805_c_macro_;
    // greater_or_equal := ( ~ lesser ) $buffering 1
    fpunit_exec_exec__comparison_greater_equal_less_26_assign_stmt_4809_c_macro_;
    fpunit_exec_exec__comparison_greater_equal_less_26_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__comparison_greater_equal_less_26_series_block_stmt_4796_c_mutex_);
}
void
_fpunit_exec_exec_comparison_greater_equal_less_55_(bit_vector *
						    __poperand1,
						    bit_vector *
						    __poperand2,
						    bit_vector *
						    __pgreater_or_equal,
						    bit_vector * __plesser)
{
    MUTEX_DECL
	(fpunit_exec_exec__comparison_greater_equal_less_55_series_block_stmt_4811_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__comparison_greater_equal_less_55_series_block_stmt_4811_c_mutex_);
    fpunit_exec_exec__comparison_greater_equal_less_55_inner_inarg_prep_macro__;
    // operand1_lower := ( $slice operand1 27 0 ) $buffering 1
    fpunit_exec_exec__comparison_greater_equal_less_55_assign_stmt_4819_c_macro_;
    // operand1_higher := ( $slice operand1 54 28 ) $buffering 1
    fpunit_exec_exec__comparison_greater_equal_less_55_assign_stmt_4824_c_macro_;
    // operand2_lower := ( $slice operand2 27 0 ) $buffering 1
    fpunit_exec_exec__comparison_greater_equal_less_55_assign_stmt_4828_c_macro_;
    // operand2_higher := ( $slice operand2 54 28 ) $buffering 1
    fpunit_exec_exec__comparison_greater_equal_less_55_assign_stmt_4832_c_macro_;
    // higher_equal := (operand1_higher == operand2_higher) $buffering 1
    fpunit_exec_exec__comparison_greater_equal_less_55_assign_stmt_4837_c_macro_;
    // higher_lesser := (operand1_higher < operand2_higher) $buffering 1
    fpunit_exec_exec__comparison_greater_equal_less_55_assign_stmt_4842_c_macro_;
    // lower_lesser := (operand1_lower < operand2_lower) $buffering 1
    fpunit_exec_exec__comparison_greater_equal_less_55_assign_stmt_4847_c_macro_;
    // lesser := (higher_lesser | (higher_equal & lower_lesser))
    // $buffering 1
    fpunit_exec_exec__comparison_greater_equal_less_55_assign_stmt_4854_c_macro_;
    // greater_or_equal := ( ~ lesser ) $buffering 1
    fpunit_exec_exec__comparison_greater_equal_less_55_assign_stmt_4858_c_macro_;
    fpunit_exec_exec__comparison_greater_equal_less_55_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__comparison_greater_equal_less_55_series_block_stmt_4811_c_mutex_);
}
void
_fpunit_exec_exec_decode_alu_ispec_(bit_vector * __pispec,
				    bit_vector * __pis_add,
				    bit_vector * __pis_sub,
				    bit_vector * __pis_mul,
				    bit_vector * __pis_div,
				    bit_vector * __psigned_mul_div,
				    bit_vector * __pis_and,
				    bit_vector * __pis_or,
				    bit_vector * __pis_xor,
				    bit_vector * __pis_xnor,
				    bit_vector * __pis_sll,
				    bit_vector * __pis_srl,
				    bit_vector * __pis_sra,
				    bit_vector * __pnegate_second_operand,
				    bit_vector * __pwith_carry,
				    bit_vector * __pset_cc,
				    bit_vector * __ptagged_alu_op,
				    bit_vector * __ptrap_on_overflow)
{
    MUTEX_DECL
	(fpunit_exec_exec__decode_alu_ispec_series_block_stmt_4860_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__decode_alu_ispec_series_block_stmt_4860_c_mutex_);
    fpunit_exec_exec__decode_alu_ispec_inner_inarg_prep_macro__;
    // is_add := ( $slice ispec 16 16 ) $buffering 1
    fpunit_exec_exec__decode_alu_ispec_assign_stmt_4882_c_macro_;
    // is_sub := ( $slice ispec 15 15 ) $buffering 1
    fpunit_exec_exec__decode_alu_ispec_assign_stmt_4886_c_macro_;
    // is_mul := ( $slice ispec 14 14 ) $buffering 1
    fpunit_exec_exec__decode_alu_ispec_assign_stmt_4890_c_macro_;
    // is_div := ( $slice ispec 13 13 ) $buffering 1
    fpunit_exec_exec__decode_alu_ispec_assign_stmt_4894_c_macro_;
    // signed_mul_div := ( $slice ispec 12 12 ) $buffering 1
    fpunit_exec_exec__decode_alu_ispec_assign_stmt_4898_c_macro_;
    // is_and := ( $slice ispec 11 11 ) $buffering 1
    fpunit_exec_exec__decode_alu_ispec_assign_stmt_4902_c_macro_;
    // is_or := ( $slice ispec 10 10 ) $buffering 1
    fpunit_exec_exec__decode_alu_ispec_assign_stmt_4906_c_macro_;
    // is_xor := ( $slice ispec 9 9 ) $buffering 1
    fpunit_exec_exec__decode_alu_ispec_assign_stmt_4910_c_macro_;
    // is_xnor := ( $slice ispec 8 8 ) $buffering 1
    fpunit_exec_exec__decode_alu_ispec_assign_stmt_4914_c_macro_;
    // is_sll := ( $slice ispec 7 7 ) $buffering 1
    fpunit_exec_exec__decode_alu_ispec_assign_stmt_4918_c_macro_;
    // is_srl := ( $slice ispec 6 6 ) $buffering 1
    fpunit_exec_exec__decode_alu_ispec_assign_stmt_4922_c_macro_;
    // is_sra := ( $slice ispec 5 5 ) $buffering 1
    fpunit_exec_exec__decode_alu_ispec_assign_stmt_4926_c_macro_;
    // negate_second_operand := ( $slice ispec 4 4 ) $buffering 1
    fpunit_exec_exec__decode_alu_ispec_assign_stmt_4930_c_macro_;
    // with_carry := ( $slice ispec 3 3 ) $buffering 1
    fpunit_exec_exec__decode_alu_ispec_assign_stmt_4934_c_macro_;
    // set_cc := ( $slice ispec 2 2 ) $buffering 1
    fpunit_exec_exec__decode_alu_ispec_assign_stmt_4938_c_macro_;
    // tagged_alu_op := ( $slice ispec 1 1 ) $buffering 1
    fpunit_exec_exec__decode_alu_ispec_assign_stmt_4942_c_macro_;
    // trap_on_overflow := ( $slice ispec 0 0 ) $buffering 1
    fpunit_exec_exec__decode_alu_ispec_assign_stmt_4946_c_macro_;
    fpunit_exec_exec__decode_alu_ispec_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__decode_alu_ispec_series_block_stmt_4860_c_mutex_);
}
void
_fpunit_exec_exec_decode_cp_ispec_(bit_vector * __pispec,
				   bit_vector * __pcp_op2,
				   bit_vector * __pcp_op1)
{
    MUTEX_DECL
	(fpunit_exec_exec__decode_cp_ispec_series_block_stmt_4948_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__decode_cp_ispec_series_block_stmt_4948_c_mutex_);
    fpunit_exec_exec__decode_cp_ispec_inner_inarg_prep_macro__;
    // cp_op2 := ( $slice ispec 1 1 ) $buffering 1
    fpunit_exec_exec__decode_cp_ispec_assign_stmt_4955_c_macro_;
    // cp_op1 := ( $slice ispec 0 0 ) $buffering 1
    fpunit_exec_exec__decode_cp_ispec_assign_stmt_4959_c_macro_;
    fpunit_exec_exec__decode_cp_ispec_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__decode_cp_ispec_series_block_stmt_4948_c_mutex_);
}
void
_fpunit_exec_exec_decode_cti_for_offset_calculation_(bit_vector * __pinstr,
						     bit_vector *
						     __pcti_annul_flag,
						     bit_vector *
						     __pis_call,
						     bit_vector * __pis_ba,
						     bit_vector * __pis_bn,
						     bit_vector *
						     __pis_bicc,
						     bit_vector *
						     __pis_fbfcc,
						     bit_vector *
						     __pis_cbccc,
						     bit_vector * __pcond,
						     bit_vector *
						     __pimm_offset)
{
    MUTEX_DECL
	(fpunit_exec_exec__decode_cti_for_offset_calculation_series_block_stmt_4961_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__decode_cti_for_offset_calculation_series_block_stmt_4961_c_mutex_);
    fpunit_exec_exec__decode_cti_for_offset_calculation_inner_inarg_prep_macro__;
    // op := ( $slice instr 31 30 ) $buffering 1
    fpunit_exec_exec__decode_cti_for_offset_calculation_assign_stmt_4975_c_macro_;
    // op2 := ( $slice instr 24 22 ) $buffering 1
    fpunit_exec_exec__decode_cti_for_offset_calculation_assign_stmt_4979_c_macro_;
    // op3 := ( $slice instr 24 19 ) $buffering 1
    fpunit_exec_exec__decode_cti_for_offset_calculation_assign_stmt_4983_c_macro_;
    // is_call := (op == 1 ) $buffering 1
    fpunit_exec_exec__decode_cti_for_offset_calculation_assign_stmt_4988_c_macro_;
    // is_bicc := ((op == 0 ) & (op2 == 2 )) $buffering 1
    fpunit_exec_exec__decode_cti_for_offset_calculation_assign_stmt_4997_c_macro_;
    // is_fbfcc := ((op == 0 ) & (op2 == 6 )) $buffering 1
    fpunit_exec_exec__decode_cti_for_offset_calculation_assign_stmt_5006_c_macro_;
    // is_cbccc := ((op == 0 ) & (op2 == 7 )) $buffering 1
    fpunit_exec_exec__decode_cti_for_offset_calculation_assign_stmt_5015_c_macro_;
    // cond := ( $slice instr 28 25 ) $buffering 1
    fpunit_exec_exec__decode_cti_for_offset_calculation_assign_stmt_5019_c_macro_;
    // is_ba := ((is_bicc | is_fbfcc) & (cond == 8 )) $buffering 1
    fpunit_exec_exec__decode_cti_for_offset_calculation_assign_stmt_5028_c_macro_;
    // is_bn := ((is_bicc | is_fbfcc) & (cond == 0 )) $buffering 1
    fpunit_exec_exec__decode_cti_for_offset_calculation_assign_stmt_5037_c_macro_;
    // simm30to32 := ($bitcast ($uint<32>) ($cast ($int<32>) ($bitcast
    // ($int<30>) ( $slice instr 29 0 ) ) ) ) $buffering 1
    fpunit_exec_exec__decode_cti_for_offset_calculation_assign_stmt_5046_c_macro_;
    // simm22to32 := ($bitcast ($uint<32>) ($cast ($int<32>) ($bitcast
    // ($int<22>) ( $slice instr 21 0 ) ) ) ) $buffering 1
    fpunit_exec_exec__decode_cti_for_offset_calculation_assign_stmt_5054_c_macro_;
    // imm_offset := (( $mux is_call simm30to32 simm22to32 ) << 2 )
    // $buffering 1
    fpunit_exec_exec__decode_cti_for_offset_calculation_assign_stmt_5062_c_macro_;
    // cti_annul_flag := (instr [] 29 ) $buffering 1
    fpunit_exec_exec__decode_cti_for_offset_calculation_assign_stmt_5067_c_macro_;
    fpunit_exec_exec__decode_cti_for_offset_calculation_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__decode_cti_for_offset_calculation_series_block_stmt_4961_c_mutex_);
}
void
_fpunit_exec_exec_decode_cti_ispec_(bit_vector * __pispec,
				    bit_vector * __pcond,
				    bit_vector * __pis_call,
				    bit_vector * __pis_rett,
				    bit_vector * __pis_jmpl,
				    bit_vector * __pis_ticc,
				    bit_vector * __pis_bicc,
				    bit_vector * __pis_fbfcc,
				    bit_vector * __pis_cbccc)
{
    MUTEX_DECL
	(fpunit_exec_exec__decode_cti_ispec_series_block_stmt_5069_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__decode_cti_ispec_series_block_stmt_5069_c_mutex_);
    fpunit_exec_exec__decode_cti_ispec_inner_inarg_prep_macro__;
    // cond := ( $slice ispec 10 7 ) $buffering 1
    fpunit_exec_exec__decode_cti_ispec_assign_stmt_5082_c_macro_;
    // is_call := ( $slice ispec 6 6 ) $buffering 1
    fpunit_exec_exec__decode_cti_ispec_assign_stmt_5086_c_macro_;
    // is_rett := ( $slice ispec 5 5 ) $buffering 1
    fpunit_exec_exec__decode_cti_ispec_assign_stmt_5090_c_macro_;
    // is_jmpl := ( $slice ispec 4 4 ) $buffering 1
    fpunit_exec_exec__decode_cti_ispec_assign_stmt_5094_c_macro_;
    // is_ticc := ( $slice ispec 3 3 ) $buffering 1
    fpunit_exec_exec__decode_cti_ispec_assign_stmt_5098_c_macro_;
    // is_bicc := ( $slice ispec 2 2 ) $buffering 1
    fpunit_exec_exec__decode_cti_ispec_assign_stmt_5102_c_macro_;
    // is_fbfcc := ( $slice ispec 1 1 ) $buffering 1
    fpunit_exec_exec__decode_cti_ispec_assign_stmt_5106_c_macro_;
    // is_cbccc := ( $slice ispec 0 0 ) $buffering 1
    fpunit_exec_exec__decode_cti_ispec_assign_stmt_5110_c_macro_;
    fpunit_exec_exec__decode_cti_ispec_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__decode_cti_ispec_series_block_stmt_5069_c_mutex_);
}
void
_fpunit_exec_exec_decode_dti_ispec_(bit_vector * __pispec,
				    bit_vector * __pis_load,
				    bit_vector * __pis_store,
				    bit_vector * __pis_atomic_ldstub,
				    bit_vector * __pis_swap,
				    bit_vector * __pS, bit_vector * __pU,
				    bit_vector * __pFP,
				    bit_vector * __pbyte,
				    bit_vector * __phalf_word,
				    bit_vector * __pword,
				    bit_vector * __pdouble_word,
				    bit_vector * __pis_fp_access,
				    bit_vector * __pis_cp_access,
				    bit_vector * __pis_fp_cp_sr_access,
				    bit_vector * __pis_fp_cp_q_access,
				    bit_vector * __pasi_bit,
				    bit_vector * __pasi_id_8)
{
    MUTEX_DECL
	(fpunit_exec_exec__decode_dti_ispec_series_block_stmt_5112_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__decode_dti_ispec_series_block_stmt_5112_c_mutex_);
    fpunit_exec_exec__decode_dti_ispec_inner_inarg_prep_macro__;
    // is_load := ( $slice ispec 23 23 ) $buffering 1
    fpunit_exec_exec__decode_dti_ispec_assign_stmt_5134_c_macro_;
    // is_store := ( $slice ispec 22 22 ) $buffering 1
    fpunit_exec_exec__decode_dti_ispec_assign_stmt_5138_c_macro_;
    // is_atomic_ldstub := ( $slice ispec 21 21 ) $buffering 1
    fpunit_exec_exec__decode_dti_ispec_assign_stmt_5142_c_macro_;
    // is_swap := ( $slice ispec 20 20 ) $buffering 1
    fpunit_exec_exec__decode_dti_ispec_assign_stmt_5146_c_macro_;
    // S := ( $slice ispec 19 19 ) $buffering 1
    fpunit_exec_exec__decode_dti_ispec_assign_stmt_5150_c_macro_;
    // U := ( $slice ispec 18 18 ) $buffering 1
    fpunit_exec_exec__decode_dti_ispec_assign_stmt_5154_c_macro_;
    // FP := ( $slice ispec 17 17 ) $buffering 1
    fpunit_exec_exec__decode_dti_ispec_assign_stmt_5158_c_macro_;
    // double_word := ( $slice ispec 16 16 ) $buffering 1
    fpunit_exec_exec__decode_dti_ispec_assign_stmt_5162_c_macro_;
    // word := ( $slice ispec 15 15 ) $buffering 1
    fpunit_exec_exec__decode_dti_ispec_assign_stmt_5166_c_macro_;
    // half_word := ( $slice ispec 14 14 ) $buffering 1
    fpunit_exec_exec__decode_dti_ispec_assign_stmt_5170_c_macro_;
    // byte := ( $slice ispec 13 13 ) $buffering 1
    fpunit_exec_exec__decode_dti_ispec_assign_stmt_5174_c_macro_;
    // is_fp_access := ( $slice ispec 12 12 ) $buffering 1
    fpunit_exec_exec__decode_dti_ispec_assign_stmt_5178_c_macro_;
    // is_cp_access := ( $slice ispec 11 11 ) $buffering 1
    fpunit_exec_exec__decode_dti_ispec_assign_stmt_5182_c_macro_;
    // is_fp_cp_sr_access := ( $slice ispec 10 10 ) $buffering 1
    fpunit_exec_exec__decode_dti_ispec_assign_stmt_5186_c_macro_;
    // is_fp_cp_q_access := ( $slice ispec 9 9 ) $buffering 1
    fpunit_exec_exec__decode_dti_ispec_assign_stmt_5190_c_macro_;
    // asi_bit := ( $slice ispec 8 8 ) $buffering 1
    fpunit_exec_exec__decode_dti_ispec_assign_stmt_5194_c_macro_;
    // asi_id_8 := ( $slice ispec 7 0 ) $buffering 1
    fpunit_exec_exec__decode_dti_ispec_assign_stmt_5198_c_macro_;
    fpunit_exec_exec__decode_dti_ispec_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__decode_dti_ispec_series_block_stmt_5112_c_mutex_);
}
void
_fpunit_exec_exec_decode_fp_ispec_(bit_vector * __pispec,
				   bit_vector * __popf,
				   bit_vector * __pfp_op1,
				   bit_vector * __pfp_op2)
{
    MUTEX_DECL
	(fpunit_exec_exec__decode_fp_ispec_series_block_stmt_5200_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__decode_fp_ispec_series_block_stmt_5200_c_mutex_);
    fpunit_exec_exec__decode_fp_ispec_inner_inarg_prep_macro__;
    // opf := ( $slice ispec 9 2 ) $buffering 1
    fpunit_exec_exec__decode_fp_ispec_assign_stmt_5208_c_macro_;
    // fp_op1 := ( $slice ispec 1 1 ) $buffering 1
    fpunit_exec_exec__decode_fp_ispec_assign_stmt_5212_c_macro_;
    // fp_op2 := ( $slice ispec 0 0 ) $buffering 1
    fpunit_exec_exec__decode_fp_ispec_assign_stmt_5216_c_macro_;
    fpunit_exec_exec__decode_fp_ispec_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__decode_fp_ispec_series_block_stmt_5200_c_mutex_);
}
void
_fpunit_exec_exec_decode_instruction_stage_1_(bit_vector *
					      __pannulled_instr,
					      bit_vector * __pthread_head,
					      bit_vector * __pstream_head,
					      bit_vector *
					      __pdebug_mode_selected,
					      bit_vector * __plast_was_cti,
					      bit_vector * __pinstr_raw,
					      bit_vector * __pinstr_class,
					      bit_vector * __pinstr_spec,
					      bit_vector *
					      __pinstr_pipeline_usage,
					      bit_vector *
					      __pstream_corrector_info)
{
    MUTEX_DECL
	(fpunit_exec_exec__decode_instruction_stage_1_series_block_stmt_5218_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__decode_instruction_stage_1_series_block_stmt_5218_c_mutex_);
    fpunit_exec_exec__decode_instruction_stage_1_inner_inarg_prep_macro__;
    // instr := ( $mux annulled_instr _h01000000 instr_raw ) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5235_c_macro_;
    // $guard (annulled_instr) $report (decode annulled_marked_as_nop
    // instr_raw instr_raw instr instr )
    fpunit_exec_exec__decode_instruction_stage_1_stmt_5239_c_macro_;
    // $volatile op := ( $slice instr 31 30 ) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5243_c_macro_;
    // $volatile op2 := ( $slice instr 24 22 ) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5247_c_macro_;
    // $volatile op3 := ( $slice instr 24 19 ) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5251_c_macro_;
    // $volatile opf := ( $slice instr 13 5 ) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5255_c_macro_;
    // $volatile op3_col := ( $slice op3 5 4 ) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5259_c_macro_;
    // $volatile op3_row := ( $slice op3 3 0 ) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5263_c_macro_;
    // $volatile op_eq_2 := (op == 2 ) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5268_c_macro_;
    // $volatile op_eq_3 := (op == 3 ) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5273_c_macro_;
    // $volatile rs1 := ( $slice instr 18 14 ) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5277_c_macro_;
    // $volatile rs2 := ( $slice instr 4 0 ) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5281_c_macro_;
    // $volatile rd := ( $slice instr 29 25 ) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5285_c_macro_;
    // $volatile imm_flag := (instr [] 13 ) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5290_c_macro_;
    // $volatile annul_flag := (instr [] 29 ) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5295_c_macro_;
    // $report (decode_stage1 decoded_stage1___instr_info____ instr instr
    // op op op2 op2 op3 op3 opf opf rs1 rs1 rs2 rs2 rd rd imm_flag
    // imm_flag annul_flag annul_flag imm30 ( $slice instr 29 0 ) imm22 (
    // $slice instr 21 0 ) imm13 ( $slice instr 12 0 ) )
    fpunit_exec_exec__decode_instruction_stage_1_stmt_5312_c_macro_;
    // $volatile is_load_instr := (op_eq_3 & (((((op3_row < 2 ) |
    // ((op3_row == 2 ) & (op3_col < 2 ))) | (op3_row == 3 )) | ((op3_row
    // == 9 ) & (op3_col < 2 ))) | ((op3_row == 10 ) & (op3_col < 2 ))))
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5347_c_macro_;
    // $volatile is_store_instr := (op_eq_3 & ((op3_row > 3 ) & (op3_row < 
    // 8 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5358_c_macro_;
    // $volatile is_atomic_ldstub_instr := (op_eq_3 & ((op3_row == 13 ) &
    // (op3_col < 2 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5369_c_macro_;
    // $volatile is_swap_instr := (op_eq_3 & ((op3_row == 15 ) & (op3_col
    // < 2 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5380_c_macro_;
    // $volatile data_instr_type := ((is_load_instr && is_store_instr) &&
    // (is_atomic_ldstub_instr && is_swap_instr)) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5389_c_macro_;
    // $volatile is_data_transfer_instr := (data_instr_type != 0 )
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5394_c_macro_;
    // $volatile S := (((op3_row == 9 ) | (op3_row == 10 )) & (op3_col < 2 
    // )) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5407_c_macro_;
    // $volatile FP := (((op3_col == 2 ) & (op3_row != 2 )) & (op3_row < 8 
    // )) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5420_c_macro_;
    // $volatile U := ( ~ (S | FP) ) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5426_c_macro_;
    // $volatile data_transfer_data_type := ((S && U) && FP) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5433_c_macro_;
    // $volatile is_u8_transfer := ((((op3_row == 1 ) & (op3_col < 2 )) |
    // ((op3_row == 5 ) & (op3_col < 2 ))) | (((op3_row == 9 ) & (op3_col
    // < 2 )) | is_atomic_ldstub_instr)) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5460_c_macro_;
    // $volatile is_u16_transfer := ((((op3_row == 2 ) & (op3_col < 2 )) | 
    // ((op3_row == 10 ) & (op3_col < 2 ))) | ((op3_row == 6 ) & (op3_col
    // < 2 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5485_c_macro_;
    // $volatile is_u64_transfer := (((op3_row == 3 ) | (op3_row == 7 )) | 
    // ((op3_row == 6 ) & (op3_col > 1 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5502_c_macro_;
    // $volatile is_u32_transfer := ( ~ ((is_u8_transfer |
    // is_u16_transfer) | is_u64_transfer) ) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5510_c_macro_;
    // $volatile data_transfer_width := ((is_u64_transfer &&
    // is_u32_transfer) && (is_u16_transfer && is_u8_transfer)) $buffering 
    // 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5519_c_macro_;
    // $volatile is_fp_load := (is_load_instr & FP) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5524_c_macro_;
    // $volatile is_fp_load_to_fsr := (is_fp_load & (op3_row == 1 ))
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5531_c_macro_;
    // $volatile is_fp_store := (is_store_instr & FP) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5536_c_macro_;
    // $volatile is_fp_store_from_fsr := (is_fp_store & (op3_row == 5 ))
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5543_c_macro_;
    // $volatile is_fp_store_from_fq := (is_fp_store & (op3_row == 6 ))
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5550_c_macro_;
    // $volatile is_fp_access := (is_fp_load | is_fp_store) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5555_c_macro_;
    // $volatile is_cp_load := (is_load_instr & (op3_col == 3 ))
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5562_c_macro_;
    // $volatile is_cp_load_to_cpsr := (is_cp_load & (op3_row == 1 ))
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5569_c_macro_;
    // $volatile is_cp_store := (is_store_instr & (op3_col == 3 ))
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5576_c_macro_;
    // $volatile is_cp_store_from_cpsr := (is_cp_store & (op3_row == 5 ))
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5583_c_macro_;
    // $volatile is_cp_store_from_cpq := (is_cp_store & (op3_row == 6 ))
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5590_c_macro_;
    // $volatile is_cp_access := (is_cp_load | is_cp_store) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5595_c_macro_;
    // $volatile is_fp_cp_sr_access := ((is_fp_load_to_fsr |
    // is_fp_store_from_fsr) | (is_cp_load_to_cpsr |
    // is_cp_store_from_cpsr)) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5604_c_macro_;
    // $volatile is_fp_cp_q_access := (is_fp_store_from_fq |
    // is_cp_store_from_cpq) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5609_c_macro_;
    // $volatile asi_bit := (op_eq_3 & (op3_col == 1 )) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5616_c_macro_;
    // $volatile asi_id_8 := ( $slice instr 12 5 ) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5620_c_macro_;
    // $volatile data_transfer_instr_spec := ((((data_instr_type &&
    // data_transfer_data_type) && data_transfer_width) && (is_fp_access
    // && is_cp_access)) && ((is_fp_cp_sr_access && is_fp_cp_q_access) &&
    // (asi_bit && asi_id_8))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5639_c_macro_;
    // $guard (is_data_transfer_instr) $report (decode_stage1
    // decode_stage_1_data_transfer_ispec__ data_instr_type
    // data_instr_type data_transfer_data_type data_transfer_data_type
    // data_transfer_width data_transfer_width is_fp_access is_fp_access
    // is_cp_access is_cp_access is_fp_cp_sr_access is_fp_cp_sr_access
    // is_fp_cp_q_access is_fp_cp_q_access asi_bit asi_bit asi_id_8
    // asi_id_8 )
    fpunit_exec_exec__decode_instruction_stage_1_stmt_5650_c_macro_;
    // $volatile cond := ( $slice instr 28 25 ) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5654_c_macro_;
    // $volatile is_call := (op == 1 ) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5659_c_macro_;
    // $volatile is_bicc := ((op == 0 ) & (op2 == 2 )) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5668_c_macro_;
    // $volatile is_ba_or_bn_cond := ((cond == 8 ) | (cond == 0 ))
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5677_c_macro_;
    // $volatile is_fbfcc := ((op == 0 ) & (op2 == 6 )) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5686_c_macro_;
    // $volatile is_cbccc := ((op == 0 ) & (op2 == 7 )) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5695_c_macro_;
    // $volatile is_ticc := (op_eq_2 & ((op3_row == 10 ) & (op3_col == 3
    // ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5706_c_macro_;
    // $volatile is_jmpl := (op_eq_2 & ((op3_row == 8 ) & (op3_col == 3
    // ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5717_c_macro_;
    // $volatile is_rett := (op_eq_2 & ((op3_row == 9 ) & (op3_col == 3
    // ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5728_c_macro_;
    // $volatile control_transfer_instr_spec := (((cond && is_call) &&
    // (is_rett && is_jmpl)) && ((is_ticc && is_bicc) && (is_fbfcc &&
    // is_cbccc))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5745_c_macro_;
    // $volatile is_control_transfer_instr := (((is_call | is_rett) |
    // (is_jmpl | is_ticc)) | ((is_bicc | is_fbfcc) | is_cbccc))
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5760_c_macro_;
    // $guard (is_control_transfer_instr) $report (decode_stage1
    // decode_stage1_control_transfer_ispec__ cond cond is_call is_call
    // is_rett is_rett is_jmpl is_jmpl is_ticc is_ticc is_bicc is_bicc
    // is_fbfcc is_fbfcc is_cbccc is_cbccc )
    fpunit_exec_exec__decode_instruction_stage_1_stmt_5770_c_macro_;
    // $volatile is_nop := (((op == 0 ) & (op2 == 4 )) & ((rd == 0 ) & ((
    // $slice instr 21 0 ) == 0 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5788_c_macro_;
    // $volatile is_sethi := (((op == 0 ) & (op2 == 4 )) & ((rd != 0 ) |
    // (( $slice instr 21 0 ) != 0 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5806_c_macro_;
    // $volatile is_mulscc := ((op_eq_2 & (op3_col == 2 )) & (op3_row == 4 
    // )) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5817_c_macro_;
    // $volatile is_flush := ((op_eq_2 & (op3_col == 3 )) & (op3_row == 11 
    // )) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5828_c_macro_;
    // $volatile is_stbar := (((op_eq_2 & (op3_col == 2 )) & (op3_row == 8 
    // )) & ((rd == 0 ) & (rs1 == 15 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5847_c_macro_;
    // $volatile is_save := ((op_eq_2 & (op3_col == 3 )) & (op3_row == 12
    // )) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5858_c_macro_;
    // $volatile is_restore := (op_eq_2 & ((op3_col == 3 ) & (op3_row ==
    // 13 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5869_c_macro_;
    // $volatile is_read_asr := ((op_eq_2 & (op3_col == 2 )) & ((op3_row
    // == 8 ) & (rs1 != 0 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5884_c_macro_;
    // $volatile is_read_y := ((op_eq_2 & (op3_col == 2 )) & ((op3_row ==
    // 8 ) & (rs1 == 0 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5899_c_macro_;
    // $volatile is_read_psr := (op_eq_2 & ((op3_col == 2 ) & (op3_row ==
    // 9 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5910_c_macro_;
    // $volatile is_read_wim := (op_eq_2 & ((op3_col == 2 ) & (op3_row ==
    // 10 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5921_c_macro_;
    // $volatile is_read_tbr := (op_eq_2 & ((op3_col == 2 ) & (op3_row ==
    // 11 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5932_c_macro_;
    // $volatile is_write_asr := ((op_eq_2 & (op3_col == 3 )) & ((op3_row
    // == 0 ) & (rd != 0 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5947_c_macro_;
    // $volatile is_write_y := ((op_eq_2 & (op3_col == 3 )) & ((op3_row == 
    // 0 ) & (rd == 0 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5962_c_macro_;
    // $volatile is_write_psr := (op_eq_2 & ((op3_col == 3 ) & (op3_row == 
    // 1 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5973_c_macro_;
    // $volatile is_write_wim := (op_eq_2 & ((op3_col == 3 ) & (op3_row == 
    // 2 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5984_c_macro_;
    // $volatile is_write_tbr := (op_eq_2 & ((op3_col == 3 ) & (op3_row == 
    // 3 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_5995_c_macro_;
    // $volatile misc_instr_spec := (((((is_nop && is_sethi) && is_mulscc) 
    // && (is_flush && is_stbar)) && ((is_save && is_restore) &&
    // (is_read_asr && is_read_y))) && (((is_read_psr && is_read_wim) &&
    // (is_read_tbr && is_write_asr)) && ((is_write_y && is_write_psr) &&
    // (is_write_wim && is_write_tbr)))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6030_c_macro_;
    // $volatile is_misc_instr := (misc_instr_spec != 0 ) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6035_c_macro_;
    // $guard (is_misc_instr) $report (decode_stage1
    // decode_stage1_misc_instr_ispec__ is_nop is_nop is_sethi is_sethi
    // is_mulscc is_mulscc is_flush is_flush is_stbar is_stbar is_save
    // is_save is_restore is_restore is_read_asr is_read_asr is_read_y
    // is_read_y is_read_psr is_read_psr is_read_wim is_read_wim
    // is_read_tbr is_read_tbr is_write_asr is_write_asr is_write_y
    // is_write_y is_write_psr is_write_psr is_write_wim is_write_wim
    // is_write_tbr is_write_tbr )
    fpunit_exec_exec__decode_instruction_stage_1_stmt_6054_c_macro_;
    // $volatile is_add := (op_eq_2 & (((op3_row == 0 ) & (op3_col < 3 ))
    // | (((op3_row == 2 ) & (op3_col == 2 )) | ((op3_row == 8 ) &
    // (op3_col < 2 ))))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6081_c_macro_;
    // $volatile is_sub := (op_eq_2 & ((((op3_row == 4 ) | (op3_row == 12
    // )) & (op3_col < 2 )) | (((op3_row == 1 ) | (op3_row == 3 )) &
    // (op3_col == 2 )))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6108_c_macro_;
    // $volatile with_carry := ((is_add & (op3_row == 8 )) | (is_sub &
    // (op3_row == 12 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6121_c_macro_;
    // $volatile is_mul := (op_eq_2 & (((op3_row == 10 ) | (op3_row == 11
    // )) & (op3_col < 2 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6136_c_macro_;
    // $volatile is_div := (op_eq_2 & ((op3_row > 13 ) & (op3_col < 2 )))
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6147_c_macro_;
    // $volatile signed_mul_div := ((is_mul & (op3_row == 11 )) | (is_div
    // & (op3_row == 15 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6160_c_macro_;
    // $volatile is_and := (op_eq_2 & (((op3_row == 1 ) | (op3_row == 5 )) 
    // & (op3_col < 2 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6175_c_macro_;
    // $volatile is_or := (op_eq_2 & (((op3_row == 2 ) | (op3_row == 6 ))
    // & (op3_col < 2 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6190_c_macro_;
    // $volatile is_xor := (op_eq_2 & ((op3_row == 3 ) & (op3_col < 2 )))
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6201_c_macro_;
    // $volatile is_xnor := (op_eq_2 & ((op3_row == 7 ) & (op3_col < 2 ))) 
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6212_c_macro_;
    // $volatile is_sll := (op_eq_2 & ((op3_row == 5 ) & (op3_col == 2 ))) 
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6223_c_macro_;
    // $volatile is_srl := (op_eq_2 & ((op3_row == 6 ) & (op3_col == 2 ))) 
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6234_c_macro_;
    // $volatile is_sra := (op_eq_2 & ((op3_row == 7 ) & (op3_col == 2 ))) 
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6245_c_macro_;
    // $volatile negate_second_operand := (op_eq_2 & (((op3_row == 5 ) |
    // (op3_row == 6 )) & (op3_col < 2 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6260_c_macro_;
    // $volatile set_cc := (op_eq_2 & ((( ~ ((op3_row == 9 ) | (op3_row == 
    // 13 )) ) & (op3_col == 1 )) | ((op3_row < 5 ) & (op3_col == 2 ))))
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6284_c_macro_;
    // $volatile tagged_alu_op := (op_eq_2 & ((op3_row < 4 ) & (op3_col == 
    // 2 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6295_c_macro_;
    // $volatile trap_on_overflow := (op_eq_2 & (((op3_row == 2 ) |
    // (op3_row == 3 )) & (op3_col == 2 ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6310_c_macro_;
    // $volatile is_alu_instr := ((((is_add | is_sub) | is_mul) | ((is_div 
    // | is_and) | is_or)) | (((is_xor | is_xnor) | is_sll) | (is_srl |
    // is_sra))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6333_c_macro_;
    // $volatile alu_instr_spec := (((((is_add && is_sub) && is_mul) &&
    // (is_div && signed_mul_div)) && ((is_and && is_or) && (is_xor &&
    // is_xnor))) && (((is_sll && is_srl) && (is_sra &&
    // negate_second_operand)) && ((with_carry && set_cc) &&
    // (tagged_alu_op && trap_on_overflow)))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6368_c_macro_;
    // $guard (is_alu_instr) $report (decode_stage1
    // decode_stage1_alu_ispec__ is_add is_add is_sub is_sub is_mul is_mul 
    // is_div is_div signed_mul_div signed_mul_div is_and is_and is_or
    // is_or is_xor is_xor is_xnor is_xnor is_sll is_sll is_srl is_srl
    // is_sra is_sra negate_second_operand negate_second_operand
    // with_carry with_carry set_cc set_cc tagged_alu_op tagged_alu_op
    // trap_on_overflow trap_on_overflow )
    fpunit_exec_exec__decode_instruction_stage_1_stmt_6387_c_macro_;
    // $volatile is_fp_op_1 := (op_eq_2 & ((op3_col == 3 ) & (op3_row == 4 
    // ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6398_c_macro_;
    // $volatile is_fp_op_2 := (op_eq_2 & ((op3_col == 3 ) & (op3_row == 5 
    // ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6409_c_macro_;
    // $volatile fp_op_instr_spec := ((opf && is_fp_op_2) && is_fp_op_1)
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6416_c_macro_;
    // $volatile is_fp_op_instr := (is_fp_op_2 | is_fp_op_1) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6421_c_macro_;
    // $guard (is_fp_op_instr) $report (decode_stage1
    // decode_stage1_fp_ispec__ opf opf is_fp_op_1 is_fp_op_1 is_fp_op_2
    // is_fp_op_2 )
    fpunit_exec_exec__decode_instruction_stage_1_stmt_6426_c_macro_;
    // $volatile is_cp_op_1 := (op_eq_2 & ((op3_col == 3 ) & (op3_row == 6 
    // ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6437_c_macro_;
    // $volatile is_cp_op_2 := (op_eq_2 & ((op3_col == 3 ) & (op3_row == 7 
    // ))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6448_c_macro_;
    // $volatile cp_op_instr_spec := (is_cp_op_2 && is_cp_op_1) $buffering 
    // 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6453_c_macro_;
    // $volatile is_cp_op_instr := (is_cp_op_2 | is_cp_op_1) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6458_c_macro_;
    // $guard (is_cp_op_instr) $report (decode_stage1
    // decode_stage1_cp_ispec__ is_cp_op_1 is_cp_op_1 is_cp_op_2
    // is_cp_op_2 )
    fpunit_exec_exec__decode_instruction_stage_1_stmt_6462_c_macro_;
    // $volatile is_illegal_instr := ( ~ (((is_cp_op_instr |
    // is_fp_op_instr) | is_alu_instr) | ((is_control_transfer_instr |
    // is_data_transfer_instr) | is_misc_instr)) ) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6476_c_macro_;
    // $report (decode_stage1 instruction_classification__ dti
    // is_data_transfer_instr cti is_control_transfer_instr alu
    // is_alu_instr misc is_misc_instr fp is_fp_op_instr cp is_cp_op_instr 
    // illegal is_illegal_instr )
    fpunit_exec_exec__decode_instruction_stage_1_stmt_6484_c_macro_;
    // instr_spec := (((( $mux is_data_transfer_instr ($bitcast
    // ($uint<24>) data_transfer_instr_spec ) _b0 ) | ( $mux
    // is_control_transfer_instr ($bitcast ($uint<24>)
    // control_transfer_instr_spec ) _b0 ) ) | (( $mux is_alu_instr
    // ($bitcast ($uint<24>) alu_instr_spec ) _b0 ) | ( $mux is_misc_instr 
    // ($bitcast ($uint<24>) misc_instr_spec ) _b0 ) )) | ((( $mux
    // is_fp_op_instr ($bitcast ($uint<24>) fp_op_instr_spec ) _b0 ) | (
    // $mux is_cp_op_instr ($bitcast ($uint<24>) cp_op_instr_spec ) _b0 )
    // ) | ( $mux is_illegal_instr 0 _b0 ) )) $buffering 2
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6526_c_macro_;
    // instr_class := (((( $mux is_data_transfer_instr DATA_TRANSFER_INSTR 
    // _b0 ) | ( $mux is_control_transfer_instr CONTROL_TRANSFER_INSTR _b0 
    // ) ) | (( $mux is_alu_instr ALU_INSTR _b0 ) | ( $mux is_misc_instr
    // MISC_INSTR _b0 ) )) | ((( $mux is_fp_op_instr FP_INSTR _b0 ) | (
    // $mux is_cp_op_instr CP_INSTR _b0 ) ) | ( $mux is_illegal_instr
    // ILLEGAL_INSTR _b0 ) )) $buffering 2
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6562_c_macro_;
    // $report (decode_stage1 instr_spec_and_class__ instr_spec instr_spec 
    // instr_class instr_class )
    fpunit_exec_exec__decode_instruction_stage_1_stmt_6565_c_macro_;
    // $volatile uses_iu_cc := (is_bicc & ( ~ is_ba_or_bn_cond ))
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6571_c_macro_;
    // $volatile uses_fp_cc := (is_fbfcc & ( ~ is_ba_or_bn_cond ))
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6577_c_macro_;
    // $volatile iu_cti := (((is_call | is_rett) | is_jmpl) | (is_ticc |
    // is_bicc)) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6588_c_macro_;
    // $volatile uses_iu1 := (((( ~ is_bicc ) & iu_cti) | is_alu_instr) |
    // (is_misc_instr & ( ~ ((is_flush | is_nop) | is_stbar) )))
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6605_c_macro_;
    // $volatile reads_iu_rfile := ((uses_iu1 | is_data_transfer_instr) |
    // ((is_bicc & ( ~ is_ba_or_bn_cond )) | (is_misc_instr & ( ~ is_nop
    // )))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6620_c_macro_;
    // $volatile fu_cti := is_fbfcc $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6623_c_macro_;
    // $volatile cp_cti := is_cbccc $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6626_c_macro_;
    // $volatile iu_flush := is_flush $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6629_c_macro_;
    // $volatile iu_write_psr := is_write_psr $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6632_c_macro_;
    // $volatile iu_mmu_ctrl_write := ((is_store_instr & asi_bit) &
    // ((asi_id_8 == ASI_MMU_FLUSH_PROBE) | (asi_id_8 ==
    // ASI_MMU_REGISTER))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6645_c_macro_;
    // stream_corrector_info := (((iu_cti && fu_cti) && cp_cti) &&
    // ((iu_flush && iu_write_psr) && iu_mmu_ctrl_write)) $buffering 2
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6658_c_macro_;
    // $volatile uses_iu2 := (((is_alu_instr | is_rett) | is_call) |
    // ((is_jmpl | (is_misc_instr & ( ~ ((is_nop | is_flush) | is_stbar)
    // ))) | (is_data_transfer_instr & (((is_load_instr & ( ~
    // (is_fp_access | is_cp_access) )) | is_atomic_ldstub_instr) |
    // is_swap_instr)))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6689_c_macro_;
    // $volatile cpunit_cti := (is_control_transfer_instr & is_cbccc)
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6694_c_macro_;
    // $volatile uses_fu1 := (is_fp_op_instr | (is_data_transfer_instr &
    // is_fp_load)) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6701_c_macro_;
    // $volatile reads_fu_rfile := ((is_fp_op_instr | (is_fbfcc & ( ~
    // is_ba_or_bn_cond ))) | (is_data_transfer_instr & (is_fp_load |
    // is_fp_store))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6715_c_macro_;
    // $volatile fu1_can_trap := is_fp_op_instr $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6718_c_macro_;
    // $volatile uses_fu2 := (is_fp_op_instr | (is_data_transfer_instr &
    // (is_fp_load | is_fp_store))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6727_c_macro_;
    // $volatile uses_cu1 := (ZERO_1 & ((is_cp_op_instr | cpunit_cti) |
    // (is_data_transfer_instr & (is_cp_store | is_cp_load)))) $buffering
    // 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6740_c_macro_;
    // $volatile uses_cu2 := uses_cu1 $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6743_c_macro_;
    // $volatile uses_ls := (is_data_transfer_instr | (is_misc_instr &
    // (is_flush | is_stbar))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6752_c_macro_;
    // $volatile iu1_to_iu2_fast := ((uses_iu1 & ( ~ tagged_alu_op )) & (( 
    // ~ trap_on_overflow ) & ((((is_and | is_or) | is_xor) | ((is_xnor |
    // is_add) | is_sub)) | (((is_sethi | is_sll) | is_srl) | (is_sra |
    // is_mul))))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6783_c_macro_;
    // $volatile iu1_can_trap := (uses_iu1 & (((is_ticc | is_jmpl) |
    // is_rett) | ((is_div | (tagged_alu_op & trap_on_overflow)) |
    // (is_misc_instr & ( ~ (((is_nop | is_stbar) | is_sethi) | (is_mulscc 
    // | is_flush)) ))))) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6811_c_macro_;
    // $volatile iu1_to_iu2 := ((uses_iu1 & ( ~ iu1_to_iu2_fast )) &
    // (uses_iu2 | iu1_can_trap)) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6821_c_macro_;
    // $volatile iu1_to_sc := (uses_iu1 & (((iu_cti & ( ~ is_call )) & ( ~ 
    // is_bicc )) | iu_write_psr)) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6834_c_macro_;
    // $volatile iu_reg_to_ls := ((is_data_transfer_instr | is_flush) |
    // is_stbar) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6841_c_macro_;
    // $volatile iu1_to_ls_trap := iu1_can_trap $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6844_c_macro_;
    // $volatile iu1_to_fu2 := iu1_can_trap $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6847_c_macro_;
    // $volatile iu1_to_cu2 := ZERO_1 $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6850_c_macro_;
    // $volatile fu1_to_fu2 := uses_fu1 $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6853_c_macro_;
    // $volatile fu1_to_sc := ZERO_1 $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6856_c_macro_;
    // $volatile fu_reg_to_ls := (is_data_transfer_instr & is_fp_store)
    // $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6861_c_macro_;
    // $volatile fu1_to_ls := fu1_can_trap $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6864_c_macro_;
    // $volatile fu1_to_iu2 := fu1_can_trap $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6867_c_macro_;
    // $volatile fu1_to_cu2 := ZERO_1 $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6870_c_macro_;
    // $volatile cu1_to_cu2 := uses_cu1 $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6873_c_macro_;
    // $volatile cu1_to_sc := ZERO_1 $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6876_c_macro_;
    // $volatile cu1_to_ls := ZERO_1 $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6879_c_macro_;
    // $volatile cu1_to_iu2 := ZERO_1 $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6882_c_macro_;
    // $volatile cu1_to_fu2 := ZERO_1 $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6885_c_macro_;
    // $volatile send_from_sc_to_rest := (((thread_head | stream_head) |
    // (last_was_cti | is_rett)) | ((is_write_psr | is_flush) |
    // iu_mmu_ctrl_write)) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6900_c_macro_;
    // $volatile sc_to_iu2 := send_from_sc_to_rest $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6903_c_macro_;
    // $volatile sc_to_fu2 := send_from_sc_to_rest $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6906_c_macro_;
    // $volatile sc_to_cu2 := (ZERO_1 & send_from_sc_to_rest) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6911_c_macro_;
    // $volatile sc_to_ls := send_from_sc_to_rest $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6914_c_macro_;
    // $volatile ls_to_iu2 := is_data_transfer_instr $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6917_c_macro_;
    // $volatile ls_to_fu2 := is_data_transfer_instr $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6920_c_macro_;
    // $volatile ls_to_cu2 := (ZERO_1 & uses_ls) $buffering 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_6925_c_macro_;
    // instr_pipeline_usage := ((((((uses_iu_cc && uses_fp_cc) &&
    // uses_iu1) && (uses_iu2 && uses_ls)) && (((uses_fu1 && uses_fu2) &&
    // uses_cu1) && (uses_cu2 && reads_iu_rfile))) && ((((iu1_can_trap &&
    // reads_fu_rfile) && fu1_can_trap) && (iu1_to_iu2_fast &&
    // iu1_to_iu2)) && ((iu1_to_sc && iu_reg_to_ls) && (iu1_to_ls_trap &&
    // iu1_to_fu2)))) && (((((iu1_to_cu2 && fu1_to_fu2) && fu1_to_sc) &&
    // (fu_reg_to_ls && fu1_to_ls)) && (((fu1_to_iu2 && fu1_to_cu2) &&
    // cu1_to_cu2) && (cu1_to_sc && cu1_to_ls))) && ((((cu1_to_iu2 &&
    // cu1_to_fu2) && sc_to_iu2) && (sc_to_fu2 && sc_to_cu2)) &&
    // ((sc_to_ls && ls_to_iu2) && (ls_to_fu2 && ls_to_cu2))))) $buffering 
    // 1
    fpunit_exec_exec__decode_instruction_stage_1_assign_stmt_7002_c_macro_;
    fpunit_exec_exec__decode_instruction_stage_1_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__decode_instruction_stage_1_series_block_stmt_5218_c_mutex_);
}
void
_fpunit_exec_exec_decode_is_flush_asi_(bit_vector * __pasi_id_8,
				       bit_vector * __pis_flush_asi)
{
    MUTEX_DECL
	(fpunit_exec_exec__decode_is_flush_asi_series_block_stmt_7004_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__decode_is_flush_asi_series_block_stmt_7004_c_mutex_);
    fpunit_exec_exec__decode_is_flush_asi_inner_inarg_prep_macro__;
    // is_flush_asi := (((((asi_id_8 == ASI_FLUSH_I_D_PAGE) | (asi_id_8 == 
    // ASI_FLUSH_I_D_SEGMENT)) | (asi_id_8 == ASI_FLUSH_I_D_REGION)) |
    // ((asi_id_8 == ASI_FLUSH_I_D_CONTEXT) | (asi_id_8 ==
    // ASI_FLUSH_I_D_USER))) | ((((asi_id_8 == ASI_FLUSH_I_PAGE) |
    // (asi_id_8 == ASI_FLUSH_I_SEGMENT)) | (asi_id_8 ==
    // ASI_FLUSH_I_REGION)) | ((asi_id_8 == ASI_FLUSH_I_CONTEXT) |
    // (asi_id_8 == ASI_FLUSH_I_USER)))) $buffering 1
    fpunit_exec_exec__decode_is_flush_asi_assign_stmt_7047_c_macro_;
    fpunit_exec_exec__decode_is_flush_asi_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__decode_is_flush_asi_series_block_stmt_7004_c_mutex_);
}
void
_fpunit_exec_exec_decode_misc_ispec_(bit_vector * __pispec,
				     bit_vector * __pis_nop,
				     bit_vector * __pis_sethi,
				     bit_vector * __pis_mulscc,
				     bit_vector * __pis_flush,
				     bit_vector * __pis_stbar,
				     bit_vector * __pis_save,
				     bit_vector * __pis_restore,
				     bit_vector * __pis_read_asr,
				     bit_vector * __pis_read_y,
				     bit_vector * __pis_read_psr,
				     bit_vector * __pis_read_wim,
				     bit_vector * __pis_read_tbr,
				     bit_vector * __pis_write_asr,
				     bit_vector * __pis_write_y,
				     bit_vector * __pis_write_psr,
				     bit_vector * __pis_write_wim,
				     bit_vector * __pis_write_tbr)
{
    MUTEX_DECL
	(fpunit_exec_exec__decode_misc_ispec_series_block_stmt_7049_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__decode_misc_ispec_series_block_stmt_7049_c_mutex_);
    fpunit_exec_exec__decode_misc_ispec_inner_inarg_prep_macro__;
    // is_nop := ( $slice ispec 16 16 ) $buffering 1
    fpunit_exec_exec__decode_misc_ispec_assign_stmt_7071_c_macro_;
    // is_sethi := ( $slice ispec 15 15 ) $buffering 1
    fpunit_exec_exec__decode_misc_ispec_assign_stmt_7075_c_macro_;
    // is_mulscc := ( $slice ispec 14 14 ) $buffering 1
    fpunit_exec_exec__decode_misc_ispec_assign_stmt_7079_c_macro_;
    // is_flush := ( $slice ispec 13 13 ) $buffering 1
    fpunit_exec_exec__decode_misc_ispec_assign_stmt_7083_c_macro_;
    // is_stbar := ( $slice ispec 12 12 ) $buffering 1
    fpunit_exec_exec__decode_misc_ispec_assign_stmt_7087_c_macro_;
    // is_save := ( $slice ispec 11 11 ) $buffering 1
    fpunit_exec_exec__decode_misc_ispec_assign_stmt_7091_c_macro_;
    // is_restore := ( $slice ispec 10 10 ) $buffering 1
    fpunit_exec_exec__decode_misc_ispec_assign_stmt_7095_c_macro_;
    // is_read_asr := ( $slice ispec 9 9 ) $buffering 1
    fpunit_exec_exec__decode_misc_ispec_assign_stmt_7099_c_macro_;
    // is_read_y := ( $slice ispec 8 8 ) $buffering 1
    fpunit_exec_exec__decode_misc_ispec_assign_stmt_7103_c_macro_;
    // is_read_psr := ( $slice ispec 7 7 ) $buffering 1
    fpunit_exec_exec__decode_misc_ispec_assign_stmt_7107_c_macro_;
    // is_read_wim := ( $slice ispec 6 6 ) $buffering 1
    fpunit_exec_exec__decode_misc_ispec_assign_stmt_7111_c_macro_;
    // is_read_tbr := ( $slice ispec 5 5 ) $buffering 1
    fpunit_exec_exec__decode_misc_ispec_assign_stmt_7115_c_macro_;
    // is_write_asr := ( $slice ispec 4 4 ) $buffering 1
    fpunit_exec_exec__decode_misc_ispec_assign_stmt_7119_c_macro_;
    // is_write_y := ( $slice ispec 3 3 ) $buffering 1
    fpunit_exec_exec__decode_misc_ispec_assign_stmt_7123_c_macro_;
    // is_write_psr := ( $slice ispec 2 2 ) $buffering 1
    fpunit_exec_exec__decode_misc_ispec_assign_stmt_7127_c_macro_;
    // is_write_wim := ( $slice ispec 1 1 ) $buffering 1
    fpunit_exec_exec__decode_misc_ispec_assign_stmt_7131_c_macro_;
    // is_write_tbr := ( $slice ispec 0 0 ) $buffering 1
    fpunit_exec_exec__decode_misc_ispec_assign_stmt_7135_c_macro_;
    fpunit_exec_exec__decode_misc_ispec_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__decode_misc_ispec_series_block_stmt_7049_c_mutex_);
}
void
_fpunit_exec_exec_decode_stream_corrector_info_(bit_vector * __psc_info,
						bit_vector * __piu_cti,
						bit_vector * __pfp_cti,
						bit_vector * __pcp_cti,
						bit_vector * __piu_flush,
						bit_vector *
						__piu_write_psr,
						bit_vector *
						__piu_mmu_ctrl_write)
{
    MUTEX_DECL
	(fpunit_exec_exec__decode_stream_corrector_info_series_block_stmt_7137_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__decode_stream_corrector_info_series_block_stmt_7137_c_mutex_);
    fpunit_exec_exec__decode_stream_corrector_info_inner_inarg_prep_macro__;
    // iu_cti := ( $slice sc_info 5 5 ) $buffering 1
    fpunit_exec_exec__decode_stream_corrector_info_assign_stmt_7148_c_macro_;
    // fp_cti := ( $slice sc_info 4 4 ) $buffering 1
    fpunit_exec_exec__decode_stream_corrector_info_assign_stmt_7152_c_macro_;
    // cp_cti := ( $slice sc_info 3 3 ) $buffering 1
    fpunit_exec_exec__decode_stream_corrector_info_assign_stmt_7156_c_macro_;
    // iu_flush := ( $slice sc_info 2 2 ) $buffering 1
    fpunit_exec_exec__decode_stream_corrector_info_assign_stmt_7160_c_macro_;
    // iu_write_psr := ( $slice sc_info 1 1 ) $buffering 1
    fpunit_exec_exec__decode_stream_corrector_info_assign_stmt_7164_c_macro_;
    // iu_mmu_ctrl_write := ( $slice sc_info 0 0 ) $buffering 1
    fpunit_exec_exec__decode_stream_corrector_info_assign_stmt_7168_c_macro_;
    fpunit_exec_exec__decode_stream_corrector_info_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__decode_stream_corrector_info_series_block_stmt_7137_c_mutex_);
}
void
_fpunit_exec_exec_decode_thread_control_word_(bit_vector * __pctrl_word,
					      bit_vector *
					      __psc_instr_class,
					      bit_vector * __pdebug_mode,
					      bit_vector *
					      __plogger_active,
					      bit_vector * __pproc_ilvl,
					      bit_vector * __penable_traps,
					      bit_vector *
					      __psingle_step_mode,
					      bit_vector *
					      __pignore_break_points,
					      bit_vector * __pS,
					      bit_vector * __pimm_bit,
					      bit_vector * __pis_write_psr,
					      bit_vector *
					      __pis_mmu_ctrl_write,
					      bit_vector * __pis_flush,
					      bit_vector * __pis_cti,
					      bit_vector * __pmis_predict,
					      bit_vector * __ptrap_bit,
					      bit_vector * __pstream_head,
					      bit_vector * __pthread_head)
{
    MUTEX_DECL
	(fpunit_exec_exec__decode_thread_control_word_series_block_stmt_7170_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__decode_thread_control_word_series_block_stmt_7170_c_mutex_);
    fpunit_exec_exec__decode_thread_control_word_inner_inarg_prep_macro__;
    // sc_instr_class := ( $slice ctrl_word 21 19 ) $buffering 1
    fpunit_exec_exec__decode_thread_control_word_assign_stmt_7192_c_macro_;
    // debug_mode := ( $slice ctrl_word 18 18 ) $buffering 1
    fpunit_exec_exec__decode_thread_control_word_assign_stmt_7196_c_macro_;
    // logger_active := ( $slice ctrl_word 17 17 ) $buffering 1
    fpunit_exec_exec__decode_thread_control_word_assign_stmt_7200_c_macro_;
    // proc_ilvl := ( $slice ctrl_word 16 13 ) $buffering 1
    fpunit_exec_exec__decode_thread_control_word_assign_stmt_7204_c_macro_;
    // enable_traps := ( $slice ctrl_word 12 12 ) $buffering 1
    fpunit_exec_exec__decode_thread_control_word_assign_stmt_7208_c_macro_;
    // single_step_mode := ( $slice ctrl_word 11 11 ) $buffering 1
    fpunit_exec_exec__decode_thread_control_word_assign_stmt_7212_c_macro_;
    // ignore_break_points := ( $slice ctrl_word 10 10 ) $buffering 1
    fpunit_exec_exec__decode_thread_control_word_assign_stmt_7216_c_macro_;
    // S := ( $slice ctrl_word 9 9 ) $buffering 1
    fpunit_exec_exec__decode_thread_control_word_assign_stmt_7220_c_macro_;
    // imm_bit := ( $slice ctrl_word 8 8 ) $buffering 1
    fpunit_exec_exec__decode_thread_control_word_assign_stmt_7224_c_macro_;
    // is_write_psr := ( $slice ctrl_word 7 7 ) $buffering 1
    fpunit_exec_exec__decode_thread_control_word_assign_stmt_7228_c_macro_;
    // is_mmu_ctrl_write := ( $slice ctrl_word 6 6 ) $buffering 1
    fpunit_exec_exec__decode_thread_control_word_assign_stmt_7232_c_macro_;
    // is_flush := ( $slice ctrl_word 5 5 ) $buffering 1
    fpunit_exec_exec__decode_thread_control_word_assign_stmt_7236_c_macro_;
    // is_cti := ( $slice ctrl_word 4 4 ) $buffering 1
    fpunit_exec_exec__decode_thread_control_word_assign_stmt_7240_c_macro_;
    // mis_predict := ( $slice ctrl_word 3 3 ) $buffering 1
    fpunit_exec_exec__decode_thread_control_word_assign_stmt_7244_c_macro_;
    // trap_bit := ( $slice ctrl_word 2 2 ) $buffering 1
    fpunit_exec_exec__decode_thread_control_word_assign_stmt_7248_c_macro_;
    // stream_head := ( $slice ctrl_word 1 1 ) $buffering 1
    fpunit_exec_exec__decode_thread_control_word_assign_stmt_7252_c_macro_;
    // thread_head := ( $slice ctrl_word 0 0 ) $buffering 1
    fpunit_exec_exec__decode_thread_control_word_assign_stmt_7256_c_macro_;
    fpunit_exec_exec__decode_thread_control_word_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__decode_thread_control_word_series_block_stmt_7170_c_mutex_);
}
void
_fpunit_exec_exec_delay_32_2_(bit_vector * __pX, bit_vector * __pY)
{
    MUTEX_DECL
	(fpunit_exec_exec__delay_32_2_series_block_stmt_7258_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__delay_32_2_series_block_stmt_7258_c_mutex_);
    fpunit_exec_exec__delay_32_2_inner_inarg_prep_macro__;
    // Y := X $buffering 2// bits of buffering = 64. 
    fpunit_exec_exec__delay_32_2_assign_stmt_7263_c_macro_;
    fpunit_exec_exec__delay_32_2_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__delay_32_2_series_block_stmt_7258_c_mutex_);
}
void
fpunit_exec_exec_delay_32_2(uint32_t X, uint32_t * Y)
{
    fpunit_exec_exec__delay_32_2_outer_arg_decl_macro__;
    _fpunit_exec_exec_delay_32_2_(&__X, &__Y);
    fpunit_exec_exec__delay_32_2_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_delay_64_3_(bit_vector * __pX, bit_vector * __pY)
{
    MUTEX_DECL
	(fpunit_exec_exec__delay_64_3_series_block_stmt_7265_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__delay_64_3_series_block_stmt_7265_c_mutex_);
    fpunit_exec_exec__delay_64_3_inner_inarg_prep_macro__;
    // Y := X $buffering 3// bits of buffering = 192. 
    fpunit_exec_exec__delay_64_3_assign_stmt_7270_c_macro_;
    fpunit_exec_exec__delay_64_3_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__delay_64_3_series_block_stmt_7265_c_mutex_);
}
void
fpunit_exec_exec_delay_64_3(uint64_t X, uint64_t * Y)
{
    fpunit_exec_exec__delay_64_3_outer_arg_decl_macro__;
    _fpunit_exec_exec_delay_64_3_(&__X, &__Y);
    fpunit_exec_exec__delay_64_3_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_denormalize_32_(bit_vector * __psign,
				  bit_vector * __pbiased_exp,
				  bit_vector * __pmantissa,
				  bit_vector * __presult)
{
    MUTEX_DECL
	(fpunit_exec_exec__denormalize_32_series_block_stmt_7332_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__denormalize_32_series_block_stmt_7332_c_mutex_);
    fpunit_exec_exec__denormalize_32_inner_inarg_prep_macro__;
    // $volatile s_biased_exp := ($bitcast ($int<13>) biased_exp )
    // $buffering 1
    fpunit_exec_exec__denormalize_32_assign_stmt_7340_c_macro_;
    // $volatile needs_denormalization := (s_biased_exp < 1 ) $buffering 1
    fpunit_exec_exec__denormalize_32_assign_stmt_7345_c_macro_;
    // $volatile denorm_shift_amount := (1 - s_biased_exp) $buffering 1
    fpunit_exec_exec__denormalize_32_assign_stmt_7350_c_macro_;
    // $volatile is_denormalizable := (needs_denormalization &
    // (denorm_shift_amount <= 24 )) $buffering 1
    fpunit_exec_exec__denormalize_32_assign_stmt_7357_c_macro_;
    // $volatile p := ((ONE_1 && mantissa) && ZERO_8) $buffering 1
    fpunit_exec_exec__denormalize_32_assign_stmt_7364_c_macro_;
    // $volatile q := ($bitcast ($uint<5>) denorm_shift_amount )
    // $buffering 1
    fpunit_exec_exec__denormalize_32_assign_stmt_7368_c_macro_;
    // $volatile $call i32_srl (p q ) (shifted ) 
    fpunit_exec_exec__denormalize_32_call_stmt_7372_c_macro_;
    // mantissa_denorm_final := ( $slice shifted 30 8 ) $buffering 1
    fpunit_exec_exec__denormalize_32_assign_stmt_7376_c_macro_;
    // $volatile result_denormal := ((sign && ZERO_8) &&
    // mantissa_denorm_final) $buffering 1
    fpunit_exec_exec__denormalize_32_assign_stmt_7383_c_macro_;
    // $volatile result_zero := (sign && ZERO_31) $buffering 1
    fpunit_exec_exec__denormalize_32_assign_stmt_7388_c_macro_;
    // $volatile result_normal := ((sign && ( $slice biased_exp 7 0 ) ) && 
    // mantissa) $buffering 1
    fpunit_exec_exec__denormalize_32_assign_stmt_7396_c_macro_;
    // result := ( $mux needs_denormalization ( $mux is_denormalizable
    // result_denormal result_zero ) result_normal ) $buffering 1
    fpunit_exec_exec__denormalize_32_assign_stmt_7405_c_macro_;
    fpunit_exec_exec__denormalize_32_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__denormalize_32_series_block_stmt_7332_c_mutex_);
}
void
_fpunit_exec_exec_denormalize_64_(bit_vector * __psign,
				  bit_vector * __pbiased_exp,
				  bit_vector * __pmantissa,
				  bit_vector * __presult)
{
    MUTEX_DECL
	(fpunit_exec_exec__denormalize_64_series_block_stmt_7478_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__denormalize_64_series_block_stmt_7478_c_mutex_);
    fpunit_exec_exec__denormalize_64_inner_inarg_prep_macro__;
    // $volatile s_biased_exp := ($bitcast ($int<13>) biased_exp )
    // $buffering 1
    fpunit_exec_exec__denormalize_64_assign_stmt_7486_c_macro_;
    // $volatile needs_denormalization := (s_biased_exp < 1 ) $buffering 1
    fpunit_exec_exec__denormalize_64_assign_stmt_7491_c_macro_;
    // $volatile denorm_shift_amount := (1 - s_biased_exp) $buffering 1
    fpunit_exec_exec__denormalize_64_assign_stmt_7496_c_macro_;
    // $volatile is_denormalizable := (needs_denormalization &
    // (denorm_shift_amount <= 52 )) $buffering 1
    fpunit_exec_exec__denormalize_64_assign_stmt_7503_c_macro_;
    // $volatile p := ((ONE_1 && mantissa) && ZERO_11) $buffering 1
    fpunit_exec_exec__denormalize_64_assign_stmt_7510_c_macro_;
    // $volatile q := ($bitcast ($uint<6>) denorm_shift_amount )
    // $buffering 1
    fpunit_exec_exec__denormalize_64_assign_stmt_7514_c_macro_;
    // $volatile $call i64_srl (p q ) (shifted ) 
    fpunit_exec_exec__denormalize_64_call_stmt_7518_c_macro_;
    // mantissa_denorm_final := ( $slice shifted 62 11 ) $buffering 1
    fpunit_exec_exec__denormalize_64_assign_stmt_7522_c_macro_;
    // $volatile result_denormal := ((sign && ZERO_11) &&
    // mantissa_denorm_final) $buffering 1
    fpunit_exec_exec__denormalize_64_assign_stmt_7529_c_macro_;
    // $volatile result_zero := (sign && ZERO_63) $buffering 1
    fpunit_exec_exec__denormalize_64_assign_stmt_7534_c_macro_;
    // $volatile result_normal := ((sign && ( $slice biased_exp 10 0 ) )
    // && mantissa) $buffering 1
    fpunit_exec_exec__denormalize_64_assign_stmt_7542_c_macro_;
    // result := ( $mux needs_denormalization ( $mux is_denormalizable
    // result_denormal result_zero ) result_normal ) $buffering 1
    fpunit_exec_exec__denormalize_64_assign_stmt_7551_c_macro_;
    fpunit_exec_exec__denormalize_64_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__denormalize_64_series_block_stmt_7478_c_mutex_);
}
void
_fpunit_exec_exec_denormalize_fp_32_(bit_vector * __pextn_result,
				     bit_vector * __pf32_result)
{
    MUTEX_DECL
	(fpunit_exec_exec__denormalize_fp_32_series_block_stmt_7655_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__denormalize_fp_32_series_block_stmt_7655_c_mutex_);
    fpunit_exec_exec__denormalize_fp_32_inner_inarg_prep_macro__;
    // $volatile EXTENDED_RESULT := extn_result $buffering 1
    fpunit_exec_exec__denormalize_fp_32_assign_stmt_7660_c_macro_;
    // $volatile sticky := ( $slice EXTENDED_RESULT 80 80 ) $buffering 1
    fpunit_exec_exec__denormalize_fp_32_assign_stmt_7664_c_macro_;
    // $volatile apply_sticky_correction := ( $slice EXTENDED_RESULT 79 79 
    // ) $buffering 1
    fpunit_exec_exec__denormalize_fp_32_assign_stmt_7668_c_macro_;
    // $volatile sign := ( $slice EXTENDED_RESULT 78 78 ) $buffering 1
    fpunit_exec_exec__denormalize_fp_32_assign_stmt_7672_c_macro_;
    // $volatile u_exp_13 := ( $slice EXTENDED_RESULT 74 62 ) $buffering 1
    fpunit_exec_exec__denormalize_fp_32_assign_stmt_7676_c_macro_;
    // $volatile mantissa_62 := ( $slice EXTENDED_RESULT 61 0 ) $buffering 
    // 1
    fpunit_exec_exec__denormalize_fp_32_assign_stmt_7680_c_macro_;
    // $volatile $call round_32_extn (sticky apply_sticky_correction
    // u_exp_13 mantissa_62 ) (sp_exp_13_post_round
    // sp_mantissa_23_post_round ) 
    fpunit_exec_exec__denormalize_fp_32_call_stmt_7687_c_macro_;
    // $volatile $call denormalize_32 (sign sp_exp_13_post_round
    // sp_mantissa_23_post_round ) (f32_normalized ) 
    fpunit_exec_exec__denormalize_fp_32_call_stmt_7692_c_macro_;
    // f32_result := f32_normalized $buffering 1// bits of buffering = 32. 
    // 
    fpunit_exec_exec__denormalize_fp_32_assign_stmt_7695_c_macro_;
    fpunit_exec_exec__denormalize_fp_32_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__denormalize_fp_32_series_block_stmt_7655_c_mutex_);
}
void
_fpunit_exec_exec_denormalize_fp_64_(bit_vector * __pextn_result,
				     bit_vector * __pf64_result)
{
    MUTEX_DECL
	(fpunit_exec_exec__denormalize_fp_64_series_block_stmt_7790_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__denormalize_fp_64_series_block_stmt_7790_c_mutex_);
    fpunit_exec_exec__denormalize_fp_64_inner_inarg_prep_macro__;
    // $volatile EXTENDED_RESULT := extn_result $buffering 1
    fpunit_exec_exec__denormalize_fp_64_assign_stmt_7795_c_macro_;
    // $volatile sticky := ( $slice EXTENDED_RESULT 80 80 ) $buffering 1
    fpunit_exec_exec__denormalize_fp_64_assign_stmt_7799_c_macro_;
    // $volatile apply_sticky_correction := ( $slice EXTENDED_RESULT 79 79 
    // ) $buffering 1
    fpunit_exec_exec__denormalize_fp_64_assign_stmt_7803_c_macro_;
    // $volatile sign := ( $slice EXTENDED_RESULT 78 78 ) $buffering 1
    fpunit_exec_exec__denormalize_fp_64_assign_stmt_7807_c_macro_;
    // $volatile u_exp_13 := ( $slice EXTENDED_RESULT 74 62 ) $buffering 1
    fpunit_exec_exec__denormalize_fp_64_assign_stmt_7811_c_macro_;
    // $volatile mantissa_62 := ( $slice EXTENDED_RESULT 61 0 ) $buffering 
    // 1
    fpunit_exec_exec__denormalize_fp_64_assign_stmt_7815_c_macro_;
    // $volatile $call round_64_extn (sticky apply_sticky_correction
    // u_exp_13 mantissa_62 ) (dp_exp_13_post_round
    // dp_mantissa_52_post_round ) 
    fpunit_exec_exec__denormalize_fp_64_call_stmt_7822_c_macro_;
    // $volatile $call denormalize_64 (sign dp_exp_13_post_round
    // dp_mantissa_52_post_round ) (f64_normalized ) 
    fpunit_exec_exec__denormalize_fp_64_call_stmt_7827_c_macro_;
    // f64_result := f64_normalized $buffering 1// bits of buffering = 64. 
    // 
    fpunit_exec_exec__denormalize_fp_64_assign_stmt_7830_c_macro_;
    fpunit_exec_exec__denormalize_fp_64_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__denormalize_fp_64_series_block_stmt_7790_c_mutex_);
}
void
_fpunit_exec_exec_early_decode_for_fetch_(bit_vector * __pinstr,
					  bit_vector * __pis_cti,
					  bit_vector * __pis_flush,
					  bit_vector * __pis_write_psr,
					  bit_vector *
					  __pis_write_to_mmu_ctrl_register,
					  bit_vector * __pwill_trap,
					  bit_vector * __pimm_bit,
					  bit_vector * __pannul_bit)
{
    MUTEX_DECL
	(fpunit_exec_exec__early_decode_for_fetch_series_block_stmt_7832_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__early_decode_for_fetch_series_block_stmt_7832_c_mutex_);
    fpunit_exec_exec__early_decode_for_fetch_inner_inarg_prep_macro__;
    // op := ( $slice instr 31 30 ) $buffering 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_7844_c_macro_;
    // op_eq_2 := (op == 2 ) $buffering 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_7849_c_macro_;
    // op_eq_3 := (op == 3 ) $buffering 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_7854_c_macro_;
    // op2 := ( $slice instr 24 22 ) $buffering 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_7858_c_macro_;
    // op3 := ( $slice instr 24 19 ) $buffering 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_7862_c_macro_;
    // op3_col := ( $slice op3 5 4 ) $buffering 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_7866_c_macro_;
    // op3_row := ( $slice op3 3 0 ) $buffering 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_7870_c_macro_;
    // is_call := (op == 1 ) $buffering 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_7875_c_macro_;
    // is_branch := ((op == 0 ) & (((op2 == 2 ) | (op2 == 6 )) | (op2 == 7 
    // ))) $buffering 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_7892_c_macro_;
    // is_jmpl := (op_eq_2 & ((op3_row == 8 ) & (op3_col == 3 )))
    // $buffering 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_7903_c_macro_;
    // is_rett := (op_eq_2 & ((op3_row == 9 ) & (op3_col == 3 )))
    // $buffering 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_7914_c_macro_;
    // is_ticc := (op_eq_2 & ((op3_row == 10 ) & (op3_col == 3 )))
    // $buffering 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_7925_c_macro_;
    // cond := ( $slice instr 28 25 ) $buffering 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_7929_c_macro_;
    // annul_bit := (instr [] 29 ) $buffering 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_7934_c_macro_;
    // is_unimplemented := ((op == 0 ) & (op2 == 0 )) $buffering 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_7943_c_macro_;
    // will_trap := ((is_ticc & (cond == 8 )) | is_unimplemented)
    // $buffering 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_7952_c_macro_;
    // is_cti := ((is_call | is_branch) | (is_jmpl | is_rett)) $buffering
    // 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_7961_c_macro_;
    // is_flush_instr := ((op_eq_2 & (op3_col == 3 )) & (op3_row == 11 ))
    // $buffering 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_7972_c_macro_;
    // asi_bit := ((op_eq_3 & (op3_col == 1 )) & ((op3_row < 8 ) |
    // ((op3_row > 8 ) & (op3_row < 11 )))) $buffering 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_7991_c_macro_;
    // asi_id_8 := ( $slice instr 12 5 ) $buffering 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_7995_c_macro_;
    // $volatile $call decode_is_flush_asi (asi_id_8 ) (is_flush_asi ) 
    fpunit_exec_exec__early_decode_for_fetch_call_stmt_7998_c_macro_;
    // is_flush := (is_flush_instr | (asi_bit & is_flush_asi)) $buffering
    // 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_8005_c_macro_;
    // is_write_psr := (op_eq_2 & ((op3_col == 3 ) & (op3_row == 1 )))
    // $buffering 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_8016_c_macro_;
    // imm_bit := (instr [] 13 ) $buffering 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_8021_c_macro_;
    // is_load_instr := (op_eq_3 & (((((op3_row < 2 ) | ((op3_row == 2 ) & 
    // (op3_col < 2 ))) | (op3_row == 3 )) | ((op3_row == 9 ) & (op3_col < 
    // 2 ))) | ((op3_row == 10 ) & (op3_col < 2 )))) $buffering 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_8056_c_macro_;
    // is_store_instr := (op_eq_3 & ((op3_row > 3 ) & (op3_row < 8 )))
    // $buffering 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_8067_c_macro_;
    // is_write_to_mmu_ctrl_register := (((is_load_instr | is_store_instr) 
    // & asi_bit) & ((asi_id_8 == ASI_MMU_FLUSH_PROBE) | (asi_id_8 ==
    // ASI_MMU_REGISTER))) $buffering 1
    fpunit_exec_exec__early_decode_for_fetch_assign_stmt_8082_c_macro_;
    fpunit_exec_exec__early_decode_for_fetch_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__early_decode_for_fetch_series_block_stmt_7832_c_mutex_);
}
void
_fpunit_exec_exec_exec_bicc_generic_(bit_vector * __pbr_annul_flag,
				     bit_vector * __pbr_cond,
				     bit_vector * __pccodes,
				     bit_vector * __pbr_taken,
				     bit_vector * __pannul_next)
{
    MUTEX_DECL
	(fpunit_exec_exec__exec_bicc_generic_series_block_stmt_8084_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__exec_bicc_generic_series_block_stmt_8084_c_mutex_);
    fpunit_exec_exec__exec_bicc_generic_inner_inarg_prep_macro__;
    // $volatile N := (ccodes [] 3 ) $buffering 1
    fpunit_exec_exec__exec_bicc_generic_assign_stmt_8094_c_macro_;
    // $volatile Z := (ccodes [] 2 ) $buffering 1
    fpunit_exec_exec__exec_bicc_generic_assign_stmt_8099_c_macro_;
    // $volatile V := (ccodes [] 1 ) $buffering 1
    fpunit_exec_exec__exec_bicc_generic_assign_stmt_8104_c_macro_;
    // $volatile C := (ccodes [] 0 ) $buffering 1
    fpunit_exec_exec__exec_bicc_generic_assign_stmt_8109_c_macro_;
    // br_taken := ((((( $mux (br_cond == 8 ) ONE_1 _b0 ) | ( $mux
    // (br_cond == 0 ) ZERO_1 _b0 ) ) | (( $mux (br_cond == 9 ) ( ~ Z )
    // _b0 ) | ( $mux (br_cond == 1 ) Z _b0 ) )) | ((( $mux (br_cond == 10 
    // ) ( ~ (Z | (N ^ V)) ) _b0 ) | ( $mux (br_cond == 2 ) (Z | (N ^ V))
    // _b0 ) ) | (( $mux (br_cond == 11 ) ( ~ (N ^ V) ) _b0 ) | ( $mux
    // (br_cond == 3 ) (N ^ V) _b0 ) ))) | (((( $mux (br_cond == 12 ) ( ~
    // (C | Z) ) _b0 ) | ( $mux (br_cond == 4 ) (C | Z) _b0 ) ) | (( $mux
    // (br_cond == 13 ) ( ~ C ) _b0 ) | ( $mux (br_cond == 5 ) C _b0 ) ))
    // | ((( $mux (br_cond == 14 ) ( ~ N ) _b0 ) | ( $mux (br_cond == 6 )
    // N _b0 ) ) | (( $mux (br_cond == 15 ) ( ~ V ) _b0 ) | ( $mux
    // (br_cond == 7 ) V _b0 ) )))) $buffering 1
    fpunit_exec_exec__exec_bicc_generic_assign_stmt_8245_c_macro_;
    // $volatile branch_always := (br_cond == 8 ) $buffering 1
    fpunit_exec_exec__exec_bicc_generic_assign_stmt_8250_c_macro_;
    // annul_next := ( $mux br_taken (branch_always & br_annul_flag)
    // br_annul_flag ) $buffering 1
    fpunit_exec_exec__exec_bicc_generic_assign_stmt_8258_c_macro_;
    fpunit_exec_exec__exec_bicc_generic_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__exec_bicc_generic_series_block_stmt_8084_c_mutex_);
}
void
_fpunit_exec_exec_exec_daemon_()
{
    MUTEX_DECL
	(fpunit_exec_exec__exec_daemon_series_block_stmt_16372_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__exec_daemon_series_block_stmt_16372_c_mutex_);
    fpunit_exec_exec__exec_daemon_inner_inarg_prep_macro__;
    fpunit_exec_exec__exec_daemon_branch_block_stmt_16373_c_export_decl_macro_;
    {
	{
	    // do-while: file ./.Aa//linked.opt.aa, line 3687
	    __declare_static_bit_vector(konst_18050, 1);
	    bit_vector_clear(&konst_18050);
	    konst_18050.val.byte_array[0] = 1;
	    uint8_t         do_while_entry_flag;
	    do_while_entry_flag = 1;
	    uint8_t         do_while_loopback_flag;
	    do_while_loopback_flag = 0;
	    while (1) {
		// merge file ./.Aa//linked.opt.aa, line 3689
		fpunit_exec_exec__exec_daemon_merge_stmt_16375_c_preamble_macro_;
		fpunit_exec_exec__exec_daemon_merge_stmt_16375_c_postamble_macro_;
		// decoded_info := teu_idispatch_to_fpunit_exec $buffering 
		// 1// bits of buffering = 79. 
		fpunit_exec_exec__exec_daemon_assign_stmt_16378_c_macro_;
		// $volatile get_rfile_resp := (decoded_info [] 6 )
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16383_c_macro_;
		// $guard (get_rfile_resp) $report (fpunit_exec
		// get_rfile_resp decoded_info decoded_info )
		fpunit_exec_exec__exec_daemon_stmt_16386_c_macro_;
		// $guard (get_rfile_resp) ops :=
		// fpunit_register_file_read_access_response $buffering
		// 1// bits of buffering = 174. 
		fpunit_exec_exec__exec_daemon_assign_stmt_16390_c_macro_;
		// get_rfile_resp_16652_delayed_1_0 := get_rfile_resp
		// $buffering 1 $cut_through // bits of buffering = 1.
		// Orphaned statement with target
		// get_rfile_resp_16652_delayed_1_0 ?? 
		fpunit_exec_exec__exec_daemon_assign_stmt_16393_c_macro_;
		// get_rfile_resp_16658_delayed_1_0 := get_rfile_resp
		// $buffering 1 $cut_through // bits of buffering = 1. 
		fpunit_exec_exec__exec_daemon_assign_stmt_16396_c_macro_;
		// $volatile ops_valid :=
		// (get_rfile_resp_16658_delayed_1_0 & (ops [] 172 ))
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16403_c_macro_;
		// $guard (ops_valid)
		// noblock_fpunit_exec_to_regfile_credit_return := ONE_1
		// $buffering 1// bits of buffering = 1. 
		fpunit_exec_exec__exec_daemon_assign_stmt_16407_c_macro_;
		// decoded_info_d := decoded_info $buffering 1// bits of
		// buffering = 79. 
		fpunit_exec_exec__exec_daemon_assign_stmt_16410_c_macro_;
		// $volatile $call pre_op_preparation (decoded_info_d ops
		// ) (thread_head stream_head thread_id stream_id slot_id
		// do_not_bypass write_reg_id fbcond annul_flag
		// decode_trap unimpl_instr invalid_reg seq_error
		// ieee_754_exception cexc fp_dti issue_fmovs issue_fnegs
		// issue_fabss issue_fbfcc issue_fadds issue_fsubs
		// issue_fmuls issue_fdivs issue_fsqrts issue_fcmps
		// issue_fcmpes issue_fitos issue_fstoi issue_fstod
		// issue_faddd issue_fsubd issue_fsmuld issue_fmuld
		// issue_fdivd issue_fsqrtd issue_fcmpd issue_fcmped
		// issue_fitod issue_fdtoi issue_fdtos issue_vfadd
		// issue_vfsub issue_vfmul vf_data_type issue_vfhtoi16
		// issue_vfi16toh issue_faddreduce16 issue_fstoh
		// issue_fhtos is_store ldfsr skip_fp r1_val_h r1_val_l
		// r2_val_h r2_val_l fsr_val f1_s f2_s f1_d f2_d st_val_h
		// st_val_l uses_fu1 fu1_to_fu2 fu1_to_sc fu1_trap_to_ls
		// fu1_to_iu2 fu1_to_cu2 f1_s_class f2_s_class f1_d_class
		// f2_d_class ) 
		fpunit_exec_exec__exec_daemon_call_stmt_16487_c_macro_;
		// $report (fpunit_exec pre_op_preparation thread_id
		// thread_id stream_id stream_id slot_id slot_id
		// write_reg_id write_reg_id fbcond fbcond annul_flag
		// annul_flag decode_trap decode_trap unimpl_instr
		// unimpl_instr invalid_reg invalid_reg seq_error
		// seq_error ieee_754_exception ieee_754_exception cexc
		// cexc fp_dti fp_dti issue_fmovs issue_fmovs issue_fnegs
		// issue_fnegs issue_fabss issue_fabss issue_fbfcc
		// issue_fbfcc issue_fadds issue_fadds issue_fsubs
		// issue_fsubs issue_fmuls issue_fmuls issue_fdivs
		// issue_fdivs issue_fsqrts issue_fsqrts issue_fcmps
		// issue_fcmps issue_fcmpes issue_fcmpes issue_fitos
		// issue_fitos issue_fstoi issue_fstoi issue_fstod
		// issue_fstod issue_faddd issue_faddd issue_fsubd
		// issue_fsubd issue_fsmuld issue_fsmuld issue_fmuld
		// issue_fmuld issue_fdivd issue_fdivd issue_fsqrtd
		// issue_fsqrtd issue_fcmpd issue_fcmpd issue_fcmped
		// issue_fcmped issue_fitod issue_fitod issue_fdtoi
		// issue_fdtoi issue_fdtos issue_fdtos issue_vfadd
		// issue_vfadd issue_vfsub issue_vfsub issue_vfmul
		// issue_vfmul vf_data_type vf_data_type issue_vfhtoi16
		// issue_vfhtoi16 issue_vfi16toh issue_vfi16toh
		// issue_faddreduce16 issue_faddreduce16 issue_fstoh
		// issue_fstoh issue_fhtos issue_fhtos is_store is_store
		// ldfsr ldfsr skip_fp skip_fp r1_val_h r1_val_h r1_val_l
		// r1_val_l r2_val_h r2_val_h r2_val_l r2_val_l fsr_val
		// fsr_val f1_s f1_s f2_s f2_s f1_d f1_d f2_d f2_d
		// st_val_h st_val_h st_val_l st_val_l uses_fu1 uses_fu1
		// fu1_to_fu2 fu1_to_fu2 fu1_to_sc fu1_to_sc f1_s_class
		// f1_s_class f2_s_class f2_s_class f1_d_class f1_d_class
		// f2_d_class f2_d_class )
		fpunit_exec_exec__exec_daemon_stmt_16556_c_macro_;
		// $volatile simd_alu := ((issue_vfadd | issue_vfsub) |
		// issue_vfmul) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16563_c_macro_;
		// $volatile simd_32_flag := (simd_alu & (vf_data_type ==
		// 4 )) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16570_c_macro_;
		// $volatile issue_simd_32 := simd_32_flag $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16573_c_macro_;
		// $volatile simd_16_flag := (simd_alu & (vf_data_type ==
		// 2 )) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16580_c_macro_;
		// $volatile uf1_s := ($bitcast ($uint<32>) f1_s )
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16584_c_macro_;
		// $volatile uf1_d := ($bitcast ($uint<64>) f1_d )
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16588_c_macro_;
		// $volatile uf2_d := ($bitcast ($uint<64>) f2_d )
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16592_c_macro_;
		// $guard (issue_vfhtoi16) $call exec_vfhtoi16 (uf1_d )
		// (vfhtoi16_result ) 
		fpunit_exec_exec__exec_daemon_call_stmt_16596_c_macro_;
		// $guard (issue_vfi16toh) $call exec_vfi16toh (uf1_d )
		// (vfi16toh_result ) 
		fpunit_exec_exec__exec_daemon_call_stmt_16600_c_macro_;
		// $volatile issue_vfconv := (issue_vfhtoi16 |
		// issue_vfi16toh) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16605_c_macro_;
		// issue_vfhtoi16_16871_delayed_2_0 := issue_vfhtoi16
		// $buffering 2 $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_16608_c_macro_;
		// $volatile vfconv_result_d := ( $mux
		// issue_vfhtoi16_16871_delayed_2_0 vfhtoi16_result
		// vfi16toh_result ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16614_c_macro_;
		// $volatile $call exec_fhtos (( $slice uf1_s 15 0 ) )
		// (fhtos_result ) 
		fpunit_exec_exec__exec_daemon_call_stmt_16618_c_macro_;
		// $volatile $call exec_fstoh (uf1_s ) (fstoh_result ) 
		fpunit_exec_exec__exec_daemon_call_stmt_16621_c_macro_;
		// $volatile issue_fhconv := (issue_fstoh | issue_fhtos)
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16626_c_macro_;
		// $volatile fhconv_result_s := ( $mux issue_fstoh
		// (ZERO_16 && fstoh_result) fhtos_result ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16634_c_macro_;
		// $volatile negate_second_operand := ((issue_fsubs |
		// issue_fsubd) | issue_vfsub) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16641_c_macro_;
		// $volatile movs_result := r2_val_l $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16644_c_macro_;
		// $volatile negs_result := ((ONE_32 << 31 ) ^ r2_val_l)
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16651_c_macro_;
		// $volatile fnegs_result := ($bitcast ($float<8,23>)
		// negs_result ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16655_c_macro_;
		// $volatile abs_result := (( ~ (ONE_32 << 31 ) ) &
		// r2_val_l) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16663_c_macro_;
		// $volatile negd_result := ((ONE_64 << 63 ) ^ (r2_val_h
		// && r2_val_l)) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16672_c_macro_;
		// $volatile fnegd_result := ($bitcast ($float<11,52>)
		// negd_result ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16676_c_macro_;
		// $volatile triv_result_s := ((( $mux issue_fmovs
		// movs_result _b0 ) | ( $mux issue_fnegs negs_result _b0
		// ) ) | ( $mux issue_fabss abs_result _b0 ) ) $buffering
		// 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16692_c_macro_;
		// $volatile triv_flag_s := ((issue_fmovs | issue_fnegs) | 
		// issue_fabss) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16699_c_macro_;
		// $volatile use_fadders := ((issue_fadds | issue_fsubs) | 
		// (simd_32_flag & (issue_vfadd | issue_vfsub)))
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16710_c_macro_;
		// $volatile adder_op2_s := ( $mux issue_fsubs
		// fnegs_result f2_s ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16716_c_macro_;
		// $volatile uadder_op2_s := ($bitcast ($uint<32>)
		// adder_op2_s ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16720_c_macro_;
		// $volatile $call SingleToDouble (f2_s ) (f2_s_d ) 
		fpunit_exec_exec__exec_daemon_call_stmt_16723_c_macro_;
		// $volatile fstod_result := f2_s_d $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16726_c_macro_;
		// $volatile use_fadderd := (issue_faddd | issue_fsubd)
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16731_c_macro_;
		// $volatile adder_op2_d := ( $mux issue_faddd f2_d
		// fnegd_result ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16737_c_macro_;
		// $volatile uadder_op2_d := ($bitcast ($uint<64>)
		// adder_op2_d ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16741_c_macro_;
		// $volatile use_dp_fadder := (use_fadders | use_fadderd)
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16746_c_macro_;
		// $volatile $call negate_classification (f2_s_class )
		// (neg_f2_s_class ) 
		fpunit_exec_exec__exec_daemon_call_stmt_16749_c_macro_;
		// $volatile $call negate_classification (f2_d_class )
		// (neg_f2_d_class ) 
		fpunit_exec_exec__exec_daemon_call_stmt_16752_c_macro_;
		// $volatile adder_op2_s_class := ( $mux
		// negate_second_operand neg_f2_s_class f2_s_class )
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16758_c_macro_;
		// $volatile adder_op2_d_class := ( $mux
		// negate_second_operand neg_f2_d_class f2_d_class )
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16764_c_macro_;
		// $volatile single_precision_inputs_to_adder :=
		// ((issue_fadds | issue_fsubs) | (issue_vfadd |
		// issue_vfsub)) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16773_c_macro_;
		// $volatile double_precision_inputs_to_adder :=
		// (issue_faddd | issue_fsubd) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16778_c_macro_;
		// $guard (use_dp_fadder) $call fpadd64_op
		// (single_precision_inputs_to_adder
		// double_precision_inputs_to_adder uf1_s f1_s_class
		// uadder_op2_s adder_op2_s_class uf1_d f1_d_class
		// uadder_op2_d adder_op2_d_class ) (denormalize_flag_add
		// extn_result_add ) 
		fpunit_exec_exec__exec_daemon_call_stmt_16792_c_macro_;
		// $volatile use_faddervs := (simd_32_flag & (issue_vfadd
		// | issue_vfsub)) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16799_c_macro_;
		// $volatile use_fmulvs := (simd_32_flag & issue_vfmul)
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16804_c_macro_;
		// $volatile vs_op_1 := ( $slice uf1_d 63 32 ) $buffering
		// 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16808_c_macro_;
		// $volatile vs_fop_1 := ($bitcast ($float<8,23>) vs_op_1
		// ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16812_c_macro_;
		// $volatile $call classFp32IntoClassWord (vs_fop_1 )
		// (vs_fop_1_class ) 
		fpunit_exec_exec__exec_daemon_call_stmt_16815_c_macro_;
		// $volatile vs_op_2 := ( $slice uf2_d 63 32 ) $buffering
		// 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16819_c_macro_;
		// $volatile vs_fop_2 := ($bitcast ($float<8,23>) vs_op_2
		// ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16823_c_macro_;
		// $volatile $call classFp32IntoClassWord (vs_fop_2 )
		// (vs_fop_2_class ) 
		fpunit_exec_exec__exec_daemon_call_stmt_16826_c_macro_;
		// $volatile $call negate_classification (vs_fop_2_class ) 
		// (neg_vs_fop_2_class ) 
		fpunit_exec_exec__exec_daemon_call_stmt_16829_c_macro_;
		// $volatile vs_addsub_fop_2_class := ( $mux
		// negate_second_operand neg_vs_fop_2_class vs_fop_2_class 
		// ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16835_c_macro_;
		// $guard (use_faddervs) $call fpadd32_op (vs_op_1
		// vs_fop_1_class vs_op_2 vs_addsub_fop_2_class )
		// (vs_addsub_needs_norm vs_addsub_extension_result ) 
		fpunit_exec_exec__exec_daemon_call_stmt_16843_c_macro_;
		// $guard (use_fmulvs) $call fpmul32_op (vs_op_1
		// vs_fop_1_class vs_op_2 vs_fop_2_class )
		// (vs_mul_needs_norm vs_mul_extension_result ) 
		fpunit_exec_exec__exec_daemon_call_stmt_16851_c_macro_;
		// use_faddervs_17114_delayed_1_0 := use_faddervs
		// $buffering 1 $cut_through // bits of buffering = 1. 
		fpunit_exec_exec__exec_daemon_assign_stmt_16854_c_macro_;
		// $volatile condition_denormalize_flag_vs_addsub :=
		// (use_faddervs_17114_delayed_1_0 & vs_addsub_needs_norm) 
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16859_c_macro_;
		// use_fmulvs_17119_delayed_2_0 := use_fmulvs $buffering 2 
		// $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_16862_c_macro_;
		// $volatile condition_denormalize_flag_vs_mul :=
		// (use_fmulvs_17119_delayed_2_0 & vs_mul_needs_norm)
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16867_c_macro_;
		// condition_denormalize_flag_vs_addsub_17124_delayed_1_0
		// := condition_denormalize_flag_vs_addsub $buffering 1
		// $cut_through // bits of buffering = 1. 
		fpunit_exec_exec__exec_daemon_assign_stmt_16870_c_macro_;
		// $volatile denormalize_vs :=
		// (condition_denormalize_flag_vs_addsub_17124_delayed_1_0 
		// | condition_denormalize_flag_vs_mul) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16875_c_macro_;
		// use_faddervs_17129_delayed_1_0 := use_faddervs
		// $buffering 1 $cut_through // bits of buffering = 1. 
		fpunit_exec_exec__exec_daemon_assign_stmt_16878_c_macro_;
		// MUX_17132_17132_delayed_1_0 := ( $mux
		// use_faddervs_17129_delayed_1_0
		// vs_addsub_extension_result _b0 ) $buffering 1
		// $cut_through // bits of buffering = 81. 
		fpunit_exec_exec__exec_daemon_assign_stmt_16884_c_macro_;
		// use_fmulvs_17133_delayed_2_0 := use_fmulvs $buffering 2 
		// $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_16887_c_macro_;
		// $volatile extn_result_to_vs_round_and_normalize :=
		// (MUX_17132_17132_delayed_1_0 | ( $mux
		// use_fmulvs_17133_delayed_2_0 vs_mul_extension_result
		// _b0 ) ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16895_c_macro_;
		// $volatile $call round_fp_32
		// (extn_result_to_vs_round_and_normalize )
		// (vs_round_result ) 
		fpunit_exec_exec__exec_daemon_call_stmt_16898_c_macro_;
		// $guard (denormalize_vs) $call denormalize_fp_32
		// (extn_result_to_vs_round_and_normalize )
		// (denorm_result_vs_slow ) 
		fpunit_exec_exec__exec_daemon_call_stmt_16902_c_macro_;
		// $volatile simd32_result_fast_h := vs_round_result
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16905_c_macro_;
		// $volatile simd32_result_slow_h := denorm_result_vs_slow 
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16908_c_macro_;
		// $volatile use_dp_fmul := ((issue_fmuld | issue_fmuls) | 
		// (issue_fsmuld | (simd_32_flag & issue_vfmul)))
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16919_c_macro_;
		// $volatile double_mul := (issue_fmuld | issue_fsmuld)
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16924_c_macro_;
		// $volatile mul_uf1_s := ($bitcast ($uint<32>) f1_s )
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16928_c_macro_;
		// $volatile mul_uf2_s := ($bitcast ($uint<32>) f2_s )
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16932_c_macro_;
		// $volatile mul_uf1_d := ($bitcast ($uint<64>) f1_d )
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16936_c_macro_;
		// $volatile mul_uf2_d := ($bitcast ($uint<64>) f2_d )
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16940_c_macro_;
		// $volatile single_precision_inputs_to_mul :=
		// ((issue_fmuls | issue_fsmuld) | issue_vfmul) $buffering 
		// 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16947_c_macro_;
		// $guard (use_dp_fmul) $call fpmul64_op
		// (single_precision_inputs_to_mul double_mul mul_uf1_s
		// f1_s_class mul_uf2_s f2_s_class mul_uf1_d f1_d_class
		// mul_uf2_d f2_d_class ) (denormalize_flag_mul
		// extn_result_mul ) 
		fpunit_exec_exec__exec_daemon_call_stmt_16961_c_macro_;
		// $volatile fitod_in := ( $mux ops_valid r2_val_l 0 )
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16967_c_macro_;
		// $volatile $call fitod64 (fitod_in ) (fitod_result ) 
		fpunit_exec_exec__exec_daemon_call_stmt_16970_c_macro_;
		// $volatile convert_to_single := (issue_fitos |
		// issue_fdtos) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16975_c_macro_;
		// $volatile to_single_in := ( $mux issue_fdtos f2_d
		// fitod_result ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16981_c_macro_;
		// $guard (convert_to_single) $call DoubleToSingle
		// (to_single_in ) (denorm_double_to_single
		// extn_result_double_to_single ) 
		fpunit_exec_exec__exec_daemon_call_stmt_16986_c_macro_;
		// use_dp_fadder_17236_delayed_2_0 := use_dp_fadder
		// $buffering 2 $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_16989_c_macro_;
		// $volatile condition_denormalize_flag_add :=
		// (use_dp_fadder_17236_delayed_2_0 &
		// denormalize_flag_add) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_16994_c_macro_;
		// use_dp_fmul_17241_delayed_2_0 := use_dp_fmul $buffering 
		// 2 $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_16997_c_macro_;
		// $volatile condition_denormalize_flag_mul :=
		// (use_dp_fmul_17241_delayed_2_0 & denormalize_flag_mul)
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17002_c_macro_;
		// convert_to_single_17246_delayed_2_0 :=
		// convert_to_single $buffering 2 $cut_through // bits of
		// buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17005_c_macro_;
		// $volatile condition_denormalize_flag_double_to_single
		// := (convert_to_single_17246_delayed_2_0 &
		// denorm_double_to_single) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17010_c_macro_;
		// $volatile denormalize_flag :=
		// ((condition_denormalize_flag_double_to_single |
		// condition_denormalize_flag_add) |
		// condition_denormalize_flag_mul) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17017_c_macro_;
		// use_dp_fadder_17258_delayed_2_0 := use_dp_fadder
		// $buffering 2 $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17020_c_macro_;
		// use_dp_fmul_17262_delayed_2_0 := use_dp_fmul $buffering 
		// 2 $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17023_c_macro_;
		// convert_to_single_17267_delayed_2_0 :=
		// convert_to_single $buffering 2 $cut_through // bits of
		// buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17026_c_macro_;
		// $volatile extn_result_to_round_and_normalize := (((
		// $mux use_dp_fadder_17258_delayed_2_0 extn_result_add
		// _b0 ) | ( $mux use_dp_fmul_17262_delayed_2_0
		// extn_result_mul _b0 ) ) | ( $mux
		// convert_to_single_17267_delayed_2_0
		// extn_result_double_to_single _b0 ) ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17042_c_macro_;
		// $volatile double_precision_round_normalize :=
		// (use_fadderd | double_mul) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17047_c_macro_;
		// $volatile $call round_fp_64
		// (extn_result_to_round_and_normalize ) (round_d_result ) 
		// 
		fpunit_exec_exec__exec_daemon_call_stmt_17050_c_macro_;
		// $volatile $call round_fp_32
		// (extn_result_to_round_and_normalize ) (round_s_result ) 
		// 
		fpunit_exec_exec__exec_daemon_call_stmt_17053_c_macro_;
		// double_precision_round_normalize_17286_delayed_2_0 :=
		// double_precision_round_normalize $buffering 2
		// $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17056_c_macro_;
		// $volatile denormalize_flag_64 := (denormalize_flag &
		// double_precision_round_normalize_17286_delayed_2_0)
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17061_c_macro_;
		// $guard (denormalize_flag_64) $call denormalize_fp_64
		// (extn_result_to_round_and_normalize )
		// (denorm_result_d_slow ) 
		fpunit_exec_exec__exec_daemon_call_stmt_17065_c_macro_;
		// NOT_u1_u1_17296_17296_delayed_2_0 := ( ~
		// double_precision_round_normalize ) $buffering 2
		// $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17069_c_macro_;
		// $volatile denormalize_flag_32 := (denormalize_flag &
		// NOT_u1_u1_17296_17296_delayed_2_0) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17074_c_macro_;
		// $guard (denormalize_flag_32) $call denormalize_fp_32
		// (extn_result_to_round_and_normalize )
		// (denorm_result_s_slow ) 
		fpunit_exec_exec__exec_daemon_call_stmt_17078_c_macro_;
		// denormalize_flag_32_17304_delayed_1_0 :=
		// denormalize_flag_32 $buffering 1 $cut_through // bits
		// of buffering = 1. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17081_c_macro_;
		// round_s_result_17306_delayed_1_0 := round_s_result
		// $buffering 1 $cut_through // bits of buffering = 32. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17084_c_macro_;
		// $volatile addsubs_result := ( $mux
		// denormalize_flag_32_17304_delayed_1_0
		// denorm_result_s_slow round_s_result_17306_delayed_1_0 ) 
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17090_c_macro_;
		// denormalize_flag_64_17310_delayed_1_0 :=
		// denormalize_flag_64 $buffering 1 $cut_through // bits
		// of buffering = 1. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17093_c_macro_;
		// round_d_result_17312_delayed_1_0 := round_d_result
		// $buffering 1 $cut_through // bits of buffering = 64. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17096_c_macro_;
		// $volatile addsubd_result := ( $mux
		// denormalize_flag_64_17310_delayed_1_0
		// denorm_result_d_slow round_d_result_17312_delayed_1_0 ) 
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17102_c_macro_;
		// denormalize_flag_32_17316_delayed_1_0 :=
		// denormalize_flag_32 $buffering 1 $cut_through // bits
		// of buffering = 1. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17105_c_macro_;
		// round_s_result_17318_delayed_1_0 := round_s_result
		// $buffering 1 $cut_through // bits of buffering = 32. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17108_c_macro_;
		// $volatile muls_result := ( $mux
		// denormalize_flag_32_17316_delayed_1_0
		// denorm_result_s_slow round_s_result_17318_delayed_1_0 ) 
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17114_c_macro_;
		// denormalize_flag_64_17322_delayed_1_0 :=
		// denormalize_flag_64 $buffering 1 $cut_through // bits
		// of buffering = 1. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17117_c_macro_;
		// round_d_result_17324_delayed_1_0 := round_d_result
		// $buffering 1 $cut_through // bits of buffering = 64. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17120_c_macro_;
		// $volatile muld_result := ( $mux
		// denormalize_flag_64_17322_delayed_1_0
		// denorm_result_d_slow round_d_result_17324_delayed_1_0 ) 
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17126_c_macro_;
		// $volatile fsmuld_result := ($bitcast ($float<11,52>)
		// muld_result ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17130_c_macro_;
		// condition_denormalize_flag_double_to_single_17332_delayed_1_0 
		// := condition_denormalize_flag_double_to_single
		// $buffering 1 $cut_through // bits of buffering = 1. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17133_c_macro_;
		// round_s_result_17334_delayed_1_0 := round_s_result
		// $buffering 1 $cut_through // bits of buffering = 32. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17136_c_macro_;
		// $volatile to_single_out := ( $mux
		// condition_denormalize_flag_double_to_single_17332_delayed_1_0 
		// denorm_result_s_slow round_s_result_17334_delayed_1_0 ) 
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17142_c_macro_;
		// use_fadders_17338_delayed_3_0 := use_fadders $buffering 
		// 3 $cut_through // bits of buffering = 3. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17145_c_macro_;
		// $volatile add_sub_mul_s_result := ( $mux
		// use_fadders_17338_delayed_3_0 addsubs_result
		// muls_result ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17151_c_macro_;
		// use_fadderd_17344_delayed_3_0 := use_fadderd $buffering 
		// 3 $cut_through // bits of buffering = 3. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17154_c_macro_;
		// $volatile add_sub_mul_d_result := ( $mux
		// use_fadderd_17344_delayed_3_0 addsubd_result
		// muld_result ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17160_c_macro_;
		// $volatile simd32_result_fast_l := round_s_result
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17163_c_macro_;
		// $volatile simd32_result_slow_l := add_sub_mul_s_result
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17166_c_macro_;
		// $volatile issue_simd_16 := ((simd_16_flag & simd_alu) | 
		// issue_faddreduce16) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17173_c_macro_;
		// $guard (issue_simd_16) $call exec_fp_simd_16_op
		// (issue_vfadd issue_vfsub issue_vfmul issue_faddreduce16 
		// uf1_d uf2_d ) (simd_16_result_64 ) 
		fpunit_exec_exec__exec_daemon_call_stmt_17182_c_macro_;
		// $guard (issue_fdivs) $call fpdivide32 (f1_s f2_s )
		// (fdivs_result ) 
		fpunit_exec_exec__exec_daemon_call_stmt_17187_c_macro_;
		// $volatile divs_result := ($bitcast ($uint<32>)
		// fdivs_result ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17191_c_macro_;
		// $guard (issue_fsqrts) $call fpsqrt32_bit_wise (f2_s )
		// (fsqrts_result ) 
		fpunit_exec_exec__exec_daemon_call_stmt_17195_c_macro_;
		// $volatile sqrts_result := ($bitcast ($uint<32>)
		// fsqrts_result ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17199_c_macro_;
		// $volatile cmp_in_1_s := ( $mux ops_valid f1_s 0 )
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17205_c_macro_;
		// $volatile cmp_in_2_s := ( $mux ops_valid f2_s 0 )
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17211_c_macro_;
		// $volatile $call fpcmp32 (cmp_in_1_s cmp_in_2_s 0 )
		// (cmps_flags ) 
		fpunit_exec_exec__exec_daemon_call_stmt_17216_c_macro_;
		// $volatile $call fpcmp32 (cmp_in_1_s cmp_in_2_s 1 )
		// (cmpes_flags ) 
		fpunit_exec_exec__exec_daemon_call_stmt_17221_c_macro_;
		// $volatile dtoi_in := ( $mux issue_fdtoi f2_d f2_s_d )
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17227_c_macro_;
		// $volatile issue_toi := (issue_fstoi | issue_fdtoi)
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17232_c_macro_;
		// $guard (issue_toi) $call fdtoi_op (dtoi_in )
		// (toi_result_temp ) 
		fpunit_exec_exec__exec_daemon_call_stmt_17236_c_macro_;
		// $volatile dtoi_result := ($bitcast ($uint<32>)
		// toi_result_temp ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17240_c_macro_;
		// $volatile stoi_result := ($bitcast ($uint<32>)
		// toi_result_temp ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17244_c_macro_;
		// $guard (issue_fdivd) $call fpdivide64 (f1_d f2_d )
		// (fdivd_result ) 
		fpunit_exec_exec__exec_daemon_call_stmt_17249_c_macro_;
		// $guard (issue_fsqrtd) $call fpsqrt64_bit_wise (f2_d )
		// (fsqrtd_result ) 
		fpunit_exec_exec__exec_daemon_call_stmt_17253_c_macro_;
		// $volatile cmp_in_1_d := ( $mux ops_valid f1_d 0 )
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17259_c_macro_;
		// $volatile cmp_in_2_d := ( $mux ops_valid f2_d 0 )
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17265_c_macro_;
		// $volatile $call fpcmp64 (cmp_in_1_d cmp_in_2_d 0 )
		// (cmpd_flags ) 
		fpunit_exec_exec__exec_daemon_call_stmt_17270_c_macro_;
		// $volatile $call fpcmp64 (cmp_in_1_d cmp_in_2_d 1 )
		// (cmped_flags ) 
		fpunit_exec_exec__exec_daemon_call_stmt_17275_c_macro_;
		// $volatile itos_result := round_s_result $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17278_c_macro_;
		// $volatile stod_result := ($bitcast ($uint<64>)
		// fstod_result ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17282_c_macro_;
		// $volatile divd_result := ($bitcast ($uint<64>)
		// fdivd_result ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17286_c_macro_;
		// $volatile sqrtd_result := ($bitcast ($uint<64>)
		// fsqrtd_result ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17290_c_macro_;
		// $volatile itod_result := ($bitcast ($uint<64>)
		// fitod_result ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17294_c_macro_;
		// $volatile dtos_result_slow := ($bitcast ($uint<32>)
		// to_single_out ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17298_c_macro_;
		// $volatile dtos_result_fast := round_s_result $buffering 
		// 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17301_c_macro_;
		// $volatile fp_has_trapped := (uses_fu1 & (decode_trap |
		// ieee_754_exception)) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17308_c_macro_;
		// $volatile fp_traps := (((uses_fu1 & unimpl_instr) &&
		// (uses_fu1 & invalid_reg)) && ((uses_fu1 & seq_error) && 
		// (uses_fu1 & ieee_754_exception))) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17325_c_macro_;
		// OR_u1_u1_17536_17536_delayed_3_0 := ((issue_faddd |
		// issue_fsubd) | (issue_fmuld | issue_fsmuld)) $buffering 
		// 3 $cut_through // bits of buffering = 3. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17334_c_macro_;
		// issue_fdivd_17545_delayed_3_0 := issue_fdivd $buffering 
		// 3 $cut_through // bits of buffering = 3. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17337_c_macro_;
		// issue_simd_32_17549_delayed_3_0 := issue_simd_32
		// $buffering 3 $cut_through // bits of buffering = 3. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17340_c_macro_;
		// issue_fsqrtd_17540_delayed_3_0 := issue_fsqrtd
		// $buffering 3 $cut_through // bits of buffering = 3. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17343_c_macro_;
		// $volatile i_result_d := ((( $mux
		// OR_u1_u1_17536_17536_delayed_3_0 add_sub_mul_d_result
		// _b0 ) | ( $mux issue_fsqrtd_17540_delayed_3_0
		// sqrtd_result _b0 ) ) | (( $mux
		// issue_fdivd_17545_delayed_3_0 divd_result _b0 ) | (
		// $mux issue_simd_32_17549_delayed_3_0
		// (simd32_result_slow_h && simd32_result_slow_l) _b0 ) )) 
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17366_c_macro_;
		// MUX_17584_17584_delayed_1_0 := ( $mux issue_fitod
		// itod_result _b0 ) $buffering 1 $cut_through // bits of
		// buffering = 64. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17372_c_macro_;
		// simd_16_flag_17585_delayed_1_0 := simd_16_flag
		// $buffering 1 $cut_through // bits of buffering = 1. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17375_c_macro_;
		// OR_u64_u64_17589_17589_delayed_1_0 :=
		// (MUX_17584_17584_delayed_1_0 | ( $mux
		// simd_16_flag_17585_delayed_1_0 simd_16_result_64 _b0 )
		// ) $buffering 1 $cut_through // bits of buffering = 64. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17383_c_macro_;
		// MUX_17579_17579_delayed_2_0 := ( $mux issue_fstod
		// stod_result _b0 ) $buffering 2 $cut_through // bits of
		// buffering = 128. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17389_c_macro_;
		// OR_u1_u1_17565_17565_delayed_2_0 := ((issue_faddd |
		// issue_fsubd) | (issue_fsmuld | issue_fmuld)) $buffering 
		// 2 $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17398_c_macro_;
		// issue_simd_32_17569_delayed_2_0 := issue_simd_32
		// $buffering 2 $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17401_c_macro_;
		// issue_vfconv_17590_delayed_2_0 := issue_vfconv
		// $buffering 2 $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17404_c_macro_;
		// $volatile i_result_d_fast := (((( $mux
		// OR_u1_u1_17565_17565_delayed_2_0 round_d_result _b0 ) | 
		// ( $mux issue_simd_32_17569_delayed_2_0
		// (simd32_result_fast_h && simd32_result_fast_l) _b0 ) )
		// | MUX_17579_17579_delayed_2_0) |
		// (OR_u64_u64_17589_17589_delayed_1_0 | ( $mux
		// issue_vfconv_17590_delayed_2_0 vfconv_result_d _b0 ) )) 
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17426_c_macro_;
		// OR_u1_u1_17602_17602_delayed_3_0 := ((issue_fadds |
		// issue_fsubs) | issue_fmuls) $buffering 3 $cut_through
		// // bits of buffering = 3. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17433_c_macro_;
		// issue_fdivs_17606_delayed_3_0 := issue_fdivs $buffering 
		// 3 $cut_through // bits of buffering = 3. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17436_c_macro_;
		// issue_fsqrts_17611_delayed_3_0 := issue_fsqrts
		// $buffering 3 $cut_through // bits of buffering = 3. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17439_c_macro_;
		// issue_fdtos_17615_delayed_3_0 := issue_fdtos $buffering 
		// 3 $cut_through // bits of buffering = 3. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17442_c_macro_;
		// $volatile i_result_s := ((( $mux
		// OR_u1_u1_17602_17602_delayed_3_0 add_sub_mul_s_result
		// _b0 ) | ( $mux issue_fdivs_17606_delayed_3_0
		// divs_result _b0 ) ) | (( $mux
		// issue_fsqrts_17611_delayed_3_0 sqrts_result _b0 ) | (
		// $mux issue_fdtos_17615_delayed_3_0 dtos_result_slow _b0 
		// ) )) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17463_c_macro_;
		// MUX_17634_17634_delayed_2_0 := ( $mux triv_flag_s
		// triv_result_s _b0 ) $buffering 2 $cut_through // bits
		// of buffering = 64. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17469_c_macro_;
		// OR_u1_u1_17627_17627_delayed_2_0 := ((issue_fadds |
		// issue_fsubs) | issue_fmuls) $buffering 2 $cut_through
		// // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17476_c_macro_;
		// MUX_17663_17663_delayed_1_0 := ( $mux issue_fhconv
		// fhconv_result_s _b0 ) $buffering 1 $cut_through // bits 
		// of buffering = 32. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17482_c_macro_;
		// issue_faddreduce16_17655_delayed_1_0 :=
		// issue_faddreduce16 $buffering 1 $cut_through // bits of 
		// buffering = 1. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17485_c_macro_;
		// OR_u32_u32_17664_17664_delayed_1_0 := (( $mux
		// issue_faddreduce16_17655_delayed_1_0 ( $slice
		// simd_16_result_64 31 0 ) _b0 ) |
		// MUX_17663_17663_delayed_1_0) $buffering 1 $cut_through
		// // bits of buffering = 32. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17494_c_macro_;
		// issue_fstoi_17636_delayed_2_0 := issue_fstoi $buffering 
		// 2 $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17497_c_macro_;
		// issue_fdtoi_17640_delayed_2_0 := issue_fdtoi $buffering 
		// 2 $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17500_c_macro_;
		// issue_fdtos_17646_delayed_2_0 := issue_fdtos $buffering 
		// 2 $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17503_c_macro_;
		// issue_fitos_17650_delayed_2_0 := issue_fitos $buffering 
		// 2 $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17506_c_macro_;
		// $volatile i_result_s_fast := (((( $mux
		// OR_u1_u1_17627_17627_delayed_2_0 round_s_result _b0 ) | 
		// MUX_17634_17634_delayed_2_0) | (( $mux
		// issue_fstoi_17636_delayed_2_0 stoi_result _b0 ) | (
		// $mux issue_fdtoi_17640_delayed_2_0 dtoi_result _b0 ) )) 
		// | ((( $mux issue_fdtos_17646_delayed_2_0
		// dtos_result_fast _b0 ) | ( $mux
		// issue_fitos_17650_delayed_2_0 itos_result _b0 ) ) |
		// OR_u32_u32_17664_17664_delayed_1_0)) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17536_c_macro_;
		// $volatile update_fcc := ((issue_fcmps | issue_fcmpes) | 
		// (issue_fcmpd | issue_fcmped)) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17545_c_macro_;
		// $volatile updated_fcc := ((( $mux issue_fcmps
		// cmps_flags _b0 ) | ( $mux issue_fcmpes cmpes_flags _b0
		// ) ) | (( $mux issue_fcmpd cmpd_flags _b0 ) | ( $mux
		// issue_fcmped cmped_flags _b0 ) )) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17566_c_macro_;
		// $volatile i_result_d_h := ( $slice i_result_d 63 32 )
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17570_c_macro_;
		// $volatile i_result_d_l := ( $slice i_result_d 31 0 )
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17574_c_macro_;
		// $volatile i_result_d_h_fast := ( $slice i_result_d_fast 
		// 63 32 ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17578_c_macro_;
		// $volatile i_result_d_l_fast := ( $slice i_result_d_fast 
		// 31 0 ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17582_c_macro_;
		// $volatile is_double_result := ((((issue_faddd |
		// issue_fsubd) | issue_fmuld) | (issue_fsqrtd |
		// issue_fsmuld)) | (((issue_fdivd | issue_fitod) |
		// issue_fstod) | (simd_alu | issue_vfconv))) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17603_c_macro_;
		// $volatile is_single_result := ((((issue_fadds |
		// issue_fsubs) | (issue_fmuls | issue_fsqrts)) |
		// ((issue_fdivs | issue_fmovs) | issue_fnegs)) |
		// (((issue_fabss | issue_fdtoi) | (issue_fstoi |
		// issue_fdtos)) | ((issue_fitos | issue_faddreduce16) |
		// issue_fhconv))) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17632_c_macro_;
		// is_double_result_17765_delayed_3_0 := is_double_result
		// $buffering 3 $cut_through // bits of buffering = 3. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17635_c_macro_;
		// $volatile wb_h := ( $mux
		// is_double_result_17765_delayed_3_0 i_result_d_h ZERO_32 
		// ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17641_c_macro_;
		// is_double_result_17771_delayed_3_0 := is_double_result
		// $buffering 3 $cut_through // bits of buffering = 3. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17644_c_macro_;
		// is_single_result_17775_delayed_3_0 := is_single_result
		// $buffering 3 $cut_through // bits of buffering = 3. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17647_c_macro_;
		// $volatile wb_l := (( $mux
		// is_double_result_17771_delayed_3_0 i_result_d_l _b0 ) | 
		// ( $mux is_single_result_17775_delayed_3_0 i_result_s
		// _b0 ) ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17658_c_macro_;
		// is_double_result_17782_delayed_2_0 := is_double_result
		// $buffering 2 $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17661_c_macro_;
		// $volatile wb_h_fast := ( $mux
		// is_double_result_17782_delayed_2_0 i_result_d_h_fast
		// ZERO_32 ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17667_c_macro_;
		// is_double_result_17788_delayed_2_0 := is_double_result
		// $buffering 2 $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17670_c_macro_;
		// is_single_result_17792_delayed_2_0 := is_single_result
		// $buffering 2 $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17673_c_macro_;
		// $volatile wb_l_fast := (( $mux
		// is_double_result_17788_delayed_2_0 i_result_d_l_fast
		// _b0 ) | ( $mux is_single_result_17792_delayed_2_0
		// i_result_s_fast _b0 ) ) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17684_c_macro_;
		// OR_u1_u1_17805_17805_delayed_2_0 := ((issue_fdivs |
		// issue_fdivd) | (issue_fsqrts | issue_fsqrtd))
		// $buffering 2 $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17693_c_macro_;
		// use_dp_fmul_17806_delayed_2_0 := use_dp_fmul $buffering 
		// 2 $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17696_c_macro_;
		// use_dp_fadder_17810_delayed_2_0 := use_dp_fadder
		// $buffering 2 $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17699_c_macro_;
		// use_faddervs_17814_delayed_1_0 := use_faddervs
		// $buffering 1 $cut_through // bits of buffering = 1. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17702_c_macro_;
		// AND_u1_u1_17816_17816_delayed_1_0 :=
		// (use_faddervs_17814_delayed_1_0 & vs_addsub_needs_norm) 
		// $buffering 1 $cut_through // bits of buffering = 1. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17707_c_macro_;
		// use_fmulvs_17817_delayed_2_0 := use_fmulvs $buffering 2 
		// $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17710_c_macro_;
		// issue_fdtos_17821_delayed_2_0 := issue_fdtos $buffering 
		// 2 $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17713_c_macro_;
		// $volatile fast_is_not_valid :=
		// (((OR_u1_u1_17805_17805_delayed_2_0 |
		// (use_dp_fmul_17806_delayed_2_0 & denormalize_flag_mul)) 
		// | (use_dp_fadder_17810_delayed_2_0 &
		// denormalize_flag_add)) |
		// ((AND_u1_u1_17816_17816_delayed_1_0 |
		// (use_fmulvs_17817_delayed_2_0 & vs_mul_needs_norm)) |
		// (issue_fdtos_17821_delayed_2_0 &
		// denorm_double_to_single))) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17734_c_macro_;
		// NOT_u1_u1_17834_17834_delayed_2_0 := ( ~ fp_dti )
		// $buffering 2 $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17738_c_macro_;
		// NOT_u1_u1_17829_17829_delayed_2_0 := ( ~ skip_fp )
		// $buffering 2 $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17742_c_macro_;
		// AND_u1_u1_17840_17840_delayed_2_0 := (( ~ do_not_bypass 
		// ) & ( ~ issue_fbfcc )) $buffering 2 $cut_through //
		// bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17749_c_macro_;
		// $volatile send_bypass :=
		// (((NOT_u1_u1_17829_17829_delayed_2_0 & ( ~
		// fast_is_not_valid )) &
		// NOT_u1_u1_17834_17834_delayed_2_0) &
		// AND_u1_u1_17840_17840_delayed_2_0) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17759_c_macro_;
		// $volatile write_reg_flag := (((((issue_fadds |
		// issue_fsubs) | issue_fmuls) | (issue_fmovs |
		// issue_fnegs)) | (((issue_fabss | issue_fstoi) |
		// issue_fdtoi) | (issue_fitos | issue_faddd))) |
		// ((((issue_fsubd | issue_fsmuld) | issue_fmuld) |
		// (issue_fstod | issue_fitod)) | ((simd_alu |
		// issue_faddreduce16) | (issue_fstoh | issue_fhtos))))
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17798_c_macro_;
		// $volatile bypass_ftt := ((( $mux (uses_fu1 &
		// unimpl_instr) ($bitcast ($uint<3>) 3 ) _b0 ) | ( $mux
		// (uses_fu1 & invalid_reg) ($bitcast ($uint<3>) 6 ) _b0 ) 
		// ) | (( $mux (uses_fu1 & seq_error) ($bitcast ($uint<3>) 
		// 4 ) _b0 ) | ( $mux ((uses_fu1 & ( ~ decode_trap )) &
		// ieee_754_exception) ($bitcast ($uint<3>) 1 ) _b0 ) ))
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17834_c_macro_;
		// thread_id_17920_delayed_2_0 := thread_id $buffering 2
		// $cut_through // bits of buffering = 8. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17837_c_macro_;
		// CONCAT_u2_u8_17924_17924_delayed_2_0 := (stream_id &&
		// slot_id) $buffering 2 $cut_through // bits of buffering 
		// = 16. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17842_c_macro_;
		// CONCAT_u3_u6_17930_17930_delayed_2_0 := ((update_fcc && 
		// updated_fcc) && bypass_ftt) $buffering 2 $cut_through
		// // bits of buffering = 12. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17849_c_macro_;
		// CONCAT_u6_u7_17936_17936_delayed_2_0 := ((cexc &&
		// write_reg_flag) && is_double_result) $buffering 2
		// $cut_through // bits of buffering = 14. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17856_c_macro_;
		// write_reg_id_17937_delayed_2_0 := write_reg_id
		// $buffering 2 $cut_through // bits of buffering = 10. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17859_c_macro_;
		// $volatile bypass_to_reg_file := ((((send_bypass &&
		// thread_id_17920_delayed_2_0) &&
		// CONCAT_u2_u8_17924_17924_delayed_2_0) &&
		// CONCAT_u3_u6_17930_17930_delayed_2_0) &&
		// (CONCAT_u6_u7_17936_17936_delayed_2_0 &&
		// ((write_reg_id_17937_delayed_2_0 && wb_h_fast) &&
		// wb_l_fast))) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17876_c_macro_;
		// noblock_fpunit_exec_bypass_signal_to_register_file :=
		// bypass_to_reg_file $buffering 1// bits of buffering =
		// 95. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17879_c_macro_;
		// thread_id_17951_delayed_2_0 := thread_id $buffering 2
		// $cut_through // bits of buffering = 8. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17882_c_macro_;
		// CONCAT_u2_u8_17955_17955_delayed_2_0 := (stream_id &&
		// slot_id) $buffering 2 $cut_through // bits of buffering 
		// = 16. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17887_c_macro_;
		// CONCAT_u2_u7_17967_17967_delayed_2_0 := ((ZERO_1 &&
		// (uses_fu1 & (decode_trap | ieee_754_exception))) &&
		// (ieee_754_exception && fp_traps)) $buffering 2
		// $cut_through // bits of buffering = 14. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17900_c_macro_;
		// CONCAT_u8_u11_17975_17975_delayed_2_0 := ((cexc &&
		// ZERO_3) && (update_fcc && updated_fcc)) $buffering 2
		// $cut_through // bits of buffering = 22. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17909_c_macro_;
		// skip_fp_17976_delayed_2_0 := skip_fp $buffering 2
		// $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17912_c_macro_;
		// $volatile to_wb_fast := ((((( ~ fast_is_not_valid ) &&
		// thread_id_17951_delayed_2_0) &&
		// CONCAT_u2_u8_17955_17955_delayed_2_0) &&
		// CONCAT_u2_u7_17967_17967_delayed_2_0) &&
		// (CONCAT_u8_u11_17975_17975_delayed_2_0 &&
		// ((skip_fp_17976_delayed_2_0 && wb_h_fast) &&
		// wb_l_fast))) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_17930_c_macro_;
		// fu1_to_fu2_17984_delayed_2_0 := fu1_to_fu2 $buffering 2 
		// $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17933_c_macro_;
		// $guard (fu1_to_fu2_17984_delayed_2_0)
		// fpunit_exec_to_writeback_fast := to_wb_fast $buffering
		// 1// bits of buffering = 96. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17937_c_macro_;
		// $guard (fu1_to_fu2) $report (fpunit_exec
		// fpunit_exec_to_writeback thread_id thread_id stream_id
		// stream_id slot_id slot_id ieee_754_exception
		// ieee_754_exception decode_trap decode_trap cexc cexc
		// wb_h wb_h wb_l wb_l update_fcc update_fcc updated_fcc
		// updated_fcc skip_fp skip_fp )
		fpunit_exec_exec__exec_daemon_stmt_17950_c_macro_;
		// thread_id_18003_delayed_2_0 := thread_id $buffering 2
		// $cut_through // bits of buffering = 8. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17953_c_macro_;
		// CONCAT_u2_u8_18007_18007_delayed_2_0 := (stream_id &&
		// slot_id) $buffering 2 $cut_through // bits of buffering 
		// = 16. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17958_c_macro_;
		// CONCAT_u2_u7_18019_18019_delayed_2_0 := ((ZERO_1 &&
		// (uses_fu1 & (decode_trap | ieee_754_exception))) &&
		// (ieee_754_exception && fp_traps)) $buffering 2
		// $cut_through // bits of buffering = 14. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17971_c_macro_;
		// CONCAT_u13_u20_18020_18020_delayed_1_0 :=
		// (((fast_is_not_valid && thread_id_18003_delayed_2_0) && 
		// CONCAT_u2_u8_18007_18007_delayed_2_0) &&
		// CONCAT_u2_u7_18019_18019_delayed_2_0) $buffering 1
		// $cut_through // bits of buffering = 20. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17980_c_macro_;
		// CONCAT_u8_u11_18027_18027_delayed_3_0 := ((cexc &&
		// ZERO_3) && (update_fcc && updated_fcc)) $buffering 3
		// $cut_through // bits of buffering = 33. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17989_c_macro_;
		// skip_fp_18028_delayed_3_0 := skip_fp $buffering 3
		// $cut_through // bits of buffering = 3. 
		fpunit_exec_exec__exec_daemon_assign_stmt_17992_c_macro_;
		// $volatile to_wb_slow :=
		// (CONCAT_u13_u20_18020_18020_delayed_1_0 &&
		// (CONCAT_u8_u11_18027_18027_delayed_3_0 &&
		// ((skip_fp_18028_delayed_3_0 && wb_h) && wb_l)))
		// $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_18003_c_macro_;
		// fu1_to_fu2_18037_delayed_2_0 := fu1_to_fu2 $buffering 2 
		// $cut_through // bits of buffering = 2. 
		fpunit_exec_exec__exec_daemon_assign_stmt_18006_c_macro_;
		// $volatile send_to_slow := (fu1_to_fu2_18037_delayed_2_0 
		// & fast_is_not_valid) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_18011_c_macro_;
		// send_to_slow_18041_delayed_1_0 := send_to_slow
		// $buffering 1 $cut_through // bits of buffering = 1. 
		fpunit_exec_exec__exec_daemon_assign_stmt_18014_c_macro_;
		// $guard (send_to_slow_18041_delayed_1_0)
		// fpunit_exec_to_writeback_slow := to_wb_slow $buffering
		// 1// bits of buffering = 96. 
		fpunit_exec_exec__exec_daemon_assign_stmt_18018_c_macro_;
		// $volatile trap_or_error := fp_has_trapped $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_18021_c_macro_;
		// $volatile to_ls := ((thread_id && stream_id) &&
		// (slot_id && trap_or_error)) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_18030_c_macro_;
		// $guard (fu1_trap_to_ls) teu_fpunit_trap_to_loadstore := 
		// to_ls $buffering 1// bits of buffering = 13. 
		fpunit_exec_exec__exec_daemon_assign_stmt_18034_c_macro_;
		// $volatile to_iu := ((thread_id && stream_id) &&
		// (slot_id && trap_or_error)) $buffering 1
		fpunit_exec_exec__exec_daemon_assign_stmt_18043_c_macro_;
		// $guard (fu1_to_iu2) teu_fpunit_trap_to_iunit := to_iu
		// $buffering 1// bits of buffering = 13. 
		fpunit_exec_exec__exec_daemon_assign_stmt_18047_c_macro_;
		// $sleep 100
		fpunit_exec_exec__exec_daemon_stmt_18048_c_macro_;
		do_while_entry_flag = 0;
		do_while_loopback_flag = 1;
		bit_vector_clear(&konst_18050);
		konst_18050.val.byte_array[0] = 1;
		if (!bit_vector_to_uint64(0, &konst_18050))
		    break;
	    }
	}
	fpunit_exec_exec__exec_daemon_branch_block_stmt_16373_c_export_apply_macro_;
    }
    fpunit_exec_exec__exec_daemon_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__exec_daemon_series_block_stmt_16372_c_mutex_);
}
void
fpunit_exec_exec_exec_daemon()
{
    fpunit_exec_exec__exec_daemon_outer_arg_decl_macro__;
    _fpunit_exec_exec_exec_daemon_();
    fpunit_exec_exec__exec_daemon_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_exec_fbfcc_generic_(bit_vector * __pbr_cond,
				      bit_vector * __pfcc,
				      bit_vector * __pannul_flag,
				      bit_vector * __pbr_taken,
				      bit_vector * __pannul_next)
{
    MUTEX_DECL
	(fpunit_exec_exec__exec_fbfcc_generic_series_block_stmt_18053_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__exec_fbfcc_generic_series_block_stmt_18053_c_mutex_);
    fpunit_exec_exec__exec_fbfcc_generic_inner_inarg_prep_macro__;
    // $volatile E := (fcc == 0 ) $buffering 1
    fpunit_exec_exec__exec_fbfcc_generic_assign_stmt_18063_c_macro_;
    // $volatile L := (fcc == 1 ) $buffering 1
    fpunit_exec_exec__exec_fbfcc_generic_assign_stmt_18068_c_macro_;
    // $volatile G := (fcc == 2 ) $buffering 1
    fpunit_exec_exec__exec_fbfcc_generic_assign_stmt_18073_c_macro_;
    // $volatile U := (fcc == 3 ) $buffering 1
    fpunit_exec_exec__exec_fbfcc_generic_assign_stmt_18078_c_macro_;
    // $volatile br_taken_raw := ((((( $mux (br_cond == 8 ) ONE_1 _b0 ) |
    // ( $mux (br_cond == 0 ) ZERO_1 _b0 ) ) | (( $mux (br_cond == 7 ) U
    // _b0 ) | ( $mux (br_cond == 6 ) G _b0 ) )) | ((( $mux (br_cond == 5
    // ) (G | U) _b0 ) | ( $mux (br_cond == 4 ) L _b0 ) ) | (( $mux
    // (br_cond == 3 ) (L | U) _b0 ) | ( $mux (br_cond == 2 ) (L | G) _b0
    // ) ))) | (((( $mux (br_cond == 1 ) ( ~ E ) _b0 ) | ( $mux (br_cond
    // == 9 ) E _b0 ) ) | (( $mux (br_cond == 10 ) (E | U) _b0 ) | ( $mux
    // (br_cond == 11 ) (G | E) _b0 ) )) | ((( $mux (br_cond == 12 ) ( ~ L 
    // ) _b0 ) | ( $mux (br_cond == 13 ) (L | E) _b0 ) ) | (( $mux
    // (br_cond == 14 ) ( ~ G ) _b0 ) | ( $mux (br_cond == 15 ) ( ~ U )
    // _b0 ) )))) $buffering 1
    fpunit_exec_exec__exec_fbfcc_generic_assign_stmt_18207_c_macro_;
    // $volatile branch_always := (br_cond == 8 ) $buffering 1
    fpunit_exec_exec__exec_fbfcc_generic_assign_stmt_18212_c_macro_;
    // annul_next := ( $mux br_taken_raw (branch_always & annul_flag)
    // annul_flag ) $buffering 1
    fpunit_exec_exec__exec_fbfcc_generic_assign_stmt_18220_c_macro_;
    // br_taken := br_taken_raw $buffering 1
    fpunit_exec_exec__exec_fbfcc_generic_assign_stmt_18223_c_macro_;
    fpunit_exec_exec__exec_fbfcc_generic_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__exec_fbfcc_generic_series_block_stmt_18053_c_mutex_);
}
void
_fpunit_exec_exec_exec_fhtoi16_(bit_vector * __puf1_h,
				bit_vector * __presult)
{
    MUTEX_DECL
	(fpunit_exec_exec__exec_fhtoi16_series_block_stmt_9507_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__exec_fhtoi16_series_block_stmt_9507_c_mutex_);
    fpunit_exec_exec__exec_fhtoi16_inner_inarg_prep_macro__;
    // $volatile $call classifyFp16 (uf1_h ) (f1_zero f1_normal f1_inf
    // f1_nan ) 
    fpunit_exec_exec__exec_fhtoi16_call_stmt_9515_c_macro_;
    // $volatile $call splitFp16 (uf1_h ) (f1_sign f1_exponent f1_mantissa 
    // ) 
    fpunit_exec_exec__exec_fhtoi16_call_stmt_9520_c_macro_;
    // $volatile frac_ext := ((ZERO_15 && ONE_1) && f1_mantissa)
    // $buffering 1
    fpunit_exec_exec__exec_fhtoi16_assign_stmt_9527_c_macro_;
    // $volatile unbiased_exp_h_i9 := (($bitcast ($int<9>) f1_exponent ) - 
    // 15 ) $buffering 1
    fpunit_exec_exec__exec_fhtoi16_assign_stmt_9534_c_macro_;
    // $volatile is_zero := (unbiased_exp_h_i9 < 0 ) $buffering 1
    fpunit_exec_exec__exec_fhtoi16_assign_stmt_9539_c_macro_;
    // $volatile left_shift_amount := ($bitcast ($uint<26>)
    // unbiased_exp_h_i9 ) $buffering 1
    fpunit_exec_exec__exec_fhtoi16_assign_stmt_9543_c_macro_;
    // $volatile overflow := (left_shift_amount > 15 ) $buffering 1
    fpunit_exec_exec__exec_fhtoi16_assign_stmt_9548_c_macro_;
    // $volatile ufrac := ( $slice (frac_ext << left_shift_amount) 25 10 ) 
    // $buffering 1
    fpunit_exec_exec__exec_fhtoi16_assign_stmt_9554_c_macro_;
    // result := ( $mux is_zero 0 ((( $mux (overflow & f1_sign) _h8000 _b0 
    // ) | ( $mux (overflow & ( ~ f1_sign )) _h7FFF _b0 ) ) | ( $mux ( ~
    // overflow ) ( $mux f1_sign ( $call increment_16 (( ~ ufrac ) ) )
    // ufrac ) _b0 ) ) ) $buffering 2// bits of buffering = 32. 
    fpunit_exec_exec__exec_fhtoi16_assign_stmt_9584_c_macro_;
    fpunit_exec_exec__exec_fhtoi16_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__exec_fhtoi16_series_block_stmt_9507_c_mutex_);
}
void
fpunit_exec_exec_exec_fhtoi16(uint16_t uf1_h, uint16_t * result)
{
    fpunit_exec_exec__exec_fhtoi16_outer_arg_decl_macro__;
    _fpunit_exec_exec_exec_fhtoi16_(&__uf1_h, &__result);
    fpunit_exec_exec__exec_fhtoi16_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_exec_fhtos_(bit_vector * __puf1_h,
			      bit_vector * __presult)
{
    MUTEX_DECL
	(fpunit_exec_exec__exec_fhtos_series_block_stmt_9797_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__exec_fhtos_series_block_stmt_9797_c_mutex_);
    fpunit_exec_exec__exec_fhtos_inner_inarg_prep_macro__;
    // $volatile $call splitFp16 (uf1_h ) (uf1_sign uf1_exponent
    // uf1_mantissa ) 
    fpunit_exec_exec__exec_fhtos_call_stmt_9804_c_macro_;
    // $volatile $call classifyFp16 (uf1_h ) (f1_zero f1_normal f1_nan
    // f1_inf ) 
    fpunit_exec_exec__exec_fhtos_call_stmt_9810_c_macro_;
    // $volatile unbiased_exp_h := (($bitcast ($int<9>) uf1_exponent ) -
    // 15 ) $buffering 1
    fpunit_exec_exec__exec_fhtos_assign_stmt_9816_c_macro_;
    // $volatile exp_8 := ($bitcast ($uint<8>) (unbiased_exp_h + 127 ) )
    // $buffering 1
    fpunit_exec_exec__exec_fhtos_assign_stmt_9822_c_macro_;
    // $volatile man_23 := (uf1_mantissa && ($bitcast ($uint<13>) 0 ))
    // $buffering 1
    fpunit_exec_exec__exec_fhtos_assign_stmt_9828_c_macro_;
    // $volatile result_norm := ((uf1_sign && exp_8) && man_23) $buffering 
    // 1
    fpunit_exec_exec__exec_fhtos_assign_stmt_9835_c_macro_;
    // $volatile result_qnan := ((ZERO_1 && ($bitcast ($uint<8>) _hFF ))
    // && (ONE_1 && ZERO_22)) $buffering 1
    fpunit_exec_exec__exec_fhtos_assign_stmt_9845_c_macro_;
    // $volatile result_zero := (uf1_sign && ZERO_31) $buffering 1
    fpunit_exec_exec__exec_fhtos_assign_stmt_9850_c_macro_;
    // $volatile result_infinity := ((uf1_sign && ($bitcast ($uint<8>)
    // _hFF )) && ZERO_23) $buffering 1
    fpunit_exec_exec__exec_fhtos_assign_stmt_9858_c_macro_;
    // result := ( $mux f1_inf result_infinity ( $mux f1_zero result_zero
    // ( $mux f1_normal result_norm result_qnan ) ) ) $buffering 2
    fpunit_exec_exec__exec_fhtos_assign_stmt_9870_c_macro_;
    fpunit_exec_exec__exec_fhtos_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__exec_fhtos_series_block_stmt_9797_c_mutex_);
}
void
fpunit_exec_exec_exec_fhtos(uint16_t uf1_h, uint32_t * result)
{
    fpunit_exec_exec__exec_fhtos_outer_arg_decl_macro__;
    _fpunit_exec_exec_exec_fhtos_(&__uf1_h, &__result);
    fpunit_exec_exec__exec_fhtos_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_exec_fi16toh_(bit_vector * __pX, bit_vector * __pY)
{
    MUTEX_DECL
	(fpunit_exec_exec__exec_fi16toh_series_block_stmt_9695_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__exec_fi16toh_series_block_stmt_9695_c_mutex_);
    fpunit_exec_exec__exec_fi16toh_inner_inarg_prep_macro__;
    // $volatile $call twos_complement_16 (X ) (Xcompl ) 
    fpunit_exec_exec__exec_fi16toh_call_stmt_9700_c_macro_;
    // $volatile sign := (X [] 15 ) $buffering 1
    fpunit_exec_exec__exec_fi16toh_assign_stmt_9705_c_macro_;
    // $volatile Xmagn := ( $mux sign Xcompl X ) $buffering 1
    fpunit_exec_exec__exec_fi16toh_assign_stmt_9711_c_macro_;
    // $volatile $call find_left_16 (Xmagn ) (pos1 found1 ) 
    fpunit_exec_exec__exec_fi16toh_call_stmt_9715_c_macro_;
    // $volatile is_zero := (Xmagn == 0 ) $buffering 1
    fpunit_exec_exec__exec_fi16toh_assign_stmt_9720_c_macro_;
    // $volatile shift_amount := ($bitcast ($uint<5>) (16 - ($bitcast
    // ($uint<5>) pos1 )) ) $buffering 1
    fpunit_exec_exec__exec_fi16toh_assign_stmt_9727_c_macro_;
    // $volatile expon := (($bitcast ($uint<5>) pos1 ) + 15 ) $buffering 1
    fpunit_exec_exec__exec_fi16toh_assign_stmt_9733_c_macro_;
    // $volatile $call i16_sll (Xmagn shift_amount ) (shifted_mantissa_16
    // ) 
    fpunit_exec_exec__exec_fi16toh_call_stmt_9737_c_macro_;
    // $volatile mantissa := ( $slice shifted_mantissa_16 15 6 )
    // $buffering 1
    fpunit_exec_exec__exec_fi16toh_assign_stmt_9741_c_macro_;
    // $volatile result_nz := ((sign && expon) && mantissa) $buffering 1
    fpunit_exec_exec__exec_fi16toh_assign_stmt_9748_c_macro_;
    // Y := ( $mux is_zero 0 result_nz ) $buffering 2// bits of buffering
    // = 32. 
    fpunit_exec_exec__exec_fi16toh_assign_stmt_9754_c_macro_;
    fpunit_exec_exec__exec_fi16toh_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__exec_fi16toh_series_block_stmt_9695_c_mutex_);
}
void
fpunit_exec_exec_exec_fi16toh(uint16_t X, uint16_t * Y)
{
    fpunit_exec_exec__exec_fi16toh_outer_arg_decl_macro__;
    _fpunit_exec_exec_exec_fi16toh_(&__X, &__Y);
    fpunit_exec_exec__exec_fi16toh_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_exec_fp_simd_16_op_(bit_vector * __pissue_vfadd,
				      bit_vector * __pissue_vfsub,
				      bit_vector * __pissue_vfmul,
				      bit_vector * __pissue_faddreduce16,
				      bit_vector * __puf1_d,
				      bit_vector * __puf2_d,
				      bit_vector * __psimd_16_result)
{
    MUTEX_DECL
	(fpunit_exec_exec__exec_fp_simd_16_op_series_block_stmt_14069_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__exec_fp_simd_16_op_series_block_stmt_14069_c_mutex_);
    fpunit_exec_exec__exec_fp_simd_16_op_inner_inarg_prep_macro__;
    // $volatile x3 := ( $slice uf1_d 63 48 ) $buffering 1
    fpunit_exec_exec__exec_fp_simd_16_op_assign_stmt_14080_c_macro_;
    // $volatile x2 := ( $slice uf1_d 47 32 ) $buffering 1
    fpunit_exec_exec__exec_fp_simd_16_op_assign_stmt_14084_c_macro_;
    // $volatile x1 := ( $slice uf1_d 31 16 ) $buffering 1
    fpunit_exec_exec__exec_fp_simd_16_op_assign_stmt_14088_c_macro_;
    // $volatile x0 := ( $slice uf1_d 15 0 ) $buffering 1
    fpunit_exec_exec__exec_fp_simd_16_op_assign_stmt_14092_c_macro_;
    // $volatile y3 := ( $slice uf2_d 63 48 ) $buffering 1
    fpunit_exec_exec__exec_fp_simd_16_op_assign_stmt_14096_c_macro_;
    // $volatile y2 := ( $slice uf2_d 47 32 ) $buffering 1
    fpunit_exec_exec__exec_fp_simd_16_op_assign_stmt_14100_c_macro_;
    // $volatile y1 := ( $slice uf2_d 31 16 ) $buffering 1
    fpunit_exec_exec__exec_fp_simd_16_op_assign_stmt_14104_c_macro_;
    // $volatile y0 := ( $slice uf2_d 15 0 ) $buffering 1
    fpunit_exec_exec__exec_fp_simd_16_op_assign_stmt_14108_c_macro_;
    // $volatile is_addsub := (issue_vfadd | issue_vfsub) $buffering 1
    fpunit_exec_exec__exec_fp_simd_16_op_assign_stmt_14113_c_macro_;
    // $volatile addsub_op_1_3 := x3 $buffering 1
    fpunit_exec_exec__exec_fp_simd_16_op_assign_stmt_14116_c_macro_;
    // $volatile addsub_op_2_3 := ( $mux is_addsub y3 x2 ) $buffering 1
    fpunit_exec_exec__exec_fp_simd_16_op_assign_stmt_14122_c_macro_;
    // $volatile $call faddsub16 (addsub_op_1_3 addsub_op_2_3 issue_vfsub
    // ) (a3 ) 
    fpunit_exec_exec__exec_fp_simd_16_op_call_stmt_14127_c_macro_;
    // $volatile addsub_op_1_2 := ( $mux is_addsub x2 x1 ) $buffering 1
    fpunit_exec_exec__exec_fp_simd_16_op_assign_stmt_14133_c_macro_;
    // $volatile addsub_op_2_2 := ( $mux is_addsub y2 x0 ) $buffering 1
    fpunit_exec_exec__exec_fp_simd_16_op_assign_stmt_14139_c_macro_;
    // $volatile $call faddsub16 (addsub_op_1_2 addsub_op_2_2 issue_vfsub
    // ) (a2 ) 
    fpunit_exec_exec__exec_fp_simd_16_op_call_stmt_14144_c_macro_;
    // $volatile addsub_op_1_1 := ( $mux is_addsub x1 a3 ) $buffering 1
    fpunit_exec_exec__exec_fp_simd_16_op_assign_stmt_14150_c_macro_;
    // $volatile addsub_op_2_1 := ( $mux is_addsub y1 a2 ) $buffering 1
    fpunit_exec_exec__exec_fp_simd_16_op_assign_stmt_14156_c_macro_;
    // $volatile $call faddsub16 (addsub_op_1_1 addsub_op_2_1 issue_vfsub
    // ) (a1 ) 
    fpunit_exec_exec__exec_fp_simd_16_op_call_stmt_14161_c_macro_;
    // $volatile addsub_op_1_0 := x0 $buffering 1
    fpunit_exec_exec__exec_fp_simd_16_op_assign_stmt_14164_c_macro_;
    // $volatile addsub_op_2_0 := y0 $buffering 1
    fpunit_exec_exec__exec_fp_simd_16_op_assign_stmt_14167_c_macro_;
    // $volatile $call faddsub16 (addsub_op_1_0 addsub_op_2_0 issue_vfsub
    // ) (a0 ) 
    fpunit_exec_exec__exec_fp_simd_16_op_call_stmt_14172_c_macro_;
    // $volatile reduce_result_64 := (ZERO_48 && a1) $buffering 1
    fpunit_exec_exec__exec_fp_simd_16_op_assign_stmt_14177_c_macro_;
    // $volatile addsub_result_64 := ((a3 && a2) && (a1 && a0)) $buffering 
    // 1
    fpunit_exec_exec__exec_fp_simd_16_op_assign_stmt_14186_c_macro_;
    // $volatile $call fmul16 (x3 y3 ) (m3 ) 
    fpunit_exec_exec__exec_fp_simd_16_op_call_stmt_14190_c_macro_;
    // $volatile $call fmul16 (x2 y2 ) (m2 ) 
    fpunit_exec_exec__exec_fp_simd_16_op_call_stmt_14194_c_macro_;
    // $volatile $call fmul16 (x1 y1 ) (m1 ) 
    fpunit_exec_exec__exec_fp_simd_16_op_call_stmt_14198_c_macro_;
    // $volatile $call fmul16 (x0 y0 ) (m0 ) 
    fpunit_exec_exec__exec_fp_simd_16_op_call_stmt_14202_c_macro_;
    // $volatile mul_result_64 := ((m3 && m2) && (m1 && m0)) $buffering 1
    fpunit_exec_exec__exec_fp_simd_16_op_assign_stmt_14211_c_macro_;
    // simd_16_result := ((( $mux is_addsub addsub_result_64 _b0 ) | (
    // $mux issue_vfmul mul_result_64 _b0 ) ) | ( $mux issue_faddreduce16
    // reduce_result_64 _b0 ) ) $buffering 2// bits of buffering = 128. 
    fpunit_exec_exec__exec_fp_simd_16_op_assign_stmt_14227_c_macro_;
    fpunit_exec_exec__exec_fp_simd_16_op_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__exec_fp_simd_16_op_series_block_stmt_14069_c_mutex_);
}
void
_fpunit_exec_exec_exec_fstoh_(bit_vector * __puf1_s,
			      bit_vector * __presult)
{
    MUTEX_DECL
	(fpunit_exec_exec__exec_fstoh_series_block_stmt_9923_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__exec_fstoh_series_block_stmt_9923_c_mutex_);
    fpunit_exec_exec__exec_fstoh_inner_inarg_prep_macro__;
    // $volatile sign_s := (uf1_s [] 31 ) $buffering 1
    fpunit_exec_exec__exec_fstoh_assign_stmt_9930_c_macro_;
    // $volatile exp_s := ( $slice uf1_s 30 23 ) $buffering 1
    fpunit_exec_exec__exec_fstoh_assign_stmt_9934_c_macro_;
    // $volatile mant_s := ( $slice uf1_s 22 0 ) $buffering 1
    fpunit_exec_exec__exec_fstoh_assign_stmt_9938_c_macro_;
    // $volatile $call classify_32 (($bitcast ($float<8,23>) uf1_s ) )
    // (f1_zero f1_normal f1_denormal f1_inf f1_nan ) 
    fpunit_exec_exec__exec_fstoh_call_stmt_9946_c_macro_;
    // $volatile bias := ($bitcast ($int<10>) ( $mux f1_denormal ($bitcast 
    // ($int<10>) 126 ) 127 ) ) $buffering 1
    fpunit_exec_exec__exec_fstoh_assign_stmt_9954_c_macro_;
    // $volatile exp_without_bias := (($bitcast ($int<10>) exp_s ) - bias) 
    // $buffering 1
    fpunit_exec_exec__exec_fstoh_assign_stmt_9960_c_macro_;
    // $volatile max_h_exponent := ($bitcast ($int<10>) 16 ) $buffering 1
    fpunit_exec_exec__exec_fstoh_assign_stmt_9964_c_macro_;
    // $volatile min_h_exponent := ($bitcast ($int<10>) -15 ) $buffering 1
    fpunit_exec_exec__exec_fstoh_assign_stmt_9968_c_macro_;
    // $volatile exp_overflow := (exp_without_bias > max_h_exponent)
    // $buffering 1
    fpunit_exec_exec__exec_fstoh_assign_stmt_9973_c_macro_;
    // $volatile exp_underflow := (exp_without_bias < min_h_exponent)
    // $buffering 1
    fpunit_exec_exec__exec_fstoh_assign_stmt_9978_c_macro_;
    // $volatile mantissa_h := ( $slice mant_s 22 13 ) $buffering 1
    fpunit_exec_exec__exec_fstoh_assign_stmt_9982_c_macro_;
    // $volatile nominal_h_bias := ($bitcast ($int<10>) 15 ) $buffering 1
    fpunit_exec_exec__exec_fstoh_assign_stmt_9986_c_macro_;
    // $volatile exp_normal := ($bitcast ($uint<5>) (exp_without_bias +
    // nominal_h_bias) ) $buffering 1
    fpunit_exec_exec__exec_fstoh_assign_stmt_9992_c_macro_;
    // $volatile result_normal := ((sign_s && exp_normal) && mantissa_h)
    // $buffering 1
    fpunit_exec_exec__exec_fstoh_assign_stmt_9999_c_macro_;
    // $volatile result_abnormal := ( $mux (f1_inf | exp_overflow) ( $call 
    // getHalfInf (sign_s ) ) ( $mux ((f1_zero | f1_denormal) |
    // exp_underflow) ( $call getHalfZero (sign_s ) ) ( $call getHalfNan
    // (sign_s ) ) ) ) $buffering 1
    fpunit_exec_exec__exec_fstoh_assign_stmt_10017_c_macro_;
    // $volatile abnormal_flag := (((f1_inf | f1_zero) | f1_denormal) |
    // (exp_overflow | exp_underflow)) $buffering 1
    fpunit_exec_exec__exec_fstoh_assign_stmt_10028_c_macro_;
    // result := ( $mux abnormal_flag result_abnormal result_normal )
    // $buffering 2
    fpunit_exec_exec__exec_fstoh_assign_stmt_10034_c_macro_;
    fpunit_exec_exec__exec_fstoh_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__exec_fstoh_series_block_stmt_9923_c_mutex_);
}
void
fpunit_exec_exec_exec_fstoh(uint32_t uf1_s, uint16_t * result)
{
    fpunit_exec_exec__exec_fstoh_outer_arg_decl_macro__;
    _fpunit_exec_exec_exec_fstoh_(&__uf1_s, &__result);
    fpunit_exec_exec__exec_fstoh_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_exec_vfhtoi16_(bit_vector * __pX, bit_vector * __pY)
{
    MUTEX_DECL
	(fpunit_exec_exec__exec_vfhtoi16_series_block_stmt_9586_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__exec_vfhtoi16_series_block_stmt_9586_c_mutex_);
    fpunit_exec_exec__exec_vfhtoi16_inner_inarg_prep_macro__;
    // $volatile X3 := ( $slice X 63 48 ) $buffering 1
    fpunit_exec_exec__exec_vfhtoi16_assign_stmt_9592_c_macro_;
    // $volatile X2 := ( $slice X 47 32 ) $buffering 1
    fpunit_exec_exec__exec_vfhtoi16_assign_stmt_9596_c_macro_;
    // $volatile X1 := ( $slice X 31 16 ) $buffering 1
    fpunit_exec_exec__exec_vfhtoi16_assign_stmt_9600_c_macro_;
    // $volatile X0 := ( $slice X 15 0 ) $buffering 1
    fpunit_exec_exec__exec_vfhtoi16_assign_stmt_9604_c_macro_;
    // $call exec_fhtoi16 (X3 ) (Y3 ) 
    fpunit_exec_exec__exec_vfhtoi16_call_stmt_9607_c_macro_;
    // $call exec_fhtoi16 (X2 ) (Y2 ) 
    fpunit_exec_exec__exec_vfhtoi16_call_stmt_9610_c_macro_;
    // $call exec_fhtoi16 (X1 ) (Y1 ) 
    fpunit_exec_exec__exec_vfhtoi16_call_stmt_9613_c_macro_;
    // $call exec_fhtoi16 (X0 ) (Y0 ) 
    fpunit_exec_exec__exec_vfhtoi16_call_stmt_9616_c_macro_;
    // $volatile Y := ((Y3 && Y2) && (Y1 && Y0)) $buffering 1
    fpunit_exec_exec__exec_vfhtoi16_assign_stmt_9625_c_macro_;
    fpunit_exec_exec__exec_vfhtoi16_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__exec_vfhtoi16_series_block_stmt_9586_c_mutex_);
}
void
fpunit_exec_exec_exec_vfhtoi16(uint64_t X, uint64_t * Y)
{
    fpunit_exec_exec__exec_vfhtoi16_outer_arg_decl_macro__;
    _fpunit_exec_exec_exec_vfhtoi16_(&__X, &__Y);
    fpunit_exec_exec__exec_vfhtoi16_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_exec_vfi16toh_(bit_vector * __pX, bit_vector * __pY)
{
    MUTEX_DECL
	(fpunit_exec_exec__exec_vfi16toh_series_block_stmt_9756_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__exec_vfi16toh_series_block_stmt_9756_c_mutex_);
    fpunit_exec_exec__exec_vfi16toh_inner_inarg_prep_macro__;
    // $volatile X3 := ( $slice X 63 48 ) $buffering 1
    fpunit_exec_exec__exec_vfi16toh_assign_stmt_9762_c_macro_;
    // $volatile X2 := ( $slice X 47 32 ) $buffering 1
    fpunit_exec_exec__exec_vfi16toh_assign_stmt_9766_c_macro_;
    // $volatile X1 := ( $slice X 31 16 ) $buffering 1
    fpunit_exec_exec__exec_vfi16toh_assign_stmt_9770_c_macro_;
    // $volatile X0 := ( $slice X 15 0 ) $buffering 1
    fpunit_exec_exec__exec_vfi16toh_assign_stmt_9774_c_macro_;
    // $call exec_fi16toh (X3 ) (Y3 ) 
    fpunit_exec_exec__exec_vfi16toh_call_stmt_9777_c_macro_;
    // $call exec_fi16toh (X2 ) (Y2 ) 
    fpunit_exec_exec__exec_vfi16toh_call_stmt_9780_c_macro_;
    // $call exec_fi16toh (X1 ) (Y1 ) 
    fpunit_exec_exec__exec_vfi16toh_call_stmt_9783_c_macro_;
    // $call exec_fi16toh (X0 ) (Y0 ) 
    fpunit_exec_exec__exec_vfi16toh_call_stmt_9786_c_macro_;
    // $volatile Y := ((Y3 && Y2) && (Y1 && Y0)) $buffering 1
    fpunit_exec_exec__exec_vfi16toh_assign_stmt_9795_c_macro_;
    fpunit_exec_exec__exec_vfi16toh_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__exec_vfi16toh_series_block_stmt_9756_c_mutex_);
}
void
fpunit_exec_exec_exec_vfi16toh(uint64_t X, uint64_t * Y)
{
    fpunit_exec_exec__exec_vfi16toh_outer_arg_decl_macro__;
    _fpunit_exec_exec_exec_vfi16toh_(&__X, &__Y);
    fpunit_exec_exec__exec_vfi16toh_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_execute_fbfcc_(bit_vector * __pbr_cond,
				 bit_vector * __pfsr,
				 bit_vector * __pannul_flag,
				 bit_vector * __pbr_taken,
				 bit_vector * __pannul_next)
{
    MUTEX_DECL
	(fpunit_exec_exec__execute_fbfcc_series_block_stmt_18225_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__execute_fbfcc_series_block_stmt_18225_c_mutex_);
    fpunit_exec_exec__execute_fbfcc_inner_inarg_prep_macro__;
    // $report (fpunit_exec execute_fbcc_in_args__ br_cond br_cond fsr fsr 
    // annul_flag annul_flag )
    fpunit_exec_exec__execute_fbfcc_stmt_18234_c_macro_;
    // $volatile fcc := ( $slice fsr 11 10 ) $buffering 1
    fpunit_exec_exec__execute_fbfcc_assign_stmt_18238_c_macro_;
    // $volatile E := (fcc == 0 ) $buffering 1
    fpunit_exec_exec__execute_fbfcc_assign_stmt_18243_c_macro_;
    // $volatile L := (fcc == 1 ) $buffering 1
    fpunit_exec_exec__execute_fbfcc_assign_stmt_18248_c_macro_;
    // $volatile G := (fcc == 2 ) $buffering 1
    fpunit_exec_exec__execute_fbfcc_assign_stmt_18253_c_macro_;
    // $volatile U := (fcc == 3 ) $buffering 1
    fpunit_exec_exec__execute_fbfcc_assign_stmt_18258_c_macro_;
    // $volatile br_taken_raw := ((((( $mux (br_cond == 8 ) ONE_1 _b0 ) |
    // ( $mux (br_cond == 0 ) ZERO_1 _b0 ) ) | (( $mux (br_cond == 7 ) U
    // _b0 ) | ( $mux (br_cond == 6 ) G _b0 ) )) | ((( $mux (br_cond == 5
    // ) (G | U) _b0 ) | ( $mux (br_cond == 4 ) L _b0 ) ) | (( $mux
    // (br_cond == 3 ) (L | U) _b0 ) | ( $mux (br_cond == 2 ) (L | G) _b0
    // ) ))) | (((( $mux (br_cond == 1 ) ( ~ E ) _b0 ) | ( $mux (br_cond
    // == 9 ) E _b0 ) ) | (( $mux (br_cond == 10 ) (E | U) _b0 ) | ( $mux
    // (br_cond == 11 ) (G | E) _b0 ) )) | ((( $mux (br_cond == 12 ) ( ~ L 
    // ) _b0 ) | ( $mux (br_cond == 13 ) (L | E) _b0 ) ) | (( $mux
    // (br_cond == 14 ) ( ~ G ) _b0 ) | ( $mux (br_cond == 15 ) ( ~ U )
    // _b0 ) )))) $buffering 1
    fpunit_exec_exec__execute_fbfcc_assign_stmt_18387_c_macro_;
    // $volatile branch_always := (br_cond == 8 ) $buffering 1
    fpunit_exec_exec__execute_fbfcc_assign_stmt_18392_c_macro_;
    // annul_next := ( $mux br_taken_raw (branch_always & annul_flag)
    // annul_flag ) $buffering 1
    fpunit_exec_exec__execute_fbfcc_assign_stmt_18400_c_macro_;
    // br_taken := br_taken_raw $buffering 1
    fpunit_exec_exec__execute_fbfcc_assign_stmt_18403_c_macro_;
    // $report (fpunit_exec execute_fbcc_out_args__ br_taken br_taken
    // annul_next annul_next )
    fpunit_exec_exec__execute_fbfcc_stmt_18406_c_macro_;
    fpunit_exec_exec__execute_fbfcc_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__execute_fbfcc_series_block_stmt_18225_c_mutex_);
}
void
_fpunit_exec_exec_expDiffDouble_(bit_vector * __puf1_d,
				 bit_vector * __puf2_d,
				 bit_vector *
				 __pexp_a_greater_than_exp_b_d,
				 bit_vector * __pexp_a_equal_exp_b_d,
				 bit_vector * __pexp_ab_d)
{
    MUTEX_DECL
	(fpunit_exec_exec__expDiffDouble_series_block_stmt_10145_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__expDiffDouble_series_block_stmt_10145_c_mutex_);
    fpunit_exec_exec__expDiffDouble_inner_inarg_prep_macro__;
    // ea := ( $slice uf1_d 62 52 ) $buffering 1
    fpunit_exec_exec__expDiffDouble_assign_stmt_10154_c_macro_;
    // eb := ( $slice uf2_d 62 52 ) $buffering 1
    fpunit_exec_exec__expDiffDouble_assign_stmt_10158_c_macro_;
    // $volatile $call compare11 (ea eb ) (exp_a_greater_than_exp_b_d
    // exp_a_equal_exp_b_d ) 
    fpunit_exec_exec__expDiffDouble_call_stmt_10163_c_macro_;
    // eab := (ea - eb) $buffering 1
    fpunit_exec_exec__expDiffDouble_assign_stmt_10168_c_macro_;
    // eba := (eb - ea) $buffering 1
    fpunit_exec_exec__expDiffDouble_assign_stmt_10173_c_macro_;
    // exp_ab_d := ($bitcast ($int<13>) ( $mux exp_a_greater_than_exp_b_d
    // eab eba ) ) $buffering 1
    fpunit_exec_exec__expDiffDouble_assign_stmt_10180_c_macro_;
    fpunit_exec_exec__expDiffDouble_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__expDiffDouble_series_block_stmt_10145_c_mutex_);
}
void
_fpunit_exec_exec_expDiffSingle_(bit_vector * __puf1_s,
				 bit_vector * __puf2_s,
				 bit_vector *
				 __pexp_a_greater_than_exp_b_s,
				 bit_vector * __pexp_a_equal_exp_b_s,
				 bit_vector * __pexp_ab_s)
{
    MUTEX_DECL
	(fpunit_exec_exec__expDiffSingle_series_block_stmt_10182_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__expDiffSingle_series_block_stmt_10182_c_mutex_);
    fpunit_exec_exec__expDiffSingle_inner_inarg_prep_macro__;
    // ea := ( $slice uf1_s 30 23 ) $buffering 1
    fpunit_exec_exec__expDiffSingle_assign_stmt_10191_c_macro_;
    // eb := ( $slice uf2_s 30 23 ) $buffering 1
    fpunit_exec_exec__expDiffSingle_assign_stmt_10195_c_macro_;
    // $volatile $call compare8 (ea eb ) (exp_a_greater_than_exp_b_s
    // exp_a_equal_exp_b_s ) 
    fpunit_exec_exec__expDiffSingle_call_stmt_10200_c_macro_;
    // eab := (ea - eb) $buffering 1
    fpunit_exec_exec__expDiffSingle_assign_stmt_10205_c_macro_;
    // eba := (eb - ea) $buffering 1
    fpunit_exec_exec__expDiffSingle_assign_stmt_10210_c_macro_;
    // exp_ab_s := ($bitcast ($int<13>) ( $mux exp_a_greater_than_exp_b_s
    // eab eba ) ) $buffering 1
    fpunit_exec_exec__expDiffSingle_assign_stmt_10217_c_macro_;
    fpunit_exec_exec__expDiffSingle_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__expDiffSingle_series_block_stmt_10182_c_mutex_);
}
void
_fpunit_exec_exec_fadd16_wrap_(bit_vector * __pf1, bit_vector * __pf2,
			       bit_vector * __presult)
{
    MUTEX_DECL
	(fpunit_exec_exec__fadd16_wrap_series_block_stmt_18408_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fadd16_wrap_series_block_stmt_18408_c_mutex_);
    fpunit_exec_exec__fadd16_wrap_inner_inarg_prep_macro__;
    // $volatile $call faddsub16 (f1 f2 ZERO_1 ) (result ) 
    fpunit_exec_exec__fadd16_wrap_call_stmt_18416_c_macro_;
    fpunit_exec_exec__fadd16_wrap_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fadd16_wrap_series_block_stmt_18408_c_mutex_);
}
void
fpunit_exec_exec_fadd16_wrap(uint16_t f1, uint16_t f2, uint16_t * result)
{
    fpunit_exec_exec__fadd16_wrap_outer_arg_decl_macro__;
    _fpunit_exec_exec_fadd16_wrap_(&__f1, &__f2, &__result);
    fpunit_exec_exec__fadd16_wrap_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_faddsub16_(bit_vector * __pf1, bit_vector * __pf2,
			     bit_vector * __psub, bit_vector * __presult)
{
    MUTEX_DECL
	(fpunit_exec_exec__faddsub16_series_block_stmt_13531_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__faddsub16_series_block_stmt_13531_c_mutex_);
    fpunit_exec_exec__faddsub16_inner_inarg_prep_macro__;
    // $volatile $call negateVal (f2 ) (f2c ) 
    fpunit_exec_exec__faddsub16_call_stmt_13541_c_macro_;
    // $volatile f2_actual := ( $mux sub f2c f2 ) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13547_c_macro_;
    // $volatile $call classifyFp16 (f1 ) (f1_zero f1_normal f1_nan f1_inf 
    // ) 
    fpunit_exec_exec__faddsub16_call_stmt_13553_c_macro_;
    // $volatile $call classifyFp16 (f2_actual ) (f2_zero f2_normal f2_nan 
    // f2_inf ) 
    fpunit_exec_exec__faddsub16_call_stmt_13559_c_macro_;
    // $volatile $call splitFp16 (f1 ) (sign_f1 f1_exp f1_fraction ) 
    fpunit_exec_exec__faddsub16_call_stmt_13564_c_macro_;
    // $volatile $call splitFp16 (f2_actual ) (sign_f2 f2_exp f2_fraction
    // ) 
    fpunit_exec_exec__faddsub16_call_stmt_13569_c_macro_;
    // $volatile f1_frac := (ONE_1 && f1_fraction) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13574_c_macro_;
    // $volatile f2_frac := (ONE_1 && f2_fraction) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13579_c_macro_;
    // $volatile exp_a := (($bitcast ($int<7>) f1_exp ) - 15 ) $buffering
    // 1
    fpunit_exec_exec__faddsub16_assign_stmt_13585_c_macro_;
    // $volatile exp_b := (($bitcast ($int<7>) f2_exp ) - 15 ) $buffering
    // 1
    fpunit_exec_exec__faddsub16_assign_stmt_13591_c_macro_;
    // $volatile exp_a_minus_b := (exp_a - exp_b) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13596_c_macro_;
    // $volatile exp_b_minus_a := (exp_b - exp_a) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13601_c_macro_;
    // $volatile exp_a_greater_than_b := (exp_a > exp_b) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13606_c_macro_;
    // $volatile exp_a_equal_exp_b := (exp_a == exp_b) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13611_c_macro_;
    // $volatile exp_ab := ( $mux exp_a_greater_than_b exp_a_minus_b
    // exp_b_minus_a ) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13617_c_macro_;
    // $volatile mantissa_a_pre_shift := ((ZERO_1 && f1_frac) && ($bitcast 
    // ($uint<1>) 0 )) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13625_c_macro_;
    // $volatile mantissa_b_pre_shift := ((ZERO_1 && f2_frac) && ($bitcast 
    // ($uint<1>) 0 )) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13633_c_macro_;
    // $volatile to_be_shifted := ( $mux exp_a_greater_than_b
    // mantissa_b_pre_shift mantissa_a_pre_shift ) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13639_c_macro_;
    // $volatile shifted_output := (to_be_shifted >> ($bitcast ($uint<13>) 
    // exp_ab )) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13645_c_macro_;
    // $volatile mantissa_a_post_shift := ( $mux (exp_a_greater_than_b |
    // exp_a_equal_exp_b) mantissa_a_pre_shift shifted_output ) $buffering 
    // 1
    fpunit_exec_exec__faddsub16_assign_stmt_13653_c_macro_;
    // $volatile mantissa_b_post_shift := ( $mux exp_a_greater_than_b
    // shifted_output mantissa_b_pre_shift ) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13659_c_macro_;
    // $volatile exponent_post_align := ( $mux exp_a_greater_than_b exp_a
    // exp_b ) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13665_c_macro_;
    // $volatile a_frac_ge_b_frac := (mantissa_a_post_shift >=
    // mantissa_b_post_shift) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13670_c_macro_;
    // $volatile need_to_take_twos_complement_a := (((sign_f1 & ( ~
    // sign_f2 )) & ( ~ a_frac_ge_b_frac )) | ((( ~ sign_f1 ) & sign_f2) & 
    // ( ~ a_frac_ge_b_frac ))) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13687_c_macro_;
    // $volatile need_to_take_twos_complement_b := (((sign_f2 & ( ~
    // sign_f1 )) & a_frac_ge_b_frac) | ((( ~ sign_f2 ) & sign_f1) &
    // a_frac_ge_b_frac)) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13702_c_macro_;
    // $volatile carry_in := (need_to_take_twos_complement_a |
    // need_to_take_twos_complement_b) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13707_c_macro_;
    // $volatile mantissa_operand_a_ext := (( $mux
    // need_to_take_twos_complement_a ( ~ mantissa_a_post_shift )
    // mantissa_a_post_shift ) && carry_in) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13716_c_macro_;
    // $volatile mantissa_operand_b_ext := (( $mux
    // need_to_take_twos_complement_b ( ~ mantissa_b_post_shift )
    // mantissa_b_post_shift ) && carry_in) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13725_c_macro_;
    // $volatile mantissa_added_ext := (mantissa_operand_a_ext +
    // mantissa_operand_b_ext) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13730_c_macro_;
    // $volatile need_to_shift := (((sign_f1 & sign_f2) | (( ~ sign_f1 ) & 
    // ( ~ sign_f2 ))) & (mantissa_added_ext [] 13 )) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13745_c_macro_;
    // $volatile mantissa_out_shifted := ( $slice mantissa_added_ext 13 3
    // ) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13749_c_macro_;
    // $volatile mantissa_out_unshifted := ( $slice mantissa_added_ext 12
    // 2 ) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13753_c_macro_;
    // $volatile sign_result := (((sign_f1 & sign_f2) | ((sign_f1 & ( ~
    // sign_f2 )) & a_frac_ge_b_frac)) | ((( ~ sign_f1 ) & sign_f2) & ( ~
    // a_frac_ge_b_frac ))) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13773_c_macro_;
    // $volatile mantissa_non_normalized := ( $mux need_to_shift (ZERO_1
    // && mantissa_out_shifted) (ZERO_1 && mantissa_out_unshifted) )
    // $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13783_c_macro_;
    // $volatile $call find_left_16 (($bitcast ($uint<16>)
    // mantissa_non_normalized ) ) (position_of_one one_found ) 
    fpunit_exec_exec__faddsub16_call_stmt_13788_c_macro_;
    // $volatile left_shift_amount := (10 - ($bitcast ($uint<5>)
    // position_of_one )) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13794_c_macro_;
    // $volatile $call i16_sll (($bitcast ($uint<16>)
    // mantissa_non_normalized ) left_shift_amount )
    // (final_mantissa_aligned_16 ) 
    fpunit_exec_exec__faddsub16_call_stmt_13799_c_macro_;
    // final_mantissa := ( $slice final_mantissa_aligned_16 9 0 )
    // $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13803_c_macro_;
    // $volatile left_shift_amount_E := ($bitcast ($int<7>)
    // left_shift_amount ) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13807_c_macro_;
    // $volatile final_exponent_without_bias := ((exponent_post_align - (
    // $mux one_found left_shift_amount_E _b0 ) ) + ( $mux need_to_shift 1 
    // 0 ) ) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13820_c_macro_;
    // $volatile final_exponent := ($bitcast ($uint<5>)
    // (final_exponent_without_bias + 15 ) ) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13826_c_macro_;
    // $volatile $call check_fh_exponent_overflow
    // (final_exponent_without_bias ) (overflow underflow ) 
    fpunit_exec_exec__faddsub16_call_stmt_13830_c_macro_;
    // $volatile non_zero_result := ((sign_result && final_exponent) &&
    // final_mantissa) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13837_c_macro_;
    // $volatile result_normal := ( $mux one_found non_zero_result _b0 )
    // $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13843_c_macro_;
    // $volatile result_abnormal := (((( $mux (f1_nan | f2_nan) ( $call
    // getHalfNan (ZERO_1 ) ) _b0 ) | ( $mux (underflow | (f1_zero &
    // f2_zero)) ( $call getHalfZero (ZERO_1 ) ) _b0 ) ) | ( $mux
    // (((f1_inf & f2_inf) & (sign_f1 == sign_f2)) | overflow) ( $call
    // getHalfInf (sign_f1 ) ) _b0 ) ) | ((( $mux ((f1_inf & f2_inf) &
    // (sign_f1 != sign_f2)) ( $call getHalfNan (ZERO_1 ) ) _b0 ) | ( $mux 
    // (f1_inf & f2_zero) ( $call getHalfInf (sign_f1 ) ) _b0 ) ) | ( $mux 
    // (f1_zero & f2_inf) ( $call getHalfInf ((sign_f1 ^ sub) ) ) _b0 ) )) 
    // $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13906_c_macro_;
    // $volatile abnormal_flag := (((f1_inf | f2_inf) | (f1_nan | f2_nan)) 
    // | ((overflow | underflow) | (f1_zero & f2_zero))) $buffering 1
    fpunit_exec_exec__faddsub16_assign_stmt_13923_c_macro_;
    // result := ( $mux abnormal_flag result_abnormal result_normal )
    // $buffering 2
    fpunit_exec_exec__faddsub16_assign_stmt_13929_c_macro_;
    fpunit_exec_exec__faddsub16_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__faddsub16_series_block_stmt_13531_c_mutex_);
}
void
_fpunit_exec_exec_fdtoi_op_(double *__pX, bit_vector * __pY)
{
    MUTEX_DECL
	(fpunit_exec_exec__fdtoi_op_series_block_stmt_15294_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fdtoi_op_series_block_stmt_15294_c_mutex_);
    fpunit_exec_exec__fdtoi_op_inner_inarg_prep_macro__;
    // Y := ($cast ($int<32>) X ) $buffering 2// bits of buffering = 64. 
    fpunit_exec_exec__fdtoi_op_assign_stmt_15300_c_macro_;
    fpunit_exec_exec__fdtoi_op_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fdtoi_op_series_block_stmt_15294_c_mutex_);
}
void
fpunit_exec_exec_fdtoi_op(double X, int32_t * Y)
{
    fpunit_exec_exec__fdtoi_op_outer_arg_decl_macro__;
    _fpunit_exec_exec_fdtoi_op_(&__X, &__Y);
    fpunit_exec_exec__fdtoi_op_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fdtoi_wrap_(double *__pX, bit_vector * __pY)
{
    MUTEX_DECL
	(fpunit_exec_exec__fdtoi_wrap_series_block_stmt_18418_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fdtoi_wrap_series_block_stmt_18418_c_mutex_);
    fpunit_exec_exec__fdtoi_wrap_inner_inarg_prep_macro__;
    // $call fdtoi_op (X ) (Y ) 
    fpunit_exec_exec__fdtoi_wrap_call_stmt_18423_c_macro_;
    fpunit_exec_exec__fdtoi_wrap_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fdtoi_wrap_series_block_stmt_18418_c_mutex_);
}
void
fpunit_exec_exec_fdtoi_wrap(double X, int32_t * Y)
{
    fpunit_exec_exec__fdtoi_wrap_outer_arg_decl_macro__;
    _fpunit_exec_exec_fdtoi_wrap_(&__X, &__Y);
    fpunit_exec_exec__fdtoi_wrap_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fdtos_wrap_(double *__pX, float *__pRESULT)
{
    MUTEX_DECL
	(fpunit_exec_exec__fdtos_wrap_series_block_stmt_18425_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fdtos_wrap_series_block_stmt_18425_c_mutex_);
    fpunit_exec_exec__fdtos_wrap_inner_inarg_prep_macro__;
    // $call DoubleToSingle (X ) (needs_denorm extn_result ) 
    fpunit_exec_exec__fdtos_wrap_call_stmt_18431_c_macro_;
    // $volatile $call round_fp_32 (extn_result ) (s_result_fast ) 
    fpunit_exec_exec__fdtos_wrap_call_stmt_18434_c_macro_;
    // $guard (needs_denorm) $call denormalize_fp_32 (extn_result )
    // (s_result_slow ) 
    fpunit_exec_exec__fdtos_wrap_call_stmt_18438_c_macro_;
    // RESULT := ($bitcast ($float<8,23>) ( $mux needs_denorm
    // s_result_slow s_result_fast ) ) $buffering 1// bits of buffering =
    // 32. 
    fpunit_exec_exec__fdtos_wrap_assign_stmt_18445_c_macro_;
    fpunit_exec_exec__fdtos_wrap_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fdtos_wrap_series_block_stmt_18425_c_mutex_);
}
void
fpunit_exec_exec_fdtos_wrap(double X, float *RESULT)
{
    float           __RESULT;
    fpunit_exec_exec__fdtos_wrap_outer_arg_decl_macro__;
    _fpunit_exec_exec_fdtos_wrap_(&__X, &__RESULT);
    fpunit_exec_exec__fdtos_wrap_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_find_left_16_(bit_vector * __pfp_16,
				bit_vector * __pposition,
				bit_vector * __pfound)
{
    MUTEX_DECL
	(fpunit_exec_exec__find_left_16_series_block_stmt_3083_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__find_left_16_series_block_stmt_3083_c_mutex_);
    fpunit_exec_exec__find_left_16_inner_inarg_prep_macro__;
    // $volatile fp_8_upper := ( $slice fp_16 15 8 ) $buffering 1
    fpunit_exec_exec__find_left_16_assign_stmt_3090_c_macro_;
    // $volatile fp_8_lower := ( $slice fp_16 7 0 ) $buffering 1
    fpunit_exec_exec__find_left_16_assign_stmt_3094_c_macro_;
    // $volatile $call find_left_8 (fp_8_upper ) (fp_8_upper_index
    // found_upper ) 
    fpunit_exec_exec__find_left_16_call_stmt_3098_c_macro_;
    // $volatile $call find_left_8 (fp_8_lower ) (fp_8_lower_index
    // found_lower ) 
    fpunit_exec_exec__find_left_16_call_stmt_3102_c_macro_;
    // $volatile position := ( $mux found_upper (ONE_1 &&
    // fp_8_upper_index) ( $mux found_lower (ZERO_1 && fp_8_lower_index)
    // ZERO_4 ) ) $buffering 1
    fpunit_exec_exec__find_left_16_assign_stmt_3115_c_macro_;
    // $volatile found := (found_upper | found_lower) $buffering 1
    fpunit_exec_exec__find_left_16_assign_stmt_3120_c_macro_;
    fpunit_exec_exec__find_left_16_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__find_left_16_series_block_stmt_3083_c_mutex_);
}
void
_fpunit_exec_exec_find_left_24_(bit_vector * __pfp_24,
				bit_vector * __pposition,
				bit_vector * __pfound)
{
    MUTEX_DECL
	(fpunit_exec_exec__find_left_24_series_block_stmt_1725_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__find_left_24_series_block_stmt_1725_c_mutex_);
    fpunit_exec_exec__find_left_24_inner_inarg_prep_macro__;
    // $volatile fp_2 := ( $slice fp_24 23 16 ) $buffering 1
    fpunit_exec_exec__find_left_24_assign_stmt_1732_c_macro_;
    // $volatile fp_1 := ( $slice fp_24 15 8 ) $buffering 1
    fpunit_exec_exec__find_left_24_assign_stmt_1736_c_macro_;
    // $volatile fp_0 := ( $slice fp_24 7 0 ) $buffering 1
    fpunit_exec_exec__find_left_24_assign_stmt_1740_c_macro_;
    // $volatile $call find_left_8 (fp_2 ) (pos_2 found_2 ) 
    fpunit_exec_exec__find_left_24_call_stmt_1744_c_macro_;
    // $volatile $call find_left_8 (fp_1 ) (pos_1 found_1 ) 
    fpunit_exec_exec__find_left_24_call_stmt_1748_c_macro_;
    // $volatile $call find_left_8 (fp_0 ) (pos_0 found_0 ) 
    fpunit_exec_exec__find_left_24_call_stmt_1752_c_macro_;
    // found := ((found_2 | found_1) | found_0) $buffering 1
    fpunit_exec_exec__find_left_24_assign_stmt_1759_c_macro_;
    // position := ( $mux found_2 ((ONE_1 && ZERO_1) && pos_2) ( $mux
    // found_1 ((ZERO_1 && ONE_1) && pos_1) ( $mux found_0 ((ZERO_1 &&
    // ZERO_1) && pos_0) 0 ) ) ) $buffering 1
    fpunit_exec_exec__find_left_24_assign_stmt_1783_c_macro_;
    fpunit_exec_exec__find_left_24_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__find_left_24_series_block_stmt_1725_c_mutex_);
}
void
_fpunit_exec_exec_find_left_32_(bit_vector * __pfp_32,
				bit_vector * __pposition,
				bit_vector * __pfound)
{
    MUTEX_DECL
	(fpunit_exec_exec__find_left_32_series_block_stmt_3122_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__find_left_32_series_block_stmt_3122_c_mutex_);
    fpunit_exec_exec__find_left_32_inner_inarg_prep_macro__;
    // $volatile fp_16_upper := ( $slice fp_32 31 16 ) $buffering 1
    fpunit_exec_exec__find_left_32_assign_stmt_3129_c_macro_;
    // $volatile fp_16_lower := ( $slice fp_32 15 0 ) $buffering 1
    fpunit_exec_exec__find_left_32_assign_stmt_3133_c_macro_;
    // $volatile $call find_left_16 (fp_16_upper ) (fp_16_upper_index
    // found_upper ) 
    fpunit_exec_exec__find_left_32_call_stmt_3137_c_macro_;
    // $volatile $call find_left_16 (fp_16_lower ) (fp_16_lower_index
    // found_lower ) 
    fpunit_exec_exec__find_left_32_call_stmt_3141_c_macro_;
    // $volatile position := ( $mux found_upper (ONE_1 &&
    // fp_16_upper_index) ( $mux found_lower (ZERO_1 && fp_16_lower_index) 
    // ZERO_5 ) ) $buffering 1
    fpunit_exec_exec__find_left_32_assign_stmt_3154_c_macro_;
    // $volatile found := (found_upper | found_lower) $buffering 1
    fpunit_exec_exec__find_left_32_assign_stmt_3159_c_macro_;
    fpunit_exec_exec__find_left_32_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__find_left_32_series_block_stmt_3122_c_mutex_);
}
void
_fpunit_exec_exec_find_left_4_(bit_vector * __pfp_4,
			       bit_vector * __pposition,
			       bit_vector * __pfound)
{
    MUTEX_DECL
	(fpunit_exec_exec__find_left_4_series_block_stmt_1638_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__find_left_4_series_block_stmt_1638_c_mutex_);
    fpunit_exec_exec__find_left_4_inner_inarg_prep_macro__;
    // $volatile x3 := ( $slice fp_4 3 3 ) $buffering 1
    fpunit_exec_exec__find_left_4_assign_stmt_1645_c_macro_;
    // $volatile x2 := ( $slice fp_4 2 2 ) $buffering 1
    fpunit_exec_exec__find_left_4_assign_stmt_1649_c_macro_;
    // $volatile x1 := ( $slice fp_4 1 1 ) $buffering 1
    fpunit_exec_exec__find_left_4_assign_stmt_1653_c_macro_;
    // $volatile x0 := ( $slice fp_4 0 0 ) $buffering 1
    fpunit_exec_exec__find_left_4_assign_stmt_1657_c_macro_;
    // $volatile found := ((x3 | x2) | (x1 | x0)) $buffering 1
    fpunit_exec_exec__find_left_4_assign_stmt_1666_c_macro_;
    // $volatile y1 := (x3 | x2) $buffering 1
    fpunit_exec_exec__find_left_4_assign_stmt_1671_c_macro_;
    // $volatile y0 := (x3 | (x1 & ( ~ x2 ))) $buffering 1
    fpunit_exec_exec__find_left_4_assign_stmt_1679_c_macro_;
    // $volatile position := (y1 && y0) $buffering 1
    fpunit_exec_exec__find_left_4_assign_stmt_1684_c_macro_;
    fpunit_exec_exec__find_left_4_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__find_left_4_series_block_stmt_1638_c_mutex_);
}
void
_fpunit_exec_exec_find_left_53_(bit_vector * __pfp_53,
				bit_vector * __pposition,
				bit_vector * __pfound)
{
    MUTEX_DECL
	(fpunit_exec_exec__find_left_53_series_block_stmt_1785_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__find_left_53_series_block_stmt_1785_c_mutex_);
    fpunit_exec_exec__find_left_53_inner_inarg_prep_macro__;
    // $volatile fp_3 := ( $slice fp_53 52 52 ) $buffering 1
    fpunit_exec_exec__find_left_53_assign_stmt_1792_c_macro_;
    // $volatile fp_2 := ( $slice fp_53 51 48 ) $buffering 1
    fpunit_exec_exec__find_left_53_assign_stmt_1796_c_macro_;
    // $volatile fp_1 := ( $slice fp_53 47 24 ) $buffering 1
    fpunit_exec_exec__find_left_53_assign_stmt_1800_c_macro_;
    // $volatile fp_0 := ( $slice fp_53 23 0 ) $buffering 1
    fpunit_exec_exec__find_left_53_assign_stmt_1804_c_macro_;
    // $volatile $call find_left_4 (fp_2 ) (pos_2 found_2 ) 
    fpunit_exec_exec__find_left_53_call_stmt_1808_c_macro_;
    // $volatile $call find_left_24 (fp_1 ) (pos_1 found_1 ) 
    fpunit_exec_exec__find_left_53_call_stmt_1812_c_macro_;
    // $volatile $call find_left_24 (fp_0 ) (pos_0 found_0 ) 
    fpunit_exec_exec__find_left_53_call_stmt_1816_c_macro_;
    // found := ((fp_3 | found_2) | (found_1 | found_0)) $buffering 1
    fpunit_exec_exec__find_left_53_assign_stmt_1825_c_macro_;
    // position := ( $mux fp_3 52 ( $mux found_2 (($bitcast ($uint<6>)
    // pos_2 ) + 48 ) ( $mux found_1 (($bitcast ($uint<6>) pos_1 ) + 24 )
    // ( $mux found_0 ($bitcast ($uint<6>) pos_0 ) 0 ) ) ) ) $buffering 1
    fpunit_exec_exec__find_left_53_assign_stmt_1847_c_macro_;
    fpunit_exec_exec__find_left_53_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__find_left_53_series_block_stmt_1785_c_mutex_);
}
void
_fpunit_exec_exec_find_left_8_(bit_vector * __pfp_8,
			       bit_vector * __pposition,
			       bit_vector * __pfound)
{
    MUTEX_DECL
	(fpunit_exec_exec__find_left_8_series_block_stmt_1686_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__find_left_8_series_block_stmt_1686_c_mutex_);
    fpunit_exec_exec__find_left_8_inner_inarg_prep_macro__;
    // $volatile fp_4_upper := ( $slice fp_8 7 4 ) $buffering 1
    fpunit_exec_exec__find_left_8_assign_stmt_1693_c_macro_;
    // $volatile fp_4_lower := ( $slice fp_8 3 0 ) $buffering 1
    fpunit_exec_exec__find_left_8_assign_stmt_1697_c_macro_;
    // $volatile $call find_left_4 (fp_4_upper ) (fp_4_upper_index
    // found_upper ) 
    fpunit_exec_exec__find_left_8_call_stmt_1701_c_macro_;
    // $volatile $call find_left_4 (fp_4_lower ) (fp_4_lower_index
    // found_lower ) 
    fpunit_exec_exec__find_left_8_call_stmt_1705_c_macro_;
    // $volatile position := ( $mux found_upper (ONE_1 &&
    // fp_4_upper_index) ( $mux found_lower (ZERO_1 && fp_4_lower_index)
    // ZERO_3 ) ) $buffering 1
    fpunit_exec_exec__find_left_8_assign_stmt_1718_c_macro_;
    // $volatile found := (found_upper | found_lower) $buffering 1
    fpunit_exec_exec__find_left_8_assign_stmt_1723_c_macro_;
    fpunit_exec_exec__find_left_8_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__find_left_8_series_block_stmt_1686_c_mutex_);
}
void
_fpunit_exec_exec_find_leftmost_35_(bit_vector * __pfp_35,
				    bit_vector * __pposition,
				    bit_vector * __pfound)
{
    MUTEX_DECL
	(fpunit_exec_exec__find_leftmost_35_series_block_stmt_11332_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__find_leftmost_35_series_block_stmt_11332_c_mutex_);
    fpunit_exec_exec__find_leftmost_35_inner_inarg_prep_macro__;
    // $volatile fp_3_upper := ( $slice fp_35 34 32 ) $buffering 1
    fpunit_exec_exec__find_leftmost_35_assign_stmt_11339_c_macro_;
    // fp_34 := ( $slice fp_3_upper 2 2 ) $buffering 1
    fpunit_exec_exec__find_leftmost_35_assign_stmt_11343_c_macro_;
    // fp_33 := ( $slice fp_3_upper 1 1 ) $buffering 1
    fpunit_exec_exec__find_leftmost_35_assign_stmt_11347_c_macro_;
    // found_upper := (fp_3_upper != 0 ) $buffering 1
    fpunit_exec_exec__find_leftmost_35_assign_stmt_11352_c_macro_;
    // fp_upper_index := ( $mux fp_34 ($bitcast ($uint<6>) _b100010 ) (
    // $mux fp_33 ($bitcast ($uint<6>) _b100001 ) ($bitcast ($uint<6>)
    // _b100000 ) ) ) $buffering 1
    fpunit_exec_exec__find_leftmost_35_assign_stmt_11364_c_macro_;
    // $volatile fp_32_lower := ( $slice fp_35 31 0 ) $buffering 1
    fpunit_exec_exec__find_leftmost_35_assign_stmt_11368_c_macro_;
    // $volatile $call find_left_32 (fp_32_lower ) (fp_32_lower_index
    // found_lower ) 
    fpunit_exec_exec__find_leftmost_35_call_stmt_11372_c_macro_;
    // $volatile position := ( $mux found_upper fp_upper_index ( $mux
    // found_lower (ZERO_1 && fp_32_lower_index) ZERO_6 ) ) $buffering 1
    fpunit_exec_exec__find_leftmost_35_assign_stmt_11383_c_macro_;
    // $volatile found := (found_upper | found_lower) $buffering 1
    fpunit_exec_exec__find_leftmost_35_assign_stmt_11388_c_macro_;
    fpunit_exec_exec__find_leftmost_35_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__find_leftmost_35_series_block_stmt_11332_c_mutex_);
}
void
_fpunit_exec_exec_find_leftmost_64_(bit_vector * __pfp_64,
				    bit_vector * __pposition,
				    bit_vector * __pfound)
{
    MUTEX_DECL
	(fpunit_exec_exec__find_leftmost_64_series_block_stmt_3161_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__find_leftmost_64_series_block_stmt_3161_c_mutex_);
    fpunit_exec_exec__find_leftmost_64_inner_inarg_prep_macro__;
    // $volatile fp_32_upper := ( $slice fp_64 63 32 ) $buffering 1
    fpunit_exec_exec__find_leftmost_64_assign_stmt_3168_c_macro_;
    // $volatile fp_32_lower := ( $slice fp_64 31 0 ) $buffering 1
    fpunit_exec_exec__find_leftmost_64_assign_stmt_3172_c_macro_;
    // $volatile $call find_left_32 (fp_32_upper ) (fp_32_upper_index
    // found_upper ) 
    fpunit_exec_exec__find_leftmost_64_call_stmt_3176_c_macro_;
    // $volatile $call find_left_32 (fp_32_lower ) (fp_32_lower_index
    // found_lower ) 
    fpunit_exec_exec__find_leftmost_64_call_stmt_3180_c_macro_;
    // $volatile position := ( $mux found_upper (ONE_1 &&
    // fp_32_upper_index) ( $mux found_lower (ZERO_1 && fp_32_lower_index) 
    // ZERO_6 ) ) $buffering 1
    fpunit_exec_exec__find_leftmost_64_assign_stmt_3193_c_macro_;
    // $volatile found := (found_upper | found_lower) $buffering 1
    fpunit_exec_exec__find_leftmost_64_assign_stmt_3198_c_macro_;
    fpunit_exec_exec__find_leftmost_64_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__find_leftmost_64_series_block_stmt_3161_c_mutex_);
}
void
_fpunit_exec_exec_fitod64_(bit_vector * __pX, double *__pY)
{
    MUTEX_DECL(fpunit_exec_exec__fitod64_series_block_stmt_13376_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__fitod64_series_block_stmt_13376_c_mutex_);
    fpunit_exec_exec__fitod64_inner_inarg_prep_macro__;
    // $volatile S := (X [] 31 ) $buffering 1
    fpunit_exec_exec__fitod64_assign_stmt_13383_c_macro_;
    // $volatile notX := ( ~ X ) $buffering 1
    fpunit_exec_exec__fitod64_assign_stmt_13387_c_macro_;
    // $volatile $call increment_32 (notX ) (twosComplX ) 
    fpunit_exec_exec__fitod64_call_stmt_13390_c_macro_;
    // $volatile iX := ( $mux S twosComplX X ) $buffering 1
    fpunit_exec_exec__fitod64_assign_stmt_13396_c_macro_;
    // $volatile $call find_left_32 (iX ) (idx_raw found ) 
    fpunit_exec_exec__fitod64_call_stmt_13400_c_macro_;
    // $volatile exponent := ((ZERO_1 && ( ~ ZERO_10 )) + ($bitcast
    // ($uint<11>) idx_raw )) $buffering 1
    fpunit_exec_exec__fitod64_assign_stmt_13409_c_macro_;
    // $volatile ls_amount := (32 - ($bitcast ($uint<6>) idx_raw ))
    // $buffering 1
    fpunit_exec_exec__fitod64_assign_stmt_13415_c_macro_;
    // $volatile $call i32_sll (iX ls_amount ) (ix_shifted ) 
    fpunit_exec_exec__fitod64_call_stmt_13419_c_macro_;
    // $volatile mantissa := (ix_shifted && ZERO_20) $buffering 1
    fpunit_exec_exec__fitod64_assign_stmt_13424_c_macro_;
    // $volatile uY := ( $mux found ((S && exponent) && mantissa) ZERO_64
    // ) $buffering 1
    fpunit_exec_exec__fitod64_assign_stmt_13434_c_macro_;
    // $volatile Y := ($bitcast ($float<11,52>) uY ) $buffering 2
    fpunit_exec_exec__fitod64_assign_stmt_13438_c_macro_;
    fpunit_exec_exec__fitod64_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fitod64_series_block_stmt_13376_c_mutex_);
}
void
fpunit_exec_exec_fitod64(uint32_t X, double *Y)
{
    double          __Y;
    fpunit_exec_exec__fitod64_outer_arg_decl_macro__;
    _fpunit_exec_exec_fitod64_(&__X, &__Y);
    fpunit_exec_exec__fitod64_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fitod64_wrap_(bit_vector * __pX, double *__pY)
{
    MUTEX_DECL
	(fpunit_exec_exec__fitod64_wrap_series_block_stmt_18447_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fitod64_wrap_series_block_stmt_18447_c_mutex_);
    fpunit_exec_exec__fitod64_wrap_inner_inarg_prep_macro__;
    // $volatile $call fitod64 (X ) (uY ) 
    fpunit_exec_exec__fitod64_wrap_call_stmt_18452_c_macro_;
    // Y := uY $buffering 1// bits of buffering = 64. 
    fpunit_exec_exec__fitod64_wrap_assign_stmt_18455_c_macro_;
    fpunit_exec_exec__fitod64_wrap_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fitod64_wrap_series_block_stmt_18447_c_mutex_);
}
void
fpunit_exec_exec_fitod64_wrap(uint32_t X, double *Y)
{
    double          __Y;
    fpunit_exec_exec__fitod64_wrap_outer_arg_decl_macro__;
    _fpunit_exec_exec_fitod64_wrap_(&__X, &__Y);
    fpunit_exec_exec__fitod64_wrap_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fitos32_wrap_(bit_vector * __pX, float *__pY)
{
    MUTEX_DECL
	(fpunit_exec_exec__fitos32_wrap_series_block_stmt_18457_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fitos32_wrap_series_block_stmt_18457_c_mutex_);
    fpunit_exec_exec__fitos32_wrap_inner_inarg_prep_macro__;
    // $volatile $call fitod64 (X ) (dY ) 
    fpunit_exec_exec__fitos32_wrap_call_stmt_18462_c_macro_;
    // $call DoubleToSingle (dY ) (denorm_dY extn_dY ) 
    fpunit_exec_exec__fitos32_wrap_call_stmt_18466_c_macro_;
    // $volatile $call round_fp_32 (extn_dY ) (rY ) 
    fpunit_exec_exec__fitos32_wrap_call_stmt_18469_c_macro_;
    // $guard (denorm_dY) $call denormalize_fp_32 (extn_dY ) (nrY ) 
    fpunit_exec_exec__fitos32_wrap_call_stmt_18473_c_macro_;
    // Y := ($bitcast ($float<8,23>) ( $mux denorm_dY nrY rY ) )
    // $buffering 1// bits of buffering = 32. 
    fpunit_exec_exec__fitos32_wrap_assign_stmt_18480_c_macro_;
    fpunit_exec_exec__fitos32_wrap_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fitos32_wrap_series_block_stmt_18457_c_mutex_);
}
void
fpunit_exec_exec_fitos32_wrap(uint32_t X, float *Y)
{
    float           __Y;
    fpunit_exec_exec__fitos32_wrap_outer_arg_decl_macro__;
    _fpunit_exec_exec_fitos32_wrap_(&__X, &__Y);
    fpunit_exec_exec__fitos32_wrap_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fmul16_(bit_vector * __pf1, bit_vector * __pf2,
			  bit_vector * __presult)
{
    MUTEX_DECL(fpunit_exec_exec__fmul16_series_block_stmt_13931_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__fmul16_series_block_stmt_13931_c_mutex_);
    fpunit_exec_exec__fmul16_inner_inarg_prep_macro__;
    // $volatile $call classifyFp16 (f1 ) (f1_zero f1_normal f1_nan f1_inf 
    // ) 
    fpunit_exec_exec__fmul16_call_stmt_13940_c_macro_;
    // $volatile $call classifyFp16 (f2 ) (f2_zero f2_normal f2_nan f2_inf 
    // ) 
    fpunit_exec_exec__fmul16_call_stmt_13946_c_macro_;
    // $volatile sign_f1 := ( $slice f1 15 15 ) $buffering 1
    fpunit_exec_exec__fmul16_assign_stmt_13950_c_macro_;
    // $volatile f1_exp_biased := ( $slice f1 14 10 ) $buffering 1
    fpunit_exec_exec__fmul16_assign_stmt_13954_c_macro_;
    // $volatile f1_fraction := ( $slice f1 9 0 ) $buffering 1
    fpunit_exec_exec__fmul16_assign_stmt_13958_c_macro_;
    // $volatile exp_a := (($bitcast ($int<7>) f1_exp_biased ) - 15 )
    // $buffering 1
    fpunit_exec_exec__fmul16_assign_stmt_13964_c_macro_;
    // $volatile sign_f2 := ( $slice f2 15 15 ) $buffering 1
    fpunit_exec_exec__fmul16_assign_stmt_13968_c_macro_;
    // $volatile f2_exp_biased := ( $slice f2 14 10 ) $buffering 1
    fpunit_exec_exec__fmul16_assign_stmt_13972_c_macro_;
    // $volatile f2_fraction := ( $slice f2 9 0 ) $buffering 1
    fpunit_exec_exec__fmul16_assign_stmt_13976_c_macro_;
    // $volatile exp_b := (($bitcast ($int<7>) f2_exp_biased ) - 15 )
    // $buffering 1
    fpunit_exec_exec__fmul16_assign_stmt_13982_c_macro_;
    // $volatile exp_ab := (exp_a + exp_b) $buffering 1
    fpunit_exec_exec__fmul16_assign_stmt_13987_c_macro_;
    // $volatile sign_result := (sign_f1 ^ sign_f2) $buffering 1
    fpunit_exec_exec__fmul16_assign_stmt_13992_c_macro_;
    // $volatile f1_frac := (ONE_1 && f1_fraction) $buffering 1
    fpunit_exec_exec__fmul16_assign_stmt_13997_c_macro_;
    // $volatile f2_frac := (ONE_1 && f2_fraction) $buffering 1
    fpunit_exec_exec__fmul16_assign_stmt_14002_c_macro_;
    // frac_result_ext := (($bitcast ($uint<22>) f1_frac ) * ($bitcast
    // ($uint<22>) f2_frac )) $buffering 1
    fpunit_exec_exec__fmul16_assign_stmt_14009_c_macro_;
    // $volatile shift_by_one := (frac_result_ext [] 21 ) $buffering 1
    fpunit_exec_exec__fmul16_assign_stmt_14014_c_macro_;
    // $volatile frac_result := ( $mux shift_by_one ( $slice
    // frac_result_ext 20 11 ) ( $slice frac_result_ext 19 10 ) )
    // $buffering 1
    fpunit_exec_exec__fmul16_assign_stmt_14022_c_macro_;
    // $volatile adjusted_exponent := ( $mux shift_by_one (exp_ab + 1 )
    // exp_ab ) $buffering 1
    fpunit_exec_exec__fmul16_assign_stmt_14030_c_macro_;
    // $volatile exponent_result := ($bitcast ($uint<5>)
    // (adjusted_exponent + 15 ) ) $buffering 1
    fpunit_exec_exec__fmul16_assign_stmt_14036_c_macro_;
    // $volatile $call check_fh_exponent_overflow (adjusted_exponent )
    // (overflow underflow ) 
    fpunit_exec_exec__fmul16_call_stmt_14040_c_macro_;
    // result := ( $mux ((f1_inf | f2_inf) | overflow) ( $call getHalfInf
    // (sign_result ) ) ( $mux (f1_nan | f2_nan) ( $call getHalfNan
    // (sign_result ) ) ( $mux (f1_zero | underflow) ( $call getHalfZero
    // (sign_result ) ) ((sign_result && exponent_result) && frac_result)
    // ) ) ) $buffering 1
    fpunit_exec_exec__fmul16_assign_stmt_14067_c_macro_;
    fpunit_exec_exec__fmul16_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fmul16_series_block_stmt_13931_c_mutex_);
}
void
fpunit_exec_exec_fmul16(uint16_t f1, uint16_t f2, uint16_t * result)
{
    fpunit_exec_exec__fmul16_outer_arg_decl_macro__;
    _fpunit_exec_exec_fmul16_(&__f1, &__f2, &__result);
    fpunit_exec_exec__fmul16_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fmul16_wrap_(bit_vector * __pf1, bit_vector * __pf2,
			       bit_vector * __presult)
{
    MUTEX_DECL
	(fpunit_exec_exec__fmul16_wrap_series_block_stmt_18482_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fmul16_wrap_series_block_stmt_18482_c_mutex_);
    fpunit_exec_exec__fmul16_wrap_inner_inarg_prep_macro__;
    // $volatile $call fmul16 (f1 f2 ) (result ) 
    fpunit_exec_exec__fmul16_wrap_call_stmt_18489_c_macro_;
    fpunit_exec_exec__fmul16_wrap_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fmul16_wrap_series_block_stmt_18482_c_mutex_);
}
void
fpunit_exec_exec_fmul16_wrap(uint16_t f1, uint16_t f2, uint16_t * result)
{
    fpunit_exec_exec__fmul16_wrap_outer_arg_decl_macro__;
    _fpunit_exec_exec_fmul16_wrap_(&__f1, &__f2, &__result);
    fpunit_exec_exec__fmul16_wrap_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fnegs_64_(double *__pf, double *__pnf)
{
    MUTEX_DECL
	(fpunit_exec_exec__fnegs_64_series_block_stmt_18491_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fnegs_64_series_block_stmt_18491_c_mutex_);
    fpunit_exec_exec__fnegs_64_inner_inarg_prep_macro__;
    // uf := ($bitcast ($uint<64>) f ) $buffering 1
    fpunit_exec_exec__fnegs_64_assign_stmt_18497_c_macro_;
    // nuf := (( ~ (uf [] 63 ) ) && ( $slice uf 62 0 ) ) $buffering 1
    fpunit_exec_exec__fnegs_64_assign_stmt_18506_c_macro_;
    // nf := ($bitcast ($float<11,52>) nuf ) $buffering 1
    fpunit_exec_exec__fnegs_64_assign_stmt_18510_c_macro_;
    fpunit_exec_exec__fnegs_64_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fnegs_64_series_block_stmt_18491_c_mutex_);
}
void
fpunit_exec_exec_fnegs_64(double f, double *nf)
{
    double          __nf;
    fpunit_exec_exec__fnegs_64_outer_arg_decl_macro__;
    _fpunit_exec_exec_fnegs_64_(&__f, &__nf);
    fpunit_exec_exec__fnegs_64_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fpadd32_op_(bit_vector * __puf1_s,
			      bit_vector * __pf1_s_class,
			      bit_vector * __puf2_s,
			      bit_vector * __pf2_s_class,
			      bit_vector * __pneeds_norm,
			      bit_vector * __pextn_result)
{
    MUTEX_DECL
	(fpunit_exec_exec__fpadd32_op_series_block_stmt_11461_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fpadd32_op_series_block_stmt_11461_c_mutex_);
    fpunit_exec_exec__fpadd32_op_inner_inarg_prep_macro__;
    // $volatile $call SingleToExtendedFp (uf1_s f1_s_class ) (uf1_s_efp ) 
    // 
    fpunit_exec_exec__fpadd32_op_call_stmt_11471_c_macro_;
    // $volatile $call SingleToExtendedFp (uf2_s f2_s_class ) (uf2_s_efp ) 
    // 
    fpunit_exec_exec__fpadd32_op_call_stmt_11475_c_macro_;
    // $volatile sign_uf1_d := ( $slice uf1_s_efp 66 66 ) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11479_c_macro_;
    // $volatile f1_exp13_unbiased := ( $slice uf1_s_efp 65 53 )
    // $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11483_c_macro_;
    // $volatile f1_top_bit := ( $slice uf1_s_efp 52 52 ) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11487_c_macro_;
    // $volatile f1_fraction := ( $slice uf1_s_efp 51 29 ) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11491_c_macro_;
    // $volatile sign_uf2_d := ( $slice uf2_s_efp 66 66 ) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11495_c_macro_;
    // $volatile f2_exp13_unbiased := ( $slice uf2_s_efp 65 53 )
    // $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11499_c_macro_;
    // $volatile f2_top_bit := ( $slice uf2_s_efp 52 52 ) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11503_c_macro_;
    // $volatile f2_fraction := ( $slice uf2_s_efp 51 29 ) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11507_c_macro_;
    // $volatile $call classify_utility (ONE_1 f1_s_class _b0 ) (f1_zero
    // f1_normal f1_denormal f1_nan f1_inf f1_pos_inf f1_neg_inf ) 
    fpunit_exec_exec__fpadd32_op_call_stmt_11518_c_macro_;
    // $volatile $call classify_utility (ONE_1 f2_s_class _b0 ) (f2_zero
    // f2_normal f2_denormal f2_nan f2_inf f2_pos_inf f2_neg_inf ) 
    fpunit_exec_exec__fpadd32_op_call_stmt_11529_c_macro_;
    // $volatile f1_frac := (f1_top_bit && f1_fraction) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11534_c_macro_;
    // $volatile f2_frac := (f2_top_bit && f2_fraction) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11539_c_macro_;
    // $report (fpunit_exec fpadd32_op_fractions f1_frac f1_frac f2_frac
    // f2_frac )
    fpunit_exec_exec__fpadd32_op_stmt_11542_c_macro_;
    // $volatile exp_a := ($bitcast ($int<13>) f1_exp13_unbiased )
    // $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11546_c_macro_;
    // $volatile exp_b := ($bitcast ($int<13>) f2_exp13_unbiased )
    // $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11550_c_macro_;
    // $volatile $call expDiffSingle (uf1_s uf2_s )
    // (exp_a_greater_than_exp_b exp_a_equal_exp_b exp_ab ) 
    fpunit_exec_exec__fpadd32_op_call_stmt_11556_c_macro_;
    // $report (fpunit_exec fpadd32_op_exponents exp_a exp_a exp_b exp_b
    // exp_a_greater_than_exp_b exp_a_greater_than_exp_b exp_a_equal_exp_b 
    // exp_a_equal_exp_b )
    fpunit_exec_exec__fpadd32_op_stmt_11561_c_macro_;
    // $volatile mantissa_a_pre_shift_35 := ((ZERO_1 && f1_frac) &&
    // ZERO_10) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11568_c_macro_;
    // $volatile mantissa_b_pre_shift_35 := ((ZERO_1 && f2_frac) &&
    // ZERO_10) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11575_c_macro_;
    // $volatile to_be_shifted_35 := ( $mux exp_a_greater_than_exp_b
    // mantissa_b_pre_shift_35 mantissa_a_pre_shift_35 ) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11581_c_macro_;
    // $volatile exp_ab_6 := ( $mux (exp_ab > 35 ) ($bitcast ($uint<6>) 35 
    // ) ($bitcast ($uint<6>) exp_ab ) ) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11591_c_macro_;
    // $volatile $call u35_sr_special (to_be_shifted_35 exp_ab_6 )
    // (shifted_output_temp_35 sticky_temp ) 
    fpunit_exec_exec__fpadd32_op_call_stmt_11596_c_macro_;
    // $volatile shifted_output_35 := ( $mux ( ~ exp_a_equal_exp_b )
    // shifted_output_temp_35 ($bitcast ($uint<35>) _b0 ) ) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11604_c_macro_;
    // $volatile mantissa_a_post_shift_35 := ( $mux
    // (exp_a_greater_than_exp_b | exp_a_equal_exp_b)
    // mantissa_a_pre_shift_35 shifted_output_35 ) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11612_c_macro_;
    // $volatile mantissa_b_post_shift_35 := ( $mux
    // exp_a_greater_than_exp_b shifted_output_35 mantissa_b_pre_shift_35
    // ) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11618_c_macro_;
    // $volatile exponent_post_align := ( $mux exp_a_greater_than_exp_b
    // exp_a exp_b ) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11624_c_macro_;
    // $report (fpunit_exec fpadd32_op_post_shift mantissa_a_post_shift_35 
    // mantissa_a_post_shift_35 mantissa_b_post_shift_35
    // mantissa_b_post_shift_35 exponent_post_align exponent_post_align )
    fpunit_exec_exec__fpadd32_op_stmt_11628_c_macro_;
    // $volatile $call compare24 (f1_frac f2_frac ) (G E ) 
    fpunit_exec_exec__fpadd32_op_call_stmt_11633_c_macro_;
    // $volatile a_frac_ge_b_frac := ( $mux exp_a_equal_exp_b (G | E)
    // exp_a_greater_than_exp_b ) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11641_c_macro_;
    // $volatile need_to_take_twos_complement_a := (((sign_uf1_d & ( ~
    // sign_uf2_d )) & ( ~ a_frac_ge_b_frac )) | ((( ~ sign_uf1_d ) &
    // sign_uf2_d) & ( ~ a_frac_ge_b_frac ))) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11658_c_macro_;
    // $volatile need_to_take_twos_complement_b := (((sign_uf2_d & ( ~
    // sign_uf1_d )) & a_frac_ge_b_frac) | ((( ~ sign_uf2_d ) &
    // sign_uf1_d) & a_frac_ge_b_frac)) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11673_c_macro_;
    // $volatile carry_in := (need_to_take_twos_complement_a |
    // need_to_take_twos_complement_b) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11678_c_macro_;
    // $volatile mantissa_operand_a_35 := ( $mux
    // need_to_take_twos_complement_a ( ~ mantissa_a_post_shift_35 )
    // mantissa_a_post_shift_35 ) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11685_c_macro_;
    // $volatile mantissa_operand_b_35 := ( $mux
    // need_to_take_twos_complement_b ( ~ mantissa_b_post_shift_35 )
    // mantissa_b_post_shift_35 ) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11692_c_macro_;
    // $volatile $call adder_35_with_carry (mantissa_operand_a_35
    // mantissa_operand_b_35 carry_in ) (mantissa_added_35 carry_out ) 
    fpunit_exec_exec__fpadd32_op_call_stmt_11698_c_macro_;
    // $volatile sign_result := (((sign_uf1_d & sign_uf2_d) | ((sign_uf1_d 
    // & ( ~ sign_uf2_d )) & a_frac_ge_b_frac)) | ((( ~ sign_uf1_d ) &
    // sign_uf2_d) & ( ~ a_frac_ge_b_frac ))) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11718_c_macro_;
    // $report (fpunit_exec fpadd32_op_mantissa_added
    // mantissa_operand_a_35 mantissa_operand_a_35 mantissa_operand_b_35
    // mantissa_operand_b_35 carry_in carry_in mantissa_added_35
    // mantissa_added_35 carry_out carry_out sign_result sign_result )
    fpunit_exec_exec__fpadd32_op_stmt_11725_c_macro_;
    // $volatile mantissa_out_35 := mantissa_added_35 $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11728_c_macro_;
    // $volatile need_to_shift := (( ~ carry_in ) & (mantissa_out_35 [] 34 
    // )) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11736_c_macro_;
    // $volatile mantissa_out_shifted_34 := ( $slice mantissa_out_35 34 1
    // ) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11740_c_macro_;
    // $volatile mantissa_35_bits := ( $mux need_to_shift (ZERO_1 &&
    // mantissa_out_shifted_34) (ZERO_1 && ( $slice mantissa_out_35 33 0 ) 
    // ) ) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11751_c_macro_;
    // $report (fpunit_exec fpadd32_op_final_mantissa_35 mantissa_35_bits
    // mantissa_35_bits )
    fpunit_exec_exec__fpadd32_op_stmt_11753_c_macro_;
    // $volatile $call find_leftmost_35 (mantissa_35_bits )
    // (position_of_one one_found ) 
    fpunit_exec_exec__fpadd32_op_call_stmt_11757_c_macro_;
    // $volatile left_shift_amount := ($bitcast ($uint<6>) (33 -
    // position_of_one) ) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11763_c_macro_;
    // $volatile add_result_zero := ( ~ one_found ) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11767_c_macro_;
    // $volatile $call i35_sll (mantissa_35_bits left_shift_amount )
    // (final_mantissa_aligned_35 ) 
    fpunit_exec_exec__fpadd32_op_call_stmt_11771_c_macro_;
    // $volatile final_mantissa_33_aligned := ( $slice
    // final_mantissa_aligned_35 32 0 ) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11775_c_macro_;
    // $volatile final_mantissa_62_aligned := (final_mantissa_33_aligned
    // && ($bitcast ($uint<29>) _b0 )) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11781_c_macro_;
    // $volatile exponent_correction := (( $mux need_to_shift exp_base_1
    // exp_base_0 ) - ( $mux one_found ($bitcast ($int<13>)
    // left_shift_amount ) _b0 ) ) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11793_c_macro_;
    // $volatile final_exponent_without_bias := (exponent_post_align +
    // exponent_correction) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11798_c_macro_;
    // $report (fpunit_exec fpadd32_op_final_exponent_without_bias
    // exponent_post_align exponent_post_align exponent_correction
    // exponent_correction final_exponent_without_bias
    // final_exponent_without_bias )
    fpunit_exec_exec__fpadd32_op_stmt_11802_c_macro_;
    // $volatile SP_exp_overflow := (final_exponent_without_bias > 127 )
    // $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11807_c_macro_;
    // $volatile SP_exp_underflow := (final_exponent_without_bias < -126 ) 
    // $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11812_c_macro_;
    // $volatile underflow_SP := (SP_exp_underflow & ( ~ add_result_zero
    // )) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11818_c_macro_;
    // $volatile overflow_SP := (SP_exp_overflow & ( ~ add_result_zero ))
    // $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11824_c_macro_;
    // $volatile overflow := overflow_SP $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11827_c_macro_;
    // $volatile condition_nan := ((f1_nan | f2_nan) | ((f1_pos_inf &
    // f2_neg_inf) | (f1_neg_inf & f2_pos_inf))) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11840_c_macro_;
    // $volatile condition_inf := (((f1_pos_inf & f2_pos_inf) |
    // (f1_neg_inf & f2_neg_inf)) | overflow) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11851_c_macro_;
    // $volatile condition_zero := ((f1_zero & f2_zero) | add_result_zero) 
    // $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11858_c_macro_;
    // $volatile underflow := (( ~ condition_zero ) & underflow_SP)
    // $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11864_c_macro_;
    // $report (fpunit_exec fpadd32_op_final_exceptions SP_exp_overflow
    // SP_exp_overflow SP_exp_underflow SP_exp_underflow underflow_SP
    // underflow_SP overflow_SP overflow_SP condition_nan condition_nan
    // condition_inf condition_inf condition_zero condition_zero )
    fpunit_exec_exec__fpadd32_op_stmt_11872_c_macro_;
    // $volatile SP_nothing_to_be_done_condition_normal := (((( ~ overflow 
    // ) & ( ~ underflow )) & ( ~ condition_zero )) & (( ~ condition_inf ) 
    // & ( ~ condition_nan ))) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11888_c_macro_;
    // $volatile SP_normalization_required := (((overflow | underflow) & ( 
    // ~ condition_zero )) & (( ~ condition_inf ) & ( ~ condition_nan )))
    // $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11902_c_macro_;
    // $volatile normalization_required := SP_normalization_required
    // $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11905_c_macro_;
    // $volatile nothing_to_be_done_condition_normal :=
    // SP_nothing_to_be_done_condition_normal $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11908_c_macro_;
    // $volatile exponent_to_be_passed := (((( $mux condition_nan
    // ALL_ONE_13 _b0 ) | ( $mux condition_inf ALL_ONE_13 _b0 ) ) | ( $mux 
    // condition_zero ($bitcast ($int<13>) ZERO_13 ) _b0 ) ) | (( $mux
    // nothing_to_be_done_condition_normal final_exponent_without_bias _b0 
    // ) | ( $mux normalization_required final_exponent_without_bias _b0 ) 
    // )) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11935_c_macro_;
    // $volatile mantissa_to_be_passed := ((( $mux condition_nan (ONE_1 && 
    // ZERO_61) _b0 ) | ( $mux (condition_inf | condition_zero) ZERO_62
    // _b0 ) ) | ( $mux (nothing_to_be_done_condition_normal |
    // normalization_required) final_mantissa_62_aligned _b0 ) )
    // $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11957_c_macro_;
    // $volatile a_was_shifted := ( ~ exp_a_greater_than_exp_b )
    // $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11961_c_macro_;
    // $volatile a_negative := need_to_take_twos_complement_a $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11964_c_macro_;
    // $volatile b_was_shifted := exp_a_greater_than_exp_b $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11967_c_macro_;
    // $volatile b_negative := need_to_take_twos_complement_b $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11970_c_macro_;
    // $volatile condition_to_pass_sticky_bit := ((((a_was_shifted &
    // a_negative) & b_negative) | ((a_was_shifted & ( ~ a_negative )) & ( 
    // ~ b_negative ))) | (((b_was_shifted & a_negative) & b_negative) |
    // ((b_was_shifted & ( ~ a_negative )) & ( ~ b_negative ))))
    // $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_11999_c_macro_;
    // $volatile sticky := (((sticky_temp & condition_to_pass_sticky_bit)
    // & ( ~ condition_zero )) & (( ~ condition_inf ) & ( ~ condition_nan
    // ))) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_12013_c_macro_;
    // $volatile apply_sticky_correction := (sticky_temp & ((a_was_shifted 
    // & a_negative) | (b_was_shifted & b_negative))) $buffering 1
    fpunit_exec_exec__fpadd32_op_assign_stmt_12024_c_macro_;
    // needs_norm := ((normalization_required & ( ~ condition_zero )) & (( 
    // ~ condition_inf ) & ( ~ condition_nan ))) $buffering 2// bits of
    // buffering = 2. 
    fpunit_exec_exec__fpadd32_op_assign_stmt_12036_c_macro_;
    // extn_result := (((sticky && apply_sticky_correction) &&
    // (sign_result && condition_nan)) && ((condition_inf &&
    // condition_zero) && (($bitcast ($uint<13>) exponent_to_be_passed )
    // && mantissa_to_be_passed))) $buffering 2// bits of buffering = 162. 
    // 
    fpunit_exec_exec__fpadd32_op_assign_stmt_12054_c_macro_;
    // $report (fpunit_exec fpadd32_op_final_results exponent_to_be_passed 
    // exponent_to_be_passed mantissa_to_be_passed mantissa_to_be_passed )
    fpunit_exec_exec__fpadd32_op_stmt_12057_c_macro_;
    fpunit_exec_exec__fpadd32_op_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fpadd32_op_series_block_stmt_11461_c_mutex_);
}
void
_fpunit_exec_exec_fpadd32_wrap_(float *__pX, float *__pY, float *__pRESULT)
{
    MUTEX_DECL
	(fpunit_exec_exec__fpadd32_wrap_series_block_stmt_18512_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fpadd32_wrap_series_block_stmt_18512_c_mutex_);
    fpunit_exec_exec__fpadd32_wrap_inner_inarg_prep_macro__;
    // $volatile $call classFp32 (X ) (xpn xnn xpd xnd xqnan xsnan xpi xni 
    // xpz xnz ) 
    fpunit_exec_exec__fpadd32_wrap_call_stmt_18527_c_macro_;
    // x_class := ((((xpn && xnn) && xpd) && (xnd && xqnan)) && (((xsnan
    // && xpi) && xni) && (xpz && xnz))) $buffering 1// bits of buffering
    // = 10. 
    fpunit_exec_exec__fpadd32_wrap_assign_stmt_18548_c_macro_;
    // $volatile $call classFp32 (Y ) (ypn ynn ypd ynd yqnan ysnan ypi yni 
    // ypz ynz ) 
    fpunit_exec_exec__fpadd32_wrap_call_stmt_18560_c_macro_;
    // y_class := ((((ypn && ynn) && ypd) && (ynd && yqnan)) && (((ysnan
    // && ypi) && yni) && (ypz && ynz))) $buffering 1// bits of buffering
    // = 10. 
    fpunit_exec_exec__fpadd32_wrap_assign_stmt_18581_c_macro_;
    // $call fpadd64_op (ONE_1 ZERO_1 ($bitcast ($uint<32>) X ) x_class
    // ($bitcast ($uint<32>) Y ) y_class _b0 _b0 _b0 _b0 )
    // (denormalize_flag_add extn_result_add ) 
    fpunit_exec_exec__fpadd32_wrap_call_stmt_18596_c_macro_;
    // $volatile $call round_fp_32 (extn_result_add ) (adds_result_fast ) 
    fpunit_exec_exec__fpadd32_wrap_call_stmt_18599_c_macro_;
    // $guard (denormalize_flag_add) $call denormalize_fp_32
    // (extn_result_add ) (adds_result_slow ) 
    fpunit_exec_exec__fpadd32_wrap_call_stmt_18603_c_macro_;
    // $volatile RESULT := ($bitcast ($float<8,23>) ( $mux
    // denormalize_flag_add adds_result_slow adds_result_fast ) )
    // $buffering 1
    fpunit_exec_exec__fpadd32_wrap_assign_stmt_18610_c_macro_;
    fpunit_exec_exec__fpadd32_wrap_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fpadd32_wrap_series_block_stmt_18512_c_mutex_);
}
void
fpunit_exec_exec_fpadd32_wrap(float X, float Y, float *RESULT)
{
    float           __RESULT;
    fpunit_exec_exec__fpadd32_wrap_outer_arg_decl_macro__;
    _fpunit_exec_exec_fpadd32_wrap_(&__X, &__Y, &__RESULT);
    fpunit_exec_exec__fpadd32_wrap_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fpadd32_wrap_new_(float *__pX, float *__pY,
				    float *__pRESULT)
{
    MUTEX_DECL
	(fpunit_exec_exec__fpadd32_wrap_new_series_block_stmt_18612_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fpadd32_wrap_new_series_block_stmt_18612_c_mutex_);
    fpunit_exec_exec__fpadd32_wrap_new_inner_inarg_prep_macro__;
    // $volatile $call classFp32 (X ) (xpn xnn xpd xnd xqnan xsnan xpi xni 
    // xpz xnz ) 
    fpunit_exec_exec__fpadd32_wrap_new_call_stmt_18627_c_macro_;
    // x_class := ((((xpn && xnn) && xpd) && (xnd && xqnan)) && (((xsnan
    // && xpi) && xni) && (xpz && xnz))) $buffering 1// bits of buffering
    // = 10. 
    fpunit_exec_exec__fpadd32_wrap_new_assign_stmt_18648_c_macro_;
    // $volatile $call classFp32 (Y ) (ypn ynn ypd ynd yqnan ysnan ypi yni 
    // ypz ynz ) 
    fpunit_exec_exec__fpadd32_wrap_new_call_stmt_18660_c_macro_;
    // y_class := ((((ypn && ynn) && ypd) && (ynd && yqnan)) && (((ysnan
    // && ypi) && yni) && (ypz && ynz))) $buffering 1// bits of buffering
    // = 10. 
    fpunit_exec_exec__fpadd32_wrap_new_assign_stmt_18681_c_macro_;
    // $call fpadd32_op (($bitcast ($uint<32>) X ) x_class ($bitcast
    // ($uint<32>) Y ) y_class ) (denormalize_flag_add extn_result_add ) 
    fpunit_exec_exec__fpadd32_wrap_new_call_stmt_18690_c_macro_;
    // $volatile $call round_fp_32 (extn_result_add ) (adds_result_fast ) 
    fpunit_exec_exec__fpadd32_wrap_new_call_stmt_18693_c_macro_;
    // $guard (denormalize_flag_add) $call denormalize_fp_32
    // (extn_result_add ) (adds_result_slow ) 
    fpunit_exec_exec__fpadd32_wrap_new_call_stmt_18697_c_macro_;
    // $volatile RESULT := ($bitcast ($float<8,23>) ( $mux
    // denormalize_flag_add adds_result_slow adds_result_fast ) )
    // $buffering 1
    fpunit_exec_exec__fpadd32_wrap_new_assign_stmt_18704_c_macro_;
    fpunit_exec_exec__fpadd32_wrap_new_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fpadd32_wrap_new_series_block_stmt_18612_c_mutex_);
}
void
fpunit_exec_exec_fpadd32_wrap_new(float X, float Y, float *RESULT)
{
    float           __RESULT;
    fpunit_exec_exec__fpadd32_wrap_new_outer_arg_decl_macro__;
    _fpunit_exec_exec_fpadd32_wrap_new_(&__X, &__Y, &__RESULT);
    fpunit_exec_exec__fpadd32_wrap_new_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fpadd64_op_(bit_vector * __puse_single_precision_inputs,
			      bit_vector * __pdouble_precision_outputs,
			      bit_vector * __puf1_s,
			      bit_vector * __pf1_s_class,
			      bit_vector * __puf2_s,
			      bit_vector * __pf2_s_class,
			      bit_vector * __puf1_d_i,
			      bit_vector * __pf1_d_class,
			      bit_vector * __puf2_d_i,
			      bit_vector * __pf2_d_class,
			      bit_vector * __pneeds_norm,
			      bit_vector * __pextn_result)
{
    MUTEX_DECL
	(fpunit_exec_exec__fpadd64_op_series_block_stmt_10453_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fpadd64_op_series_block_stmt_10453_c_mutex_);
    fpunit_exec_exec__fpadd64_op_inner_inarg_prep_macro__;
    // $volatile $call SingleToExtendedFp (uf1_s f1_s_class ) (uf1_s_efp ) 
    // 
    fpunit_exec_exec__fpadd64_op_call_stmt_10469_c_macro_;
    // $volatile $call SingleToExtendedFp (uf2_s f2_s_class ) (uf2_s_efp ) 
    // 
    fpunit_exec_exec__fpadd64_op_call_stmt_10473_c_macro_;
    // $volatile $call DoubleToExtendedFp (uf1_d_i f1_d_class )
    // (uf1_d_i_efp ) 
    fpunit_exec_exec__fpadd64_op_call_stmt_10477_c_macro_;
    // $volatile $call DoubleToExtendedFp (uf2_d_i f2_d_class )
    // (uf2_d_i_efp ) 
    fpunit_exec_exec__fpadd64_op_call_stmt_10481_c_macro_;
    // $volatile uf1_d_efp := ( $mux use_single_precision_inputs uf1_s_efp 
    // uf1_d_i_efp ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10487_c_macro_;
    // $volatile uf2_d_efp := ( $mux use_single_precision_inputs uf2_s_efp 
    // uf2_d_i_efp ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10493_c_macro_;
    // $volatile sign_uf1_d := ( $slice uf1_d_efp 66 66 ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10497_c_macro_;
    // $volatile f1_exp13_unbiased := ( $slice uf1_d_efp 65 53 )
    // $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10501_c_macro_;
    // $volatile f1_top_bit := ( $slice uf1_d_efp 52 52 ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10505_c_macro_;
    // $volatile f1_fraction := ( $slice uf1_d_efp 51 0 ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10509_c_macro_;
    // $volatile sign_uf2_d := ( $slice uf2_d_efp 66 66 ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10513_c_macro_;
    // $volatile f2_exp13_unbiased := ( $slice uf2_d_efp 65 53 )
    // $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10517_c_macro_;
    // $volatile f2_top_bit := ( $slice uf2_d_efp 52 52 ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10521_c_macro_;
    // $volatile f2_fraction := ( $slice uf2_d_efp 51 0 ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10525_c_macro_;
    // $volatile $call classify_utility (use_single_precision_inputs
    // f1_s_class f1_d_class ) (f1_zero f1_normal f1_denormal f1_nan
    // f1_inf f1_pos_inf f1_neg_inf ) 
    fpunit_exec_exec__fpadd64_op_call_stmt_10536_c_macro_;
    // $volatile $call classify_utility (use_single_precision_inputs
    // f2_s_class f2_d_class ) (f2_zero f2_normal f2_denormal f2_nan
    // f2_inf f2_pos_inf f2_neg_inf ) 
    fpunit_exec_exec__fpadd64_op_call_stmt_10547_c_macro_;
    // $volatile f1_frac := (f1_top_bit && f1_fraction) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10552_c_macro_;
    // $volatile f2_frac := (f2_top_bit && f2_fraction) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10557_c_macro_;
    // $report (fpunit_exec fpadd64_op_fractions f1_frac f1_frac f2_frac
    // f2_frac )
    fpunit_exec_exec__fpadd64_op_stmt_10560_c_macro_;
    // $volatile exp_a := ($bitcast ($int<13>) f1_exp13_unbiased )
    // $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10564_c_macro_;
    // $volatile exp_b := ($bitcast ($int<13>) f2_exp13_unbiased )
    // $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10568_c_macro_;
    // $volatile $call expDiffDouble (uf1_d_i uf2_d_i )
    // (exp_a_greater_than_exp_b_d exp_a_equal_exp_b_d exp_ab_d ) 
    fpunit_exec_exec__fpadd64_op_call_stmt_10574_c_macro_;
    // $volatile $call expDiffSingle (uf1_s uf2_s )
    // (exp_a_greater_than_exp_b_s exp_a_equal_exp_b_s exp_ab_s ) 
    fpunit_exec_exec__fpadd64_op_call_stmt_10580_c_macro_;
    // $volatile exp_ab := ( $mux use_single_precision_inputs exp_ab_s
    // exp_ab_d ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10586_c_macro_;
    // $volatile exp_a_greater_than_exp_b := ( $mux
    // use_single_precision_inputs exp_a_greater_than_exp_b_s
    // exp_a_greater_than_exp_b_d ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10592_c_macro_;
    // $volatile exp_a_equal_exp_b := ( $mux use_single_precision_inputs
    // exp_a_equal_exp_b_s exp_a_equal_exp_b_d ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10598_c_macro_;
    // $report (fpunit_exec fpadd64_op_exponents exp_a exp_a exp_b exp_b
    // exp_a_greater_than_exp_b exp_a_greater_than_exp_b exp_a_equal_exp_b 
    // exp_a_equal_exp_b exp_ab exp_ab )
    fpunit_exec_exec__fpadd64_op_stmt_10604_c_macro_;
    // $volatile mantissa_a_pre_shift := ((ZERO_1 && f1_frac) && ZERO_10)
    // $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10611_c_macro_;
    // $volatile mantissa_b_pre_shift := ((ZERO_1 && f2_frac) && ZERO_10)
    // $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10618_c_macro_;
    // $volatile to_be_shifted := ( $mux exp_a_greater_than_exp_b
    // mantissa_b_pre_shift mantissa_a_pre_shift ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10624_c_macro_;
    // $volatile exp_ab_7 := ( $mux (exp_ab > 64 ) ($bitcast ($uint<7>) 64 
    // ) ($bitcast ($uint<7>) exp_ab ) ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10634_c_macro_;
    // $volatile $call u64_sr_special (to_be_shifted exp_ab_7 )
    // (shifted_output sticky_temp ) 
    fpunit_exec_exec__fpadd64_op_call_stmt_10639_c_macro_;
    // $volatile mantissa_a_pre_shift_d := ((ZERO_1 && f1_frac) &&
    // ZERO_10) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10646_c_macro_;
    // $volatile mantissa_b_pre_shift_d := ((ZERO_1 && f2_frac) &&
    // ZERO_10) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10653_c_macro_;
    // $volatile mantissa_a_post_shift := ( $mux (exp_a_greater_than_exp_b 
    // | exp_a_equal_exp_b) mantissa_a_pre_shift_d shifted_output )
    // $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10661_c_macro_;
    // $volatile mantissa_b_post_shift := ( $mux exp_a_greater_than_exp_b
    // shifted_output mantissa_b_pre_shift_d ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10667_c_macro_;
    // $volatile exponent_post_align := ( $mux exp_a_greater_than_exp_b
    // exp_a exp_b ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10673_c_macro_;
    // $report (fpunit_exec fpadd64_op_post_shift mantissa_a_post_shift
    // mantissa_a_post_shift mantissa_b_post_shift mantissa_b_post_shift
    // exponent_post_align exponent_post_align )
    fpunit_exec_exec__fpadd64_op_stmt_10677_c_macro_;
    // $volatile $call compare53 (f1_frac f2_frac ) (G E ) 
    fpunit_exec_exec__fpadd64_op_call_stmt_10682_c_macro_;
    // $volatile a_frac_ge_b_frac := ( $mux exp_a_equal_exp_b (G | E)
    // exp_a_greater_than_exp_b ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10690_c_macro_;
    // $volatile a_frac_gt_b_frac := ( $mux exp_a_equal_exp_b G
    // exp_a_greater_than_exp_b ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10696_c_macro_;
    // $volatile need_to_take_twos_complement_a := (((sign_uf1_d & ( ~
    // sign_uf2_d )) & ( ~ a_frac_ge_b_frac )) | ((( ~ sign_uf1_d ) &
    // sign_uf2_d) & ( ~ a_frac_ge_b_frac ))) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10713_c_macro_;
    // $volatile need_to_take_twos_complement_b := (((sign_uf2_d & ( ~
    // sign_uf1_d )) & a_frac_ge_b_frac) | ((( ~ sign_uf2_d ) &
    // sign_uf1_d) & a_frac_ge_b_frac)) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10728_c_macro_;
    // $volatile a_was_shifted := ( ~ exp_a_greater_than_exp_b )
    // $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10732_c_macro_;
    // $volatile a_negative := need_to_take_twos_complement_a $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10735_c_macro_;
    // $volatile b_was_shifted := exp_a_greater_than_exp_b $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10738_c_macro_;
    // $volatile b_negative := need_to_take_twos_complement_b $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10741_c_macro_;
    // $volatile apply_sticky_correction := (sticky_temp & ((a_was_shifted 
    // & a_negative) | (b_was_shifted & b_negative))) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10752_c_macro_;
    // $volatile carry_in := (need_to_take_twos_complement_a |
    // need_to_take_twos_complement_b) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10757_c_macro_;
    // $volatile mantissa_operand_a := ( $mux
    // need_to_take_twos_complement_a ( ~ mantissa_a_post_shift )
    // mantissa_a_post_shift ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10764_c_macro_;
    // $volatile mantissa_operand_b := ( $mux
    // need_to_take_twos_complement_b ( ~ mantissa_b_post_shift )
    // mantissa_b_post_shift ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10771_c_macro_;
    // $volatile $call adder_64_with_carry (mantissa_operand_a
    // mantissa_operand_b carry_in ) (mantissa_added carry_out ) 
    fpunit_exec_exec__fpadd64_op_call_stmt_10777_c_macro_;
    // $volatile sign_result := (((sign_uf1_d & sign_uf2_d) | ((sign_uf1_d 
    // & ( ~ sign_uf2_d )) & a_frac_gt_b_frac)) | ((( ~ sign_uf1_d ) &
    // sign_uf2_d) & ( ~ a_frac_ge_b_frac ))) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10797_c_macro_;
    // $report (fpunit_exec fpadd64_op_mantissa_added mantissa_operand_a
    // mantissa_operand_a mantissa_operand_b mantissa_operand_b carry_in
    // carry_in mantissa_added mantissa_added carry_out carry_out
    // sign_result sign_result )
    fpunit_exec_exec__fpadd64_op_stmt_10804_c_macro_;
    // mantissa_out := mantissa_added $buffering 1// bits of buffering =
    // 64. 
    fpunit_exec_exec__fpadd64_op_assign_stmt_10807_c_macro_;
    // $volatile need_to_shift := (( ~ carry_in ) & (mantissa_out [] 63 )) 
    // $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10815_c_macro_;
    // $volatile mantissa_out_shifted := ( $slice mantissa_out 63 1 )
    // $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10819_c_macro_;
    // $volatile mantissa_64_bits := ( $mux need_to_shift (ZERO_1 &&
    // mantissa_out_shifted) (ZERO_1 && ( $slice mantissa_out 62 0 ) ) )
    // $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10830_c_macro_;
    // $report (fpunit_exec fpadd64_op_final_mantissa_64 mantissa_64_bits
    // mantissa_64_bits )
    fpunit_exec_exec__fpadd64_op_stmt_10832_c_macro_;
    // $volatile $call find_leftmost_64 (mantissa_64_bits )
    // (position_of_one one_found ) 
    fpunit_exec_exec__fpadd64_op_call_stmt_10836_c_macro_;
    // $volatile left_shift_amount := ($bitcast ($uint<6>) (62 -
    // position_of_one) ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10842_c_macro_;
    // $volatile add_result_zero := ( ~ one_found ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10846_c_macro_;
    // $volatile $call i64_sll (mantissa_64_bits left_shift_amount )
    // (final_mantissa_aligned ) 
    fpunit_exec_exec__fpadd64_op_call_stmt_10850_c_macro_;
    // $volatile final_mantissa_62_aligned := ( $slice
    // final_mantissa_aligned 61 0 ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10854_c_macro_;
    // $volatile exponent_correction := (( $mux need_to_shift exp_base_1
    // exp_base_0 ) - ( $mux one_found ($bitcast ($int<13>)
    // left_shift_amount ) _b0 ) ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10866_c_macro_;
    // $volatile final_exponent_without_bias := (exponent_post_align +
    // exponent_correction) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10871_c_macro_;
    // $report (fpunit_exec fpadd64_op_final_exponent_without_bias
    // exponent_post_align exponent_post_align exponent_correction
    // exponent_correction final_exponent_without_bias
    // final_exponent_without_bias )
    fpunit_exec_exec__fpadd64_op_stmt_10875_c_macro_;
    // $volatile DP_exp_overflow := (final_exponent_without_bias > 1023 )
    // $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10880_c_macro_;
    // $volatile DP_exp_underflow := (final_exponent_without_bias < -1022
    // ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10885_c_macro_;
    // $volatile SP_exp_overflow := (final_exponent_without_bias > 127 )
    // $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10890_c_macro_;
    // $volatile SP_exp_underflow := (final_exponent_without_bias < -126 ) 
    // $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10895_c_macro_;
    // $volatile underflow_SP := (SP_exp_underflow & ( ~ add_result_zero
    // )) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10901_c_macro_;
    // $volatile underflow_DP := (DP_exp_underflow & ( ~ add_result_zero
    // )) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10907_c_macro_;
    // $volatile overflow_SP := (SP_exp_overflow & ( ~ add_result_zero ))
    // $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10913_c_macro_;
    // $volatile overflow_DP := (DP_exp_overflow & ( ~ add_result_zero ))
    // $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10919_c_macro_;
    // $volatile overflow := ( $mux double_precision_outputs overflow_DP
    // overflow_SP ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10925_c_macro_;
    // $volatile condition_nan := ((f1_nan | f2_nan) | ((f1_pos_inf &
    // f2_neg_inf) | (f1_neg_inf & f2_pos_inf))) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10938_c_macro_;
    // $volatile condition_inf := (((f1_pos_inf & f2_pos_inf) |
    // (f1_neg_inf & f2_neg_inf)) | overflow) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10949_c_macro_;
    // $volatile condition_zero := ((f1_zero & f2_zero) | add_result_zero) 
    // $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10956_c_macro_;
    // $volatile underflow := (( ~ condition_zero ) & ( $mux
    // double_precision_outputs underflow_DP underflow_SP ) ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10965_c_macro_;
    // $report (fpunit_exec fpadd64_op_final_exceptions DP_exp_overflow
    // DP_exp_overflow DP_exp_underflow DP_exp_underflow SP_exp_overflow
    // SP_exp_overflow SP_exp_underflow SP_exp_underflow underflow_SP
    // underflow_SP underflow_DP underflow_DP overflow_SP overflow_SP
    // overflow_DP overflow_DP condition_nan condition_nan condition_inf
    // condition_inf condition_zero condition_zero )
    fpunit_exec_exec__fpadd64_op_stmt_10977_c_macro_;
    // $volatile SP_nothing_to_be_done_condition_normal := (((( ~ overflow 
    // ) & ( ~ underflow )) & ( ~ condition_zero )) & (( ~ condition_inf ) 
    // & ( ~ condition_nan ))) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_10993_c_macro_;
    // $volatile SP_normalization_required := (((overflow | underflow) & ( 
    // ~ condition_zero )) & (( ~ condition_inf ) & ( ~ condition_nan )))
    // $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_11007_c_macro_;
    // $volatile DP_nothing_to_be_done_condition_normal := (((( ~ overflow 
    // ) & ( ~ underflow )) & ( ~ condition_zero )) & (( ~ condition_inf ) 
    // & ( ~ condition_nan ))) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_11023_c_macro_;
    // $volatile DP_normalization_required := (((overflow | underflow) & ( 
    // ~ condition_zero )) & (( ~ condition_inf ) & ( ~ condition_nan )))
    // $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_11037_c_macro_;
    // $volatile normalization_required := ( $mux double_precision_outputs 
    // DP_normalization_required SP_normalization_required ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_11043_c_macro_;
    // $volatile nothing_to_be_done_condition_normal := ( $mux
    // double_precision_outputs DP_nothing_to_be_done_condition_normal
    // SP_nothing_to_be_done_condition_normal ) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_11049_c_macro_;
    // $volatile exponent_to_be_passed := (((( $mux condition_nan
    // ALL_ONE_13 _b0 ) | ( $mux condition_inf ALL_ONE_13 _b0 ) ) | ( $mux 
    // condition_zero ($bitcast ($int<13>) ZERO_13 ) _b0 ) ) | (( $mux
    // nothing_to_be_done_condition_normal final_exponent_without_bias _b0 
    // ) | ( $mux normalization_required final_exponent_without_bias _b0 ) 
    // )) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_11076_c_macro_;
    // $volatile mantissa_to_be_passed := ((( $mux condition_nan (ONE_1 && 
    // ZERO_61) _b0 ) | ( $mux (condition_inf | condition_zero) ZERO_62
    // _b0 ) ) | ( $mux (nothing_to_be_done_condition_normal |
    // normalization_required) final_mantissa_62_aligned _b0 ) )
    // $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_11098_c_macro_;
    // $volatile condition_to_pass_sticky_bit := ((((a_was_shifted &
    // a_negative) & b_negative) | ((a_was_shifted & ( ~ a_negative )) & ( 
    // ~ b_negative ))) | (((b_was_shifted & a_negative) & b_negative) |
    // ((b_was_shifted & ( ~ a_negative )) & ( ~ b_negative ))))
    // $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_11127_c_macro_;
    // $volatile sticky := (((sticky_temp & condition_to_pass_sticky_bit)
    // & ( ~ condition_zero )) & (( ~ condition_inf ) & ( ~ condition_nan
    // ))) $buffering 1
    fpunit_exec_exec__fpadd64_op_assign_stmt_11141_c_macro_;
    // needs_norm := ((normalization_required & ( ~ condition_zero )) & (( 
    // ~ condition_inf ) & ( ~ condition_nan ))) $buffering 2// bits of
    // buffering = 2. 
    fpunit_exec_exec__fpadd64_op_assign_stmt_11153_c_macro_;
    // extn_result := (((sticky && apply_sticky_correction) &&
    // (sign_result && condition_nan)) && ((condition_inf &&
    // condition_zero) && (($bitcast ($uint<13>) exponent_to_be_passed )
    // && mantissa_to_be_passed))) $buffering 2// bits of buffering = 162. 
    // 
    fpunit_exec_exec__fpadd64_op_assign_stmt_11171_c_macro_;
    // $report (fpunit_exec fpadd64_op_final_results exponent_to_be_passed 
    // exponent_to_be_passed mantissa_to_be_passed mantissa_to_be_passed )
    fpunit_exec_exec__fpadd64_op_stmt_11174_c_macro_;
    fpunit_exec_exec__fpadd64_op_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fpadd64_op_series_block_stmt_10453_c_mutex_);
}
void
_fpunit_exec_exec_fpadd64_wrap_(double *__pX, double *__pY,
				double *__pRESULT)
{
    MUTEX_DECL
	(fpunit_exec_exec__fpadd64_wrap_series_block_stmt_18706_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fpadd64_wrap_series_block_stmt_18706_c_mutex_);
    fpunit_exec_exec__fpadd64_wrap_inner_inarg_prep_macro__;
    // $volatile $call classFp64 (X ) (xpn xnn xpd xnd xqnan xsnan xpi xni 
    // xpz xnz ) 
    fpunit_exec_exec__fpadd64_wrap_call_stmt_18721_c_macro_;
    // x_class := ((((xpn && xnn) && xpd) && (xnd && xqnan)) && (((xsnan
    // && xpi) && xni) && (xpz && xnz))) $buffering 1// bits of buffering
    // = 10. 
    fpunit_exec_exec__fpadd64_wrap_assign_stmt_18742_c_macro_;
    // $volatile $call classFp64 (Y ) (ypn ynn ypd ynd yqnan ysnan ypi yni 
    // ypz ynz ) 
    fpunit_exec_exec__fpadd64_wrap_call_stmt_18754_c_macro_;
    // y_class := ((((ypn && ynn) && ypd) && (ynd && yqnan)) && (((ysnan
    // && ypi) && yni) && (ypz && ynz))) $buffering 1// bits of buffering
    // = 10. 
    fpunit_exec_exec__fpadd64_wrap_assign_stmt_18775_c_macro_;
    // $call fpadd64_op (ZERO_1 ONE_1 _b0 _b0 _b0 _b0 ($bitcast
    // ($uint<64>) X ) x_class ($bitcast ($uint<64>) Y ) y_class )
    // (denormalize_flag_add extn_result_add ) 
    fpunit_exec_exec__fpadd64_wrap_call_stmt_18790_c_macro_;
    // $volatile $call round_fp_64 (extn_result_add ) (addd_result_fast ) 
    fpunit_exec_exec__fpadd64_wrap_call_stmt_18793_c_macro_;
    // $guard (denormalize_flag_add) $call denormalize_fp_64
    // (extn_result_add ) (addd_result_slow ) 
    fpunit_exec_exec__fpadd64_wrap_call_stmt_18797_c_macro_;
    // $volatile RESULT := ($bitcast ($float<11,52>) ( $mux
    // denormalize_flag_add addd_result_slow addd_result_fast ) )
    // $buffering 1
    fpunit_exec_exec__fpadd64_wrap_assign_stmt_18804_c_macro_;
    fpunit_exec_exec__fpadd64_wrap_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fpadd64_wrap_series_block_stmt_18706_c_mutex_);
}
void
fpunit_exec_exec_fpadd64_wrap(double X, double Y, double *RESULT)
{
    double          __RESULT;
    fpunit_exec_exec__fpadd64_wrap_outer_arg_decl_macro__;
    _fpunit_exec_exec_fpadd64_wrap_(&__X, &__Y, &__RESULT);
    fpunit_exec_exec__fpadd64_wrap_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fpcmp32_(float *__pa, float *__pb,
			   bit_vector * __pe_flag,
			   bit_vector * __pcmp_flags)
{
    MUTEX_DECL(fpunit_exec_exec__fpcmp32_series_block_stmt_15255_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__fpcmp32_series_block_stmt_15255_c_mutex_);
    fpunit_exec_exec__fpcmp32_inner_inarg_prep_macro__;
    // cmp_flags := ((( $mux (a == b) 0 _b0 ) | ( $mux (a < b) 1 _b0 ) ) | 
    // (( $mux (a > b) 2 _b0 ) | ( $mux (a >< b) 3 _b0 ) )) $buffering 1
    fpunit_exec_exec__fpcmp32_assign_stmt_15288_c_macro_;
    // $report (fpunit_exec fpcmp32_trace__ a a b b cmp_flags cmp_flags )
    fpunit_exec_exec__fpcmp32_stmt_15292_c_macro_;
    fpunit_exec_exec__fpcmp32_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fpcmp32_series_block_stmt_15255_c_mutex_);
}
void
_fpunit_exec_exec_fpcmp64_(double *__pa, double *__pb,
			   bit_vector * __pe_flag,
			   bit_vector * __pcmp_flags)
{
    MUTEX_DECL(fpunit_exec_exec__fpcmp64_series_block_stmt_16333_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__fpcmp64_series_block_stmt_16333_c_mutex_);
    fpunit_exec_exec__fpcmp64_inner_inarg_prep_macro__;
    // cmp_flags := ((( $mux (a == b) 0 _b0 ) | ( $mux (a < b) 1 _b0 ) ) | 
    // (( $mux (a > b) 2 _b0 ) | ( $mux (a >< b) 3 _b0 ) )) $buffering 1
    fpunit_exec_exec__fpcmp64_assign_stmt_16366_c_macro_;
    // $report (fpunit_exec fpcmp64_trace__ a a b b cmp_flags cmp_flags )
    fpunit_exec_exec__fpcmp64_stmt_16370_c_macro_;
    fpunit_exec_exec__fpcmp64_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fpcmp64_series_block_stmt_16333_c_mutex_);
}
void
_fpunit_exec_exec_fpdivide32_(float *__pf1_s, float *__pf2_s,
			      float *__pf1BYf2)
{
    MUTEX_DECL
	(fpunit_exec_exec__fpdivide32_series_block_stmt_14433_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fpdivide32_series_block_stmt_14433_c_mutex_);
    fpunit_exec_exec__fpdivide32_inner_inarg_prep_macro__;
    // $volatile uf1_s := ($bitcast ($uint<32>) f1_s ) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14440_c_macro_;
    // $volatile uf2_s := ($bitcast ($uint<32>) f2_s ) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14444_c_macro_;
    // $volatile sign_uf1_s := (uf1_s [] 31 ) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14449_c_macro_;
    // $volatile sign_uf2_s := (uf2_s [] 31 ) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14454_c_macro_;
    // $volatile sign_result := (sign_uf1_s ^ sign_uf2_s) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14459_c_macro_;
    // $volatile $call classFp32 (f1_s ) (f1_s_pos_normal f1_s_neg_normal
    // f1_s_pos_denormal f1_s_neg_denormal f1_s_qnan f1_s_snan
    // f1_s_pos_inf f1_s_neg_inf f1_s_pos_zero f1_s_neg_zero ) 
    fpunit_exec_exec__fpdivide32_call_stmt_14471_c_macro_;
    // $volatile $call classFp32 (f2_s ) (f2_s_pos_normal f2_s_neg_normal
    // f2_s_pos_denormal f2_s_neg_denormal f2_s_qnan f2_s_snan
    // f2_s_pos_inf f2_s_neg_inf f2_s_pos_zero f2_s_neg_zero ) 
    fpunit_exec_exec__fpdivide32_call_stmt_14483_c_macro_;
    // $volatile f1_s_zero := (f1_s_pos_zero | f1_s_neg_zero) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14488_c_macro_;
    // $volatile f2_s_zero := (f2_s_pos_zero | f2_s_neg_zero) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14493_c_macro_;
    // $volatile f1_s_normal := (f1_s_pos_normal | f1_s_neg_normal)
    // $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14498_c_macro_;
    // $volatile f2_s_normal := (f2_s_pos_normal | f2_s_neg_normal)
    // $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14503_c_macro_;
    // $volatile f1_s_denormal := (f1_s_pos_denormal | f1_s_neg_denormal)
    // $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14508_c_macro_;
    // $volatile f2_s_denormal := (f2_s_pos_denormal | f2_s_neg_denormal)
    // $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14513_c_macro_;
    // $volatile f1_s_inf := (f1_s_pos_inf | f1_s_neg_inf) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14518_c_macro_;
    // $volatile f2_s_inf := (f2_s_pos_inf | f2_s_neg_inf) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14523_c_macro_;
    // $volatile $call break_number_32 (uf1_s f1_s_normal f1_s_denormal
    // f1_s_qnan f1_s_snan f1_s_inf f1_s_zero DENORM ) (f1_s_frac
    // f1_s_expon ) 
    fpunit_exec_exec__fpdivide32_call_stmt_14534_c_macro_;
    // $volatile $call break_number_32 (uf2_s f2_s_normal f2_s_denormal
    // f2_s_qnan f2_s_snan f2_s_inf f2_s_zero DENORM ) (f2_s_frac
    // f2_s_expon ) 
    fpunit_exec_exec__fpdivide32_call_stmt_14545_c_macro_;
    // $guard (f1_s_denormal) $call normalize_32 (f1_s_frac f1_s_expon )
    // (f1_s_frac_norm f1_s_expon_norm ) 
    fpunit_exec_exec__fpdivide32_call_stmt_14551_c_macro_;
    // $guard (f2_s_denormal) $call normalize_32 (f2_s_frac f2_s_expon )
    // (f2_s_frac_norm f2_s_expon_norm ) 
    fpunit_exec_exec__fpdivide32_call_stmt_14557_c_macro_;
    // $volatile f1_fraction := ( $mux f1_s_denormal f1_s_frac_norm
    // f1_s_frac ) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14563_c_macro_;
    // $volatile f2_fraction := ( $mux f2_s_denormal f2_s_frac_norm
    // f2_s_frac ) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14569_c_macro_;
    // $volatile f1_expon := ( $mux f1_s_denormal f1_s_expon_norm
    // f1_s_expon ) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14575_c_macro_;
    // $volatile f2_expon := ( $mux f2_s_denormal f2_s_expon_norm
    // f2_s_expon ) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14581_c_macro_;
    // $volatile expon_difference := (f1_expon - f2_expon) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14586_c_macro_;
    // $call short_divide_24_pipelined_optimised (f1_fraction f2_fraction
    // ) (quotient ) 
    fpunit_exec_exec__fpdivide32_call_stmt_14590_c_macro_;
    // $volatile quotient_MSB := (quotient [] 28 ) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14595_c_macro_;
    // $volatile mantissa_24_before_rounding := ( $mux quotient_MSB (
    // $slice quotient 28 5 ) ( $slice quotient 27 4 ) ) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14603_c_macro_;
    // $volatile guard_bits_5 := ( $slice quotient 4 0 ) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14607_c_macro_;
    // $volatile guard_bits_4 := ( $slice quotient 3 0 ) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14611_c_macro_;
    // $volatile guard_5_up_round_condition := (guard_bits_5 >= 16 )
    // $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14616_c_macro_;
    // $volatile guard_4_up_round_condition := (guard_bits_4 >= 8 )
    // $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14621_c_macro_;
    // $volatile upround_the_mantissa := ( $mux quotient_MSB
    // guard_5_up_round_condition guard_4_up_round_condition ) $buffering
    // 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14627_c_macro_;
    // $volatile mantissa_24_incremented := (mantissa_24_before_rounding + 
    // 1 ) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14632_c_macro_;
    // $volatile mantissa_24_incr_top_bit := (mantissa_24_incremented []
    // 23 ) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14637_c_macro_;
    // $volatile mantissa_23 := ( $mux upround_the_mantissa ( $mux
    // mantissa_24_incr_top_bit ( $slice mantissa_24_incremented 22 0 )
    // ZERO_23 ) ( $slice mantissa_24_before_rounding 22 0 ) ) $buffering
    // 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14648_c_macro_;
    // $volatile exponent_adjustment := (( $mux quotient_MSB 0 (($bitcast
    // ($int<10>) 0 ) - 1 ) ) + ( $mux mantissa_24_incr_top_bit 0
    // ($bitcast ($int<10>) 1 ) ) ) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14663_c_macro_;
    // $volatile expon_bias := expbase_127 $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14666_c_macro_;
    // $volatile exponent_before_round := (expon_difference + expon_bias)
    // $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14671_c_macro_;
    // $volatile exponent := (exponent_before_round + exponent_adjustment) 
    // $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14676_c_macro_;
    // $volatile exponent_unbiased := (exponent - expon_bias) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14681_c_macro_;
    // $volatile exponent_8 := ($bitcast ($uint<8>) exponent ) $buffering
    // 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14685_c_macro_;
    // $volatile mantissa := mantissa_23 $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14688_c_macro_;
    // $volatile overflow := (exponent_unbiased > 127 ) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14693_c_macro_;
    // $volatile underflow := (exponent_unbiased < -126 ) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14698_c_macro_;
    // $volatile qnan_condition := (((f2_s_qnan | f2_s_snan) | (f2_s_inf & 
    // ((f1_s_inf | f1_s_snan) | f1_s_qnan))) | (((f2_s_zero & ((f1_s_zero 
    // | f1_s_snan) | f1_s_qnan)) | f1_s_qnan) | f1_s_snan)) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14723_c_macro_;
    // $volatile denorm_shift_amount := ((0 - 126 ) - exponent_unbiased)
    // $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14730_c_macro_;
    // $volatile is_denormalizable := ((underflow & (denorm_shift_amount
    // <= 24 )) & ( ~ qnan_condition )) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14740_c_macro_;
    // $volatile p := ((ONE_1 && mantissa) && ZERO_8) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14747_c_macro_;
    // $volatile q := ($bitcast ($uint<5>) denorm_shift_amount )
    // $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14751_c_macro_;
    // $volatile $call i32_srl (p q ) (shifted ) 
    fpunit_exec_exec__fpdivide32_call_stmt_14755_c_macro_;
    // mantissa_denorm_final := ( $slice shifted 30 8 ) $buffering 1//
    // bits of buffering = 23. 
    fpunit_exec_exec__fpdivide32_assign_stmt_14759_c_macro_;
    // $volatile result_denormal := ((sign_result && ZERO_8) &&
    // mantissa_denorm_final) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14766_c_macro_;
    // $volatile result_normal := ((sign_result && exponent_8) &&
    // mantissa) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14773_c_macro_;
    // $volatile result_qnan := ((sign_result && ALL_ONE_8) && (ONE_1 &&
    // ZERO_22)) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14782_c_macro_;
    // $volatile result_zero := (sign_result && ZERO_31) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14787_c_macro_;
    // $volatile result_infinity := ((sign_result && ALL_ONE_8) &&
    // ZERO_23) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14794_c_macro_;
    // $volatile underflow_not_denorm := (underflow & ( ~
    // is_denormalizable )) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14800_c_macro_;
    // $volatile zero_condition := (((f2_s_zero & ((f1_s_zero | f1_s_qnan) 
    // | f1_s_snan)) | f1_s_zero) | underflow_not_denorm) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14813_c_macro_;
    // $volatile inf_condition := (((f2_s_zero & ((f1_s_normal |
    // f1_s_denormal) | f1_s_inf)) | (f1_s_inf & (f2_s_normal |
    // f2_s_denormal))) | overflow) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14830_c_macro_;
    // $volatile normal_condition := (((f1_s_normal | f1_s_denormal) &
    // (f2_s_normal | f2_s_denormal)) & (( ~ overflow ) & ( ~ underflow
    // ))) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14845_c_macro_;
    // $volatile result := (((( $mux zero_condition result_zero _b0 ) | (
    // $mux qnan_condition result_qnan _b0 ) ) | ( $mux inf_condition
    // result_infinity _b0 ) ) | (( $mux normal_condition result_normal
    // _b0 ) | ( $mux is_denormalizable result_denormal _b0 ) ))
    // $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14871_c_macro_;
    // $volatile f1BYf2 := ($bitcast ($float<8,23>) result ) $buffering 1
    fpunit_exec_exec__fpdivide32_assign_stmt_14875_c_macro_;
    fpunit_exec_exec__fpdivide32_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fpdivide32_series_block_stmt_14433_c_mutex_);
}
void
fpunit_exec_exec_fpdivide32(float f1_s, float f2_s, float *f1BYf2)
{
    float           __f1BYf2;
    fpunit_exec_exec__fpdivide32_outer_arg_decl_macro__;
    _fpunit_exec_exec_fpdivide32_(&__f1_s, &__f2_s, &__f1BYf2);
    fpunit_exec_exec__fpdivide32_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fpdivide64_(double *__pf1_d, double *__pf2_d,
			      double *__pf1BYf2)
{
    MUTEX_DECL
	(fpunit_exec_exec__fpdivide64_series_block_stmt_15510_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fpdivide64_series_block_stmt_15510_c_mutex_);
    fpunit_exec_exec__fpdivide64_inner_inarg_prep_macro__;
    // $volatile uf1_d := ($bitcast ($uint<64>) f1_d ) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15517_c_macro_;
    // $volatile uf2_d := ($bitcast ($uint<64>) f2_d ) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15521_c_macro_;
    // $volatile sign_uf1_d := (uf1_d [] 63 ) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15526_c_macro_;
    // $volatile sign_uf2_d := (uf2_d [] 63 ) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15531_c_macro_;
    // $volatile sign_result := (sign_uf1_d ^ sign_uf2_d) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15536_c_macro_;
    // $volatile $call classFp64 (f1_d ) (f1_d_pos_normal f1_d_neg_normal
    // f1_d_pos_denormal f1_d_neg_denormal f1_d_qnan f1_d_snan
    // f1_d_pos_inf f1_d_neg_inf f1_d_pos_zero f1_d_neg_zero ) 
    fpunit_exec_exec__fpdivide64_call_stmt_15548_c_macro_;
    // $volatile $call classFp64 (f2_d ) (f2_d_pos_normal f2_d_neg_normal
    // f2_d_pos_denormal f2_d_neg_denormal f2_d_qnan f2_d_snan
    // f2_d_pos_inf f2_d_neg_inf f2_d_pos_zero f2_d_neg_zero ) 
    fpunit_exec_exec__fpdivide64_call_stmt_15560_c_macro_;
    // $volatile f1_d_zero := (f1_d_pos_zero | f1_d_neg_zero) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15565_c_macro_;
    // $volatile f2_d_zero := (f2_d_pos_zero | f2_d_neg_zero) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15570_c_macro_;
    // $volatile f1_d_normal := (f1_d_pos_normal | f1_d_neg_normal)
    // $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15575_c_macro_;
    // $volatile f2_d_normal := (f2_d_pos_normal | f2_d_neg_normal)
    // $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15580_c_macro_;
    // $volatile f1_d_denormal := (f1_d_pos_denormal | f1_d_neg_denormal)
    // $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15585_c_macro_;
    // $volatile f2_d_denormal := (f2_d_pos_denormal | f2_d_neg_denormal)
    // $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15590_c_macro_;
    // $volatile f1_d_inf := (f1_d_pos_inf | f1_d_neg_inf) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15595_c_macro_;
    // $volatile f2_d_inf := (f2_d_pos_inf | f2_d_neg_inf) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15600_c_macro_;
    // $volatile $call break_number_64 (uf1_d f1_d_normal f1_d_denormal
    // f1_d_qnan f1_d_snan f1_d_inf f1_d_zero DENORM ) (f1_d_frac
    // f1_d_expon ) 
    fpunit_exec_exec__fpdivide64_call_stmt_15611_c_macro_;
    // $volatile $call break_number_64 (uf2_d f2_d_normal f2_d_denormal
    // f2_d_qnan f2_d_snan f2_d_inf f2_d_zero DENORM ) (f2_d_frac
    // f2_d_expon ) 
    fpunit_exec_exec__fpdivide64_call_stmt_15622_c_macro_;
    // $guard (f1_d_denormal) $call normalize_64 (f1_d_frac f1_d_expon )
    // (f1_d_frac_norm f1_d_expon_norm ) 
    fpunit_exec_exec__fpdivide64_call_stmt_15628_c_macro_;
    // $guard (f2_d_denormal) $call normalize_64 (f2_d_frac f2_d_expon )
    // (f2_d_frac_norm f2_d_expon_norm ) 
    fpunit_exec_exec__fpdivide64_call_stmt_15634_c_macro_;
    // $volatile f1_fraction := ( $mux f1_d_denormal f1_d_frac_norm
    // f1_d_frac ) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15640_c_macro_;
    // $volatile f2_fraction := ( $mux f2_d_denormal f2_d_frac_norm
    // f2_d_frac ) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15646_c_macro_;
    // $volatile f1_expon := ( $mux f1_d_denormal f1_d_expon_norm
    // f1_d_expon ) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15652_c_macro_;
    // $volatile f2_expon := ( $mux f2_d_denormal f2_d_expon_norm
    // f2_d_expon ) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15658_c_macro_;
    // $volatile expon_difference := (f1_expon - f2_expon) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15663_c_macro_;
    // $call short_divide_53_pipelined_optimised (f1_fraction f2_fraction
    // ) (quotient ) 
    fpunit_exec_exec__fpdivide64_call_stmt_15667_c_macro_;
    // $volatile quotient_MSB := (quotient [] 57 ) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15672_c_macro_;
    // $volatile mantissa_53_before_rounding := ( $mux quotient_MSB (
    // $slice quotient 57 5 ) ( $slice quotient 56 4 ) ) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15680_c_macro_;
    // $volatile guard_bits_5 := ( $slice quotient 4 0 ) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15684_c_macro_;
    // $volatile guard_bits_4 := ( $slice quotient 3 0 ) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15688_c_macro_;
    // $volatile guard_5_up_round_condition := (guard_bits_5 >= 16 )
    // $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15693_c_macro_;
    // $volatile guard_4_up_round_condition := (guard_bits_4 >= 8 )
    // $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15698_c_macro_;
    // $volatile upround_the_mantissa := ( $mux quotient_MSB
    // guard_5_up_round_condition guard_4_up_round_condition ) $buffering
    // 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15704_c_macro_;
    // $volatile mantissa_53_incremented := (mantissa_53_before_rounding + 
    // 1 ) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15709_c_macro_;
    // $volatile mantissa_53_incr_top_bit := (mantissa_53_incremented []
    // 52 ) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15714_c_macro_;
    // $volatile mantissa_52 := ( $mux upround_the_mantissa ( $mux
    // mantissa_53_incr_top_bit ( $slice mantissa_53_incremented 51 0 )
    // ZERO_52 ) ( $slice mantissa_53_before_rounding 51 0 ) ) $buffering
    // 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15725_c_macro_;
    // $volatile exponent_adjustment := (( $mux quotient_MSB 0 (($bitcast
    // ($int<13>) 0 ) - 1 ) ) + ( $mux mantissa_53_incr_top_bit 0
    // ($bitcast ($int<13>) 1 ) ) ) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15740_c_macro_;
    // $volatile expon_bias := expbase_1023 $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15743_c_macro_;
    // $volatile exponent_before_round := (expon_difference + expon_bias)
    // $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15748_c_macro_;
    // $volatile exponent := (exponent_before_round + exponent_adjustment) 
    // $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15753_c_macro_;
    // $volatile exponent_unbiased := (exponent - expon_bias) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15758_c_macro_;
    // $volatile exponent_11 := ($bitcast ($uint<11>) exponent )
    // $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15762_c_macro_;
    // $volatile mantissa := mantissa_52 $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15765_c_macro_;
    // $volatile overflow := (exponent_unbiased > 1023 ) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15770_c_macro_;
    // $volatile underflow := (exponent_unbiased < -1022 ) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15775_c_macro_;
    // $volatile qnan_condition := (((f2_d_qnan | f2_d_snan) | (f2_d_inf & 
    // ((f1_d_inf | f1_d_snan) | f1_d_qnan))) | (((f2_d_zero & ((f1_d_zero 
    // | f1_d_snan) | f1_d_qnan)) | f1_d_qnan) | f1_d_snan)) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15800_c_macro_;
    // $volatile denorm_shift_amount := ((0 - 1022 ) - exponent_unbiased)
    // $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15807_c_macro_;
    // $volatile is_denormalizable := ((underflow & (denorm_shift_amount
    // <= 52 )) & ( ~ qnan_condition )) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15817_c_macro_;
    // $volatile p := ((ONE_1 && mantissa) && ZERO_11) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15824_c_macro_;
    // $volatile q := ($bitcast ($uint<6>) denorm_shift_amount )
    // $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15828_c_macro_;
    // $volatile $call i64_srl (p q ) (shifted ) 
    fpunit_exec_exec__fpdivide64_call_stmt_15832_c_macro_;
    // mantissa_denorm_final := ( $slice shifted 62 11 ) $buffering 1//
    // bits of buffering = 52. 
    fpunit_exec_exec__fpdivide64_assign_stmt_15836_c_macro_;
    // $volatile result_denormal := ((sign_result && ZERO_11) &&
    // mantissa_denorm_final) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15843_c_macro_;
    // $volatile result_normal := ((sign_result && exponent_11) &&
    // mantissa) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15850_c_macro_;
    // $volatile result_qnan := ((sign_result && ALL_ONE_11) && (ONE_1 &&
    // ZERO_51)) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15859_c_macro_;
    // $volatile result_zero := (sign_result && ZERO_63) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15864_c_macro_;
    // $volatile result_infinity := ((sign_result && ALL_ONE_11) &&
    // ZERO_52) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15871_c_macro_;
    // $volatile underflow_not_denorm := (underflow & ( ~
    // is_denormalizable )) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15877_c_macro_;
    // $volatile zero_condition := (((f2_d_zero & ((f1_d_zero | f1_d_qnan) 
    // | f1_d_snan)) | f1_d_zero) | underflow_not_denorm) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15890_c_macro_;
    // $volatile inf_condition := (((f2_d_zero & ((f1_d_normal |
    // f1_d_denormal) | f1_d_inf)) | (f1_d_inf & (f2_d_normal |
    // f2_d_denormal))) | overflow) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15907_c_macro_;
    // $volatile normal_condition := (((f1_d_normal | f1_d_denormal) &
    // (f2_d_normal | f2_d_denormal)) & (( ~ overflow ) & ( ~ underflow
    // ))) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15922_c_macro_;
    // $volatile result := (((( $mux zero_condition result_zero _b0 ) | (
    // $mux qnan_condition result_qnan _b0 ) ) | ( $mux inf_condition
    // result_infinity _b0 ) ) | (( $mux normal_condition result_normal
    // _b0 ) | ( $mux is_denormalizable result_denormal _b0 ) ))
    // $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15948_c_macro_;
    // $volatile f1BYf2 := ($bitcast ($float<11,52>) result ) $buffering 1
    fpunit_exec_exec__fpdivide64_assign_stmt_15952_c_macro_;
    fpunit_exec_exec__fpdivide64_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fpdivide64_series_block_stmt_15510_c_mutex_);
}
void
fpunit_exec_exec_fpdivide64(double f1_d, double f2_d, double *f1BYf2)
{
    double          __f1BYf2;
    fpunit_exec_exec__fpdivide64_outer_arg_decl_macro__;
    _fpunit_exec_exec_fpdivide64_(&__f1_d, &__f2_d, &__f1BYf2);
    fpunit_exec_exec__fpdivide64_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fpmul32_op_(bit_vector * __puf1_s,
			      bit_vector * __pf1_s_class,
			      bit_vector * __puf2_s,
			      bit_vector * __pf2_s_class,
			      bit_vector * __pneeds_norm,
			      bit_vector * __pextn_result)
{
    MUTEX_DECL
	(fpunit_exec_exec__fpmul32_op_series_block_stmt_12198_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fpmul32_op_series_block_stmt_12198_c_mutex_);
    fpunit_exec_exec__fpmul32_op_inner_inarg_prep_macro__;
    // $volatile $call classify_utility (ONE_1 f1_s_class 0 ) (f1_zero
    // f1_normal f1_denormal f1_nan f1_inf f1_pos_inf f1_neg_inf ) 
    fpunit_exec_exec__fpmul32_op_call_stmt_12215_c_macro_;
    // $volatile $call classify_utility (ONE_1 f2_s_class 0 ) (f2_zero
    // f2_normal f2_denormal f2_nan f2_inf f2_pos_inf f2_neg_inf ) 
    fpunit_exec_exec__fpmul32_op_call_stmt_12226_c_macro_;
    // $volatile $call SingleToExtendedFp (uf1_s f1_s_class ) (uf1_s_efp ) 
    // 
    fpunit_exec_exec__fpmul32_op_call_stmt_12230_c_macro_;
    // $volatile $call SingleToExtendedFp (uf2_s f2_s_class ) (uf2_s_efp ) 
    // 
    fpunit_exec_exec__fpmul32_op_call_stmt_12234_c_macro_;
    // $volatile sign_uf1_s := ( $slice uf1_s_efp 66 66 ) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12238_c_macro_;
    // $volatile f1_exp13_unbiased := ( $slice uf1_s_efp 65 53 )
    // $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12242_c_macro_;
    // $volatile f1_top_bit := ( $slice uf1_s_efp 52 52 ) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12246_c_macro_;
    // $volatile f1_fraction := ( $slice uf1_s_efp 51 29 ) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12250_c_macro_;
    // $volatile sign_uf2_s := ( $slice uf2_s_efp 66 66 ) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12254_c_macro_;
    // $volatile f2_exp13_unbiased := ( $slice uf2_s_efp 65 53 )
    // $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12258_c_macro_;
    // $volatile f2_top_bit := ( $slice uf2_s_efp 52 52 ) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12262_c_macro_;
    // $volatile f2_fraction := ( $slice uf2_s_efp 51 29 ) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12266_c_macro_;
    // $volatile sign_result := (sign_uf1_s ^ sign_uf2_s) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12271_c_macro_;
    // $volatile f1_frac_v := (f1_top_bit && f1_fraction) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12276_c_macro_;
    // $volatile f2_frac_v := (f2_top_bit && f2_fraction) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12281_c_macro_;
    // $volatile exp_a := ($bitcast ($int<13>) f1_exp13_unbiased )
    // $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12285_c_macro_;
    // $volatile exp_b := ($bitcast ($int<13>) f2_exp13_unbiased )
    // $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12289_c_macro_;
    // $volatile $call find_left_24 (f1_frac_v ) (f1_top_bit_pos
    // f1_top_bit_found ) 
    fpunit_exec_exec__fpmul32_op_call_stmt_12293_c_macro_;
    // $volatile $call find_left_24 (f2_frac_v ) (f2_top_bit_pos
    // f2_top_bit_found ) 
    fpunit_exec_exec__fpmul32_op_call_stmt_12297_c_macro_;
    // $volatile f1_left_shift_correction := ($bitcast ($int<13>) (23 -
    // f1_top_bit_pos) ) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12303_c_macro_;
    // $volatile exp_a_corrected := (exp_a - f1_left_shift_correction)
    // $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12308_c_macro_;
    // $volatile f2_left_shift_correction := ($bitcast ($int<13>) (23 -
    // f2_top_bit_pos) ) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12314_c_macro_;
    // $volatile exp_b_corrected := (exp_b - f2_left_shift_correction)
    // $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12319_c_macro_;
    // $volatile mul_result_left_shift_amount := (f1_left_shift_correction 
    // + f2_left_shift_correction) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12324_c_macro_;
    // $volatile f1_frac := f1_frac_v $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12327_c_macro_;
    // $volatile f2_frac := f2_frac_v $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12330_c_macro_;
    // $volatile exp_ab := (exp_a_corrected + exp_b_corrected) $buffering
    // 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12335_c_macro_;
    // $call mul24 (f1_frac f2_frac ) (frac_result_48bits ) 
    fpunit_exec_exec__fpmul32_op_call_stmt_12339_c_macro_;
    // $volatile frac_result_35 := ( $slice frac_result_48bits 47 13 )
    // $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12343_c_macro_;
    // $volatile value_of_bits_thrown_away_greater_than_zero := ( ~ ((
    // $slice frac_result_35 6 0 ) == 0 ) ) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12350_c_macro_;
    // $volatile implied_shift_amount := ( $mux
    // (mul_result_left_shift_amount > 35 ) 35 ($bitcast ($uint<6>)
    // mul_result_left_shift_amount ) ) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12359_c_macro_;
    // $volatile $call i35_sll (frac_result_35 implied_shift_amount )
    // (frac_result_35_with_implied_shift ) 
    fpunit_exec_exec__fpmul32_op_call_stmt_12363_c_macro_;
    // $volatile shift_by_one := (frac_result_35_with_implied_shift [] 34
    // ) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12368_c_macro_;
    // $volatile thrown_away_bit := ( $mux shift_by_one
    // (frac_result_35_with_implied_shift [] 0 ) _b0 ) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12376_c_macro_;
    // $volatile mantissa_33_bits := ( $mux shift_by_one ( $slice
    // frac_result_35_with_implied_shift 33 1 ) ( $slice
    // frac_result_35_with_implied_shift 32 0 ) ) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12384_c_macro_;
    // $volatile mantissa_62_bits := (mantissa_33_bits && ($bitcast
    // ($uint<29>) _b0 )) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12390_c_macro_;
    // $volatile sticky_raw := (thrown_away_bit |
    // value_of_bits_thrown_away_greater_than_zero) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12395_c_macro_;
    // $volatile exponent_correction := ( $mux shift_by_one exp_base_1
    // exp_base_0 ) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12401_c_macro_;
    // $volatile exponent_without_bias := (exp_ab + exponent_correction)
    // $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12406_c_macro_;
    // $volatile SP_overflow := (exponent_without_bias > 127 ) $buffering
    // 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12411_c_macro_;
    // $volatile SP_underflow := (exponent_without_bias < -126 )
    // $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12416_c_macro_;
    // $volatile overflow := SP_overflow $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12419_c_macro_;
    // $volatile condition_zero := (f1_zero | f2_zero) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12424_c_macro_;
    // $volatile condition_nan := ((f1_nan | f2_nan) | ((f1_zero & f2_inf) 
    // | (f1_inf & f2_zero))) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12437_c_macro_;
    // $volatile condition_inf := (((f1_inf & ((f2_inf | f2_normal) |
    // f2_denormal)) | (f2_inf & ((f1_inf | f1_normal) | f1_denormal))) |
    // overflow) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12456_c_macro_;
    // $volatile underflow := (( ~ condition_zero ) & SP_underflow)
    // $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12462_c_macro_;
    // $volatile sticky := ((sticky_raw & ( ~ condition_zero )) & (( ~
    // condition_inf ) & ( ~ condition_nan ))) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12474_c_macro_;
    // $volatile SP_nothing_to_be_done_condition_normal := (((( ~ overflow 
    // ) & ( ~ underflow )) & ( ~ condition_zero )) & (( ~ condition_inf ) 
    // & ( ~ condition_nan ))) $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12490_c_macro_;
    // $volatile SP_normalization_required := (((overflow | underflow) & ( 
    // ~ condition_zero )) & (( ~ condition_inf ) & ( ~ condition_nan )))
    // $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12504_c_macro_;
    // $volatile normalization_required := SP_normalization_required
    // $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12507_c_macro_;
    // $volatile nothing_to_be_done_condition_normal :=
    // SP_nothing_to_be_done_condition_normal $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12510_c_macro_;
    // condition_nan_d := condition_nan $buffering 1// bits of buffering = 
    // 1. 
    fpunit_exec_exec__fpmul32_op_assign_stmt_12513_c_macro_;
    // condition_zero_d := condition_zero $buffering 1// bits of buffering 
    // = 1. 
    fpunit_exec_exec__fpmul32_op_assign_stmt_12516_c_macro_;
    // $volatile exponent_to_be_passed := ((( $mux (condition_nan_d |
    // condition_inf) ALL_ONE_13 _b0 ) | ( $mux condition_zero_d ($bitcast 
    // ($int<13>) ZERO_13 ) _b0 ) ) | ( $mux (normalization_required |
    // nothing_to_be_done_condition_normal) exponent_without_bias _b0 ) )
    // $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12537_c_macro_;
    // $volatile mantissa_to_be_passed := ((( $mux condition_nan_d (ONE_1
    // && ZERO_61) _b0 ) | ( $mux condition_inf ZERO_62 _b0 ) ) | (( $mux
    // condition_zero_d ZERO_62 _b0 ) | ( $mux (normalization_required |
    // nothing_to_be_done_condition_normal) mantissa_62_bits _b0 ) ))
    // $buffering 1
    fpunit_exec_exec__fpmul32_op_assign_stmt_12562_c_macro_;
    // needs_norm := ((normalization_required & ( ~ condition_zero_d )) &
    // (( ~ condition_inf ) & ( ~ condition_nan_d ))) $buffering 2// bits
    // of buffering = 2. 
    fpunit_exec_exec__fpmul32_op_assign_stmt_12574_c_macro_;
    // extn_result := (((sticky && nothing_to_be_done_condition_normal) && 
    // (sign_result && condition_nan_d)) && ((condition_inf &&
    // condition_zero_d) && (($bitcast ($uint<13>) exponent_to_be_passed ) 
    // && mantissa_to_be_passed))) $buffering 2// bits of buffering = 162. 
    // 
    fpunit_exec_exec__fpmul32_op_assign_stmt_12592_c_macro_;
    fpunit_exec_exec__fpmul32_op_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fpmul32_op_series_block_stmt_12198_c_mutex_);
}
void
_fpunit_exec_exec_fpmul32_wrap_(float *__pX, float *__pY, float *__pRESULT)
{
    MUTEX_DECL
	(fpunit_exec_exec__fpmul32_wrap_series_block_stmt_18806_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fpmul32_wrap_series_block_stmt_18806_c_mutex_);
    fpunit_exec_exec__fpmul32_wrap_inner_inarg_prep_macro__;
    // $volatile $call classFp32 (X ) (xpn xnn xpd xnd xqnan xsnan xpi xni 
    // xpz xnz ) 
    fpunit_exec_exec__fpmul32_wrap_call_stmt_18821_c_macro_;
    // x_class := ((((xpn && xnn) && xpd) && (xnd && xqnan)) && (((xsnan
    // && xpi) && xni) && (xpz && xnz))) $buffering 1// bits of buffering
    // = 10. 
    fpunit_exec_exec__fpmul32_wrap_assign_stmt_18842_c_macro_;
    // $volatile $call classFp32 (Y ) (ypn ynn ypd ynd yqnan ysnan ypi yni 
    // ypz ynz ) 
    fpunit_exec_exec__fpmul32_wrap_call_stmt_18854_c_macro_;
    // y_class := ((((ypn && ynn) && ypd) && (ynd && yqnan)) && (((ysnan
    // && ypi) && yni) && (ypz && ynz))) $buffering 1// bits of buffering
    // = 10. 
    fpunit_exec_exec__fpmul32_wrap_assign_stmt_18875_c_macro_;
    // $call fpmul64_op (ONE_1 ZERO_1 ($bitcast ($uint<32>) X ) x_class
    // ($bitcast ($uint<32>) Y ) y_class _b0 _b0 _b0 _b0 )
    // (denormalize_flag_mul extn_result_mul ) 
    fpunit_exec_exec__fpmul32_wrap_call_stmt_18890_c_macro_;
    // $volatile $call round_fp_32 (extn_result_mul ) (muls_result_fast ) 
    fpunit_exec_exec__fpmul32_wrap_call_stmt_18893_c_macro_;
    // $guard (denormalize_flag_mul) $call denormalize_fp_32
    // (extn_result_mul ) (muls_result_slow ) 
    fpunit_exec_exec__fpmul32_wrap_call_stmt_18897_c_macro_;
    // $volatile RESULT := ($bitcast ($float<8,23>) ( $mux
    // denormalize_flag_mul muls_result_slow muls_result_fast ) )
    // $buffering 1
    fpunit_exec_exec__fpmul32_wrap_assign_stmt_18904_c_macro_;
    fpunit_exec_exec__fpmul32_wrap_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fpmul32_wrap_series_block_stmt_18806_c_mutex_);
}
void
fpunit_exec_exec_fpmul32_wrap(float X, float Y, float *RESULT)
{
    float           __RESULT;
    fpunit_exec_exec__fpmul32_wrap_outer_arg_decl_macro__;
    _fpunit_exec_exec_fpmul32_wrap_(&__X, &__Y, &__RESULT);
    fpunit_exec_exec__fpmul32_wrap_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fpmul32_wrap_new_(float *__pX, float *__pY,
				    float *__pRESULT)
{
    MUTEX_DECL
	(fpunit_exec_exec__fpmul32_wrap_new_series_block_stmt_18906_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fpmul32_wrap_new_series_block_stmt_18906_c_mutex_);
    fpunit_exec_exec__fpmul32_wrap_new_inner_inarg_prep_macro__;
    // $volatile $call classFp32 (X ) (xpn xnn xpd xnd xqnan xsnan xpi xni 
    // xpz xnz ) 
    fpunit_exec_exec__fpmul32_wrap_new_call_stmt_18921_c_macro_;
    // x_class := ((((xpn && xnn) && xpd) && (xnd && xqnan)) && (((xsnan
    // && xpi) && xni) && (xpz && xnz))) $buffering 1// bits of buffering
    // = 10. 
    fpunit_exec_exec__fpmul32_wrap_new_assign_stmt_18942_c_macro_;
    // $volatile $call classFp32 (Y ) (ypn ynn ypd ynd yqnan ysnan ypi yni 
    // ypz ynz ) 
    fpunit_exec_exec__fpmul32_wrap_new_call_stmt_18954_c_macro_;
    // y_class := ((((ypn && ynn) && ypd) && (ynd && yqnan)) && (((ysnan
    // && ypi) && yni) && (ypz && ynz))) $buffering 1// bits of buffering
    // = 10. 
    fpunit_exec_exec__fpmul32_wrap_new_assign_stmt_18975_c_macro_;
    // $call fpmul32_op (($bitcast ($uint<32>) X ) x_class ($bitcast
    // ($uint<32>) Y ) y_class ) (denormalize_flag_mul extn_result_mul ) 
    fpunit_exec_exec__fpmul32_wrap_new_call_stmt_18984_c_macro_;
    // $volatile $call round_fp_32 (extn_result_mul ) (muls_result_fast ) 
    fpunit_exec_exec__fpmul32_wrap_new_call_stmt_18987_c_macro_;
    // $guard (denormalize_flag_mul) $call denormalize_fp_32
    // (extn_result_mul ) (muls_result_slow ) 
    fpunit_exec_exec__fpmul32_wrap_new_call_stmt_18991_c_macro_;
    // $volatile RESULT := ($bitcast ($float<8,23>) ( $mux
    // denormalize_flag_mul muls_result_slow muls_result_fast ) )
    // $buffering 1
    fpunit_exec_exec__fpmul32_wrap_new_assign_stmt_18998_c_macro_;
    fpunit_exec_exec__fpmul32_wrap_new_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fpmul32_wrap_new_series_block_stmt_18906_c_mutex_);
}
void
fpunit_exec_exec_fpmul32_wrap_new(float X, float Y, float *RESULT)
{
    float           __RESULT;
    fpunit_exec_exec__fpmul32_wrap_new_outer_arg_decl_macro__;
    _fpunit_exec_exec_fpmul32_wrap_new_(&__X, &__Y, &__RESULT);
    fpunit_exec_exec__fpmul32_wrap_new_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fpmul64_op_(bit_vector * __puse_single_precision_inputs,
			      bit_vector * __pdouble_precision_outputs,
			      bit_vector * __puf1_s,
			      bit_vector * __pf1_s_class,
			      bit_vector * __puf2_s,
			      bit_vector * __pf2_s_class,
			      bit_vector * __puf1_d_i,
			      bit_vector * __pf1_d_class,
			      bit_vector * __puf2_d_i,
			      bit_vector * __pf2_d_class,
			      bit_vector * __pneeds_norm,
			      bit_vector * __pextn_result)
{
    MUTEX_DECL
	(fpunit_exec_exec__fpmul64_op_series_block_stmt_12810_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fpmul64_op_series_block_stmt_12810_c_mutex_);
    fpunit_exec_exec__fpmul64_op_inner_inarg_prep_macro__;
    // $volatile $call classify_utility (use_single_precision_inputs
    // f1_s_class f1_d_class ) (f1_zero f1_normal f1_denormal f1_nan
    // f1_inf f1_pos_inf f1_neg_inf ) 
    fpunit_exec_exec__fpmul64_op_call_stmt_12833_c_macro_;
    // $volatile $call classify_utility (use_single_precision_inputs
    // f2_s_class f2_d_class ) (f2_zero f2_normal f2_denormal f2_nan
    // f2_inf f2_pos_inf f2_neg_inf ) 
    fpunit_exec_exec__fpmul64_op_call_stmt_12844_c_macro_;
    // $volatile $call SingleToExtendedFp (uf1_s f1_s_class ) (uf1_s_efp ) 
    // 
    fpunit_exec_exec__fpmul64_op_call_stmt_12848_c_macro_;
    // $volatile $call SingleToExtendedFp (uf2_s f2_s_class ) (uf2_s_efp ) 
    // 
    fpunit_exec_exec__fpmul64_op_call_stmt_12852_c_macro_;
    // $volatile $call DoubleToExtendedFp (uf1_d_i f1_d_class )
    // (uf1_d_i_efp ) 
    fpunit_exec_exec__fpmul64_op_call_stmt_12856_c_macro_;
    // $volatile $call DoubleToExtendedFp (uf2_d_i f2_d_class )
    // (uf2_d_i_efp ) 
    fpunit_exec_exec__fpmul64_op_call_stmt_12860_c_macro_;
    // $volatile uf1_d_efp := ( $mux use_single_precision_inputs uf1_s_efp 
    // uf1_d_i_efp ) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12866_c_macro_;
    // $volatile uf2_d_efp := ( $mux use_single_precision_inputs uf2_s_efp 
    // uf2_d_i_efp ) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12872_c_macro_;
    // $volatile sign_uf1_d := ( $slice uf1_d_efp 66 66 ) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12876_c_macro_;
    // $volatile f1_exp13_unbiased := ( $slice uf1_d_efp 65 53 )
    // $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12880_c_macro_;
    // $volatile f1_top_bit := ( $slice uf1_d_efp 52 52 ) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12884_c_macro_;
    // $volatile f1_fraction := ( $slice uf1_d_efp 51 0 ) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12888_c_macro_;
    // $volatile sign_uf2_d := ( $slice uf2_d_efp 66 66 ) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12892_c_macro_;
    // $volatile f2_exp13_unbiased := ( $slice uf2_d_efp 65 53 )
    // $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12896_c_macro_;
    // $volatile f2_top_bit := ( $slice uf2_d_efp 52 52 ) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12900_c_macro_;
    // $volatile f2_fraction := ( $slice uf2_d_efp 51 0 ) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12904_c_macro_;
    // $volatile sign_result := (sign_uf1_d ^ sign_uf2_d) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12909_c_macro_;
    // $volatile f1_frac_v := (f1_top_bit && f1_fraction) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12914_c_macro_;
    // $volatile f2_frac_v := (f2_top_bit && f2_fraction) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12919_c_macro_;
    // $volatile exp_a := ($bitcast ($int<13>) f1_exp13_unbiased )
    // $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12923_c_macro_;
    // $volatile exp_b := ($bitcast ($int<13>) f2_exp13_unbiased )
    // $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12927_c_macro_;
    // $volatile $call find_left_53 (f1_frac_v ) (f1_top_bit_pos
    // f1_top_bit_found ) 
    fpunit_exec_exec__fpmul64_op_call_stmt_12931_c_macro_;
    // $volatile $call find_left_53 (f2_frac_v ) (f2_top_bit_pos
    // f2_top_bit_found ) 
    fpunit_exec_exec__fpmul64_op_call_stmt_12935_c_macro_;
    // $volatile f1_left_shift_correction := ($bitcast ($int<13>) (52 -
    // f1_top_bit_pos) ) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12941_c_macro_;
    // $volatile exp_a_corrected := (exp_a - f1_left_shift_correction)
    // $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12946_c_macro_;
    // $volatile f2_left_shift_correction := ($bitcast ($int<13>) (52 -
    // f2_top_bit_pos) ) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12952_c_macro_;
    // $volatile exp_b_corrected := (exp_b - f2_left_shift_correction)
    // $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12957_c_macro_;
    // $volatile mul_result_left_shift_amount := (f1_left_shift_correction 
    // + f2_left_shift_correction) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12962_c_macro_;
    // $volatile exp_ab := (exp_a_corrected + exp_b_corrected) $buffering
    // 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12967_c_macro_;
    // $call mul53 (f1_frac_v f2_frac_v ) (frac_result_106bits ) 
    fpunit_exec_exec__fpmul64_op_call_stmt_12971_c_macro_;
    // $volatile frac_result_64 := ( $slice frac_result_106bits 105 42 )
    // $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12975_c_macro_;
    // $volatile value_of_bits_thrown_away_greater_than_zero := ( ~ ((
    // $slice frac_result_106bits 41 0 ) == 0 ) ) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12982_c_macro_;
    // $volatile implied_shift_amount := ($bitcast ($uint<6>)
    // mul_result_left_shift_amount ) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12986_c_macro_;
    // $volatile $call i64_sll (frac_result_64 implied_shift_amount )
    // (frac_result_64_with_implied_shift_raw ) 
    fpunit_exec_exec__fpmul64_op_call_stmt_12990_c_macro_;
    // $volatile frac_result_64_with_implied_shift := ( $mux
    // (mul_result_left_shift_amount > 63 ) 0
    // frac_result_64_with_implied_shift_raw ) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_12998_c_macro_;
    // $volatile shift_by_one := (frac_result_64_with_implied_shift [] 63
    // ) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_13003_c_macro_;
    // $volatile thrown_away_bit := ( $mux shift_by_one
    // (frac_result_64_with_implied_shift [] 0 ) _b0 ) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_13011_c_macro_;
    // $volatile mantissa_62_bits := ( $mux shift_by_one ( $slice
    // frac_result_64_with_implied_shift 62 1 ) ( $slice
    // frac_result_64_with_implied_shift 61 0 ) ) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_13019_c_macro_;
    // $volatile sticky_raw := (thrown_away_bit |
    // value_of_bits_thrown_away_greater_than_zero) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_13024_c_macro_;
    // $volatile exponent_correction := ( $mux shift_by_one exp_base_1
    // exp_base_0 ) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_13030_c_macro_;
    // $volatile exponent_without_bias := (exp_ab + exponent_correction)
    // $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_13035_c_macro_;
    // $volatile DP_overflow := (exponent_without_bias > 1023 ) $buffering 
    // 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_13040_c_macro_;
    // $volatile DP_underflow := (exponent_without_bias < -1022 )
    // $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_13045_c_macro_;
    // $volatile SP_overflow := (exponent_without_bias > 127 ) $buffering
    // 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_13050_c_macro_;
    // $volatile SP_underflow := (exponent_without_bias < -126 )
    // $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_13055_c_macro_;
    // $volatile overflow := ( $mux double_precision_outputs DP_overflow
    // SP_overflow ) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_13061_c_macro_;
    // $volatile condition_zero := (f1_zero | f2_zero) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_13066_c_macro_;
    // $volatile condition_nan := ((f1_nan | f2_nan) | ((f1_zero & f2_inf) 
    // | (f1_inf & f2_zero))) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_13079_c_macro_;
    // $volatile condition_inf := (((f1_inf & ((f2_inf | f2_normal) |
    // f2_denormal)) | (f2_inf & ((f1_inf | f1_normal) | f1_denormal))) |
    // overflow) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_13098_c_macro_;
    // $volatile underflow := (( ~ condition_zero ) & ( $mux
    // double_precision_outputs DP_underflow SP_underflow ) ) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_13107_c_macro_;
    // $volatile sticky := ((sticky_raw & ( ~ condition_zero )) & (( ~
    // condition_inf ) & ( ~ condition_nan ))) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_13119_c_macro_;
    // $volatile SP_nothing_to_be_done_condition_normal := (((( ~ overflow 
    // ) & ( ~ underflow )) & ( ~ condition_zero )) & (( ~ condition_inf ) 
    // & ( ~ condition_nan ))) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_13135_c_macro_;
    // $volatile SP_normalization_required := (((overflow | underflow) & ( 
    // ~ condition_zero )) & (( ~ condition_inf ) & ( ~ condition_nan )))
    // $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_13149_c_macro_;
    // $volatile DP_nothing_to_be_done_condition_normal := (((( ~ overflow 
    // ) & ( ~ underflow )) & ( ~ condition_zero )) & (( ~ condition_inf ) 
    // & ( ~ condition_nan ))) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_13165_c_macro_;
    // $volatile DP_normalization_required := (((overflow | underflow) & ( 
    // ~ condition_zero )) & (( ~ condition_inf ) & ( ~ condition_nan )))
    // $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_13179_c_macro_;
    // $volatile normalization_required := ( $mux double_precision_outputs 
    // DP_normalization_required SP_normalization_required ) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_13185_c_macro_;
    // $volatile nothing_to_be_done_condition_normal := ( $mux
    // double_precision_outputs DP_nothing_to_be_done_condition_normal
    // SP_nothing_to_be_done_condition_normal ) $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_13191_c_macro_;
    // condition_nan_d := condition_nan $buffering 1// bits of buffering = 
    // 1. 
    fpunit_exec_exec__fpmul64_op_assign_stmt_13194_c_macro_;
    // condition_zero_d := condition_zero $buffering 1// bits of buffering 
    // = 1. 
    fpunit_exec_exec__fpmul64_op_assign_stmt_13197_c_macro_;
    // $volatile exponent_to_be_passed := ((( $mux (condition_nan_d |
    // condition_inf) ALL_ONE_13 _b0 ) | ( $mux condition_zero_d ($bitcast 
    // ($int<13>) ZERO_13 ) _b0 ) ) | ( $mux (normalization_required |
    // nothing_to_be_done_condition_normal) exponent_without_bias _b0 ) )
    // $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_13218_c_macro_;
    // $volatile mantissa_to_be_passed := ((( $mux condition_nan_d (ONE_1
    // && ZERO_61) _b0 ) | ( $mux condition_inf ZERO_62 _b0 ) ) | (( $mux
    // condition_zero_d ZERO_62 _b0 ) | ( $mux (normalization_required |
    // nothing_to_be_done_condition_normal) mantissa_62_bits _b0 ) ))
    // $buffering 1
    fpunit_exec_exec__fpmul64_op_assign_stmt_13243_c_macro_;
    // needs_norm := ((normalization_required & ( ~ condition_zero_d )) &
    // (( ~ condition_inf ) & ( ~ condition_nan_d ))) $buffering 2// bits
    // of buffering = 2. 
    fpunit_exec_exec__fpmul64_op_assign_stmt_13255_c_macro_;
    // extn_result := (((sticky && ZERO_1) && (sign_result &&
    // condition_nan_d)) && ((condition_inf && condition_zero_d) &&
    // (($bitcast ($uint<13>) exponent_to_be_passed ) &&
    // mantissa_to_be_passed))) $buffering 2// bits of buffering = 162. 
    fpunit_exec_exec__fpmul64_op_assign_stmt_13273_c_macro_;
    fpunit_exec_exec__fpmul64_op_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fpmul64_op_series_block_stmt_12810_c_mutex_);
}
void
_fpunit_exec_exec_fpmul64_wrap_(double *__pX, double *__pY,
				double *__pRESULT)
{
    MUTEX_DECL
	(fpunit_exec_exec__fpmul64_wrap_series_block_stmt_19000_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fpmul64_wrap_series_block_stmt_19000_c_mutex_);
    fpunit_exec_exec__fpmul64_wrap_inner_inarg_prep_macro__;
    // $volatile $call classFp64 (X ) (xpn xnn xpd xnd xqnan xsnan xpi xni 
    // xpz xnz ) 
    fpunit_exec_exec__fpmul64_wrap_call_stmt_19015_c_macro_;
    // x_class := ((((xpn && xnn) && xpd) && (xnd && xqnan)) && (((xsnan
    // && xpi) && xni) && (xpz && xnz))) $buffering 1// bits of buffering
    // = 10. 
    fpunit_exec_exec__fpmul64_wrap_assign_stmt_19036_c_macro_;
    // $volatile $call classFp64 (Y ) (ypn ynn ypd ynd yqnan ysnan ypi yni 
    // ypz ynz ) 
    fpunit_exec_exec__fpmul64_wrap_call_stmt_19048_c_macro_;
    // y_class := ((((ypn && ynn) && ypd) && (ynd && yqnan)) && (((ysnan
    // && ypi) && yni) && (ypz && ynz))) $buffering 1// bits of buffering
    // = 10. 
    fpunit_exec_exec__fpmul64_wrap_assign_stmt_19069_c_macro_;
    // $call fpmul64_op (ZERO_1 ONE_1 _b0 _b0 _b0 _b0 ($bitcast
    // ($uint<64>) X ) x_class ($bitcast ($uint<64>) Y ) y_class )
    // (denormalize_flag_mul extn_result_mul ) 
    fpunit_exec_exec__fpmul64_wrap_call_stmt_19084_c_macro_;
    // $volatile $call round_fp_64 (extn_result_mul ) (muld_result_fast ) 
    fpunit_exec_exec__fpmul64_wrap_call_stmt_19087_c_macro_;
    // $guard (denormalize_flag_mul) $call denormalize_fp_64
    // (extn_result_mul ) (muld_result_slow ) 
    fpunit_exec_exec__fpmul64_wrap_call_stmt_19091_c_macro_;
    // $volatile RESULT := ($bitcast ($float<11,52>) ( $mux
    // denormalize_flag_mul muld_result_slow muld_result_fast ) )
    // $buffering 1
    fpunit_exec_exec__fpmul64_wrap_assign_stmt_19098_c_macro_;
    fpunit_exec_exec__fpmul64_wrap_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fpmul64_wrap_series_block_stmt_19000_c_mutex_);
}
void
fpunit_exec_exec_fpmul64_wrap(double X, double Y, double *RESULT)
{
    double          __RESULT;
    fpunit_exec_exec__fpmul64_wrap_outer_arg_decl_macro__;
    _fpunit_exec_exec_fpmul64_wrap_(&__X, &__Y, &__RESULT);
    fpunit_exec_exec__fpmul64_wrap_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fpsqrt32_bit_wise_(float *__pa, float *__psqrt_a)
{
    MUTEX_DECL
	(fpunit_exec_exec__fpsqrt32_bit_wise_series_block_stmt_15177_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fpsqrt32_bit_wise_series_block_stmt_15177_c_mutex_);
    fpunit_exec_exec__fpsqrt32_bit_wise_inner_inarg_prep_macro__;
    // $volatile $call classify_and_prepare_32 (a ) (e_e e_m special_case
    // special_case_result ) 
    fpunit_exec_exec__fpsqrt32_bit_wise_call_stmt_15185_c_macro_;
    // $report (fpdiv32bitwise fpsqrt32_bit_wise_in_args__ a a e_e e_e e_m 
    // e_m special_case special_case special_case_result
    // special_case_result )
    fpunit_exec_exec__fpsqrt32_bit_wise_stmt_15191_c_macro_;
    // $guard (~special_case) $call short_sqrt_32 (e_m ) (sticky s_e_m ) 
    fpunit_exec_exec__fpsqrt32_bit_wise_call_stmt_15196_c_macro_;
    // $guard (~special_case) $report (fpdiv32bitwise
    // fpsqrt32_bit_wise_post_short_sqrt sticky sticky e_m e_m s_e_m s_e_m 
    // )
    fpunit_exec_exec__fpsqrt32_bit_wise_stmt_15201_c_macro_;
    // $volatile s_e_e := ( $mux ((e_e < 0 ) & (e_e == -1 )) 0 (e_e >> 1 ) 
    // ) $buffering 1
    fpunit_exec_exec__fpsqrt32_bit_wise_assign_stmt_15215_c_macro_;
    // $report (fpdiv32bitwise fpsqrt32_bit_wise_to_round s_e_e s_e_e
    // s_e_m s_e_m )
    fpunit_exec_exec__fpsqrt32_bit_wise_stmt_15218_c_macro_;
    // $volatile sticky_qualified := ( $mux special_case _b0 sticky )
    // $buffering 1
    fpunit_exec_exec__fpsqrt32_bit_wise_assign_stmt_15224_c_macro_;
    // $volatile s_e_e_qualified := ( $mux special_case _b0 s_e_e )
    // $buffering 1
    fpunit_exec_exec__fpsqrt32_bit_wise_assign_stmt_15230_c_macro_;
    // $volatile s_e_m_qualified := ( $mux special_case _b0 s_e_m )
    // $buffering 1
    fpunit_exec_exec__fpsqrt32_bit_wise_assign_stmt_15236_c_macro_;
    // $volatile $call round_e_32 (sticky_qualified s_e_e_qualified
    // s_e_m_qualified ) (fsqrt32_normalized_result ) 
    fpunit_exec_exec__fpsqrt32_bit_wise_call_stmt_15241_c_macro_;
    // $volatile ur := ($bitcast ($uint<32>) fsqrt32_normalized_result )
    // $buffering 1
    fpunit_exec_exec__fpsqrt32_bit_wise_assign_stmt_15245_c_macro_;
    // $report (fpdiv32bitwise fpsqrt32_bit_wise_from_round ur ur )
    fpunit_exec_exec__fpsqrt32_bit_wise_stmt_15247_c_macro_;
    // $volatile sqrt_a := ( $mux special_case special_case_result
    // fsqrt32_normalized_result ) $buffering 1
    fpunit_exec_exec__fpsqrt32_bit_wise_assign_stmt_15253_c_macro_;
    fpunit_exec_exec__fpsqrt32_bit_wise_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fpsqrt32_bit_wise_series_block_stmt_15177_c_mutex_);
}
void
fpunit_exec_exec_fpsqrt32_bit_wise(float a, float *sqrt_a)
{
    float           __sqrt_a;
    fpunit_exec_exec__fpsqrt32_bit_wise_outer_arg_decl_macro__;
    _fpunit_exec_exec_fpsqrt32_bit_wise_(&__a, &__sqrt_a);
    fpunit_exec_exec__fpsqrt32_bit_wise_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fpsqrt64_bit_wise_(double *__pa, double *__psqrt_a)
{
    MUTEX_DECL
	(fpunit_exec_exec__fpsqrt64_bit_wise_series_block_stmt_16255_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fpsqrt64_bit_wise_series_block_stmt_16255_c_mutex_);
    fpunit_exec_exec__fpsqrt64_bit_wise_inner_inarg_prep_macro__;
    // $volatile $call classify_and_prepare_64 (a ) (e_e e_m special_case
    // special_case_result ) 
    fpunit_exec_exec__fpsqrt64_bit_wise_call_stmt_16263_c_macro_;
    // $report (fpdiv64bitwise fpsqrt64_bit_wise_in_args__ a a e_e e_e e_m 
    // e_m special_case special_case special_case_result
    // special_case_result )
    fpunit_exec_exec__fpsqrt64_bit_wise_stmt_16269_c_macro_;
    // $guard (~special_case) $call short_sqrt_56 (e_m ) (sticky s_e_m ) 
    fpunit_exec_exec__fpsqrt64_bit_wise_call_stmt_16274_c_macro_;
    // $guard (~special_case) $report (fpdiv64bitwise
    // fpsqrt64_bit_wise_post_short_sqrt sticky sticky e_m e_m s_e_m s_e_m 
    // )
    fpunit_exec_exec__fpsqrt64_bit_wise_stmt_16279_c_macro_;
    // $volatile s_e_e := ( $mux ((e_e < 0 ) & (e_e == -1 )) 0 (e_e >> 1 ) 
    // ) $buffering 1
    fpunit_exec_exec__fpsqrt64_bit_wise_assign_stmt_16293_c_macro_;
    // $report (fpdiv64bitwise fpsqrt64_bit_wise_to_round s_e_e s_e_e
    // s_e_m s_e_m )
    fpunit_exec_exec__fpsqrt64_bit_wise_stmt_16296_c_macro_;
    // $volatile sticky_qualified := ( $mux special_case _b0 sticky )
    // $buffering 1
    fpunit_exec_exec__fpsqrt64_bit_wise_assign_stmt_16302_c_macro_;
    // $volatile s_e_e_qualified := ( $mux special_case _b0 s_e_e )
    // $buffering 1
    fpunit_exec_exec__fpsqrt64_bit_wise_assign_stmt_16308_c_macro_;
    // $volatile s_e_m_qualified := ( $mux special_case _b0 s_e_m )
    // $buffering 1
    fpunit_exec_exec__fpsqrt64_bit_wise_assign_stmt_16314_c_macro_;
    // $volatile $call round_e_64 (sticky_qualified s_e_e_qualified
    // s_e_m_qualified ) (fsqrt64_normalized_result ) 
    fpunit_exec_exec__fpsqrt64_bit_wise_call_stmt_16319_c_macro_;
    // $volatile ur := ($bitcast ($uint<64>) fsqrt64_normalized_result )
    // $buffering 1
    fpunit_exec_exec__fpsqrt64_bit_wise_assign_stmt_16323_c_macro_;
    // $report (fpdiv64bitwise fpsqrt64_bit_wise_from_round ur ur )
    fpunit_exec_exec__fpsqrt64_bit_wise_stmt_16325_c_macro_;
    // $volatile sqrt_a := ( $mux special_case special_case_result
    // fsqrt64_normalized_result ) $buffering 1
    fpunit_exec_exec__fpsqrt64_bit_wise_assign_stmt_16331_c_macro_;
    fpunit_exec_exec__fpsqrt64_bit_wise_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fpsqrt64_bit_wise_series_block_stmt_16255_c_mutex_);
}
void
fpunit_exec_exec_fpsqrt64_bit_wise(double a, double *sqrt_a)
{
    double          __sqrt_a;
    fpunit_exec_exec__fpsqrt64_bit_wise_outer_arg_decl_macro__;
    _fpunit_exec_exec_fpsqrt64_bit_wise_(&__a, &__sqrt_a);
    fpunit_exec_exec__fpsqrt64_bit_wise_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fpsub32_wrap_(float *__pX, float *__pY, float *__pRESULT)
{
    MUTEX_DECL
	(fpunit_exec_exec__fpsub32_wrap_series_block_stmt_19100_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fpsub32_wrap_series_block_stmt_19100_c_mutex_);
    fpunit_exec_exec__fpsub32_wrap_inner_inarg_prep_macro__;
    // $volatile $call classFp32 (X ) (xpn xnn xpd xnd xqnan xsnan xpi xni 
    // xpz xnz ) 
    fpunit_exec_exec__fpsub32_wrap_call_stmt_19115_c_macro_;
    // x_class := ((((xpn && xnn) && xpd) && (xnd && xqnan)) && (((xsnan
    // && xpi) && xni) && (xpz && xnz))) $buffering 1// bits of buffering
    // = 10. 
    fpunit_exec_exec__fpsub32_wrap_assign_stmt_19136_c_macro_;
    // $volatile $call classFp32 (Y ) (ypn ynn ypd ynd yqnan ysnan ypi yni 
    // ypz ynz ) 
    fpunit_exec_exec__fpsub32_wrap_call_stmt_19148_c_macro_;
    // y_class := ((((ypn && ynn) && ypd) && (ynd && yqnan)) && (((ysnan
    // && ypi) && yni) && (ypz && ynz))) $buffering 1// bits of buffering
    // = 10. 
    fpunit_exec_exec__fpsub32_wrap_assign_stmt_19169_c_macro_;
    // $volatile $call negate_classification (y_class ) (y_n_class ) 
    fpunit_exec_exec__fpsub32_wrap_call_stmt_19172_c_macro_;
    // uY := ($bitcast ($uint<32>) Y ) $buffering 1// bits of buffering =
    // 32. 
    fpunit_exec_exec__fpsub32_wrap_assign_stmt_19176_c_macro_;
    // unY := (( ~ (uY [] 31 ) ) && ( $slice uY 30 0 ) ) $buffering 1//
    // bits of buffering = 32. 
    fpunit_exec_exec__fpsub32_wrap_assign_stmt_19185_c_macro_;
    // $call fpadd64_op (ONE_1 ZERO_1 ($bitcast ($uint<32>) X ) x_class
    // unY y_n_class _b0 _b0 _b0 _b0 ) (denormalize_flag_add
    // extn_result_add ) 
    fpunit_exec_exec__fpsub32_wrap_call_stmt_19199_c_macro_;
    // $volatile $call round_fp_32 (extn_result_add ) (adds_result_fast ) 
    fpunit_exec_exec__fpsub32_wrap_call_stmt_19202_c_macro_;
    // $guard (denormalize_flag_add) $call denormalize_fp_32
    // (extn_result_add ) (adds_result_slow ) 
    fpunit_exec_exec__fpsub32_wrap_call_stmt_19206_c_macro_;
    // $volatile RESULT := ($bitcast ($float<8,23>) ( $mux
    // denormalize_flag_add adds_result_slow adds_result_fast ) )
    // $buffering 1
    fpunit_exec_exec__fpsub32_wrap_assign_stmt_19213_c_macro_;
    fpunit_exec_exec__fpsub32_wrap_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fpsub32_wrap_series_block_stmt_19100_c_mutex_);
}
void
fpunit_exec_exec_fpsub32_wrap(float X, float Y, float *RESULT)
{
    float           __RESULT;
    fpunit_exec_exec__fpsub32_wrap_outer_arg_decl_macro__;
    _fpunit_exec_exec_fpsub32_wrap_(&__X, &__Y, &__RESULT);
    fpunit_exec_exec__fpsub32_wrap_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fpsub32_wrap_new_(float *__pX, float *__pY,
				    float *__pRESULT)
{
    MUTEX_DECL
	(fpunit_exec_exec__fpsub32_wrap_new_series_block_stmt_19215_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fpsub32_wrap_new_series_block_stmt_19215_c_mutex_);
    fpunit_exec_exec__fpsub32_wrap_new_inner_inarg_prep_macro__;
    // $volatile $call classFp32 (X ) (xpn xnn xpd xnd xqnan xsnan xpi xni 
    // xpz xnz ) 
    fpunit_exec_exec__fpsub32_wrap_new_call_stmt_19230_c_macro_;
    // x_class := ((((xpn && xnn) && xpd) && (xnd && xqnan)) && (((xsnan
    // && xpi) && xni) && (xpz && xnz))) $buffering 1// bits of buffering
    // = 10. 
    fpunit_exec_exec__fpsub32_wrap_new_assign_stmt_19251_c_macro_;
    // $volatile $call classFp32 (Y ) (ypn ynn ypd ynd yqnan ysnan ypi yni 
    // ypz ynz ) 
    fpunit_exec_exec__fpsub32_wrap_new_call_stmt_19263_c_macro_;
    // y_class := ((((ypn && ynn) && ypd) && (ynd && yqnan)) && (((ysnan
    // && ypi) && yni) && (ypz && ynz))) $buffering 1// bits of buffering
    // = 10. 
    fpunit_exec_exec__fpsub32_wrap_new_assign_stmt_19284_c_macro_;
    // $volatile $call negate_classification (y_class ) (y_n_class ) 
    fpunit_exec_exec__fpsub32_wrap_new_call_stmt_19287_c_macro_;
    // uY := ($bitcast ($uint<32>) Y ) $buffering 1// bits of buffering =
    // 32. 
    fpunit_exec_exec__fpsub32_wrap_new_assign_stmt_19291_c_macro_;
    // unY := (( ~ (uY [] 31 ) ) && ( $slice uY 30 0 ) ) $buffering 1//
    // bits of buffering = 32. 
    fpunit_exec_exec__fpsub32_wrap_new_assign_stmt_19300_c_macro_;
    // $call fpadd32_op (($bitcast ($uint<32>) X ) x_class unY y_n_class ) 
    // (denormalize_flag_add extn_result_add ) 
    fpunit_exec_exec__fpsub32_wrap_new_call_stmt_19308_c_macro_;
    // $volatile $call round_fp_32 (extn_result_add ) (adds_result_fast ) 
    fpunit_exec_exec__fpsub32_wrap_new_call_stmt_19311_c_macro_;
    // $guard (denormalize_flag_add) $call denormalize_fp_32
    // (extn_result_add ) (adds_result_slow ) 
    fpunit_exec_exec__fpsub32_wrap_new_call_stmt_19315_c_macro_;
    // $volatile RESULT := ($bitcast ($float<8,23>) ( $mux
    // denormalize_flag_add adds_result_slow adds_result_fast ) )
    // $buffering 1
    fpunit_exec_exec__fpsub32_wrap_new_assign_stmt_19322_c_macro_;
    fpunit_exec_exec__fpsub32_wrap_new_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fpsub32_wrap_new_series_block_stmt_19215_c_mutex_);
}
void
fpunit_exec_exec_fpsub32_wrap_new(float X, float Y, float *RESULT)
{
    float           __RESULT;
    fpunit_exec_exec__fpsub32_wrap_new_outer_arg_decl_macro__;
    _fpunit_exec_exec_fpsub32_wrap_new_(&__X, &__Y, &__RESULT);
    fpunit_exec_exec__fpsub32_wrap_new_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fpsub64_wrap_(double *__pX, double *__pY,
				double *__pRESULT)
{
    MUTEX_DECL
	(fpunit_exec_exec__fpsub64_wrap_series_block_stmt_19324_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fpsub64_wrap_series_block_stmt_19324_c_mutex_);
    fpunit_exec_exec__fpsub64_wrap_inner_inarg_prep_macro__;
    // $volatile $call classFp64 (X ) (xpn xnn xpd xnd xqnan xsnan xpi xni 
    // xpz xnz ) 
    fpunit_exec_exec__fpsub64_wrap_call_stmt_19339_c_macro_;
    // x_class := ((((xpn && xnn) && xpd) && (xnd && xqnan)) && (((xsnan
    // && xpi) && xni) && (xpz && xnz))) $buffering 1// bits of buffering
    // = 10. 
    fpunit_exec_exec__fpsub64_wrap_assign_stmt_19360_c_macro_;
    // $volatile $call classFp64 (Y ) (ypn ynn ypd ynd yqnan ysnan ypi yni 
    // ypz ynz ) 
    fpunit_exec_exec__fpsub64_wrap_call_stmt_19372_c_macro_;
    // y_class := ((((ypn && ynn) && ypd) && (ynd && yqnan)) && (((ysnan
    // && ypi) && yni) && (ypz && ynz))) $buffering 1// bits of buffering
    // = 10. 
    fpunit_exec_exec__fpsub64_wrap_assign_stmt_19393_c_macro_;
    // $volatile $call negate_classification (y_class ) (y_n_class ) 
    fpunit_exec_exec__fpsub64_wrap_call_stmt_19396_c_macro_;
    // uY := ($bitcast ($uint<64>) Y ) $buffering 1// bits of buffering =
    // 64. 
    fpunit_exec_exec__fpsub64_wrap_assign_stmt_19400_c_macro_;
    // unY := (( ~ (uY [] 63 ) ) && ( $slice uY 62 0 ) ) $buffering 1//
    // bits of buffering = 64. 
    fpunit_exec_exec__fpsub64_wrap_assign_stmt_19409_c_macro_;
    // $call fpadd64_op (ZERO_1 ONE_1 _b0 _b0 _b0 _b0 ($bitcast
    // ($uint<64>) X ) x_class unY y_n_class ) (denormalize_flag_add
    // extn_result_add ) 
    fpunit_exec_exec__fpsub64_wrap_call_stmt_19423_c_macro_;
    // $volatile $call round_fp_64 (extn_result_add ) (addd_result_fast ) 
    fpunit_exec_exec__fpsub64_wrap_call_stmt_19426_c_macro_;
    // $guard (denormalize_flag_add) $call denormalize_fp_64
    // (extn_result_add ) (addd_result_slow ) 
    fpunit_exec_exec__fpsub64_wrap_call_stmt_19430_c_macro_;
    // $volatile RESULT := ($bitcast ($float<11,52>) ( $mux
    // denormalize_flag_add addd_result_slow addd_result_fast ) )
    // $buffering 1
    fpunit_exec_exec__fpsub64_wrap_assign_stmt_19437_c_macro_;
    fpunit_exec_exec__fpsub64_wrap_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fpsub64_wrap_series_block_stmt_19324_c_mutex_);
}
void
fpunit_exec_exec_fpsub64_wrap(double X, double Y, double *RESULT)
{
    double          __RESULT;
    fpunit_exec_exec__fpsub64_wrap_outer_arg_decl_macro__;
    _fpunit_exec_exec_fpsub64_wrap_(&__X, &__Y, &__RESULT);
    fpunit_exec_exec__fpsub64_wrap_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fpu_increment_64_(bit_vector * __pA, bit_vector * __pSUM)
{
    MUTEX_DECL
	(fpunit_exec_exec__fpu_increment_64_series_block_stmt_19439_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fpu_increment_64_series_block_stmt_19439_c_mutex_);
    fpunit_exec_exec__fpu_increment_64_inner_inarg_prep_macro__;
    // $volatile A0 := ( $slice A 15 0 ) $buffering 1
    fpunit_exec_exec__fpu_increment_64_assign_stmt_19445_c_macro_;
    // $volatile A1 := ( $slice A 31 16 ) $buffering 1
    fpunit_exec_exec__fpu_increment_64_assign_stmt_19449_c_macro_;
    // $volatile A2 := ( $slice A 47 32 ) $buffering 1
    fpunit_exec_exec__fpu_increment_64_assign_stmt_19453_c_macro_;
    // $volatile A3 := ( $slice A 63 48 ) $buffering 1
    fpunit_exec_exec__fpu_increment_64_assign_stmt_19457_c_macro_;
    // $volatile $call adder_18 (A0 0 ONE_1 ) (CIN1_S0 CIN1_C0 ) 
    fpunit_exec_exec__fpu_increment_64_call_stmt_19463_c_macro_;
    // $volatile $call adder_18 (A1 0 ONE_1 ) (CIN1_S1 CIN1_C1 ) 
    fpunit_exec_exec__fpu_increment_64_call_stmt_19469_c_macro_;
    // $volatile $call adder_18 (A2 0 ONE_1 ) (CIN1_S2 CIN1_C2 ) 
    fpunit_exec_exec__fpu_increment_64_call_stmt_19475_c_macro_;
    // $volatile $call adder_18 (A3 0 ONE_1 ) (CIN1_S3 CIN1_C3 ) 
    fpunit_exec_exec__fpu_increment_64_call_stmt_19481_c_macro_;
    // $volatile P0 := (A0 == ( ~ 0 )) $buffering 1
    fpunit_exec_exec__fpu_increment_64_assign_stmt_19487_c_macro_;
    // $volatile P1 := (A1 == ( ~ 0 )) $buffering 1
    fpunit_exec_exec__fpu_increment_64_assign_stmt_19493_c_macro_;
    // $volatile P2 := (A2 == ( ~ 0 )) $buffering 1
    fpunit_exec_exec__fpu_increment_64_assign_stmt_19499_c_macro_;
    // $volatile sum_0 := CIN1_S0 $buffering 1
    fpunit_exec_exec__fpu_increment_64_assign_stmt_19502_c_macro_;
    // $volatile carry_0 := P0 $buffering 1
    fpunit_exec_exec__fpu_increment_64_assign_stmt_19505_c_macro_;
    // $volatile sum_1 := ( $mux P0 CIN1_S1 A1 ) $buffering 1
    fpunit_exec_exec__fpu_increment_64_assign_stmt_19511_c_macro_;
    // $volatile carry_1 := (P1 & carry_0) $buffering 1
    fpunit_exec_exec__fpu_increment_64_assign_stmt_19516_c_macro_;
    // $volatile sum_2 := ( $mux carry_1 CIN1_S2 A2 ) $buffering 1
    fpunit_exec_exec__fpu_increment_64_assign_stmt_19522_c_macro_;
    // $volatile carry_2 := ((P0 & P1) & P2) $buffering 1
    fpunit_exec_exec__fpu_increment_64_assign_stmt_19529_c_macro_;
    // $volatile sum_3 := ( $mux carry_2 CIN1_S3 A3 ) $buffering 1
    fpunit_exec_exec__fpu_increment_64_assign_stmt_19535_c_macro_;
    // SUM := ((sum_3 && sum_2) && (sum_1 && sum_0)) $buffering 1
    fpunit_exec_exec__fpu_increment_64_assign_stmt_19544_c_macro_;
    fpunit_exec_exec__fpu_increment_64_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fpu_increment_64_series_block_stmt_19439_c_mutex_);
}
void
fpunit_exec_exec_fpu_increment_64(uint64_t A, uint64_t * SUM)
{
    fpunit_exec_exec__fpu_increment_64_outer_arg_decl_macro__;
    _fpunit_exec_exec_fpu_increment_64_(&__A, &__SUM);
    fpunit_exec_exec__fpu_increment_64_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fpunit_exec_pipe_merge_daemon_()
{
    MUTEX_DECL
	(fpunit_exec_exec__fpunit_exec_pipe_merge_daemon_series_block_stmt_19546_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fpunit_exec_pipe_merge_daemon_series_block_stmt_19546_c_mutex_);
    fpunit_exec_exec__fpunit_exec_pipe_merge_daemon_inner_inarg_prep_macro__;
    fpunit_exec_exec__fpunit_exec_pipe_merge_daemon_branch_block_stmt_19547_c_export_decl_macro_;
    {
	{
	    // do-while: file ./.Aa//linked.opt.aa, line 4216
	    __declare_static_bit_vector(konst_19579, 1);
	    bit_vector_clear(&konst_19579);
	    konst_19579.val.byte_array[0] = 1;
	    uint8_t         do_while_entry_flag;
	    do_while_entry_flag = 1;
	    uint8_t         do_while_loopback_flag;
	    do_while_loopback_flag = 0;
	    while (1) {
		// merge file ./.Aa//linked.opt.aa, line 4218
		fpunit_exec_exec__fpunit_exec_pipe_merge_daemon_merge_stmt_19549_c_preamble_macro_;
		fpunit_exec_exec__fpunit_exec_pipe_merge_daemon_merge_stmt_19549_c_postamble_macro_;
		// u := fpunit_exec_to_writeback_fast $buffering 1// bits
		// of buffering = 96. 
		fpunit_exec_exec__fpunit_exec_pipe_merge_daemon_assign_stmt_19552_c_macro_;
		// $volatile fast_valid := (u [] 95 ) $buffering 1
		fpunit_exec_exec__fpunit_exec_pipe_merge_daemon_assign_stmt_19557_c_macro_;
		// $guard (~fast_valid) v := fpunit_exec_to_writeback_slow 
		// $buffering 1// bits of buffering = 96. 
		fpunit_exec_exec__fpunit_exec_pipe_merge_daemon_assign_stmt_19561_c_macro_;
		// u_19596_delayed_1_0 := u $buffering 1 $cut_through //
		// bits of buffering = 96. 
		fpunit_exec_exec__fpunit_exec_pipe_merge_daemon_assign_stmt_19564_c_macro_;
		// fast_valid_19595_delayed_1_0 := fast_valid $buffering 1 
		// $cut_through // bits of buffering = 1. 
		fpunit_exec_exec__fpunit_exec_pipe_merge_daemon_assign_stmt_19567_c_macro_;
		// $volatile to_wb := ( $mux fast_valid_19595_delayed_1_0
		// u_19596_delayed_1_0 v ) $buffering 1
		fpunit_exec_exec__fpunit_exec_pipe_merge_daemon_assign_stmt_19573_c_macro_;
		// fpunit_exec_to_writeback := to_wb $buffering 1// bits
		// of buffering = 96. 
		fpunit_exec_exec__fpunit_exec_pipe_merge_daemon_assign_stmt_19576_c_macro_;
		// $sleep 100
		fpunit_exec_exec__fpunit_exec_pipe_merge_daemon_stmt_19577_c_macro_;
		do_while_entry_flag = 0;
		do_while_loopback_flag = 1;
		bit_vector_clear(&konst_19579);
		konst_19579.val.byte_array[0] = 1;
		if (!bit_vector_to_uint64(0, &konst_19579))
		    break;
	    }
	}
	fpunit_exec_exec__fpunit_exec_pipe_merge_daemon_branch_block_stmt_19547_c_export_apply_macro_;
    }
    fpunit_exec_exec__fpunit_exec_pipe_merge_daemon_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fpunit_exec_pipe_merge_daemon_series_block_stmt_19546_c_mutex_);
}
void
fpunit_exec_exec_fpunit_exec_pipe_merge_daemon()
{
    fpunit_exec_exec__fpunit_exec_pipe_merge_daemon_outer_arg_decl_macro__;
    _fpunit_exec_exec_fpunit_exec_pipe_merge_daemon_();
    fpunit_exec_exec__fpunit_exec_pipe_merge_daemon_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fstod_wrap_(float *__pX, double *__pRESULT)
{
    MUTEX_DECL
	(fpunit_exec_exec__fstod_wrap_series_block_stmt_19582_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fstod_wrap_series_block_stmt_19582_c_mutex_);
    fpunit_exec_exec__fstod_wrap_inner_inarg_prep_macro__;
    // $volatile $call SingleToDouble (X ) (r ) 
    fpunit_exec_exec__fstod_wrap_call_stmt_19587_c_macro_;
    // RESULT := r $buffering 1// bits of buffering = 64. 
    fpunit_exec_exec__fstod_wrap_assign_stmt_19590_c_macro_;
    fpunit_exec_exec__fstod_wrap_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fstod_wrap_series_block_stmt_19582_c_mutex_);
}
void
fpunit_exec_exec_fstod_wrap(float X, double *RESULT)
{
    double          __RESULT;
    fpunit_exec_exec__fstod_wrap_outer_arg_decl_macro__;
    _fpunit_exec_exec_fstod_wrap_(&__X, &__RESULT);
    fpunit_exec_exec__fstod_wrap_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fstoi_wrap_(float *__pX, bit_vector * __pY)
{
    MUTEX_DECL
	(fpunit_exec_exec__fstoi_wrap_series_block_stmt_19592_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fstoi_wrap_series_block_stmt_19592_c_mutex_);
    fpunit_exec_exec__fstoi_wrap_inner_inarg_prep_macro__;
    // $volatile $call SingleToDouble (X ) (Xd ) 
    fpunit_exec_exec__fstoi_wrap_call_stmt_19597_c_macro_;
    // $call fdtoi_op (Xd ) (Y ) 
    fpunit_exec_exec__fstoi_wrap_call_stmt_19600_c_macro_;
    fpunit_exec_exec__fstoi_wrap_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fstoi_wrap_series_block_stmt_19592_c_mutex_);
}
void
fpunit_exec_exec_fstoi_wrap(float X, int32_t * Y)
{
    fpunit_exec_exec__fstoi_wrap_outer_arg_decl_macro__;
    _fpunit_exec_exec_fstoi_wrap_(&__X, &__Y);
    fpunit_exec_exec__fstoi_wrap_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_fsub16_wrap_(bit_vector * __pf1, bit_vector * __pf2,
			       bit_vector * __presult)
{
    MUTEX_DECL
	(fpunit_exec_exec__fsub16_wrap_series_block_stmt_19602_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__fsub16_wrap_series_block_stmt_19602_c_mutex_);
    fpunit_exec_exec__fsub16_wrap_inner_inarg_prep_macro__;
    // $volatile $call faddsub16 (f1 f2 ONE_1 ) (result ) 
    fpunit_exec_exec__fsub16_wrap_call_stmt_19610_c_macro_;
    fpunit_exec_exec__fsub16_wrap_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__fsub16_wrap_series_block_stmt_19602_c_mutex_);
}
void
fpunit_exec_exec_fsub16_wrap(uint16_t f1, uint16_t f2, uint16_t * result)
{
    fpunit_exec_exec__fsub16_wrap_outer_arg_decl_macro__;
    _fpunit_exec_exec_fsub16_wrap_(&__f1, &__f2, &__result);
    fpunit_exec_exec__fsub16_wrap_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_generate_pre_compute_exceptions_(bit_vector *
						   __pthread_id,
						   bit_vector *
						   __pstream_id,
						   bit_vector * __pslot_id,
						   bit_vector * __pfpadds,
						   bit_vector * __pfpsubs,
						   bit_vector * __pfpmuls,
						   bit_vector * __pfpdivs,
						   bit_vector * __pfpcmps,
						   bit_vector * __pfpcmpes,
						   bit_vector * __pfpsqrts,
						   bit_vector * __pfstoi,
						   bit_vector * __pfitos,
						   bit_vector * __pfstod,
						   float *__pf1_s,
						   float *__pf2_s,
						   bit_vector * __pfpaddd,
						   bit_vector * __pfpsubd,
						   bit_vector * __pfpmuld,
						   bit_vector * __pfpdivd,
						   bit_vector * __pfpcmpd,
						   bit_vector * __pfpcmped,
						   bit_vector * __pfpsqrtd,
						   bit_vector * __pfdtoi,
						   bit_vector * __pfdtos,
						   double *__pf1_d,
						   double *__pf2_d,
						   bit_vector * __pnvc,
						   bit_vector * __pofc,
						   bit_vector * __pufc,
						   bit_vector * __pdzc,
						   bit_vector * __pnxc,
						   bit_vector *
						   __pf1_s_classification,
						   bit_vector *
						   __pf2_s_classification,
						   bit_vector *
						   __pf1_d_classification,
						   bit_vector *
						   __pf2_d_classification)
{
    MUTEX_DECL
	(fpunit_exec_exec__generate_pre_compute_exceptions_series_block_stmt_8260_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__generate_pre_compute_exceptions_series_block_stmt_8260_c_mutex_);
    fpunit_exec_exec__generate_pre_compute_exceptions_inner_inarg_prep_macro__;
    // $volatile $call classFp32 (f1_s ) (f1_s_pos_normal f1_s_neg_normal
    // f1_s_pos_denormal f1_s_neg_denormal f1_s_qnan f1_s_snan
    // f1_s_pos_inf f1_s_neg_inf f1_s_pos_zero f1_s_neg_zero ) 
    fpunit_exec_exec__generate_pre_compute_exceptions_call_stmt_8307_c_macro_;
    // f1_s_classification := ((((f1_s_pos_normal && f1_s_neg_normal) &&
    // f1_s_pos_denormal) && (f1_s_neg_denormal && f1_s_qnan)) &&
    // (((f1_s_snan && f1_s_pos_inf) && f1_s_neg_inf) && (f1_s_pos_zero && 
    // f1_s_neg_zero))) $buffering 1
    fpunit_exec_exec__generate_pre_compute_exceptions_assign_stmt_8328_c_macro_;
    // $volatile $call classFp32 (f2_s ) (f2_s_pos_normal f2_s_neg_normal
    // f2_s_pos_denormal f2_s_neg_denormal f2_s_qnan f2_s_snan
    // f2_s_pos_inf f2_s_neg_inf f2_s_pos_zero f2_s_neg_zero ) 
    fpunit_exec_exec__generate_pre_compute_exceptions_call_stmt_8340_c_macro_;
    // f2_s_classification := ((((f2_s_pos_normal && f2_s_neg_normal) &&
    // f2_s_pos_denormal) && (f2_s_neg_denormal && f2_s_qnan)) &&
    // (((f2_s_snan && f2_s_pos_inf) && f2_s_neg_inf) && (f2_s_pos_zero && 
    // f2_s_neg_zero))) $buffering 1
    fpunit_exec_exec__generate_pre_compute_exceptions_assign_stmt_8361_c_macro_;
    // $volatile $call classFp64 (f1_d ) (f1_d_pos_normal f1_d_neg_normal
    // f1_d_pos_denormal f1_d_neg_denormal f1_d_qnan f1_d_snan
    // f1_d_pos_inf f1_d_neg_inf f1_d_pos_zero f1_d_neg_zero ) 
    fpunit_exec_exec__generate_pre_compute_exceptions_call_stmt_8373_c_macro_;
    // f1_d_classification := ((((f1_d_pos_normal && f1_d_neg_normal) &&
    // f1_d_pos_denormal) && (f1_d_neg_denormal && f1_d_qnan)) &&
    // (((f1_d_snan && f1_d_pos_inf) && f1_d_neg_inf) && (f1_d_pos_zero && 
    // f1_d_neg_zero))) $buffering 1
    fpunit_exec_exec__generate_pre_compute_exceptions_assign_stmt_8394_c_macro_;
    // $volatile $call classFp64 (f2_d ) (f2_d_pos_normal f2_d_neg_normal
    // f2_d_pos_denormal f2_d_neg_denormal f2_d_qnan f2_d_snan
    // f2_d_pos_inf f2_d_neg_inf f2_d_pos_zero f2_d_neg_zero ) 
    fpunit_exec_exec__generate_pre_compute_exceptions_call_stmt_8406_c_macro_;
    // f2_d_classification := ((((f2_d_pos_normal && f2_d_neg_normal) &&
    // f2_d_pos_denormal) && (f2_d_neg_denormal && f2_d_qnan)) &&
    // (((f2_d_snan && f2_d_pos_inf) && f2_d_neg_inf) && (f2_d_pos_zero && 
    // f2_d_neg_zero))) $buffering 1
    fpunit_exec_exec__generate_pre_compute_exceptions_assign_stmt_8427_c_macro_;
    // single_precision := ((((fpadds | fpsubs) | fpmuls) | (fpdivs |
    // fpcmps)) | ((fpsqrts | fstoi) | (fitos | fstod))) $buffering 1
    fpunit_exec_exec__generate_pre_compute_exceptions_assign_stmt_8446_c_macro_;
    // double_precision := (((fpaddd | fpsubd) | (fpmuld | fpdivd)) |
    // ((fpcmpd | fpsqrtd) | (fdtoi | fdtos))) $buffering 1
    fpunit_exec_exec__generate_pre_compute_exceptions_assign_stmt_8463_c_macro_;
    // $report (fpunit_exec generate_precompute_exceptions_arguments___
    // thread_id thread_id stream_id stream_id slot_id slot_id fpadds
    // fpadds fpsubs fpsubs fpmuls fpmuls fpdivs fpdivs fpcmps fpcmps
    // fpsqrts fpsqrts fstoi fstoi fitos fitos fstod fstod fpaddd fpaddd
    // fpsubd fpsubd fpmuld fpmuld fpdivd fpdivd fpcmpd fpcmpd fpsqrtd
    // fpsqrtd fdtoi fdtoi fdtos fdtos f1_s f1_s f2_s f2_s f1_d f1_d f2_d
    // f2_d single_precision single_precision double_precision
    // double_precision f1_s_snan f1_s_snan f1_s_qnan f1_s_qnan
    // f1_s_pos_zero f1_s_pos_zero f1_s_neg_zero f1_s_neg_zero f2_s_snan
    // f2_s_snan f2_s_qnan f2_s_qnan f2_s_pos_zero f2_s_pos_zero
    // f2_s_neg_zero f2_s_neg_zero f1_d_snan f1_d_snan f1_d_qnan f1_d_qnan 
    // f2_d_snan f2_d_snan f2_d_qnan f2_d_qnan )
    fpunit_exec_exec__generate_pre_compute_exceptions_stmt_8502_c_macro_;
    // snan_nv := ((( $mux (((fpadds | fpsubs) | fpmuls) | (fpdivs |
    // fpcmps)) (f1_s_snan | f2_s_snan) _b0 ) | ( $mux ((fpsqrts | fstoi)
    // | fstod) f2_s_snan _b0 ) ) | (( $mux (((fpaddd | fpsubd) | fpmuld)
    // | (fpdivd | fpcmpd)) (f1_d_snan | f2_d_snan) _b0 ) | ( $mux
    // ((fpsqrtd | fdtoi) | fdtos) f2_d_snan _b0 ) )) $buffering 1
    fpunit_exec_exec__generate_pre_compute_exceptions_assign_stmt_8551_c_macro_;
    // add_sub_nv := ((( $mux fpadds ((f1_s_pos_inf & f2_s_neg_inf) |
    // (f2_s_pos_inf & f1_s_neg_inf)) _b0 ) | ( $mux fpsubs ((f1_s_pos_inf 
    // & f2_s_pos_inf) | (f2_s_neg_inf & f1_s_neg_inf)) _b0 ) ) | (( $mux
    // fpaddd ((f1_d_pos_inf & f2_d_neg_inf) | (f2_d_pos_inf &
    // f1_d_neg_inf)) _b0 ) | ( $mux fpsubd ((f1_d_pos_inf & f2_d_pos_inf) 
    // | (f2_d_neg_inf & f1_d_neg_inf)) _b0 ) )) $buffering 1
    fpunit_exec_exec__generate_pre_compute_exceptions_assign_stmt_8596_c_macro_;
    // mul_nv := (( $mux fpmuls (((f1_s_pos_zero | f1_s_neg_zero) |
    // (f2_s_pos_zero | f2_s_neg_zero)) & ((f1_s_pos_inf | f1_s_neg_inf) | 
    // (f2_s_pos_inf | f2_s_neg_inf))) _b0 ) | ( $mux fpmuld
    // (((f1_d_pos_zero | f1_d_neg_zero) | (f2_d_pos_zero |
    // f2_d_neg_zero)) & ((f1_d_pos_inf | f1_d_neg_inf) | (f2_d_pos_inf |
    // f2_d_neg_inf))) _b0 ) ) $buffering 1
    fpunit_exec_exec__generate_pre_compute_exceptions_assign_stmt_8635_c_macro_;
    // div_nv := (( $mux fpdivs (((f1_s_pos_zero | f1_s_neg_zero) &
    // (f2_s_pos_zero | f2_s_neg_zero)) | ((f1_s_pos_inf | f1_s_neg_inf) & 
    // (f2_s_pos_inf | f2_s_neg_inf))) _b0 ) | ( $mux fpdivd
    // (((f1_d_pos_zero | f1_d_neg_zero) & (f2_d_pos_zero |
    // f2_d_neg_zero)) | ((f1_d_pos_inf | f1_d_neg_inf) & (f2_d_pos_inf |
    // f2_d_neg_inf))) _b0 ) ) $buffering 1
    fpunit_exec_exec__generate_pre_compute_exceptions_assign_stmt_8674_c_macro_;
    // sqrt_nv := (( $mux fpsqrts ((f2_s_neg_normal | f2_s_neg_denormal) | 
    // f2_s_neg_inf) _b0 ) | ( $mux fpsqrtd ((f2_d_neg_normal |
    // f2_d_neg_denormal) | f2_d_neg_inf) _b0 ) ) $buffering 1
    fpunit_exec_exec__generate_pre_compute_exceptions_assign_stmt_8693_c_macro_;
    // conv_nv := ((( $mux fstoi (f1_s_qnan | f1_s_snan) _b0 ) | ( $mux
    // fdtoi (f1_d_qnan | f1_d_snan) _b0 ) ) | (( $mux fstod f1_s_snan _b0 
    // ) | ( $mux fdtos f1_d_snan _b0 ) )) $buffering 1
    fpunit_exec_exec__generate_pre_compute_exceptions_assign_stmt_8718_c_macro_;
    // fcmp_nv := ((( $mux fpcmps (f1_s_snan | f2_s_snan) _b0 ) | ( $mux
    // fpcmpd (f1_d_snan | f2_d_snan) _b0 ) ) | (( $mux fpcmpes
    // ((f1_s_snan | f2_s_snan) | (f1_s_qnan | f2_s_qnan)) _b0 ) | ( $mux
    // fpcmped ((f1_d_snan | f2_d_snan) | (f1_d_qnan | f2_d_qnan)) _b0 )
    // )) $buffering 1
    fpunit_exec_exec__generate_pre_compute_exceptions_assign_stmt_8755_c_macro_;
    // nvc := (((snan_nv | add_sub_nv) | (mul_nv | div_nv)) | ((sqrt_nv |
    // fcmp_nv) | conv_nv)) $buffering 1
    fpunit_exec_exec__generate_pre_compute_exceptions_assign_stmt_8770_c_macro_;
    // nxc := 0 $buffering 1
    fpunit_exec_exec__generate_pre_compute_exceptions_assign_stmt_8773_c_macro_;
    // dzc := 0 $buffering 1
    fpunit_exec_exec__generate_pre_compute_exceptions_assign_stmt_8776_c_macro_;
    // ofc := 0 $buffering 1
    fpunit_exec_exec__generate_pre_compute_exceptions_assign_stmt_8779_c_macro_;
    // ufc := 0 $buffering 1
    fpunit_exec_exec__generate_pre_compute_exceptions_assign_stmt_8782_c_macro_;
    // $report (fpunit_exec generate_precompute_exceptions_response__
    // snan_nv snan_nv add_sub_nv add_sub_nv mul_nv mul_nv div_nv div_nv
    // sqrt_nv sqrt_nv fcmp_nv fcmp_nv conv_nv conv_nv nvc nvc nxc nxc dzc 
    // dzc ofc ofc ufc ufc )
    fpunit_exec_exec__generate_pre_compute_exceptions_stmt_8795_c_macro_;
    fpunit_exec_exec__generate_pre_compute_exceptions_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__generate_pre_compute_exceptions_series_block_stmt_8260_c_mutex_);
}
void
_fpunit_exec_exec_getHalfInf_(bit_vector * __ps, bit_vector * __pret_val)
{
    MUTEX_DECL
	(fpunit_exec_exec__getHalfInf_series_block_stmt_9872_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__getHalfInf_series_block_stmt_9872_c_mutex_);
    fpunit_exec_exec__getHalfInf_inner_inarg_prep_macro__;
    // exp := ( ~ ($bitcast ($uint<5>) 0 ) ) $buffering 1
    fpunit_exec_exec__getHalfInf_assign_stmt_9879_c_macro_;
    // mant := ($bitcast ($uint<10>) 0 ) $buffering 1
    fpunit_exec_exec__getHalfInf_assign_stmt_9883_c_macro_;
    // ret_val := ((s && exp) && mant) $buffering 1
    fpunit_exec_exec__getHalfInf_assign_stmt_9890_c_macro_;
    fpunit_exec_exec__getHalfInf_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__getHalfInf_series_block_stmt_9872_c_mutex_);
}
void
_fpunit_exec_exec_getHalfNan_(bit_vector * __ps, bit_vector * __pret_val)
{
    MUTEX_DECL
	(fpunit_exec_exec__getHalfNan_series_block_stmt_9901_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__getHalfNan_series_block_stmt_9901_c_mutex_);
    fpunit_exec_exec__getHalfNan_inner_inarg_prep_macro__;
    // exp := ( ~ ($bitcast ($uint<5>) 0 ) ) $buffering 1
    fpunit_exec_exec__getHalfNan_assign_stmt_9908_c_macro_;
    // mant := (ONE_1 && ($bitcast ($uint<9>) 0 )) $buffering 1
    fpunit_exec_exec__getHalfNan_assign_stmt_9914_c_macro_;
    // ret_val := ((s && exp) && mant) $buffering 1
    fpunit_exec_exec__getHalfNan_assign_stmt_9921_c_macro_;
    fpunit_exec_exec__getHalfNan_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__getHalfNan_series_block_stmt_9901_c_mutex_);
}
void
_fpunit_exec_exec_getHalfZero_(bit_vector * __ps, bit_vector * __pret_val)
{
    MUTEX_DECL
	(fpunit_exec_exec__getHalfZero_series_block_stmt_9892_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__getHalfZero_series_block_stmt_9892_c_mutex_);
    fpunit_exec_exec__getHalfZero_inner_inarg_prep_macro__;
    // ret_val := (s && ZERO_15) $buffering 1
    fpunit_exec_exec__getHalfZero_assign_stmt_9899_c_macro_;
    fpunit_exec_exec__getHalfZero_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__getHalfZero_series_block_stmt_9892_c_mutex_);
}
void
_fpunit_exec_exec_global_storage_initializer__()
{
    MUTEX_DECL
	(fpunit_exec_exec__global_storage_initializer__series_block_stmt_19612_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__global_storage_initializer__series_block_stmt_19612_c_mutex_);
    fpunit_exec_exec__global_storage_initializer__inner_inarg_prep_macro__;
    /*
     * null 
     */ ;
    fpunit_exec_exec__global_storage_initializer__inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__global_storage_initializer__series_block_stmt_19612_c_mutex_);
}
void
fpunit_exec_exec_global_storage_initializer_()
{
    fpunit_exec_exec__global_storage_initializer__outer_arg_decl_macro__;
    _fpunit_exec_exec_global_storage_initializer__();
    fpunit_exec_exec__global_storage_initializer__outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_i16_sll_(bit_vector * __pX, bit_vector * __pS,
			   bit_vector * __pY)
{
    MUTEX_DECL(fpunit_exec_exec__i16_sll_series_block_stmt_9638_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__i16_sll_series_block_stmt_9638_c_mutex_);
    fpunit_exec_exec__i16_sll_inner_inarg_prep_macro__;
    // X0 := ( $mux (S [] 0 ) (( $slice X 14 0 ) && ZERO_1) X ) $buffering 
    // 1
    fpunit_exec_exec__i16_sll_assign_stmt_9652_c_macro_;
    // X1 := ( $mux (S [] 1 ) (( $slice X0 13 0 ) && ZERO_2) X0 )
    // $buffering 1
    fpunit_exec_exec__i16_sll_assign_stmt_9663_c_macro_;
    // X2 := ( $mux (S [] 2 ) (( $slice X1 11 0 ) && ZERO_4) X1 )
    // $buffering 1
    fpunit_exec_exec__i16_sll_assign_stmt_9674_c_macro_;
    // X3 := ( $mux (S [] 3 ) (( $slice X2 7 0 ) && ZERO_8) X2 )
    // $buffering 1
    fpunit_exec_exec__i16_sll_assign_stmt_9685_c_macro_;
    // Y := ( $mux (S [] 4 ) 0 X3 ) $buffering 1
    fpunit_exec_exec__i16_sll_assign_stmt_9693_c_macro_;
    fpunit_exec_exec__i16_sll_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__i16_sll_series_block_stmt_9638_c_mutex_);
}
void
_fpunit_exec_exec_i24_sll_(bit_vector * __pX, bit_vector * __pS,
			   bit_vector * __pY)
{
    MUTEX_DECL(fpunit_exec_exec__i24_sll_series_block_stmt_2232_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__i24_sll_series_block_stmt_2232_c_mutex_);
    fpunit_exec_exec__i24_sll_inner_inarg_prep_macro__;
    // X0 := ( $mux (S [] 0 ) (( $slice X 22 0 ) && ZERO_1) X ) $buffering 
    // 1
    fpunit_exec_exec__i24_sll_assign_stmt_2246_c_macro_;
    // X1 := ( $mux (S [] 1 ) (( $slice X0 21 0 ) && ZERO_2) X0 )
    // $buffering 1
    fpunit_exec_exec__i24_sll_assign_stmt_2257_c_macro_;
    // X2 := ( $mux (S [] 2 ) (( $slice X1 19 0 ) && ZERO_4) X1 )
    // $buffering 1
    fpunit_exec_exec__i24_sll_assign_stmt_2268_c_macro_;
    // X3 := ( $mux (S [] 3 ) (( $slice X2 15 0 ) && ZERO_8) X2 )
    // $buffering 1
    fpunit_exec_exec__i24_sll_assign_stmt_2279_c_macro_;
    // Y := ( $mux (S [] 4 ) (( $slice X3 7 0 ) && ZERO_16) X3 )
    // $buffering 1
    fpunit_exec_exec__i24_sll_assign_stmt_2290_c_macro_;
    fpunit_exec_exec__i24_sll_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__i24_sll_series_block_stmt_2232_c_mutex_);
}
void
_fpunit_exec_exec_i32_sll_(bit_vector * __pX, bit_vector * __pS,
			   bit_vector * __pY)
{
    MUTEX_DECL(fpunit_exec_exec__i32_sll_series_block_stmt_13308_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__i32_sll_series_block_stmt_13308_c_mutex_);
    fpunit_exec_exec__i32_sll_inner_inarg_prep_macro__;
    // X0 := ( $mux (S [] 0 ) (( $slice X 30 0 ) && ZERO_1) X ) $buffering 
    // 1
    fpunit_exec_exec__i32_sll_assign_stmt_13322_c_macro_;
    // X1 := ( $mux (S [] 1 ) (( $slice X0 29 0 ) && ZERO_2) X0 )
    // $buffering 1
    fpunit_exec_exec__i32_sll_assign_stmt_13333_c_macro_;
    // X2 := ( $mux (S [] 2 ) (( $slice X1 27 0 ) && ZERO_4) X1 )
    // $buffering 1
    fpunit_exec_exec__i32_sll_assign_stmt_13344_c_macro_;
    // X3 := ( $mux (S [] 3 ) (( $slice X2 23 0 ) && ZERO_8) X2 )
    // $buffering 1
    fpunit_exec_exec__i32_sll_assign_stmt_13355_c_macro_;
    // X4 := ( $mux (S [] 4 ) (( $slice X3 15 0 ) && ZERO_16) X3 )
    // $buffering 1
    fpunit_exec_exec__i32_sll_assign_stmt_13366_c_macro_;
    // Y := ( $mux (S [] 5 ) 0 X4 ) $buffering 1
    fpunit_exec_exec__i32_sll_assign_stmt_13374_c_macro_;
    fpunit_exec_exec__i32_sll_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__i32_sll_series_block_stmt_13308_c_mutex_);
}
void
_fpunit_exec_exec_i32_srl_(bit_vector * __pX, bit_vector * __pS,
			   bit_vector * __pY)
{
    MUTEX_DECL(fpunit_exec_exec__i32_srl_series_block_stmt_7272_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__i32_srl_series_block_stmt_7272_c_mutex_);
    fpunit_exec_exec__i32_srl_inner_inarg_prep_macro__;
    // X0 := ( $mux (S [] 0 ) (ZERO_1 && ( $slice X 31 1 ) ) X )
    // $buffering 1
    fpunit_exec_exec__i32_srl_assign_stmt_7286_c_macro_;
    // X1 := ( $mux (S [] 1 ) (ZERO_2 && ( $slice X0 31 2 ) ) X0 )
    // $buffering 1
    fpunit_exec_exec__i32_srl_assign_stmt_7297_c_macro_;
    // X2 := ( $mux (S [] 2 ) (ZERO_4 && ( $slice X1 31 4 ) ) X1 )
    // $buffering 1
    fpunit_exec_exec__i32_srl_assign_stmt_7308_c_macro_;
    // X3 := ( $mux (S [] 3 ) (ZERO_8 && ( $slice X2 31 8 ) ) X2 )
    // $buffering 1
    fpunit_exec_exec__i32_srl_assign_stmt_7319_c_macro_;
    // Y := ( $mux (S [] 4 ) (ZERO_16 && ( $slice X3 31 16 ) ) X3 )
    // $buffering 1
    fpunit_exec_exec__i32_srl_assign_stmt_7330_c_macro_;
    fpunit_exec_exec__i32_srl_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__i32_srl_series_block_stmt_7272_c_mutex_);
}
void
_fpunit_exec_exec_i35_sll_(bit_vector * __pX, bit_vector * __pS,
			   bit_vector * __pY)
{
    MUTEX_DECL(fpunit_exec_exec__i35_sll_series_block_stmt_11390_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__i35_sll_series_block_stmt_11390_c_mutex_);
    fpunit_exec_exec__i35_sll_inner_inarg_prep_macro__;
    // X0 := ( $mux (S [] 0 ) (( $slice X 33 0 ) && ZERO_1) X ) $buffering 
    // 1
    fpunit_exec_exec__i35_sll_assign_stmt_11404_c_macro_;
    // X1 := ( $mux (S [] 1 ) (( $slice X0 32 0 ) && ZERO_2) X0 )
    // $buffering 1
    fpunit_exec_exec__i35_sll_assign_stmt_11415_c_macro_;
    // X2 := ( $mux (S [] 2 ) (( $slice X1 30 0 ) && ZERO_4) X1 )
    // $buffering 1
    fpunit_exec_exec__i35_sll_assign_stmt_11426_c_macro_;
    // X3 := ( $mux (S [] 3 ) (( $slice X2 26 0 ) && ZERO_8) X2 )
    // $buffering 1
    fpunit_exec_exec__i35_sll_assign_stmt_11437_c_macro_;
    // X4 := ( $mux (S [] 4 ) (( $slice X3 18 0 ) && ZERO_16) X3 )
    // $buffering 1
    fpunit_exec_exec__i35_sll_assign_stmt_11448_c_macro_;
    // Y := ( $mux (S [] 5 ) (( $slice X4 2 0 ) && ZERO_32) X4 )
    // $buffering 1
    fpunit_exec_exec__i35_sll_assign_stmt_11459_c_macro_;
    fpunit_exec_exec__i35_sll_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__i35_sll_series_block_stmt_11390_c_mutex_);
}
void
_fpunit_exec_exec_i53_sll_(bit_vector * __pX, bit_vector * __pS,
			   bit_vector * __pY)
{
    MUTEX_DECL(fpunit_exec_exec__i53_sll_series_block_stmt_1849_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__i53_sll_series_block_stmt_1849_c_mutex_);
    fpunit_exec_exec__i53_sll_inner_inarg_prep_macro__;
    // X0 := ( $mux (S [] 0 ) (( $slice X 51 0 ) && ZERO_1) X ) $buffering 
    // 1
    fpunit_exec_exec__i53_sll_assign_stmt_1863_c_macro_;
    // X1 := ( $mux (S [] 1 ) (( $slice X0 50 0 ) && ZERO_2) X0 )
    // $buffering 1
    fpunit_exec_exec__i53_sll_assign_stmt_1874_c_macro_;
    // X2 := ( $mux (S [] 2 ) (( $slice X1 48 0 ) && ZERO_4) X1 )
    // $buffering 1
    fpunit_exec_exec__i53_sll_assign_stmt_1886_c_macro_;
    // X3 := ( $mux (S [] 3 ) (( $slice X2 44 0 ) && ZERO_8) X2 )
    // $buffering 1
    fpunit_exec_exec__i53_sll_assign_stmt_1898_c_macro_;
    // X4 := ( $mux (S [] 4 ) (( $slice X3 36 0 ) && ZERO_16) X3 )
    // $buffering 1
    fpunit_exec_exec__i53_sll_assign_stmt_1910_c_macro_;
    // Y := ( $mux (S [] 5 ) (( $slice X4 20 0 ) && ZERO_32) X4 )
    // $buffering 1
    fpunit_exec_exec__i53_sll_assign_stmt_1922_c_macro_;
    fpunit_exec_exec__i53_sll_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__i53_sll_series_block_stmt_1849_c_mutex_);
}
void
_fpunit_exec_exec_i64_sll_(bit_vector * __pX, bit_vector * __pS,
			   bit_vector * __pY)
{
    MUTEX_DECL(fpunit_exec_exec__i64_sll_series_block_stmt_10382_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__i64_sll_series_block_stmt_10382_c_mutex_);
    fpunit_exec_exec__i64_sll_inner_inarg_prep_macro__;
    // X0 := ( $mux (S [] 0 ) (( $slice X 62 0 ) && ZERO_1) X ) $buffering 
    // 1
    fpunit_exec_exec__i64_sll_assign_stmt_10396_c_macro_;
    // X1 := ( $mux (S [] 1 ) (( $slice X0 61 0 ) && ZERO_2) X0 )
    // $buffering 1
    fpunit_exec_exec__i64_sll_assign_stmt_10407_c_macro_;
    // X2 := ( $mux (S [] 2 ) (( $slice X1 59 0 ) && ZERO_4) X1 )
    // $buffering 1
    fpunit_exec_exec__i64_sll_assign_stmt_10418_c_macro_;
    // X3 := ( $mux (S [] 3 ) (( $slice X2 55 0 ) && ZERO_8) X2 )
    // $buffering 1
    fpunit_exec_exec__i64_sll_assign_stmt_10429_c_macro_;
    // X4 := ( $mux (S [] 4 ) (( $slice X3 47 0 ) && ZERO_16) X3 )
    // $buffering 1
    fpunit_exec_exec__i64_sll_assign_stmt_10440_c_macro_;
    // Y := ( $mux (S [] 5 ) (( $slice X4 31 0 ) && ZERO_32) X4 )
    // $buffering 1
    fpunit_exec_exec__i64_sll_assign_stmt_10451_c_macro_;
    fpunit_exec_exec__i64_sll_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__i64_sll_series_block_stmt_10382_c_mutex_);
}
void
_fpunit_exec_exec_i64_srl_(bit_vector * __pX, bit_vector * __pS,
			   bit_vector * __pY)
{
    MUTEX_DECL(fpunit_exec_exec__i64_srl_series_block_stmt_7407_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__i64_srl_series_block_stmt_7407_c_mutex_);
    fpunit_exec_exec__i64_srl_inner_inarg_prep_macro__;
    // X0 := ( $mux (S [] 0 ) (ZERO_1 && ( $slice X 63 1 ) ) X )
    // $buffering 1
    fpunit_exec_exec__i64_srl_assign_stmt_7421_c_macro_;
    // X1 := ( $mux (S [] 1 ) (ZERO_2 && ( $slice X0 63 2 ) ) X0 )
    // $buffering 1
    fpunit_exec_exec__i64_srl_assign_stmt_7432_c_macro_;
    // X2 := ( $mux (S [] 2 ) (ZERO_4 && ( $slice X1 63 4 ) ) X1 )
    // $buffering 1
    fpunit_exec_exec__i64_srl_assign_stmt_7443_c_macro_;
    // X3 := ( $mux (S [] 3 ) (ZERO_8 && ( $slice X2 63 8 ) ) X2 )
    // $buffering 1
    fpunit_exec_exec__i64_srl_assign_stmt_7454_c_macro_;
    // X4 := ( $mux (S [] 4 ) (ZERO_16 && ( $slice X3 63 16 ) ) X3 )
    // $buffering 1
    fpunit_exec_exec__i64_srl_assign_stmt_7465_c_macro_;
    // Y := ( $mux (S [] 5 ) (ZERO_32 && ( $slice X4 63 32 ) ) X4 )
    // $buffering 1
    fpunit_exec_exec__i64_srl_assign_stmt_7476_c_macro_;
    fpunit_exec_exec__i64_srl_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__i64_srl_series_block_stmt_7407_c_mutex_);
}
void
_fpunit_exec_exec_increment_16_(bit_vector * __pA, bit_vector * __pB)
{
    MUTEX_DECL
	(fpunit_exec_exec__increment_16_series_block_stmt_9474_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__increment_16_series_block_stmt_9474_c_mutex_);
    fpunit_exec_exec__increment_16_inner_inarg_prep_macro__;
    // AH := ( $slice A 15 8 ) $buffering 1
    fpunit_exec_exec__increment_16_assign_stmt_9480_c_macro_;
    // AL := ( $slice A 7 0 ) $buffering 1
    fpunit_exec_exec__increment_16_assign_stmt_9484_c_macro_;
    // BL := (AL + 1 ) $buffering 1
    fpunit_exec_exec__increment_16_assign_stmt_9489_c_macro_;
    // tBH := (AH + 1 ) $buffering 1
    fpunit_exec_exec__increment_16_assign_stmt_9494_c_macro_;
    // B := (( $mux (( ~ AL ) == 0 ) tBH AH ) && BL) $buffering 1
    fpunit_exec_exec__increment_16_assign_stmt_9505_c_macro_;
    fpunit_exec_exec__increment_16_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__increment_16_series_block_stmt_9474_c_mutex_);
}
void
fpunit_exec_exec_increment_16(uint16_t A, uint16_t * B)
{
    fpunit_exec_exec__increment_16_outer_arg_decl_macro__;
    _fpunit_exec_exec_increment_16_(&__A, &__B);
    fpunit_exec_exec__increment_16_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_increment_32_(bit_vector * __pA, bit_vector * __pB)
{
    MUTEX_DECL
	(fpunit_exec_exec__increment_32_series_block_stmt_13275_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__increment_32_series_block_stmt_13275_c_mutex_);
    fpunit_exec_exec__increment_32_inner_inarg_prep_macro__;
    // AH := ( $slice A 31 16 ) $buffering 1
    fpunit_exec_exec__increment_32_assign_stmt_13281_c_macro_;
    // AL := ( $slice A 15 0 ) $buffering 1
    fpunit_exec_exec__increment_32_assign_stmt_13285_c_macro_;
    // BL := (AL + 1 ) $buffering 1
    fpunit_exec_exec__increment_32_assign_stmt_13290_c_macro_;
    // tBH := (AH + 1 ) $buffering 1
    fpunit_exec_exec__increment_32_assign_stmt_13295_c_macro_;
    // B := (( $mux (( ~ AL ) == 0 ) tBH AH ) && BL) $buffering 1
    fpunit_exec_exec__increment_32_assign_stmt_13306_c_macro_;
    fpunit_exec_exec__increment_32_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__increment_32_series_block_stmt_13275_c_mutex_);
}
void
fpunit_exec_exec_increment_32(uint32_t A, uint32_t * B)
{
    fpunit_exec_exec__increment_32_outer_arg_decl_macro__;
    _fpunit_exec_exec_increment_32_(&__A, &__B);
    fpunit_exec_exec__increment_32_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_increment_64_(bit_vector * __pA, bit_vector * __pB)
{
    MUTEX_DECL
	(fpunit_exec_exec__increment_64_series_block_stmt_19615_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__increment_64_series_block_stmt_19615_c_mutex_);
    fpunit_exec_exec__increment_64_inner_inarg_prep_macro__;
    // AH := ( $slice A 63 32 ) $buffering 1
    fpunit_exec_exec__increment_64_assign_stmt_19621_c_macro_;
    // AL := ( $slice A 31 0 ) $buffering 1
    fpunit_exec_exec__increment_64_assign_stmt_19625_c_macro_;
    // $volatile $call increment_32 (AL ) (BL ) 
    fpunit_exec_exec__increment_64_call_stmt_19628_c_macro_;
    // $volatile $call increment_32 (AH ) (tBH ) 
    fpunit_exec_exec__increment_64_call_stmt_19631_c_macro_;
    // B := (( $mux (( ~ AL ) == 0 ) tBH AH ) && BL) $buffering 1
    fpunit_exec_exec__increment_64_assign_stmt_19642_c_macro_;
    fpunit_exec_exec__increment_64_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__increment_64_series_block_stmt_19615_c_mutex_);
}
void
fpunit_exec_exec_increment_64(uint64_t A, uint64_t * B)
{
    fpunit_exec_exec__increment_64_outer_arg_decl_macro__;
    _fpunit_exec_exec_increment_64_(&__A, &__B);
    fpunit_exec_exec__increment_64_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_isSnand_(double *__pf, bit_vector * __pis_snan)
{
    MUTEX_DECL(fpunit_exec_exec__isSnand_series_block_stmt_19644_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__isSnand_series_block_stmt_19644_c_mutex_);
    fpunit_exec_exec__isSnand_inner_inarg_prep_macro__;
    // $volatile $call classFp64 (f ) (pos_normal neg_normal pos_denormal
    // neg_denormal qnan is_snan pos_inf neg_inf pos_zero neg_zero ) 
    fpunit_exec_exec__isSnand_call_stmt_19658_c_macro_;
    fpunit_exec_exec__isSnand_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__isSnand_series_block_stmt_19644_c_mutex_);
}
void
_fpunit_exec_exec_isSnans_(float *__pf, bit_vector * __pis_snan)
{
    MUTEX_DECL(fpunit_exec_exec__isSnans_series_block_stmt_19660_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__isSnans_series_block_stmt_19660_c_mutex_);
    fpunit_exec_exec__isSnans_inner_inarg_prep_macro__;
    // $volatile $call classFp32 (f ) (pos_normal neg_normal pos_denormal
    // neg_denormal qnan is_snan pos_inf neg_inf pos_zero neg_zero ) 
    fpunit_exec_exec__isSnans_call_stmt_19674_c_macro_;
    fpunit_exec_exec__isSnans_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__isSnans_series_block_stmt_19660_c_mutex_);
}
void
_fpunit_exec_exec_make_new_estimate_32_(bit_vector * __plast_root_estimate,
					bit_vector * __plast_residue,
					bit_vector *
					__plast_shifted_index_word,
					bit_vector *
					__pcurrent_root_estimate,
					bit_vector * __pcurrent_residue,
					bit_vector *
					__pcurrent_residue_sign)
{
    MUTEX_DECL
	(fpunit_exec_exec__make_new_estimate_32_series_block_stmt_14877_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__make_new_estimate_32_series_block_stmt_14877_c_mutex_);
    fpunit_exec_exec__make_new_estimate_32_inner_inarg_prep_macro__;
    // $report (fpdiv32bitwise make_new_estimate_32_in_args__
    // last_root_estimate last_root_estimate last_residue last_residue
    // last_shifted_index_word last_shifted_index_word )
    fpunit_exec_exec__make_new_estimate_32_stmt_14887_c_macro_;
    // current_shifted_index_word := (ZERO_1 && ( $slice
    // last_shifted_index_word 31 1 ) ) $buffering 1
    fpunit_exec_exec__make_new_estimate_32_assign_stmt_14893_c_macro_;
    // current_root_estimate := (last_root_estimate |
    // current_shifted_index_word) $buffering 1
    fpunit_exec_exec__make_new_estimate_32_assign_stmt_14898_c_macro_;
    // current_shifted_index_word_right_shifted := (ZERO_1 && ( $slice
    // current_shifted_index_word 31 1 ) ) $buffering 1
    fpunit_exec_exec__make_new_estimate_32_assign_stmt_14904_c_macro_;
    // current_increment := ((ZERO_1 && (last_root_estimate |
    // current_shifted_index_word_right_shifted)) && ZERO_1) $buffering 1
    fpunit_exec_exec__make_new_estimate_32_assign_stmt_14913_c_macro_;
    // current_residue := (last_residue - current_increment) $buffering 1
    fpunit_exec_exec__make_new_estimate_32_assign_stmt_14918_c_macro_;
    // current_residue_sign := (last_residue < current_increment)
    // $buffering 1
    fpunit_exec_exec__make_new_estimate_32_assign_stmt_14923_c_macro_;
    // $report (fpdiv32bitwise make_new_estimate_32_outargs
    // current_shifted_index_word current_shifted_index_word
    // current_root_estimate current_root_estimate
    // current_shifted_index_word_right_shifted
    // current_shifted_index_word_right_shifted current_increment
    // current_increment current_residue current_residue
    // current_residue_sign current_residue_sign )
    fpunit_exec_exec__make_new_estimate_32_stmt_14930_c_macro_;
    fpunit_exec_exec__make_new_estimate_32_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__make_new_estimate_32_series_block_stmt_14877_c_mutex_);
}
void
_fpunit_exec_exec_make_new_estimate_56_(bit_vector * __plast_root_estimate,
					bit_vector * __plast_residue,
					bit_vector *
					__plast_shifted_index_word,
					bit_vector *
					__pcurrent_root_estimate,
					bit_vector * __pcurrent_residue,
					bit_vector *
					__pcurrent_residue_sign)
{
    MUTEX_DECL
	(fpunit_exec_exec__make_new_estimate_56_series_block_stmt_15954_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__make_new_estimate_56_series_block_stmt_15954_c_mutex_);
    fpunit_exec_exec__make_new_estimate_56_inner_inarg_prep_macro__;
    // $report (fpdiv64bitwise make_new_estimate_56_in_args__
    // last_root_estimate last_root_estimate last_residue last_residue
    // last_shifted_index_word last_shifted_index_word )
    fpunit_exec_exec__make_new_estimate_56_stmt_15964_c_macro_;
    // current_shifted_index_word := (ZERO_1 && ( $slice
    // last_shifted_index_word 55 1 ) ) $buffering 1
    fpunit_exec_exec__make_new_estimate_56_assign_stmt_15970_c_macro_;
    // current_root_estimate := (last_root_estimate |
    // current_shifted_index_word) $buffering 1
    fpunit_exec_exec__make_new_estimate_56_assign_stmt_15975_c_macro_;
    // current_shifted_index_word_right_shifted := (ZERO_1 && ( $slice
    // current_shifted_index_word 55 1 ) ) $buffering 1
    fpunit_exec_exec__make_new_estimate_56_assign_stmt_15981_c_macro_;
    // current_increment := ((ZERO_1 && (last_root_estimate |
    // current_shifted_index_word_right_shifted)) && ZERO_1) $buffering 1
    fpunit_exec_exec__make_new_estimate_56_assign_stmt_15990_c_macro_;
    // current_residue := (last_residue - current_increment) $buffering 1
    fpunit_exec_exec__make_new_estimate_56_assign_stmt_15995_c_macro_;
    // current_residue_sign := (last_residue < current_increment)
    // $buffering 1
    fpunit_exec_exec__make_new_estimate_56_assign_stmt_16000_c_macro_;
    // $report (fpdiv64bitwise make_new_estimate_56_outargs
    // current_shifted_index_word current_shifted_index_word
    // current_root_estimate current_root_estimate
    // current_shifted_index_word_right_shifted
    // current_shifted_index_word_right_shifted current_increment
    // current_increment current_residue current_residue
    // current_residue_sign current_residue_sign )
    fpunit_exec_exec__make_new_estimate_56_stmt_16007_c_macro_;
    fpunit_exec_exec__make_new_estimate_56_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__make_new_estimate_56_series_block_stmt_15954_c_mutex_);
}
void
_fpunit_exec_exec_mem_load___(bit_vector * __paddress,
			      bit_vector * __pdata)
{
    MUTEX_DECL
	(fpunit_exec_exec__mem_load___series_block_stmt_19676_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__mem_load___series_block_stmt_19676_c_mutex_);
    fpunit_exec_exec__mem_load___inner_inarg_prep_macro__;
    // data := default_mem_pool[((address * 1 ) + 0 )] $buffering 1// bits 
    // of buffering = 8. 
    fpunit_exec_exec__mem_load___assign_stmt_19686_c_macro_;
    fpunit_exec_exec__mem_load___inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__mem_load___series_block_stmt_19676_c_mutex_);
}
void
fpunit_exec_exec_mem_load__(uint32_t address, uint8_t * data)
{
    fpunit_exec_exec__mem_load___outer_arg_decl_macro__;
    _fpunit_exec_exec_mem_load___(&__address, &__data);
    fpunit_exec_exec__mem_load___outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_mem_store___(bit_vector * __paddress,
			       bit_vector * __pdata)
{
    MUTEX_DECL
	(fpunit_exec_exec__mem_store___series_block_stmt_19688_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__mem_store___series_block_stmt_19688_c_mutex_);
    fpunit_exec_exec__mem_store___inner_inarg_prep_macro__;
    // default_mem_pool[((address * 1 ) + 0 )] := data $buffering 1// bits 
    // of buffering = 8. 
    fpunit_exec_exec__mem_store___assign_stmt_19698_c_macro_;
    fpunit_exec_exec__mem_store___inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__mem_store___series_block_stmt_19688_c_mutex_);
}
void
fpunit_exec_exec_mem_store__(uint32_t address, uint8_t data)
{
    fpunit_exec_exec__mem_store___outer_arg_decl_macro__;
    _fpunit_exec_exec_mem_store___(&__address, &__data);
    fpunit_exec_exec__mem_store___outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_mul24_(bit_vector * __pL, bit_vector * __pR,
			 bit_vector * __pRESULT)
{
    MUTEX_DECL(fpunit_exec_exec__mul24_series_block_stmt_12059_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__mul24_series_block_stmt_12059_c_mutex_);
    fpunit_exec_exec__mul24_inner_inarg_prep_macro__;
    // $volatile A1 := ( $slice L 23 12 ) $buffering 1
    fpunit_exec_exec__mul24_assign_stmt_12066_c_macro_;
    // $volatile A0 := ( $slice L 11 0 ) $buffering 1
    fpunit_exec_exec__mul24_assign_stmt_12070_c_macro_;
    // $volatile B1 := ( $slice R 23 12 ) $buffering 1
    fpunit_exec_exec__mul24_assign_stmt_12074_c_macro_;
    // $volatile B0 := ( $slice R 11 0 ) $buffering 1
    fpunit_exec_exec__mul24_assign_stmt_12078_c_macro_;
    // $volatile a0b0 := (($bitcast ($uint<24>) A0 ) * ($bitcast
    // ($uint<24>) B0 )) $buffering 1
    fpunit_exec_exec__mul24_assign_stmt_12085_c_macro_;
    // $volatile a0b1 := (($bitcast ($uint<24>) A0 ) * ($bitcast
    // ($uint<24>) B1 )) $buffering 1
    fpunit_exec_exec__mul24_assign_stmt_12092_c_macro_;
    // $volatile a1b0 := (($bitcast ($uint<24>) A1 ) * ($bitcast
    // ($uint<24>) B0 )) $buffering 1
    fpunit_exec_exec__mul24_assign_stmt_12099_c_macro_;
    // $volatile a1b1 := (($bitcast ($uint<24>) A1 ) * ($bitcast
    // ($uint<24>) B1 )) $buffering 1
    fpunit_exec_exec__mul24_assign_stmt_12106_c_macro_;
    // $volatile a0b0_l := ( $slice a0b0 11 0 ) $buffering 1
    fpunit_exec_exec__mul24_assign_stmt_12110_c_macro_;
    // $volatile a0b0_h := ( $slice a0b0 23 12 ) $buffering 1
    fpunit_exec_exec__mul24_assign_stmt_12114_c_macro_;
    // $volatile a0b1_l := ( $slice a0b1 11 0 ) $buffering 1
    fpunit_exec_exec__mul24_assign_stmt_12118_c_macro_;
    // $volatile a0b1_h := ( $slice a0b1 23 12 ) $buffering 1
    fpunit_exec_exec__mul24_assign_stmt_12122_c_macro_;
    // $volatile a1b0_l := ( $slice a1b0 11 0 ) $buffering 1
    fpunit_exec_exec__mul24_assign_stmt_12126_c_macro_;
    // $volatile a1b0_h := ( $slice a1b0 23 12 ) $buffering 1
    fpunit_exec_exec__mul24_assign_stmt_12130_c_macro_;
    // $volatile a1b1_l := ( $slice a1b1 11 0 ) $buffering 1
    fpunit_exec_exec__mul24_assign_stmt_12134_c_macro_;
    // $volatile a1b1_h := ( $slice a1b1 23 12 ) $buffering 1
    fpunit_exec_exec__mul24_assign_stmt_12138_c_macro_;
    // $volatile P0 := a0b0_l $buffering 1
    fpunit_exec_exec__mul24_assign_stmt_12141_c_macro_;
    // $volatile eP1 := (($bitcast ($uint<14>) a0b0_h ) + (($bitcast
    // ($uint<14>) a0b1_l ) + ($bitcast ($uint<14>) a1b0_l ))) $buffering
    // 1
    fpunit_exec_exec__mul24_assign_stmt_12151_c_macro_;
    // $volatile P1 := ( $slice eP1 11 0 ) $buffering 1
    fpunit_exec_exec__mul24_assign_stmt_12155_c_macro_;
    // $volatile cP1 := ($bitcast ($uint<14>) ( $slice eP1 13 12 ) )
    // $buffering 1
    fpunit_exec_exec__mul24_assign_stmt_12160_c_macro_;
    // $volatile eP2 := ((($bitcast ($uint<14>) a1b0_h ) + ($bitcast
    // ($uint<14>) a0b1_h )) + (($bitcast ($uint<14>) a1b1_l ) + cP1))
    // $buffering 1
    fpunit_exec_exec__mul24_assign_stmt_12172_c_macro_;
    // $volatile P2 := ( $slice eP2 11 0 ) $buffering 1
    fpunit_exec_exec__mul24_assign_stmt_12176_c_macro_;
    // $volatile cP2 := ($bitcast ($uint<12>) ( $slice eP2 13 12 ) )
    // $buffering 1
    fpunit_exec_exec__mul24_assign_stmt_12181_c_macro_;
    // $volatile P3 := (($bitcast ($uint<12>) a1b1_h ) + cP2) $buffering 1
    fpunit_exec_exec__mul24_assign_stmt_12187_c_macro_;
    // RESULT := ((P3 && P2) && (P1 && P0)) $buffering 1// bits of
    // buffering = 48. 
    fpunit_exec_exec__mul24_assign_stmt_12196_c_macro_;
    fpunit_exec_exec__mul24_inner_outarg_prep_macro__;
    MUTEX_UNLOCK(fpunit_exec_exec__mul24_series_block_stmt_12059_c_mutex_);
}
void
_fpunit_exec_exec_mul53_(bit_vector * __pL, bit_vector * __pR,
			 bit_vector * __pRESULT)
{
    MUTEX_DECL(fpunit_exec_exec__mul53_series_block_stmt_12667_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__mul53_series_block_stmt_12667_c_mutex_);
    fpunit_exec_exec__mul53_inner_inarg_prep_macro__;
    // $volatile A1 := (ZERO_1 && ( $slice L 52 27 ) ) $buffering 1
    fpunit_exec_exec__mul53_assign_stmt_12676_c_macro_;
    // $volatile A0 := ( $slice L 26 0 ) $buffering 1
    fpunit_exec_exec__mul53_assign_stmt_12680_c_macro_;
    // $volatile B1 := (ZERO_1 && ( $slice R 52 27 ) ) $buffering 1
    fpunit_exec_exec__mul53_assign_stmt_12686_c_macro_;
    // $volatile B0 := ( $slice R 26 0 ) $buffering 1
    fpunit_exec_exec__mul53_assign_stmt_12690_c_macro_;
    // a0b0 := (($bitcast ($uint<54>) A0 ) * ($bitcast ($uint<54>) B0 ))
    // $buffering 1// bits of buffering = 54. 
    fpunit_exec_exec__mul53_assign_stmt_12697_c_macro_;
    // a0b1 := (($bitcast ($uint<54>) A0 ) * ($bitcast ($uint<54>) B1 ))
    // $buffering 1// bits of buffering = 54. 
    fpunit_exec_exec__mul53_assign_stmt_12704_c_macro_;
    // a1b0 := (($bitcast ($uint<54>) A1 ) * ($bitcast ($uint<54>) B0 ))
    // $buffering 1// bits of buffering = 54. 
    fpunit_exec_exec__mul53_assign_stmt_12711_c_macro_;
    // a1b1 := (($bitcast ($uint<54>) A1 ) * ($bitcast ($uint<54>) B1 ))
    // $buffering 1// bits of buffering = 54. 
    fpunit_exec_exec__mul53_assign_stmt_12718_c_macro_;
    // $volatile a0b0_l := ( $slice a0b0 26 0 ) $buffering 1
    fpunit_exec_exec__mul53_assign_stmt_12722_c_macro_;
    // $volatile a0b0_h := ( $slice a0b0 53 27 ) $buffering 1
    fpunit_exec_exec__mul53_assign_stmt_12726_c_macro_;
    // $volatile a0b1_l := ( $slice a0b1 26 0 ) $buffering 1
    fpunit_exec_exec__mul53_assign_stmt_12730_c_macro_;
    // $volatile a0b1_h := ( $slice a0b1 53 27 ) $buffering 1
    fpunit_exec_exec__mul53_assign_stmt_12734_c_macro_;
    // $volatile a1b0_l := ( $slice a1b0 26 0 ) $buffering 1
    fpunit_exec_exec__mul53_assign_stmt_12738_c_macro_;
    // $volatile a1b0_h := ( $slice a1b0 53 27 ) $buffering 1
    fpunit_exec_exec__mul53_assign_stmt_12742_c_macro_;
    // $volatile a1b1_l := ( $slice a1b1 26 0 ) $buffering 1
    fpunit_exec_exec__mul53_assign_stmt_12746_c_macro_;
    // $volatile a1b1_h := ( $slice a1b1 53 27 ) $buffering 1
    fpunit_exec_exec__mul53_assign_stmt_12750_c_macro_;
    // $volatile P0 := a0b0_l $buffering 1
    fpunit_exec_exec__mul53_assign_stmt_12753_c_macro_;
    // $volatile eP1 := (($bitcast ($uint<29>) a0b0_h ) + (($bitcast
    // ($uint<29>) a0b1_l ) + ($bitcast ($uint<29>) a1b0_l ))) $buffering
    // 1
    fpunit_exec_exec__mul53_assign_stmt_12763_c_macro_;
    // $volatile P1 := ( $slice eP1 26 0 ) $buffering 1
    fpunit_exec_exec__mul53_assign_stmt_12767_c_macro_;
    // $volatile cP1 := ($bitcast ($uint<29>) ( $slice eP1 28 27 ) )
    // $buffering 1
    fpunit_exec_exec__mul53_assign_stmt_12772_c_macro_;
    // $volatile eP2 := ((($bitcast ($uint<29>) a1b0_h ) + ($bitcast
    // ($uint<29>) a0b1_h )) + (($bitcast ($uint<29>) a1b1_l ) + cP1))
    // $buffering 1
    fpunit_exec_exec__mul53_assign_stmt_12784_c_macro_;
    // $volatile P2 := ( $slice eP2 26 0 ) $buffering 1
    fpunit_exec_exec__mul53_assign_stmt_12788_c_macro_;
    // $volatile cP2 := ($bitcast ($uint<25>) ( $slice eP2 28 27 ) )
    // $buffering 1
    fpunit_exec_exec__mul53_assign_stmt_12793_c_macro_;
    // $volatile P3 := (($bitcast ($uint<25>) a1b1_h ) + cP2) $buffering 1
    fpunit_exec_exec__mul53_assign_stmt_12799_c_macro_;
    // RESULT := ((P3 && P2) && (P1 && P0)) $buffering 1// bits of
    // buffering = 106. 
    fpunit_exec_exec__mul53_assign_stmt_12808_c_macro_;
    fpunit_exec_exec__mul53_inner_outarg_prep_macro__;
    MUTEX_UNLOCK(fpunit_exec_exec__mul53_series_block_stmt_12667_c_mutex_);
}
void
_fpunit_exec_exec_needSignalFromRetire_(bit_vector * __pmsg_from_sc,
					bit_vector * __psc_valid,
					bit_vector * __pwait_on_iretire)
{
    MUTEX_DECL
	(fpunit_exec_exec__needSignalFromRetire_series_block_stmt_19700_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__needSignalFromRetire_series_block_stmt_19700_c_mutex_);
    fpunit_exec_exec__needSignalFromRetire_inner_inarg_prep_macro__;
    // $volatile sc_valid := ( $slice msg_from_sc 146 146 ) $buffering 1
    fpunit_exec_exec__needSignalFromRetire_assign_stmt_19707_c_macro_;
    // $volatile w := ( $slice msg_from_sc 133 133 ) $buffering 1
    fpunit_exec_exec__needSignalFromRetire_assign_stmt_19711_c_macro_;
    // wait_on_iretire := (sc_valid & w) $buffering 1
    fpunit_exec_exec__needSignalFromRetire_assign_stmt_19716_c_macro_;
    fpunit_exec_exec__needSignalFromRetire_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__needSignalFromRetire_series_block_stmt_19700_c_mutex_);
}
void
_fpunit_exec_exec_negateVal_(bit_vector * __pa, bit_vector * __pret_val)
{
    MUTEX_DECL
	(fpunit_exec_exec__negateVal_series_block_stmt_13513_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__negateVal_series_block_stmt_13513_c_mutex_);
    fpunit_exec_exec__negateVal_inner_inarg_prep_macro__;
    // ret_val := ( $mux (a != 0 ) (( ~ (a [] 15 ) ) && ( $slice a 14 0 )
    // ) a ) $buffering 1
    fpunit_exec_exec__negateVal_assign_stmt_13529_c_macro_;
    fpunit_exec_exec__negateVal_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__negateVal_series_block_stmt_13513_c_mutex_);
}
void
fpunit_exec_exec_negateVal(uint16_t a, uint16_t * ret_val)
{
    fpunit_exec_exec__negateVal_outer_arg_decl_macro__;
    _fpunit_exec_exec_negateVal_(&__a, &__ret_val);
    fpunit_exec_exec__negateVal_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_negate_classification_(bit_vector * __pC,
					 bit_vector * __pNC)
{
    MUTEX_DECL
	(fpunit_exec_exec__negate_classification_series_block_stmt_10036_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__negate_classification_series_block_stmt_10036_c_mutex_);
    fpunit_exec_exec__negate_classification_inner_inarg_prep_macro__;
    // pn := ( $slice C 9 9 ) $buffering 1
    fpunit_exec_exec__negate_classification_assign_stmt_10042_c_macro_;
    // nn := ( $slice C 8 8 ) $buffering 1
    fpunit_exec_exec__negate_classification_assign_stmt_10046_c_macro_;
    // pd := ( $slice C 7 7 ) $buffering 1
    fpunit_exec_exec__negate_classification_assign_stmt_10050_c_macro_;
    // nd := ( $slice C 6 6 ) $buffering 1
    fpunit_exec_exec__negate_classification_assign_stmt_10054_c_macro_;
    // qn := ( $slice C 5 5 ) $buffering 1
    fpunit_exec_exec__negate_classification_assign_stmt_10058_c_macro_;
    // sn := ( $slice C 4 4 ) $buffering 1
    fpunit_exec_exec__negate_classification_assign_stmt_10062_c_macro_;
    // pi := ( $slice C 3 3 ) $buffering 1
    fpunit_exec_exec__negate_classification_assign_stmt_10066_c_macro_;
    // ni := ( $slice C 2 2 ) $buffering 1
    fpunit_exec_exec__negate_classification_assign_stmt_10070_c_macro_;
    // pz := ( $slice C 1 1 ) $buffering 1
    fpunit_exec_exec__negate_classification_assign_stmt_10074_c_macro_;
    // nz := ( $slice C 0 0 ) $buffering 1
    fpunit_exec_exec__negate_classification_assign_stmt_10078_c_macro_;
    // cn := (pn | nn) $buffering 1
    fpunit_exec_exec__negate_classification_assign_stmt_10083_c_macro_;
    // cd := (pd | nd) $buffering 1
    fpunit_exec_exec__negate_classification_assign_stmt_10088_c_macro_;
    // ci := (pi | ni) $buffering 1
    fpunit_exec_exec__negate_classification_assign_stmt_10093_c_macro_;
    // cz := (pz | nz) $buffering 1
    fpunit_exec_exec__negate_classification_assign_stmt_10098_c_macro_;
    // NC := (((((cn & ( ~ pn )) && (cn & ( ~ nn ))) && (cd & ( ~ pd )))
    // && ((cd & ( ~ nd )) && qn)) && (((sn && (ci & ( ~ pi ))) && (ci & ( 
    // ~ ni ))) && ((cz & ( ~ pz )) && (cz & ( ~ nz ))))) $buffering 1
    fpunit_exec_exec__negate_classification_assign_stmt_10143_c_macro_;
    fpunit_exec_exec__negate_classification_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__negate_classification_series_block_stmt_10036_c_mutex_);
}
void
_fpunit_exec_exec_normalize_32_(bit_vector * __pfract,
				bit_vector * __pexpon,
				bit_vector * __pfract_norm,
				bit_vector * __pexpon_norm)
{
    MUTEX_DECL
	(fpunit_exec_exec__normalize_32_series_block_stmt_14229_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__normalize_32_series_block_stmt_14229_c_mutex_);
    fpunit_exec_exec__normalize_32_inner_inarg_prep_macro__;
    // $volatile $call find_left_24 (fract ) (index found ) 
    fpunit_exec_exec__normalize_32_call_stmt_14237_c_macro_;
    // $volatile shiftx := (23 - ($bitcast ($uint<6>) index )) $buffering
    // 1
    fpunit_exec_exec__normalize_32_assign_stmt_14243_c_macro_;
    // $volatile $call i24_sll (fract ( $slice shiftx 4 0 ) )
    // (fraction_norm ) 
    fpunit_exec_exec__normalize_32_call_stmt_14248_c_macro_;
    // $volatile exp_shift := ($bitcast ($int<10>) shiftx ) $buffering 1
    fpunit_exec_exec__normalize_32_assign_stmt_14252_c_macro_;
    // fract_norm := fraction_norm $buffering 1// bits of buffering = 24. 
    fpunit_exec_exec__normalize_32_assign_stmt_14255_c_macro_;
    // expon_norm := (expon - exp_shift) $buffering 1// bits of buffering
    // = 10. 
    fpunit_exec_exec__normalize_32_assign_stmt_14260_c_macro_;
    fpunit_exec_exec__normalize_32_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__normalize_32_series_block_stmt_14229_c_mutex_);
}
void
_fpunit_exec_exec_normalize_64_(bit_vector * __pfract,
				bit_vector * __pexpon,
				bit_vector * __pfract_norm,
				bit_vector * __pexpon_norm)
{
    MUTEX_DECL
	(fpunit_exec_exec__normalize_64_series_block_stmt_15302_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__normalize_64_series_block_stmt_15302_c_mutex_);
    fpunit_exec_exec__normalize_64_inner_inarg_prep_macro__;
    // $volatile fract_64 := ($bitcast ($uint<64>) fract ) $buffering 1
    fpunit_exec_exec__normalize_64_assign_stmt_15310_c_macro_;
    // $volatile $call find_leftmost_64 (fract_64 ) (index found ) 
    fpunit_exec_exec__normalize_64_call_stmt_15314_c_macro_;
    // $volatile shiftx := (FRACTION_WIDTH_52 - index) $buffering 1
    fpunit_exec_exec__normalize_64_assign_stmt_15319_c_macro_;
    // $volatile $call i64_sll (fract_64 ($bitcast ($uint<6>) shiftx ) )
    // (fraction_norm ) 
    fpunit_exec_exec__normalize_64_call_stmt_15324_c_macro_;
    // $volatile exp_shift := ($bitcast ($int<13>) shiftx ) $buffering 1
    fpunit_exec_exec__normalize_64_assign_stmt_15328_c_macro_;
    // fract_norm := ( $slice fraction_norm 52 0 ) $buffering 1// bits of
    // buffering = 53. 
    fpunit_exec_exec__normalize_64_assign_stmt_15332_c_macro_;
    // expon_norm := (expon - exp_shift) $buffering 1// bits of buffering
    // = 13. 
    fpunit_exec_exec__normalize_64_assign_stmt_15337_c_macro_;
    fpunit_exec_exec__normalize_64_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__normalize_64_series_block_stmt_15302_c_mutex_);
}
void
_fpunit_exec_exec_pre_op_preparation_(bit_vector * __pdecoded_info,
				      bit_vector * __pops,
				      bit_vector * __pthread_head,
				      bit_vector * __pstream_head,
				      bit_vector * __pthread_id,
				      bit_vector * __pstream_id,
				      bit_vector * __pslot_id,
				      bit_vector * __pdo_not_bypass,
				      bit_vector * __pwrite_reg_id,
				      bit_vector * __pfbcond,
				      bit_vector * __pannul_flag,
				      bit_vector * __pdecode_trap,
				      bit_vector * __punimpl_instr,
				      bit_vector * __pinvalid_reg,
				      bit_vector * __pseq_error,
				      bit_vector * __pieee_754_exception,
				      bit_vector * __pcexc,
				      bit_vector * __pfp_dti,
				      bit_vector * __pissue_fmovs,
				      bit_vector * __pissue_fnegs,
				      bit_vector * __pissue_fabss,
				      bit_vector * __pissue_fbfcc,
				      bit_vector * __pissue_fadds,
				      bit_vector * __pissue_fsubs,
				      bit_vector * __pissue_fmuls,
				      bit_vector * __pissue_fdivs,
				      bit_vector * __pissue_fsqrts,
				      bit_vector * __pissue_fcmps,
				      bit_vector * __pissue_fcmpes,
				      bit_vector * __pissue_fitos,
				      bit_vector * __pissue_fstoi,
				      bit_vector * __pissue_fstod,
				      bit_vector * __pissue_faddd,
				      bit_vector * __pissue_fsubd,
				      bit_vector * __pissue_fsmuld,
				      bit_vector * __pissue_fmuld,
				      bit_vector * __pissue_fdivd,
				      bit_vector * __pissue_fsqrtd,
				      bit_vector * __pissue_fcmpd,
				      bit_vector * __pissue_fcmped,
				      bit_vector * __pissue_fitod,
				      bit_vector * __pissue_fdtoi,
				      bit_vector * __pissue_fdtos,
				      bit_vector * __pissue_vfadd,
				      bit_vector * __pissue_vfsub,
				      bit_vector * __pissue_vfmul,
				      bit_vector * __pvf_data_type,
				      bit_vector * __pissue_vfhtoi16,
				      bit_vector * __pissue_vfi16toh,
				      bit_vector * __pissue_faddreduce16,
				      bit_vector * __pissue_fstoh,
				      bit_vector * __pissue_fhtos,
				      bit_vector * __pis_store,
				      bit_vector * __pldfsr,
				      bit_vector * __pskip_fp,
				      bit_vector * __pr1_val_h,
				      bit_vector * __pr1_val_l,
				      bit_vector * __pr2_val_h,
				      bit_vector * __pr2_val_l,
				      bit_vector * __pfsr_val,
				      float *__pf1_s, float *__pf2_s,
				      double *__pf1_d, double *__pf2_d,
				      bit_vector * __pst_val_h,
				      bit_vector * __pst_val_l,
				      bit_vector * __puses_fu1,
				      bit_vector * __pfu1_to_fu2,
				      bit_vector * __pfu1_to_sc,
				      bit_vector * __pfu1_to_ls,
				      bit_vector * __pfu1_to_iu2,
				      bit_vector * __pfu1_to_cu2,
				      bit_vector * __pf1_s_class,
				      bit_vector * __pf2_s_class,
				      bit_vector * __pf1_d_class,
				      bit_vector * __pf2_d_class)
{
    MUTEX_DECL
	(fpunit_exec_exec__pre_op_preparation_series_block_stmt_8797_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__pre_op_preparation_series_block_stmt_8797_c_mutex_);
    fpunit_exec_exec__pre_op_preparation_inner_inarg_prep_macro__;
    // $volatile thread_head := ( $slice decoded_info 78 78 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8877_c_macro_;
    // $volatile stream_head := ( $slice decoded_info 77 77 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8881_c_macro_;
    // $volatile thread_id := ( $slice decoded_info 76 73 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8885_c_macro_;
    // $volatile stream_id := ( $slice decoded_info 72 71 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8889_c_macro_;
    // $volatile slot_id := ( $slice decoded_info 70 65 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8893_c_macro_;
    // $volatile do_not_bypass := ( $slice decoded_info 64 64 ) $buffering 
    // 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8897_c_macro_;
    // $volatile write_reg_id := ( $slice decoded_info 63 59 ) $buffering
    // 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8901_c_macro_;
    // $volatile decode_trap := ( $slice decoded_info 58 58 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8905_c_macro_;
    // $volatile unimpl_instr := ( $slice decoded_info 57 57 ) $buffering
    // 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8909_c_macro_;
    // $volatile invalid_reg := ( $slice decoded_info 56 56 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8913_c_macro_;
    // $volatile seq_error := ( $slice decoded_info 55 55 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8917_c_macro_;
    // $volatile fbfcc := ( $slice decoded_info 54 54 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8921_c_macro_;
    // $volatile annul_flag := ( $slice decoded_info 53 53 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8925_c_macro_;
    // $volatile fadds := ( $slice decoded_info 52 52 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8929_c_macro_;
    // $volatile fsubs := ( $slice decoded_info 51 51 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8933_c_macro_;
    // $volatile fmuls := ( $slice decoded_info 50 50 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8937_c_macro_;
    // $volatile fdivs := ( $slice decoded_info 49 49 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8941_c_macro_;
    // $volatile fsqrts := ( $slice decoded_info 48 48 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8945_c_macro_;
    // $volatile fcmps := ( $slice decoded_info 47 47 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8949_c_macro_;
    // $volatile fcmpes := ( $slice decoded_info 46 46 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8953_c_macro_;
    // $volatile fmovs := ( $slice decoded_info 45 45 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8957_c_macro_;
    // $volatile fnegs := ( $slice decoded_info 44 44 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8961_c_macro_;
    // $volatile fabss := ( $slice decoded_info 43 43 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8965_c_macro_;
    // $volatile fitos := ( $slice decoded_info 42 42 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8969_c_macro_;
    // $volatile fstoi := ( $slice decoded_info 41 41 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8973_c_macro_;
    // $volatile fstod := ( $slice decoded_info 40 40 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8977_c_macro_;
    // $volatile faddd := ( $slice decoded_info 39 39 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8981_c_macro_;
    // $volatile fsubd := ( $slice decoded_info 38 38 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8985_c_macro_;
    // $volatile fsmuld := ( $slice decoded_info 37 37 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8989_c_macro_;
    // $volatile fmuld := ( $slice decoded_info 36 36 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8993_c_macro_;
    // $volatile fdivd := ( $slice decoded_info 35 35 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_8997_c_macro_;
    // $volatile fsqrtd := ( $slice decoded_info 34 34 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9001_c_macro_;
    // $volatile fcmpd := ( $slice decoded_info 33 33 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9005_c_macro_;
    // $volatile fcmped := ( $slice decoded_info 32 32 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9009_c_macro_;
    // $volatile fitod := ( $slice decoded_info 31 31 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9013_c_macro_;
    // $volatile fdtoi := ( $slice decoded_info 30 30 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9017_c_macro_;
    // $volatile fdtos := ( $slice decoded_info 29 29 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9021_c_macro_;
    // $volatile ldf := ( $slice decoded_info 28 28 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9025_c_macro_;
    // $volatile lddf := ( $slice decoded_info 27 27 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9029_c_macro_;
    // $volatile ldfsr := ( $slice decoded_info 26 26 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9033_c_macro_;
    // $volatile stf := ( $slice decoded_info 25 25 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9037_c_macro_;
    // $volatile stdf := ( $slice decoded_info 24 24 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9041_c_macro_;
    // $volatile stfsr := ( $slice decoded_info 23 23 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9045_c_macro_;
    // $volatile stdfq := ( $slice decoded_info 22 22 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9049_c_macro_;
    // $volatile vfadd32 := ( $slice decoded_info 21 21 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9053_c_macro_;
    // $volatile vfadd16 := ( $slice decoded_info 20 20 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9057_c_macro_;
    // $volatile vfsub32 := ( $slice decoded_info 19 19 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9061_c_macro_;
    // $volatile vfsub16 := ( $slice decoded_info 18 18 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9065_c_macro_;
    // $volatile vfmul32 := ( $slice decoded_info 17 17 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9069_c_macro_;
    // $volatile vfmul16 := ( $slice decoded_info 16 16 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9073_c_macro_;
    // $volatile vfhtoi16 := ( $slice decoded_info 15 15 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9077_c_macro_;
    // $volatile vfi16toh := ( $slice decoded_info 14 14 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9081_c_macro_;
    // $volatile faddreduce16 := ( $slice decoded_info 13 13 ) $buffering
    // 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9085_c_macro_;
    // $volatile fstoh := ( $slice decoded_info 12 12 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9089_c_macro_;
    // $volatile fhtos := ( $slice decoded_info 11 11 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9093_c_macro_;
    // $volatile fbcond := ( $slice decoded_info 10 7 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9097_c_macro_;
    // $volatile uses_fu1 := ( $slice decoded_info 6 6 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9101_c_macro_;
    // $volatile fu1_to_fu2 := ( $slice decoded_info 5 5 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9105_c_macro_;
    // $volatile fu1_to_sc := ( $slice decoded_info 4 4 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9109_c_macro_;
    // $volatile fu1_to_ls := ( $slice decoded_info 3 3 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9113_c_macro_;
    // $volatile fu1_to_iu2 := ( $slice decoded_info 2 2 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9117_c_macro_;
    // $volatile fu1_to_cu2 := ( $slice decoded_info 1 1 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9121_c_macro_;
    // $volatile skip_fp := ( $slice decoded_info 0 0 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9125_c_macro_;
    // $report (fpunit_exec fpunit_decode_to_exec thread_id thread_id
    // stream_id stream_id slot_id slot_id )
    fpunit_exec_exec__pre_op_preparation_stmt_9129_c_macro_;
    // issue_vfadd := (vfadd16 | vfadd32) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9134_c_macro_;
    // issue_vfsub := (vfsub16 | vfsub32) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9139_c_macro_;
    // issue_vfmul := (vfmul16 | vfmul32) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9144_c_macro_;
    // vf_data_type := (( $mux ((vfadd16 | vfsub16) | vfmul16) 2 _b0 ) | ( 
    // $mux ((vfadd32 | vfsub32) | vfmul32) 4 _b0 ) ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9163_c_macro_;
    // issue_vfhtoi16 := vfhtoi16 $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9166_c_macro_;
    // issue_vfi16toh := vfi16toh $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9169_c_macro_;
    // issue_faddreduce16 := faddreduce16 $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9172_c_macro_;
    // issue_fstoh := fstoh $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9175_c_macro_;
    // issue_fhtos := fhtos $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9178_c_macro_;
    // $volatile fp_dti := (((ldf | lddf) | (ldfsr | stf)) | ((stdf |
    // stfsr) | stdfq)) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9193_c_macro_;
    // $volatile skip_fp_regs := ( $slice ops 173 173 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9197_c_macro_;
    // $volatile ops_valid := ( $slice ops 172 172 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9201_c_macro_;
    // $volatile thread_id_1 := ( $slice ops 171 168 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9205_c_macro_;
    // $volatile stream_id_1 := ( $slice ops 167 166 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9209_c_macro_;
    // $volatile slot_id_1 := ( $slice ops 165 160 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9213_c_macro_;
    // $volatile r1_val_h := ( $slice ops 159 128 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9217_c_macro_;
    // $volatile r1_val_l := ( $slice ops 127 96 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9221_c_macro_;
    // $volatile r2_val_h := ( $slice ops 95 64 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9225_c_macro_;
    // $volatile r2_val_l := ( $slice ops 63 32 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9229_c_macro_;
    // $volatile fsr_val := ( $slice ops 31 0 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9233_c_macro_;
    // $report (fpunit_exec fpunit_regs_read_access_response ops_valid
    // ops_valid thread_id_1 thread_id_1 slot_id_1 slot_id_1 r1_val_h
    // r1_val_h r1_val_l r1_val_l r2_val_h r2_val_h r2_val_l r2_val_l
    // fsr_val fsr_val skip_fp_regs skip_fp_regs )
    fpunit_exec_exec__pre_op_preparation_stmt_9243_c_macro_;
    // $volatile fsr_tem := ( $slice fsr_val 27 23 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9247_c_macro_;
    // $assert (( ~ uses_fu1 ) | (skip_fp == skip_fp_regs)) $report
    // (fpunit_exec skip_fp_mismatch )
    fpunit_exec_exec__pre_op_preparation_stmt_9254_c_macro_;
    // $assert (( ~ uses_fu1 ) | (thread_id == thread_id_1)) $report
    // (fpunit_exec thread_id_mismatch )
    fpunit_exec_exec__pre_op_preparation_stmt_9261_c_macro_;
    // $assert (( ~ uses_fu1 ) | (stream_id == stream_id_1)) $report
    // (fpunit_exec stream_id_mismatch )
    fpunit_exec_exec__pre_op_preparation_stmt_9268_c_macro_;
    // $assert (( ~ uses_fu1 ) | (slot_id == slot_id_1)) $report
    // (fpunit_exec slot_id_mismatch )
    fpunit_exec_exec__pre_op_preparation_stmt_9275_c_macro_;
    // $volatile f1_s := ($bitcast ($float<8,23>) r1_val_l ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9279_c_macro_;
    // $volatile uf1_d := (r1_val_h && r1_val_l) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9284_c_macro_;
    // $volatile f1_d := ($bitcast ($float<11,52>) uf1_d ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9288_c_macro_;
    // $volatile f2_s := ($bitcast ($float<8,23>) r2_val_l ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9292_c_macro_;
    // $volatile uf2_d := (r2_val_h && r2_val_l) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9297_c_macro_;
    // $volatile f2_d := ($bitcast ($float<11,52>) uf2_d ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9301_c_macro_;
    // $volatile NVM := ( $slice fsr_tem 4 4 ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9305_c_macro_;
    // $volatile $call generate_pre_compute_exceptions (thread_id
    // stream_id slot_id fadds fsubs (fmuls | fsmuld) fdivs fcmps fcmpes
    // fsqrts fstoi fitos fstod f1_s f2_s faddd fsubd fmuld fdivd fcmpd
    // fcmped fsqrtd fdtoi fdtos f1_d f2_d ) (nvc ofc ufc dzc nxc
    // f1_s_class f2_s_class f1_d_class f2_d_class ) 
    fpunit_exec_exec__pre_op_preparation_call_stmt_9343_c_macro_;
    // $volatile ieee_754_exception := ((uses_fu1 & NVM) & nvc) $buffering 
    // 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9350_c_macro_;
    // $volatile cexc := (((nvc && ofc) && ufc) && (dzc && nxc))
    // $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9361_c_macro_;
    // $guard (ieee_754_exception) $report (fpunit_exec
    // snan_exception_found thread_id thread_id stream_id stream_id
    // slot_id slot_id nvc nvc )
    fpunit_exec_exec__pre_op_preparation_stmt_9367_c_macro_;
    // $volatile ok_to_issue := (uses_fu1 & ( ~ decode_trap )) $buffering
    // 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9373_c_macro_;
    // $volatile issue_fmovs := fmovs $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9376_c_macro_;
    // $volatile issue_fnegs := fnegs $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9379_c_macro_;
    // $volatile issue_fabss := fabss $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9382_c_macro_;
    // $volatile issue_fbfcc := fbfcc $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9385_c_macro_;
    // $volatile issue_fadds := fadds $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9388_c_macro_;
    // $volatile issue_fsubs := fsubs $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9391_c_macro_;
    // $volatile issue_fmuls := fmuls $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9394_c_macro_;
    // $volatile issue_fdivs := (ok_to_issue & fdivs) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9399_c_macro_;
    // $volatile issue_fsqrts := (ok_to_issue & fsqrts) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9404_c_macro_;
    // $volatile issue_fcmps := fcmps $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9407_c_macro_;
    // $volatile issue_fcmpes := fcmpes $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9410_c_macro_;
    // $volatile issue_fitos := fitos $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9413_c_macro_;
    // $volatile issue_fstoi := fstoi $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9416_c_macro_;
    // $volatile issue_fstod := fstod $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9419_c_macro_;
    // $volatile issue_faddd := faddd $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9422_c_macro_;
    // $volatile issue_fsubd := fsubd $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9425_c_macro_;
    // $volatile issue_fsmuld := fsmuld $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9428_c_macro_;
    // $volatile issue_fmuld := fmuld $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9431_c_macro_;
    // $volatile issue_fdivd := (ok_to_issue & fdivd) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9436_c_macro_;
    // $volatile issue_fsqrtd := (ok_to_issue & fsqrtd) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9441_c_macro_;
    // $volatile issue_fcmpd := fcmpd $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9444_c_macro_;
    // $volatile issue_fcmped := fcmped $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9447_c_macro_;
    // $volatile issue_fitod := fitod $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9450_c_macro_;
    // $volatile issue_fdtoi := fdtoi $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9453_c_macro_;
    // $volatile issue_fdtos := fdtos $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9456_c_macro_;
    // $volatile st_val_l := ( $mux stfsr fsr_val r1_val_l ) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9462_c_macro_;
    // $volatile st_val_h := r1_val_h $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9465_c_macro_;
    // $volatile is_store := ((stf | stdf) | stfsr) $buffering 1
    fpunit_exec_exec__pre_op_preparation_assign_stmt_9472_c_macro_;
    fpunit_exec_exec__pre_op_preparation_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__pre_op_preparation_series_block_stmt_8797_c_mutex_);
}
void
_fpunit_exec_exec_round_32_extn_(bit_vector * __psticky,
				 bit_vector * __papply_sticky_correction,
				 bit_vector * __punbiased_exp_13,
				 bit_vector * __pmantissa_62,
				 bit_vector *
				 __psp_biased_exp_13_post_round,
				 bit_vector * __psp_mantissa_23_post_round)
{
    MUTEX_DECL
	(fpunit_exec_exec__round_32_extn_series_block_stmt_7553_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__round_32_extn_series_block_stmt_7553_c_mutex_);
    fpunit_exec_exec__round_32_extn_inner_inarg_prep_macro__;
    // $report (fpunit_exec round_32_extn_in_args sticky sticky
    // unbiased_exp_13 unbiased_exp_13 mantissa_62 mantissa_62 )
    fpunit_exec_exec__round_32_extn_stmt_7563_c_macro_;
    // s_exp_13 := ($bitcast ($uint<13>) unbiased_exp_13 ) $buffering 1
    fpunit_exec_exec__round_32_extn_assign_stmt_7567_c_macro_;
    // SP_frac_temp := ((ZERO_1 && ONE_1) && ( $slice mantissa_62 61 39 )
    // ) $buffering 1
    fpunit_exec_exec__round_32_extn_assign_stmt_7575_c_macro_;
    // SP_lsb_frac := (mantissa_62 [] 39 ) $buffering 1
    fpunit_exec_exec__round_32_extn_assign_stmt_7580_c_macro_;
    // SP_round_bits := ( $slice mantissa_62 38 0 ) $buffering 1
    fpunit_exec_exec__round_32_extn_assign_stmt_7584_c_macro_;
    // SP_round_value_equal := (SP_round_bits == SP_round_mid) $buffering
    // 1
    fpunit_exec_exec__round_32_extn_assign_stmt_7589_c_macro_;
    // SP_round_value_greater := (SP_round_bits > SP_round_mid) $buffering 
    // 1
    fpunit_exec_exec__round_32_extn_assign_stmt_7594_c_macro_;
    // SP_need_to_round := ((SP_round_value_greater |
    // ((SP_round_value_equal & SP_lsb_frac) & ( ~ apply_sticky_correction 
    // ))) | ((SP_round_value_equal & sticky) & ( ~
    // apply_sticky_correction ))) $buffering 1
    fpunit_exec_exec__round_32_extn_assign_stmt_7611_c_macro_;
    // SP_round_operator := ( $mux SP_need_to_round ONE_25 ZERO_25 )
    // $buffering 1
    fpunit_exec_exec__round_32_extn_assign_stmt_7617_c_macro_;
    // SP_fraction_rounded := (SP_frac_temp + SP_round_operator)
    // $buffering 1
    fpunit_exec_exec__round_32_extn_assign_stmt_7622_c_macro_;
    // SP_increase_exponent := ((( ~ ( $slice SP_frac_temp 22 0 ) ) == _b0 
    // ) & SP_need_to_round) $buffering 1
    fpunit_exec_exec__round_32_extn_assign_stmt_7631_c_macro_;
    // $report (fpunit_exec round_32_extn_increase_exponent SP_frac_temp
    // SP_frac_temp SP_increase_exponent SP_increase_exponent
    // SP_fraction_rounded SP_fraction_rounded SP_frac_temp SP_frac_temp )
    fpunit_exec_exec__round_32_extn_stmt_7636_c_macro_;
    // sp_mantissa_23_post_round := ( $mux SP_increase_exponent ( $slice
    // SP_fraction_rounded 23 1 ) ( $slice SP_fraction_rounded 22 0 ) )
    // $buffering 1
    fpunit_exec_exec__round_32_extn_assign_stmt_7644_c_macro_;
    // sp_biased_exp_13_post_round := ($bitcast ($uint<13>) (s_exp_13 + (
    // $mux SP_increase_exponent 128 127 ) ) ) $buffering 1
    fpunit_exec_exec__round_32_extn_assign_stmt_7653_c_macro_;
    fpunit_exec_exec__round_32_extn_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__round_32_extn_series_block_stmt_7553_c_mutex_);
}
void
_fpunit_exec_exec_round_64_extn_(bit_vector * __psticky,
				 bit_vector * __papply_sticky_correction,
				 bit_vector * __punbiased_exp_13,
				 bit_vector * __pmantissa_62,
				 bit_vector *
				 __pdp_biased_exp_13_post_round,
				 bit_vector * __pdp_mantissa_52_post_round)
{
    MUTEX_DECL
	(fpunit_exec_exec__round_64_extn_series_block_stmt_7697_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__round_64_extn_series_block_stmt_7697_c_mutex_);
    fpunit_exec_exec__round_64_extn_inner_inarg_prep_macro__;
    // s_exp_13 := ($bitcast ($int<13>) unbiased_exp_13 ) $buffering 1
    fpunit_exec_exec__round_64_extn_assign_stmt_7707_c_macro_;
    // DP_frac_temp := ((ZERO_1 && ONE_1) && ( $slice mantissa_62 61 10 )
    // ) $buffering 1
    fpunit_exec_exec__round_64_extn_assign_stmt_7715_c_macro_;
    // DP_lsb_frac := (mantissa_62 [] 10 ) $buffering 1
    fpunit_exec_exec__round_64_extn_assign_stmt_7720_c_macro_;
    // DP_round_bits := ( $slice mantissa_62 9 0 ) $buffering 1
    fpunit_exec_exec__round_64_extn_assign_stmt_7724_c_macro_;
    // DP_round_value_equal := (DP_round_bits == DP_round_mid) $buffering
    // 1
    fpunit_exec_exec__round_64_extn_assign_stmt_7729_c_macro_;
    // DP_round_value_greater := (DP_round_bits > DP_round_mid) $buffering 
    // 1
    fpunit_exec_exec__round_64_extn_assign_stmt_7734_c_macro_;
    // DP_need_to_round := ((DP_round_value_greater |
    // ((DP_round_value_equal & DP_lsb_frac) & ( ~ apply_sticky_correction 
    // ))) | ((DP_round_value_equal & sticky) & ( ~
    // apply_sticky_correction ))) $buffering 1
    fpunit_exec_exec__round_64_extn_assign_stmt_7751_c_macro_;
    // DP_round_operator := ( $mux DP_need_to_round ONE_54 ZERO_54 )
    // $buffering 1
    fpunit_exec_exec__round_64_extn_assign_stmt_7757_c_macro_;
    // DP_fraction_rounded := (DP_frac_temp + DP_round_operator)
    // $buffering 1
    fpunit_exec_exec__round_64_extn_assign_stmt_7762_c_macro_;
    // DP_increase_exponent := ((( ~ ( $slice DP_frac_temp 51 0 ) ) == _b0 
    // ) & DP_need_to_round) $buffering 1
    fpunit_exec_exec__round_64_extn_assign_stmt_7771_c_macro_;
    // dp_biased_exp_13_post_round := ($bitcast ($uint<13>) (s_exp_13 + (
    // $mux DP_increase_exponent 1024 1023 ) ) ) $buffering 1
    fpunit_exec_exec__round_64_extn_assign_stmt_7780_c_macro_;
    // dp_mantissa_52_post_round := ( $mux DP_increase_exponent ( $slice
    // DP_fraction_rounded 52 1 ) ( $slice DP_fraction_rounded 51 0 ) )
    // $buffering 1
    fpunit_exec_exec__round_64_extn_assign_stmt_7788_c_macro_;
    fpunit_exec_exec__round_64_extn_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__round_64_extn_series_block_stmt_7697_c_mutex_);
}
void
_fpunit_exec_exec_round_e_32_(bit_vector * __psticky_flag,
			      bit_vector * __psigned_unbiased_exponent,
			      bit_vector * __ppadded_mantissa,
			      float *__presult)
{
    MUTEX_DECL
	(fpunit_exec_exec__round_e_32_series_block_stmt_15135_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__round_e_32_series_block_stmt_15135_c_mutex_);
    fpunit_exec_exec__round_e_32_inner_inarg_prep_macro__;
    // ue_13 := ($bitcast ($uint<13>) signed_unbiased_exponent )
    // $buffering 1
    fpunit_exec_exec__round_e_32_assign_stmt_15143_c_macro_;
    // m_62 := (( $slice padded_mantissa 30 0 ) && ZERO_31) $buffering 1
    fpunit_exec_exec__round_e_32_assign_stmt_15149_c_macro_;
    // $report (round_e_32 in_args__ signed_unbiased_exponent
    // signed_unbiased_exponent padded_mantissa padded_mantissa ue_13
    // ue_13 m_62 m_62 )
    fpunit_exec_exec__round_e_32_stmt_15154_c_macro_;
    // $volatile $call round_32_extn (sticky_flag ZERO_1 ue_13 m_62 )
    // (r_ue_13 r_m_23 ) 
    fpunit_exec_exec__round_e_32_call_stmt_15161_c_macro_;
    // ur32 := ((ZERO_1 && ( $slice r_ue_13 7 0 ) ) && r_m_23) $buffering
    // 1
    fpunit_exec_exec__round_e_32_assign_stmt_15169_c_macro_;
    // result := ($bitcast ($float<8,23>) ur32 ) $buffering 1
    fpunit_exec_exec__round_e_32_assign_stmt_15173_c_macro_;
    // $report (round_e_32 out_args__ ur32 ur32 )
    fpunit_exec_exec__round_e_32_stmt_15175_c_macro_;
    fpunit_exec_exec__round_e_32_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__round_e_32_series_block_stmt_15135_c_mutex_);
}
void
_fpunit_exec_exec_round_e_64_(bit_vector * __psticky_flag,
			      bit_vector * __psigned_unbiased_exponent,
			      bit_vector * __ppadded_mantissa,
			      double *__presult)
{
    MUTEX_DECL
	(fpunit_exec_exec__round_e_64_series_block_stmt_16213_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__round_e_64_series_block_stmt_16213_c_mutex_);
    fpunit_exec_exec__round_e_64_inner_inarg_prep_macro__;
    // ue_13 := ($bitcast ($uint<13>) signed_unbiased_exponent )
    // $buffering 1
    fpunit_exec_exec__round_e_64_assign_stmt_16221_c_macro_;
    // m_62 := (( $slice padded_mantissa 54 0 ) && ZERO_7) $buffering 1
    fpunit_exec_exec__round_e_64_assign_stmt_16227_c_macro_;
    // $report (round_e_64 in_args__ signed_unbiased_exponent
    // signed_unbiased_exponent padded_mantissa padded_mantissa ue_13
    // ue_13 m_62 m_62 )
    fpunit_exec_exec__round_e_64_stmt_16232_c_macro_;
    // $volatile $call round_64_extn (sticky_flag ZERO_1 ue_13 m_62 )
    // (r_ue_13 r_m_52 ) 
    fpunit_exec_exec__round_e_64_call_stmt_16239_c_macro_;
    // ur64 := ((ZERO_1 && ( $slice r_ue_13 10 0 ) ) && r_m_52) $buffering 
    // 1
    fpunit_exec_exec__round_e_64_assign_stmt_16247_c_macro_;
    // result := ($bitcast ($float<11,52>) ur64 ) $buffering 1
    fpunit_exec_exec__round_e_64_assign_stmt_16251_c_macro_;
    // $report (round_e_64 out_args__ ur64 ur64 )
    fpunit_exec_exec__round_e_64_stmt_16253_c_macro_;
    fpunit_exec_exec__round_e_64_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__round_e_64_series_block_stmt_16213_c_mutex_);
}
void
_fpunit_exec_exec_round_fp_32_(bit_vector * __pEXTENDED_RESULT,
			       bit_vector * __pRESULT_32)
{
    MUTEX_DECL
	(fpunit_exec_exec__round_fp_32_series_block_stmt_12594_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__round_fp_32_series_block_stmt_12594_c_mutex_);
    fpunit_exec_exec__round_fp_32_inner_inarg_prep_macro__;
    // $volatile sticky := ( $slice EXTENDED_RESULT 80 80 ) $buffering 1
    fpunit_exec_exec__round_fp_32_assign_stmt_12600_c_macro_;
    // $volatile apply_sticky_correction := ( $slice EXTENDED_RESULT 79 79 
    // ) $buffering 1
    fpunit_exec_exec__round_fp_32_assign_stmt_12604_c_macro_;
    // $volatile sign := ( $slice EXTENDED_RESULT 78 78 ) $buffering 1
    fpunit_exec_exec__round_fp_32_assign_stmt_12608_c_macro_;
    // $volatile nan := ( $slice EXTENDED_RESULT 77 77 ) $buffering 1
    fpunit_exec_exec__round_fp_32_assign_stmt_12612_c_macro_;
    // $volatile inf := ( $slice EXTENDED_RESULT 76 76 ) $buffering 1
    fpunit_exec_exec__round_fp_32_assign_stmt_12616_c_macro_;
    // $volatile zero := ( $slice EXTENDED_RESULT 75 75 ) $buffering 1
    fpunit_exec_exec__round_fp_32_assign_stmt_12620_c_macro_;
    // $volatile unbiased_exp_13 := ( $slice EXTENDED_RESULT 74 62 )
    // $buffering 1
    fpunit_exec_exec__round_fp_32_assign_stmt_12624_c_macro_;
    // $volatile mantissa_62 := ( $slice EXTENDED_RESULT 61 0 ) $buffering 
    // 1
    fpunit_exec_exec__round_fp_32_assign_stmt_12628_c_macro_;
    // $report (fpunit_exec round_fp_in_args sticky sticky
    // apply_sticky_correction apply_sticky_correction sign sign nan nan
    // inf inf zero zero unbiased_exp_13 unbiased_exp_13 mantissa_62
    // mantissa_62 )
    fpunit_exec_exec__round_fp_32_stmt_12637_c_macro_;
    // $volatile $call round_32_extn (sticky apply_sticky_correction
    // unbiased_exp_13 mantissa_62 ) (sp_biased_exp_13_post_round
    // sp_mantissa_23_post_round ) 
    fpunit_exec_exec__round_fp_32_call_stmt_12644_c_macro_;
    // RESULT_32 := ( $mux ((nan | inf) | zero) ((sign && ( $slice
    // unbiased_exp_13 7 0 ) ) && ( $slice mantissa_62 61 39 ) ) ((sign && 
    // ( $slice sp_biased_exp_13_post_round 7 0 ) ) &&
    // sp_mantissa_23_post_round) ) $buffering 1
    fpunit_exec_exec__round_fp_32_assign_stmt_12665_c_macro_;
    fpunit_exec_exec__round_fp_32_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__round_fp_32_series_block_stmt_12594_c_mutex_);
}
void
_fpunit_exec_exec_round_fp_64_(bit_vector * __pEXTENDED_RESULT,
			       bit_vector * __pRESULT_64)
{
    MUTEX_DECL
	(fpunit_exec_exec__round_fp_64_series_block_stmt_13440_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__round_fp_64_series_block_stmt_13440_c_mutex_);
    fpunit_exec_exec__round_fp_64_inner_inarg_prep_macro__;
    // $volatile sticky := ( $slice EXTENDED_RESULT 80 80 ) $buffering 1
    fpunit_exec_exec__round_fp_64_assign_stmt_13446_c_macro_;
    // $volatile apply_sticky_correction := ( $slice EXTENDED_RESULT 79 79 
    // ) $buffering 1
    fpunit_exec_exec__round_fp_64_assign_stmt_13450_c_macro_;
    // $volatile sign := ( $slice EXTENDED_RESULT 78 78 ) $buffering 1
    fpunit_exec_exec__round_fp_64_assign_stmt_13454_c_macro_;
    // $volatile nan := ( $slice EXTENDED_RESULT 77 77 ) $buffering 1
    fpunit_exec_exec__round_fp_64_assign_stmt_13458_c_macro_;
    // $volatile inf := ( $slice EXTENDED_RESULT 76 76 ) $buffering 1
    fpunit_exec_exec__round_fp_64_assign_stmt_13462_c_macro_;
    // $volatile zero := ( $slice EXTENDED_RESULT 75 75 ) $buffering 1
    fpunit_exec_exec__round_fp_64_assign_stmt_13466_c_macro_;
    // $volatile unbiased_exp_13 := ( $slice EXTENDED_RESULT 74 62 )
    // $buffering 1
    fpunit_exec_exec__round_fp_64_assign_stmt_13470_c_macro_;
    // $volatile mantissa_62 := ( $slice EXTENDED_RESULT 61 0 ) $buffering 
    // 1
    fpunit_exec_exec__round_fp_64_assign_stmt_13474_c_macro_;
    // $report (fpunit_exec round_fp_in_args sticky sticky
    // apply_sticky_correction apply_sticky_correction sign sign nan nan
    // inf inf zero zero unbiased_exp_13 unbiased_exp_13 mantissa_62
    // mantissa_62 )
    fpunit_exec_exec__round_fp_64_stmt_13483_c_macro_;
    // $volatile $call round_64_extn (sticky apply_sticky_correction
    // unbiased_exp_13 mantissa_62 ) (dp_biased_exp_13_post_round
    // dp_mantissa_52_post_round ) 
    fpunit_exec_exec__round_fp_64_call_stmt_13490_c_macro_;
    // RESULT_64 := ( $mux ((nan | inf) | zero) ((sign && ( $slice
    // unbiased_exp_13 10 0 ) ) && ( $slice mantissa_62 61 10 ) ) ((sign
    // && ( $slice dp_biased_exp_13_post_round 10 0 ) ) &&
    // dp_mantissa_52_post_round) ) $buffering 1
    fpunit_exec_exec__round_fp_64_assign_stmt_13511_c_macro_;
    fpunit_exec_exec__round_fp_64_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__round_fp_64_series_block_stmt_13440_c_mutex_);
}
void
_fpunit_exec_exec_shifter_left_right_32_(bit_vector * __pop,
					 bit_vector * __pshiftx,
					 bit_vector * __pleft,
					 bit_vector * __pshifted)
{
    MUTEX_DECL
	(fpunit_exec_exec__shifter_left_right_32_series_block_stmt_19718_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__shifter_left_right_32_series_block_stmt_19718_c_mutex_);
    fpunit_exec_exec__shifter_left_right_32_inner_inarg_prep_macro__;
    // $volatile l4 := (shiftx [] 4 ) $buffering 1
    fpunit_exec_exec__shifter_left_right_32_assign_stmt_19727_c_macro_;
    // $volatile l3 := (shiftx [] 3 ) $buffering 1
    fpunit_exec_exec__shifter_left_right_32_assign_stmt_19732_c_macro_;
    // $volatile l2 := (shiftx [] 2 ) $buffering 1
    fpunit_exec_exec__shifter_left_right_32_assign_stmt_19737_c_macro_;
    // $volatile l1 := (shiftx [] 1 ) $buffering 1
    fpunit_exec_exec__shifter_left_right_32_assign_stmt_19742_c_macro_;
    // $volatile l0 := (shiftx [] 0 ) $buffering 1
    fpunit_exec_exec__shifter_left_right_32_assign_stmt_19747_c_macro_;
    // $volatile reversed_input := ((((((op [] 0 ) && (op [] 1 )) && ((op
    // [] 2 ) && (op [] 3 ))) && (((op [] 4 ) && (op [] 5 )) && ((op [] 6
    // ) && (op [] 7 )))) && ((((op [] 8 ) && (op [] 9 )) && ((op [] 10 )
    // && (op [] 11 ))) && (((op [] 12 ) && (op [] 13 )) && ((op [] 14 )
    // && (op [] 15 ))))) && (((((op [] 16 ) && (op [] 17 )) && ((op [] 18 
    // ) && (op [] 19 ))) && (((op [] 20 ) && (op [] 21 )) && ((op [] 22 ) 
    // && (op [] 23 )))) && ((((op [] 24 ) && (op [] 25 )) && ((op [] 26 ) 
    // && (op [] 27 ))) && (((op [] 28 ) && (op [] 29 )) && ((op [] 30 )
    // && (op [] 31 )))))) $buffering 1
    fpunit_exec_exec__shifter_left_right_32_assign_stmt_19876_c_macro_;
    // $volatile level_4_no_shift := ( $mux left op reversed_input )
    // $buffering 1
    fpunit_exec_exec__shifter_left_right_32_assign_stmt_19882_c_macro_;
    // $volatile level_4_shift := (( $slice level_4_no_shift 15 0 ) &&
    // ZERO_16) $buffering 1
    fpunit_exec_exec__shifter_left_right_32_assign_stmt_19888_c_macro_;
    // $volatile level_4_output := ( $mux l4 level_4_shift
    // level_4_no_shift ) $buffering 1
    fpunit_exec_exec__shifter_left_right_32_assign_stmt_19894_c_macro_;
    // $volatile level_3_no_shift := level_4_output $buffering 1
    fpunit_exec_exec__shifter_left_right_32_assign_stmt_19897_c_macro_;
    // $volatile level_3_shift := (( $slice level_3_no_shift 23 0 ) &&
    // ZERO_8) $buffering 1
    fpunit_exec_exec__shifter_left_right_32_assign_stmt_19903_c_macro_;
    // $volatile level_3_output := ( $mux l3 level_3_shift
    // level_3_no_shift ) $buffering 1
    fpunit_exec_exec__shifter_left_right_32_assign_stmt_19909_c_macro_;
    // $volatile level_2_no_shift := level_3_output $buffering 1
    fpunit_exec_exec__shifter_left_right_32_assign_stmt_19912_c_macro_;
    // $volatile level_2_shift := (( $slice level_2_no_shift 27 0 ) &&
    // ZERO_4) $buffering 1
    fpunit_exec_exec__shifter_left_right_32_assign_stmt_19918_c_macro_;
    // $volatile level_2_output := ( $mux l2 level_2_shift
    // level_2_no_shift ) $buffering 1
    fpunit_exec_exec__shifter_left_right_32_assign_stmt_19924_c_macro_;
    // $volatile level_1_no_shift := level_2_output $buffering 1
    fpunit_exec_exec__shifter_left_right_32_assign_stmt_19927_c_macro_;
    // $volatile level_1_shift := (( $slice level_1_no_shift 29 0 ) &&
    // ZERO_2) $buffering 1
    fpunit_exec_exec__shifter_left_right_32_assign_stmt_19933_c_macro_;
    // $volatile level_1_output := ( $mux l1 level_1_shift
    // level_1_no_shift ) $buffering 1
    fpunit_exec_exec__shifter_left_right_32_assign_stmt_19939_c_macro_;
    // $volatile level_0_no_shift := level_1_output $buffering 1
    fpunit_exec_exec__shifter_left_right_32_assign_stmt_19942_c_macro_;
    // $volatile level_0_shift := (( $slice level_1_output 30 0 ) &&
    // ZERO_1) $buffering 1
    fpunit_exec_exec__shifter_left_right_32_assign_stmt_19948_c_macro_;
    // $volatile level_0_output := ( $mux l0 level_0_shift
    // level_0_no_shift ) $buffering 1
    fpunit_exec_exec__shifter_left_right_32_assign_stmt_19954_c_macro_;
    // $volatile reversed_output := ((((((level_0_output [] 0 ) &&
    // (level_0_output [] 1 )) && ((level_0_output [] 2 ) &&
    // (level_0_output [] 3 ))) && (((level_0_output [] 4 ) &&
    // (level_0_output [] 5 )) && ((level_0_output [] 6 ) &&
    // (level_0_output [] 7 )))) && ((((level_0_output [] 8 ) &&
    // (level_0_output [] 9 )) && ((level_0_output [] 10 ) &&
    // (level_0_output [] 11 ))) && (((level_0_output [] 12 ) &&
    // (level_0_output [] 13 )) && ((level_0_output [] 14 ) &&
    // (level_0_output [] 15 ))))) && (((((level_0_output [] 16 ) &&
    // (level_0_output [] 17 )) && ((level_0_output [] 18 ) &&
    // (level_0_output [] 19 ))) && (((level_0_output [] 20 ) &&
    // (level_0_output [] 21 )) && ((level_0_output [] 22 ) &&
    // (level_0_output [] 23 )))) && ((((level_0_output [] 24 ) &&
    // (level_0_output [] 25 )) && ((level_0_output [] 26 ) &&
    // (level_0_output [] 27 ))) && (((level_0_output [] 28 ) &&
    // (level_0_output [] 29 )) && ((level_0_output [] 30 ) &&
    // (level_0_output [] 31 )))))) $buffering 1
    fpunit_exec_exec__shifter_left_right_32_assign_stmt_20083_c_macro_;
    // shifted := ( $mux left level_0_output reversed_output ) $buffering
    // 1// bits of buffering = 32. 
    fpunit_exec_exec__shifter_left_right_32_assign_stmt_20089_c_macro_;
    fpunit_exec_exec__shifter_left_right_32_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__shifter_left_right_32_series_block_stmt_19718_c_mutex_);
}
void
_fpunit_exec_exec_shifter_left_right_64_(bit_vector * __pop,
					 bit_vector * __pshiftx,
					 bit_vector * __pleft,
					 bit_vector * __pshifted)
{
    MUTEX_DECL
	(fpunit_exec_exec__shifter_left_right_64_series_block_stmt_20091_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__shifter_left_right_64_series_block_stmt_20091_c_mutex_);
    fpunit_exec_exec__shifter_left_right_64_inner_inarg_prep_macro__;
    // $volatile l5 := (shiftx [] 5 ) $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20100_c_macro_;
    // $volatile l4 := (shiftx [] 4 ) $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20105_c_macro_;
    // $volatile l3 := (shiftx [] 3 ) $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20110_c_macro_;
    // $volatile l2 := (shiftx [] 2 ) $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20115_c_macro_;
    // $volatile l1 := (shiftx [] 1 ) $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20120_c_macro_;
    // $volatile l0 := (shiftx [] 0 ) $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20125_c_macro_;
    // $volatile reversed_input := (((((((op [] 0 ) && (op [] 1 )) && ((op 
    // [] 2 ) && (op [] 3 ))) && (((op [] 4 ) && (op [] 5 )) && ((op [] 6
    // ) && (op [] 7 )))) && ((((op [] 8 ) && (op [] 9 )) && ((op [] 10 )
    // && (op [] 11 ))) && (((op [] 12 ) && (op [] 13 )) && ((op [] 14 )
    // && (op [] 15 ))))) && (((((op [] 16 ) && (op [] 17 )) && ((op [] 18 
    // ) && (op [] 19 ))) && (((op [] 20 ) && (op [] 21 )) && ((op [] 22 ) 
    // && (op [] 23 )))) && ((((op [] 24 ) && (op [] 25 )) && ((op [] 26 ) 
    // && (op [] 27 ))) && (((op [] 28 ) && (op [] 29 )) && ((op [] 30 )
    // && (op [] 31 )))))) && ((((((op [] 32 ) && (op [] 33 )) && ((op []
    // 34 ) && (op [] 35 ))) && (((op [] 36 ) && (op [] 37 )) && ((op []
    // 38 ) && (op [] 39 )))) && ((((op [] 40 ) && (op [] 41 )) && ((op [] 
    // 42 ) && (op [] 43 ))) && (((op [] 44 ) && (op [] 45 )) && ((op []
    // 46 ) && (op [] 47 ))))) && (((((op [] 48 ) && (op [] 49 )) && ((op
    // [] 50 ) && (op [] 51 ))) && (((op [] 52 ) && (op [] 53 )) && ((op
    // [] 54 ) && (op [] 55 )))) && ((((op [] 56 ) && (op [] 57 )) && ((op 
    // [] 58 ) && (op [] 59 ))) && (((op [] 60 ) && (op [] 61 )) && ((op
    // [] 62 ) && (op [] 63 ))))))) $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20382_c_macro_;
    // $volatile level_5_no_shift := ( $mux left op reversed_input )
    // $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20388_c_macro_;
    // $volatile level_5_shift := (( $slice level_5_no_shift 31 0 ) &&
    // ZERO_32) $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20394_c_macro_;
    // $volatile level_5_output := ( $mux l5 level_5_shift
    // level_5_no_shift ) $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20400_c_macro_;
    // $volatile level_4_no_shift := level_5_output $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20403_c_macro_;
    // $volatile level_4_shift := (( $slice level_5_output 47 0 ) &&
    // ZERO_16) $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20409_c_macro_;
    // $volatile level_4_output := ( $mux l4 level_4_shift
    // level_4_no_shift ) $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20415_c_macro_;
    // $volatile level_3_no_shift := level_4_output $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20418_c_macro_;
    // $volatile level_3_shift := (( $slice level_4_output 55 0 ) &&
    // ZERO_8) $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20424_c_macro_;
    // level_3_output := ( $mux l3 level_3_shift level_3_no_shift )
    // $buffering 1// bits of buffering = 64. 
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20430_c_macro_;
    // $volatile level_2_no_shift := level_3_output $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20433_c_macro_;
    // $volatile level_2_shift := (( $slice level_3_output 59 0 ) &&
    // ZERO_4) $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20439_c_macro_;
    // $volatile level_2_output := ( $mux l2 level_2_shift
    // level_2_no_shift ) $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20445_c_macro_;
    // $volatile level_1_no_shift := level_2_output $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20448_c_macro_;
    // $volatile level_1_shift := (( $slice level_2_output 61 0 ) &&
    // ZERO_2) $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20454_c_macro_;
    // $volatile level_1_output := ( $mux l1 level_1_shift
    // level_1_no_shift ) $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20460_c_macro_;
    // $volatile level_0_no_shift := level_1_output $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20463_c_macro_;
    // $volatile level_0_shift := (( $slice level_1_output 62 0 ) &&
    // ZERO_1) $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20469_c_macro_;
    // $volatile level_0_output := ( $mux l0 level_0_shift
    // level_0_no_shift ) $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20475_c_macro_;
    // $volatile reversed_output := (((((((level_0_output [] 0 ) &&
    // (level_0_output [] 1 )) && ((level_0_output [] 2 ) &&
    // (level_0_output [] 3 ))) && (((level_0_output [] 4 ) &&
    // (level_0_output [] 5 )) && ((level_0_output [] 6 ) &&
    // (level_0_output [] 7 )))) && ((((level_0_output [] 8 ) &&
    // (level_0_output [] 9 )) && ((level_0_output [] 10 ) &&
    // (level_0_output [] 11 ))) && (((level_0_output [] 12 ) &&
    // (level_0_output [] 13 )) && ((level_0_output [] 14 ) &&
    // (level_0_output [] 15 ))))) && (((((level_0_output [] 16 ) &&
    // (level_0_output [] 17 )) && ((level_0_output [] 18 ) &&
    // (level_0_output [] 19 ))) && (((level_0_output [] 20 ) &&
    // (level_0_output [] 21 )) && ((level_0_output [] 22 ) &&
    // (level_0_output [] 23 )))) && ((((level_0_output [] 24 ) &&
    // (level_0_output [] 25 )) && ((level_0_output [] 26 ) &&
    // (level_0_output [] 27 ))) && (((level_0_output [] 28 ) &&
    // (level_0_output [] 29 )) && ((level_0_output [] 30 ) &&
    // (level_0_output [] 31 )))))) && ((((((level_0_output [] 32 ) &&
    // (level_0_output [] 33 )) && ((level_0_output [] 34 ) &&
    // (level_0_output [] 35 ))) && (((level_0_output [] 36 ) &&
    // (level_0_output [] 37 )) && ((level_0_output [] 38 ) &&
    // (level_0_output [] 39 )))) && ((((level_0_output [] 40 ) &&
    // (level_0_output [] 41 )) && ((level_0_output [] 42 ) &&
    // (level_0_output [] 43 ))) && (((level_0_output [] 44 ) &&
    // (level_0_output [] 45 )) && ((level_0_output [] 46 ) &&
    // (level_0_output [] 47 ))))) && (((((level_0_output [] 48 ) &&
    // (level_0_output [] 49 )) && ((level_0_output [] 50 ) &&
    // (level_0_output [] 51 ))) && (((level_0_output [] 52 ) &&
    // (level_0_output [] 53 )) && ((level_0_output [] 54 ) &&
    // (level_0_output [] 55 )))) && ((((level_0_output [] 56 ) &&
    // (level_0_output [] 57 )) && ((level_0_output [] 58 ) &&
    // (level_0_output [] 59 ))) && (((level_0_output [] 60 ) &&
    // (level_0_output [] 61 )) && ((level_0_output [] 62 ) &&
    // (level_0_output [] 63 ))))))) $buffering 1
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20732_c_macro_;
    // shifted := ( $mux left level_0_output reversed_output ) $buffering
    // 1// bits of buffering = 64. 
    fpunit_exec_exec__shifter_left_right_64_assign_stmt_20738_c_macro_;
    fpunit_exec_exec__shifter_left_right_64_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__shifter_left_right_64_series_block_stmt_20091_c_mutex_);
}
void
_fpunit_exec_exec_short_divide_24_core_(bit_vector * __pdivisorx1,
					bit_vector * __pdivisorx2,
					bit_vector * __pdivisorx3,
					bit_vector * __pP,
					bit_vector * __pA,
					bit_vector * __pP_shift,
					bit_vector * __pA_shift)
{
    MUTEX_DECL
	(fpunit_exec_exec__short_divide_24_core_series_block_stmt_14262_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__short_divide_24_core_series_block_stmt_14262_c_mutex_);
    fpunit_exec_exec__short_divide_24_core_inner_inarg_prep_macro__;
    // $volatile P_23_0 := ( $slice P 23 0 ) $buffering 1
    fpunit_exec_exec__short_divide_24_core_assign_stmt_14273_c_macro_;
    // $volatile A_29_28 := ( $slice A 29 28 ) $buffering 1
    fpunit_exec_exec__short_divide_24_core_assign_stmt_14277_c_macro_;
    // $volatile P_shift_start := (P_23_0 && A_29_28) $buffering 1
    fpunit_exec_exec__short_divide_24_core_assign_stmt_14282_c_macro_;
    // $volatile $call comparison_greater_equal_less_26 (P_shift_start
    // divisorx1 ) (cond_greater_than_B cond_less_than_B ) 
    fpunit_exec_exec__short_divide_24_core_call_stmt_14287_c_macro_;
    // $volatile $call comparison_greater_equal_less_26 (P_shift_start
    // divisorx2 ) (cond_greater_than_2B cond_lesser_than_2B ) 
    fpunit_exec_exec__short_divide_24_core_call_stmt_14292_c_macro_;
    // $volatile $call comparison_greater_equal_less_26 (P_shift_start
    // divisorx3 ) (cond_greater_than_3B cond_lesser_than_3B ) 
    fpunit_exec_exec__short_divide_24_core_call_stmt_14297_c_macro_;
    // $volatile condition_1 := cond_greater_than_2B $buffering 1
    fpunit_exec_exec__short_divide_24_core_assign_stmt_14300_c_macro_;
    // $volatile condition_0 := ((cond_greater_than_2B &
    // cond_greater_than_3B) | (cond_lesser_than_2B &
    // cond_greater_than_B)) $buffering 1
    fpunit_exec_exec__short_divide_24_core_assign_stmt_14309_c_macro_;
    // $volatile diff_operand := ( $mux cond_greater_than_3B divisorx3 (
    // $mux cond_greater_than_2B divisorx2 ( $mux cond_greater_than_B
    // divisorx1 ZERO_26 ) ) ) $buffering 1
    fpunit_exec_exec__short_divide_24_core_assign_stmt_14321_c_macro_;
    // $volatile A_shift := ((( $slice A 27 0 ) && condition_1) &&
    // condition_0) $buffering 1
    fpunit_exec_exec__short_divide_24_core_assign_stmt_14329_c_macro_;
    // $volatile P_shift := (P_shift_start - diff_operand) $buffering 1
    fpunit_exec_exec__short_divide_24_core_assign_stmt_14334_c_macro_;
    fpunit_exec_exec__short_divide_24_core_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__short_divide_24_core_series_block_stmt_14262_c_mutex_);
}
void
_fpunit_exec_exec_short_divide_24_pipelined_optimised_(bit_vector *
						       __pdividend,
						       bit_vector *
						       __pdivisor_24,
						       bit_vector * __pquo)
{
    MUTEX_DECL
	(fpunit_exec_exec__short_divide_24_pipelined_optimised_series_block_stmt_14336_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__short_divide_24_pipelined_optimised_series_block_stmt_14336_c_mutex_);
    fpunit_exec_exec__short_divide_24_pipelined_optimised_inner_inarg_prep_macro__;
    // divisorx2 := ($bitcast ($uint<26>) (divisor_24 && ZERO_1) )
    // $buffering 2// bits of buffering = 52. 
    fpunit_exec_exec__short_divide_24_pipelined_optimised_assign_stmt_14345_c_macro_;
    // divisorx1 := ($bitcast ($uint<26>) divisor_24 ) $buffering 2// bits 
    // of buffering = 52. 
    fpunit_exec_exec__short_divide_24_pipelined_optimised_assign_stmt_14349_c_macro_;
    // divisorx3 := (($bitcast ($uint<26>) (divisor_24 && ZERO_1) ) +
    // ($bitcast ($uint<26>) divisor_24 )) $buffering 2// bits of
    // buffering = 52. 
    fpunit_exec_exec__short_divide_24_pipelined_optimised_assign_stmt_14358_c_macro_;
    fpunit_exec_exec__short_divide_24_pipelined_optimised_branch_block_stmt_14359_c_export_decl_macro_;
    {
	{
	    // do-while: file ./.Aa//linked.opt.aa, line 3220
	    uint8_t         do_while_entry_flag;
	    do_while_entry_flag = 1;
	    uint8_t         do_while_loopback_flag;
	    do_while_loopback_flag = 0;
	    while (1) {
		// merge file ./.Aa//linked.opt.aa, line 3222
		fpunit_exec_exec__short_divide_24_pipelined_optimised_merge_stmt_14361_c_preamble_macro_;
		// $phi N := ($bitcast ($uint<6>) 0 ) $on $entry NN_1 $on
		// $loopback 
		// type of target is $uint<6>
		fpunit_exec_exec__short_divide_24_pipelined_optimised_phi_stmt_14362_c_macro_;
		// $phi P := (ZERO_4 && ( $slice dividend 23 2 ) ) $on
		// $entry next_P_1 $on $loopback 
		// type of target is $uint<26>
		fpunit_exec_exec__short_divide_24_pipelined_optimised_phi_stmt_14367_c_macro_;
		// $phi A := (( $slice dividend 1 0 ) && ZERO_28) $on
		// $entry next_A_1 $on $loopback 
		// type of target is $uint<30>
		fpunit_exec_exec__short_divide_24_pipelined_optimised_phi_stmt_14374_c_macro_;
		fpunit_exec_exec__short_divide_24_pipelined_optimised_merge_stmt_14361_c_postamble_macro_;
		// $volatile $call short_divide_24_core (divisorx1
		// divisorx2 divisorx3 P A ) (P_shift_0 A_shift_0 ) 
		fpunit_exec_exec__short_divide_24_pipelined_optimised_call_stmt_14389_c_macro_;
		// $volatile next_P_0 := P_shift_0 $buffering 1
		fpunit_exec_exec__short_divide_24_pipelined_optimised_assign_stmt_14392_c_macro_;
		// $volatile next_A_0 := A_shift_0 $buffering 1
		fpunit_exec_exec__short_divide_24_pipelined_optimised_assign_stmt_14395_c_macro_;
		// $volatile NN_0 := (N + 1 ) $buffering 1
		fpunit_exec_exec__short_divide_24_pipelined_optimised_assign_stmt_14400_c_macro_;
		// $volatile $call short_divide_24_core (divisorx1
		// divisorx2 divisorx3 next_P_0 next_A_0 ) (P_shift_1
		// A_shift_1 ) 
		fpunit_exec_exec__short_divide_24_pipelined_optimised_call_stmt_14408_c_macro_;
		// $volatile next_P_1 := P_shift_1 $buffering 1
		fpunit_exec_exec__short_divide_24_pipelined_optimised_assign_stmt_14411_c_macro_;
		// $volatile next_A_1 := A_shift_1 $buffering 1
		fpunit_exec_exec__short_divide_24_pipelined_optimised_assign_stmt_14414_c_macro_;
		// $volatile NN_1 := (NN_0 + 1 ) $buffering 1
		fpunit_exec_exec__short_divide_24_pipelined_optimised_assign_stmt_14419_c_macro_;
		// $volatile continue_flag := (N <= 12 ) $buffering 1
		fpunit_exec_exec__short_divide_24_pipelined_optimised_assign_stmt_14424_c_macro_;
		do_while_entry_flag = 0;
		do_while_loopback_flag = 1;
		if (has_undefined_bit(&continue_flag)) {
		    fprintf(stderr,
			    "Error: variable continue_flag has undefined value (%s) at test point.\n",
			    to_string(&continue_flag));
		    assert(0);
		}

		if (!bit_vector_to_uint64(0, &continue_flag))
		    break;
	    }
	}
	fpunit_exec_exec__short_divide_24_pipelined_optimised_branch_block_stmt_14359_c_export_apply_macro_;
    }
    // quo := ( $slice A 28 0 ) $buffering 2// bits of buffering = 58. 
    fpunit_exec_exec__short_divide_24_pipelined_optimised_assign_stmt_14431_c_macro_;
    fpunit_exec_exec__short_divide_24_pipelined_optimised_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__short_divide_24_pipelined_optimised_series_block_stmt_14336_c_mutex_);
}
void
_fpunit_exec_exec_short_divide_53_core_(bit_vector * __pdivisorx1,
					bit_vector * __pdivisorx2,
					bit_vector * __pdivisorx3,
					bit_vector * __pP,
					bit_vector * __pA,
					bit_vector * __pnext_P,
					bit_vector * __pnext_A)
{
    MUTEX_DECL
	(fpunit_exec_exec__short_divide_53_core_series_block_stmt_15339_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__short_divide_53_core_series_block_stmt_15339_c_mutex_);
    fpunit_exec_exec__short_divide_53_core_inner_inarg_prep_macro__;
    // P_52_0 := ( $slice P 52 0 ) $buffering 1
    fpunit_exec_exec__short_divide_53_core_assign_stmt_15350_c_macro_;
    // A_105_104 := ( $slice A 105 104 ) $buffering 1
    fpunit_exec_exec__short_divide_53_core_assign_stmt_15354_c_macro_;
    // P_shift_start := (P_52_0 && A_105_104) $buffering 1
    fpunit_exec_exec__short_divide_53_core_assign_stmt_15359_c_macro_;
    // $volatile $call comparison_greater_equal_less_55 (P_shift_start
    // divisorx1 ) (cond_greater_than_B cond_less_than_B ) 
    fpunit_exec_exec__short_divide_53_core_call_stmt_15364_c_macro_;
    // $volatile $call comparison_greater_equal_less_55 (P_shift_start
    // divisorx2 ) (cond_greater_than_2B cond_lesser_than_2B ) 
    fpunit_exec_exec__short_divide_53_core_call_stmt_15369_c_macro_;
    // $volatile $call comparison_greater_equal_less_55 (P_shift_start
    // divisorx3 ) (cond_greater_than_3B cond_lesser_than_3B ) 
    fpunit_exec_exec__short_divide_53_core_call_stmt_15374_c_macro_;
    // condition_1 := cond_greater_than_2B $buffering 1
    fpunit_exec_exec__short_divide_53_core_assign_stmt_15377_c_macro_;
    // condition_0 := ((cond_greater_than_2B & cond_greater_than_3B) |
    // (cond_lesser_than_2B & cond_greater_than_B)) $buffering 1
    fpunit_exec_exec__short_divide_53_core_assign_stmt_15386_c_macro_;
    // diff_operand := ( $mux cond_greater_than_3B divisorx3 ( $mux
    // cond_greater_than_2B divisorx2 ( $mux cond_greater_than_B divisorx1 
    // ZERO_55 ) ) ) $buffering 1
    fpunit_exec_exec__short_divide_53_core_assign_stmt_15398_c_macro_;
    // next_P := (P_shift_start - diff_operand) $buffering 1
    fpunit_exec_exec__short_divide_53_core_assign_stmt_15403_c_macro_;
    // next_A := ((( $slice A 103 0 ) && condition_1) && condition_0)
    // $buffering 1
    fpunit_exec_exec__short_divide_53_core_assign_stmt_15411_c_macro_;
    fpunit_exec_exec__short_divide_53_core_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__short_divide_53_core_series_block_stmt_15339_c_mutex_);
}
void
_fpunit_exec_exec_short_divide_53_pipelined_optimised_(bit_vector *
						       __pdividend,
						       bit_vector *
						       __pdivisor,
						       bit_vector * __pquo)
{
    MUTEX_DECL
	(fpunit_exec_exec__short_divide_53_pipelined_optimised_series_block_stmt_15413_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__short_divide_53_pipelined_optimised_series_block_stmt_15413_c_mutex_);
    fpunit_exec_exec__short_divide_53_pipelined_optimised_inner_inarg_prep_macro__;
    // divisorx2 := ($bitcast ($uint<55>) (divisor && ZERO_1) ) $buffering 
    // 2// bits of buffering = 110. 
    fpunit_exec_exec__short_divide_53_pipelined_optimised_assign_stmt_15422_c_macro_;
    // divisorx1 := ($bitcast ($uint<55>) divisor ) $buffering 2// bits of 
    // buffering = 110. 
    fpunit_exec_exec__short_divide_53_pipelined_optimised_assign_stmt_15426_c_macro_;
    // divisorx3 := (($bitcast ($uint<55>) divisor ) + ($bitcast
    // ($uint<55>) (divisor && ZERO_1) )) $buffering 2// bits of buffering 
    // = 110. 
    fpunit_exec_exec__short_divide_53_pipelined_optimised_assign_stmt_15435_c_macro_;
    fpunit_exec_exec__short_divide_53_pipelined_optimised_branch_block_stmt_15436_c_export_decl_macro_;
    {
	{
	    // do-while: file ./.Aa//linked.opt.aa, line 3474
	    uint8_t         do_while_entry_flag;
	    do_while_entry_flag = 1;
	    uint8_t         do_while_loopback_flag;
	    do_while_loopback_flag = 0;
	    while (1) {
		// merge file ./.Aa//linked.opt.aa, line 3476
		fpunit_exec_exec__short_divide_53_pipelined_optimised_merge_stmt_15438_c_preamble_macro_;
		// $phi N := ($bitcast ($uint<8>) 0 ) $on $entry NN_1 $on
		// $loopback 
		// type of target is $uint<8>
		fpunit_exec_exec__short_divide_53_pipelined_optimised_phi_stmt_15439_c_macro_;
		// $phi P := (ZERO_4 && ( $slice dividend 52 2 ) ) $on
		// $entry next_P_1 $on $loopback 
		// type of target is $uint<55>
		fpunit_exec_exec__short_divide_53_pipelined_optimised_phi_stmt_15444_c_macro_;
		// $phi A := (( $slice dividend 1 0 ) && ZERO_104) $on
		// $entry next_A_1 $on $loopback 
		// type of target is $uint<106>
		fpunit_exec_exec__short_divide_53_pipelined_optimised_phi_stmt_15451_c_macro_;
		fpunit_exec_exec__short_divide_53_pipelined_optimised_merge_stmt_15438_c_postamble_macro_;
		// $volatile $call short_divide_53_core (divisorx1
		// divisorx2 divisorx3 P A ) (next_P_0_v next_A_0_v ) 
		fpunit_exec_exec__short_divide_53_pipelined_optimised_call_stmt_15466_c_macro_;
		// $volatile NN_0 := (N + 1 ) $buffering 1
		fpunit_exec_exec__short_divide_53_pipelined_optimised_assign_stmt_15471_c_macro_;
		// $volatile next_P_0 := next_P_0_v $buffering 1
		fpunit_exec_exec__short_divide_53_pipelined_optimised_assign_stmt_15474_c_macro_;
		// $volatile next_A_0 := next_A_0_v $buffering 1
		fpunit_exec_exec__short_divide_53_pipelined_optimised_assign_stmt_15477_c_macro_;
		// $volatile $call short_divide_53_core (divisorx1
		// divisorx2 divisorx3 next_P_0 next_A_0 ) (next_P_1_v
		// next_A_1_v ) 
		fpunit_exec_exec__short_divide_53_pipelined_optimised_call_stmt_15485_c_macro_;
		// $volatile NN_1 := (NN_0 + 1 ) $buffering 1
		fpunit_exec_exec__short_divide_53_pipelined_optimised_assign_stmt_15490_c_macro_;
		// $volatile next_P_1 := next_P_1_v $buffering 1
		fpunit_exec_exec__short_divide_53_pipelined_optimised_assign_stmt_15493_c_macro_;
		// $volatile next_A_1 := next_A_1_v $buffering 1
		fpunit_exec_exec__short_divide_53_pipelined_optimised_assign_stmt_15496_c_macro_;
		// $volatile continue_flag := (N <= 26 ) $buffering 1
		fpunit_exec_exec__short_divide_53_pipelined_optimised_assign_stmt_15501_c_macro_;
		do_while_entry_flag = 0;
		do_while_loopback_flag = 1;
		if (has_undefined_bit(&continue_flag)) {
		    fprintf(stderr,
			    "Error: variable continue_flag has undefined value (%s) at test point.\n",
			    to_string(&continue_flag));
		    assert(0);
		}

		if (!bit_vector_to_uint64(0, &continue_flag))
		    break;
	    }
	}
	fpunit_exec_exec__short_divide_53_pipelined_optimised_branch_block_stmt_15436_c_export_apply_macro_;
    }
    // quo := ( $slice A 58 1 ) $buffering 2// bits of buffering = 116. 
    fpunit_exec_exec__short_divide_53_pipelined_optimised_assign_stmt_15508_c_macro_;
    fpunit_exec_exec__short_divide_53_pipelined_optimised_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__short_divide_53_pipelined_optimised_series_block_stmt_15413_c_mutex_);
}
void
_fpunit_exec_exec_short_sqrt_32_(bit_vector * __pX, bit_vector * __psticky,
				 bit_vector * __proot_X)
{
    MUTEX_DECL
	(fpunit_exec_exec__short_sqrt_32_series_block_stmt_15000_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__short_sqrt_32_series_block_stmt_15000_c_mutex_);
    fpunit_exec_exec__short_sqrt_32_inner_inarg_prep_macro__;
    // $report (fpdiv32bitwise X__ X X )
    fpunit_exec_exec__short_sqrt_32_stmt_15005_c_macro_;
    // $volatile start_index := 31 $buffering 1
    fpunit_exec_exec__short_sqrt_32_assign_stmt_15008_c_macro_;
    // $report (fpdiv32bitwise start_index__ start_index start_index )
    fpunit_exec_exec__short_sqrt_32_stmt_15010_c_macro_;
    // $volatile start_root_estimate := _h80000000 $buffering 1
    fpunit_exec_exec__short_sqrt_32_assign_stmt_15013_c_macro_;
    // $report (fpdiv32bitwise start_root_estimate__ start_root_estimate
    // start_root_estimate )
    fpunit_exec_exec__short_sqrt_32_stmt_15015_c_macro_;
    // $volatile start_residue := (((( $slice X 31 30 ) - 1 ) && ( $slice
    // X 29 0 ) ) && ZERO_2) $buffering 1
    fpunit_exec_exec__short_sqrt_32_assign_stmt_15026_c_macro_;
    // $report (fpdiv32bitwise start_residue__ start_residue start_residue 
    // )
    fpunit_exec_exec__short_sqrt_32_stmt_15028_c_macro_;
    // $volatile start_shifted_index_word := _h80000000 $buffering 1
    fpunit_exec_exec__short_sqrt_32_assign_stmt_15031_c_macro_;
    // $report (fpdiv32bitwise start_shifted_index_word__
    // start_shifted_index_word start_shifted_index_word )
    fpunit_exec_exec__short_sqrt_32_stmt_15033_c_macro_;
    fpunit_exec_exec__short_sqrt_32_branch_block_stmt_15034_c_export_decl_macro_;
    {
	{
	    // do-while: file ./.Aa//linked.opt.aa, line 3358
	    uint8_t         do_while_entry_flag;
	    do_while_entry_flag = 1;
	    uint8_t         do_while_loopback_flag;
	    do_while_loopback_flag = 0;
	    while (1) {
		// merge file ./.Aa//linked.opt.aa, line 3360
		fpunit_exec_exec__short_sqrt_32_merge_stmt_15036_c_preamble_macro_;
		// $phi last_root_estimate := start_root_estimate $on
		// $entry next_root_estimate $on $loopback 
		// type of target is $uint<32>
		fpunit_exec_exec__short_sqrt_32_phi_stmt_15037_c_macro_;
		// $phi last_residue := start_residue $on $entry
		// next_last_residue $on $loopback 
		// type of target is $uint<34>
		fpunit_exec_exec__short_sqrt_32_phi_stmt_15041_c_macro_;
		// $phi last_shifted_index_word :=
		// start_shifted_index_word $on $entry
		// next_last_shifted_index_word $on $loopback 
		// type of target is $uint<32>
		fpunit_exec_exec__short_sqrt_32_phi_stmt_15045_c_macro_;
		// $phi last_index := start_index $on $entry
		// next_last_index $on $loopback 
		// type of target is $uint<8>
		fpunit_exec_exec__short_sqrt_32_phi_stmt_15049_c_macro_;
		fpunit_exec_exec__short_sqrt_32_merge_stmt_15036_c_postamble_macro_;
		// $report (fpdiv32bitwise short_sqrt_32_status last_index 
		// last_index last_root_estimate last_root_estimate
		// last_residue last_residue last_shifted_index_word
		// last_shifted_index_word )
		fpunit_exec_exec__short_sqrt_32_stmt_15058_c_macro_;
		// $volatile next_last_index_0 := ( $mux (last_index > 0 ) 
		// (last_index - 1 ) 0 ) $buffering 1
		fpunit_exec_exec__short_sqrt_32_assign_stmt_15068_c_macro_;
		// $volatile next_last_index_1 := ( $mux (last_index > 1 ) 
		// (last_index - 2 ) 0 ) $buffering 1
		fpunit_exec_exec__short_sqrt_32_assign_stmt_15078_c_macro_;
		// $volatile next_last_index := ( $mux (last_index > 2 )
		// (last_index - 3 ) 0 ) $buffering 1
		fpunit_exec_exec__short_sqrt_32_assign_stmt_15088_c_macro_;
		// $volatile continue_flag := ((next_last_index > 0 ) &
		// (last_residue != 0 )) $buffering 1
		fpunit_exec_exec__short_sqrt_32_assign_stmt_15097_c_macro_;
		// $volatile $call short_sqrt_32_core (last_root_estimate
		// last_residue last_shifted_index_word last_index )
		// (next_root_estimate_0 next_last_residue_0
		// next_last_shifted_index_word_0 sticky_flag_0 ) 
		fpunit_exec_exec__short_sqrt_32_call_stmt_15106_c_macro_;
		// $volatile $call short_sqrt_32_core
		// (next_root_estimate_0 next_last_residue_0
		// next_last_shifted_index_word_0 next_last_index_0 )
		// (next_root_estimate_1 next_last_residue_1
		// next_last_shifted_index_word_1 sticky_flag_1 ) 
		fpunit_exec_exec__short_sqrt_32_call_stmt_15115_c_macro_;
		// $volatile $call short_sqrt_32_core
		// (next_root_estimate_1 next_last_residue_1
		// next_last_shifted_index_word_1 next_last_index_1 )
		// (next_root_estimate next_last_residue
		// next_last_shifted_index_word sticky_flag ) 
		fpunit_exec_exec__short_sqrt_32_call_stmt_15124_c_macro_;
		do_while_entry_flag = 0;
		do_while_loopback_flag = 1;
		if (has_undefined_bit(&continue_flag)) {
		    fprintf(stderr,
			    "Error: variable continue_flag has undefined value (%s) at test point.\n",
			    to_string(&continue_flag));
		    assert(0);
		}

		if (!bit_vector_to_uint64(0, &continue_flag))
		    break;
	    }
	}
	fpunit_exec_exec__short_sqrt_32_branch_block_stmt_15034_c_export_apply_macro_;
    }
    // sticky := sticky_out $buffering 2// bits of buffering = 2. 
    fpunit_exec_exec__short_sqrt_32_assign_stmt_15130_c_macro_;
    // root_X := root_estimate $buffering 2// bits of buffering = 64. 
    fpunit_exec_exec__short_sqrt_32_assign_stmt_15133_c_macro_;
    fpunit_exec_exec__short_sqrt_32_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__short_sqrt_32_series_block_stmt_15000_c_mutex_);
}
void
_fpunit_exec_exec_short_sqrt_32_core_(bit_vector * __plast_root_estimate,
				      bit_vector * __plast_residue,
				      bit_vector *
				      __plast_shifted_index_word,
				      bit_vector * __plast_index,
				      bit_vector * __pnext_root_estimate,
				      bit_vector * __pnext_residue,
				      bit_vector *
				      __pnext_last_shifted_index_word,
				      bit_vector * __psticky_flag)
{
    MUTEX_DECL
	(fpunit_exec_exec__short_sqrt_32_core_series_block_stmt_14932_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__short_sqrt_32_core_series_block_stmt_14932_c_mutex_);
    fpunit_exec_exec__short_sqrt_32_core_inner_inarg_prep_macro__;
    // current_index := ( $mux (last_index > 0 ) (last_index - 1 ) 0 )
    // $buffering 1
    fpunit_exec_exec__short_sqrt_32_core_assign_stmt_14950_c_macro_;
    // $report (fpdiv32bitwise short_sqrt_32_core_in_args
    // last_root_estimate last_root_estimate last_residue last_residue
    // last_shifted_index_word last_shifted_index_word last_index
    // last_index current_index current_index )
    fpunit_exec_exec__short_sqrt_32_core_stmt_14956_c_macro_;
    // $volatile $call make_new_estimate_32 (last_root_estimate
    // last_residue last_shifted_index_word ) (current_root_estimate
    // current_residue current_residue_sign ) 
    fpunit_exec_exec__short_sqrt_32_core_call_stmt_14963_c_macro_;
    // next_root_estimate := ( $mux ( ~ current_residue_sign )
    // current_root_estimate last_root_estimate ) $buffering 1
    fpunit_exec_exec__short_sqrt_32_core_assign_stmt_14970_c_macro_;
    // next_residue_before_shift := ( $mux ( ~ current_residue_sign )
    // current_residue last_residue ) $buffering 1
    fpunit_exec_exec__short_sqrt_32_core_assign_stmt_14977_c_macro_;
    // next_residue := (( $slice next_residue_before_shift 32 0 ) &&
    // ZERO_1) $buffering 1
    fpunit_exec_exec__short_sqrt_32_core_assign_stmt_14983_c_macro_;
    // sticky_flag := (next_residue != 0 ) $buffering 1
    fpunit_exec_exec__short_sqrt_32_core_assign_stmt_14988_c_macro_;
    // next_last_shifted_index_word := (ZERO_1 && ( $slice
    // last_shifted_index_word 31 1 ) ) $buffering 1
    fpunit_exec_exec__short_sqrt_32_core_assign_stmt_14994_c_macro_;
    // $report (fpdiv32bitwise short_sqrt_32_core_out_args next_residue
    // next_residue next_root_estimate next_root_estimate
    // next_last_shifted_index_word next_last_shifted_index_word )
    fpunit_exec_exec__short_sqrt_32_core_stmt_14998_c_macro_;
    fpunit_exec_exec__short_sqrt_32_core_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__short_sqrt_32_core_series_block_stmt_14932_c_mutex_);
}
void
_fpunit_exec_exec_short_sqrt_56_(bit_vector * __pX, bit_vector * __psticky,
				 bit_vector * __proot_X)
{
    MUTEX_DECL
	(fpunit_exec_exec__short_sqrt_56_series_block_stmt_16078_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__short_sqrt_56_series_block_stmt_16078_c_mutex_);
    fpunit_exec_exec__short_sqrt_56_inner_inarg_prep_macro__;
    // $report (fpdiv64bitwise X__ X X )
    fpunit_exec_exec__short_sqrt_56_stmt_16083_c_macro_;
    // $volatile start_index := 55 $buffering 1
    fpunit_exec_exec__short_sqrt_56_assign_stmt_16086_c_macro_;
    // $report (fpdiv64bitwise start_index__ start_index start_index )
    fpunit_exec_exec__short_sqrt_56_stmt_16088_c_macro_;
    // $volatile start_root_estimate := _h80000000000000 $buffering 1
    fpunit_exec_exec__short_sqrt_56_assign_stmt_16091_c_macro_;
    // $report (fpdiv64bitwise start_root_estimate__ start_root_estimate
    // start_root_estimate )
    fpunit_exec_exec__short_sqrt_56_stmt_16093_c_macro_;
    // $volatile start_residue := (((( $slice X 55 54 ) - 1 ) && ( $slice
    // X 53 0 ) ) && ZERO_2) $buffering 1
    fpunit_exec_exec__short_sqrt_56_assign_stmt_16104_c_macro_;
    // $report (fpdiv64bitwise start_residue__ start_residue start_residue 
    // )
    fpunit_exec_exec__short_sqrt_56_stmt_16106_c_macro_;
    // $volatile start_shifted_index_word := _h80000000000000 $buffering 1
    fpunit_exec_exec__short_sqrt_56_assign_stmt_16109_c_macro_;
    // $report (fpdiv64bitwise start_shifted_index_word__
    // start_shifted_index_word start_shifted_index_word )
    fpunit_exec_exec__short_sqrt_56_stmt_16111_c_macro_;
    fpunit_exec_exec__short_sqrt_56_branch_block_stmt_16112_c_export_decl_macro_;
    {
	{
	    // do-while: file ./.Aa//linked.opt.aa, line 3612
	    uint8_t         do_while_entry_flag;
	    do_while_entry_flag = 1;
	    uint8_t         do_while_loopback_flag;
	    do_while_loopback_flag = 0;
	    while (1) {
		// merge file ./.Aa//linked.opt.aa, line 3614
		fpunit_exec_exec__short_sqrt_56_merge_stmt_16114_c_preamble_macro_;
		// $phi last_root_estimate := start_root_estimate $on
		// $entry next_root_estimate $on $loopback 
		// type of target is $uint<56>
		fpunit_exec_exec__short_sqrt_56_phi_stmt_16115_c_macro_;
		// $phi last_residue := start_residue $on $entry
		// next_last_residue $on $loopback 
		// type of target is $uint<58>
		fpunit_exec_exec__short_sqrt_56_phi_stmt_16119_c_macro_;
		// $phi last_shifted_index_word :=
		// start_shifted_index_word $on $entry
		// next_last_shifted_index_word $on $loopback 
		// type of target is $uint<56>
		fpunit_exec_exec__short_sqrt_56_phi_stmt_16123_c_macro_;
		// $phi last_index := start_index $on $entry
		// next_last_index $on $loopback 
		// type of target is $uint<8>
		fpunit_exec_exec__short_sqrt_56_phi_stmt_16127_c_macro_;
		fpunit_exec_exec__short_sqrt_56_merge_stmt_16114_c_postamble_macro_;
		// $report (fpdiv64bitwise short_sqrt_64_status last_index 
		// last_index last_root_estimate last_root_estimate
		// last_residue last_residue last_shifted_index_word
		// last_shifted_index_word )
		fpunit_exec_exec__short_sqrt_56_stmt_16136_c_macro_;
		// $volatile next_last_index_0 := ( $mux (last_index > 0 ) 
		// (last_index - 1 ) 0 ) $buffering 1
		fpunit_exec_exec__short_sqrt_56_assign_stmt_16146_c_macro_;
		// $volatile next_last_index_1 := ( $mux (last_index > 1 ) 
		// (last_index - 2 ) 0 ) $buffering 1
		fpunit_exec_exec__short_sqrt_56_assign_stmt_16156_c_macro_;
		// $volatile next_last_index := ( $mux (last_index > 2 )
		// (last_index - 3 ) 0 ) $buffering 1
		fpunit_exec_exec__short_sqrt_56_assign_stmt_16166_c_macro_;
		// $volatile continue_flag := ((next_last_index > 0 ) &
		// (last_residue != 0 )) $buffering 1
		fpunit_exec_exec__short_sqrt_56_assign_stmt_16175_c_macro_;
		// $volatile $call short_sqrt_56_core (last_root_estimate
		// last_residue last_shifted_index_word last_index )
		// (next_root_estimate_0 next_last_residue_0
		// next_last_shifted_index_word_0 sticky_flag_0 ) 
		fpunit_exec_exec__short_sqrt_56_call_stmt_16184_c_macro_;
		// $volatile $call short_sqrt_56_core
		// (next_root_estimate_0 next_last_residue_0
		// next_last_shifted_index_word_0 next_last_index_0 )
		// (next_root_estimate_1 next_last_residue_1
		// next_last_shifted_index_word_1 sticky_flag_1 ) 
		fpunit_exec_exec__short_sqrt_56_call_stmt_16193_c_macro_;
		// $volatile $call short_sqrt_56_core
		// (next_root_estimate_1 next_last_residue_1
		// next_last_shifted_index_word_1 next_last_index_1 )
		// (next_root_estimate next_last_residue
		// next_last_shifted_index_word sticky_flag ) 
		fpunit_exec_exec__short_sqrt_56_call_stmt_16202_c_macro_;
		do_while_entry_flag = 0;
		do_while_loopback_flag = 1;
		if (has_undefined_bit(&continue_flag)) {
		    fprintf(stderr,
			    "Error: variable continue_flag has undefined value (%s) at test point.\n",
			    to_string(&continue_flag));
		    assert(0);
		}

		if (!bit_vector_to_uint64(0, &continue_flag))
		    break;
	    }
	}
	fpunit_exec_exec__short_sqrt_56_branch_block_stmt_16112_c_export_apply_macro_;
    }
    // sticky := sticky_out $buffering 2// bits of buffering = 2. 
    fpunit_exec_exec__short_sqrt_56_assign_stmt_16208_c_macro_;
    // root_X := root_estimate $buffering 2// bits of buffering = 112. 
    fpunit_exec_exec__short_sqrt_56_assign_stmt_16211_c_macro_;
    fpunit_exec_exec__short_sqrt_56_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__short_sqrt_56_series_block_stmt_16078_c_mutex_);
}
void
_fpunit_exec_exec_short_sqrt_56_core_(bit_vector * __plast_root_estimate,
				      bit_vector * __plast_residue,
				      bit_vector *
				      __plast_shifted_index_word,
				      bit_vector * __plast_index,
				      bit_vector * __pnext_root_estimate,
				      bit_vector * __pnext_residue,
				      bit_vector *
				      __pnext_last_shifted_index_word,
				      bit_vector * __psticky_flag)
{
    MUTEX_DECL
	(fpunit_exec_exec__short_sqrt_56_core_series_block_stmt_16009_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__short_sqrt_56_core_series_block_stmt_16009_c_mutex_);
    fpunit_exec_exec__short_sqrt_56_core_inner_inarg_prep_macro__;
    // current_index := ( $mux (last_index > 0 ) (last_index - 1 ) 0 )
    // $buffering 1
    fpunit_exec_exec__short_sqrt_56_core_assign_stmt_16027_c_macro_;
    // $report (fpdiv64bitwise short_sqrt_56_core_in_args
    // last_root_estimate last_root_estimate last_residue last_residue
    // last_shifted_index_word last_shifted_index_word last_index
    // last_index current_index current_index )
    fpunit_exec_exec__short_sqrt_56_core_stmt_16033_c_macro_;
    // $volatile $call make_new_estimate_56 (last_root_estimate
    // last_residue last_shifted_index_word ) (current_root_estimate
    // current_residue current_residue_sign ) 
    fpunit_exec_exec__short_sqrt_56_core_call_stmt_16040_c_macro_;
    // next_root_estimate := ( $mux ( ~ current_residue_sign )
    // current_root_estimate last_root_estimate ) $buffering 1
    fpunit_exec_exec__short_sqrt_56_core_assign_stmt_16047_c_macro_;
    // next_residue_before_shift := ( $mux ( ~ current_residue_sign )
    // current_residue last_residue ) $buffering 1
    fpunit_exec_exec__short_sqrt_56_core_assign_stmt_16054_c_macro_;
    // next_residue := (( $slice next_residue_before_shift 56 0 ) &&
    // ZERO_1) $buffering 1
    fpunit_exec_exec__short_sqrt_56_core_assign_stmt_16061_c_macro_;
    // sticky_flag := (next_residue != 0 ) $buffering 1
    fpunit_exec_exec__short_sqrt_56_core_assign_stmt_16066_c_macro_;
    // next_last_shifted_index_word := (ZERO_1 && ( $slice
    // last_shifted_index_word 55 1 ) ) $buffering 1
    fpunit_exec_exec__short_sqrt_56_core_assign_stmt_16072_c_macro_;
    // $report (fpdiv32bitwise short_sqrt_56_core_out_args next_residue
    // next_residue next_root_estimate next_root_estimate
    // next_last_shifted_index_word next_last_shifted_index_word )
    fpunit_exec_exec__short_sqrt_56_core_stmt_16076_c_macro_;
    fpunit_exec_exec__short_sqrt_56_core_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__short_sqrt_56_core_series_block_stmt_16009_c_mutex_);
}
void
_fpunit_exec_exec_signature_8_(bit_vector * __pA, bit_vector * __pAS)
{
    MUTEX_DECL
	(fpunit_exec_exec__signature_8_series_block_stmt_20740_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__signature_8_series_block_stmt_20740_c_mutex_);
    fpunit_exec_exec__signature_8_inner_inarg_prep_macro__;
    // AS := ((( $slice A 7 0 ) ^ ( $slice A 15 8 ) ) ^ (( $slice A 23 16
    // ) ^ ( $slice A 31 24 ) )) $buffering 1
    fpunit_exec_exec__signature_8_assign_stmt_20755_c_macro_;
    fpunit_exec_exec__signature_8_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__signature_8_series_block_stmt_20740_c_mutex_);
}
void
fpunit_exec_exec_signature_8(uint32_t A, uint8_t * AS)
{
    fpunit_exec_exec__signature_8_outer_arg_decl_macro__;
    _fpunit_exec_exec_signature_8_(&__A, &__AS);
    fpunit_exec_exec__signature_8_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_splitFp16_(bit_vector * __pua, bit_vector * __psign,
			     bit_vector * __pexponent,
			     bit_vector * __pmantissa)
{
    MUTEX_DECL
	(fpunit_exec_exec__splitFp16_series_block_stmt_3709_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__splitFp16_series_block_stmt_3709_c_mutex_);
    fpunit_exec_exec__splitFp16_inner_inarg_prep_macro__;
    // sign := (ua [] 15 ) $buffering 1
    fpunit_exec_exec__splitFp16_assign_stmt_3718_c_macro_;
    // exponent := ( $slice ua 14 10 ) $buffering 1
    fpunit_exec_exec__splitFp16_assign_stmt_3722_c_macro_;
    // mantissa := ( $slice ua 9 0 ) $buffering 1
    fpunit_exec_exec__splitFp16_assign_stmt_3726_c_macro_;
    fpunit_exec_exec__splitFp16_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__splitFp16_series_block_stmt_3709_c_mutex_);
}
void
_fpunit_exec_exec_twos_complement_16_(bit_vector * __pA, bit_vector * __pB)
{
    MUTEX_DECL
	(fpunit_exec_exec__twos_complement_16_series_block_stmt_9627_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__twos_complement_16_series_block_stmt_9627_c_mutex_);
    fpunit_exec_exec__twos_complement_16_inner_inarg_prep_macro__;
    // cA := ( ~ A ) $buffering 1
    fpunit_exec_exec__twos_complement_16_assign_stmt_9633_c_macro_;
    // $volatile $call increment_16 (cA ) (B ) 
    fpunit_exec_exec__twos_complement_16_call_stmt_9636_c_macro_;
    fpunit_exec_exec__twos_complement_16_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__twos_complement_16_series_block_stmt_9627_c_mutex_);
}
void
fpunit_exec_exec_twos_complement_16(uint16_t A, uint16_t * B)
{
    fpunit_exec_exec__twos_complement_16_outer_arg_decl_macro__;
    _fpunit_exec_exec_twos_complement_16_(&__A, &__B);
    fpunit_exec_exec__twos_complement_16_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_twos_complement_32_(bit_vector * __pA, bit_vector * __pB)
{
    MUTEX_DECL
	(fpunit_exec_exec__twos_complement_32_series_block_stmt_20757_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__twos_complement_32_series_block_stmt_20757_c_mutex_);
    fpunit_exec_exec__twos_complement_32_inner_inarg_prep_macro__;
    // cA := ( ~ A ) $buffering 1
    fpunit_exec_exec__twos_complement_32_assign_stmt_20763_c_macro_;
    // $volatile $call increment_32 (cA ) (B ) 
    fpunit_exec_exec__twos_complement_32_call_stmt_20766_c_macro_;
    fpunit_exec_exec__twos_complement_32_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__twos_complement_32_series_block_stmt_20757_c_mutex_);
}
void
fpunit_exec_exec_twos_complement_32(uint32_t A, uint32_t * B)
{
    fpunit_exec_exec__twos_complement_32_outer_arg_decl_macro__;
    _fpunit_exec_exec_twos_complement_32_(&__A, &__B);
    fpunit_exec_exec__twos_complement_32_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_twos_complement_64_(bit_vector * __pA, bit_vector * __pB)
{
    MUTEX_DECL
	(fpunit_exec_exec__twos_complement_64_series_block_stmt_20768_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__twos_complement_64_series_block_stmt_20768_c_mutex_);
    fpunit_exec_exec__twos_complement_64_inner_inarg_prep_macro__;
    // cA := ( ~ A ) $buffering 1
    fpunit_exec_exec__twos_complement_64_assign_stmt_20774_c_macro_;
    // $volatile $call increment_64 (cA ) (B ) 
    fpunit_exec_exec__twos_complement_64_call_stmt_20777_c_macro_;
    fpunit_exec_exec__twos_complement_64_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__twos_complement_64_series_block_stmt_20768_c_mutex_);
}
void
fpunit_exec_exec_twos_complement_64(uint64_t A, uint64_t * B)
{
    fpunit_exec_exec__twos_complement_64_outer_arg_decl_macro__;
    _fpunit_exec_exec_twos_complement_64_(&__A, &__B);
    fpunit_exec_exec__twos_complement_64_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_u32_sll_(bit_vector * __pX, bit_vector * __pS,
			   bit_vector * __pY)
{
    MUTEX_DECL(fpunit_exec_exec__u32_sll_series_block_stmt_20779_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__u32_sll_series_block_stmt_20779_c_mutex_);
    fpunit_exec_exec__u32_sll_inner_inarg_prep_macro__;
    // X0 := ( $mux (S [] 0 ) (( $slice X 30 0 ) && ZERO_1) X ) $buffering 
    // 1
    fpunit_exec_exec__u32_sll_assign_stmt_20793_c_macro_;
    // X1 := ( $mux (S [] 1 ) (( $slice X0 29 0 ) && ZERO_2) X0 )
    // $buffering 1
    fpunit_exec_exec__u32_sll_assign_stmt_20804_c_macro_;
    // X2 := ( $mux (S [] 2 ) (( $slice X1 27 0 ) && ZERO_4) X1 )
    // $buffering 1
    fpunit_exec_exec__u32_sll_assign_stmt_20815_c_macro_;
    // X3 := ( $mux (S [] 3 ) (( $slice X2 23 0 ) && ZERO_8) X2 )
    // $buffering 1
    fpunit_exec_exec__u32_sll_assign_stmt_20826_c_macro_;
    // X4 := ( $mux (S [] 4 ) (( $slice X3 15 0 ) && ZERO_16) X3 )
    // $buffering 1
    fpunit_exec_exec__u32_sll_assign_stmt_20837_c_macro_;
    // Y := ( $mux (S [] 5 ) _b0 X4 ) $buffering 1
    fpunit_exec_exec__u32_sll_assign_stmt_20845_c_macro_;
    fpunit_exec_exec__u32_sll_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__u32_sll_series_block_stmt_20779_c_mutex_);
}
void
_fpunit_exec_exec_u35_sr_special_(bit_vector * __pX, bit_vector * __pS,
				  bit_vector * __pY,
				  bit_vector * __psticky)
{
    MUTEX_DECL
	(fpunit_exec_exec__u35_sr_special_series_block_stmt_11176_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__u35_sr_special_series_block_stmt_11176_c_mutex_);
    fpunit_exec_exec__u35_sr_special_inner_inarg_prep_macro__;
    // X0 := ( $mux (S [] 0 ) (ZERO_1 && ( $slice X 34 1 ) ) X )
    // $buffering 1
    fpunit_exec_exec__u35_sr_special_assign_stmt_11192_c_macro_;
    // t0 := ( $mux (S [] 0 ) (X [] 0 ) _b0 ) $buffering 1
    fpunit_exec_exec__u35_sr_special_assign_stmt_11202_c_macro_;
    // X1 := ( $mux (S [] 1 ) (ZERO_2 && ( $slice X0 34 2 ) ) X0 )
    // $buffering 1
    fpunit_exec_exec__u35_sr_special_assign_stmt_11213_c_macro_;
    // t1 := ( $mux (S [] 1 ) ( ~ (( $slice X0 1 0 ) == 0 ) ) _b0 )
    // $buffering 1
    fpunit_exec_exec__u35_sr_special_assign_stmt_11225_c_macro_;
    // X2 := ( $mux (S [] 2 ) (ZERO_4 && ( $slice X1 34 4 ) ) X1 )
    // $buffering 1
    fpunit_exec_exec__u35_sr_special_assign_stmt_11236_c_macro_;
    // t2 := ( $mux (S [] 2 ) ( ~ (( $slice X1 3 0 ) == 0 ) ) _b0 )
    // $buffering 1
    fpunit_exec_exec__u35_sr_special_assign_stmt_11248_c_macro_;
    // X3 := ( $mux (S [] 3 ) (ZERO_8 && ( $slice X2 34 8 ) ) X2 )
    // $buffering 1
    fpunit_exec_exec__u35_sr_special_assign_stmt_11259_c_macro_;
    // t3 := ( $mux (S [] 3 ) ( ~ (( $slice X2 7 0 ) == 0 ) ) _b0 )
    // $buffering 1
    fpunit_exec_exec__u35_sr_special_assign_stmt_11271_c_macro_;
    // X4 := ( $mux (S [] 4 ) (ZERO_16 && ( $slice X3 34 16 ) ) X3 )
    // $buffering 1
    fpunit_exec_exec__u35_sr_special_assign_stmt_11282_c_macro_;
    // t4 := ( $mux (S [] 4 ) ( ~ (( $slice X3 15 0 ) == 0 ) ) _b0 )
    // $buffering 1
    fpunit_exec_exec__u35_sr_special_assign_stmt_11294_c_macro_;
    // Y := ( $mux (S [] 5 ) (ZERO_32 && ( $slice X4 34 32 ) ) X4 )
    // $buffering 1
    fpunit_exec_exec__u35_sr_special_assign_stmt_11305_c_macro_;
    // t5 := ( $mux (S [] 5 ) ( ~ (( $slice X4 31 0 ) == 0 ) ) _b0 )
    // $buffering 1
    fpunit_exec_exec__u35_sr_special_assign_stmt_11317_c_macro_;
    // sticky := (((t0 | t1) | t2) | ((t3 | t4) | t5)) $buffering 1
    fpunit_exec_exec__u35_sr_special_assign_stmt_11330_c_macro_;
    fpunit_exec_exec__u35_sr_special_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__u35_sr_special_series_block_stmt_11176_c_mutex_);
}
void
_fpunit_exec_exec_u64_shift_(bit_vector * __pis_sll,
			     bit_vector * __pis_srl, bit_vector * __px,
			     bit_vector * __pshift_amount,
			     bit_vector * __presult)
{
    MUTEX_DECL
	(fpunit_exec_exec__u64_shift_series_block_stmt_21005_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__u64_shift_series_block_stmt_21005_c_mutex_);
    fpunit_exec_exec__u64_shift_inner_inarg_prep_macro__;
    // $volatile $call u64_sll (x shift_amount ) (result_sll ) 
    fpunit_exec_exec__u64_shift_call_stmt_21014_c_macro_;
    // $volatile $call u64_srl (x shift_amount ) (result_srl ) 
    fpunit_exec_exec__u64_shift_call_stmt_21018_c_macro_;
    // result := ( $mux is_sll result_sll result_srl ) $buffering 2// bits 
    // of buffering = 128. 
    fpunit_exec_exec__u64_shift_assign_stmt_21024_c_macro_;
    fpunit_exec_exec__u64_shift_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__u64_shift_series_block_stmt_21005_c_mutex_);
}
void
_fpunit_exec_exec_u64_shift_sticky_(bit_vector * __pis_sll,
				    bit_vector * __pis_srl,
				    bit_vector * __px,
				    bit_vector * __pshift_amount,
				    bit_vector * __presult,
				    bit_vector * __psticky)
{
    MUTEX_DECL
	(fpunit_exec_exec__u64_shift_sticky_series_block_stmt_21026_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__u64_shift_sticky_series_block_stmt_21026_c_mutex_);
    fpunit_exec_exec__u64_shift_sticky_inner_inarg_prep_macro__;
    // $volatile $call u64_sll (x shift_amount ) (result_sll ) 
    fpunit_exec_exec__u64_shift_sticky_call_stmt_21036_c_macro_;
    // $volatile $call u64_sr_special (x shift_amount ) (result_srl
    // shifted_bit_rep ) 
    fpunit_exec_exec__u64_shift_sticky_call_stmt_21041_c_macro_;
    // sticky := ( $mux is_srl shifted_bit_rep _b0 ) $buffering 1
    fpunit_exec_exec__u64_shift_sticky_assign_stmt_21047_c_macro_;
    // result := ( $mux is_sll result_sll result_srl ) $buffering 1
    fpunit_exec_exec__u64_shift_sticky_assign_stmt_21053_c_macro_;
    fpunit_exec_exec__u64_shift_sticky_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__u64_shift_sticky_series_block_stmt_21026_c_mutex_);
}
void
_fpunit_exec_exec_u64_sll_(bit_vector * __pX, bit_vector * __pS,
			   bit_vector * __pY)
{
    MUTEX_DECL(fpunit_exec_exec__u64_sll_series_block_stmt_20847_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__u64_sll_series_block_stmt_20847_c_mutex_);
    fpunit_exec_exec__u64_sll_inner_inarg_prep_macro__;
    // X0 := ( $mux (S [] 0 ) (( $slice X 62 0 ) && ZERO_1) X ) $buffering 
    // 1
    fpunit_exec_exec__u64_sll_assign_stmt_20861_c_macro_;
    // X1 := ( $mux (S [] 1 ) (( $slice X0 61 0 ) && ZERO_2) X0 )
    // $buffering 1
    fpunit_exec_exec__u64_sll_assign_stmt_20872_c_macro_;
    // X2 := ( $mux (S [] 2 ) (( $slice X1 59 0 ) && ZERO_4) X1 )
    // $buffering 1
    fpunit_exec_exec__u64_sll_assign_stmt_20883_c_macro_;
    // X3 := ( $mux (S [] 3 ) (( $slice X2 55 0 ) && ZERO_8) X2 )
    // $buffering 1
    fpunit_exec_exec__u64_sll_assign_stmt_20894_c_macro_;
    // X4 := ( $mux (S [] 4 ) (( $slice X3 47 0 ) && ZERO_16) X3 )
    // $buffering 1
    fpunit_exec_exec__u64_sll_assign_stmt_20905_c_macro_;
    // X5 := ( $mux (S [] 5 ) (( $slice X4 31 0 ) && ZERO_32) X4 )
    // $buffering 1
    fpunit_exec_exec__u64_sll_assign_stmt_20916_c_macro_;
    // Y := ( $mux (S [] 6 ) _b0 X5 ) $buffering 1
    fpunit_exec_exec__u64_sll_assign_stmt_20924_c_macro_;
    fpunit_exec_exec__u64_sll_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__u64_sll_series_block_stmt_20847_c_mutex_);
}
void
_fpunit_exec_exec_u64_sr_special_(bit_vector * __pX, bit_vector * __pS,
				  bit_vector * __pY,
				  bit_vector * __psticky)
{
    MUTEX_DECL
	(fpunit_exec_exec__u64_sr_special_series_block_stmt_10219_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__u64_sr_special_series_block_stmt_10219_c_mutex_);
    fpunit_exec_exec__u64_sr_special_inner_inarg_prep_macro__;
    // X0 := ( $mux (S [] 0 ) (ZERO_1 && ( $slice X 63 1 ) ) X )
    // $buffering 1
    fpunit_exec_exec__u64_sr_special_assign_stmt_10234_c_macro_;
    // t0 := ( $mux (S [] 0 ) (X [] 0 ) _b0 ) $buffering 1
    fpunit_exec_exec__u64_sr_special_assign_stmt_10244_c_macro_;
    // X1 := ( $mux (S [] 1 ) (ZERO_2 && ( $slice X0 63 2 ) ) X0 )
    // $buffering 1
    fpunit_exec_exec__u64_sr_special_assign_stmt_10255_c_macro_;
    // t1 := ( $mux (S [] 1 ) ( ~ (( $slice X0 1 0 ) == 0 ) ) _b0 )
    // $buffering 1
    fpunit_exec_exec__u64_sr_special_assign_stmt_10267_c_macro_;
    // X2 := ( $mux (S [] 2 ) (ZERO_4 && ( $slice X1 63 4 ) ) X1 )
    // $buffering 1
    fpunit_exec_exec__u64_sr_special_assign_stmt_10278_c_macro_;
    // t2 := ( $mux (S [] 2 ) ( ~ (( $slice X1 3 0 ) == 0 ) ) _b0 )
    // $buffering 1
    fpunit_exec_exec__u64_sr_special_assign_stmt_10290_c_macro_;
    // X3 := ( $mux (S [] 3 ) (ZERO_8 && ( $slice X2 63 8 ) ) X2 )
    // $buffering 1
    fpunit_exec_exec__u64_sr_special_assign_stmt_10301_c_macro_;
    // t3 := ( $mux (S [] 3 ) ( ~ (( $slice X2 7 0 ) == 0 ) ) _b0 )
    // $buffering 1
    fpunit_exec_exec__u64_sr_special_assign_stmt_10313_c_macro_;
    // X4 := ( $mux (S [] 4 ) (ZERO_16 && ( $slice X3 63 16 ) ) X3 )
    // $buffering 1
    fpunit_exec_exec__u64_sr_special_assign_stmt_10324_c_macro_;
    // t4 := ( $mux (S [] 4 ) ( ~ (( $slice X3 15 0 ) == 0 ) ) _b0 )
    // $buffering 1
    fpunit_exec_exec__u64_sr_special_assign_stmt_10336_c_macro_;
    // X5 := ( $mux (S [] 5 ) (ZERO_32 && ( $slice X4 63 32 ) ) X4 )
    // $buffering 1
    fpunit_exec_exec__u64_sr_special_assign_stmt_10347_c_macro_;
    // t5 := ( $mux (S [] 5 ) ( ~ (( $slice X4 31 0 ) == 0 ) ) _b0 )
    // $buffering 1
    fpunit_exec_exec__u64_sr_special_assign_stmt_10359_c_macro_;
    // Y := ( $mux (S [] 6 ) _b0 X5 ) $buffering 1
    fpunit_exec_exec__u64_sr_special_assign_stmt_10367_c_macro_;
    // sticky := (((t0 | t1) | t2) | ((t3 | t4) | t5)) $buffering 1
    fpunit_exec_exec__u64_sr_special_assign_stmt_10380_c_macro_;
    fpunit_exec_exec__u64_sr_special_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__u64_sr_special_series_block_stmt_10219_c_mutex_);
}
void
_fpunit_exec_exec_u64_srl_(bit_vector * __pX, bit_vector * __pS,
			   bit_vector * __pY)
{
    MUTEX_DECL(fpunit_exec_exec__u64_srl_series_block_stmt_20926_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__u64_srl_series_block_stmt_20926_c_mutex_);
    fpunit_exec_exec__u64_srl_inner_inarg_prep_macro__;
    // X0 := ( $mux (S [] 0 ) (ZERO_1 && ( $slice X 63 1 ) ) X )
    // $buffering 1
    fpunit_exec_exec__u64_srl_assign_stmt_20940_c_macro_;
    // X1 := ( $mux (S [] 1 ) (ZERO_2 && ( $slice X0 63 2 ) ) X0 )
    // $buffering 1
    fpunit_exec_exec__u64_srl_assign_stmt_20951_c_macro_;
    // X2 := ( $mux (S [] 2 ) (ZERO_4 && ( $slice X1 63 4 ) ) X1 )
    // $buffering 1
    fpunit_exec_exec__u64_srl_assign_stmt_20962_c_macro_;
    // X3 := ( $mux (S [] 3 ) (ZERO_8 && ( $slice X2 63 8 ) ) X2 )
    // $buffering 1
    fpunit_exec_exec__u64_srl_assign_stmt_20973_c_macro_;
    // X4 := ( $mux (S [] 4 ) (ZERO_16 && ( $slice X3 63 16 ) ) X3 )
    // $buffering 1
    fpunit_exec_exec__u64_srl_assign_stmt_20984_c_macro_;
    // X5 := ( $mux (S [] 5 ) (ZERO_32 && ( $slice X4 63 32 ) ) X4 )
    // $buffering 1
    fpunit_exec_exec__u64_srl_assign_stmt_20995_c_macro_;
    // Y := ( $mux (S [] 6 ) _b0 X5 ) $buffering 1
    fpunit_exec_exec__u64_srl_assign_stmt_21003_c_macro_;
    fpunit_exec_exec__u64_srl_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__u64_srl_series_block_stmt_20926_c_mutex_);
}
void
_fpunit_exec_exec_u64_true_divide_(bit_vector * __pudividend,
				   bit_vector * __pudivisor,
				   bit_vector * __pquotient)
{
    MUTEX_DECL
	(fpunit_exec_exec__u64_true_divide_series_block_stmt_21055_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__u64_true_divide_series_block_stmt_21055_c_mutex_);
    fpunit_exec_exec__u64_true_divide_inner_inarg_prep_macro__;
    fpunit_exec_exec__u64_true_divide_branch_block_stmt_21059_c_export_decl_macro_;
    {
	{
	    // do-while: file ./.Aa//linked.opt.aa, line 4459
	    __declare_static_bit_vector(UGE_u64_u1_21098, 1);
	    uint8_t         do_while_entry_flag;
	    do_while_entry_flag = 1;
	    uint8_t         do_while_loopback_flag;
	    do_while_loopback_flag = 0;
	    while (1) {
		// merge file ./.Aa//linked.opt.aa, line 4461
		fpunit_exec_exec__u64_true_divide_merge_stmt_21061_c_preamble_macro_;
		// $phi QUOTIENT := ZERO_64 $on $entry NQUOTIENT $on
		// $loopback 
		// type of target is $uint<64>
		fpunit_exec_exec__u64_true_divide_phi_stmt_21062_c_macro_;
		// $phi DIVIDEND := udividend $on $entry NDIVIDEND $on
		// $loopback 
		// type of target is $uint<64>
		fpunit_exec_exec__u64_true_divide_phi_stmt_21066_c_macro_;
		fpunit_exec_exec__u64_true_divide_merge_stmt_21061_c_postamble_macro_;
		// $report (iunit_exec true_divide DIVIDEND DIVIDEND
		// QUOTIENT QUOTIENT )
		fpunit_exec_exec__u64_true_divide_stmt_21073_c_macro_;
		// $call alignDivisorToDividend (DIVIDEND udivisor ) (SD
		// CQ ) 
		fpunit_exec_exec__u64_true_divide_call_stmt_21078_c_macro_;
		// QUOTIENT_21091_delayed_2_0 := QUOTIENT $buffering 2
		// $cut_through // bits of buffering = 128. 
		fpunit_exec_exec__u64_true_divide_assign_stmt_21081_c_macro_;
		// NQUOTIENT := (QUOTIENT_21091_delayed_2_0 + CQ)
		// $buffering 1// bits of buffering = 64. 
		fpunit_exec_exec__u64_true_divide_assign_stmt_21086_c_macro_;
		// DIVIDEND_21096_delayed_2_0 := DIVIDEND $buffering 2
		// $cut_through // bits of buffering = 128. 
		fpunit_exec_exec__u64_true_divide_assign_stmt_21089_c_macro_;
		// NDIVIDEND := (DIVIDEND_21096_delayed_2_0 - SD)
		// $buffering 1// bits of buffering = 64. 
		fpunit_exec_exec__u64_true_divide_assign_stmt_21094_c_macro_;
		do_while_entry_flag = 0;
		do_while_loopback_flag = 1;
		bit_vector_greater_equal(0, &(DIVIDEND), &(udivisor),
					 &(UGE_u64_u1_21098));
		if (has_undefined_bit(&UGE_u64_u1_21098)) {
		    fprintf(stderr,
			    "Error: variable UGE_u64_u1_21098 has undefined value (%s) at test point.\n",
			    to_string(&UGE_u64_u1_21098));
		    assert(0);
		}

		if (!bit_vector_to_uint64(0, &UGE_u64_u1_21098))
		    break;
	    }
	}
	fpunit_exec_exec__u64_true_divide_branch_block_stmt_21059_c_export_apply_macro_;
    }
    // $volatile quotient := q $buffering 1
    fpunit_exec_exec__u64_true_divide_assign_stmt_21102_c_macro_;
    fpunit_exec_exec__u64_true_divide_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__u64_true_divide_series_block_stmt_21055_c_mutex_);
}
void
fpunit_exec_exec_u64_true_divide(uint64_t udividend, uint64_t udivisor,
				 uint64_t * quotient)
{
    fpunit_exec_exec__u64_true_divide_outer_arg_decl_macro__;
    _fpunit_exec_exec_u64_true_divide_(&__udividend, &__udivisor,
				       &__quotient);
    fpunit_exec_exec__u64_true_divide_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_u_cmp_32_(bit_vector * __pa, bit_vector * __pb,
			    bit_vector * __pl, bit_vector * __pg,
			    bit_vector * __pe)
{
    MUTEX_DECL(fpunit_exec_exec__u_cmp_32_series_block_stmt_3200_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__u_cmp_32_series_block_stmt_3200_c_mutex_);
    fpunit_exec_exec__u_cmp_32_inner_inarg_prep_macro__;
    // al := ( $slice a 15 0 ) $buffering 1
    fpunit_exec_exec__u_cmp_32_assign_stmt_3209_c_macro_;
    // ah := ( $slice a 31 16 ) $buffering 1
    fpunit_exec_exec__u_cmp_32_assign_stmt_3213_c_macro_;
    // bl := ( $slice b 15 0 ) $buffering 1
    fpunit_exec_exec__u_cmp_32_assign_stmt_3217_c_macro_;
    // bh := ( $slice b 31 16 ) $buffering 1
    fpunit_exec_exec__u_cmp_32_assign_stmt_3221_c_macro_;
    // ll := (al < bl) $buffering 1
    fpunit_exec_exec__u_cmp_32_assign_stmt_3226_c_macro_;
    // gl := (al > bl) $buffering 1
    fpunit_exec_exec__u_cmp_32_assign_stmt_3231_c_macro_;
    // el := (al == bl) $buffering 1
    fpunit_exec_exec__u_cmp_32_assign_stmt_3236_c_macro_;
    // lh := (ah < bh) $buffering 1
    fpunit_exec_exec__u_cmp_32_assign_stmt_3241_c_macro_;
    // gh := (ah > bh) $buffering 1
    fpunit_exec_exec__u_cmp_32_assign_stmt_3246_c_macro_;
    // eh := (ah == bh) $buffering 1
    fpunit_exec_exec__u_cmp_32_assign_stmt_3251_c_macro_;
    // l := (lh | (eh & ll)) $buffering 1
    fpunit_exec_exec__u_cmp_32_assign_stmt_3258_c_macro_;
    // e := (eh & el) $buffering 1
    fpunit_exec_exec__u_cmp_32_assign_stmt_3263_c_macro_;
    // g := (gh | (eh & gl)) $buffering 1
    fpunit_exec_exec__u_cmp_32_assign_stmt_3270_c_macro_;
    fpunit_exec_exec__u_cmp_32_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__u_cmp_32_series_block_stmt_3200_c_mutex_);
}
void
_fpunit_exec_exec_u_cmp_34_(bit_vector * __pa, bit_vector * __pb,
			    bit_vector * __pl, bit_vector * __pg,
			    bit_vector * __pe)
{
    MUTEX_DECL
	(fpunit_exec_exec__u_cmp_34_series_block_stmt_21104_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__u_cmp_34_series_block_stmt_21104_c_mutex_);
    fpunit_exec_exec__u_cmp_34_inner_inarg_prep_macro__;
    // al := ( $slice a 31 0 ) $buffering 1
    fpunit_exec_exec__u_cmp_34_assign_stmt_21113_c_macro_;
    // ah := ( $slice a 33 32 ) $buffering 1
    fpunit_exec_exec__u_cmp_34_assign_stmt_21117_c_macro_;
    // bl := ( $slice b 31 0 ) $buffering 1
    fpunit_exec_exec__u_cmp_34_assign_stmt_21121_c_macro_;
    // bh := ( $slice b 33 32 ) $buffering 1
    fpunit_exec_exec__u_cmp_34_assign_stmt_21125_c_macro_;
    // $volatile $call u_cmp_32 (al bl ) (ll gl el ) 
    fpunit_exec_exec__u_cmp_34_call_stmt_21131_c_macro_;
    // lh := (ah < bh) $buffering 1
    fpunit_exec_exec__u_cmp_34_assign_stmt_21136_c_macro_;
    // gh := (ah > bh) $buffering 1
    fpunit_exec_exec__u_cmp_34_assign_stmt_21141_c_macro_;
    // eh := (ah == bh) $buffering 1
    fpunit_exec_exec__u_cmp_34_assign_stmt_21146_c_macro_;
    // l := (lh | (eh & ll)) $buffering 1
    fpunit_exec_exec__u_cmp_34_assign_stmt_21153_c_macro_;
    // e := (eh & el) $buffering 1
    fpunit_exec_exec__u_cmp_34_assign_stmt_21158_c_macro_;
    // g := (gh | (eh & gl)) $buffering 1
    fpunit_exec_exec__u_cmp_34_assign_stmt_21165_c_macro_;
    fpunit_exec_exec__u_cmp_34_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__u_cmp_34_series_block_stmt_21104_c_mutex_);
}
void
_fpunit_exec_exec_u_cmp_64_(bit_vector * __pa, bit_vector * __pb,
			    bit_vector * __pl, bit_vector * __pg,
			    bit_vector * __pe)
{
    MUTEX_DECL(fpunit_exec_exec__u_cmp_64_series_block_stmt_3272_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__u_cmp_64_series_block_stmt_3272_c_mutex_);
    fpunit_exec_exec__u_cmp_64_inner_inarg_prep_macro__;
    // al := ( $slice a 31 0 ) $buffering 1
    fpunit_exec_exec__u_cmp_64_assign_stmt_3281_c_macro_;
    // ah := ( $slice a 63 32 ) $buffering 1
    fpunit_exec_exec__u_cmp_64_assign_stmt_3285_c_macro_;
    // bl := ( $slice b 31 0 ) $buffering 1
    fpunit_exec_exec__u_cmp_64_assign_stmt_3289_c_macro_;
    // bh := ( $slice b 63 32 ) $buffering 1
    fpunit_exec_exec__u_cmp_64_assign_stmt_3293_c_macro_;
    // $volatile $call u_cmp_32 (al bl ) (ll gl el ) 
    fpunit_exec_exec__u_cmp_64_call_stmt_3299_c_macro_;
    // $volatile $call u_cmp_32 (ah bh ) (lh gh eh ) 
    fpunit_exec_exec__u_cmp_64_call_stmt_3305_c_macro_;
    // l := (lh | (eh & ll)) $buffering 1
    fpunit_exec_exec__u_cmp_64_assign_stmt_3312_c_macro_;
    // e := (eh & el) $buffering 1
    fpunit_exec_exec__u_cmp_64_assign_stmt_3317_c_macro_;
    // g := (gh | (eh & gl)) $buffering 1
    fpunit_exec_exec__u_cmp_64_assign_stmt_3324_c_macro_;
    fpunit_exec_exec__u_cmp_64_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__u_cmp_64_series_block_stmt_3272_c_mutex_);
}
void
_fpunit_exec_exec_u_set_index_64_(bit_vector * __pidx, bit_vector * __px)
{
    MUTEX_DECL
	(fpunit_exec_exec__u_set_index_64_series_block_stmt_3326_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__u_set_index_64_series_block_stmt_3326_c_mutex_);
    fpunit_exec_exec__u_set_index_64_inner_inarg_prep_macro__;
    // idx_16 := ($bitcast ($uint<16>) idx ) $buffering 1
    fpunit_exec_exec__u_set_index_64_assign_stmt_3332_c_macro_;
    // x00 := (($bitcast ($uint<16>) 1 ) << idx_16) $buffering 1
    fpunit_exec_exec__u_set_index_64_assign_stmt_3338_c_macro_;
    // x01 := ( $mux (idx_16 >= 16 ) (($bitcast ($uint<16>) 1 ) << (idx_16 
    // - 16 )) ZERO_16 ) $buffering 1
    fpunit_exec_exec__u_set_index_64_assign_stmt_3351_c_macro_;
    // x10 := ( $mux (idx_16 >= 32 ) (($bitcast ($uint<16>) 1 ) << (idx_16 
    // - 32 )) ZERO_16 ) $buffering 1
    fpunit_exec_exec__u_set_index_64_assign_stmt_3364_c_macro_;
    // x11 := ( $mux (idx_16 >= 48 ) (($bitcast ($uint<16>) 1 ) << (idx_16 
    // - 48 )) ZERO_16 ) $buffering 1
    fpunit_exec_exec__u_set_index_64_assign_stmt_3377_c_macro_;
    // x := ((x11 && x10) && (x01 && x00)) $buffering 1
    fpunit_exec_exec__u_set_index_64_assign_stmt_3386_c_macro_;
    fpunit_exec_exec__u_set_index_64_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__u_set_index_64_series_block_stmt_3326_c_mutex_);
}
void
_fpunit_exec_exec_uaddsub32_(bit_vector * __pL, bit_vector * __pR,
			     bit_vector * __pcarry_in,
			     bit_vector * __psubtract_flag,
			     bit_vector * __pret_val_x_x,
			     bit_vector * __pcarry_out)
{
    MUTEX_DECL
	(fpunit_exec_exec__uaddsub32_series_block_stmt_21167_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__uaddsub32_series_block_stmt_21167_c_mutex_);
    fpunit_exec_exec__uaddsub32_inner_inarg_prep_macro__;
    // r33 := ( $mux subtract_flag ((($bitcast ($uint<33>) L ) - ($bitcast 
    // ($uint<33>) R )) - ($bitcast ($uint<33>) carry_in )) ((($bitcast
    // ($uint<33>) L ) + ($bitcast ($uint<33>) R )) + ($bitcast
    // ($uint<33>) carry_in )) ) $buffering 1// bits of buffering = 33. 
    fpunit_exec_exec__uaddsub32_assign_stmt_21193_c_macro_;
    // ret_val_x_x := ( $slice r33 31 0 ) $buffering 1// bits of buffering 
    // = 32. 
    fpunit_exec_exec__uaddsub32_assign_stmt_21197_c_macro_;
    // carry_out := (r33 [] 32 ) $buffering 1// bits of buffering = 1. 
    fpunit_exec_exec__uaddsub32_assign_stmt_21202_c_macro_;
    fpunit_exec_exec__uaddsub32_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__uaddsub32_series_block_stmt_21167_c_mutex_);
}
void
_fpunit_exec_exec_umul32_(bit_vector * __pL, bit_vector * __pR,
			  bit_vector * __pret_val_x_x)
{
    MUTEX_DECL(fpunit_exec_exec__umul32_series_block_stmt_21204_c_mutex_);
    MUTEX_LOCK(fpunit_exec_exec__umul32_series_block_stmt_21204_c_mutex_);
    fpunit_exec_exec__umul32_inner_inarg_prep_macro__;
    // ret_val_x_x := (($bitcast ($uint<64>) L ) * ($bitcast ($uint<64>) R 
    // )) $buffering 1// bits of buffering = 64. 
    fpunit_exec_exec__umul32_assign_stmt_21214_c_macro_;
    fpunit_exec_exec__umul32_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__umul32_series_block_stmt_21204_c_mutex_);
}
void
fpunit_exec_exec_umul32(uint32_t L, uint32_t R, uint64_t * ret_val_x_x)
{
    fpunit_exec_exec__umul32_outer_arg_decl_macro__;
    _fpunit_exec_exec_umul32_(&__L, &__R, &__ret_val_x_x);
    fpunit_exec_exec__umul32_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_ushift32_(bit_vector * __pL, bit_vector * __pR,
			    bit_vector * __pshift_right_flag,
			    bit_vector * __psigned_flag,
			    bit_vector * __pret_val_x_x)
{
    MUTEX_DECL
	(fpunit_exec_exec__ushift32_series_block_stmt_21216_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__ushift32_series_block_stmt_21216_c_mutex_);
    fpunit_exec_exec__ushift32_inner_inarg_prep_macro__;
    // ret_val_x_x := ( $mux (shift_right_flag & signed_flag) ($bitcast
    // ($uint<32>) (($bitcast ($int<32>) L ) >> ($bitcast ($int<32>) R ))
    // ) ( $mux shift_right_flag (L >> R) (L << R) ) ) $buffering 1// bits 
    // of buffering = 32. 
    fpunit_exec_exec__ushift32_assign_stmt_21241_c_macro_;
    fpunit_exec_exec__ushift32_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__ushift32_series_block_stmt_21216_c_mutex_);
}
void
_fpunit_exec_exec_vfadd16_wrap_(bit_vector * __pu, bit_vector * __pv,
				bit_vector * __presult)
{
    MUTEX_DECL
	(fpunit_exec_exec__vfadd16_wrap_series_block_stmt_21243_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__vfadd16_wrap_series_block_stmt_21243_c_mutex_);
    fpunit_exec_exec__vfadd16_wrap_inner_inarg_prep_macro__;
    // $call exec_fp_simd_16_op (ONE_1 ZERO_1 ZERO_1 ZERO_1 u v ) (result
    // ) 
    fpunit_exec_exec__vfadd16_wrap_call_stmt_21254_c_macro_;
    fpunit_exec_exec__vfadd16_wrap_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__vfadd16_wrap_series_block_stmt_21243_c_mutex_);
}
void
fpunit_exec_exec_vfadd16_wrap(uint64_t u, uint64_t v, uint64_t * result)
{
    fpunit_exec_exec__vfadd16_wrap_outer_arg_decl_macro__;
    _fpunit_exec_exec_vfadd16_wrap_(&__u, &__v, &__result);
    fpunit_exec_exec__vfadd16_wrap_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_vfaddreduce16_wrap_(bit_vector * __pu, bit_vector * __pv,
				      bit_vector * __presult)
{
    MUTEX_DECL
	(fpunit_exec_exec__vfaddreduce16_wrap_series_block_stmt_21256_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__vfaddreduce16_wrap_series_block_stmt_21256_c_mutex_);
    fpunit_exec_exec__vfaddreduce16_wrap_inner_inarg_prep_macro__;
    // $call exec_fp_simd_16_op (ZERO_1 ZERO_1 ZERO_1 ONE_1 u v ) (r64 ) 
    fpunit_exec_exec__vfaddreduce16_wrap_call_stmt_21267_c_macro_;
    // result := ( $slice r64 31 0 ) $buffering 1// bits of buffering =
    // 32. 
    fpunit_exec_exec__vfaddreduce16_wrap_assign_stmt_21271_c_macro_;
    fpunit_exec_exec__vfaddreduce16_wrap_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__vfaddreduce16_wrap_series_block_stmt_21256_c_mutex_);
}
void
fpunit_exec_exec_vfaddreduce16_wrap(uint64_t u, uint64_t v,
				    uint32_t * result)
{
    fpunit_exec_exec__vfaddreduce16_wrap_outer_arg_decl_macro__;
    _fpunit_exec_exec_vfaddreduce16_wrap_(&__u, &__v, &__result);
    fpunit_exec_exec__vfaddreduce16_wrap_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_vfmul16_wrap_(bit_vector * __pu, bit_vector * __pv,
				bit_vector * __presult)
{
    MUTEX_DECL
	(fpunit_exec_exec__vfmul16_wrap_series_block_stmt_21273_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__vfmul16_wrap_series_block_stmt_21273_c_mutex_);
    fpunit_exec_exec__vfmul16_wrap_inner_inarg_prep_macro__;
    // $call exec_fp_simd_16_op (ZERO_1 ZERO_1 ONE_1 ZERO_1 u v ) (result
    // ) 
    fpunit_exec_exec__vfmul16_wrap_call_stmt_21284_c_macro_;
    fpunit_exec_exec__vfmul16_wrap_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__vfmul16_wrap_series_block_stmt_21273_c_mutex_);
}
void
fpunit_exec_exec_vfmul16_wrap(uint64_t u, uint64_t v, uint64_t * result)
{
    fpunit_exec_exec__vfmul16_wrap_outer_arg_decl_macro__;
    _fpunit_exec_exec_vfmul16_wrap_(&__u, &__v, &__result);
    fpunit_exec_exec__vfmul16_wrap_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_vfsub16_wrap_(bit_vector * __pu, bit_vector * __pv,
				bit_vector * __presult)
{
    MUTEX_DECL
	(fpunit_exec_exec__vfsub16_wrap_series_block_stmt_21286_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__vfsub16_wrap_series_block_stmt_21286_c_mutex_);
    fpunit_exec_exec__vfsub16_wrap_inner_inarg_prep_macro__;
    // $call exec_fp_simd_16_op (ZERO_1 ONE_1 ZERO_1 ZERO_1 u v ) (result
    // ) 
    fpunit_exec_exec__vfsub16_wrap_call_stmt_21297_c_macro_;
    fpunit_exec_exec__vfsub16_wrap_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__vfsub16_wrap_series_block_stmt_21286_c_mutex_);
}
void
fpunit_exec_exec_vfsub16_wrap(uint64_t u, uint64_t v, uint64_t * result)
{
    fpunit_exec_exec__vfsub16_wrap_outer_arg_decl_macro__;
    _fpunit_exec_exec_vfsub16_wrap_(&__u, &__v, &__result);
    fpunit_exec_exec__vfsub16_wrap_outer_op_xfer_macro__;
}


void
_fpunit_exec_exec_writeback_fsm_(bit_vector * __pwb_state,
				 bit_vector * __pvalid_bit,
				 bit_vector * __pthread_head,
				 bit_vector * __pstream_head,
				 bit_vector * __pbreak_thread,
				 bit_vector * __pterminate_thread,
				 bit_vector * __pkill_thread_now,
				 bit_vector * __pbreak_stream,
				 bit_vector * __pnext_wb_state,
				 bit_vector * __pinstr_can_execute)
{
    MUTEX_DECL
	(fpunit_exec_exec__writeback_fsm_series_block_stmt_21299_c_mutex_);
    MUTEX_LOCK
	(fpunit_exec_exec__writeback_fsm_series_block_stmt_21299_c_mutex_);
    fpunit_exec_exec__writeback_fsm_inner_inarg_prep_macro__;
    // next_wb_state := ((( $mux (wb_state == WB_RESET) ( $mux ( ~
    // valid_bit ) WB_RESET ( $mux break_thread WB_TRAPPED ( $mux
    // break_stream WB_MISPREDICTED_STREAM WB_NORMAL ) ) ) _b0 ) | ( $mux
    // (wb_state == WB_NORMAL) ( $mux ( ~ valid_bit ) WB_NORMAL ( $mux
    // break_thread WB_TRAPPED ( $mux break_stream WB_MISPREDICTED_STREAM
    // WB_NORMAL ) ) ) _b0 ) ) | (( $mux (wb_state ==
    // WB_MISPREDICTED_STREAM) ( $mux ( ~ valid_bit )
    // WB_MISPREDICTED_STREAM ( $mux (stream_head & break_thread)
    // WB_TRAPPED ( $mux (stream_head & break_stream)
    // WB_MISPREDICTED_STREAM ( $mux stream_head WB_NORMAL
    // WB_MISPREDICTED_STREAM ) ) ) ) _b0 ) | ( $mux (wb_state ==
    // WB_TRAPPED) ( $mux ( ~ valid_bit ) WB_TRAPPED ( $mux (thread_head & 
    // break_thread) WB_TRAPPED ( $mux (thread_head & break_stream)
    // WB_MISPREDICTED_STREAM ( $mux thread_head WB_NORMAL WB_TRAPPED ) )
    // ) ) _b0 ) )) $buffering 1
    fpunit_exec_exec__writeback_fsm_assign_stmt_21392_c_macro_;
    // instr_can_execute := (valid_bit & ((( $mux (wb_state == WB_RESET) ( 
    // $mux kill_thread_now ZERO_1 ONE_1 ) _b0 ) | ( $mux (wb_state ==
    // WB_NORMAL) ( $mux kill_thread_now ZERO_1 ONE_1 ) _b0 ) ) | (( $mux
    // (wb_state == WB_MISPREDICTED_STREAM) ( $mux (stream_head &
    // kill_thread_now) ZERO_1 ( $mux stream_head ONE_1 ZERO_1 ) ) _b0 ) | 
    // ( $mux (wb_state == WB_TRAPPED) ( $mux (thread_head &
    // kill_thread_now) ZERO_1 ( $mux thread_head ONE_1 ZERO_1 ) ) _b0 )
    // ))) $buffering 1
    fpunit_exec_exec__writeback_fsm_assign_stmt_21445_c_macro_;
    fpunit_exec_exec__writeback_fsm_inner_outarg_prep_macro__;
    MUTEX_UNLOCK
	(fpunit_exec_exec__writeback_fsm_series_block_stmt_21299_c_mutex_);
}
DEFINE_THREAD(fpunit_exec_exec_exec_daemon);
PTHREAD_DECL(fpunit_exec_exec_exec_daemon);
DEFINE_THREAD(fpunit_exec_exec_fpunit_exec_pipe_merge_daemon);
PTHREAD_DECL(fpunit_exec_exec_fpunit_exec_pipe_merge_daemon);
void
fpunit_exec_exec_start_daemons(FILE * fp, int trace_on)
{
    fpunit_exec_exec___report_log_file__ = fp;
    fpunit_exec_exec___trace_on__ = trace_on;
    fpunit_exec_exec___init_aa_globals__();
    PTHREAD_CREATE(fpunit_exec_exec_exec_daemon);
    PTHREAD_CREATE(fpunit_exec_exec_fpunit_exec_pipe_merge_daemon);
}
void
fpunit_exec_exec_stop_daemons()
{
    PTHREAD_CANCEL(fpunit_exec_exec_exec_daemon);
    PTHREAD_CANCEL(fpunit_exec_exec_fpunit_exec_pipe_merge_daemon);
}
