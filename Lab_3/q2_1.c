#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int pid;
    int n;
    printf("Enter the value of n : ");
    scanf("%d",&n);
    pid = fork();
    if(pid > 0) // odd by parent
    {
        printf("Odd numbers are : ");
        for(int i = 1; i <= n; i = i+2)
            printf("%d ",i);
        printf("\n");
    }
    else if(pid == 0) // even by child
    {
        printf("Even numbers are : ");
        for(int i = 2; i <= n; i = i+2)
            printf("%d ",i);
        printf("\n");
    }
    else
    {
        printf("Fork failed!!!\n");
    }
    return 0;
}
