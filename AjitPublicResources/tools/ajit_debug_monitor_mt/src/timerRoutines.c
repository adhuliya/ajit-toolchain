// From ImageRC

#include <time.h>
#include <limits.h>
#include "timerRoutines.h"

struct timespec start_time;
struct timespec stop_time;
static double elapsed_time = 0.0;

double timeDiff(struct timespec *t1, struct timespec *t2)
{
        double time_diff;
        time_diff = (double) (t2->tv_sec - t1->tv_sec);
        double x = ((double) (t2->tv_nsec - t1->tv_nsec))*1.0e-9;

        time_diff += x;
        return(time_diff);
}

void rcResetTimer()
{
        elapsed_time = 0.0;
}

double rcGetElapsedTime()
{
        return(elapsed_time);
}

void rcStartTimer()
{
        clock_gettime(CLOCK_REALTIME, &start_time);
}


void rcStopTimer()
{
        clock_gettime(CLOCK_REALTIME, &stop_time);
        double curr_time  = timeDiff(&start_time, &stop_time);
        elapsed_time += curr_time;
}

