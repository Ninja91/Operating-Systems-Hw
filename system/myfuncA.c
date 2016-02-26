#include <xinu.h>
static unsigned long	*esp;
char myfuncA(int x){
    unsigned long * topsp;

    asm("movl %esp, esp");
    topsp = esp;
    kprintf("\ncurrpid : %d\n", currpid);
    kprintf("\nWhile myfuncA is called and nefore it has returned\n");
    kprintf("run-time stack top : address = 0x%x, content = 0x%x\n", topsp, (unsigned long *) *topsp);

    return x > 0 ? (x %26) + 'A' : ((-x) % 26) + 'a';
}
