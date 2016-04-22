#include<xinu.h>

extern void send_func(pid32, umsg32);
extern void send_func2(pid32,int, umsg32, umsg32);
extern void recv_func();
extern void recv_func2_null();
extern void recv_func2();
extern void recv_func3(uint32);
extern void recv_func4(uint32, uint32);

    /* Test case for MYSIGRECV */
void lab4q3t1()
{
    pid32 recvpid, sendpid;
    kprintf("\n Inside first test case\n");
    resume(recvpid = create(recv_func2, 1024, 10, "receiver process", 0, NULL));
    resume(sendpid = create(send_func, 1024, 10, "sender process", 2, recvpid, 11111));
    resume(recvpid = create(recv_func2, 1024, 10, "receiver process", 0, NULL));
}

void lab4q3t2()
{
    pid32 recvpid, sendpid;
    kprintf("\n Inside second test case\n");
    resume(recvpid = create(recv_func2, 1024, 10, "receiver process", 0, NULL));
    resume(sendpid = create(send_func, 1024, 10, "sender process", 2, recvpid, 11111));
    resume(sendpid = create(send_func, 1024, 10, "sender process", 2, recvpid, 22222));
    resume(sendpid = create(send_func, 1024, 10, "sender process", 2, recvpid, 33333));
    resume(recvpid = create(recv_func2_null, 1024, 10, "receiver process", 0, NULL));
}

void lab4q3t3()
{
    pid32 recvpid, sendpid;
    kprintf("\n Inside third test case\n");
    resume(recvpid = create(recv_func2, 1024, 10, "receiver process", 0, NULL));
    resume(sendpid = create(send_func2, 1024, 10, "sender process", 4, recvpid, 10, 11111, 22222));
}

/*Test case for MYSIGXCPU*/
void lab4q3t4()
{
    pid32 recvpid, sendpid;
    kprintf("\n Inside first test case\n");
    resume(recvpid = create(recv_func3, 1024, 10, "receiver process", 1, 750));
    resume(sendpid = create(send_func, 1024, 10, "sender process", 2, recvpid, 11111));
    resume(recvpid = create(recv_func3, 1024, 10, "receiver process", 1, 1));
    resume(sendpid = create(send_func, 1024, 10, "sender process", 2, recvpid, 22222));
}

/*Test case for MYSIGALRM*/
void lab4q3t5()
{
    pid32 recvpid, sendpid;
    kprintf("\n Inside first test case\n");
    resume(recvpid = create(recv_func4, 1024, 10, "receiver process", 2, 100, 400));
    resume(sendpid = create(send_func, 1024, 10, "sender process", 2, recvpid, 11111));
}

void lab4q3t6()
{
    pid32 recvpid, sendpid;
    kprintf("\n Inside second test case\n");
    resume(recvpid = create(recv_func4, 1024, 10, "receiver process", 2, 500, 0));
    resume(sendpid = create(send_func, 1024, 10, "sender process", 2, recvpid, 11111));
}
