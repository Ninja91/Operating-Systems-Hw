#include <xinu.h>

void en_paging(){
  unsigned long temp;
  
  temp = 0X80000013;
  write_cr0(temp); 
}
