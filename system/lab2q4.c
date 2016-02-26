#include<xinu.h>
#include<lab2.h>
void lab2q4t1()
{
    pid32 pr[6];
    int i;
    for(i = 0; i < 6; i++){
        resume(pr[i] = create(cpubound, 1024, 200, "cpubound process", 2, 10, 10));
    }
}
void lab2q4t2()
{
    pid32 pr[6];
    int i;
    for(i = 0; i < 6; i++){
        resume(pr[i] = create(iobound, 1024, 200, "iobound process", 3, 10, 10, 30));
    }
}
void lab2q4t3()
{
    pid32 pr[6];
    int i;
    for(i = 0; i < 6; i++){
        resume(pr[i++] = create(cpubound, 1024, 200, "cpubound process", 2, 10, 10));
        resume(pr[i] = create(iobound, 1024, 200, "iobound process", 3, 10, 10, 30));
    }
}
