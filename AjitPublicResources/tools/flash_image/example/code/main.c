//Program for RPN calculator  using serial interrupts
#include <stdint.h>
#include <stdio.h>
#include "stack.h"
char expr[MAX_SIZE];		//Arrays are automatically initialized with all NULL elements , int equivalent to '\0'
#ifdef AJIT
// include AJIT related header files here.
#include "ajit_access_routines.h"
#include "core_portme.h"

extern int run_forever;
void add_delay();

int k = 0;
//int flag_calculate = 0;
int flag_line_over = 0;
int exit_flag = 0;

int __enable_serial()
{
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);
	return(0);
}

int __enable_serial_interrupt()
{
	__ajit_write_serial_control_register__ (TX_ENABLE | RX_ENABLE |RX_INTR_ENABLE);
	return(0);
}

#define PRINTF ee_printf
#else
#define PRINTF printf
#endif

#ifdef AJIT
//integer return value of '\0' =0 and '\n' is 10
int  __ajit_serial_getline__ (char* s){
	int i = 0;
	while(1)
	{
		int rval = 0;
		while(rval == 0)
		{
			rval = __ajit_serial_getchar__();		
		}

		if(rval == 10)		//newline
			break;
		
		s[i] = rval;
		i++;
	}

	return i;	//length of line
}

/***PROBLEM : unless you give enter key (ie. \n) scanf type functions such as gets, getchar
dont work and because of \n its taken as first char read in next scanf type functions***/
/***REASON : Its linux terminal which keeps stdio data in buffer and transfers it only  on the
press of '\n'***/
void __ajit_dummy_read__(){

	int dummy = 0;			//dummy read for \n after every scanf type input		
	while(dummy == 0)		
	  dummy = __ajit_serial_getchar__();
}

int __ajit_getchar__(){

	int i = 0;			//dummy read for \n after every scanf type input		
	while(i == 0)		
	  i = __ajit_serial_getchar__();
	
	return i;
}

void __serial_isr(){
	
	//__ajit_write_irc_control_register__(0);	//disable irc
	__AJIT_WRITE_IRC_CONTROL_REGISTER__(0);

	//PRINTF("ISR ENTER (k=%d)\n",k);

	//uint32_t B = __ajit_read_serial_rx_register__();
	uint32_t B;
	__AJIT_READ_SERIAL_RX_REGISTER__(B);

	if(B == 'q')
	{
		exit_flag = 1;
	}
 
	if((k == (MAX_SIZE-1)) || (B == '\n'))
	{
		expr[k] = '\0';	//text line over
		k = 0;
		flag_line_over = 1;
	}
	else if (B != 0) 
	{
		expr[k]= B;
		k++;
	}


	//PRINTF("ISR EXIT (%x)\n",B);
}

#endif

int calculate(char* expr, STACK* s){
	int i,t,a,b,c;
	i=0;
			
	//PRINTF("\nIn Calculate\n");
	while(expr[i]!='\0'){		//*modify required

		if(expr[i] >= '0' && expr[i] <='9'){
			t = expr[i] - '0';
			push(s, t);	//push operands

		}else{
			//operator;
	           	b=pop(s);
			a=pop(s);
			switch(expr[i]){
				case '+' :
					c=a+b;
					push(s,c);
			      		break;
			      	case '-' :
					c=a-b;
	  				push(s,c);
		        	 	break;
		 	     	case '*' :
			        	c=a*b;
					push(s,c);
			       		break;
			      	case '/' :
			        	c=a/b;
					push(s,c);
			        	break;
			      	default :
			        	PRINTF("Wrong operator\n" );
			}
								
		}
		i++;
	}

	c= pop(s);
	return c;
}

int main () {

	int c;
	STACK s;

	initStack(&s);

#ifdef AJIT
	//flag_line_over = 0;
	// exit_flag = 0;
#endif

#ifdef AJIT
	__enable_serial_interrupt();
#endif
	
	PRINTF("?? : \n");		//for ee_printf \n is delimiter
	while(1){
		
		
		#ifdef AJIT
		
		//	__ajit_write_irc_control_register__(1);	//enable irc	
		__AJIT_WRITE_IRC_CONTROL_REGISTER__(1);
		//After above instruction anytime interrupt can work
		add_delay();
		//__ajit_write_irc_control_register__(0);	//disable irc
		__AJIT_WRITE_IRC_CONTROL_REGISTER__(0);

		if(flag_line_over == 1){		//interrupt has occured, line has been read, ISR serviced
					
			flag_line_over = 0;

			if(exit_flag)
			{
				break;
			}

			c = calculate(expr,&s);
			PRINTF("\nR: %d\n",c);
			PRINTF("?? :\n ");		//for ee_printf \n is delimiter
		}
	
		#else
		gets(expr);
		c = calculate(expr,&s);
		PRINTF("\nR: %d\n",c);
		PRINTF("?? : \n");		//for ee_printf \n is delimiter
		#endif


		//break;
		
	}

	
	
	PRINTF("\nBYE(%d)\n", exit_flag);
	//exit_flag = 0;

	return(0);
	
}
