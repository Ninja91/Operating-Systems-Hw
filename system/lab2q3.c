#include<xinu.h>
#include<lab2.h>
void lab2q3t1()
{
    pid32 app_unlim0, app_unlim1, app_unlim2, app_unlim3, app_unlim4;
    int i = 100;

    /* Creating 4 process of a higher priority (21) and one sleep process o same priority and a lower priority process. */
    /* Lower priority process is expected to starve and sleep process must use very few cycles */
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

    /* Printing the CPU cycles */
    kprintf("\napp_lim0 cpu cycles: %d\n", proctab[app_unlim0].prcpumsec);
    kprintf("\napp_lim1 cpu cycles: %d\n", proctab[app_unlim1].prcpumsec);
    kprintf("\napp_lim2 cpu cycles: %d\n", proctab[app_unlim2].prcpumsec);
    kprintf("\napp_sleep3 cpu cycles: %d\n", proctab[app_unlim3].prcpumsec);
    kprintf("\napp_lim4 cpu cycles: %d\n", proctab[app_unlim4].prcpumsec);
}
