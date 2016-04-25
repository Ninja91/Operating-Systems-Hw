#include <xinu.h>
void hook_ptable_create(unsigned int p)
{
    kprintf("\n=== Created page table %d\n", p);
}

void hook_ptable_delete(unsigned int p)
{
    kprintf("\n=== Deleted page table %d\n", p);
}

void hook_pfault(char *addr)
{
    kprintf("\n=== Page fault for address %d\n", addr);
}

void hook_pswap_out(unsigned int pagenum, int framenum)
{
    kprintf("\n=== Replacing frame number %d, virtual page %d", framenum, pagenum);
}
