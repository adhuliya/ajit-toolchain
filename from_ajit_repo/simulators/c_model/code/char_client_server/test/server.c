#include <stdio.h>
#include <stdlib.h>

#include <char_client_server.h>

int main(int argc, char* argv[])
{
	char line_buffer[4096];
	if(argc < 2)
	{
		fprintf(stderr,"Error: specify port number.\n");
		return(1);
	}

	int port_number = atoi(argv[1]);
	int server_sock = start_char_server(port_number);
	if(server_sock < 0)
	{
		fprintf(stderr,"Error: could not start server on port number %d.\n", port_number);
		return(1);
	}

	int client_sock = server_open_client_connection(server_sock);
	if(client_sock < 0)
	{
		fprintf(stderr,"Error: could not get client connection on server on port number %d.\n", port_number);
		return(1);
	}

	while(1)
	{
		send_character(client_sock,'%');
		int N = get_line(client_sock,line_buffer, 4096);
		send_character(client_sock,'%');
		send_string(client_sock,line_buffer);
	}
	return(0);
}

