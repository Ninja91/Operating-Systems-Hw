#include <xinu.h>

/*
 * This function creates a page table
 * */

pt_t * create_pt() 
{ 
    frame_t * frame;
    int i;
    
    frame = create_frame();     //first get a frame
    frame->type = FRAME_PT;     //indicate that the frame is used for a page table
    pt_t    * pt;
    pt = (pt_t *)((((frame->frame_no)+FRAME0)*NBPG)); //address of the page table created
    
    for( i = 0; i < 1024; i++){    /* there are 1024 entries inside each frame */ 
        pt[i].pt_pres  = 0;        /* page is present?             */ 
        pt[i].pt_write = 0;        /* page is writable?            */
        pt[i].pt_user  = 0;        /* is user level protection?    */
        pt[i].pt_pwt   = 0;        /* write through for this page? */
        pt[i].pt_pcd   = 0;        /* cache disable for this page? */
        pt[i].pt_acc   = 0;        /* page was accessed?           */
        pt[i].pt_dirty = 0;        /* page was written?            */
        pt[i].pt_mbz   = 0;        /* must be zero                 */
        pt[i].pt_global= 0;        /* should be zero in 586        */
        pt[i].pt_avail = 0;        /* for programmer's use         */
        pt[i].pt_base  = 0; /* location of page? */ 

    }
    hook_ptable_create(((frame->frame_no)+1024));    
    return pt;

}

