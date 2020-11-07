#ifndef __STATS_KEEPING_H__
#define __STATS_KEEPING_H__

//Functions for keeping counts of instructions 
//executed in the sparc core
void increment_instruction_count();
uint64_t get_instruction_count();

#endif
