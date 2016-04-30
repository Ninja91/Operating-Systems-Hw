/* This file has functions for frame creation and management */
#include <xinu.h>

frame_t frame_table[NFRAMES];
frame_t * frame_fifo_head;

int init_frame_table() {
    int i;
    frame_fifo_head = NULL; 

    for(i = 0; i < NFRAMES; i++) {
        frame_table[i].frame_no = i;
        frame_table[i].reference_count = 0;
        frame_table[i].accessed = 0;
        frame_table[i].type = FRAME_FREE;
        frame_table[i].status = FRAME_FREE;

        frame_table[i].bs_id = -1;
        frame_table[i].bs_pg = 0;
        frame_table[i].bs_frames_q = NULL;

        frame_table[i].fifo_queue = NULL;
        frame_table[i].pid = -1;
        frame_table[i].virtual_page_no=0;
    }

    return OK;
}

int dec_frame_refcount(frame_t * frame) {
    --(frame->reference_count);

    //freeing the frame once refcount becomes 0
    if(frame->reference_count == 0)
    {
        free_frame(frame);
    } 

    return OK;
}

frame_t * fifo_enqueue (frame_t * fifo_head, frame_t * fifo_node) {
    if (fifo_head == NULL)
        return fifo_node;

    frame_t * cur = fifo_head;
    while(cur->fifo_queue != NULL) {
        cur = cur->fifo_queue;
    }
    cur->fifo_queue = fifo_node;
    return fifo_head;
}

frame_t  *create_frame() {
    frame_t * frame;
    frame_t * cur;

    frame = remove_frame();
    if (frame == NULL) {
        kprintf("This is a problem\n");       
        return NULL;
    }

    frame->reference_count = 0;
    frame->status = FRAME_USED;
    frame->accessed  = 0;

    frame->bs_id = -1;
    frame->bs_pg  = 0;
    frame->bs_frames_q=NULL;

    frame->fifo_queue = NULL;

    frame_fifo_head = fifo_enqueue(frame_fifo_head, frame);
    return frame;
}


frame_t * remove_frame() 
{
    int i;
    frame_t * frame;

    for(i = 0; i < NFRAMES; i++) {
        frame = &frame_table[i];
        if (frame->status == FRAME_FREE)
            return frame;
    }

    frame = fifo_dequeue_bs_frame();
    if (frame == NULL) {
        kprintf("This is a problem\n");       
        return NULL;
    }

    hook_pswap_out(((frame->frame_no)+FRAME0),frame->frame_no);       
    free_frame(frame);

    return frame;
}

frame_t * fifo_dequeue_bs_frame()
{
    frame_t * fifo_node = frame_fifo_head;

    while (fifo_node != NULL) {
        if (fifo_node->type == FRAME_BS) {
            return fifo_node;
        }

        fifo_node = fifo_node->fifo_queue;
    }

    return NULL;
}  


//remove all the free frames in the backing store
int remove_frame_from_backing_store(void * bs)
{
    bs_entry * bsptr = (bs_entry *) bs;
    frame_t * prev_node = NULL;
    frame_t * cur_node  = bsptr->frames;

    for ( ;cur_node!=NULL; cur_node = cur_node->bs_frames_q)
    {
        if (cur_node->status == FRAME_FREE) {
            if (prev_node == NULL) {
                bsptr->frames = cur_node->bs_frames_q;
            }
            else {
                prev_node->bs_frames_q = cur_node->bs_frames_q;
            }
            continue;
        } 
        prev_node = cur_node;

    }

    return OK;
}

int rm_page_links(int address)
{
    struct procent *pptr;
    int page_no =((unsigned int) (address)/NBPG);
    int i,j,k;
    pd_t * pd;
    pt_t * pt;
    frame_t * frame;
    int dirty = 0;
    for(i=0;i<NPROC;i++)
    {
        pptr = &proctab[i];
        if( pptr->prstate != PR_FREE)
        {
            pd = pptr->pd;
            for(j=4;j<1024;j++)
            {
                if(pd[j].pd_pres == 1)
                {
                    pt =((unsigned int)((pd[j].pd_base)*NBPG));
                    for(k=0;k<1024;k++)
                    {
                        if(pt[k].pt_pres==1 && pt[k].pt_base == page_no)
                        {
                            if(pt[k].pt_dirty ==1)
                                dirty =1;

                            free_page(&pt[k]);

                            frame = &frame_table[(((unsigned int)(pt)/NBPG) - FRAME0)];

                            dec_frame_refcount(frame);

                            if(frame->status == FRAME_FREE)
                                pd[j].pd_pres = 0;
                        }  
                    }
                }
            }
        }
    }
    return dirty;
}

int free_frame(frame_t * frame)
{

    int dirty = rm_page_links(( FRAME0 + frame->frame_no ) * NBPG);

    if (frame->type == FRAME_BS && dirty) {
        write_bs((char *)(( FRAME0 + frame->frame_no )*NBPG), frame->bs_id, frame->bs_pg);
    }

    frame->status = FRAME_FREE;

    if (frame->type != FRAME_BS) {
        rm_all_free_frame();
    }
    else {
        rm_all_free_frame();
        remove_frame_from_backing_store(&bstab[frame->bs_id]);
    }

    frame->accessed = 0;
    frame->type   = FRAME_FREE;
    frame->reference_count = 0;

    frame->bs_id   = -1;
    frame->bs_pg = 0;

    return OK;
}

//removes the frame which is free from the frame queue
int rm_all_free_frame()
{

    frame_t * prev_node;
    frame_t * cur_node; 

    for (prev_node = NULL, cur_node = frame_fifo_head; cur_node!=NULL; cur_node = cur_node->fifo_queue) {
        if (cur_node->status == FRAME_FREE) {
            if (prev_node == NULL) {
                frame_fifo_head = cur_node->fifo_queue;
            } 
            else {
                prev_node->fifo_queue = cur_node->fifo_queue;
            }
            continue;
        }
        prev_node = cur_node;
    }

    return OK;
}


//find the frame which maps to the backstore with back store id and the page in the offset
frame_t * lookup_frame_mappedto_bspage(int bs_id, int bsoffset) 
{
    int i;
    frame_t * frame;

    for(i = 0; i < NFRAMES; i++) 
    {
        frame = &frame_table[i];
        if (frame->status!=FRAME_FREE && frame->type == FRAME_BS && frame->bs_id == bs_id && frame->bs_pg == bsoffset)
        { 
            return frame;
        }
    }
    return NULL;
}




