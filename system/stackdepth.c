#include <xinu.h>
static unsigned long	*esp;
static unsigned long	*ebp;

/*------------------------------------------------------------------------
 * stackdepth - print a stack depth process
 *------------------------------------------------------------------------
 */
#define DEBUG
uint32 stackdepth()
{
	struct procent	*proc = &proctab[currpid];
	unsigned long	*topsp, *topbp;
    uint32 cnt = 0;

    asm("movl %esp,esp");
    asm("movl %ebp,ebp");
    topsp = esp;
    topbp = ebp;
 
#ifdef DEBUG
	kprintf("\n\nesp %X ebp %X \n", topsp, topbp);
#endif

    while(topbp < (unsigned long *)proc->prstkbase){
        kprintf("\n\nStack frame from top %d : ebp = %X, size = %d\n", cnt, topbp, (unsigned long *) *topbp - topbp);
        cnt++;
        topbp = (unsigned long *) *topbp;
    }
	return cnt - 1;
}
