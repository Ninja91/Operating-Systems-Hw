/* alrm_queue.h - firstid, firstkey, isempty, lastkey, nonempty		*/

extern	struct qentry	alrm_queuetab[];
extern	qid16	alrmq;		/* queue for processes registered in alarmms	*/

/* Inline queue manipulation functions */

#define	alrm_firstid(q)	(alrm_queuetab[queuehead(q)].qnext)
#define	alrm_lastid(q)	(alrm_queuetab[queuetail(q)].qprev)
#define	alrm_isempty(q)	(alrm_firstid(q) >= NPROC)
#define	alrm_nonempty(q)	(alrm_firstid(q) <  NPROC)
#define	alrm_firstkey(q)	(alrm_queuetab[alrm_firstid(q)].qkey)
#define	alrm_lastkey(q)	(alrm_queuetab[ alrm_lastid(q)].qkey)

/* Inline to check queue id assumes interrupts are disabled */

#define	isbadqid(x)	(((int32)(x) < 0) || (int32)(x) >= NQENT-1)
