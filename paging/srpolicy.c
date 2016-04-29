#include <xinu.h>
int  srpolicy(
        int polcy) {  
    if(polcy!=3 && polcy!=4) {
        kprintf("\n Error replaccement ploicy is not correct");
        return SYSERR;
    }

    page_replacement_policy = polcy;
    return OK;

}
