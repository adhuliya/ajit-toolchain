// This is a simple example that demonstrates a Hello World program.
#include <misc.h>
#include <math.h>
#include <cortos.h>
#include <nbench1.h>
#include <nbench0.h>
#include <cortos.h>
#include "arrays.h"
#include <ajit_access_routines.h>



#define sprintf cortos_printf
#define output_string cortos_printf

/********************************
** BACK PROPAGATION NEURAL NET **
*********************************
** This code is a modified version of the code
** that was submitted to BYTE Magazine by
** Maureen Caudill.  It accomanied an article
** that I CANNOT NOW RECALL.
** The author's original heading/comment was
** as follows:
**
**  Backpropagation Network
**  Written by Maureen Caudill
**  in Think C 4.0 on a Macintosh
**
**  (c) Maureen Caudill 1988-1991
**  This network will accept 5x7 input patterns
**  and produce 8 bit output patterns.
**  The source code may be copied or modified without restriction,
**  but no fee may be charged for its use.
**
** ++++++++++++++
** I have modified the code so that it will work
** on systems other than a Macintosh -- RG
*/

/***********
** DoNNet **
************
** Perform the neural net benchmark.
** Note that this benchmark is one of the few that
** requires an input file.  That file is "NNET.DAT" and
** should be on the local directory (from which the
** benchmark program in launched).
*/


void setup()
{
        __ajit_serial_configure__(1,0,0);
        __ajit_serial_set_baudrate__ (115200, 80000000);
        __ajit_serial_set_uart_reset__ (0);

        cortos_printf("Init channel.\n");

}
void main(void)
{

cortos_printf("entered main\n");
int i;                  /* Index */
//time_t time_and_date;   /* Self-explanatory */
struct tm *loctime;
double bmean;           /* Benchmark mean */
double bstdev;          /* Benchmark stdev */
double lx_memindex;     /* Linux memory index (mainly integer operations)*/
double lx_intindex;     /* Linux integer index */
double lx_fpindex;      /* Linux floating-point index */
double intindex;        /* Integer index */
double fpindex;         /* Floating-point index */
ulong bnumrun;          /* # of runs */
global_min_ticks=MINIMUM_TICKS;
global_min_seconds=MINIMUM_SECONDS;
global_allstats=0;
global_custrun=0;
global_align=8;
write_to_file=0;
lx_memindex=(double)1.0;        /* set for geometric mean computations */
lx_intindex=(double)1.0;
lx_fpindex=(double)1.0;
intindex=(double)1.0;
fpindex=(double)1.0;
mem_array_ents=0;  
if (0!=bench_with_confidence(
                        &bmean,
                        &bstdev,
                        &bnumrun)){
                  cortos_printf("\n** WARNING: The current test result is NOT 95 % statistically certain.\n");
                  cortos_printf("** WARNING: The variation among the individual results is too large.\n");
                  cortos_printf("                    :");
                }

cortos_printf("DONE \n");
cortos_printf(" %lf  : \n", bmean);

}
/////////////////////////////////////////////////

static int bench_with_confidence(
        double *mean,                   /* Mean of scores */
        double *stdev,                  /* Standard deviation */
        ulong *numtries)                /* # of attempts */
{
double myscores[30];            /* Need at least 5 scores, use at most 30 */
double c_half_interval;         /* Confidence half interval */
int i;                          /* Index */
/* double newscore; */          /* For improving confidence interval */

/*
** Get first 5 scores.  Then begin confidence testing.
*/
for (i=0;i<5;i++)
{       //func csall funcptr
	DoNNET();
        myscores[i]=global_nnetstruct.iterspersec;
#ifdef DEBUG
        cortos_printf("score # %d = %f\n", i, myscores[i]);
#endif
}
//*numtries=5;            /* Show 5 attempts */




//cortos_printf("reached here\n");
/*** The system allows a maximum of 30 tries before it gives
** up.  Since we've done 5 already, we'll allow 25 more.
*/

/*
** Enter loop to test for confidence criteria.
*/
while(1)
{
        /*
        ** Calculate confidence. Should always return 0.
        */
        if (0!=calc_confidence(myscores,
                5,
                &c_half_interval,
                mean,
                stdev)) return(-1);


//	cortos_printf("confidence calculated\n");
        /*
        ** Is the length of the half interval 5% or less of mean?
        ** If so, we can go home.  Otherwise, we have to continue.
        */
        if(c_half_interval/ (*mean) <= (double)0.05)
                break;

#ifdef OLDCODE
#undef OLDCODE
#endif
        /* We now simply add a new test run and hope that the runs
           finally stabilize, Uwe F. Mayer */
        if(*numtries==30) return(-1);
        //func casll funcptr
	DoNNET();
        myscores[*numtries]==global_nnetstruct.iterspersec;
#ifdef DEBUG
        cortos_printf("score # %ld = %f\n", *numtries, myscores[*numtries]);
#endif
        *numtries+=1;
}

return(0);
}


static int calc_confidence(double scores[], /* Array of scores */
                int num_scores,             /* number of scores in array */
                double *c_half_interval,    /* Confidence half-int */
                double *smean,              /* Standard mean */
                double *sdev)               /* Sample stand dev */
{
/* Here is a list of the student-t distribution up to 29 degrees of
   freedom. The value at 0 is bogus, as there is no value for zero
   degrees of freedom. */
double student_t[30]={0.0 , 12.706 , 4.303 , 3.182 , 2.776 , 2.571 ,
                             2.447 , 2.365 , 2.306 , 2.262 , 2.228 ,
                             2.201 , 2.179 , 2.160 , 2.145 , 2.131 ,
                             2.120 , 2.110 , 2.101 , 2.093 , 2.086 ,
                             2.080 , 2.074 , 2.069 , 2.064 , 2.060 ,
                             2.056 , 2.052 , 2.048 , 2.045 };
int i;          /* Index */
if ((num_scores<2) || (num_scores>30)) {
  output_string("Internal error: calc_confidence called with an illegal number of scores\n");
  return(-1);
}
/*
** First calculate mean.
*/
*smean=(double)0.0;
for(i=0;i<num_scores;i++){
  *smean+=scores[i];
}
*smean/=(double)num_scores;

/* Get standard deviation */
*sdev=(double)0.0;
for(i=0;i<num_scores;i++) {
  *sdev+=(scores[i]-(*smean))*(scores[i]-(*smean));
}
*sdev/=(double)(num_scores-1);
*sdev=sqrt(*sdev);

/* Now calculate the length of the confidence half-interval.  For a
** confidence level of 95% our confidence coefficient gives us a
** multiplying factor of the upper .025 quartile of a t distribution
** with num_scores-1 degrees of freedom, and dividing by sqrt(number of
** observations). See any introduction to statistics.
*/
*c_half_interval=student_t[num_scores-1] * (*sdev) / sqrt((double)num_scores);
return(0);
}


void DoNNET(void)
{
//cortos_printf("entered DONNet");
NNetStruct *locnnetstruct;      /* Local ptr to global data */
char *errorcontext;
ulong accumtime;
double iterations;

/*
** Link to global data
*/
locnnetstruct=&global_nnetstruct;
/*
** Set error contex

t
*/
errorcontext="CPU:NNET";

/*
** Init random number generator.
** NOTE: It is important that the random number generator
**  be re-initialized for every pass through this test.
**  The NNET algorithm uses the random number generator
**  to initialize the net.  Results are sensitive to
**  the initial neural net state.
*/
/* randnum(3L); */
randnum((int32)3);

/*
** Read in the input and output patterns.  We'll do this
** only once here at the beginning.  These values don't
** change once loaded.
*/
//if(read_data_file()!=0)
//   ErrorExit();

int i,patt;

for (patt=0; patt<26; patt++)
{

	for (i=0;i<35; i++)
        {
                if (in_pats[patt][i] >= 0.9)
                        in_pats[patt][i] = 0.9;
                if (in_pats[patt][i] <= 0.1)
                        in_pats[patt][i] = 0.1;
        }
}
/*for (patt=0; patt<26; patt++)
{
	for (i=0;i<IN_SIZE; i++)
        {
                cortos_printf("in_pats[%d][%d] =%lf \n",patt,i,in_pats[patt][i]);
        }

}*/
/*
** See if we need to perform self adjustment loop.
*/
if(locnnetstruct->adjust==0)
{
        /*
        ** Do self-adjustment.  This involves initializing the
        ** # of loops and increasing the loop count until we
        ** get a number of loops that we can use.
        */
        for(locnnetstruct->loops=1L;
          locnnetstruct->loops<MAXNNETLOOPS;
          locnnetstruct->loops++)
          {     /*randnum(3L); */
                randnum((int32)3);
                if(DoNNetIteration(locnnetstruct->loops)
                        >global_min_ticks) break;
          }
}
//cortos_printf("loops = %lld\n",locnnetstruct->loops);
/*
** All's well if we get here.  Do the test.
*/
accumtime=0L;
iterations=(double)0.0;

do {
        /* randnum(3L); */    /* Gotta do this for Neural Net */
        randnum((int32)3);    /* Gotta do this for Neural Net */
        accumtime+=DoNNetIteration(locnnetstruct->loops);
        iterations+=(double)locnnetstruct->loops;
} while(TicksToSecs(accumtime)<locnnetstruct->request_secs);

/*
** Clean up, calculate results, and go home.  Be sure to
** show that we don't have to rerun adjustment code.
*/
locnnetstruct->iterspersec=iterations / TicksToFracSecs(accumtime);

if(locnnetstruct->adjust==0)
        locnnetstruct->adjust=1;

//cortos_printf("exit do nnet\n");
return;
}



/********************
** DoNNetIteration **
*********************
** Do a single iteration of the neural net benchmark.
** By iteration, we mean a "learning" pass.
*/
static ulong DoNNetIteration(ulong nloops)
{
//cortos_printf("starting iteration\n");
ulong elapsed;          /* Elapsed time */
int patt;

/*
** Run nloops learning cycles.  Notice that, counted with
** the learning cycle is the weight randomization and
** zeroing of changes.  This should reduce clock jitter,
** since we don't have to stop and start the clock for
** each iteration.
*/
//elapsed=StartStopwatch();

numpats = MAXPATS;
uint64_t t0 = cortos_get_clock_time();
while(nloops--)
{
	int req_passes=99;
        randomize_wts();
        zero_changes();
        iteration_count=1;
        learned = F;
        numpasses = 0;
        while (learned == F)
        {
		//cortos_printf("value of patts is = %d \n",patt);
                for (patt=0; patt<numpats; patt++)
                {
                        worst_error = 0.0;      /* reset this every pass through data */
                        move_wt_changes();      /* move last pass's wt changes to momentum array */
                        do_forward_pass(patt);
                        do_back_pass(patt);
                        iteration_count++;
                }
		//cortos_printf("numpats --  \n");
                numpasses ++;
		learned = (numpasses==req_passes) ? TRUE : FALSE;
		check_out_error();
//                learned = check_out_error();
        }
//#ifdef DEBUG
//cortos_printf("Learned in %d passes\n",numpasses);
//#endif
}
uint64_t t1 = cortos_get_clock_time();
elapsed = (t1-t0);
return((elapsed));
}
/***************************
** Process the middle layer's forward pass
** The activation of middle layer's neurode is the weighted
** sum of the inputs from the input pattern, with sigmoid
** function applied to the inputs.
**/
static void  do_mid_forward(int patt)
{
double  sum;
int     neurode, i;

for (neurode=0;neurode<MID_SIZE; neurode++)
{
        sum = 0.0;
        for (i=0; i<IN_SIZE; i++)
        {       /* compute weighted sum of input signals */
                sum += mid_wts[neurode][i]*in_pats[patt][i];
        }
	for (i=0; i<IN_SIZE; i++)
        {
                CORTOS_DEBUG("sum=%lf and mid_wts[%d][%d] = %lf \n",sum,neurode,i,mid_wts[neurode][i]);
        }

        /*
        ** apply sigmoid function f(x) = 1/(1+exp(-x)) to weighted sum
        */
        sum = 1.0/(1.0+exp(-sum));
        mid_out[neurode] = sum;
	CORTOS_DEBUG("mid_out is %lf \n",mid_out[neurode]);
}
return;
}
/*********************
** do_out_forward() **
**********************
** process the forward pass through the output layer
** The activation of the output layer is the weighted sum of
** the inputs (outputs from middle layer), modified by the
** sigmoid function.
**/
static void  do_out_forward()
{
double sum;
int neurode, i;

for (neurode=0; neurode<OUT_SIZE; neurode++)
{
        sum = 0.0;
        for (i=0; i<MID_SIZE; i++)
        {       /*
                ** compute weighted sum of input signals
                ** from middle layer
                */
                sum += out_wts[neurode][i]*mid_out[i];
        }
	for (i=0; i<MID_SIZE; i++)
        {
                CORTOS_DEBUG("sum=%lf and out_wts[%d][%d] = %lf \n",sum,neurode,i,out_wts[neurode][i]);
        }

        /*
        ** Apply f(x) = 1/(1+exp(-x)) to weighted input
        */
        sum = 1.0/(1.0+exp(-sum));
        out_out[neurode] = sum;
	CORTOS_DEBUG("out_out is %lf \n",out_out[neurode]);
}
return;
}
/**********************
** do_forward_pass() **
***********************
** control function for the forward pass through the network
** NOTE: I have disabled the call to display_output() in
**  the benchmark version -- RG.
**/
static void  do_forward_pass(int patt)
{
do_mid_forward(patt);   /* process forward pass, middle layer */
do_out_forward();       /* process forward pass, output layer */
/* display_output(patt);        ** display results of forward pass */
return;
}

/***********************
** do_out_error(patt) **
************************
** Compute the error for the output layer neurodes.
** This is simply Desired - Actual.
**/
static void do_out_error(int patt)
{
int neurode;
double error,tot_error, sum;

tot_error = 0.0;
sum = 0.0;
for (neurode=0; neurode<OUT_SIZE; neurode++)
{
        out_error[neurode] = out_pats[patt][neurode] - out_out[neurode];
        /*
        ** while we're here, also compute magnitude
        ** of total error and worst error in this pass.
        ** We use these to decide if we are done yet.
        */
        error = out_error[neurode];
        if (error <0.0)
        {
                sum += -error;
                if (-error > tot_error)
                        tot_error = -error; /* worst error this pattern */
        }
        else
        {
                sum += error;
                if (error > tot_error)
                        tot_error = error; /* worst error this pattern */
        }
}
avg_out_error[patt] = sum/OUT_SIZE;
tot_out_error[patt] = tot_error;

CORTOS_DEBUG("avg out error = %lf and tot out error = %lf \n",avg_out_error[patt],tot_out_error[patt]);

return;
}

/***********************
** worst_pass_error() **
************************
** Find the worst and average error in the pass and save it
**/
static void  worst_pass_error()
{
double error,sum;

int i;

error = 0.0;
sum = 0.0;
for (i=0; i<numpats; i++)
{
        if (tot_out_error[i] > error) error = tot_out_error[i];
        sum += avg_out_error[i];
}
worst_error = error;
average_error = sum/numpats;

CORTOS_DEBUG("worst error = %lf and average error = %lf \n",worst_error,average_error);

return;
}

/*******************
** do_mid_error() **
********************
** Compute the error for the middle layer neurodes
** This is based on the output errors computed above.
** Note that the derivative of the sigmoid f(x) is
**        f'(x) = f(x)(1 - f(x))
** Recall that f(x) is merely the output of the middle
** layer neurode on the forward pass.
**/
static void do_mid_error()
{
double sum;
int neurode, i;
for (neurode=0; neurode<MID_SIZE; neurode++)
{
        sum = 0.0;
        for (i=0; i<OUT_SIZE; i++)
                sum += out_wts[i][neurode]*out_error[i];

        /*
        ** apply the derivative of the sigmoid here
        ** Because of the choice of sigmoid f(I), the derivative
        ** of the sigmoid is f'(I) = f(I)(1 - f(I))
        */
        mid_error[neurode] = mid_out[neurode]*(1-mid_out[neurode])*sum;
}
for (neurode=0; neurode<MID_SIZE; neurode++){
CORTOS_DEBUG("mid error[%d] = %lf \n",neurode,mid_error[neurode]);
}
return;
}

/*********************
** adjust_out_wts() **
**********************
** Adjust the weights of the output layer.  The error for
** the output layer has been previously propagated back to
** the middle layer.
** Use the Delta Rule with momentum term to adjust the weights.
**/
static void adjust_out_wts()
{
int weight, neurode;
double learn,delta,alph;

learn = BETA;
alph  = ALPHA;
for (neurode=0; neurode<OUT_SIZE; neurode++)
{
        for (weight=0; weight<MID_SIZE; weight++)
        {
                /* standard delta rule */
                delta = learn * out_error[neurode] * mid_out[weight];

                /* now the momentum term */
                delta += alph * out_wt_change[neurode][weight];
                out_wts[neurode][weight] += delta;

                /* keep track of this pass's cum wt changes for next pass's momentum */
                out_wt_cum_change[neurode][weight] += delta;
		CORTOS_DEBUG("out wts [%d][%d] =%lf and out wt cum change[%d][%d] = %lf \n",neurode,weight,out_wts[neurode][weight],neurode,weight,out_wt_cum_change[neurode][weight]);
        }
}




return;
}
/*************************
** adjust_mid_wts(patt) **
**************************
** Adjust the middle layer weights using the previously computed
** errors.
** We use the Generalized Delta Rule with momentum term
**/
static void adjust_mid_wts(int patt)
{
int weight, neurode;
double learn,alph,delta;

learn = BETA;
alph  = ALPHA;
for (neurode=0; neurode<MID_SIZE; neurode++)
{
        for (weight=0; weight<IN_SIZE; weight++)
        {
                /* first the basic delta rule */
                delta = learn * mid_error[neurode] * in_pats[patt][weight];

                /* with the momentum term */
                delta += alph * mid_wt_change[neurode][weight];
                mid_wts[neurode][weight] += delta;

                /* keep track of this pass's cum wt changes for next pass's momentum */
                mid_wt_cum_change[neurode][weight] += delta;
		CORTOS_DEBUG("mid wts [%d][%d] =%lf and mid wt cum change[%d][%d] = %lf \n",neurode,weight,mid_wts[neurode][weight],neurode,weight,mid_wt_cum_change[neurode][weight]);
        }
}
return;
}

/*******************
** do_back_pass() **
********************
** Process the backward propagation of error through network.
**/
void  do_back_pass(int patt)
{

do_out_error(patt);
do_mid_error();
adjust_out_wts();
adjust_mid_wts(patt);

return;
}

/**********************
** move_wt_changes() **
***********************
** Move the weight changes accumulated last pass into the wt-change
** array for use by the momentum term in this pass. Also zero out
** the accumulating arrays after the move.
**/
static void move_wt_changes()
{
int i,j;
for (i = 0; i<MID_SIZE; i++)
        for (j = 0; j<IN_SIZE; j++)
        {
                mid_wt_change[i][j] = mid_wt_cum_change[i][j];
                /*
                ** Zero it out for next pass accumulation.
                */
                mid_wt_cum_change[i][j] = 0.0;
		CORTOS_DEBUG("mid wt chnage [%d][%d] =%lf and mid wt cum change[%d][%d] = %lf \n",i,j,mid_wt_change[i][j],i,j,mid_wt_cum_change[i][j]);

        }

for (i = 0; i<OUT_SIZE; i++)
        for (j=0; j<MID_SIZE; j++)
        {
                out_wt_change[i][j] = out_wt_cum_change[i][j];
                out_wt_cum_change[i][j] = 0.0;
		CORTOS_DEBUG("out wt chnage [%d][%d] =%lf and out wt cum change[%d][%d] = %lf \n",i,j,out_wt_change[i][j],i,j,out_wt_cum_change[i][j]);
        }

return;
}

/**********************
** check_out_error() **
***********************
** Check to see if the error in the output layer is below
** MARGIN*OUT_SIZE for all output patterns.  If so, then
** assume the network has learned acceptably well.  This
** is simply an arbitrary measure of how well the network
** has learned -- many other standards are possible.
**/
static int check_out_error()
{
int result,i,error;

result  = T;
error   = F;
worst_pass_error();     /* identify the worst error in this pass */

/*
#ifdef DEBUG
printf("\n Iteration # %d",iteration_count);
#endif
*/
for (i=0; i<numpats; i++)
{
/*      printf("\n Error pattern %d:   Worst: %8.3f; Average: %8.3f",
          i+1,tot_out_error[i], avg_out_error[i]);
        fprintf(outfile,
         "\n Error pattern %d:   Worst: %8.3f; Average: %8.3f",
         i+1,tot_out_error[i]);
*/

        if (worst_error >= STOP) result = F;
        if (tot_out_error[i] >= 16.0) error = T;
}

if (error == T) result = ERR;

CORTOS_DEBUG("error is %d and result is %d \n", error,result);

#ifdef DEBUG
/* printf("\n Error this pass thru data:   Worst: %8.3f; Average: %8.3f",
 worst_error,average_error);
*/
/* fprintf(outfile,
 "\n Error this pass thru data:   Worst: %8.3f; Average: %8.3f",
  worst_error, average_error); */
#endif

return(result);
}


/*******************
** zero_changes() **
********************
** Zero out all the wt change arrays
**/
static void zero_changes()
{
int i,j;

for (i = 0; i<MID_SIZE; i++)
{
        for (j=0; j<IN_SIZE; j++)
        {
                mid_wt_change[i][j] = 0.0;
                mid_wt_cum_change[i][j] = 0.0;
		CORTOS_DEBUG("mid wt chnage [%d][%d] =%lf and mid wt cum change[%d][%d] = %lf \n",i,j,mid_wt_change[i][j],i,j,mid_wt_cum_change[i][j]);
        }
}

       for (i = 0; i< OUT_SIZE; i++)
{
        for (j=0; j<MID_SIZE; j++)
        {
                out_wt_change[i][j] = 0.0;
                out_wt_cum_change[i][j] = 0.0;
		CORTOS_DEBUG("out wt chnage [%d][%d] =%lf and out wt cum change[%d][%d] = %lf \n",i,j,out_wt_change[i][j],i,j,out_wt_cum_change[i][j]);
        }
}
return;
}


/********************
** randomize_wts() **
*********************
** Intialize the weights in the middle and output layers to
** random values between -0.25..+0.25
** Function rand() returns a value between 0 and 32767.
**
** NOTE: Had to make alterations to how the random numbers were
** created.  -- RG.
**/
static void randomize_wts()
{
int neurode,i;
double value;

/*
** Following not used int benchmark version -- RG
**
**        printf("\n Please enter a random number seed (1..32767):  ");
**        scanf("%d", &i);
**        srand(i);
*/

for (neurode = 0; neurode<MID_SIZE; neurode++)
{
        for(i=0; i<IN_SIZE; i++)
        {
                /* value=(double)abs_randwc(100000L); */
                value=(double)abs_randwc((int32)100000);
                value=value/(double)100000.0 - (double) 0.5;
                mid_wts[neurode][i] = value/2;
		CORTOS_DEBUG("mid wts [%d][%d] = %lf \n",neurode,i,mid_wts[neurode][i]);

        }
}
for (neurode=0; neurode<OUT_SIZE; neurode++)
{
        for(i=0; i<MID_SIZE; i++)
        {
                /* value=(double)abs_randwc(100000L); */
                value=(double)abs_randwc((int32)100000);
                value=value/(double)10000.0 - (double) 0.5;
                out_wts[neurode][i] = value/2;
		CORTOS_DEBUG("out wts [%d][%d] = %lf \n",neurode,i,out_wts[neurode][i]);
        }
}

return;
}

