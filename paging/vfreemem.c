#include <xinu.h>
/*------------------------------------------------------------------------
 *  freemem  -  Free a memory block, returning the block to the free list
 *------------------------------------------------------------------------
 */
syscall	vfreemem(
        char		*block_ptr,	/* Pointer to memory block	*/
        uint32	size_in_bytes		/* Size of block in bytes	*/
        )
{
    intmask	mask;
    uint32	top;
    struct	memblk	*curr, *next, *block;
    struct procent * pptr;

    mask = disable();
    
    if ((size_in_bytes == 0) || ((uint32) block_ptr < (uint32) (NBPG*4096)))
    {
        restore(mask);
        return SYSERR;
    }

    size_in_bytes = (uint32) roundmb(size_in_bytes);
    block = (struct memblk *)block_ptr;
    pptr = &proctab[currpid];

    curr = &(pptr->vmemlist);			/* Walk along free list	*/
    next = curr->mnext;
    while ((next != NULL) && (next < block)) {
        curr = next;
        next = next->mnext;
    }

    if (curr == &(pptr->vmemlist)) {		/* Compute top of previous block*/
        top = (uint32) NULL;
    } else {
        top = (uint32) curr + curr->mlength;
    }

    if (((curr != &(pptr->vmemlist)) && (uint32) block < top)
            || ((next != NULL)	&& (uint32) block+size_in_bytes>(uint32)next)) {
        restore(mask);
        return SYSERR;
    }

    (pptr->vmemlist).mlength += size_in_bytes;

    if (top == (uint32) block) { 
        curr->mlength += size_in_bytes;
        block = curr;
    } else {		
        block->mnext = next;
        block->mlength = size_in_bytes;
        curr->mnext = block;
    }

    if (((uint32) block + block->mlength) == (uint32) next) {
        block->mlength += next->mlength;
        block->mnext = next->mnext;
    }
    restore(mask);
    return OK;
}
