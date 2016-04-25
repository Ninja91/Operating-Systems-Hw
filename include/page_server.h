#ifndef MAX_BS_ENTRIES
        #define MAX_BS_ENTRIES MAX_ID - MIN_ID + 1
#endif

#ifndef RD_PAGES_PER_BS
        #define RD_PAGES_PER_BS 205
#endif

#ifndef MAX_PAGES_PER_BS
        #define MAX_PAGES_PER_BS 200
#endif

//#include <paging.h>

#define BS_FREE 0
#define BS_USED 1

typedef struct bsMap{
     bsd_t bs_id;
     pid32 pid;
     int vpno; /* the virtual page number from where it starts */
     int npages; 
     struct bsMap *next;  

}bs_map;

typedef struct bs_entry{
    bsd_t   bs_id;
    byte    isopen;
	byte	isallocated;
	int32	usecount;
    unsigned int npages;
    
    frame_t *frames; /*frames that are mapped to the back store */
    bs_map *maps;   /* back store id where it is mapped to */
    int status;     //to know the status
    int isvheap;    //to know if it using the vheap     
             
}bs_entry;

#define PAGE_SERVER_ACTIVE      1
#define PAGE_SERVER_INACTIVE    2

extern bs_entry bstab[MAX_BS_ENTRIES];
extern sid32  bs_sem;
extern bool8  PAGE_SERVER_STATUS;
extern sid32  bs_init_sem;
