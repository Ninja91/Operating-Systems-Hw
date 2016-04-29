#include <xinu.h>
char  	*vgetmem(
	  uint32	nbytes
	)
{
	struct	memblk	*prev_node, *cur_node, *leftover;
    struct procent * pptr;
    pptr = &proctab[currpid];

	intmask mask = disable();
	
    if (nbytes == 0) {
		kprintf("\nnbytes  = 0\n");
        restore(mask);
		return (char *)SYSERR;
	}


	prev_node = &(pptr->vmemlist);
	cur_node = prev_node->mnext;
	nbytes = (uint32) roundmb(nbytes);

	while (cur_node) {
		if (cur_node->mlength == nbytes) {	
			(pptr->vmemlist).mlength -= nbytes;
			prev_node->mnext = cur_node->mnext;
			restore(mask);
            kprintf("\nIn vgetmem %d",cur_node);
			return (char *)(cur_node);

		} else if (cur_node->mlength > nbytes) { 
			leftover = (struct memblk *)((uint32) cur_node + nbytes);
			prev_node->mnext = leftover;
			(pptr->vmemlist).mlength -= nbytes;
			leftover->mnext = cur_node->mnext;
			leftover->mlength = cur_node->mlength - nbytes;
			restore(mask);
            kprintf("\nIn vgetmem %d",cur_node);
			return (char *)(cur_node);
		} else {		
			prev_node = cur_node;
			cur_node = cur_node->mnext;
            kprintf("\nIn vgetmem else section %d",cur_node);
		}
	}
	restore(mask);
    kprintf("\nError in vgetmem");
	return (char *)SYSERR;
}
