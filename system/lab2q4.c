#include<xinu.h>
#include<lab2.h>

/* Test case 1 for Prob 4. */
void lab2q4t1()
{
    pid32 pr[6];
    int i;
    /* Run 6 CPU Bound process*/
    for(i = 0; i < 6; i++){
        resume(pr[i] = create(cpubound, 1024, 200, "cpubound process", 2, 10, 3000));
    }
}
/* Test case 2 for Prob 4. */
void lab2q4t2()
{
    pid32 pr[6];
    int i;
    /* Run 6 IO Bound process with equal starting priority*/
    for(i = 0; i < 6; i++){
        resume(pr[i] = create(iobound, 1024, 200, "iobound process", 3, 3, 100, 30));
    }
}
/* Test case 3 for Prob 4. */
void lab2q4t3()
{
    pid32 pr[6];
    int i;
    /* Run 3 CPU Bound and 3 IO Bound process*/
    for(i = 0; i < 6; i++){
        resume(pr[i++] = create(cpubound, 1024, 200, "cpubound process", 2, 10, 30));
        resume(pr[i] = create(iobound, 1024, 200, "iobound process", 3, 10, 10, 90));
    }
}
