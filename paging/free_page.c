#include <xinu.h>
int free_page(pt_t *pt)
{
       pt->pt_pcd   = 0;        /* cache disable for this page? */
       pt->pt_acc   = 0;        /* page was accessed?           */
       pt->pt_dirty = 0;        /* page was written?            */
       pt->pt_mbz   = 0;        /* must be zero                 */
       pt->pt_global= 0;        /* should be zero in 586        */
       pt->pt_avail = 0;        /* for programmer's use         */
       pt->pt_base  = 0;        /* location of page? */  
       pt->pt_pres  = 0;        /* page is present?             */ 
       pt->pt_write = 0;        /* page is writable?            */
       pt->pt_user  = 0;        /* is user level protection?    */
       pt->pt_pwt   = 0;        /* write through for this page? */

       return OK; 
}
