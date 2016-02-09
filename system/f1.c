#include<xinu.h>
void f2(){
    //if (2 == stackdepth(currpid)){
        kprintf("Stack Depth : %d", stackdepth(currpid));
    //}
}
void f1(){
    f2();
}
