/* paging.h */

//typedef unsigned int	 bsd_t;

//data structures to maintain frames
typedef struct frame_type{
    int frame_no;  
    int type; 
    int status; 
    int bs_id; 
    int bs_pg; 
    struct frame_type * fifo_queue; 
    struct frame_type * bs_frames_q; 

    int reference_count; 
    int accessed; 

    int global_clock_var;
    int pid;
    int virtual_page_no;
} frame_t;

//need to maintain a data structure for the 32 bit virtual address
typedef struct virtual_address{
    int pg_offset  : 12;
    int pt_offset  : 10;
    int pd_offset  : 10;
}virt_address;

/* Structure for a page directory entry */

typedef struct {

    unsigned int pd_pres	: 1;		/* page table present?		*/
    unsigned int pd_write : 1;		/* page is writable?		*/
    unsigned int pd_user	: 1;		/* is use level protection?	*/
    unsigned int pd_pwt	: 1;		/* write through cachine for pt?*/
    unsigned int pd_pcd	: 1;		/* cache disable for this pt?	*/
    unsigned int pd_acc	: 1;		/* page table was accessed?	*/
    unsigned int pd_mbz	: 1;		/* must be zero			*/
    unsigned int pd_fmb	: 1;		/* four MB pages?		*/
    unsigned int pd_global: 1;		/* global (ignored)		*/
    unsigned int pd_avail : 3;		/* for programmer's use		*/
    unsigned int pd_base	: 20;		/* location of page table?	*/
} pd_t;

/* Structure for a page table entry */

typedef struct {

    unsigned int pt_pres	: 1;		/* page is present?		*/
    unsigned int pt_write : 1;		/* page is writable?		*/
    unsigned int pt_user	: 1;		/* is use level protection?	*/
    unsigned int pt_pwt	: 1;		/* write through for this page? */
    unsigned int pt_pcd	: 1;		/* cache disable for this page? */
    unsigned int pt_acc	: 1;		/* page was accessed?		*/
    unsigned int pt_dirty : 1;		/* page was written?		*/
    unsigned int pt_mbz	: 1;		/* must be zero			*/
    unsigned int pt_global: 1;		/* should be zero in 586	*/
    unsigned int pt_avail : 3;		/* for programmer's use		*/
    unsigned int pt_base	: 20;		/* location of page?		*/
} pt_t;


#define FRAME_FREE  0
#define FRAME_USED  1

#define FRAME_BS    2
#define FRAME_PT    1
#define FRAME_PD    0
/* Prototypes for required API calls */
//SYSCALL xmmap(int, bsd_t, int);
//SYSCALL xmunmap(int);

#define NBPG		4096	/* number of bytes per page	*/
#define FRAME0		1024	/* zero-th frame		*/
#define NFRAMES		50//3072	/* number of frames		*/

#define MAP_SHARED 1
#define MAP_PRIVATE 2

#define FIFO 3
#define MYPOLICY 4

#define MAX_ID		7		/* You get 8 mappings, 0 - 7 */
#define MIN_ID          0
extern pt_t * global_pg_tab[];
extern frame_t frame_table[];
