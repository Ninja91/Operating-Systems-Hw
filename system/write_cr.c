#include <xinu.h>

unsigned long tmp;
void write_cr(int reg, unsigned long n) {
  intmask mask;
  
  mask = disable();
  tmp = n;

  asm("pushl %eax");
  asm("movl tmp, %eax");		

  switch(reg) {
    case 0:
        asm("movl %eax, %cr0");
        break;

    case 3:
        asm("movl %eax, %cr3");
        break;

    case 4:
        asm("movl %eax, %cr4");
        break;

    default:
        kprintf("\n Error in write_cr");
        return 0;
  }
  asm("popl %eax");

  restore(mask);

}

void write_cr0(unsigned long n) {
    write_cr(0, n);
}
void write_cr3(unsigned long n) {
    write_cr(3, n);
}
void write_cr4(unsigned long n) {
    write_cr(4, n);
}
