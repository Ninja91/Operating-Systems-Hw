#include<xinu.h>

extern void send_func(pid32, umsg32);
extern void send_func2(pid32, umsg32);
extern void recv_func();
extern void recv_func_null();
void lab4q2t1()
{
    pid32 recvpid, sendpid;
    kprintf("\n Inside first test case\n");
    resume(recvpid = create(recv_func, 1024, 10, "receiver process", 0, NULL));
    resume(sendpid = create(send_func, 1024, 10, "sender process", 2, recvpid, 11111));
    resume(recvpid = create(recv_func, 1024, 10, "receiver process", 0, NULL));
}


void lab4q2t2()
{
    pid32 recvpid, sendpid;
    kprintf("\n Inside second test case\n");
    resume(recvpid = create(recv_func, 1024, 10, "receiver process", 0, NULL));
    resume(sendpid = create(send_func, 1024, 10, "sender process", 2, recvpid, 11111));
    resume(sendpid = create(send_func, 1024, 10, "sender process", 2, recvpid, 22222));
    resume(sendpid = create(send_func, 1024, 10, "sender process", 2, recvpid, 33333));
    resume(recvpid = create(recv_func_null, 1024, 10, "receiver process", 0, NULL));
}

void lab4q2t3()
{
    pid32 recvpid, sendpid;
    kprintf("\n Inside third test case\n");
    resume(recvpid = create(recv_func, 1024, 10, "receiver process", 0, NULL));
    resume(sendpid = create(send_func2, 1024, 10, "sender process", 4, recvpid, 10, 11111, 22222));
}
