/* alrm_insertd.c - alrm_insertd */

#include <xinu.h>
#include <alrm_queue.h>

/*------------------------------------------------------------------------
 *  alrm_insertd  -  Insert a process in delta list using delay as the key
 *------------------------------------------------------------------------
 */
status	alrm_insertd(			/* Assumes interrupts disabled	*/
	  pid32		pid,		/* ID of process to insert	*/
	  qid16		q,		/* ID of queue to use		*/
	  int32		key		/* Delay from "now" (in ms.)	*/
	)
{
	int32	next;			/* Runs through the delta list	*/
	int32	prev;			/* Follows next through the list*/

	if (isbadqid(q) || isbadpid(pid)) {
		return SYSERR;
	}

	prev = queuehead(q);
	next = alrm_queuetab[queuehead(q)].qnext;
	while ((next != queuetail(q)) && (alrm_queuetab[next].qkey <= key)) {
		key -= alrm_queuetab[next].qkey;
		prev = next;
		next = alrm_queuetab[next].qnext;
	}

	/* Insert new node between prev and next nodes */

	alrm_queuetab[pid].qnext = next;
	alrm_queuetab[pid].qprev = prev;
	alrm_queuetab[pid].qkey = key;
	alrm_queuetab[prev].qnext = pid;
	alrm_queuetab[next].qprev = pid;
	if (next != queuetail(q)) {
		alrm_queuetab[next].qkey -= key;
	}

	return OK;
}
