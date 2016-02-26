/* newqueue.c - newqueue */

#include <xinu.h>
#include <lab2.h>

/* Handling the rescheduler changes for different parts of the question*/
#ifdef LAB2_HEADER
#define LAB2COND (lab2flag == 4 || lab2flag == 5)
#else
#define LAB2COND 0
#endif
/*------------------------------------------------------------------------
 *  newqueue  -  Allocate and initialize a queue in the global queue table
 *------------------------------------------------------------------------
 */
qid16	newqueue(void)
{
	static qid16	nextqid=NPROC;	/* Next list in queuetab to use	*/
	qid16		q;		/* ID of allocated queue 	*/

	q = nextqid;
	if (q > NQENT) {		/* Check for table overflow	*/
		return SYSERR;
	}

	nextqid += 2;			/* Increment index for next call*/

	/* Initialize head and tail nodes to form an empty queue */

	queuetab[queuehead(q)].qnext = queuetail(q);
	queuetab[queuehead(q)].qprev = EMPTY;
    /* Reversing the priority order in case of Dynamic Process Scheduling (Q4 and Q5.) */
    /* The head of queue gets the minimum value as priority*/
	if (LAB2COND) 
        queuetab[queuehead(q)].qkey  = MINKEY;
    else
        queuetab[queuehead(q)].qkey  = MAXKEY;

	queuetab[queuetail(q)].qnext = EMPTY;
	queuetab[queuetail(q)].qprev = queuehead(q);
    /* Reversing the priority order in case of Dynamic Process Scheduling (Q4 and Q5.) */
    /* The tail of queue gets the maximum value as priority*/
	if (LAB2COND)
        queuetab[queuetail(q)].qkey  = MAXKEY;
    else
        queuetab[queuetail(q)].qkey  = MINKEY;
	return q;
}
