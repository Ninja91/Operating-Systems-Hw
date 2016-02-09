#include<xinu.h>

extern int victim_global;

int myvictim2(int x){
#ifdef DEBUG
    kprintf("\n\nIn myvictim2\n");
#endif
    sleepms(x *1000);
    return (x+1)*(x-1);
}

int myvictim1(int x){
#ifdef DEBUG
    kprintf("\n\nIn myvictim1\n");
#endif
    return x*x;
}

void myvictim(int x){
    char *pattern = "***************************************";

    kprintf("\n\nmyvictim pid = %d\n", currpid);
    myvictim1(x);
    myvictim2(x);
    kprintf("\n%s\nFrom PID : %d\n victim_global = %d\n%s", pattern, currpid, victim_global, pattern);
}

