#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
    int pid;
    int i = 1;
    
    for(;;)
    {
        pid = fork();
        if(pid < 0)
        {
            printf("Maximum number of processes : %d\n", i);
            exit(0);
        }
        else if(pid == 0)
        {
            i++;
        }
        else
        {
            wait(0);
            exit(0);
        }
    }
    return 0;
}
