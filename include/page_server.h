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

typedef struct bs_Mapping{
     bsd_t bs_id;
     pid32 pid;
     int npages; 
     struct bs_Mapping *next;  
     int vpno; 

}bs_map;

#define PAGE_SERVER_ACTIVE      1
#define PAGE_SERVER_INACTIVE    2

extern sid32  bs_sem;
extern bool8  PAGE_SERVER_STATUS;
extern sid32  bs_init_sem;

typedef struct bs_entry{
    bsd_t   bs_id;
    byte    isopen;
	byte	isallocated;
	int32	usecount;
    unsigned int npages;
    
    int status;  
    int isvheap; 
    frame_t *frames; 
    bs_map *maps;  
             
}bs_entry;

extern bs_entry bstab[MAX_BS_ENTRIES];
