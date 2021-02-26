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
    while(te!=0) // number of digits in number
    {
        ND++;
        te/=10;
    }
    long long sum = 0;
    while(n!=0) // armstrong number calculation
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
    int fd2[2];
    pipe(fd2);
    //fd[0] - read
    //fd[1] - write
    if(pipe(fd)==-1)
        printf("Pipe error\n");
    int a,b;
    printf("Enter the range [a, b] : ");
    scanf("%d %d",&a, &b);
    int pid;
    pid = fork();
    if(pid > 0) // parent
    {
        long long Result[b-a+1];
        long long FinRes[b-a+1];
        int fr = 0;

        close(fd[1]);
        read(fd[0], Result, (b-a+1)*sizeof(long long));
        close(fd[0]);
        printf("<inside parent>Separating Armstrong numbers from rest ...\n");
        for(int i = 0; i < (b-a+1); i++)
        {
            if(Result[i] == (a+i))
            {
                FinRes[fr] = Result[i];
                fr++;
            }
        }

        printf("<inside parent>Sending Armstrong numbers to child ...\n");
        close(fd2[0]);
        write(fd2[1], &fr, sizeof(int));
        write(fd2[1], FinRes, fr*sizeof(long long));
        close(fd2[1]);
    }
    else if(pid == 0) // child
    {
        long long sum[b-a+1];
        long long Finres[b-a+1];
        int fr;

        close(fd[0]);
        printf("<inside child>Digit extraction and power calculation ...\n");
        for(int i = 0; i < (b-a+1); i++)
        {
            sum[i] = ArmStrCalculation(a+i);
        }
        write(fd[1], sum, (b-a+1)*sizeof(long long));
        close(fd[1]);

        close(fd2[1]);
        read(fd2[0], &fr, sizeof(int));
        read(fd2[0], Finres, fr*sizeof(long long));
        close(fd2[0]);

        printf("<inside child>List of Armstrong numbers : ");
        for(int k = 0; k < fr; k++)
        {
            printf("%lld ", Finres[k]);
        }
        printf("\n");
    }
    else
    {
        printf("Fork failed\n");
    }
    return 0;
}
