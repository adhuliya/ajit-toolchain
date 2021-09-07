#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <assert.h>
#include <pthread.h>
#include "pthreadUtils.h"
#include "uart_interface.h"
#include "SockPipes.h"
#include "RxQueueServer.h"

MultiThreadRxQueue thread_queues[NCORES][NTHREADS_PER_CORE];

int socket_mode = 0;
char* sock_pipe_name = NULL;

void setRxQueueServerInSocketMode(char* pname) 
{
	fprintf(stderr,"Info: setRxQueueServerInSocketMode(%s).\n", pname);
	socket_mode = 1;
	sock_pipe_name = strdup(pname);
}


// Byte is kept in *buf. return 0 on OK.
int recvByteFromDut(uint8_t* buf)
{
	int ret_val = 1;
	if(buf == NULL)
		return(1);

	if(socket_mode  && (sock_pipe_name != NULL))
	{
#ifdef VERBOSE
		fprintf(stderr,"Info: recvByteFromDut: trying to read from pipe %s.\n", sock_pipe_name);
#endif
		*buf = sock_read_uint8(sock_pipe_name);
#ifdef VERBOSE
		fprintf(stderr,"Info: recvByteFromDut: read 0x%x on pipe %s.\n", *buf, sock_pipe_name);
#endif
		ret_val = 0;
	}
	else if(!socket_mode)
	{
		*buf = recvByte();
		ret_val = 0;
	}
	return(ret_val);
}


void initMultiThreadRxQueue (MultiThreadRxQueue* mcrq)
{
	pthread_mutex_init (&(mcrq->lock), NULL);

	MUTEX_LOCK(mcrq->lock);
	mcrq->write_pointer = 0;
	mcrq->read_pointer = 0;
	MUTEX_UNLOCK(mcrq->lock);
}

void pushByte(MultiThreadRxQueue* mcrq, uint8_t b)
{
	MUTEX_LOCK(mcrq->lock);
	mcrq->buffer[mcrq->write_pointer] = b;
	mcrq->write_pointer = (mcrq->write_pointer + 1) % MCBUFSIZE;
	if(mcrq->write_pointer == mcrq->read_pointer)
		mcrq->read_pointer = (mcrq->read_pointer + 1) % MCBUFSIZE;
	MUTEX_UNLOCK(mcrq->lock);
}
// returns 1 if popped byte exists.
int popByte(MultiThreadRxQueue* mcrq, uint8_t* b)
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

void multiThreadRxDaemon()
{
	fprintf(stderr,"Info: started multiThreadRxDaemon.\n");
	while(1)
	{
		uint8_t core_id, thread_id;

		int stat = recvByteFromDut(&core_id);
		assert(stat == 0);

		if(core_id >= NCORES)
		{
			fprintf(stderr, "Error:multiThreadDebugUartRxDaemon: core_id >= %d\n", NCORES);
		}
		stat = recvByteFromDut(&thread_id);
		assert(stat == 0);

#ifdef VERBOSE
		fprintf(stderr,"Info:multiThreadRxDaemon: received core_id=%d, thread_id=%d.\n",
					core_id, thread_id);
#endif

		if(thread_id >= NTHREADS_PER_CORE)
		{
			fprintf(stderr, "Error:multiThreadDebugUartRxDaemon: thread_id >= %d\n", NTHREADS_PER_CORE);
		}
		int I;
		for(I = 0; I < 4; I++)
		{
			uint8_t X;
			stat = recvByteFromDut(&X);
			assert(stat == 0);

			pushByte(&(thread_queues[core_id][thread_id]), X);
#ifdef VERBOSE
			fprintf(stderr,"Info:multiThreadRxDaemon: core_id=%d, thread_id=%d, pushed byte 0x%x.\n",
						core_id, thread_id, X);
#endif
		}
	}
}

DEFINE_THREAD(multiThreadRxDaemon);
PTHREAD_DECL(multiThreadRxDaemon);

void startMultiThreadRxDaemon()
{
	int I, J;
	for(I = 0; I < NCORES; I++)
	{
		for (J = 0; J < NTHREADS_PER_CORE; J++)
		{
			fprintf(stderr,"Info: initialized multiThreadRxQueue (%d, %d).\n", I, J);
			initMultiThreadRxQueue(&(thread_queues[I][J]));
		}
	}

	PTHREAD_CREATE(multiThreadRxDaemon);
}

void perThreadRecvBytesFromRxDaemon (int CORE_ID, int THREAD_ID, uint8_t*  buf, int count)
{
	int I;
	for (I = count-1; I >= 0; I--)
	{
		uint8_t bval;
		while(1)
		{
			int status = popByte (&(thread_queues[CORE_ID][THREAD_ID]), &bval);

			if(status)	
			{
#ifdef VERBOSE
				fprintf(stderr,"Info: RxDaemon (%d,%d): received 0x%x I=%d.\n", 
							CORE_ID, THREAD_ID, buf[I], I);
#endif
				break;
			}

			usleep(100);
		}
		buf[I] = bval;
	}
}

