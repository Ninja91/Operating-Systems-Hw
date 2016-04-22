#include <xinu.h>

int recvhandler(void * ptr) {
  umsg32 msg;

  msg = receive();
  /* Setting the received messafe to the void ptr */
  /* *ptr = msg; */
  kprintf("\nRecieving in Process : %d\nAt timestamp: %d\nMsg received : %d\n", 
          currpid,
          clktimemsec,
          msg);

  return OK;
}
