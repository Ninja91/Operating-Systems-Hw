#include <xinu.h>

int proc_clean_bs(int pid) {
    bs_map * prev_node;
    bs_map * cur_node;
    int i;

    kprintf("\n Entering proc_clean_bs %d", pid);
    for (i=0; i < MAX_BS_ENTRIES; i++) {
        if (bstab[i].status != BS_FREE) {           

            for (prev_node = NULL, cur_node = bstab[i].maps; cur_node!=NULL;) {
                kprintf("\n Cur_node_pid =  %d", cur_node->pid);
                if (cur_node->pid == pid) {
                    clean_frame_bs(cur_node);

                    if (prev_node == NULL) {
                        bstab[i].maps = cur_node->next;
                        freemem((char *)cur_node, sizeof(bs_map));
                        cur_node = bstab[i].maps;
                    } 
                    else {
                        prev_node->next = cur_node->next;
                        freemem((char *)cur_node, sizeof(bs_map));
                        cur_node = prev_node->next;
                    }

                } 
                else {
                    prev_node = cur_node;
                    cur_node = cur_node->next;

                }
            }
            
            if (bstab[i].maps == NULL)
                deallocate_bs(i);
        }
    }
    return OK;
}
