#include <xinu.h>
/*
 * This function frees the page directory
 * */
int free_pd(pd_t * pd)
{
    int i;
    for( i = 0; i < 1024; i++){
        free_pt((pt_t *)&pd[i]);
    }

    free_frame(&frame_table[(((unsigned int)(pd)/NBPG)-FRAME0)]);
    return OK;
}

