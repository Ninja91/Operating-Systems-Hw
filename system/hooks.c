#include <xinu.h>
#define LOGGING_ON

void hook_ptable_create(unsigned int p)
{
#ifdef LOGGING_ON
    kprintf("\n=== Created page table %d\n", p);
#endif
}

void hook_ptable_delete(unsigned int p)
{
#ifdef LOGGING_ON
    kprintf("\n=== Deleted page table %d\n", p);
#endif
}

void hook_pfault(char *addr)
{
#ifdef LOGGING_ON
    kprintf("\n=== Page fault for address %d\n", addr);
#endif
}

void hook_pswap_out(unsigned int pagenum, int framenum)
{
#ifdef LOGGING_ON
    kprintf("\n=== Replacing frame number %d, virtual page %d", framenum, pagenum);
#endif
}
