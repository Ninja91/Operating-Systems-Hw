/* paging.h */

//typedef unsigned int	 bsd_t;

//data structures to maintain frames
typedef struct frameEnt{
        int frame_no;  /*unique number associated with each frame */
        int reference_count; /*references for a frame */
        struct frameEnt * fifo_node; /*used for fifo replacement */
        int accessed; /*if frame is accessed  */
        int type; /*type of the frame i.e the page is used for page_table, page directory or it is mapped in the bs_store */
        int status; /*status : FREE or USED */
        int bs_id; /*back store is mapped to frame */
        int bs_pg; /*the page in the back store */
        struct frameEnt * bs_frames_q; /* the list of frame associated with the particular back store */
}frame_ent;

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

/* Prototypes for required API calls */
//SYSCALL xmmap(int, bsd_t, int);
//SYSCALL xmunmap(int);

#define NBPG		4096	/* number of bytes per page	*/
#define FRAME0		1024	/* zero-th frame		*/
#define NFRAMES		3072	/* number of frames		*/

#define MAP_SHARED 1
#define MAP_PRIVATE 2

#define FIFO 3
#define MYPOLICY 4

#define MAX_ID		7		/* You get 8 mappings, 0 - 7 */
#define MIN_ID          0
