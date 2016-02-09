#include<xinu.h> 
void myvictim2(int x){
    sleepms(x *1000);
}

void myvictim(int x){
    kprintf("\n\nPID : %d\n", getpid());
    myvictim2(x);
}

