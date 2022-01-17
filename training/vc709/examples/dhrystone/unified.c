/*
 ****************************************************************************
 *
 *                   "DHRYSTONE" Benchmark Program
 *                   -----------------------------
 *                                                                            
 *  Version:    C, Version 2.1
 *                                                                            
 *  File:       dhry_1.c (part 2 of 3)
 *
 *  Date:       May 25, 1988
 *
 *  Author:     Reinhold P. Weicker
 *
 ****************************************************************************
 */

#include <stdint.h>
#ifdef AJIT
#include <ajit_access_routines.h>
#include <core_portme.h>
#define PRINTF ee_printf
#define EE_TICKS_PER_SEC (100000000/256)
#else
#define PRINTF printf
#endif

#include "dhry.h"

#ifdef AJIT
#define EE_TICKS_PER_SECOND  (100000000/256)
int __enable_serial()
{
	__ajit_write_serial_control_register__ ( TX_ENABLE | RX_ENABLE);
	return(0);
}

inline void halt()
{
	__asm__ __volatile__("ta 0; nop; nop;");
}

#define ASI_MMU_REGISTER                0x04
inline void store_word_mmureg(uint32_t value, uint32_t* addr)
{
        __asm__ __volatile__("sta %0, [%1] %2\n\t" : : "r"(value), "r"(addr),
                             "i"(ASI_MMU_REGISTER) : "memory");
}


#endif

/* Global Variables: */

Rec_Pointer     Ptr_Glob,
                Next_Ptr_Glob;
int             Int_Glob;
Boolean         Bool_Glob;
char            Ch_1_Glob,
                Ch_2_Glob;
int             Arr_1_Glob [50];
int             Arr_2_Glob [50] [50];

Enumeration     Func_1 ();
  /* forward declaration necessary since Enumeration may not simply be int */

#ifndef REG
        Boolean Reg = false;
#define REG
        /* REG becomes defined as empty */
        /* i.e. no register variables   */
#else
        Boolean Reg = true;
#endif

/* variables for time measurement: */

#ifdef TIMES
struct tms      time_info;
//extern  int     times ();
                /* see library function "times" */
#define Too_Small_Time 120
                /* Measurements should last at least about 2 seconds */
#endif
#ifdef TIME
extern long     time();
                /* see library function "time"  */
#define Too_Small_Time 2
                /* Measurements should last at least 2 seconds */
#endif

long	        Begin_Time,
                	End_Time,
                	User_Time;
float           Microseconds,
                Dhrystones_Per_Second;

/* end of variables for time measurement */

  
// get rid of malloc.
Rec_Type g_rec __attribute__ ((aligned(8)));
Rec_Type p_rec __attribute__ ((aligned(8)));

void run_dhrystone (int Number_Of_Runs)
/*****/

  /* main program, corresponds to procedures        */
  /* Main and Proc_0 in the Ada version             */
{
        One_Fifty       Int_1_Loc;
  REG   One_Fifty       Int_2_Loc;
        One_Fifty       Int_3_Loc;
  REG   char            Ch_Index;
        Enumeration     Enum_Loc;
        Str_30          Str_1_Loc;
        Str_30          Str_2_Loc;
  REG   int             Run_Index;


  Enum_Loc = 0;
  Int_1_Loc = 0;
  Int_2_Loc = 0;

  Next_Ptr_Glob = &g_rec;
  Ptr_Glob = &p_rec;

  /* Initializations */
  Ptr_Glob->Ptr_Comp                    = Next_Ptr_Glob;
  Ptr_Glob->Discr                       = Ident_1;
  Ptr_Glob->variant.var_1.Enum_Comp     = Ident_3;
  Ptr_Glob->variant.var_1.Int_Comp      = 40;
  __strcpy (Ptr_Glob->variant.var_1.Str_Comp, 
          "DHRYSTONE PROGRAM, SOME STRING");
  __strcpy (Str_1_Loc, "DHRYSTONE PROGRAM, 1'ST STRING");

  Arr_2_Glob [8][7] = 10;
        /* Was missing in published program. Without this statement,    */
        /* Arr_2_Glob [8][7] would have an undefined value.             */
        /* Warning: With 16-Bit processors and Number_Of_Runs > 32000,  */
        /* overflow may occur for this array element.                   */

  PRINTF ("\n");
  PRINTF ("Dhrystone Benchmark, Version 2.1 (Language: C)\n");
  PRINTF ("\n");
  if (Reg)
  {
    PRINTF ("Program compiled with 'register' attribute\n");
    PRINTF ("\n");
  }
  else
  {
    PRINTF ("Program compiled without 'register' attribute\n");
    PRINTF ("\n");
  }
  PRINTF ("\n");

  PRINTF ("Execution starts, %d runs through Dhrystone\n", Number_Of_Runs);

 
#ifdef TIMES
#ifdef AJIT
  Begin_Time = ajit_barebones_clock();
#else
  times (&time_info);
  Begin_Time = (long) time_info.tms_utime;
#endif
#endif
#ifdef TIME
  Begin_Time = time ( (long *) 0);
#endif 

  for (Run_Index = 1; Run_Index <= Number_Of_Runs; ++Run_Index)
  {

    Proc_5();
    Proc_4();
      /* Ch_1_Glob == 'A', Ch_2_Glob == 'B', Bool_Glob == true */
    Int_1_Loc = 2;
    Int_2_Loc = 3;
    __strcpy (Str_2_Loc, "DHRYSTONE PROGRAM, 2'ND STRING");
    Enum_Loc = Ident_2;
    Bool_Glob = ! Func_2 (Str_1_Loc, Str_2_Loc);
      /* Bool_Glob == 1 */
    while (Int_1_Loc < Int_2_Loc)  /* loop body executed once */
    {
      Int_3_Loc = 5 * Int_1_Loc - Int_2_Loc;
        /* Int_3_Loc == 7 */
      Proc_7 (Int_1_Loc, Int_2_Loc, &Int_3_Loc);
        /* Int_3_Loc == 7 */
      Int_1_Loc += 1;
    } /* while */
      /* Int_1_Loc == 3, Int_2_Loc == 3, Int_3_Loc == 7 */
    Proc_8 (Arr_1_Glob, Arr_2_Glob, Int_1_Loc, Int_3_Loc);
      /* Int_Glob == 5 */
    Proc_1 (Ptr_Glob);
    for (Ch_Index = 'A'; Ch_Index <= Ch_2_Glob; ++Ch_Index)
                             /* loop body executed twice */
    {
      if (Enum_Loc == Func_1 (Ch_Index, 'C'))
          /* then, not executed */
        {
        Proc_6 (Ident_1, &Enum_Loc);
        __strcpy (Str_2_Loc, "DHRYSTONE PROGRAM, 3'RD STRING");
        Int_2_Loc = Run_Index;
        Int_Glob = Run_Index;
        }
    }
      /* Int_1_Loc == 3, Int_2_Loc == 3, Int_3_Loc == 7 */
    Int_2_Loc = Int_2_Loc * Int_1_Loc;
    Int_1_Loc = Int_2_Loc / Int_3_Loc;
    Int_2_Loc = 7 * (Int_2_Loc - Int_3_Loc) - Int_1_Loc;
      /* Int_1_Loc == 1, Int_2_Loc == 13, Int_3_Loc == 7 */
    Proc_2 (&Int_1_Loc);
      /* Int_1_Loc == 5 */

  } /* loop "for Run_Index" */

  /**************/
  /* Stop timer */
  /**************/
  
#ifdef TIMES
#ifndef AJIT
  times (&time_info);
  End_Time = (long) time_info.tms_utime;
#else
  End_Time = ajit_barebones_clock();
#endif 
#endif
#ifdef TIME
  End_Time = time ( (long *) 0);
#endif

  PRINTF ("Execution ends\n");
  PRINTF ("\n");
  PRINTF ("Final values of the variables used in the benchmark:\n");
  PRINTF ("\n");
  PRINTF ("Int_Glob:            %d\n", Int_Glob);
  PRINTF ("        should be:   %d\n", 5);
  PRINTF ("Bool_Glob:           %d\n", Bool_Glob);
  PRINTF ("        should be:   %d\n", 1);
  PRINTF ("Ch_1_Glob:           %d\n", Ch_1_Glob);
  PRINTF ("        should be:   %d\n", 'A');
  PRINTF ("Ch_2_Glob:           %d\n", Ch_2_Glob);
  PRINTF ("        should be:   %d\n", 'B');
  PRINTF ("Arr_1_Glob[8]:       %d\n", Arr_1_Glob[8]);
  PRINTF ("        should be:   %d\n", 7);
  PRINTF ("Arr_2_Glob[8][7]:    %d\n", Arr_2_Glob[8][7]);
  PRINTF ("        should be:   Number_Of_Runs + 10\n");
  PRINTF ("Ptr_Glob->\n");
  PRINTF ("  Ptr_Comp:          %d\n", (int) Ptr_Glob->Ptr_Comp);
  PRINTF ("        should be:   (implementation-dependent)\n");
  PRINTF ("  Discr:             %d\n", Ptr_Glob->Discr);
  PRINTF ("        should be:   %d\n", 0);
  PRINTF ("  Enum_Comp:         %d\n", Ptr_Glob->variant.var_1.Enum_Comp);
  PRINTF ("        should be:   %d\n", 2);
  PRINTF ("  Int_Comp:          %d\n", Ptr_Glob->variant.var_1.Int_Comp);
  PRINTF ("        should be:   %d\n", 17);
  PRINTF ("  Str_Comp:          %s\n", Ptr_Glob->variant.var_1.Str_Comp);
  PRINTF ("        should be:   DHRYSTONE PROGRAM, SOME STRING\n");
  PRINTF ("Next_Ptr_Glob->\n");
  PRINTF ("  Ptr_Comp:          %d\n", (int) Next_Ptr_Glob->Ptr_Comp);
  PRINTF ("        should be:   (implementation-dependent), same as above\n");
  PRINTF ("  Discr:             %d\n", Next_Ptr_Glob->Discr);
  PRINTF ("        should be:   %d\n", 0);
  PRINTF ("  Enum_Comp:         %d\n", Next_Ptr_Glob->variant.var_1.Enum_Comp);
  PRINTF ("        should be:   %d\n", 1);
  PRINTF ("  Int_Comp:          %d\n", Next_Ptr_Glob->variant.var_1.Int_Comp);
  PRINTF ("        should be:   %d\n", 18);
  PRINTF ("  Str_Comp:          %s\n",
                                Next_Ptr_Glob->variant.var_1.Str_Comp);
  PRINTF ("        should be:   DHRYSTONE PROGRAM, SOME STRING\n");
  PRINTF ("Int_1_Loc:           %d\n", Int_1_Loc);
  PRINTF ("        should be:   %d\n", 5);
  PRINTF ("Int_2_Loc:           %d\n", Int_2_Loc);
  PRINTF ("        should be:   %d\n", 13);
  PRINTF ("Int_3_Loc:           %d\n", Int_3_Loc);
  PRINTF ("        should be:   %d\n", 7);
  PRINTF ("Enum_Loc:            %d\n", Enum_Loc);
  PRINTF ("        should be:   %d\n", 1);
  PRINTF ("Str_1_Loc:           %s\n", Str_1_Loc);
  PRINTF ("        should be:   DHRYSTONE PROGRAM, 1'ST STRING\n");
  PRINTF ("Str_2_Loc:           %s\n", Str_2_Loc);
  PRINTF ("        should be:   DHRYSTONE PROGRAM, 2'ND STRING\n");
  PRINTF ("\n");

  User_Time = End_Time - Begin_Time;

  if (User_Time < Too_Small_Time)
  {
    PRINTF ("Number_Of_Runs=%d, Begin_Time=%d, End_Time=%d, User_time=%d\n", Number_Of_Runs, Begin_Time, End_Time, User_Time);
    PRINTF ("Measured time too small to obtain meaningful results\n");
    PRINTF ("Please increase number of runs\n");
    PRINTF ("\n");
  }
  else
  {

#ifdef TIME
    Microseconds = (float) User_Time * Mic_secs_Per_Second 
                        / (float) Number_Of_Runs;
    Dhrystones_Per_Second = (float) Number_Of_Runs / (float) User_Time;
#else
#ifndef AJIT
    Microseconds = (float) User_Time * Mic_secs_Per_Second 
                        / ((float) HZ * ((float) Number_Of_Runs));
    Dhrystones_Per_Second = ((float) HZ * (float) Number_Of_Runs)
                        / (float) User_Time;
#else
    Microseconds = (((float) User_Time) * 2.56)/Number_Of_Runs;
    Dhrystones_Per_Second = 1.0e6/Microseconds;
    //Dhrystones_Per_Second = 1.55;
#endif
#endif

    PRINTF ("Number_Of_Runs=%d, Begin_Time=%d, End_Time=%d, User_time=%d\n", Number_Of_Runs, Begin_Time, End_Time, User_Time);
    PRINTF ("Microseconds for one run through Dhrystone: ");
    PRINTF ("%f \n", Microseconds);
    PRINTF ("Dhrystones per Second:                      ");
    PRINTF ("%f \n", Dhrystones_Per_Second);
    PRINTF ("\n");
  }
  
}


void Proc_1 (Ptr_Val_Par)
/******************/

REG Rec_Pointer Ptr_Val_Par;
    /* executed once */
{
  REG Rec_Pointer Next_Record = Ptr_Val_Par->Ptr_Comp;  
                                        /* == Ptr_Glob_Next */
  /* Local variable, initialized with Ptr_Val_Par->Ptr_Comp,    */
  /* corresponds to "rename" in Ada, "with" in Pascal           */
  
  structassign (*Ptr_Val_Par->Ptr_Comp, *Ptr_Glob); 
  Ptr_Val_Par->variant.var_1.Int_Comp = 5;
  Next_Record->variant.var_1.Int_Comp 
        = Ptr_Val_Par->variant.var_1.Int_Comp;
  Next_Record->Ptr_Comp = Ptr_Val_Par->Ptr_Comp;
  Proc_3 (&Next_Record->Ptr_Comp);
    /* Ptr_Val_Par->Ptr_Comp->Ptr_Comp 
                        == Ptr_Glob->Ptr_Comp */
  if (Next_Record->Discr == Ident_1)
    /* then, executed */
  {
    Next_Record->variant.var_1.Int_Comp = 6;
    Proc_6 (Ptr_Val_Par->variant.var_1.Enum_Comp, 
           &Next_Record->variant.var_1.Enum_Comp);
    Next_Record->Ptr_Comp = Ptr_Glob->Ptr_Comp;
    Proc_7 (Next_Record->variant.var_1.Int_Comp, 10, 
           &Next_Record->variant.var_1.Int_Comp);
  }
  else /* not executed */
    structassign (*Ptr_Val_Par, *Ptr_Val_Par->Ptr_Comp);
} /* Proc_1 */


void Proc_2 (Int_Par_Ref)
/******************/
    /* executed once */
    /* *Int_Par_Ref == 1, becomes 4 */

One_Fifty   *Int_Par_Ref;
{
  One_Fifty  Int_Loc;  
  Enumeration   Enum_Loc;

  Int_Loc = *Int_Par_Ref + 10;
  do /* executed once */
    if (Ch_1_Glob == 'A')
      /* then, executed */
    {
      Int_Loc -= 1;
      *Int_Par_Ref = Int_Loc - Int_Glob;
      Enum_Loc = Ident_1;
    } /* if */
  while (Enum_Loc != Ident_1); /* true */
} /* Proc_2 */


void Proc_3 (Ptr_Ref_Par)
/******************/
    /* executed once */
    /* Ptr_Ref_Par becomes Ptr_Glob */

Rec_Pointer *Ptr_Ref_Par;

{
  if (Ptr_Glob != Null)
    /* then, executed */
    *Ptr_Ref_Par = Ptr_Glob->Ptr_Comp;
  Proc_7 (10, Int_Glob, &Ptr_Glob->variant.var_1.Int_Comp);
} /* Proc_3 */


void Proc_4 () /* without parameters */
/*******/
    /* executed once */
{
  Boolean Bool_Loc;

  Bool_Loc = Ch_1_Glob == 'A';
  Bool_Glob = Bool_Loc | Bool_Glob;
  Ch_2_Glob = 'B';
} /* Proc_4 */


void Proc_5 () /* without parameters */
/*******/
    /* executed once */
{
  Ch_1_Glob = 'A';
  Bool_Glob = false;
} /* Proc_5 */


#ifndef AJIT
int main (int argc, char* argv[])
{
	int n = 100;
	if (argc > 1)
		n = atoi(argv[1]);
	run_dhrystone (NDHRYSTONE_ITERS);
	return(0);
}
#else
int  ajit_main (void)
{
	__enable_serial();

	// set cacheable bit in MMU.
	store_word_mmureg(0x100,(uint32_t*) 0x0);
	run_dhrystone (NDHRYSTONE_ITERS);

	halt();
	return 0;
}

#endif


/*
 ****************************************************************************
 *
 *                   "DHRYSTONE" Benchmark Program
 *                   -----------------------------
 *                                                                            
 *  Version:    C, Version 2.1
 *                                                                            
 *  File:       dhry_2.c (part 3 of 3)
 *
 *  Date:       May 25, 1988
 *
 *  Author:     Reinhold P. Weicker
 *
 ****************************************************************************
 */


#ifndef REG
#define REG
        /* REG becomes defined as empty */
        /* i.e. no register variables   */
#endif

extern  int     Int_Glob;
extern  char    Ch_1_Glob;


void Proc_6 (Enum_Val_Par, Enum_Ref_Par)
/*********************************/
    /* executed once */
    /* Enum_Val_Par == Ident_3, Enum_Ref_Par becomes Ident_2 */

Enumeration  Enum_Val_Par;
Enumeration *Enum_Ref_Par;
{
  *Enum_Ref_Par = Enum_Val_Par;
  if (! Func_3 (Enum_Val_Par))
    /* then, not executed */
    *Enum_Ref_Par = Ident_4;
  switch (Enum_Val_Par)
  {
    case Ident_1: 
      *Enum_Ref_Par = Ident_1;
      break;
    case Ident_2: 
      if (Int_Glob > 100)
        /* then */
      *Enum_Ref_Par = Ident_1;
      else *Enum_Ref_Par = Ident_4;
      break;
    case Ident_3: /* executed */
      *Enum_Ref_Par = Ident_2;
      break;
    case Ident_4: break;
    case Ident_5: 
      *Enum_Ref_Par = Ident_3;
      break;
  } /* switch */
} /* Proc_6 */


void Proc_7 (Int_1_Par_Val, Int_2_Par_Val, Int_Par_Ref)
/**********************************************/
    /* executed three times                                      */ 
    /* first call:      Int_1_Par_Val == 2, Int_2_Par_Val == 3,  */
    /*                  Int_Par_Ref becomes 7                    */
    /* second call:     Int_1_Par_Val == 10, Int_2_Par_Val == 5, */
    /*                  Int_Par_Ref becomes 17                   */
    /* third call:      Int_1_Par_Val == 6, Int_2_Par_Val == 10, */
    /*                  Int_Par_Ref becomes 18                   */
One_Fifty       Int_1_Par_Val;
One_Fifty       Int_2_Par_Val;
One_Fifty      *Int_Par_Ref;
{
  One_Fifty Int_Loc;

  Int_Loc = Int_1_Par_Val + 2;
  *Int_Par_Ref = Int_2_Par_Val + Int_Loc;
} /* Proc_7 */


void Proc_8 (Arr_1_Par_Ref, Arr_2_Par_Ref, Int_1_Par_Val, Int_2_Par_Val)
/*********************************************************************/
    /* executed once      */
    /* Int_Par_Val_1 == 3 */
    /* Int_Par_Val_2 == 7 */
Arr_1_Dim       Arr_1_Par_Ref;
Arr_2_Dim       Arr_2_Par_Ref;
int             Int_1_Par_Val;
int             Int_2_Par_Val;
{
  REG One_Fifty Int_Index;
  REG One_Fifty Int_Loc;

  Int_Loc = Int_1_Par_Val + 5;
  Arr_1_Par_Ref [Int_Loc] = Int_2_Par_Val;
  Arr_1_Par_Ref [Int_Loc+1] = Arr_1_Par_Ref [Int_Loc];
  Arr_1_Par_Ref [Int_Loc+30] = Int_Loc;
  for (Int_Index = Int_Loc; Int_Index <= Int_Loc+1; ++Int_Index)
    Arr_2_Par_Ref [Int_Loc] [Int_Index] = Int_Loc;
  Arr_2_Par_Ref [Int_Loc] [Int_Loc-1] += 1;
  Arr_2_Par_Ref [Int_Loc+20] [Int_Loc] = Arr_1_Par_Ref [Int_Loc];
  Int_Glob = 5;
} /* Proc_8 */


Enumeration Func_1 (Ch_1_Par_Val, Ch_2_Par_Val)
/*************************************************/
    /* executed three times                                         */
    /* first call:      Ch_1_Par_Val == 'H', Ch_2_Par_Val == 'R'    */
    /* second call:     Ch_1_Par_Val == 'A', Ch_2_Par_Val == 'C'    */
    /* third call:      Ch_1_Par_Val == 'B', Ch_2_Par_Val == 'C'    */

Capital_Letter   Ch_1_Par_Val;
Capital_Letter   Ch_2_Par_Val;
{
  Capital_Letter        Ch_1_Loc;
  Capital_Letter        Ch_2_Loc;

  Ch_1_Loc = Ch_1_Par_Val;
  Ch_2_Loc = Ch_1_Loc;
  if (Ch_2_Loc != Ch_2_Par_Val)
    /* then, executed */
    return (Ident_1);
  else  /* not executed */
  {
    Ch_1_Glob = Ch_1_Loc;
    return (Ident_2);
   }
} /* Func_1 */


Boolean Func_2 (Str_1_Par_Ref, Str_2_Par_Ref)
/*************************************************/
    /* executed once */
    /* Str_1_Par_Ref == "DHRYSTONE PROGRAM, 1'ST STRING" */
    /* Str_2_Par_Ref == "DHRYSTONE PROGRAM, 2'ND STRING" */

Str_30  Str_1_Par_Ref;
Str_30  Str_2_Par_Ref;
{
  REG One_Thirty        Int_Loc;
      Capital_Letter    Ch_Loc;

  Int_Loc = 2;
  while (Int_Loc <= 2) /* loop body executed once */
    if (Func_1 (Str_1_Par_Ref[Int_Loc],
                Str_2_Par_Ref[Int_Loc+1]) == Ident_1)
      /* then, executed */
    {
      Ch_Loc = 'A';
      Int_Loc += 1;
    } /* if, while */
  if (Ch_Loc >= 'W' && Ch_Loc < 'Z')
    /* then, not executed */
    Int_Loc = 7;
  if (Ch_Loc == 'R')
    /* then, not executed */
    return (true);
  else /* executed */
  {
    if (__strcmp (Str_1_Par_Ref, Str_2_Par_Ref) > 0)
      /* then, not executed */

    {
      Int_Loc += 7;
      Int_Glob = Int_Loc;
      return (true);
    }
    else /* executed */
      return (false);
  } /* if Ch_Loc */
} /* Func_2 */


Boolean Func_3 (Enum_Par_Val)
/***************************/
    /* executed once        */
    /* Enum_Par_Val == Ident_3 */
Enumeration Enum_Par_Val;
{
  Enumeration Enum_Loc=0;

  Enum_Loc = Enum_Par_Val;
  if (Enum_Loc == Ident_3)
    /* then, executed */
    return (true);
  else /* not executed */
    return (false);
} /* Func_3 */

#define haszero(v) (((v) - 0x01010101) & ~(v) & 0x80808080)

void *__memcpy(void *dest, const void *src, size_t n)
{
	int I=0;
	int J=0;

#ifndef DHRYOPT
	uint32_t aligned_8 = ((((uint32_t) dest) & 0x7) | (((uint32_t) src) & 0x7)) == 0;
	if(aligned_8 && (n > 7))
	{
#endif
		uint64_t* cdest_64 = (uint64_t*) dest;
		uint64_t* csrc_64 = (uint64_t*) src;

		// transfer 64-bits at a time as much as possible
		uint64_t S = csrc_64[0];
		do 
		{
			cdest_64[I] = S;
			I++;
			J += 8;
			S = csrc_64[I];
		} while (J < n);
#ifndef DHRYOPT
	}
	else
	{
		uint32_t aligned_4 = ((((uint32_t) dest) & 0x3) | (((uint32_t) src) & 0x3)) == 0;
		if(aligned_4 && (n > 3))
		{
			uint32_t* cdest_32 = (uint32_t*) dest;
			uint32_t* csrc_32  = (uint32_t*) src;

			uint32_t S = csrc_32[0];
			do
			{
				cdest_32[I] = S;
				I++;
				J += 4;
				S = csrc_32[I];
			} while ( J < n);

		}
	}
#endif

	// copy the rest..
	if(J < n)
	{
		uint8_t* cdest_8 = (uint8_t*) dest;
		uint8_t* csrc_8 = (uint8_t*) src;
		do 
		{
			cdest_8[J] = csrc_8[J];
			J++;
		} while(J < n);
	}

	return(dest);
}

char *__strcpy(char *dest, const char *src)
{
	int I;
	I = 0;

#ifndef DHRYOPT
	uint32_t aligned_4 = ((((uint32_t) dest) & 0x3) | (((uint32_t) src) & 0x3)) == 0;
	if(aligned_4)
	{
#endif
		uint32_t* cdest_32 = (uint32_t*) dest;
		uint32_t* csrc_32 = (uint32_t*) src;

		uint32_t S = csrc_32[0];
		uint32_t brk_flag = 0;
		do 
		{
			brk_flag = haszero(S);
	
#ifdef DHRYOPT
			cdest_32[I] = S;
#else

			uint32_t b3 = (S & 0x000000ff); // first character
			uint32_t b2 = (S & 0x0000ff00);
			uint32_t b1 = (S & 0x00ff0000);
			uint32_t b0 = (S & 0xff000000); // last character.

			uint8_t cp_word = (b3 && b2 && b1);
			if(cp_word)	
			{
				cdest_32[I] = S;
			}
			else 
			{
			    int J = I << 2;
			    dest[J] = b3;
			    if(b3)
			    {
				dest[J+1] = (b2 >> 8);
				if (b2)
				{
					dest[J+2] = (b1 >> 16);
					if(b1) 
					{
						dest[J+3] = (b0 >> 24);
					}
				}
			    }
			    break;
			}
#endif // DHRYOPT

			I++;
			S = csrc_32[I];
		} while (!brk_flag);
#ifndef DHRYOPT
	}
	else
	{
		uint8_t S;
		do {
			S = *src++;	
			*dest++ = S;
		} while (S != 0);
			
	}
#endif
	return(dest);
}

int __strcmp(const char *s1, const char *s2)
{
	register int ret_val = 0;
	int I;
	I = 0;

#ifndef DHRYOPT
	uint32_t aligned_4 = ((((uint32_t) s1) & 0x3) | (((uint32_t) s2) & 0x3)) == 0;
	if(aligned_4)
	{
#endif
		uint32_t* S1_32 = (uint32_t*) s1;
		uint32_t* S2_32 = (uint32_t*) s2;

		uint32_t brk_flag = 0;
		do 
		{
			uint32_t S = S1_32[I];
			uint32_t D = S2_32[I];

			ret_val = (S-D);

			if(ret_val | haszero(S))
				brk_flag = 1;

			I++;
		} while (!brk_flag);
#ifndef DHRYOPT
	}
	else
		// byte-by-byte..
	{
		unsigned char c1, c2;
		do
		{
			c1 = (unsigned char) *s1++;
			c2 = (unsigned char) *s2++;
			if (c1 == '\0')
			{
				ret_val = c1 - c2;
				break;
			}
		}
		while (c1 == c2);
	}
#endif

	return(ret_val);
}
