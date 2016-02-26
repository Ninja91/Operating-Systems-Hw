/* resched.c - resched, resched_cntl */
#include <xinu.h>
#include <lab2.h>

#ifdef LAB2_HEADER
#define LAB2COND (lab2flag == 4 || lab2flag == 5)
#else
#define LAB2COND 0
#endif

struct	defer	Defer;
/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

    /* Calculating CPU time used by the old process*/
    ptold->prcpumsec += clktimemsec - ptold->prctxswintime;

	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
        if (LAB2COND){
            /*Updating (Actually demoting )the priority of running process by adding the cpu cycles to its priority*/
            /* Clamping prioriy to max value */
            ptold->prprio = MIN(MAXKEY, ptold->initprio + ptold->prcpumsec);

            //kprintf("\nPID: %d, clktimemsec: %d ctxtintime: %d \n", currpid, clktimemsec, prctxswintime);
            /* kprintf("\nPID: %d, prcpumsec: %d \n", currpid, ptold->prcpumsec); */
           
            /* Reversing the priority order in case of Dynamic Process Scheduling (Q4 and Q5.) */
            if (ptold->prprio < firstkey(readylist)) {
                return;
            }
        }
        else {
            if (ptold->prprio > firstkey(readylist)) {
			    return;
		    }
        }

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
		insert(currpid, readylist, ptold->prprio);
	}

	/* Force context switch to highest priority ready process */

	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = QUANTUM;		/* Reset time slice for process	*/
    
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
