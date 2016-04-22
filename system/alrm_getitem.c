/* getitem.c - getfirst, getlast, getitem */

#include <xinu.h>
#include <alrm_queue.h>

/*------------------------------------------------------------------------
 *  getfirst  -  Remove a process from the front of a queue
 *------------------------------------------------------------------------
 */
pid32	alrm_getfirst(
	  qid16		q		/* ID of queue from which to	*/
	)				/* Remove a process (assumed	*/
					/*   valid with no check)	*/
{
	pid32	head;

	if (alrm_isempty(q)) {
		return EMPTY;
	}

	head = queuehead(q);
	return alrm_getitem(alrm_queuetab[head].qnext);
}

/*------------------------------------------------------------------------
 *  alrm_getlast  -  Remove a process from end of queue
 *------------------------------------------------------------------------
 */
pid32	alrm_getlast(
	  qid16		q		/* ID of queue from which to	*/
	)				/* Remove a process (assumed	*/
					/*   valid with no check)	*/
{
	pid32 tail;

	if (alrm_isempty(q)) {
		return EMPTY;
	}

	tail = queuetail(q);
	return alrm_getitem(alrm_queuetab[tail].qprev);
}

/*------------------------------------------------------------------------
 *  alrm_getitem  -  Remove a process from an arbitrary point in a queue
 *------------------------------------------------------------------------
 */
pid32	alrm_getitem(
	  pid32		pid		/* ID of process to remove	*/
	)
{
	pid32	prev, next;

	next = alrm_queuetab[pid].qnext;	/* Following node in list	*/
	prev = alrm_queuetab[pid].qprev;	/* Previous node in list	*/
	alrm_queuetab[prev].qnext = next;
	alrm_queuetab[next].qprev = prev;
	return pid;
}
