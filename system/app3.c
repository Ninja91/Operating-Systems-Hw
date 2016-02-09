#include<xinu.h>

extern pid32 getpid();
extern syscall getprio();
extern pid32 getppid();
extern void prtprstate(pid32);

void app3(){
    kprintf(" 101x555 Result -- %d\n", 101*555);
    kprintf("app 3 PID -- %d\n", getpid());
    kprintf("app 3 Process Priority -- %d\n", getprio(getpid()));    

    kprintf("\n\nParent PID:");
    kprintf("Parent PID -- %d\n", getppid());
    kprintf("\n\nBonus Question:");
    prtprstate(getpid());
}
