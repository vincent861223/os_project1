#include <sys/types.h>
#include <unistd.h>

#define UNIT_TIME { volatile unsigned long i; for(i=0;i<1000000UL;i++); }
#define SCHED_CPU 0
#define CHILD_CPU 1

int core_assign(int,int);

int process_create(int);

int process_stop(int);

int process_wake(int);
