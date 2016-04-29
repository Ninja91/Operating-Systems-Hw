#include <xinu.h>

pt_t * global_pg_tab[5] = { 0, 0, 0, 0, 0 };
int init_pg_tab()
{
    int i,j;
    pt_t * pt;
    unsigned int device_mem = 589824;
    for(i=0;i<4;i++)
    {
        pt = create_pt();  
        global_pg_tab[i] = pt ; 
        kprintf("Address of Global page table %d is %d\n", (i+1), (int)pt);
        for( j = 0; j < 1024; j++) {   /* there are 1024 entries inside each frame */ 
            pt[j].pt_pcd   = 0;        /* cache disable for this page? */
            pt[j].pt_acc   = 0;        /* page was accessed?           */
            pt[j].pt_dirty = 0;        /* page was written?            */

            pt[j].pt_mbz   = 0;        /* must be zero                 */
            pt[j].pt_global= 0;        /* should be zero in 586        */
            pt[j].pt_avail = 0;        /* for programmer's use         */
            pt[j].pt_base  = i*1024 + j; /* The first four global page tables should map to the first 4096 pages. This is taken care of in this initialization */

            pt[j].pt_pres  = 1;        /* page is present?             */ 
            pt[j].pt_write = 1;        /* page is writable?            */
            pt[j].pt_user  = 0;        /* is user level protection?    */
            pt[j].pt_pwt   = 0;        /* write through for this page? */
        }
    }

    //create the 5th page table
    pt = create_pt();
    global_pg_tab[4] = pt;
    kprintf("the address of the device memory page table %d is %d\n",4, (int)pt);
    for( j = 0; j < 1024; j++) {
        pt[j].pt_pcd   = 0;        /* cache disable for this page? */
        pt[j].pt_acc   = 0;        /* page was accessed?           */
        pt[j].pt_dirty = 0;        /* page was written?            */
        
        pt[j].pt_mbz   = 0;        /* must be zero                 */
        pt[j].pt_global= 0;        /* should be zero in 586        */
        pt[j].pt_avail = 0;        /* for programmer's use         */
        pt[j].pt_base  = device_mem; /* location of page? . Here the first four global page tables should map to the first 4096 pages. */
        
        pt[j].pt_pres  = 1;        /* page is present?             */ 
        pt[j].pt_write = 1;        /* page is writable?            */
        pt[j].pt_user  = 0;        /* is user level protection?    */
        pt[j].pt_pwt   = 0;        /* write through for this page? */
       
        device_mem = device_mem + 1;
    }  

    return OK;
}

