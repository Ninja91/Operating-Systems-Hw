#include<xinu.h>
#include <lab2.h>
void app_lim(){
    int32 i = 100, j;
    //kprintf("\nHi. This is app_lim with PID: %d\n", currpid);
    //kprintf("\n\ Waiting to app_lim end \n");
    
    while(i--){
        j = 10000;
        while(j--);
    } // keeping the cpu busy
    
    //kprintf("\n\ Ending app_lim ..........\n");
}

void app_sleep(){
    kprintf("\n\nGoing to sleep\n");
    sleepms(100);
}
