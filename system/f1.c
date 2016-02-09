#include<xinu.h>
extern uint32 stackdepth(pid32);
void f4(){
    if (4 == stackdepth(currpid)){
        kprintf("\nStack Depth: OK");
    } 
    else {
        kprintf("\nStack Depth: NOT OK  --- gives %d\n", stackdepth(currpid));
    }
}
void f3(){
    if (3 == stackdepth(currpid)){
        kprintf("\nStack Depth: OK");
    } 
    else {
        kprintf("\nStack Depth: NOT OK  --- gives %d\n", stackdepth(currpid));
    }
    f4();
}
void f2(){
    if (2 == stackdepth(currpid)){
        kprintf("\nStack Depth: OK");
    } 
    else {
        kprintf("\nStack Depth: NOT OK  --- gives %d\n", stackdepth(currpid));
    }
    f3();    
}
void f1(){
    if (1 == stackdepth(currpid)){
        kprintf("\nStack Depth: OK");
    } 
    else {
        kprintf("\nStack Depth: NOT OK  --- gives %d\n", stackdepth(currpid));
    }
    f2();
}
