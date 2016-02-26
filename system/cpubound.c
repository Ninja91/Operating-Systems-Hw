#include<xinu.h>
#include <lab2.h>
void cpubound(int32 loop1, int32 loop2) {
    char *source = "This string will be copied repeatedly";
    char dest[100];
    char *src = source, *dst = dest;
    int32 i,j, alu_calc;

    for (i = loop1; i; i--) {
        for (j = loop2; j; j--) {
            
            //Slow operation - copying string
            src = source;
            dst = dest;
            while (*src != '\0'){
                *dst = *src;//+ i/10 + j/0x7fffffff;
                src++;
                dst++;
            }

            alu_calc = 2*3*4*5*6*7*8*9*10;
        }

        kprintf("\n\nPID: %d,\nOuter loop: %d,\nProcess Priority: %d,\n Remaining time slice: %d\n",
                currpid,
                i,
                proctab[currpid].prprio,
                preempt);
    }

    kprintf("\nCPU TIME consumed by process: %d is %d",
            currpid,
            proctab[currpid].prcpumsec);
}
