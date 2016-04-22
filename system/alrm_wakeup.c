/* alrm_wakeup.c - alrm_wakeup */

#include <xinu.h>
#include <alrm_queue.h>
/*------------------------------------------------------------------------
 *  alrm_wakeup  -  Called by clock interrupt handler to alarm a processes
 *------------------------------------------------------------------------
 */
void	alrm_wakeup(void)
{
	/* Awaken all processes that have no more time to sleep */
    pid32 prpid;
	resched_cntl(DEFER_START);
	while (alrm_nonempty(alrmq) && (alrm_firstkey(alrmq) <= 0)) {
		prpid = alrm_dequeue(alrmq);
        if (proctab[prpid].prstate == PR_SLEEP) {
            unsleep(prpid);
        }
        proctab[prpid].sigarg = 1;
        ready(prpid);

	}

	resched_cntl(DEFER_STOP);
	return;
}
