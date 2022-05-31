#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <pthread.h>
#include "pthreadUtils.h"
#include "uart_interface.h"

static pthread_mutex_t serial_device_mutex = PTHREAD_MUTEX_INITIALIZER;

// Serial device id.
int serial_device_fd = -1;

int uart_verbose_flag = 0;
int uart_blocking_flag = 1;

/* Baud rate constants from termios.h
#define B0	0x00000000
#define B50	0x00000001
#define B75	0x00000002
#define B110	0x00000003
#define B134	0x00000004
#define B150	0x00000005
#define B200	0x00000006
#define B300	0x00000007
#define B600	0x00000008
#define B1200	0x00000009
#define B1800	0x0000000a
#define B2400	0x0000000b
#define B4800	0x0000000c
#define B9600	0x0000000d
#define B19200	0x0000000e
#define B38400	0x0000000f
#define  B57600   0010001
#define  B115200  0010002

*/

//#define BAUDRATE B9600
#define BAUDRATE B115200
int uart_baud_rate=B115200;

/*
https://en.wikibooks.org/wiki/Serial_Programming/termios
*/

void setUartBlockingFlag(int x)
{
	uart_blocking_flag = x;
}

int getBaudRate() 
{
	return(uart_baud_rate);
}

//return 1 on error.
int setBaudRate(int b)
{
	int ret_val = 0;
	switch(b) {
		case 9600: uart_baud_rate = B9600; break;
		case 19200: uart_baud_rate = B19200; break;
		case 38400: uart_baud_rate = B38400; break;
		case 57600: uart_baud_rate = B57600; break;
		case 115200: uart_baud_rate = B115200; break;
		default: 
			ret_val = 1;
			fprintf(stderr,"Error: setBaudRate %d: supported values 9600/19200/38400/57600/115200.\n",
						b);
			break;
	}
	return(ret_val);
}

//
// returns < 0 if link failed.
//
int setupDebugUartLink(char* device)
{
	int sfd;

	pthread_mutex_lock(&serial_device_mutex);

	initComPort(&sfd, device);
	serial_device_fd = sfd;

	pthread_mutex_unlock(&serial_device_mutex);


	return(serial_device_fd);
}

// returns < 0 if link failed.
int setupDebugUartLinkWithBaudRate(char* device, int b)
{
	pthread_mutex_lock(&serial_device_mutex);
	int s = setBaudRate (b);
	if( s == 0)
	{
		int sfd;
		initComPort(&sfd, device);
		serial_device_fd = sfd;
	}
	else
	{
		serial_device_fd = -1;
	}
	pthread_mutex_unlock(&serial_device_mutex);

	return(serial_device_fd);
}

int calibrateUart()
{
}


//
// on success, *sfd is non-negative.
//
void initComPort(int* sfd, char* device)
{
	struct termios options;
	memset(&options,0, sizeof(options));
	options.c_iflag=0;
	options.c_oflag=0;
	options.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
	options.c_lflag=0;
	options.c_cc[VMIN]=1;
	options.c_cc[VTIME]=5;

	if(uart_blocking_flag)
		*sfd=open(device, O_RDWR);       
	else
		*sfd=open(device, O_RDWR | O_NONBLOCK);        // O_NONBLOCK might override VMIN and VTIME, so read() may return immediately.

	int ss = cfsetospeed(&options, uart_baud_rate);           
	if(ss != 0)
		fprintf(stderr,"Error: invalid UART ospeed %d.\n", uart_baud_rate);
	ss = cfsetispeed(&options, uart_baud_rate);
	if(ss != 0)
		fprintf(stderr,"Error: invalid UART ispeed %d.\n", uart_baud_rate);

	if (*sfd < 0)
	{
		fprintf(stderr, "unable to open %s\n",device);
	}
	else
	{
		tcsetattr(*sfd,TCSANOW,&options);
	}
}


int sendBytesOverUart(uint8_t* buf, int count)
{
	return(sendByteArrayBase(buf,count,1));
}

int sendByteArrayBase(uint8_t *buf, int count, int downto_flag)
{
	int I,ret_val;
	ret_val = 0;


	if(serial_device_fd >= 0)
	{
		int B, fB;

		pthread_mutex_lock(&serial_device_mutex);

		B  = (downto_flag ? (count-1) : count);
		fB = (downto_flag ? 0 : (count-1));

		while(1)
		{
			ret_val = write(serial_device_fd, &(buf[B]), 1);
			if(uart_verbose_flag)
			{
				fprintf(stderr,"Info: uart: sent 0x%x\n", buf[B]);
			}

			if(B == fB)
				break;

			B = (downto_flag ? (B-1) : (B+1));
		}
		pthread_mutex_unlock(&serial_device_mutex);

	}
	else
	{
		fprintf(stderr,"Error:Fatal: sendBytesOverUart: device not opened\n");
	}


	return(ret_val);
}

int sendByte(uint8_t x)
{
	while(1)
	{
		pthread_mutex_lock(&serial_device_mutex);
		int ret_val = write(serial_device_fd, &x, 1);
		pthread_mutex_unlock(&serial_device_mutex);

		if(ret_val == 1)
			break;

		usleep(10);
	}

	return(1);
}

uint8_t recvByte()
{
	uint8_t ret_val;

	while(1)
	{
		pthread_mutex_lock(&serial_device_mutex);
		int n = read(serial_device_fd, &ret_val, 1);
		pthread_mutex_unlock(&serial_device_mutex);
		if(n == 1)
			break;

		usleep(10);
	}

	return(ret_val);
}



int sendByteToSpecifiedUart (int fd, uint8_t b)
{
	int ret_val = write(fd, &b, 1);
	return(ret_val);
}


uint8_t recvByteFromSpecifiedUart(int fd)
{
	uint8_t ret_val;

	while(1)
	{
		pthread_mutex_lock(&serial_device_mutex);
		int n = read(fd, &ret_val, 1);
		pthread_mutex_unlock(&serial_device_mutex);
		if(n == 1)
			break;

		usleep(10);
	}

	return(ret_val);
}

//
// return 1 if byte received, else 0.
//  if noblock_flag == 1, then return after first
//  try.  Otherwise, keep reading until success.
//
// Byte is kept in *buf.
int recvBytesOverUart(uint8_t* buf, int count, int noblock_flag)
{
	return(recvBytesOverUartBase(buf,count,noblock_flag,1));
}

int recvBytesOverUartBase(uint8_t* buf,  int count, int noblock_flag, int downto_flag)
{
	int ret_val = 0;
	if(!uart_blocking_flag)
		tcdrain(serial_device_fd);

	if(serial_device_fd >= 0)
	{
		int I,fI;

		I = (downto_flag ? (count-1) : 0);
		fI = (downto_flag ? 0 : (count-1));

		while(1)
		{
			int b_ret_val = read(serial_device_fd, &(buf[I]), 1);

			if(!noblock_flag && (b_ret_val != 1))
			{
				while(1)
				{
					b_ret_val = read(serial_device_fd, &(buf[I]), 1);
					if(b_ret_val == 1) 
					{
						if(uart_verbose_flag)
						{
							fprintf(stderr,"Info: uart: received 0x%x\n", buf[I]);
						}
						break;
					}
				}
			}

			ret_val += b_ret_val;

			// on noblock-flag, stop as soon as you get 
			// a no-read.
			if(noblock_flag && (b_ret_val == 0))
				break;

			if(I == fI)
				break;

			I = (downto_flag ? (I-1) : (I+1));
		}
	}

	return(ret_val);
}


int perThreadSendBytesOverUart(int CORE_ID, int THREAD_ID, uint8_t* buf, int count)
{
	int I,ret_val;
	ret_val = 0;

	uint8_t score_id = CORE_ID;
	uint8_t sthread_id = THREAD_ID;

	if(serial_device_fd >= 0)
	{
		int B;
			
		pthread_mutex_lock(&serial_device_mutex);

		// first end the core id and the thread id.
		ret_val = write(serial_device_fd, &score_id, 1);
		ret_val = write(serial_device_fd, &sthread_id, 1);

		// then the bytes.
		for(B=count-1; B>=0; B--)
		{
			ret_val = write(serial_device_fd, &(buf[B]), 1);
			if(uart_verbose_flag)
			{
				fprintf(stderr,"Info: uart: sent 0x%x\n", buf[B]);
			}
		}
		pthread_mutex_unlock(&serial_device_mutex);

	}
	else
	{
		fprintf(stderr,"Error:Fatal: perThreadSendBytesOverUart: device not opened\n");
	}


	return(ret_val);
}
