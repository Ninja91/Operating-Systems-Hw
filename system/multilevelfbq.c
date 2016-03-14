/* queue.c - enqueue, dequeue */

#include <xinu.h>
#include <ts_disptb.h>
#include <multilevelfbq.h>

struct mltfb_qentry multilevelfbqueue[NOF_PRIOIRITIES];	/* Table of process queues	*/
struct mltfb_qentry receiverqueue[NPROC][NPROC];	/* Table of process queues	*/

/*------------------------------------------------------------------------
 *  initiialize_mltfbq  -  Initialize multilevelfbqueue queue
 *------------------------------------------------------------------------
 */
void initialize_mltfbq(){
    int i;
    for(i = 0; i < NOF_PRIOIRITIES; i++) {
        multilevelfbqueue[i].head = EMPTY;
        multilevelfbqueue[i].tail = EMPTY;
    }

    /**
     * Initializing ready queue start and end*/
    queuetab[queuehead(readylist)].qkey = MAXPRIO;
    queuetab[queuetail(readylist)].qkey = MINPRIO;
}

/*------------------------------------------------------------------------
 *  dequeue  -  Remove and return the first process on a list
 *------------------------------------------------------------------------
 */
pid32	mltfbq_dequeue(
	  qid16		q		/* ID queue to use		*/
	)
{
	pid32	pid;			/* ID of process removed	*/
    int priority_level;

	if (isbadqid(q)) {
		return SYSERR;
	} else if (isempty(q)) {
		return EMPTY;
	}
  
    pid = getfirst(q);
    /* kprintf("\nfirst PID: %d", pid); */
    if (q == readylist) {
        pri16 prio = proctab[pid].prprio;
        pid32 next = queuetab[pid].qnext;
        
        if (next == queuetail(q) || proctab[next].prprio != prio) {
            multilevelfbqueue[prio].head = EMPTY;
            multilevelfbqueue[prio].tail = EMPTY;
        }
        else {
            multilevelfbqueue[prio].head = next;
        }
    }

	queuetab[pid].qprev = EMPTY;
	queuetab[pid].qnext = EMPTY;
	return pid;
}
