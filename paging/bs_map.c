//functions related to bs mapping

#include <xinu.h>


int add_bs_map(bsd_t bsid, int pid, int vpno, int npages) {
    bs_map * bsmapptr;

    bsmapptr = (bs_map *) getmem(sizeof(bs_map));
    bsmapptr->bs_id   = bsid;
    bsmapptr->pid    = pid;
    bsmapptr->npages = npages;  
    bsmapptr->vpno   = vpno;
    bsmapptr->next   = bstab[bsid].maps;
    bstab[bsid].maps    = bsmapptr;
    return OK;
}

int delete_mapping_bs(int pid, int vpno) {
    int i;
    bs_map * prev_node;
    bs_map * cur_node;

    for (i = 0; i < MAX_BS_ENTRIES; i++) {
        if (bstab[i].status != BS_FREE && bstab[i].maps != NULL)
        {      
            for (prev_node = NULL, cur_node = bstab[i].maps; cur_node!=NULL; prev_node = cur_node, cur_node = cur_node->next) {
                if (cur_node->pid == pid) 
                {
                    if(prev_node != NULL)
                    {
                        prev_node->next = cur_node->next;
                        freemem((char *)cur_node, sizeof(bs_map));
                        return OK;
                    }
                    else
                    {
                        bstab[i].maps = cur_node->next;
                        freemem((char *)cur_node, sizeof(bs_map));
                        return OK;
                    }
                }
            }
        }
    }


    return SYSERR;
}


bs_map * find_mapping(int pid, int vpno) {
    int i;
    bs_map * prev_node;
    bs_map * cur_node;

    for (i=0; i < MAX_BS_ENTRIES; i++) {
        if (bstab[i].status != BS_FREE && bstab[i].maps != NULL) {      
            /* prev_node = NULL; */
            /* cur_node = bstab[i].maps; */

            for (prev_node = NULL, cur_node = bstab[i].maps; cur_node!=NULL; prev_node = cur_node, cur_node = cur_node->next) {
                if (cur_node->pid == pid) {
                    return cur_node;
                }
            }
        }
    }

    return NULL;
}

int clean_frame_bs(bs_map * bsm) {
    bsd_t bs_id;
    frame_t * prev_node;
    frame_t * cur_node;

    for (bs_id = bsm->bs_id, prev_node = NULL, cur_node = bstab[bs_id].frames; cur_node != NULL; prev_node = cur_node, cur_node = cur_node->bs_frames_q) {
      if (cur_node->bs_pg < bsm->npages)
            dec_frame_refcount(cur_node);
    } 
    return OK;
}
