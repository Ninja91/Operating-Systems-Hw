#include <xinu.h>

syscall registercb( int (*func) (void *)) {
   intmask mask;

   mask = disable();
   if (!func) {
   	restore(mask);
   	return (SYSERR);
   }
   
   proctab[currpid].hascbfunct = TRUE;
   proctab[currpid].regcbfuncptr = func;

   restore(mask);
   return (OK);
}
