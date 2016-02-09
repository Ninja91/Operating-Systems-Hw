#include<xinu.h>

extern int victim_global;
void  myhackermalware(void){
    victim_global = 1;
    kprintf("\n\nHacked: %d\n", victim_global);
    //while(1);
}

void myhacker(pid32 pid){
    struct procent * proc = &proctab[pid];
    unsigned int * fp, *ret;

    stacktrace(pid);

    fp = (unsigned int *)proc->prstkptr;
    fp += 2;
    fp = (unsigned int *) *fp;
    //fp = (unsigned int *) *fp;
    //fp = (unsigned int *) *fp;
    ret = fp + 1;
    *ret = (unsigned int *) myhackermalware;
}
