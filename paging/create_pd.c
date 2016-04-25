#include <xinu.h>

/*
 * This function creates page directory */
pd_t * create_pd()
{
    frame_t * frame;
    frame = create_frame();   
    frame->type = FRAME_PD; 
    pd_t  *pd;
    pd = (pd_t *)((((frame->frame_no)+1024)*NBPG)); 
    int i;
    for(i=0;i<1024;i++)
    {
        if(i<4) {
            pd[i].pd_pres  = 1;
            pd[i].pd_write = 1;
            pd[i].pd_avail = 1; 
            pd[i].pd_base  = ((unsigned int)(glb_pg_tab[i])/NBPG); 
        }
        else if(i == 576) {
            pd[i].pd_pres  = 1;
            pd[i].pd_write = 1;
            pd[i].pd_avail = 1; 
            pd[i].pd_base  = ((unsigned int)(glb_pg_tab[4])/NBPG); 
        }
        else {
            pd[i].pd_pres  = 0;       /* page table present?      */
            pd[i].pd_write = 0;       /* page is writable?        */
            pd[i].pd_avail = 0;       /* for programmer's use     */
            pd[i].pd_base  = 0;       /* location of page table?  */
        }
        pd[i].pd_user  = 0;       /* is user level protection? */
        pd[i].pd_pwt   = 0;       /* write through caching for pt?*/
        pd[i].pd_pcd   = 0;       /* cache disable for this pt?   */
        pd[i].pd_acc   = 0;       /* page table was accessed? */
        pd[i].pd_mbz   = 0;       /* must be zero         */
        pd[i].pd_fmb   = 0;       /* four MB pages?       */
        pd[i].pd_global= 0;  

    }
    return pd;
}


