#include <xinu.h>

unsigned long tmp;
unsigned long read_cr(int reg) {
    unsigned long a;
    intmask mask;

    mask = disable();

    asm("pushl %eax");
    switch (reg) {
        case 0: 
        asm("movl %cr0, %eax");
        break;
        
        case 2:
        asm("movl %cr2, %eax");
        break;
        
        case 3:
        asm("movl %cr3, %eax");
        break;
        
        case 4:
        asm("movl %cr4, %eax");
        break;

        default:
        kprintf ("\nError in reading cr");
        return 0;
    }

    asm("movl %eax, tmp");
    asm("popl %eax");
    a = tmp;

    restore(mask);
    return a;
}

unsigned long read_cr0(void) {
    return read_cr(0);
}
unsigned long read_cr2(void) {
    return read_cr(2);
}
unsigned long read_cr3(void) {
    return read_cr(3);
}
unsigned long read_cr4(void) {
    return read_cr(4);
}
