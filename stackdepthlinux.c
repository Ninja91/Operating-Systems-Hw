#include<stdio.h>

static unsigned long *esp,*ebp;

int stackdepthlinux()
{
    unsigned long *topsp,*topbp;
    int cnt = 0;
 
    asm("movl %esp,esp");
    asm("movl %ebp,ebp");
    topsp = esp;
    topbp = ebp;
    
    while(topbp != 0) /**In linux the base ebp of the process value is set to 0*/
    {
        topbp = (unsigned long *) *topbp;
        cnt++;
    }
    
    return cnt-1;
}


void foo2()
{
    printf("\n\nfoo2() stack depth = %d\n",stackdepthlinux());
}

void foo()
{
    foo2();
    printf("\n\nfoo() Stack depth = %d\n",stackdepthlinux());
}

int main()
{
    int fork_ret;
    int status;
    int local = 0;
    fork_ret = fork();
    if(fork_ret == 0) {
        foo();
        return 0;
    }
    else if (fork_ret > 0) {
            printf("\n\nmain() stack depth %d\n",stackdepthlinux());
            return 0;
    }
    else 
        return -1;
}
