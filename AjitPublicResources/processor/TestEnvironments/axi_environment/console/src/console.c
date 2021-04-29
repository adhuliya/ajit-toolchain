//console.c
//
//AUTHOR:
//Neha Karanjkar
//
//The console simply consists of an output thread and an input thread.
//
//The output thread :
//	is connected to the TX pipe fed by the serial device.
//	as soon as it sees data on teh TX pipe, it displays the data on screen
//
//The input thread :
//	is connected to the Rx pipe read by the serial device
//	it keeps waiting for user input
//	as soon as it receives a character, it sends it to the RX pipe.
// modified by MPD.

#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "console.h"
#include "pthreadUtils.h"
#include "Pipes.h"
#include "SockPipes.h"
#include "pipeHandler.h"

uint8_t console_mode = CONSOLE_NORMAL_MODE;
void consoleOutput()
{
	uint8_t  data;

	while(1)
	{
		data		= read_uint8("SERIAL_TX_to_CONSOLE");
		putchar(data);
	}	
}


#include <termios.h>
#include <stdio.h>
#include <unistd.h>

static struct termios old, new;
 
/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(STDIN_FILENO, &old); /* grab old terminal i/o settings */
  new = old; /* make new settings same as old settings */
  new.c_lflag &= (echo ? ICANON : ~ICANON); /* disable buffered i/o */
  new.c_lflag &= (echo ? ECHO : ~ECHO); /* set echo mode */
  tcsetattr(STDIN_FILENO, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(STDIN_FILENO, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void) 
{
  return getch_(1);
}

void consoleInput()
{
	uint8_t  data;

	while(1)
	{
		//wait for user input
		//
		//***** replace the getchar() with getch() if you want
		//non-echoing, unbuffered input.

		data = getchar();
		write_uint8("CONSOLE_to_SERIAL_RX", data);

		// give a ms delay to avoid saturating the uart (experiment).
		usleep(1000);
	}	
}


DEFINE_THREAD(consoleInput);
DEFINE_THREAD(consoleOutput);

void startConsoleThreads()
{
	register_pipe("SERIAL_TX_to_CONSOLE",8,8,0);
	register_pipe("CONSOLE_to_SERIAL_RX",8,8,0);

	PTHREAD_DECL(consoleOutput);
	PTHREAD_CREATE(consoleOutput);

	PTHREAD_DECL(consoleInput);
	PTHREAD_CREATE(consoleInput);
}


