#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


int start_char_server(int port_id)
{

	int sockt, newsockt, portno, clilen, bind_ret;
	struct sockaddr_in serv_addr, cli_addr;

	// Request to create socket with the given parameters
	sockt = socket(AF_INET, SOCK_STREAM, 0);
	if (sockt < 0) 	{
		fprintf(stderr,"Error:char_client_server:start_char_server: couldn't create a socket\n");
		return -1;
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port_id);

	// Bind to the socket wait for connection requests
	bind_ret = bind(sockt, (struct sockaddr *) &serv_addr,sizeof(serv_addr));
	if (bind_ret < 0) 	{
		fprintf(stderr,"Error:char_client_server:start_char_server: port is already taken\n");
		return(-1);
	}
	listen(sockt,5);
	return(sockt);
}

int server_open_client_connection(int sockt)
{
	int newsockt, clilen;
	struct sockaddr_in cli_addr;
	clilen = sizeof(cli_addr);

	puts("SWServer : Waiting for the connection from GDB..");
	// Accept the connection from the other process
	newsockt = accept(sockt, (struct sockaddr *) &cli_addr, &clilen);
	if (newsockt < 0)	{
	 	fprintf(stderr, "Error:char_client_server:open_client_connection: failed to connect.\n");
	 	return -1;
	 }

	return newsockt;
}

int client_open_server_connection(int server_port_number)
{
	int sockfd, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	n = -1;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		fprintf(stderr,"Error:client_open_server_connection: could not open client socket\n");
		return n;
	}

	server = gethostbyname("127.0.0.1");
	if (server == NULL) 
	{
		fprintf(stderr, "Error:client_open_server_connection: server host 127.0.0.1 not found..\n");
		close(sockfd);
		sockfd = -1;
	}
	else
	{
		bzero((char *) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		bcopy((char *)(server->h_addr),(char *) &serv_addr.sin_addr.s_addr,server->h_length);
		serv_addr.sin_port = htons(server_port_number);

		fprintf(stderr, "Info:client_open_server_connection: connecting to server 127.0.0.1 on port %d .......... \n",
				server_port_number);
		while(n == -1)
		{
			n=connect(sockfd,(struct sockaddr*) &serv_addr,sizeof(serv_addr));
		}

		fprintf(stderr, "Info:client_open_server_connection: successfully connected to server 127.0.0.1 on port %d .......... \n",
				server_port_number);
	}

	return(n);
}

int send_character(int client_sock, char c)
{
	char buffer [8];
	buffer[0] = c;
	int n = write(client_sock,buffer,1);
	return(n);

}

char get_character(int client_sock)
{
	char buffer [8];
	buffer[0] = 0;

	int n = read(client_sock,buffer,1);

	return(buffer[0]);
}


// get a string (stop at white-space, null-terminate it..). 
int get_string(int client_sock, char* string_buffer, int max_length) // returns number of characters received.
{
	int I;
	char c;

	if(max_length <= 0)
		return(0);

	string_buffer[0] = 0;
	if(max_length == 1)
		return(1);

	while(1)
	{
		c = get_character(client_sock);
		if(!isspace(c))
		{
			string_buffer[0] = c;
			break;
		}
	}
	for(I=1; I < (max_length-2); I++)
	{
		c = get_character(client_sock);
		if(!isspace(c))
		{
			string_buffer[I] = c;
		}
		else
			break;
	}
	string_buffer[max_length-1] = 0;
	return(I);
}

// get a line (stop at new-line or eof.). 
int get_line(int client_sock, char* string_buffer, int max_length) // returns number of characters received.
{
	int I;
	char c;

	if(max_length <= 0)
		return(0);

	string_buffer[0] = 0;
	if(max_length == 1)
		return(1);

	while(1)
	{
		c = get_character(client_sock);
		if(!isspace(c))
		{
			string_buffer[0] = c;
			break;
		}
	}

	for(I=1; I < (max_length-2); I++)
	{
		c = get_character(client_sock);
		if((c != '\n') && (c != EOF))
		{
			string_buffer[I] = c;
		}
		else
		{
			string_buffer[I] = '\n';
			string_buffer[I+1] = 0;
			break;
		}
	}
	return(I+2);
}

int  send_string(int client_sock, char* string_buffer)
{
	int L = strlen(string_buffer);
	int I;
	for(I=0; I < L; I++)
	{
		send_character(client_sock, string_buffer[I]);
	}
	return L;
}
