#include<xinu.h>

/*------------------------------------------------------------------------
 *  prtprstate  -  Prints the name and state (eg: sleep, running) of the process with a given process ID
 *------------------------------------------------------------------------
 */

void prtprstate(pid32 pid){
    struct procent *procent_struct;
    if (isbadpid(pid)){
        kprintf("\n Bad PID. Exiting....");
        return;
    }
    procent_struct = &proctab[pid];
    
    kprintf("\n\nProcess Name -- %s",procent_struct->prname);
    switch(procent_struct->prstate){
        case PR_CURR:
            kprintf("\nProcess State: Currently Running");
            break;
        case PR_FREE:
            kprintf("\nProcess State: Memory Freed/ Killed");
            break;
        case PR_READY:
            kprintf("\nProcess State: Currently in Ready state");
            break;
        case PR_RECV:
            kprintf("\nProcess State: Process Waiting for Message");
            break;
        case PR_SLEEP:
            kprintf("\nProcess State: Currently in Sleep state");
            break;
        case PR_SUSP:
            kprintf("\nProcess State: Currently in Suspended state");
            break;
        case PR_WAIT:
            kprintf("\nProcess State: Currently Waiting for resources");
            break;
        default:
            kprintf("\nProcess State: Memory Freed/ Killed");
            break;
    }
}

