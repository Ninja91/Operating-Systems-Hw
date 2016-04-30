/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

extern int app();
void func1()
{
    /* kprintf("\nIn func1 process"); */
    struct memblk * ch = vgetmem(40*4095);    
    kprintf("\nch = %d", ch);
    int i;    
    char * ptr;
    ptr = (char *)ch; 
    for(i=0;i<40*4096;i++)
    {
        *ptr ='a';    
        ptr++;
        /* kprintf("\Looping in First for loop\n"); */
        /* if (i %4096 == 0) */
            /* kprintf("\nTouching the %d frame\n", i); */

    }
    ptr = (char *)ch;
    for(i=0;i<40*4096;i++)
    {
        *ptr ='a';
        ptr++;
        /* if (i %4096 == 0) */
            /* kprintf("\nTouching the %d frame\n", i); */

    }

    kprintf("Process Id %d\n",currpid);
    vfreemem(ch,40*4096);
}

process	main(void)
{

    /* Start the network */
    /* DO NOT REMOVE OR COMMENT THIS CALL */
    netstart();

    /* Initialize the page server */
    /* DO NOT REMOVE OR COMMENT THIS CALL */
    psinit();

    kprintf("\n...creating a shell\n");
    recvclr();
    /* resume(create(shell, 8192, 50, "shell", 1, CONSOLE)); */

    srpolicy(3);
    resume(vcreate(func1, 1024, 150, 150, "p1", 0, NULL));
    resume(vcreate(func1, 1024, 200, 125, "p1", 0));
    /* resume (vcreate (app, 1024, 10, 150, "app process", 0, NULL)); */
    /* resume (vcreate (app, 1024, 10, 150, "app process", 0, NULL)); */
    /* Wait for shell to exit and recreate it */

    /* while (TRUE) { */
    /*     receive(); */
    /*     sleepms(200); */
    /*     kprintf("\n\nMain process recreating shell\n\n"); */
    /*     resume(create(shell, 4096, 20, "shell", 1, CONSOLE)); */
    /* } */
    return OK;
}
