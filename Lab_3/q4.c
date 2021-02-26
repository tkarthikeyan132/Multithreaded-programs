#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

int main()
{
    int n;
    printf("Enter the value of n : ");
    scanf("%d",&n);
    int pid;
    pid = fork();
    if(pid == 0) // child doing prime number generation
    {
        wait(NULL);
        bool prime[n+1];
        for(int i = 0; i <= n; i++)
            prime[i] = true;
        for(int p = 2; p*p <= n; p++)
        {
            if(prime[p] == true)
            {
                for(int j = p*p; j <= n; j=j+p)
                    prime[j] = false;
            }
        }
        printf("Prime numbers upto %d : ",n);
        for(int k = 2; k <= n; k++)
        {
            if(prime[k])
                printf("%d ",k);
        }
        printf("\n");
    }
    else if(pid > 0) // parent does fibonacci number generation
    {
        int prev = 0;
        int curr = 1;
        printf("First %d fibonacci numbers are : %d %d ",n,prev, curr);
        for(int i = 2; i < n; i++)
        {
            int temp = prev + curr;
            printf("%d ",temp);
            prev = curr;
            curr = temp;
        }
        printf("\n");
    }
    else
        printf("Fork error!!!\n");
    return 0;
}
