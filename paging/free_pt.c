#include <xinu.h>
/*
 * This function frees page table */
int free_pt(pt_t *pt)
{
    free_frame(&frame_table[(((unsigned int)(pt)/NBPG)-FRAME0)]);

    hook_ptable_delete(((unsigned int)(pt)/NBPG));
    return OK; 
}



