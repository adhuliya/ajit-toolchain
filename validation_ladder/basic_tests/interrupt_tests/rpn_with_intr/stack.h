#include <stdint.h>
#include <stdio.h>

#ifdef AJIT
#include "core_portme.h"
#endif

#define MAX_SIZE 10
 
typedef struct stack{
	int stk[MAX_SIZE];
	int top;
}STACK;
 
void initStack(STACK* s);
int isEmpty(STACK* s);  
int isFull(STACK* s);
int peek(STACK* s);
int pop(STACK* s);
void push(STACK* s, int data);
void display (STACK* s);


