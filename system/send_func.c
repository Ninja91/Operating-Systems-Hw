#include <xinu.h>


void send_func(pid32 recieverpid, umsg32 msg) {
    kprintf("\n Sending message from PID: %d\n At time: %d\n And sending msg: %d\n", 
            currpid,
            clktimemsec,
            msg);

    send(recieverpid, msg);
}

void send_func2(pid32 recieverpid, int slptime, umsg32 msg1, umsg32 msg2) {
    kprintf("\n Sending message from PID: %d\n At time: %d\n And sending msg: %d\n", 
            currpid,
            clktimemsec,
            msg1);

    send(recieverpid, msg1);

    sleepms(slptime);

    kprintf("\n Sending message from PID: %d\n At time: %d\n And sending msg: %d\n", 
            currpid,
            clktimemsec,
            msg2);

    send(recieverpid, msg2);
}
