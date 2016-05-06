/* Frame Managment*/
int init_frame_table();
frame_t  *create_frame();
int free_frame(frame_t * frame);
frame_t * find_frame_bs(int bs_id, int bsindex);
int dec_frame_refcount(frame_t * frame);
frame_t * remove_frame();
frame_t * fifo_dequeue_bs_frame();
int rm_all_free_frame();
int remove_frame_frm_bs(void *);
frame_t * lookup_frame_mappedto_bspage(int,int); 
