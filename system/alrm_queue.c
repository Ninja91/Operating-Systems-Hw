/* alrm_queue.c - alrm_enqueue, alrm_dequeue */

#include <xinu.h>
#include <alrm_queue.h>

struct qentry	alrm_queuetab[NQENT];	/* Table of process queues	*/

/*------------------------------------------------------------------------
 *  alrm_enqueue  -  Insert a process at the tail of a queue
 *------------------------------------------------------------------------
 */
pid32	alrm_enqueue(
	  pid32		pid,		/* ID of process to insert	*/
	  qid16		q		/* ID of queue to use		*/
	)
{
	int	tail, prev;		/* Tail & previous node indexes	*/

	if (isbadqid(q) || isbadpid(pid)) {
		return SYSERR;
	}

	tail = queuetail(q);
	prev = alrm_queuetab[tail].qprev;

	alrm_queuetab[pid].qnext  = tail;	/* Insert just before tail node	*/
	alrm_queuetab[pid].qprev  = prev;
	alrm_queuetab[prev].qnext = pid;
	alrm_queuetab[tail].qprev = pid;
	return pid;
}

/*------------------------------------------------------------------------
 *  alrm_dequeue  -  Remove and return the first process on a list
 *------------------------------------------------------------------------
 */
pid32	alrm_dequeue(
	  qid16		q		/* ID queue to use		*/
	)
{
	pid32	pid;			/* ID of process removed	*/

	if (isbadqid(q)) {
		return SYSERR;
	} else if (alrm_isempty(q)) {
		return EMPTY;
	}

	pid = alrm_getfirst(q);
	alrm_queuetab[pid].qprev = EMPTY;
	alrm_queuetab[pid].qnext = EMPTY;
	return pid;
}

/*------------------------------------------------------------------------
 *  newqueue  -  Allocate and initialize a queue in the global queue table
 *------------------------------------------------------------------------
 */
qid16	alrm_newqueue(void)
{
	static qid16	nextqid=NPROC;	/* Next list in alrm_queuetab to use	*/
	qid16		q;		/* ID of allocated queue 	*/

	q = nextqid;
	if (q > NQENT) {		/* Check for table overflow	*/
		return SYSERR;
	}

	nextqid += 2;			/* Increment index for next call*/

	/* Initialize head and tail nodes to form an empty queue */

	alrm_queuetab[queuehead(q)].qnext = queuetail(q);
	alrm_queuetab[queuehead(q)].qprev = EMPTY;
    /* Reversing the priority order in case of Dynamic Process Scheduling (Q4 and Q5.) */
    /* The head of queue gets the minimum value as priority*/
    alrm_queuetab[queuehead(q)].qkey  = MAXKEY;

	alrm_queuetab[queuetail(q)].qnext = EMPTY;
	alrm_queuetab[queuetail(q)].qprev = queuehead(q);
    /* Reversing the priority order in case of Dynamic Process Scheduling (Q4 and Q5.) */
    /* The tail of queue gets the maximum value as priority*/
    alrm_queuetab[queuetail(q)].qkey  = MINKEY;
	return q;
}
