#include <xinu.h>

/*
 * This function creates a page table
 * */

pt_t * create_pt() 
{ 
    frame_t * frame = create_frame();
    int i;
    
    frame->type = FRAME_PT;     //indicate that the frame is used for a page table
    pt_t * pt = (pt_t *)((((frame->frame_no)+FRAME0)*NBPG)); //address of the page table created
    
    for( i = 0; i < 1024; i++){   
        pt[i].pt_pcd   = 0;    
        pt[i].pt_acc   = 0;   
        pt[i].pt_dirty = 0;       
        pt[i].pt_mbz   = 0;       
        pt[i].pt_global= 0;       
        pt[i].pt_avail = 0;      
        pt[i].pt_base  = 0; 
        
        
        pt[i].pt_pres  = 0;      
        pt[i].pt_write = 0;      
        pt[i].pt_user  = 0;   
        pt[i].pt_pwt   = 0;   

    }

    hook_ptable_create(((frame->frame_no)+FRAME0));    
    return pt;
}

