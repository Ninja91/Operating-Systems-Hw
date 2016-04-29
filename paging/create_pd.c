#include <xinu.h>
/*
 * This function creates page directory */
pd_t * create_pd()
{
    pd_t  *pd;
    frame_t * frame = create_frame();   
    frame->type = FRAME_PD; 
    pd = (pd_t *)((((frame->frame_no)+FRAME0)*NBPG)); 

    int i;
    for(i=0;i<1024;i++)
    {
        if(i == 576) {
            pd[i].pd_base  = ((unsigned int)(global_pg_tab[4])/NBPG); 

            pd[i].pd_pres  = 1;
            pd[i].pd_write = 1;
            pd[i].pd_avail = 1; 
        }
        else if(i < 4) {
            pd[i].pd_base  = ((unsigned int)(global_pg_tab[i])/NBPG); 

            pd[i].pd_pres  = 1;
            pd[i].pd_write = 1;
            pd[i].pd_avail = 1; 
        }
        else {
            pd[i].pd_base  = 0;      
            
            pd[i].pd_pres  = 0;     
            pd[i].pd_write = 0;       
            pd[i].pd_avail = 0;      
        }
        pd[i].pd_global= 0;  
        
        pd[i].pd_user  = 0;      
        pd[i].pd_acc   = 0;    
        pd[i].pd_mbz   = 0;      
        
        pd[i].pd_fmb   = 0;      
        pd[i].pd_pwt   = 0;     
        pd[i].pd_pcd   = 0;    

    }
    return pd;
}


