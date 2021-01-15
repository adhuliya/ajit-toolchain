#include <stdio.h>
#include <stdlib.h>

#include <char_client_server.h>

#include <termios.h>            //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>     //STDIN_FILENO


static struct termios oldt, newt;
int set_tty_in_console_mode(void){   

	int c;   

	/*tcgetattr gets the parameters of the current terminal
	 *     STDIN_FILENO will tell tcgetattr that it should write the settings
	 *         of stdin to oldt*/
	tcgetattr( STDIN_FILENO, &oldt);
	/*now the settings will be copied*/
	newt = oldt;

	/*ICANON normally takes care that one line at a time will be processed
	 *     that means it will return if it sees a "\n" or an EOF or an EOL*/
	newt.c_lflag &= ~(ICANON | ECHO);          

	/*Those new settings will be set to STDIN
	 *     TCSANOW tells tcsetattr to change attributes immediately. */
	tcsetattr( STDIN_FILENO, TCSANOW, &newt);
}

int revert_tty()
{
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
}


int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		fprintf(stderr,"Error: specify port number.\n");
		return(1);
	}

	int client_sock = client_open_server_connection(atoi(argv[1]));	
	char line_buffer[4096];

	//set_tty_in_console_mode();
	while(1)
	{
		char v =  get_character(client_sock);
		fprintf(stdout,"%c",v);

		while(1)
		{
			char c =  getchar();
			send_character(client_sock,c);
			if((c== EOF) || (c == '\n'))
				break;
		}

		get_line (client_sock, line_buffer, 4096);
		fprintf(stdout,"%s", line_buffer);

	}
	//revert_tty();

	return(0);
}

