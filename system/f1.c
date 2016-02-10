#include<xinu.h>
extern uint32 stackdepth();
void f4(){
    if (4 == stackdepth()){
        kprintf("\nStack Depth: OK");
    } 
    else {
        kprintf("\nStack Depth: NOT OK  --- gives %d\n", stackdepth());
    }
}
void f3(){
    if (3 == stackdepth()){
        kprintf("\nStack Depth: OK");
    } 
    else {
        kprintf("\nStack Depth: NOT OK  --- gives %d\n", stackdepth());
    }
    f4();
}
void f2(){
    if (2 == stackdepth()){
        kprintf("\nStack Depth: OK");
    } 
    else {
        kprintf("\nStack Depth: NOT OK  --- gives %d\n", stackdepth());
    }
    f3();    
}
void f1(){
    if (1 == stackdepth()){
        kprintf("\nStack Depth: OK");
    } 
    else {
        kprintf("\nStack Depth: NOT OK  --- gives %d\n", stackdepth());
    }
    f2();
}
