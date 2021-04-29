#ifndef __debugServerMultiThreadDefines___
#define __debugServerMultiThreadDefines___

#define dbg_gdb_OK 		  0x00004F4B
#define dbg_gdb_ERROR		  0x00004F5C
#define dbg_gdb_BP_HIT	  	  0x53494705
#define dbg_gdb_READ_WP_HIT	  0x53494706
#define dbg_gdb_WRITE_WP_HIT	  0x53494707
#define dbg_gdb_TRAP_HIT	  0x53494709
#define dbg_gdb_RST_HIT	  	  0x53494703
#define dbg_gdb_INTR_HIT	  0x53494702
#define dbg_gdb_ERROR_MODE	  0x54412030

// commands.
#define gdb_dbg_CONNECT         	14
#define gdb_dbg_DETACH          	15
#define gdb_dbg_KILL            	19
#define gdb_dbg_CONTINUE        	16

#define gdb_dbg_SET_BREAK_POINT         8
#define gdb_dbg_REMOVE_BREAK_POINT      9
#define gdb_dbg_SET_WATCH_POINT         10
#define gdb_dbg_REMOVE_WATCH_POINT      11

#define gdb_dbg_READ_IUNIT_REG          1
#define gdb_dbg_WRITE_IUNIT_REG         2
#define gdb_dbg_READ_FPUNIT_REG         3
#define gdb_dbg_WRITE_FPUNIT_REG        4

#define gdb_dbg_READ_MEM        	6
#define gdb_dbg_WRITE_MEM       	7

#define gdb_dbg_READ_CONTROL_REG        13
#define gdb_dbg_WRITE_CONTROL_REG       20
#define gdb_dbg_READ_CPUNIT_REG         17
#define gdb_dbg_WRITE_CPUNIT_REG        18

// New: added in Sept. 2019.
#define   gdb_dbg_WRITE_RESET   	    24 
#define   gdb_dbg_WRITE_INIT_PC             25   
#define   gdb_dbg_WRITE_INIT_NPC            26  
#define   gdb_dbg_WRITE_INIT_PSR            27  
#define   gdb_dbg_READ_INIT_PC              28 
#define   gdb_dbg_READ_INIT_NPC             29
#define   gdb_dbg_READ_INIT_PSR             30
#define   gdb_dbg_READ_MODE                 31


// "ccu_to_debug" commands
// Unused opcode command
//  length    opcode    command
//      8       8       16
#define ccu_dbg_CONNECT_RQST    1
#define ccu_dbg_BP_HIT          2
#define ccu_dbg_READ_WP_HIT     3
#define ccu_dbg_WRITE_WP_HIT    4
#define ccu_dbg_THREAD_FINISH   5
#define ccu_dbg_ERROR_MODE      6
#define ccu_dbg_ERROR           7
#define ccu_dbg_OK              8
#define ccu_dbg_READ_RESPONSE   9


#endif
