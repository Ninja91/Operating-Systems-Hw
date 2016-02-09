#include<xinu.h>
extern void app3();
extern pid32 getpid();

void app2(){
    kprintf("\napp2 PID -- %d\n", getpid());
    
	resume (
	   create((void *)app3, 65536, 20, "app3 process", 0,
           NULL));

    sleepms(5000);
    kprintf("\napp2PID -- %d\n", getpid());

}
