#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    int pid;
    printf("Before fork()\n");
    pid = fork();
    if(pid == 0)
    {
        printf("Child has started:%d\n", getpid());
        printf("Parent of this child:%d\n",getppid());
        printf("child prints 1 item:\n");
        sleep(10);
        printf("child prints 2 item:\n");
    }
    else
    {
        printf("Parent has started:%d\n", getpid());
        printf("Parent of the parent proc:%d\n", getppid());
    }
    return 0;
}
