#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <pthreadUtils.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <SocketLib.h>
#include <unistd.h>


int COUNTER;

#define MAX_NUMBER_OF_PORTS 4
void Handle_Segfault(int signal)
{
	fprintf(stderr, "Error:  segmentation fault! giving up!!\n");
	exit(-1);
}

void Handle_Ctrl_C(int signal)
{
	fprintf(stderr, "Ctrl-C, Interrupt!!\n");
	fprintf(stdout, "Finished %d comparisons.\n", COUNTER);
	exit(-1);
}

				
void print_usage(char* ename)
{
	fprintf(stderr,"%s [-h] [-p port-name]+  [-n nbytes-to-be-compared] [-e error-limit] [-l log-interval]\n", ename);
	fprintf(stderr,"  -h: print this message.\n");
	fprintf(stderr,"  -p port-name: port-to-listen-on (at least two, at most four).\n");
	fprintf(stderr,"  -n nbytes-to-be-compared: number of bytes to be received in each step. (default=4)\n");
	fprintf(stderr,"  -e error-limit: number of errors before quitting. (default=16)\n");
	fprintf(stderr,"  -c count-limit: number of items to be compared before quitting. (default=1024)\n");
	fprintf(stderr,"  -l log-interval: interval for printing count of compares. (default=10000000)\n");
}

// command-line parsing
int opt;

// sends a hex string, separated into 4-byte pieces.
char* to_hex_string(char* buf, int nbytes_to_be_compared, char* print_buf)
{
	print_buf[0] = 0;
	sprintf(print_buf, "0x");
	char format_string[16];
	int I;
	int byte_count = 0;
	for(I=nbytes_to_be_compared-1; I >= 0; I--)
	{
		if((byte_count > 0) && ((byte_count % 4) == 0))
			sprintf(format_string, " 0x%02x", (unsigned char) buf[I]);
		else
			sprintf(format_string, "%02x", (unsigned char) buf[I]);

		strcat(print_buf, format_string);
		byte_count++;
	}	
	return(print_buf);
}

//
// options
//    -n <nbytes-to-be-compared> (-p portnumber)+
// at least two ports should be specified.
// at  most four ports should be specified.
//
int main(int argc, char* argv[])
{
	int nbytes_to_be_compared = 4;
	int port_array[MAX_NUMBER_OF_PORTS];
	int server_array[MAX_NUMBER_OF_PORTS];
	int port_id = 0;
	int nports = 0;
	int error_limit = 16;
	int log_interval = 1024*1024;

	// if count-limit is negative, run forever.
	int count_limit = -1;
	
	signal(SIGINT,  Handle_Ctrl_C);
        signal(SIGTERM, Handle_Segfault);
	while ((opt = getopt(argc, argv, "p:n:e:hc:l:")) != -1) {
		switch(opt) {
			case 'h':
				print_usage(argv[0]);
				break;
			case 'e':
				error_limit = atoi(optarg);
				if(error_limit < 0) 
					error_limit = 1;
				break;
			case 'c':
				count_limit = atoi(optarg);
				if(count_limit < 0) 
					count_limit = 1024;
				break;
			case 'n': 
				nbytes_to_be_compared = atoi(optarg);
				if(nbytes_to_be_compared > 0)
					fprintf(stderr,"Info: nbytes_to_be_compared = %d.\n", nbytes_to_be_compared);
				else {
					fprintf(stderr,"Error: nbytes_to_be_compared (%d) must be > 0.\n", 
									nbytes_to_be_compared);
					return(1);
				}
				break;
			case 'l': 
				log_interval = atoi(optarg);
				if(log_interval > 0)
					fprintf(stderr,"Info: nbytes_to_be_compared = %d.\n", nbytes_to_be_compared);
				else {
					fprintf(stderr,"Error: log_interval (%d) must be > 0.\n", 
									nbytes_to_be_compared);
					return(1);
				}
				break;
			case 'p':
				port_id = atoi(optarg);
				if(nports >= 4)
				{
					fprintf(stderr,"Warning: at most 4 ports supported. port %d ignored.\n", port_id);
				}
				else
				{
					fprintf(stderr,"Info: added port %d.\n", port_id);
					port_array[nports] = port_id;
					nports++;
				}
				break;
			default:
				break;
		}
	}

	if(nports < 2)
	{
		fprintf(stderr,"Error: at least two ports should be specified.\n");
		return(1);
	}
	
	// create servers.
	int I;
	for(I = 0; I < nports; I++)
	{
		// at most one client connection permitted.

		int server_sock = create_server(port_array[I], 1);
		if(server_sock >= 0)
		{
			server_array[I] = server_sock;
		}
		else
		{
			fprintf(stderr,"Error: could not create server on port %d.\n", port_array[I]);
			return(1);
		}
	}

	char* rx_array = malloc ((nbytes_to_be_compared+4)*sizeof(char));
	char* imm_array = malloc ((nbytes_to_be_compared+4)*sizeof(char));

	char print_buf_0[1024];
	char print_buf_1[1024];

	// now listen on servers.
	COUNTER = 0;
	int error_count = 0;
	char ok_flag = 0;
	while((count_limit < 0) || (COUNTER < count_limit))
	{
		char err_flag = 0;
		for(I = 0; I  < nports; I++)
		{
			
			int client_sock = 0;
			int N;
			while(client_sock <= 0)
			{
				client_sock = connect_to_client(server_array[I]);
				if(client_sock <= 0)
					usleep(1000); // wait and try again.
			}
			N = receive_string(client_sock, imm_array, nbytes_to_be_compared);

			// send ack to client sock.
			while(1)
			{
				if(can_write_to_socket(client_sock))
				{
					send(client_sock,&ok_flag, 1, 0);
					close(client_sock);
					break;
				}
				else
					usleep(1000);
			}

			if(I == 0)
			{
				memcpy(rx_array, imm_array, nbytes_to_be_compared);
			}
			else
			{
				int mismatch = 0;
				int J;
				for(J = 0; J < nbytes_to_be_compared; J++)
				{
					if(rx_array[J] != imm_array[J])
					{
						mismatch = 1;
						fprintf(stderr, "Error: byte %d mismatch at COUNT=%d, ports %d, %d.\n",
									J, COUNTER, 0, I);
					}
				}
				if(mismatch)
				{
					fprintf(stdout, "%d.\tport %d: %s\tport %d: %s\n",
							COUNTER,
							port_array[0], 
							to_hex_string(rx_array, nbytes_to_be_compared,
								(char*) &print_buf_0),
							port_array[I],
							to_hex_string(imm_array, nbytes_to_be_compared,
								(char*) &print_buf_1));
					fflush(stdout);
					err_flag = 1;
				}
			}

		}	

		if(err_flag)
			error_count++;

		if(error_count == error_limit)
		{
			fprintf(stderr,"Info: error limit reached (%d).\n", error_count);
			break;
		}

		if((COUNTER%log_interval) == 0)
		{
			fprintf(stderr,"Info: finished %d compares (%d errors).\n", COUNTER, error_count);
		}
		COUNTER++;
	}

	fprintf(stderr,"Finished %d compares with %d errors.\n", COUNTER, error_count);
	fprintf(stdout,"Finished %d compares with %d errors.\n", COUNTER, error_count);


	return(0);
}

