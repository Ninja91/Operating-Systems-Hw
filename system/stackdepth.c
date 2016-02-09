#include <xinu.h>
static unsigned long	*esp;
static unsigned long	*ebp;

/*------------------------------------------------------------------------
 * stackdepth - print a stack depth process
 *------------------------------------------------------------------------
 */
#define DEBUG
uint32 stackdepth(pid32 pid)
{
	struct procent	*proc = &proctab[pid];
	unsigned long	*topsp, *topfp;
    uint32 cnt = 0;

	if (pid == currpid) {
		asm("movl %esp,esp");
		asm("movl %ebp,ebp");
		topsp = esp;
		topfp = ebp;
	} else {
		topsp = (unsigned long *)proc->prstkptr;
		topfp = topsp + 2; 		
	}
 
#ifdef DEBUG
	kprintf("\n\nesp %X ebp %X \n", topsp, topfp);
#endif

    while(topfp < (unsigned long *)proc->prstkbase){
        kprintf("\n\nStack frame from top %d : ebp = %X, size = %d\n", cnt, topfp, (unsigned long *) *topfp - topfp);
        cnt++;
        topfp = (unsigned long *) *topfp;
    }
	return cnt - 1;
}
