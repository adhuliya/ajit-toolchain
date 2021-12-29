#include <stdint.h>
#include <stdio.h>
#include "stack.h"
#ifdef AJIT
#include "core_portme.h"
#endif

#ifdef AJIT
#define PRINTF ee_printf
#else
#define PRINTF printf
#endif

void initStack(STACK* s){

	s->top=-1;
}

int isEmpty(STACK* s) {

	if(s->top == -1)
		return 1;
	else
		return 0;
}
   
int isFull(STACK* s) {

	if(s->top == (MAX_SIZE -1))
		return 1;
	else
		return 0;
}

int peek(STACK* s) {
	return s->top;
}

int pop(STACK* s) {

	int data;	
	if(!isEmpty(s)) {
		data = s->stk[s->top];
		s->top = s->top - 1;   
		return data;
	} else {
		PRINTF("Could not retrieve data, Stack is empty.\n");
		return -1;
	}
}

void push(STACK* s, int data) {

	if(!isFull(s)) {
		s->top = s->top + 1;   
		s->stk[s->top] = data;
	} else {
		PRINTF("Could not insert data, Stack is full.\n");
	}
}


void display (STACK* s){
	int i;
	if (s->top == -1)
	{
		PRINTF ("Stack is empty\n");
		return;
	}
	else
	{
		PRINTF ("\n The status of the stack is \n");
		for (i = s->top; i >= 0; i--)
		{
		    PRINTF ("%d\n", s->stk[i]);
		}
	}
	PRINTF ("\n");
}

