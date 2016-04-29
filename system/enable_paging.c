#include <xinu.h>

void enable_paging(){
  unsigned long en_pg = 0X80000013;
  write_cr0(en_pg); 
}
