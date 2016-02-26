#include<xinu.h>
#include<lab2.h>
void lab2q5t1()
{
    pid32 pr[6];
    int i, times[] = {100, 500, 50, 2000, 100, 0};
    for(i = 0; i < 6; i++){
        resume(pr[i] = create(cpubound, 1024, 200, "cpubound process", 2, 20, 50000));
        sleepms(times[i]);
    }
}
