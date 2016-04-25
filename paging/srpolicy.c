#include <xinu.h>
int  srpolicy(
        int polcy) {  
    if(policy!=3 && policy!=4) {
        kprrintf("\n Error replaccement ploicy is not correct");
        return SYSERR;
    }

    page_replacement_policy = policy;
    return OK;

}
