#include<xinu.h>
#include <lab2.h>
void iobound(int32 loop1, int32 loop2, int32 sleep_time) {
    int32 i,j, alu_calc;

    for (i = loop1; i; i--) {
        for (j = loop2; j; j--) {
            sleepms(sleep_time);
        }

        kprintf("\n\nPID: %d,\nOuter loop: %d,\nProcess Priority: %d,\n Remaining time slice: %d\n",
                currpid,
                i,
                proctab[currpid].prprio,
                proctab[currpid].prcpumsec,
                preempt);
    }

    kprintf("\nCPU TIME consumed by process: %d is %d",
            currpid,
            proctab[currpid].prcpumsec);
}
