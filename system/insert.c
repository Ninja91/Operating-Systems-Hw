/* insert.c - insert */

#include <xinu.h>
#include <lab2.h>


/* Handling the rescheduler changes for different parts of the question*/
#ifdef LAB2_HEADER
#define LAB2COND (lab2flag == 4 || lab2flag == 5)
#else
#define LAB2COND 0
#endif
/*------------------------------------------------------------------------
 *  insert  -  Insert a process into a queue in descending key order
 *------------------------------------------------------------------------
 */
status	insert(
	  pid32		pid,		/* ID of process to insert	*/
	  qid16		q,		/* ID of queue to use		*/
	  int32		key		/* Key for the inserted process	*/
	)
{
	int16	curr;			/* Runs through items in a queue*/
	int16	prev;			/* Holds previous node index	*/

	if (isbadqid(q) || isbadpid(pid)) {
		return SYSERR;
	}

	curr = firstid(q);
    if (LAB2COND) {
        while (queuetab[curr].qkey <= key) { /* Changing to Linux/BSD format of priority representation where lower value means higher priority*/
            curr = queuetab[curr].qnext;
        }
    } 
    else {
        while (queuetab[curr].qkey >= key) { 
            curr = queuetab[curr].qnext;
        }
    }

	/* Insert process between curr node and previous node */

	prev = queuetab[curr].qprev;	/* Get index of previous node	*/
	queuetab[pid].qnext = curr;
	queuetab[pid].qprev = prev;
	queuetab[pid].qkey = key;
	queuetab[prev].qnext = pid;
	queuetab[curr].qprev = pid;
	return OK;
}
