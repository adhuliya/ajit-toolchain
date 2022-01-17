#ifndef ajit_mt_sw_traps___
#define ajit_mt_sw_traps___

#define NUMBER_OF_SW_TRAPS_SUPPORTED 	16

////////////////////////////////////////////////////////////////////////////////////////////////////////
// The software trap  handler structure for bare-metal is set up as follows.
// 
// First, it is assumed that all invalid stack pointers are initialized to
// to 0 (clear_stack_pointers must be called in the init.s script).
//
// On a software trap, the function ajit_generic_sw_trap_handler is
// called with four arguments (tbr, o1,o2,o3).  
//
// Based on the tbr value, the  generic sw trap handler calls a specific handler.
// 
// Currently we support  16 sw trap handlers which populate
// a function pointer array.  Each function pointer in the array points
// to a function with form:  void foo (uint32_t arg1, uint32_t arg2, uint32_t arg3);
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

// sets all sw trap specific handlers to null.
void ajit_initialize_sw_trap_handlers_to_null();
// set function pointer of specific handler for sw trap_level.
void ajit_set_sw_trap_handler (uint32_t sw_trap_level, void (* foo) (uint32_t, uint32_t, uint32_t));
// From the TBR, figure out the sw trap level and
// call the sw trap handler in the array (if it is not null).
// If it is null, halt the machine!
void ajit_generic_sw_trap_handler(uint32_t tbr_value, uint32_t arg1, uint32_t arg2, uint32_t arg3);

#endif
