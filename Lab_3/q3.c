#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

long long ArmStrCalculation(int n)
{
    int te = n;
    int ND = 0;
    while(te!=0)
    {
        ND++;
        te/=10;
    }
    long long sum = 0;
    while(n!=0)
    {
        int temp = n%10;
        sum = sum + pow(temp,ND);
        n/=10;
    }
    return sum;
}
int main()
{
    int fd[2];
    //fd[0] - read
    //fd[1] - write
    if(pipe(fd)==-1)
        printf("Pipe error\n");
    int a,b;
    printf("Enter the range [a, b] : ");
    scanf("%d %d",&a, &b);
    int pid;
    pid = fork();
    if(pid == 0) // child to check and display
    {
        wait(NULL);
        long long Result[b-a+1];
        close(fd[1]);
        read(fd[0], Result, (b-a+1)*sizeof(long long));
        close(fd[0]);
        printf("List of Armstrong numbers are : ");
        for(int i = 0; i < (b-a+1); i++)
        {
            if(Result[i] == (a+i))
                printf("%lld ",Result[i]);
        }
        printf("\n");
    }
    else if(pid > 0) //parent to calculate ArmStr
    {
        long long sum[b-a+1];
        close(fd[0]);
        for(int i = 0; i < (b-a+1); i++)
        {
            sum[i] = ArmStrCalculation(a+i);
        }
        write(fd[1], sum, (b-a+1)*sizeof(long long));
        close(fd[1]);
    }
    else
    {
        printf("Fork failed\n");
    }
    return 0;
}
