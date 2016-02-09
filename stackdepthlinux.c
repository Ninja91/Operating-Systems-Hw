#include<stdio.h>

static unsigned long *esp,*ebp;

int stackdepthlinux()
{

        unsigned long *topsp,*topbp;
        asm("movl %esp,esp");
        asm("movl %ebp,ebp");
        topsp=esp;
        topbp=ebp;
        int count=0;

        while(topbp!=NULL)
        {

                topsp=topbp+2;
                topbp=(unsigned long *) *topbp;
                count++;
        }

        return count-1;
}


void myfunction2()
{

        printf("Stack depth %d\n",stackdepthlinux());
}

void myfunction()
{
        myfunction2();
        printf("Stack depth %d\n",stackdepthlinux());
}
int main()
{
   int child_pid;
   int status;
   int local = 0;
   child_pid = fork();
   if (child_pid >= 0)
   {
        if(child_pid==0)
        {

                myfunction();
                int depth=stackdepthlinux();
                printf("Stack depth %d\n",depth);
        }
        else
        {
            printf("Stack depth %d\n",stackdepthlinux());
        }
        }
}
