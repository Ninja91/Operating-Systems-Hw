#include<xinu.h>
extern pid32 getpid(); 
void app1(){
    kprintf("\nHi. This is app1\n");
    kprintf("\napp1 Process ID -- %d", getpid());  //Prints the PID of the process
}
