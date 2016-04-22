#include <xinu.h>
#include <mysignal.h>
syscall registercbsig(
        uint16 asig, 
        int (*func) (void *),
        uint32 optarg) {
   intmask mask;

   mask = disable();
   if (!func) {
   	restore(mask);
   	return (SYSERR);
   }
   
   switch(asig) {
        case MYSIGRECV :
            registercb(func);
            break;
        case MYSIGXCPU :
            proctab[currpid].hassigxcpu = TRUE;
            proctab[currpid].regcbfuncptr = func;
            proctab[currpid].sigarg = optarg;
            break;
        case MYSIGALRM:
            proctab[currpid].hassigalrm = TRUE;
            proctab[currpid].regcbfuncptr = func;
            proctab[currpid].sigarg = 0; /*Now this will act as flag which will tell resched when to call the call back function 
                                           after waking up from alarm*/
            break;

   }

   restore(mask);
   return (OK);
}
