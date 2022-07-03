//Console.h
//
//AUTHOR:
//Neha Karanjkar
//
//The console simply consists of an output thread and an input thread.
#ifndef core_env_CONSOLE_H
#define core_env_CONSOLE_H
#include<stdint.h>
#include <pthread.h>
#include "pthreadUtils.h"

#define CONSOLE_NORMAL_MODE      0
#define CONSOLE_SERVER_MODE      0x1
#define CONSOLE_SOCKET_MODE      0x2

void setConsoleMode(uint8_t console_mode);
void setConsoleInSocketMode();
void setConsoleServerPort(int sport_number);
void consoleInput();
void consoleOutput(void* dev_id);
void startConsoleThreads();
void startConsoleServer();

#endif
