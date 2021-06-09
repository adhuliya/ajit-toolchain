#ifndef char_client_server_h____
#define char_client_server_h____

int  start_char_server(int port_id);
int  server_open_client_connection(int sockt); // sockt = server socket, return client socket.
int  client_open_server_connection(int port_number);

int  send_character(int client_sock, char c);
char get_character(int client_sock);
int  get_string(int client_sock, char* string_buffer, int max_length); 
int  get_line(int client_sock, char* line_buffer, int max_length); 
int  send_string(int client_sock, char* string_buffer);
#endif
