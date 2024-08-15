#ifndef debug_interpreter_ultra_lite_h___
#define debug_interpreter_ultra_lite_h___

typedef enum __InterpreterCommandUltraLite {
	UNKNOWN, // error..
	LOG, 	 // "l <log-file>
        SCRIPT, // "s"
	QUIT,  // "q"
	MMAP,  // "m"
        HELP,  // "h"
	WRST,  // "w rst 1"
	WMEM,   // "w mem <asi> <addr> <wdata>"
	RMEM, // "r mem <asi> <addr>
        TOGGLE,
	GO
} InterpreterCommandUltraLite;

int executeCommandLineUltraLite(char* line_buffer);
int executeScriptFileUltraLite(char* file_name);
void printHelpMessageUltraLite();
void getLineFromStdinUltraLite(char* lb);
InterpreterCommandUltraLite classifyOpcodeUltraLite(int write_flag, char* id);
int parseCommandLineUltraLite(char* lb, InterpreterCommandUltraLite* opcode, 
					char* cmd_file_name, uint32_t* arg1, 
					uint32_t* arg2, uint32_t *arg3, uint32_t* arg4);
int  executeInterpreterCommandUltraLite(int nargs, InterpreterCommandUltraLite op,
					char* cmd_file_name,
					uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4);
int executeScriptFileUltraLite(char* file_name);
int executeCommandLineUltraLite(char* line_buffer);
void startDebugInterpreterUltraLite();

#endif
