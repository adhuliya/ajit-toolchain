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

int multi_core_flag = 0;

MultiCoreRxQueue core_queues[NCPUS];

//#define BAUDRATE B9600
#define BAUDRATE B115200

/*
https://en.wikibooks.org/wiki/Serial_Programming/termios
*/

void setUartBlockingFlag(int x)
{
	uart_blocking_flag = x;
}

int getBuadRate() 
{
	return(BAUDRATE);
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

	cfsetospeed(&options,BAUDRATE);           
	cfsetispeed(&options,BAUDRATE);          

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




void initMultiCoreRxQueue (MultiCoreRxQueue* mcrq)
{
	pthread_mutex_init (&(mcrq->lock), NULL);

	MUTEX_LOCK(mcrq->lock);
	mcrq->write_pointer = 0;
	mcrq->read_pointer = 0;
	MUTEX_UNLOCK(mcrq->lock);
}

void pushByte(MultiCoreRxQueue* mcrq, uint8_t b)
{
	MUTEX_LOCK(mcrq->lock);
	mcrq->buffer[mcrq->write_pointer] = b;
	mcrq->write_pointer = (mcrq->write_pointer + 1) % MCBUFSIZE;
	if(mcrq->write_pointer == mcrq->read_pointer)
		mcrq->read_pointer = (mcrq->read_pointer + 1) % MCBUFSIZE;
	MUTEX_UNLOCK(mcrq->lock);
}
// returns 1 if popped byte exists.
int popByte(MultiCoreRxQueue* mcrq, uint8_t* b)
{
	int ret_val = 0;
	MUTEX_LOCK(mcrq->lock);
	if(mcrq->read_pointer != mcrq->write_pointer)
	{
		*b = mcrq->buffer[mcrq->read_pointer];
		mcrq->read_pointer = (mcrq->read_pointer + 1) % MCBUFSIZE;
		ret_val = 1;
	}
	MUTEX_UNLOCK(mcrq->lock);
	return(ret_val);
}

void multiCoreDebugUartRxDaemon()
{
	int I;
	for(I = 0; I < NCPUS; I++)
	{
		initMultiCoreRxQueue(&(core_queues[I]));
	}
	while(1)
	{
		uint8_t core_id;
		recvBytesOverUart(&core_id, 1, 0);
		if(core_id > NCPUS)
		{
			fprintf(stderr, "Error:multiCoreDebugUartRxDaemon: cpu_id > %d\n", NCPUS);
		}
		int I;
		for(I = 0; I < 4; I++)
		{
			uint8_t X;
			recvBytesOverUart(&X, 1, 0);
			pushByte(&(core_queues[core_id]), X);
		}
	}
}

DEFINE_THREAD(multiCoreDebugUartRxDaemon);
PTHREAD_DECL(multiCoreDebugUartRxDaemon);

void startMultiCoreDebugUartRxDaemon()
{
	PTHREAD_CREATE(multiCoreDebugUartRxDaemon);
}




void perCoreRecvBytesOverUart (int CORE_ID, uint8_t*  buf, int count)
{
	int I;
	for (I = count-1; I >= 0; I--)
	{
		uint8_t bval;
		while(1)
		{
			int status = popByte (&(core_queues[CORE_ID]), &bval);

			if(status)	
			{
				if(uart_verbose_flag)
					fprintf(stderr,"Info: uart: received 0x%x\n", buf[I]);
				break;
			}

			usleep(100);
		}
		buf[I] = bval;
	}
}

int perCoreSendBytesOverUart(int CORE_ID, uint8_t* buf, int count)
{
	int I,ret_val;
	ret_val = 0;

	uint8_t score_id = CORE_ID;

	if(serial_device_fd >= 0)
	{
		int B;
			
		pthread_mutex_lock(&serial_device_mutex);

		// first end the core id.
		ret_val = write(serial_device_fd, &score_id, 1);

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
		fprintf(stderr,"Error:Fatal: perCoreSendBytesOverUart: device not opened\n");
	}


	return(ret_val);
}
