#ifndef uarch_debug_utils_ultra_lite_h___
#define uarch_debug_utils_ultra_lite_h___

#define UL_READ_OP     1
#define UL_RESET_OP    2
#define UL_RUN_OP      3
#define UL_TOGGLE_OP   4
#define UL_WRITE_OP    5

int dbg_load_mmap_ultra_lite(char* memoryMapFile);
uint32_t dbg_write_reset_ultra_lite(uint32_t rval);
uint32_t dbg_read_mem_ultra_lite(uint32_t addr);
uint32_t dbg_write_mem_ultra_lite(uint32_t addr, uint32_t data);
void dbg_send_debug_command_ultra_lite(uint32_t cmd_val);
uint32_t dbg_get_debug_response_ultra_lite();
uint32_t dbg_go_ultra_lite();
uint32_t dbg_toggle_ultra_lite();


#endif
