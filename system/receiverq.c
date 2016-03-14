#include <xinu.h>
#include <receiverq.h>

struct qentry receiverq[NPROC][NPROC + 2];

void init_recieverq(){
    int i, j;
    int head = NPROC;
    int tail = head + 1;

    for(i = 0; i< NPROC; i++){
        receiverq[i][head].qnext = head + 1;
        receiverq[i][head].qprev = EMPTY;
        receiverq[i][head + 1].qprev = head;
        receiverq[i][head + 1].qnext = EMPTY;
    }
}

pid32 receiverq_dequeue(pid32 receiver_pid) {
    int head = NPROC;
    int tail = head + 1;
    
    int first = receiverq[receiver_pid][head].qnext;
    int next;

    if (first == tail) 
        return EMPTY;

    receiverq[receiver_pid][head].qnext = receiverq[receiver_pid][first].qnext;
    next = receiverq[receiver_pid][first].qnext;
    receiverq[receiver_pid][next].qprev = head;

    receiverq[receiver_pid][first].qnext = EMPTY;
    receiverq[receiver_pid][first].qprev = EMPTY;

    return first;
}

void receiverq_enqueue(pid32 receiver_pid) {
    int head = NPROC;
    int tail = head + 1;
    
    int prev;
    prev = receiverq[receiver_pid][tail].qprev;

    receiverq[receiver_pid][currpid].qnext = tail;
    receiverq[receiver_pid][currpid].qprev = prev;

    receiverq[receiver_pid][tail].qprev = currpid;
    receiverq[receiver_pid][prev].qnext = currpid;

}
