#include <xinu.h>
int free_page(pt_t *pt)
{
       pt->pt_pcd   = 0;       
       pt->pt_acc   = 0;       
       pt->pt_dirty = 0;       
       pt->pt_mbz   = 0;      
       pt->pt_global= 0;        
       pt->pt_avail = 0;       
       pt->pt_base  = 0;   
       pt->pt_pres  = 0;       
       pt->pt_write = 0;       
       pt->pt_user  = 0;      
       pt->pt_pwt   = 0;      

       return OK; 
}
