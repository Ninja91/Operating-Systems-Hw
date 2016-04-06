#include<xinu.h>
#include <lab2.h>
/* Test case 1 for Prob 4. */
void lab3q3t1()
{
    pid32 pr[6];
    int i;
    /* Run 6 CPU Bound process*/
    for(i = 0; i < 6; i++){
        /* Initial priority is set to 200 so that the main process can complete creating all the processes and all the processes
         * are in the ready queue.*/
        resume(pr[i] = create(cpubound, 1024, 10, "cpubound process", 2, 100, 3000));
    }
}
/* Test case 2 for Prob 4. */
void lab3q3t2()
{
    pid32 pr[6];
    int i;
    /* Run 6 IO Bound process with equal starting priority*/
    for(i = 0; i < 2; i++){
        /* Initial priority is set to 200 so that the main process can complete creating all the processes and all the processes
         * are in the ready queue.*/
        resume(pr[i] = create(iobound, 1024, 10, "iobound process", 3, 30, 1, 30));
    }
}
/* Test case 3 for Prob 4. */
void lab3q3t3()
{
    pid32 pr[6];
    int i;
    /* Run 3 CPU Bound and 3 IO Bound process*/
    for(i = 0; i < 6; i++){
        /* Initial priority is set to 200 so that the main process can complete creating all the processes and all the processes
         * are in the ready queue.*/
        resume(pr[i++] = create(cpubound, 1024, 10, "cpubound process", 2, 5, 3000));
        resume(pr[i] = create(iobound, 1024, 10, "iobound process", 3, 3, 10, 30));
    }
}
