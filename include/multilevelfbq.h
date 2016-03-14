struct mltfb_qentry {
    pid32 head;
    pid32 tail;
};

void initialize_mltfbq();
extern struct mltfb_qentry multilevelfbqueue[];

#define is_mltfbq_empty(qid) (multilevelfbqueue[qid].head == EMPTY && multilevelfbqueue[qid].tail == EMPTY) 


pid32	mltfbq_dequeue(qid16);
status	mltfbq_insert(
	  pid32		pid,		/* ID of process to insert	*/
	  qid16		q,		/* ID of queue to use		*/
	  int32		key		/* Key for the inserted process	*/
	);
