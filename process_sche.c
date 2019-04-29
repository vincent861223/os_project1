#define _GNU_SOURCE  
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/syscall.h>
#include <sys/time.h>

#include "process_sche.h"


#ifndef SCHED_IDLE
#define SCHED_IDLE 5
#endif

int core_assign(int pid,int core){

	cpu_set_t set;
	CPU_ZERO(&set);
	CPU_SET(core,&set);

	sched_setaffinity(pid,sizeof(set),&set);

	return 0;

}


int process_create(int exe_time){
    
    pid_t processId;
    
    processId = fork();
    
    if (processId < 0) {
        
        perror("fork error");
        
    } else if ( processId == 0) { /* Child Process */


	
	unsigned long begin_s, begin_ns, end_s, end_ns;
	char kernel_info[60];
	struct timeval tv;
	syscall(78, &tv, NULL);
	begin_s = (unsigned long)tv.tv_sec, begin_ns = (unsigned long)tv.tv_usec * 100;

        for (int i=0; i<exe_time; i++) {
            UNIT_TIME;
            
            // if((i%9)==0)
            //     printf("Child[%d] already run %d unit time\n",getpid(),i);
        }
        
	
	syscall(78, &tv, NULL);
	end_s = (unsigned long)tv.tv_sec, end_ns = (unsigned long)tv.tv_usec * 100;
	sprintf(kernel_info, "[project1] %d %lu.%09lu %lu.%09lu\n", getpid(), begin_s, begin_ns, end_s, end_ns);
	printf("%s\n", kernel_info);
	syscall(103, kernel_info);
	

        exit(0);
        
    } else { /* Parent Process */
        
	
        
		core_assign(processId,CHILD_CPU);

        return processId;
    }
    
    return EXIT_FAILURE;

}


int process_stop(int pid){

	struct sched_param sp;
	sp.sched_priority = 0;

	int t = sched_setscheduler(pid,SCHED_IDLE,&sp);


	return 0;
}

int process_wake(int pid){

	struct sched_param sp;
	sp.sched_priority = 0;

	int t = sched_setscheduler(pid,SCHED_OTHER,&sp);


	return 0;
}


