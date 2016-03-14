#include <xinu.h>
#include <lab2.h>
#include <ts_disptb.h>
#include <multilevelfbq.h>

/*------------------------------------------------------------------------
 *  insert  -  Insert a process into a queue in descending key order
 *------------------------------------------------------------------------
 */
status	mltfbq_insert(
	  pid32		pid,		/* ID of process to insert	*/
	  qid16		q,		/* ID of queue to use		*/
	  int32		key		/* Key for the inserted process	*/
	)
{
	int16	curr;			/* Runs through items in a queue*/
	int16	prev;			/* Holds previous node index	*/
	int16	next;			/* Holds previous node index	*/
    pri16 prprio;

	if (isbadqid(q) || isbadpid(pid)) {
		return SYSERR;
	}

	curr = firstid(q);

    prprio = proctab[pid].prprio;
    /* kprintf("\ninsert called with pid : %d and q= %d and readylist = %d", pid, q, readylist); */
    
    if (q == readylist){
       curr = queuetab[curr].qprev ;

        while(is_mltfbq_empty(prprio)) {
            prprio++;
            if(prprio == NOF_PRIOIRITIES){
                break;
            }
        }

        /* kprintf("\npid : %d, prprio = %d", pid, prprio); */
        if (prprio < NOF_PRIOIRITIES)
            curr = multilevelfbqueue[prprio].tail;

        prprio = proctab[pid].prprio;
        /* Insert process between curr node and previous node */

        next = queuetab[curr].qnext;
        queuetab[pid].qnext = next;
        queuetab[pid].qprev = curr;
        queuetab[pid].qkey = prprio;
        queuetab[curr].qnext = pid;
        queuetab[next].qprev = pid;

        if (prprio != proctab[curr].prprio) {
            multilevelfbqueue[prprio].head = pid;
            multilevelfbqueue[prprio].tail = pid;
        }
        else {
            multilevelfbqueue[prprio].tail = pid;
        }
    }
    else{
        insert(pid, q, key);
    }

    /* prev = queuetab[curr].qprev;	/1* Get index of previous node	*/
	/* queuetab[pid].qnext = curr; */
	/* queuetab[pid].qprev = prev; */
	/* queuetab[pid].qkey = key; */
	/* queuetab[prev].qnext = pid; */
	/* queuetab[curr].qprev = pid; */
	return OK;
}
