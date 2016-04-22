#include <xinu.h>
#include <mysignal.h>

extern int recvhandler(void *);
extern syscall	alarmms( uint32);

void recv_func() {
    if (registercb(&recvhandler) != OK) {
        kprintf("recv handler registration failed\n");
        return;
    }
    kprintf("\nProcess with PID: %d registering receiver\n", currpid);
    while(1){}
}

void recv_func_null() {
    if (registercb(NULL) != OK) {
        kprintf("recv handler registration failed\n");
        return;
    }
    kprintf("\nProcess with PID: %d registering receiver\n", currpid);
    while(1){}
}


void recv_func2() {
    if (registercbsig(MYSIGRECV, &recvhandler, 0) != OK) {
        kprintf("sig recv handler registration failed\n");
        return;
    }

    kprintf("\nProcess with PID: %d registering receiver\n", currpid);
    while(1){}
}

void recv_func2_null() {
    if (registercbsig(MYSIGRECV, NULL, 0) != OK) {
        kprintf("sig recv handler registration failed\n");
        return;
    }

    kprintf("\nProcess with PID: %d registering receiver\n", currpid);
    while(1){}
}

void recv_func3(uint32 cpucycles) {
    if (registercbsig(MYSIGXCPU, &recvhandler, cpucycles) != OK) {
        kprintf("sig xcpu handler registration failed\n");
        return;
    }

    kprintf("\nProcess with PID: %d registering receiver to be invoked after %d cpu cycles\n", currpid, cpucycles);
    while(1){}
}

void recv_func4(uint32 alrmtime, uint32 slptime) {
    if (registercbsig(MYSIGALRM, &recvhandler, 0) != OK) {
        kprintf("sig xcpu handler registration failed\n");
        return;
    }

    kprintf("\nProcess with PID: %d registering receiver which is going to sleep for %d and has alarm set for %d ms\n", currpid, slptime, alrmtime);
    alarmms(alrmtime);
    sleepms(slptime);
    while(1){}
}
