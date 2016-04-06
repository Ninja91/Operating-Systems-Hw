#include<xinu.h>
extern void sendex(pid32, umsg32, int32);
extern void sendex1(pid32, umsg32, int32);
extern void receiveex();

void lab3q4t1()
{
    pid32 pr[6];
    int i = 0;
    resume(pr[i++] = create(receiveex, 1024, 10, "receiver process", 0, NULL));
    
    resume(pr[i++] = create(sendex, 1024, 10, "send process", 3, pr[0], 100, 0));
    resume(pr[i++] = create(sendex, 1024, 10, "send process", 3, pr[0], 125, 0));
    resume(pr[i++] = create(sendex, 1024, 10, "send process", 3, pr[0], 150, 0));
    resume(pr[i++] = create(sendex, 1024, 10, "send process", 3, pr[0], 175, 0));
}
void lab3q4t2()
{
    pid32 pr[6];
    int i = 0;
    resume(pr[i++] = create(receiveex, 1024, 10, "cpubound process", 0, NULL));
    
    resume(pr[i++] = create(sendex, 1024, 10, "send process", 3, pr[0], 200, 110));
    resume(pr[i++] = create(sendex, 1024, 10, "send process", 3, pr[0], 225, 120));
    resume(pr[i++] = create(sendex, 1024, 10, "send process", 3, pr[0], 250, 130));
    resume(pr[i++] = create(sendex, 1024, 10, "send process", 3, pr[0], 275, 140));
}
void lab3q4t3()
{
    pid32 pr[6];
    int i = 0;
    resume(pr[i++] = create(receiveex, 1024, 10, "cpubound process", 0, NULL));
    
    resume(pr[i++] = create(sendex, 1024, 10, "send process", 3, pr[0], 300, 10));
    resume(pr[i++] = create(sendex, 1024, 10, "send process", 3, pr[0], 325, 20));
    resume(pr[i++] = create(sendex, 1024, 10, "send process", 3, pr[0], 350, 30));
    resume(pr[i++] = create(sendex, 1024, 10, "send process", 3, pr[0], 375, 40));
    /* for(i = 1; i < 5; i++){ */
        /* Initial priority is set to 200 so that the main process can complete creating all the processes and all the processes
         * are in the ready queue.*/
}
void lab3q4t4()
{
    pid32 pr[6];
    int i = 0;
    resume(pr[i++] = create(receiveex, 1024, 10, "cpubound process", 0, NULL));
    
    resume(pr[i++] = create(sendex, 1024, 10, "send process", 3, pr[0], 350, -20));
}
