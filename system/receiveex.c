#include <xinu.h>

void receiveex(){
    while (1){
        //sleepms(100);
        kprintf("\nReceiving : %d", receive());
    }
}
