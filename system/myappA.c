#include<xinu.h>

extern char myfuncA(int);
static unsigned long	*esp;

int myappA(int x, int main_pid){
    unsigned long * topsp;
    int res;
    struct procent * proc = &proctab[main_pid];

    kprintf("\ncurrpid : %d\n", currpid);
    kprintf("\n main's pid : %d\n", main_pid);
    kprintf("\n main's esp(prstkptr) : 0x%x\n", (unsigned long *)proc->prstkptr);

    asm("movl %esp, esp");
    topsp = esp;
    kprintf("\nBefore myfuncA is called\n");
    kprintf("run-time stack top : address = 0x%x, content = 0x%x\n", topsp, (unsigned long *) *topsp);

    res = myfuncA(x);

    asm("movl %esp, esp");
    topsp = esp;
    kprintf("\nAfter myfuncA has returned\n");
    kprintf("run-time stack top : address = 0x%x, content = 0x%x\n", topsp, (unsigned long *) *topsp);
    
    return res;
}
