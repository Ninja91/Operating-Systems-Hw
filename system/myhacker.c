#include<xinu.h>

extern int victim_global;
void  myhackermalware(void){
    victim_global = 1;
    char *pattern = "***************************************";
    kprintf("\n%s\nFrom PID: %d\n victim_global = %d\n%s\n", pattern, currpid, victim_global, pattern);
    while(1);
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
