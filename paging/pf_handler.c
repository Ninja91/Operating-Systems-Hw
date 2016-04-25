#include <xinu.h>

int pf_handler()
{
    //kprintf("Page Fault has occured\n");
    intmask mask; 

    int pd_offset;
    int pt_offset;
    int pg_offset;
    int bsoff;   
    frame_t * frame, *ptframe;

    mask = disable();

    unsigned long cr2;
    virt_address *vaddress;
    cr2 = read_cr2();
    vaddress = (virt_address *)(&cr2);
    
    pd_offset = vaddress->pd_offset;
    pt_offset = vaddress->pt_offset;
    pg_offset = vaddress->pg_offset;


    kprintf("The Page fault has occured.\n");
    get_faults();
    hook_pfault((char *)(cr2));

    pd_t *pd;
    pt_t *pt;
    pd = proctab[currpid].pd;

    bs_map * bsm;
    bsm = find_mapping(currpid, ((unsigned int)(cr2)/NBPG));
    if (bsm== NULL) {
        kill(currpid);
        restore(mask);
        return SYSERR;
    }


    bsoff = ((unsigned int)(cr2)/NBPG) - bsm->vpno;

    if (pd[pd_offset].pd_pres != 1) {
        //page table does not exist. 1st page fault has occured

        pt = create_pt();
        if (pt == NULL) {
            kill(currpid);
            restore(mask);
            return SYSERR;
        }
        //initialize the entries
        pd[pd_offset].pd_pres  = 1;   
        pd[pd_offset].pd_write = 1;   
        pd[pd_offset].pd_user  = 0;   
        pd[pd_offset].pd_pwt   = 0;   
        pd[pd_offset].pd_pcd   = 0;   
        pd[pd_offset].pd_acc   = 0;   
        pd[pd_offset].pd_mbz   = 0;   
        pd[pd_offset].pd_fmb   = 0;   
        pd[pd_offset].pd_global= 0;  
        pd[pd_offset].pd_avail = 0;   
        pd[pd_offset].pd_base  = ((unsigned int)pt/NBPG);  

    }

    frame = frame_find_bspage(bstab[bsm->bs_id].bs_id, bsoff);
    if (frame != NULL) 
    {
        frame->reference_count++;
    }
    else 
    {
        frame = create_frame();
        if (frame == NULL) {
            kprintf("Error\n");
            kill(currpid);
            restore(mask);

            return SYSERR;
        }
        frame->bs_pg = bsoff;
        frame->type   = FRAME_BS;
        frame->bs_id   = bstab[bsm->bs_id].bs_id;
        frame->reference_count = 1;

        frame->bs_frames_q = bstab[bsm->bs_id].frames;
        bstab[bsm->bs_id].frames = frame;

        read_bs((void *)((FRAME0+(frame->frame_no))*NBPG), bsm->bs_id, bsoff);
    }


    pt[pt_offset].pt_pres  = 1;
    pt[pt_offset].pt_write = 1;
    pt[pt_offset].pt_base  = FRAME0+(frame->frame_no);


    ptframe = &frame_table[(((unsigned int)(pt)/NBPG)-FRAME0)];
    ptframe->reference_count++;

    set_PDBR(((unsigned int)(pd)/NBPG));

    restore(mask);
    return OK;

}

