#include<xinu.h>
#include<lab2.h>
void lab2q3t1()
{
    pid32 app_unlim0, app_unlim1, app_unlim2, app_unlim3, app_unlim4;
    int i = 100;

    resume ( app_unlim0 = 
       create((void *)app_lim, 65536, 21, "app_unlim0 process", 0,
           NULL));
    resume ( app_unlim1 =
       create((void *)app_lim, 65536, 21, "app_unlim1 process", 0,
           NULL));
    resume ( app_unlim2 = 
       create((void *)app_lim, 65536, 21, "app_unlim2 process", 0,
           NULL));
    resume ( app_unlim3 = 
       create((void *)app_sleep, 65536, 21, "app_sleep process", 0,
           NULL));
    resume ( app_unlim4 = 
       create((void *)app_lim, 65536, 19, "app_lim process", 0,
           NULL));

    kprintf("\napp_unlim0 cpu cycles: %d\n", proctab[app_unlim0].prcpumsec);
    kprintf("\napp_unlim1 cpu cycles: %d\n", proctab[app_unlim1].prcpumsec);
    kprintf("\napp_unlim2 cpu cycles: %d\n", proctab[app_unlim2].prcpumsec);
    kprintf("\napp_unlim3 cpu cycles: %d\n", proctab[app_unlim3].prcpumsec);
    kprintf("\napp_unlim4 cpu cycles: %d\n", proctab[app_unlim4].prcpumsec);
    /* kprintf("\napp_unlim0 prio: %d\n", proctab[app_unlim0].prprio); */
    /* kprintf("\napp_unlim1 prio: %d\n", proctab[app_unlim1].prprio); */
    /* kprintf("\napp_unlim2 prio: %d\n", proctab[app_unlim2].prprio); */
}
