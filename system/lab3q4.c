#include<xinu.h>
extern void sendex(pid32, umsg32, int32);
extern void sendex1(pid32, umsg32, int32);
extern void receiveex();

void lab3q4t1()
{
    pid32 pr[6];
    int i = 0;
    resume(pr[i++] = create(receiveex, 1024, 10, "cpubound process", 0, NULL));
    
    resume(pr[i++] = create(sendex, 1024, 10, "send process", 3, pr[0], 100, 1));
    resume(pr[i++] = create(sendex, 1024, 10, "send process", 3, pr[0], 125, 1));
    resume(pr[i++] = create(sendex, 1024, 10, "send process", 3, pr[0], 150, 1));
}
void lab3q4t2()
{
    pid32 pr[6];
    int i = 0;
    resume(pr[i++] = create(receiveex, 1024, 10, "cpubound process", 0, NULL));
    
    resume(pr[i++] = create(sendex, 1024, 10, "send process", 3, pr[0], 200, 0));
    /* for(i = 1; i < 5; i++){ */
        /* Initial priority is set to 200 so that the main process can complete creating all the processes and all the processes
         * are in the ready queue.*/
    /* } */
}
void lab3q4t3()
{
    pid32 pr[6];
    int i = 0;
    resume(pr[i++] = create(receiveex, 1024, 10, "cpubound process", 0, NULL));
    
    resume(pr[i++] = create(sendex, 1024, 10, "send process", 3, pr[0], i, 200));
    resume(pr[i++] = create(sendex, 1024, 10, "send process", 3, pr[0], i, 0));
    /* for(i = 1; i < 5; i++){ */
        /* Initial priority is set to 200 so that the main process can complete creating all the processes and all the processes
         * are in the ready queue.*/
    /* } */
}
void lab3q4t4()
{
    pid32 pr[6];
    int i = 0;
    resume(pr[i++] = create(receiveex, 1024, 10, "cpubound process", 0, NULL));
    
    resume(pr[i++] = create(sendex, 1024, 10, "send process", 3, pr[0], i, 50));
    resume(pr[i++] = create(sendex, 1024, 10, "send process", 3, pr[0], i, 0));
    resume(pr[i++] = create(sendex, 1024, 10, "send process", 3, pr[0], i, 200));
    resume(pr[i++] = create(sendex, 1024, 10, "send process", 3, pr[0], i, 0));
    /* for(i = 1; i < 5; i++){ */
        /* Initial priority is set to 200 so that the main process can complete creating all the processes and all the processes
         * are in the ready queue.*/
    /* } */
}
