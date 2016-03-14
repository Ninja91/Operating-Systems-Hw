/* resched.c - resched, resched_cntl */
#include <xinu.h>
#include <lab2.h>
#include <ts_disptb.h>
#include <multilevelfbq.h>

#ifdef LAB2_HEADER
#define LAB2COND (lab2flag == 4 || lab2flag == 5)
#else
#define LAB2COND 0
#endif

struct	defer	Defer;
int timescliceconsumed;
/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/
    pri16 oldprio;

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

    /* Calculating CPU time used by the old process*/
    ptold->prcpumsec += clktimemsec - ptold->prctxswintime;

    /**
     * Updating old proess with new priority.*/
    oldprio = ptold->prprio;
    if(currpid != 0 && timescliceconsumed == 0){
       ptold->prprio = tsdtab[oldprio].ts_slpret;
    } 
    else {
        ptold->prprio = tsdtab[oldprio].ts_tqexp;
        timescliceconsumed = 0;
    }
	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
        if (LAB2COND){

            /*Updating (Actually demoting )the priority of running process by adding the cpu cycles to its priority*/
            /* Clamping prioriy to max value */
            ptold->prprio = MIN(MAXKEY, ptold->initprio + ptold->prcpumsec);

            if (lab2q5sol == 2) {
                int no_rady_procs = 0;
                int16 cycles_in_slice_used = clktimemsec - ptold->prctxswintime;
                pid32 pid;
               
                /* Counting the number of processes in the ready list currently*/
                for(pid = firstid(readylist); queuetab[pid].qnext != EMPTY; pid = queuetab[pid].qnext)
                    no_rady_procs++;
                
                /* Computing the new priority of processes in the ready list and updating in proctab and queutab.*/
                for(pid = firstid(readylist); queuetab[pid].qnext != EMPTY; pid = queuetab[pid].qnext){

                    if (pid > 2) // To ensure that only application processes are evaluated. Not even main is considered.
                        proctab[pid].prcpu_wait_ratio += cycles_in_slice_used / (no_rady_procs * QUANTUM);

                    proctab[pid].prprio -= proctab[pid].prcpu_wait_ratio;
                    queuetab[pid].qkey = proctab[pid].prprio;
                }
            }

            /* Reversing the priority order in case of Dynamic Process Scheduling (Q4 and Q5.) */
            if (ptold->prprio < firstkey(readylist)) {
                return;
            }
        }
        else {
            /* kprintf("\nptold->prprio = %d, firstkey: %d",ptold->prprio, firstkey(readylist)); */
            if (ptold->prprio > firstkey(readylist)) {
                preempt = tsdtab[ptold->prprio].ts_quantum;
			    return;
		    }
        }

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
		mltfbq_insert(currpid, readylist, ptold->prprio);
	}

	/* Force context switch to highest priority ready process */

	currpid = mltfbq_dequeue(readylist);
    /* kprintf("\n currpid = %d",currpid); */
	
    ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = tsdtab[ptnew->prprio].ts_quantum;		/* Reset time slice for process	*/
    
    /* Setting the context time in variable for the new process to keep track of the CPU cycles consumed by this process*/
    ptnew->prctxswintime = clktimemsec;
   
    ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
