#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int fibo[1000];

int fib(int n)
{
    int temp = 0;
    if(fibo[n] == -1)
    {
        if(n <= 1)
            fibo[n] = n;
        else
        {
            int pid;
            pid = vfork();
            if(pid == 0) // child will take care of fib(n-1)
            {
                temp += fib(n-1);
                exit(0);
            }
            else if(pid > 0) // parent will take care of fib(n-2)
            {
                wait(NULL);
                temp += fib(n-2);
            }
            else
            {
                printf("vfork failed!!!\n");
            }
            fibo[n] = temp;
        }
    }
    return fibo[n];
}

int main()
{
    int n, i;
    printf("Enter the number of fibonacci numbers to be generated : ");
    scanf("%d", &n);
    
    for(int i = 0; i < 1000; i++)
        fibo[i] = -1;
    
    printf("First %d fibonacci numbers are : ", n);
    for(int i = 0; i < n; i++)
        printf("%d ",fib(i));   
    
    printf("\n");
    return 0;
}
