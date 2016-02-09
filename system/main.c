/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

extern void app1(void); //to use app1() in main
extern void app2(void); //to use app2() in main
extern void f1(void);
extern void myvictim(int);
extern void myhacker(int);

extern long host2netlb(long);
extern long host2netlc(long);

int victim_global = 0;

process	main(void)
{
	kprintf("\nHello World!\n");
	kprintf("\nI'm the first XINU app and running function main() in system/main.c.\n");
	kprintf("\nI was created by nulluser() in system/initialize.c using create().\n");
	kprintf("\nMy creator will turn itself into the do-nothing null process.\n");
	kprintf("\nI will create a second XINU app that runs shell() in shell/shell.c as an example.\n");
	kprintf("\nYou can do something else, or do nothing; it's completely up to you.\n");
	kprintf("\n...creating a shell\n");
	recvclr();
	//resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

    /*
     * Createschild process calling app1()
	resume (
	   create((void *)app1, 65536, 20, "app1 process", 0,
           NULL));
    
     * Creates child process calling app2()
	resume (
	   create((void *)app2, 65536, 20, "app2 process", 0,
           NULL));*/

	/* Wait for shell to exit and recreate it */
    /*
	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
	    resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}*/

    uint32 a = 0xAABBCCDD;
    uint32 b = host2netla(a);
    kprintf("\nLil Endian to Big \n\nBig Ending of %x is %x", a, b);
    
    a = 0xAABBCCDD;
    b = host2netlb(a);
    kprintf("\nLil Endian to Big \n\nBig Ending of %x is %x", a, b);

    a = 0xAABBCCDD;
    b = host2netlc(a);
    kprintf("\nLil Endian to Big \n\nBig Ending of %x is %x", a, b);

    prntsegaddr();
   
    //kprintf("\nStack Depth:%d\n", stackdepth(currpid));
	
    resume (
	   create((void *)f1, 65536, 20, "f1  process", 0,
           NULL));
	resume (
	   create((void *)myvictim, 65536, 30, "myvictim  process", 1,
           5));
	resume (
	   create((void *)myhacker, 65536, 30, "myhacker  process", 1,
           4));
	        return OK;
}
