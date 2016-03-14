extern struct qentry receiverq[NPROC][NPROC + 2];
void init_recieverq();
void receiverq_enqueue(pid32 receiver_pid);
pid32 receiverq_dequeue(pid32 receiver_pid);
