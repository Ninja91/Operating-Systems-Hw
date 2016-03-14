/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

extern void app1(void); //to use app1() in main
extern void app2(void); //to use app2() in main
extern void f1(void);
extern void myvictim(int);
extern void myhacker(int);

extern int myappA(int, int);

extern long host2netlb(long);
extern long host2netlc(long);

extern void app_unlim(void);
extern void app_lim(void);

int victimglobal = 0;
int32 lab2flag = 6; // Flag to get different implementation for different parts of question.
// Set it to 4 for Part 4 and 5 for part 5. Anything else is for Part 3.
int32 lab2q5sol = 2; //Set this to 1 for solution1 to part 5 and set it to 2 for solution 2 of Quetion Part 5
static unsigned long	*esp;

void homework3()
{
    /* Test case for Prob 3. */
    /* lab2q3t1(); */
    /* Test case 1 for Prob 4. */
    /* lab2q4t1(); */
    /* Test case 2 for Prob 4. */
    /* lab2q4t2(); */
    /* Test case 3 for Prob 4. */
    /* lab2q4t3(); */
    /* Test case for Prob 5. */
    /* lab2q5t1(); */
    lab3q4t1();
    /* lab3q4t2(); */
}

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
    // Homework 1
    {
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
    }

    // Homework 2 
    {
        /*
        uint32 a = 0xAABBCCDD;
        uint32 b = host2netla(a);
        kprintf("\n\nLil Endian to Big Endian\nBig Endian of 0x%x is 0x%x", a, b);
        
        a = 0xAABBCCDD;
        b = host2netlb(a);
        kprintf("\n\nLil Endian to Big Endian\nBig Endian of 0x%x is 0x%x", a, host2netlb(a));

        a = 0xAABBCCDD;
        b = host2netlc(a);
        kprintf("\n\nLil Endian to Big Endian\nBig Endian of 0x%x is 0x%x", a, b);

        prntsegaddr();
       
        //kprintf("\nStack Depth:%d\n", stackdepth(currpid));
        
        resume (
           create((void *)f1, 65536, 20, "f1  process", 0,
               NULL));

        unsigned long * topsp;

        asm("movl %esp, esp");
        topsp = esp;
        kprintf("\ncurrpid : %d\n", currpid);
        kprintf("\nBefore myappA is created\n");
        kprintf("run-time stack top : address = 0x%x, content = 0x%x\n", topsp, (unsigned long *) *topsp);

        pid32 myappA_pid = create( (void *) myappA, 65536, 20, "myappA process", 2, 5, currpid);
        asm("movl %esp, esp");
        topsp = esp;
        kprintf("\nAfter myappA is created but before resuming it\n");
        kprintf("run-time stack top : address = 0x%x, content = 0x%x\n", topsp, (unsigned long *) *topsp);

        resume(myappA_pid);

        sleepms(500);

        pid32 victim_pid;

        resume (
           create((void *)myvictim, 2048, 10, "myvictim process", 1,
               5));
        resume (victim_pid = 
           create((void *)myvictim, 2048, 10, "myvictim process", 1,
               5));
        resume (
           create((void *)myhacker, 2048, 10, "myhacker process", 1,
               victim_pid));
                return OK;
                */
    }

    // Homework 3
    homework3();
    return OK;
}
