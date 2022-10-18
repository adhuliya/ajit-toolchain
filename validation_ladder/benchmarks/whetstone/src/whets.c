/*
 *  Document:         Whets.c 
 *  File Group:       Classic Benchmarks
 *  Creation Date:    6 November 1996
 *  Revision Date:    
 *
 *  Title:            Whetstone Benchmark in C/C++
 *  Keywords:         WHETSTONE BENCHMARK PERFORMANCE MIPS
 *                    MWIPS MFLOPS
 *
 *  Abstract:         C or C++ version of Whetstone one of the
 *                    Classic Numeric Benchmarks with example
 *                    results on P3 to P6 based PCs.        
 *
 *  Contributor:      Roy Longbottom 101323.2241@compuserve.com
 *                         or     Roy_Longbottom@compuserve.com
 *
 ************************************************************
 *
 *     C/C++ Whetstone Benchmark Single or Double Precision
 *
 *     Original concept        Brian Wichmann NPL      1960's
 *     Original author         Harold Curnow  CCTA     1972
 *     Self timing versions    Roy Longbottom CCTA     1978/87
 *     Optimisation control    Bangor University       1987/90
 *     C/C++ Version           Roy Longbottom          1996
 *     Compatibility & timers  Al Aburto               1996
 *
 ************************************************************
 *
 *              Official version approved by:
 *
 *         Harold Curnow  100421.1615@compuserve.com
 *
 *      Happy 25th birthday Whetstone, 21 November 1997
 *
 ************************************************************
 *
 *     The program normally runs for about 100 seconds
 *     (adjustable in main - variable duration). This time
 *     is necessary because of poor PC clock resolution.
 *     The original concept included such things as a given
 *     number of subroutine calls and divides which may be
 *     changed by optimisation. For comparison purposes the
 *     compiler and level of optimisation should be identified.
 *       
 ************************************************************
 *
 *     The original benchmark had a single variable I which
 *     controlled the running time. Constants with values up
 *     to 899 were multiplied by I to control the number
 *     passes for each loop. It was found that large values
 *     of I could overflow index registers so an extra outer
 *     loop with a second variable J was added.
 *
 *     Self timing versions were produced during the early
 *     days. The 1978 changes supplied timings of individual
 *     loops and these were used later to produce MFLOPS and
 *     MOPS ratings.
 *
 *     1987 changes converted the benchmark to Fortran 77
 *     standards and removed redundant IF statements and
 *     loops to leave the 8 active loops N1 to N8. Procedure
 *     P3 was changed to use global variables to avoid over-
 *     optimisation with the first two statements changed from
 *     X1=X and Y1=Y to X=Y and Y=Z. A self time calibrating
 *     version for PCs was also produced, the facility being
 *     incorporated in this version.
 *
 *     This version has changes to avoid worse than expected
 *     speed ratings, due to underflow, and facilities to show
*     that consistent numeric output is produced with varying
*     optimisation levels or versions in different languages.
*
*     Some of the procedures produce ever decreasing numbers.
*     To avoid problems, variables T and T1 have been changed
*     from 0.499975 and 0.50025 to 0.49999975 and 0.50000025.
*
*     Each section now has its own double loop. Inner loops
*     are run 100 times the loop constants. Calibration
*     determines the number of outer loop passes. The
*     numeric results produced in the main output are for
*     one pass on the outer loop. As underflow problems were
*     still likely on a processor 100 times faster than a 100
*     MHz Pentium, three sections have T=1.0-T inserted in the
*     outer loop to avoid the problem. The two loops avoid
*     index register overflows.
*
*     The first section is run ten times longer than required
*     for accuracy in calculating MFLOPS. This time is divided
*     by ten for inclusion in the MWIPS calculations.
*
*     This version has facilities for typing in details of the
*     particular run. This information is appended to file
*     whets.res along with the results.
*
*     Roy Longbottom  101323.2241@compuserve.com
*
************************************************************
*
*     Whetstone benchmark results are available in whets.tbl
*     from ftp.nosc.mil/pub/aburto. The results include
*     further details of the benchmarks.
*
************************************************************
*
*     Source code is available in C/C++, Fortran, Basic and
*     Visual Basic in the same format as this version. Pre-
*     compiled versions for PCs are also available via C++.
*     These comprise optimised and non-optimised versions
*     for DOS, Windows and NT.
*
*     This version compiles and runs correctly either as a
*     C or CPP program with a WATCOM and Borland compiler.
*
************************************************************
	*
* Example of initial calibration display (Pentium 100 MHz)
	*
	* Single Precision C/C++ Whetstone Benchmark
	*
	* Calibrate
	*      0.17 Seconds          1   Passes (x 100)
	*      0.77 Seconds          5   Passes (x 100)
*      3.70 Seconds         25   Passes (x 100)
	*
* Use 676  passes (x 100)
	*
	* 676 passes are used for an approximate duration of 100
	* seconds, providing an initial estimate of a speed rating
	* of 67.6 MWIPS.
	*
	* This is followed by the table of results as below. Input
	* statements are then supplied to type in the run details.
	*
	************************************************************
	* 
	* Examples of results from file whets.res
	*
	* Whetstone Single  Precision Benchmark in C/C++
	*
	* Month run         4/1996
	* PC model          Escom
	* CPU               Pentium
	* Clock MHz         100
	* Cache             256K
	* H/W Options       Neptune chipset
	* OS/DOS            Windows 95
	* Compiler          Watcom C/C++ 10.5  Win386
	* Options           No optimisation
	* Run by            Roy Longbottom
	* From              UK
	* Mail              101323.2241@compuserve.com
	*
	* Loop content                 Result            MFLOPS     MOPS   Seconds
	*
	* N1 floating point    -1.12475025653839100      19.971              0.274
	* N2 floating point    -1.12274754047393800      11.822              3.240
	* N3 if then else       1.00000000000000000               11.659     2.530
	* N4 fixed point       12.00000000000000000               13.962     6.430
	* N5 sin,cos etc.       0.49904659390449520                2.097    11.310
	* N6 floating point     0.99999988079071040       3.360             45.750
	* N7 assignments        3.00000000000000000                2.415    21.810
	* N8 exp,sqrt etc.      0.75110864639282230                1.206     8.790
	*
	* MWIPS                                          28.462            100.134
	*
	* Whetstone Single  Precision Benchmark in C/C++
	*
	* Compiler          Watcom C/C++ 10.5  Win386
	* Options           -otexan -zp4 -om -fp5 -5r
	*
	* Loop content                 Result            MFLOPS     MOPS    Seconds
	*
	* N1 floating point    -1.12475025653839100      26.751               0.478
	* N2 floating point    -1.12274754047393800      17.148               5.220
	* N3 if then else       1.00000000000000000               19.922      3.460
	* N4 fixed point       12.00000000000000000               15.978     13.130
	* N5 sin,cos etc.       0.49904659390449520                2.663     20.810
	* N6 floating point     0.99999988079071040      10.077              35.650
	* N7 assignments        3.00000000000000000               22.877      5.380
	* N8 exp,sqrt etc.      0.75110864639282230                1.513     16.370
	*
	* MWIPS                                          66.270             100.498
	*
	*
	* Whetstone Double  Precision Benchmark in C/C++
	*
	* Compiler          Watcom C/C++ 10.5 Win32NT 
	* Options           -otexan -zp4 -om -fp5 -5r
	*
	* Loop content                 Result           MFLOPS      MOPS   Seconds
	*
	* N1 floating point    -1.12398255667391900     26.548               0.486
	* N2 floating point    -1.12187079889284400     16.542               5.460
	* N3 if then else       1.00000000000000000               19.647     3.540
	* N4 fixed point       12.00000000000000000               15.680    13.500
	* N5 sin,cos etc.       0.49902937281515140                3.019    18.520
	* N6 floating point     0.99999987890802820      9.977              36.330
	* N7 assignments        3.00000000000000000               22.620     5.490
	* N8 exp,sqrt etc.      0.75100163018457870                1.493    16.740
	*
	* MWIPS                                         67.156             100.066
	*
	*  Note different numeric results to single precision. Slight variations
	*  are normal with different compilers and sometimes optimisation levels. 
	*
	**************************************************************************
	*
*       Example results via Watcom C/C++ 10.5 Win386 (P6 Win32NT)
	*
	*
	*            Single Precision Non-optimised Results -dMSC
	*
	*     MWIPS   MFLOPS  MFLOPS  MFLOPS  COS     EXP     FIXPT   IF     EQUAL
	* Key           1       2       3     MOPS    MOPS    MOPS    MOPS    MOPS
	*                                                               
	* P3  3.07    0.860   0.815   0.328   0.355   0.160   1.70    1.32   0.264
	* P4  10.0    4.68    3.51    1.27    0.482   0.298   5.73    5.20    1.18
	* P5  28.5    20.0    11.8    3.36    2.10    1.21    14.0    11.7    2.42
	* P6  81.7    47.5    37.8    10.9    3.91    2.43    51.2    42.8    7.85
	*
	*
	*    Single Precision Optimised Results -otexan -zp4 -om -fp5 -5r -dMSC
	*                                                               
	*     MWIPS   MFLOPS  MFLOPS  MFLOPS  COS     EXP     FIXPT   IF     EQUAL
	* Key           1       2       3     MOPS    MOPS    MOPS    MOPS    MOPS
	*                                                               
	* P3  5.68    0.928   0.884   0.673   0.461   0.275   2.36    2.16   0.638
	* P4  16.4    5.09    4.03    2.66    0.526   0.342   6.36    6.00    5.28
	* P5  66.3    26.8    17.1    10.1    2.66    1.51    16.0    19.9    22.9
	* P6  161     50.3    45.2    31.5    4.46    2.77    102     20.6    119
	*
	*                                                                
	*  Double Precision Optimised Results -otexan -zp4 -om -fp5 -5r -dMSC -dDP
	*                                                                                                                                
	*     MWIPS   MFLOPS  MFLOPS  MFLOPS  COS     EXP     FIXPT   IF     EQUAL
	* Key           1       2       3     MOPS    MOPS    MOPS    MOPS    MOPS
	*                                                               
	* P3  5.20    0.818   0.775   0.604   0.525   0.268   2.20    2.05   0.538
	* P4  16.5    4.74    3.76    2.51    0.627   0.343   6.22    6.45    4.09
	* P5  67.9    26.9    16.7    10.1    3.06    1.51    15.8    19.9    22.8
	* P6  167     50.3    43.5    31.5    5.37    2.83    81.3    20.6    119                                                                
	*
	*
	*                             Systems  
	*       
	* Key System       CPU     MHz   Cache    Options          OS
	*       
	* P3  Clone     AM80386DX  40    128K   with 387        Windows 95
	* P4  Escom,    80486DX2   66.7  128K   CIS chipset     Windows 95
	* P5  Escom,    Pentium   100    256K   Neptune chipset Windows 95
	* P6  Dell Pro  PentPro   200    256K   440FX PCIset    NT 3.51
	*
	**************************************************************************
	*
	*                       Running Instructions
	*
	*      1.  In order to compile successfully, include timer option as
	*          indicated below.
	*      2.  If pre-compiled codes are to be distributed, compile with the
	*          -DPRECOMP option or uncomment #define PRECOMP at PRECOMPILE
	*          below. Also insert compiler name and optimisation details
	*          at #define precompiler and #define preoptions.
	*      3.  Compile and run for single precision results
	*      4.  Compile with -DDP option or uncomment #define DP at PRECISION
	*          below and run for double precision results.
*      5.  Run with maximum and no optimisation (minimum debug)
	*      6.  Notify Roy Longbottom of other necessary changes
	*      7.  Send results file whets.res to Roy Longbottom - with one
	*          sample of each run and system details fully completed
	*
	*      Roy Longbottom  101323.2241@compuserve.com    6 November 1996
	*
	**************************************************************************
	*/

#include <math.h>       /* for sin, exp etc.           */
#include <stdio.h>      /* standard I/O                */ 
#include <string.h>     /* for strcpy - 3 occurrences  */
#include <stdlib.h>     /* for exit   - 1 occurrence   */

	/***************************************************************/
	/* Timer options. You MUST uncomment one of the options below  */
	/* or compile, for example, with the '-DUNIX' option.          */
	/***************************************************************/
	/* #define Amiga       */
	/* #define UNIX        */
	/* #define UNIX_Old    */
	/* #define VMS         */
	/* #define BORLAND_C   */
	/* #define MSC         */
	/* #define MAC         */
	/* #define IPSC        */
	/* #define FORTRAN_SEC */
	/* #define GTODay      */
	/* #define CTimer      */
	/* #define UXPM        */
	/* #define MAC_TMgr    */
	/* #define PARIX       */
	/* #define POSIX       */
	/* #define WIN32       */


	/*PRECISION PRECISION PRECISION PRECISION PRECISION PRECISION PRECISION*/

	/* #define DP */

#ifdef DP 
#define SPDP double
#define Precision "Double"
#else
#define SPDP float
#define Precision "Single"
#endif



	SPDP dtime();
	void whetstones(long xtra, long x100, int calibrate);  
	void pa(SPDP e[4], SPDP t, SPDP t2);
	void po(SPDP e1[4], long j, long k, long l);
	void p3(SPDP *x, SPDP *y, SPDP *z, SPDP t, SPDP t1, SPDP t2);
	void pout(char title[22], float ops, int type, SPDP checknum,
			SPDP time, int calibrate, int section);


SPDP loop_time[9];
SPDP loop_mops[9];
SPDP loop_mflops[9];
SPDP TimeUsed;
SPDP mwips;
char headings[9][19];
SPDP Check;
SPDP results[9];
SPDP run_times[9];

#ifdef AJIT
#include <core_portme.h>
#include "ajit_access_routines.h"
#define PRINTF ee_printf
#define EE_TICKS_PER_SEC (100000000.0/256)
//#define EE_TICKS_PER_SEC (1000.0/256)
#else
#define PRINTF printf
#endif

int main()
{
	int count = 10;
	int calibrate = 1;
	long xtra = 1;
	int section;
	long x100 = 100;
	int duration = 100;


#ifdef AJIT
	__ajit_write_serial_control_register__ ( TX_ENABLE );
#endif 
		
	PRINTF("AJIT Whetstone Run\n");

#ifdef PRINTON
	PRINTF("\n");
	PRINTF("##########################################\n"); 
	PRINTF("%s Precision C/C++ Whetstone Benchmark\n\n", Precision);

	PRINTF("Calibrate\n");
#endif
	do
	{
		TimeUsed=0;

		whetstones(xtra,x100,calibrate);

#ifdef PRINTON
		PRINTF("%11.2f Seconds %10.0lf   Passes (x 100)\n",
				TimeUsed,(SPDP)(xtra));
#endif

		calibrate++;
		count--;

		if (TimeUsed > 2.0)
		{
			count = 0;
		}
		else
		{
			xtra = xtra * 5;
		}
	}

	while (count > 0);

	if (TimeUsed > 0) xtra = (long)((SPDP)(duration * xtra) / TimeUsed);
	if (xtra < 1) xtra = 1;

	calibrate = 0;

#ifdef PRINTON
	PRINTF("\nUse %d  passes (x 100)\n", xtra);
	PRINTF("\n          %s Precision C/C++ Whetstone Benchmark",Precision);
	PRINTF("\n");
	PRINTF("\nLoop content                  Result              MFLOPS "
			"     MOPS   Seconds\n\n");
#endif

	TimeUsed=0;
	whetstones(xtra,x100,calibrate);
		
	PRINTF("***\n");
#ifdef PRINTON
	PRINTF("\nTimeUsed=%f\n", TimeUsed);
	PRINTF("\nMWIPS            ");
#endif
	if (TimeUsed>0)
	{
		mwips=(float)(xtra) * (float)(x100) / (10 * TimeUsed);
#ifdef PRINTON
		PRINTF("mwips=%f\n", mwips);
#endif
	}
	else
	{
		mwips = 0;
	}  

#ifdef PRINTON
	PRINTF("%9.3f %9.3f (%d,%d)\n\n",mwips,TimeUsed,xtra,x100);
	if (Check == 0) PRINTF("Wrong answer  ");
#endif


	/************************************************************************/
	/*             Type details of hardware, software etc.                  */
	/************************************************************************/

#ifdef PRINTON
	PRINTF ("Enter the following which will be added with results to file WHETS.RES\n");
	PRINTF ("When submitting a number of results you need only provide details once\n");
	PRINTF ("but a cross reference such as an abbreviated CPU type would be useful.\n");    
	PRINTF ("You can kill (exit or close) the program now and no data will be added.\n\n");
#endif



	/************************************************************************/
	/*               Add results to output file whets.res                   */
	/************************************************************************/
#ifdef PRINTON
	PRINTF ("\n"); 
	PRINTF ( "##############################################\n");
	PRINTF ( "Whetstone %s  Precision Benchmark in C/C++\n\n",Precision);
	PRINTF ("Date: 2019      \n");
	PRINTF ("Computer: AJIT prototype system 1 (with 4MB SRAM)  \n");
	PRINTF ("CPU chip: AJIT v0 \n");
	PRINTF ("Clock MHz: 100  \n");
	PRINTF ("Cache size: 32kB (I), 32kB (D)\n");
	PRINTF ("H/W options: MMU enabled.\n");
	PRINTF ("OS version: none\n");
	PRINTF ("Compiler: gcc  \n");
	PRINTF ("Options:   -O3 \n");
	PRINTF ("Your name:  Madhav Desai \n");
	PRINTF ("From:     IIT Bombay \n");
	PRINTF ("Email:    madhav@ee.iitb.ac.in\n");

	PRINTF ("Loop content                   Result"
			"              MFLOPS      MOPS   Seconds\n\n"); 

	for (section=1; section<9; section++)
	{
		PRINTF ("%s  %24.17f   ", headings[section], results[section]);
		if (loop_mops[section] == 99999)
		{          
			PRINTF ("  %9.3f           %9.3f\n", loop_mflops[section], loop_time[section]);
		}
		else
		{       
			PRINTF ( "            %9.3f %9.3f\n", loop_mops[section], loop_time[section], results[section]);
		}
	}

	PRINTF ( "\nMWIPS             ");
	PRINTF ( "%39.3f%20.3f\n\n",mwips,TimeUsed);
	PRINTF ( "Results  to  load  to  spreadsheet             ");
	PRINTF ( "     MWIPS   Mflops1   Mflops2   Mflops3   Cosmops"
			"   Expmops  Fixpmops    Ifmops    Eqmops\n");
	PRINTF ( "Results  to  load  to  spreadsheet             ");   

	PRINTF ( " %9.3f %9.3f %9.3f", mwips, loop_mflops[1],
			loop_mflops[2]);
	PRINTF ( " %9.3f %9.3f %9.3f", loop_mflops[6],
			loop_mops[5], loop_mops[8]);
	PRINTF ( " %9.3f %9.3f %9.3f\n\n", loop_mops[4],
			loop_mops[3], loop_mops[7]);

	PRINTF ("\n");
#endif

	for(section=1; section < 9; section++)
	{
		PRINTF("%d. %f, %f\n", section, results[section], run_times[section]);
	}
	return(0);
}

void whetstones(long xtra, long x100, int calibrate)
{

	long n1,n2,n3,n4,n5,n6,n7,n8,i,ix,n1mult;
	SPDP x,y,z;              
	long j,k,l;
	SPDP e1[4],timea,timeb, dtime();

	SPDP t =  0.49999975;
	SPDP t0 = t;        
	SPDP t1 = 0.50000025;
	SPDP t2 = 2.0;

	Check=0.0;

	n1 = 12*x100;
	n2 = 14*x100;
	n3 = 345*x100;
	n4 = 210*x100;
	n5 = 32*x100;
	n6 = 899*x100;
	n7 = 616*x100;
	n8 = 93*x100;
	n1mult = 10;

	/* Section 1, Array elements */

	e1[0] = 1.0;
	e1[1] = -1.0;
	e1[2] = -1.0;
	e1[3] = -1.0;
	timea = dtime();
	{
		for (ix=0; ix<xtra; ix++)
		{
			for(i=0; i<n1*n1mult; i++)
			{
				e1[0] = (e1[0] + e1[1] + e1[2] - e1[3]) * t;
				e1[1] = (e1[0] + e1[1] - e1[2] + e1[3]) * t;
				e1[2] = (e1[0] - e1[1] + e1[2] + e1[3]) * t;
				e1[3] = (-e1[0] + e1[1] + e1[2] + e1[3]) * t;
			}
			t = 1.0 - t;
		}
		t =  t0;                    
	}
	timeb = (dtime()-timea)/((SPDP)(n1mult));
	pout("N1 floating point\0",(float)(n1*16)*(float)(xtra),
			1,e1[3],timeb,calibrate,1);


	/* Section 2, Array as parameter */

	timea = dtime();
	{
		for (ix=0; ix<xtra; ix++)
		{ 
			for(i=0; i<n2; i++)
			{
				pa(e1,t,t2);
			}
			t = 1.0 - t;
		}
		t =  t0;
	}
	timeb = dtime()-timea;
	pout("N2 floating point\0",(float)(n2*96)*(float)(xtra),
			1,e1[3],timeb,calibrate,2);

	/* Section 3, Conditional jumps */
	j = 1;
	timea = dtime();
	{
		for (ix=0; ix<xtra; ix++)
		{
			for(i=0; i<n3; i++)
			{
				if(j==1)       j = 2;
				else           j = 3;
				if(j>2)        j = 0;
				else           j = 1;
				if(j<1)        j = 1;
				else           j = 0;
			}
		}
	}
	timeb = dtime()-timea;
	pout("N3 if then else  \0",(float)(n3*3)*(float)(xtra),
			2,(SPDP)(j),timeb,calibrate,3);

	/* Section 4, Integer arithmetic */
	j = 1;
	k = 2;
	l = 3;
	timea = dtime();
	{
		for (ix=0; ix<xtra; ix++)
		{
			for(i=0; i<n4; i++)
			{
				j = j *(k-j)*(l-k);
				k = l * k - (l-j) * k;
				l = (l-k) * (k+j);
				e1[l-2] = j + k + l;
				e1[k-2] = j * k * l;
			}
		}
	}
	timeb = dtime()-timea;
	x = e1[0]+e1[1];
	pout("N4 fixed point   \0",(float)(n4*15)*(float)(xtra),
			2,x,timeb,calibrate,4);

	/* Section 5, Trig functions */
	x = 0.5;
	y = 0.5;
	timea = dtime();
	{
		for (ix=0; ix<xtra; ix++)
		{
			for(i=1; i<n5; i++)
			{
				x = t*atan(t2*sin(x)*cos(x)/(cos(x+y)+cos(x-y)-1.0));
				y = t*atan(t2*sin(y)*cos(y)/(cos(x+y)+cos(x-y)-1.0));
			}
			t = 1.0 - t;
		}
		t = t0;
	}
	timeb = dtime()-timea;
	pout("N5 sin,cos etc.  \0",(float)(n5*26)*(float)(xtra),
			2,y,timeb,calibrate,5);

	/* Section 6, Procedure calls */
	x = 1.0;
	y = 1.0;
	z = 1.0;
	timea = dtime();
	{
		for (ix=0; ix<xtra; ix++)
		{
			for(i=0; i<n6; i++)
			{
				p3(&x,&y,&z,t,t1,t2);
			}
		}
	}
	timeb = dtime()-timea;
	pout("N6 floating point\0",(float)(n6*6)*(float)(xtra),
			1,z,timeb,calibrate,6);

	/* Section 7, Array refrences */
	j = 0;
	k = 1;
	l = 2;
	e1[0] = 1.0;
	e1[1] = 2.0;
	e1[2] = 3.0;
	timea = dtime();
	{
		for (ix=0; ix<xtra; ix++)
		{
			for(i=0;i<n7;i++)
			{
				po(e1,j,k,l);
			}
		}
	}
	timeb = dtime()-timea;
	pout("N7 assignments   \0",(float)(n7*3)*(float)(xtra),
			2,e1[2],timeb,calibrate,7);

	/* Section 8, Standard functions */
	x = 0.75;
	timea = dtime();
#ifdef PRINTON
	PRINTF("N8: timea=%f\n",timea);
#endif
	{
		for (ix=0; ix<xtra; ix++)
		{
			for(i=0; i<n8; i++)
			{
				x = sqrt(exp(log(x)/t1));
			}
		}
	}
#ifdef PRINTON
	PRINTF("N8: timea=%f\n",timea);
#endif
	timeb = dtime()-timea;
#ifdef PRINTON
	PRINTF("N8: timea=%f, timeb=%f\n", timea, timeb);
#endif
	pout("N8 exp,sqrt etc. \0",(float)(n8*4)*(float)(xtra),
			2,x,timeb,calibrate,8);

	return;
}


void pa(SPDP e[4], SPDP t, SPDP t2)
{
	long j;
	for(j=0;j<6;j++)
	{
		e[0] = (e[0]+e[1]+e[2]-e[3])*t;
		e[1] = (e[0]+e[1]-e[2]+e[3])*t;
		e[2] = (e[0]-e[1]+e[2]+e[3])*t;
		e[3] = (-e[0]+e[1]+e[2]+e[3])/t2;
	}

	return;
}

void po(SPDP e1[4], long j, long k, long l)
{
	e1[j] = e1[k];
	e1[k] = e1[l];
	e1[l] = e1[j];
	return;
}

void p3(SPDP *x, SPDP *y, SPDP *z, SPDP t, SPDP t1, SPDP t2)
{
	*x = *y;
	*y = *z;
	*x = t * (*x + *y);
	*y = t1 * (*x + *y);
	*z = (*x + *y)/t2;
	return;
}


void pout(char title[19], float ops, int type, SPDP checknum,
		SPDP time, int calibrate, int section)
{
	SPDP mops,mflops;

	Check = Check + checknum;
	loop_time[section] = time;
	strcpy (headings[section],title);
	TimeUsed =  TimeUsed + time;
	if (calibrate == 1)
	{
		results[section] = checknum;
		run_times[section] = time;
	}
	if (calibrate == 0)
	{              
#ifdef PRINTON
		PRINTF("%s %24.17f    ",headings[section],results[section]);    
#endif

		if (type == 1)
		{
			if (time>0)
			{
				mflops = ops/(1000000L*time);
			}
			else
			{
				mflops = 0;
			}
			loop_mops[section] = 99999;
			loop_mflops[section] = mflops;
#ifdef PRINTON
			PRINTF(" %9.3f          %9.3f\n",
					loop_mflops[section], loop_time[section]);                
#endif
		}
		else
		{
			if (time>0)
			{
				mops = ops/(1000000L*time);
			}
			else
			{
				mops = 0;
			}
			loop_mops[section] = mops;
			loop_mflops[section] = 0;                 
#ifdef PRINTON
			PRINTF("           %9.3f%9.3f\n",
					loop_mops[section], loop_time[section]);
#endif
		}
	}

	return;
}


/*****************************************************/
/* Various timer routines.                           */
/* Al Aburto, aburto@nosc.mil, 08 Oct 1996           */
/*                                                   */
/* t = dtime() outputs the current time in seconds.  */
/* Use CAUTION as some of these routines will mess   */
/* up when timing across the hour mark!!!            */
/*                                                   */
/* For timing I use the 'user' time whenever         */
/* possible. Using 'user+sys' time is a separate     */
/* issue.                                            */
/*                                                   */
/* Example Usage:                                    */
/* [timer options added here]                        */
/* main()                                            */
/* {                                                 */
/*  double starttime,benchtime,dtime();              */
/*                                                   */
/*  starttime = dtime();                             */ 
/*  [routine to time]                                */
/*  benchtime = dtime() - starttime;                 */
/* }                                                 */
/*                                                   */
/* [timer code below added here]                     */
/*****************************************************/

/*********************************/
/* Timer code.                   */
/*********************************/
/*******************/
/*  Amiga dtime()  */
/*******************/
#ifdef Amiga
#include <ctype.h>
#define HZ 50

SPDP dtime()
{
	SPDP q;

	struct tt
	{
		long  days;
		long  minutes;
		long  ticks;
	} tt;

	DateStamp(&tt);

	q = ((SPDP)(tt.ticks + (tt.minutes * 60L * 50L))) / (SPDP)HZ;

	return q;
}
#endif

/*****************************************************/
/*  UNIX dtime(). This is the preferred UNIX timer.  */
/*  Provided by: Markku Kolkka, mk59200@cc.tut.fi    */
/*  HP-UX Addition by: Bo Thide', bt@irfu.se         */
/*****************************************************/
#ifdef UNIX
#include <sys/time.h>
#include <sys/resource.h>

#ifdef hpux
#include <sys/syscall.h>
#define getrusage(a,b) syscall(SYS_getrusage,a,b)
#endif

struct rusage rusage;

SPDP dtime()
{
	SPDP q;

	getrusage(RUSAGE_SELF,&rusage);

	q = (SPDP)(rusage.ru_utime.tv_sec);
	q = q + (SPDP)(rusage.ru_utime.tv_usec) * 1.0e-06;

	return q;
}
#endif

/***************************************************/
/*  UNIX_Old dtime(). This is the old UNIX timer.  */
/*  Use only if absolutely necessary as HZ may be  */
/*  ill defined on your system.                    */
/***************************************************/
#ifdef UNIX_Old
#include <sys/types.h>
#include <sys/times.h>
#include <sys/param.h>

#ifndef HZ
#define HZ 60
#endif

struct tms tms;

SPDP dtime()
{
	SPDP q;

	times(&tms);

	q = (SPDP)(tms.tms_utime) / (SPDP)HZ;

	return q;
}
#endif

/*********************************************************/
/*  VMS dtime() for VMS systems.                         */
/*  Provided by: RAMO@uvphys.phys.UVic.CA                */
/*  Some people have run into problems with this timer.  */
/*********************************************************/
#ifdef VMS
#include time

#ifndef HZ
#define HZ 100
#endif

struct tbuffer_t
{
	int proc_user_time;
	int proc_system_time;
	int child_user_time;
	int child_system_time;
};
struct tbuffer_t tms;

SPDP dtime()
{
	SPDP q;

	times(&tms);

	q = (SPDP)(tms.proc_user_time) / (SPDP)HZ;

	return q;
}
#endif

/******************************/
/*  BORLAND C dtime() for DOS */
/******************************/
#ifdef BORLAND_C
#include <ctype.h>
#include <dos.h>
#include <time.h>



#define HZ 100
struct time tnow;

SPDP dtime()
{
	SPDP q;

	gettime(&tnow);

	q = 60.0 * (SPDP)(tnow.ti_min);
	q = q + (SPDP)(tnow.ti_sec);
	q = q + (SPDP)(tnow.ti_hund)/(SPDP)HZ;

	return q;
}
#endif

#ifdef AJIT
/*****************************************************/
/* Time routine for AJIT */
/* Ref: "POSIX Programmer's Guide"  O'Reilly & Assoc.*/
/*****************************************************/
SPDP __attribute__((optimize("O0"))) dtime()
{

#ifndef FAKECLOCK
	uint32_t uq = ajit_barebones_clock();
	SPDP ret_val = ((SPDP) uq)*(1.0/((SPDP)EE_TICKS_PER_SEC));
	// PRINTF("dtime: uq=0x%x, ret_val=%f\n", uq, ret_val);
	return (ret_val);
#else
	static SPDP curr_time = 0.0;
	curr_time += 5.0;
	return(curr_time);
#endif

}
#endif

/***************************************/
/*  Microsoft C (MSC) dtime() for DOS  */
/*  Also suitable for Watcom C/C++ and */
/*  some other PC compilers            */
/***************************************/
#ifdef MSC
#include <time.h>
#include <ctype.h>

#define HZ CLOCKS_PER_SEC
clock_t tnow;

SPDP dtime()
{
	SPDP q;

	tnow = clock();
	q = (SPDP)tnow / (SPDP)HZ;
	return q;
}
#endif

/*************************************/
/*  Macintosh (MAC) Think C dtime()  */
/*************************************/
#ifdef MAC
#include <time.h>

#define HZ 60

SPDP dtime()
{
	SPDP q;

	q = (SPDP)clock() / (SPDP)HZ;

	return q;
}
#endif

/************************************************************/
/*  iPSC/860 (IPSC) dtime() for i860.                       */
/*  Provided by: Dan Yergeau, yergeau@gloworm.Stanford.EDU  */
/************************************************************/
#ifdef IPSC
extern double dclock();

SPDP dtime()
{
	SPDP q;

	q = dclock();

	return q;
}
#endif

/**************************************************/
/*  FORTRAN dtime() for Cray type systems.        */
/*  This is the preferred timer for Cray systems. */
/**************************************************/
#ifdef FORTRAN_SEC

fortran double second();

SPDP dtime()
{
	SPDP q;

	second(&q);

	return q;
}
#endif

/***********************************************************/
/*  UNICOS C dtime() for Cray UNICOS systems.  Don't use   */
/*  unless absolutely necessary as returned time includes  */
/*  'user+system' time.  Provided by: R. Mike Dority,      */
/*  dority@craysea.cray.com                                */
/***********************************************************/
#ifdef CTimer
#include <time.h>

SPDP dtime()
{
	SPDP q;
	clock_t   clock(void);

	q = (SPDP)clock() / (SPDP)CLOCKS_PER_SEC;

	return q;
}
#endif

/********************************************/
/* Another UNIX timer using gettimeofday(). */
/* However, getrusage() is preferred.       */
/********************************************/
#ifdef GTODay
#include <sys/time.h>

struct timeval tnow;

SPDP dtime()
{
	SPDP q;

	gettimeofday(&tnow,NULL);
	q = (SPDP)tnow.tv_sec + (SPDP)tnow.tv_usec * 1.0e-6;

	return q;
}
#endif

/*****************************************************/
/*  Fujitsu UXP/M timer.                             */
/*  Provided by: Mathew Lim, ANUSF, M.Lim@anu.edu.au */
/*****************************************************/
#ifdef UXPM
#include <sys/types.h>
#include <sys/timesu.h>
struct tmsu rusage;

SPDP dtime()
{
	SPDP q;

	timesu(&rusage);

	q = (SPDP)(rusage.tms_utime) * 1.0e-06;

	return q;
}
#endif

/**********************************************/
/*    Macintosh (MAC_TMgr) Think C dtime()    */
/*   requires Think C Language Extensions or  */
/*    #include <MacHeaders> in the prefix     */
/*  provided by Francis H Schiffer 3rd (fhs)  */
/*         skipschiffer@genie.geis.com        */
/**********************************************/
#ifdef MAC_TMgr
#include <Timer.h>
#include <stdlib.h>

static TMTask   mgrTimer;
static Boolean  mgrInited = false;
static SPDP     mgrClock;

#define RMV_TIMER RmvTime( (QElemPtr)&mgrTimer )
#define MAX_TIME  1800000000L
/* MAX_TIME limits time between calls to */
/* dtime( ) to no more than 30 minutes   */
/* this limitation could be removed by   */
/* creating a completion routine to sum  */
/* 30 minute segments (fhs 1994 feb 9)   */

static void Remove_timer( )
{
	RMV_TIMER;
	mgrInited = false;
}

SPDP dtime( )
{
	if( mgrInited ) {
		RMV_TIMER;
		mgrClock += (MAX_TIME + mgrTimer.tmCount)*1.0e-6;
	} else {
		if( _atexit( &Remove_timer ) == 0 ) mgrInited = true;
		mgrClock = 0.0;
	}
	if( mgrInited ) {
		mgrTimer.tmAddr = NULL;
		mgrTimer.tmCount = 0;
		mgrTimer.tmWakeUp = 0;
		mgrTimer.tmReserved = 0;
		InsTime( (QElemPtr)&mgrTimer );
		PrimeTime( (QElemPtr)&mgrTimer, -MAX_TIME );
	}
	return( mgrClock );
}
#endif

/***********************************************************/
/*  Parsytec GCel timer.                                   */
/*  Provided by: Georg Wambach, gw@informatik.uni-koeln.de */
/***********************************************************/
#ifdef PARIX
#include <sys/time.h>

SPDP dtime()
{
	SPDP q;

	q = (SPDP) (TimeNowHigh()) / (SPDP) CLK_TCK_HIGH;

	return q;
}
#endif

/************************************************/
/*  Sun Solaris POSIX dtime() routine           */
/*  Provided by: Case Larsen, CTLarsen.lbl.gov  */
/************************************************/
#ifdef POSIX
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/rusage.h>

#ifdef __hpux
#include <sys/syscall.h>
#endif

struct rusage rusage;

SPDP dtime()
{
	SPDP q;

	getrusage(RUSAGE_SELF,&rusage);

	q = (SPDP)(rusage.ru_utime.tv_sec);
	q = q + (SPDP)(rusage.ru_utime.tv_nsec) * 1.0e-09;

	return q;
}
#endif


/****************************************************/
/*  Windows NT (32 bit) dtime() routine             */
/*  Provided by: Piers Haken, piersh@microsoft.com  */
/****************************************************/
#ifdef WIN32
#include <windows.h>

SPDP dtime(void)
{
	SPDP q;

	q = (SPDP)GetTickCount() * 1.0e-03;

	return q;
}
#endif


