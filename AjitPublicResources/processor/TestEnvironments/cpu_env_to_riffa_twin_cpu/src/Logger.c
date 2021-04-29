
#include <stdarg.h>
#include<stdio.h>
#include<string.h>
#include"Logger.h"


char buffer[NUM_MESSAGES][MAX_MESSAGE_SIZE];
char str[MAX_MESSAGE_SIZE];
int front;
int back;
long unsigned int size;
void reset_logger()
{
	int i,j=0;
	printf("Logger : reseting logger\n");
	for(i=0;i<NUM_MESSAGES;i++)
	for(j=0;j<MAX_MESSAGE_SIZE;j++)
		buffer[i][j]='\0';
	front =0;
	back=0;
	size=0;

}

void push_to_queue(char* msg)
{
	if(back==front && size >=NUM_MESSAGES) front = (front+1)%NUM_MESSAGES;
	char* destination = buffer[back];
	strcpy(destination, msg);
	size=size++;
	back = (back+1)%NUM_MESSAGES;
	//printf("\npush. front = %d, back = %d size = %d",front,back,size);
}

void log_message(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vsprintf(str,format, args);
    va_end(args);
    push_to_queue(str);

}

void print_queue()
{
	int count;
	fprintf(stderr,"\n");
	fprintf(stderr,"-----------------------------------------------------------\n");
	fprintf(stderr,"Printing out the last %d lines of log : \n",NUM_MESSAGES);
	fprintf(stderr,"-----------------------------------------------------------\n");
	for (count=0;count<NUM_MESSAGES;count++)
	{
		fprintf(stderr,"%d : %s",count,buffer[front]);
		front=(front+1)%NUM_MESSAGES;
		if(count>size) break;
	}
}

			





