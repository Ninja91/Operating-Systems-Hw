/* send.c - send */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  send  -  Pass a message to a process and start recipient if waiting
 *------------------------------------------------------------------------
 */
syscall	sendbt(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32	msg,    	/* Contents of message		*/
      int32     wait
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];

    if (wait < 0) {
            return SYSERR;
    } 
    else if ((prptr->prstate != PR_FREE) && !prptr->prhasmsg) {
    	prptr->prmsg = msg;		/* Deliver message		*/
	    prptr->prhasmsg = TRUE;		/* Indicate message is waiting	*/
    }
    else if(wait > 0) {
            proctab[currpid].sndmsg = msg;
            proctab[currpid].sndflag = TRUE;
            receiverq_enqueue(pid);
		    restore(mask);
            sleepms(wait);

            mask = disable();
            proctab[currpid].sndflag = FALSE;
            restore(mask);
            return SYSERR;
    } 
    else {
            proctab[currpid].sndmsg = msg;
            proctab[currpid].sndflag = TRUE;
            proctab[currpid].prstate = PR_SEND;

            receiverq_enqueue(pid);
            resched();
	}

	/* If recipient waiting or in timed-wait make it ready */

	if (prptr->prstate == PR_RECV) {
		ready(pid);
    }
	else if (prptr->prstate == PR_RECTIM) {
		unsleep(pid);
		ready(pid);
	}
	restore(mask);		/* Restore interrupts */
	return OK;
}
