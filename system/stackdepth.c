#include <xinu.h>
static unsigned long	*esp;
static unsigned long	*ebp;

/*------------------------------------------------------------------------
 * stackdepth - print a stack depth process
 *------------------------------------------------------------------------
 */
uint32 stackdepth(int pid)
{
	struct procent	*proc = &proctab[pid];
	unsigned long	*topsp, *topfp;
    uint32 cnt = 0;

	if (pid != 0 && isbadpid(pid))
		return SYSERR;
	if (pid == currpid) {
        //kprintf("\nUsing currpid\n");
		asm("movl %esp,esp");
		asm("movl %ebp,ebp");
		topsp = esp;
		topfp = ebp;
	} else {
        //kprintf("\nNot Using\n");
		topsp = (unsigned long *)proc->prstkptr;
		topfp = topsp + 2; 		
	}
    
	kprintf("\n\ntopsp %X topfp %X \n", topsp, topfp);
    while(topfp < (unsigned long *)proc->prstkbase){
        cnt++;
        topfp = *topfp;
    }
	return cnt - 1;
}
