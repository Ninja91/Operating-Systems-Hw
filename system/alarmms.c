/* alarmms.c - alarmms */

#include <xinu.h>
#include <alrm_queue.h>

#define	MAXSECONDS	4294967		/* Max seconds per 32-bit msec	*/

/*------------------------------------------------------------------------
 * alarmms  -  Registers an alarm for the calling process and n milliseconds
 *------------------------------------------------------------------------
 */
syscall	alarmms(
	  uint32	delay		/* Time to delay in msec.	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/

	mask = disable();
	if (delay == 0) {
		yield();
		restore(mask);
		return OK;
	}

    /* alrmq is the alarm queue */
	if (alrm_insertd(currpid, alrmq, delay) == SYSERR) {
		restore(mask);
		return SYSERR;
	}

	restore(mask);
	return OK;
}
