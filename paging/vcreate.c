#include<xinu.h>
pid32	vcreate(
        int  * procaddr,
        int    ssize,
        int    hsize_in_pages, 
        int    priority,
        char * name,	
        int	 nargs,
        ...
        )
{
    intmask       mask;
    pid32         pid;
    struct procent * pptr;

    int bs_id;
    mask   = disable();

    pid = create(procaddr, ssize, priority, name, nargs);
    pptr = &proctab[pid];

    bs_id = allocate_bs(hsize_in_pages);
    if (bs_id == -1) {
        kprintf("No Backing store found\n");
        restore(mask);
        return SYSERR;
    }
    bstab[bs_id].status = BS_USED;
    bstab[bs_id].isvheap = 1;
    bstab[bs_id].npages = hsize_in_pages;
    bstab[bs_id].maps   = NULL;
    bstab[bs_id].frames = NULL;

    bs_add_mapping(bs_id, pid, 4096, hsize_in_pages);

    pptr->bs_id  = bs_id;
    pptr->hvpno = 4096;  
    pptr->hsize = hsize_in_pages;

    pptr->vmemlist.mnext = (struct	memblk *) (4096*NBPG);
    pptr->vmemlist.mlength = 200*NBPG;

    restore(mask);
    return pid;
}









