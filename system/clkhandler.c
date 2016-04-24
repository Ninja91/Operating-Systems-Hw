/* clkhandler.c - clkhandler */

#include <xinu.h>

/*------------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *------------------------------------------------------------------------
 */
extern int timescliceconsumed;
void	clkhandler()
{
	static	uint32	count1000 = 1000;	/* Count to 1000 ms	*/

	/* Decrement the ms counter, and see if a second has passed */

    /* Variable to count time in msec */
    clktimemsec++;
	if((--count1000) <= 0) {

		/* One second has passed, so increment seconds count */

		clktime++;

		/* Reset the local ms counter for the next second */

		count1000 = 1000;
	}

	/** SigxCpu case*/
    /* if (proctab[currpid]->hassigxcpu == TRUE) */ 
    /*     kprintf("\nPID: %d\n sigarg %d\n",currpid, proctab[currpid]sigarg); */
	if(proctab[currpid].hassigxcpu == TRUE && (--(proctab[currpid].sigarg)) <= 0) {
		proctab[currpid].hassigxcpu = FALSE;
        proctab[currpid].prcpumsec += clktimemsec - proctab[currpid].prctxswintime;
        proctab[currpid].prctxswintime = clktimemsec;
		proctab[currpid].regcbfuncptr();
	}
	/* Handle processes in alarm queue if any exist */

	if(!alrm_isempty(alrmq)) {

		if((--alrm_queuetab[alrm_firstid(alrmq)].qkey) <= 0) {
			alrm_wakeup();
		}
	}
	/* Handle sleeping processes if any exist */

	if(!isempty(sleepq)) {

		/* Decrement the delay for the first process on the	*/
		/*   sleep queue, and awaken if the count reaches zero	*/

		if((--queuetab[firstid(sleepq)].qkey) <= 0) {
			wakeup();
		}
	}

	/* Decrement the preemption counter, and reschedule when the */
	/*   remaining time reaches zero			     */

	if((--preempt) <= 0) {
        timescliceconsumed = 1;
		preempt = QUANTUM;
		resched();
	}
}
