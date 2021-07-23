grammar ajit_validation ;

options {language=C;}
tokens
{
EQUAL='=';
G='g';
L='l';
O='o';
I='i';
F='f';
Y='y';
P='psr';
W='wim';
T='tbr';
C='pc';
N='npc';
S='fpsr';
R='cpsr';
U='mmu';
M='m';
A='asi';
X='x';
Z='asr';
CORE='core';
THREAD='thread';
}
@parser::preincludes{#include"Record.h"}
@parser::context 
{// A pointer to the data structure to be filled
Record* rec;
uint8_t mask_flag;
uint8_t thread_id_flag;
uint8_t core_id_flag;
}


@parser::includes
{
#define REC  (ctx->rec)
}


//grammar

//file	: line*  EOF ;
line
	: location EQUAL v=VALUE  (m=VALUE {ctx->mask_flag = 1;})? 
			(CORE   core_id=VALUE {ctx->core_id_flag = 1;})?
			(THREAD thread_id=VALUE {ctx->thread_id_flag = 1;})?
{ 
	
	REC->core_id = (ctx->core_id_flag ? atoi((const char*) $core_id.text->chars) : 0);
	REC->thread_id = (ctx->thread_id_flag ? atoi((const char*) $thread_id.text->chars) : 0);
	REC->expected_value =  strdup(((const char*)($v.text->chars)));
	REC->mask = (ctx->mask_flag ? strdup(((const char*)($m.text->chars))) : strdup("0xfffffffff"));
	ctx->mask_flag = 0;
	ctx->thread_id_flag = 0;
	ctx->core_id_flag = 0;

} | EOF {(REC->c = strdup("x")); } ;

location	: (reg_indexed | reg_non_indx | mem | asi);

reg_indexed	:  p=(G | L | O | I | F | U | Z) {REC->c = ((const char*)($p.text->chars));}  k=VALUE
{
	REC->reg_int=atoi(strdup((const char*)($k.text->chars)));
};

reg_non_indx 	:  p=(P | W | T | C | N | S | R | Y) 
{
	REC->c = strdup((const char*)($p.text->chars));
};

mem	: M {REC->c = strdup("mem"); } '[' addr=VALUE ']'   
{
	REC->address = strdup((const char*)($addr.text->chars));
};
asi	: A;

VALUE	: Integer | Binary | Hexadecimal ;


//comments are C+++style  single line comments


COMMENT
:   '//' ~('\n'|'\r')* '\r'? '\n' {$channel=HIDDEN;}
|   '/*' ( options {greedy=false;} : . )* '*/' {$channel=HIDDEN;}
;


//all whitespace is ignored
WS  :   ( '\n'
	  | '\t'
	  | '\r'
	  | ' '
	) +{$channel=HIDDEN;}
;

fragment Integer	:	'0' | '1'..'9' (DecimalDigit)*;
fragment Binary	: 	BinaryPrefix ( BinaryDigit)+;
fragment Hexadecimal       :	HexadecimalPrefix(HexDigit)+;
fragment BinaryPrefix          : ('0b' | '0B');
fragment HexadecimalPrefix     : ('0x' | '0X');  
fragment DecimalDigit    : '0'..'9' ;
fragment HexDigit        : ('0'..'9'|'a'..'f'|'A'..'F') ;
fragment BinaryDigit  	: ('0'|'1');
