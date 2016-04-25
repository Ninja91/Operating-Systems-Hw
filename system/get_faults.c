#include <xinu.h>
unsigned int no_of_page_faults = 0;

int get_faults()
{
    no_of_page_faults++;
    kprintf("The number of times page fault handler is called is %d\n",no_of_page_faults);
}
