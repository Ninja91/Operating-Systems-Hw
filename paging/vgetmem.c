#include <xinu.h>
char  	*vgetmem(
	  uint32	nbytes
	)
{
	struct	memblk	*prev_node, *cur_node, *leftover;
    struct procent * pptr;
	intmask	mask;
    pptr = &proctab[currpid];

	mask = disable();
	if (nbytes == 0) {
		restore(mask);
		return (char *)SYSERR;
	}

	nbytes = (uint32) roundmb(nbytes);

	prev_node = &(pptr->vmemlist);
	cur_node = prev_node->mnext;

	while (cur_node) {
		if (cur_node->mlength == nbytes) {	
			prev_node->mnext = cur_node->mnext;
			(pptr->vmemlist).mlength -= nbytes;
			restore(mask);
			return (char *)(cur_node);

		} else if (cur_node->mlength > nbytes) { 
			leftover = (struct memblk *)((uint32) cur_node + nbytes);
			prev_node->mnext = leftover;
			leftover->mnext = cur_node->mnext;
			leftover->mlength = cur_node->mlength - nbytes;
			(pptr->vmemlist).mlength -= nbytes;
			restore(mask);
			return (char *)(cur_node);
		} else {		
			prev_node = cur_node;
			cur_node = cur_node->mnext;
		}
	}
	restore(mask);
	return (char *)SYSERR;
}
