/* receive.c - receive */

#include <xinu.h>
#include <receiverq.h>

/*------------------------------------------------------------------------
 *  receive  -  Wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 i*/
umsg32	receive(void)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	umsg32	msg;			/* Message to return		*/
    pid32 nextsendr;

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == FALSE) {
		prptr->prstate = PR_RECV;
		resched();		/* Block until message arrives	*/
	}
	msg = prptr->prmsg;		/* Retrieve message		*/
	prptr->prhasmsg = FALSE;	/* Reset message flag		*/
    
    while((nextsendr = receiverq_dequeue(currpid)) != EMPTY) {
        kprintf("\n Receiver blocked sources. Next sendr: %d", nextsendr);
        if (proctab[nextsendr].prstate == PR_SLEEP) {
            prptr->prmsg = proctab[nextsendr].sndmsg;
            kprintf("\n Message: %d", prptr->prmsg);
            prptr->prhasmsg = TRUE;

            proctab[nextsendr].sndflag = FALSE;
            
            unsleep(nextsendr);
            ready(nextsendr);
        } else if (proctab[nextsendr].prstate == PR_SEND) {
            prptr->prmsg = proctab[nextsendr].sndmsg;
            kprintf("\n Message: %d", prptr->prmsg);
            prptr->prhasmsg = TRUE;

            proctab[nextsendr].sndflag = FALSE;

            ready(nextsendr);
        } else {
            continue;
        }
        break;
    }

	restore(mask);
	return msg;
}
