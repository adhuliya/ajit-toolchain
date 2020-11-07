//StartDebugThreads.h
//
//Routines to start the debug units as a thread,
//and register all pipes used.

#ifndef _START_HWSERVER_THREADS_H_
#define _START_HWSERVER_THREADS_H_

//register all pipes
//used by the debug units
void register_hw_server_pipes(hwServerState* hs);

//start debug threads
hwServerState* start_hw_server(int cpu_id);


#endif
