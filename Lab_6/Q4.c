#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

int n; // number upto which prime numbers need to be generated

void *runner(void *param);

_Bool isprime(int n);

int main(int argc, char **argv)
{
    n = atoi(argv[1]);
    int *arr = (int *)malloc(sizeof(int)*(n+1));
    for(int i = 0; i <= n; i++)
        arr[i] = i;
    
    pthread_t tid[n+1];
    
    pthread_attr_t attr[n+1];

    for(int i = 0; i <= n; i++)
        pthread_attr_init(&attr[i]);
    
    for(int i = 0; i <= n; i++)
        pthread_create(&tid[i], &attr[i], runner, &arr[i]);

    for(int j = 0; j <= n; j++)
        pthread_join(tid[j], NULL);

    printf("\n");

    return 0;
}

void *runner(void *param)
{
    int *z = param;
    if(isprime(*z))
        printf("%d ",*z);
    pthread_exit(0);
}

_Bool isprime(int n)
{
    int i, flag = 1; 
  
    // Iterate from 2 to n/2 
    for (i = 2; i <= sqrt(n); i++) { 
  
        // If n is divisible by any number between 
        // 2 and n/2, it is not prime 
        if (n % i == 0) { 
            flag = 0; 
            break; 
        } 
    } 
  
    if(n<=1) 
        flag=0; 
    else if(n==2) 
        flag=1;  
  
    if (flag == 1) { 
        return 1; 
    } 
    else { 
        return 0;
    } 
  
    return 0; 
}