#include <xinu.h>

void set_PDBR(unsigned long n) {
  n = n << 12;
  write_cr3(n); 
}
