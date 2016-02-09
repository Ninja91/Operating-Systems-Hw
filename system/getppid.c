/* getppid.c - getppid */
#include<xinu.h>
 
/*------------------------------------------------------------------------
 *  getppid  -  Return the ID of the parent process of currently executing process
 *------------------------------------------------------------------------
 */
pid32	getppid(void)
{
    struct procent *procent_struct;
    procent_struct = &proctab[currpid];
	return (procent_struct->prparent);
}
