#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/types.h>

//#define BAUDRATE B9600
#define BAUDRATE B115200

/*
https://en.wikibooks.org/wiki/Serial_Programming/termios
*/

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

  *sfd=open(device, O_RDWR | O_NONBLOCK);        // O_NONBLOCK might override VMIN and VTIME, so read() may return immediately.

  cfsetospeed(&options,BAUDRATE);           
  cfsetispeed(&options,BAUDRATE);          

  if (*sfd == -1)
  {
	  fprintf(stderr, "unable to open %s, exit.\n",device);
	  exit(1);
  }
  else
  {
	  tcsetattr(*sfd,TCSANOW,&options);
  }
}


int main(int argc, char* argv[])
{
	int sfd;

	int32_t n, i, bytes;
	uint8_t buff, readbuff;

	if(argc < 2)
	{
		fprintf(stderr,"Usage: %s [serial-dev-name]\n", argv[0]);
		return (1);
	}

	// Initialize the serial port
	initComPort(&sfd, argv[1]);

	for(i=0; i < 255*100; i++)
	{
		buff = i;
		write(sfd,&buff,1);
		tcdrain(sfd);
		while(1)
		{
			n = read(sfd, &readbuff, 1);
			if(n == 1) 
				break;
		}

		if(buff == readbuff)
		{
#ifdef DEBUG
			fprintf(stderr,"Info: Read=0x%x=Write\n", (uint32_t) readbuff);
#endif
		}
		else
			fprintf(stderr,"Error: Read=0x%x, Write=0x%x\n", (uint32_t) readbuff,(uint32_t) buff);
	}
}

