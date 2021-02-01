#ifndef debug_interpreter_h___
#define debug_interpreter_h___

typedef enum __InterpreterCommand {
	UNKNOWN, // error..
	LOG, 	 // "l <log-file>
	SETCORE, // "c <core-id>"
	GDBSTART,    // "g start"
	GDBSTOP,    // "g stop"
        SCRIPT, // "s"
	QUIT,  // "q"
	MMAP,  // "m"
        HELP,  // "h"
	WRST,  // "w rst"
	RMODE, // "r mode"
	WIPC,   // "w ipc"
	RIPC,   // "r ipc"
	WINPC,  // "w inpc"
	RINPC,  // "r inpc"
	WIPSR,  // "w ipsr"
	WPSR,  // "w psr"
	RPSR,  // "r psr"
	RIPSR,  // "r ipsr"
	WTBR,    // "w tbr"
	RTBR,    // "r tbr"
	WY,    // "w y"
	RY,    // "r y"
	WWIM,  // "w wim"
	RWIM,  // "r wim"
	WASR,  // "w asr <asr-id> <asr-val>"
	RASR,  // "r asr <asr-id>"
	WIUREG, // "w iureg <reg-id> <reg-val>"
	RIUREG, // "r iureg <reg-id>"
	WFPREG, // "w fpreg <reg-id> <reg-val>"
	RFPREG, // "r fpreg <reg-id>"
	WMEM,   // "w mem <asi> <addr> <wdata>"
	RMEM,   // "r mem <asi> <addr>
	DUMPMEM
} InterpreterCommand;

void setDebugInterpreterInMultiCoreMode(int mcm);
int getDebugInterpreterInMultiCoreMode();


#endif
