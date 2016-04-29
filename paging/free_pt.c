#include <xinu.h>
/*
 * This function frees page table */
int free_pt(pt_t *pt)
{
    hook_ptable_delete(((unsigned int)(pt)/NBPG));
    free_frame(&frame_table[(((unsigned int)(pt)/NBPG)-FRAME0)]);
    return OK; 
}



