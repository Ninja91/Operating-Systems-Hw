#include <xinu.h>
extern syscall	sendbt(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32	msg,    	/* Contents of message		*/
      int32     wait
	);

void sendex(pid32 receiver_pid, umsg32 msg, int32 wait){
    kprintf("\nSending : %d", msg);
    if (SYSERR == sendbt(receiver_pid, msg, wait))
        kprintf("\nSending not done");
}
void sendex1(pid32 receiver_pid, umsg32 msg, int32 wait){
    kprintf("\nSending : %d", msg);
    while(1)
    if (SYSERR == sendbt(receiver_pid, msg, wait)) 
        kprintf("\nSending not done");
}
