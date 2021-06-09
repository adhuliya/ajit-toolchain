#ifndef LOGGER_H
#define LOGGER_H

#define NUM_MESSAGES 200
#define MAX_MESSAGE_SIZE 200


void reset_logger();


void log_message(const char *format, ...);

void print_queue();

			

#endif



