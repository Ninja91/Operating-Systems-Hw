/* This file has functions for frame creation and management */

#include <xinu.h>


frame_t frame_table[NFRAMES];
frame_t * frame_fifo_start;

int init_frame_table()
{
  int i = 0;
 frame_fifo_start = NULL; 
  
   while(i < NFRAMES)
  {
   frame_table[i].frame_no = i;
   frame_table[i].reference_count = 0;
   frame_table[i].fifo_queue = NULL;
   frame_table[i].accessed = 0;
   frame_table[i].type = FRAME_FREE;
   frame_table[i].status = FRAME_FREE;
   frame_table[i].bs_id = -1;
   frame_table[i].bs_pg = 0;
   frame_table[i].bs_frames_q = NULL;
   i++;
   }


return OK;
}

int frame_refcount_dec(frame_t * frame)
{
 (frame->reference_count)--;
  
 //free the frame if the reference count becomes 0
 if(frame->reference_count == 0)
 {
    free_frame(frame);
 } 

 return OK;
 }

frame_t  *create_frame()
{
  
    frame_t * frame;
    frame_t * cur;


    frame = remove_frame();
    if (frame == NULL) {
        kprintf("Check if this is the problem\n");       
        return NULL;
    }
   frame->status    = FRAME_USED;
    frame->reference_count = 0;
    frame->accessed  = 0;
    frame->bs_id = -1;
    frame->bs_pg  = 0;
    frame->fifo_queue = NULL;
    frame->bs_frames_q=NULL;

    
    if (frame_fifo_start != NULL) {
cur = frame_fifo_start;
        while (cur->fifo_queue != NULL)
            cur = cur->fifo_queue;
        cur->fifo_queue = frame;        

    }
   else{
        frame_fifo_start = frame;
    }

    return frame;
}


frame_t * remove_frame()
{
 frame_t * frame;
  int i = 0;
  while(i < NFRAMES) {
     frame = &frame_table[i];
     if (frame->status == FRAME_FREE)
       return frame;
     i++;
    }

 //if none of the frames are free we have to evict them. Using the FIFO principle tp evict the frames
    
    frame = frame_get_fifo();
    hook_pswap_out(((frame->frame_no)+1024),frame->frame_no);       
  //remove any links the frame might be having before returning that frame
    free_frame(frame);

    return frame;
}

frame_t * frame_get_fifo()
{
 frame_t * prev = NULL;
  frame_t * cur = frame_fifo_start;;
  

  while (cur!= NULL) {
        if (cur->type == FRAME_BS) {
            return cur;
        }
        prev = cur;
        cur = cur->fifo_queue;
    }

    
   return NULL;
}  


int free_frame(frame_t * frame)
{
    
    int dirty;

   //check if the page was dirtied and also remove all the links    
    dirty = remove_pg_link(((1024+(frame->frame_no))*NBPG));

    //if it was drtied we must write back to the back store
    if (frame->type == FRAME_BS && dirty) {

      write_bs((char *)((1024+(frame->frame_no))*NBPG), frame->bs_id, frame->bs_pg);
     }

    //make the status free
    frame->status = FRAME_FREE;

    
    if (frame->type != FRAME_BS)
        remove_frame_list();
    else
       remove_frame_frm_bs(&bstab[frame->bs_id]);
        

    //after cleaning from the queue making it FREE
    frame->type   = FRAME_FREE;
    frame->reference_count = 0;
    
    frame->bs_id   = -1;
    frame->bs_pg = 0;
    frame->accessed = 0;


    return OK;
}

//removes the frame which is free from the frame queue
int remove_frame_list()
{
  
    frame_t * prev = NULL;
    frame_t * cur  = frame_fifo_start; 

    while (cur!=NULL) {
        if (cur->status == FRAME_FREE) {
             if (prev != NULL) {
                prev->fifo_queue = cur->fifo_queue;
                cur = prev->fifo_queue;
            } 
           else {
              frame_fifo_start = cur->fifo_queue;
                cur = frame_fifo_start;
                
            }

            continue;   //need to remove all the free frames, that is why continuing
        } 
        prev = cur;
        cur = cur->fifo_queue;
    }


   return OK;
}
   
//remove all the free frames in the backing store
int remove_frame_frm_bs(void * bs)
{
  bs_entry * bsptr;
    
    

    bsptr = (bs_entry *) bs;

  frame_t * prev = NULL;
    frame_t * cur  = bsptr->frames;
    while(cur!=NULL)
    {
    
        if (cur->status == FRAME_FREE) {


            if (prev != NULL) {
                 prev->bs_frames_q = cur->bs_frames_q;
                cur = prev->bs_frames_q;
   
                
            } else {
               bsptr->frames = cur->bs_frames_q;
                cur = bsptr->frames;
            }

            continue;
        } 

        
        prev = cur;
        cur = cur->bs_frames_q;
        
    }


    return OK;
}

//find the frame which maps to the backstore with back store id and the page in the offset
frame_t * frame_find_bspage(int bs_id, int bsoffset) 
{
    int i = 0;
    frame_t * frame;

    
    while(i < NFRAMES) 
     {
        frame = &frame_table[i];

         if (frame->status!=FRAME_FREE)
        { 
          if (frame->type == FRAME_BS)
          {  
            if (frame->bs_id == bs_id && frame->bs_pg == bsoffset) 
            {
                 return frame;

            } 

          }
         }
       i++;
      }
    return NULL;

}
 
 
