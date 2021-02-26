#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>

long long fib[30];

void *runner(void *param);

long long fibonacci(int n);

int main()
{
    int n;
    printf("Enter the number of fibonacci numbers to be generated : ");
    scanf("%d", &n);

    pthread_t tid;

    pthread_attr_t attr;

    pthread_attr_init(&attr);

    pthread_create(&tid, &attr, runner, &n);

    pthread_join(tid, NULL);

    printf("Fibonacci numbers : ");
    for(int i = 0; i < n; i++)
        printf("%lld ", fib[i]);
    printf("\n");

    return 0;
}

void *runner(void *param)
{
    int *i = param;
    if(*i < 2)
        fib[*i] = *i;
    else
    {
        int x = *i - 1;
        int y = *i - 2;

        pthread_t tid1, tid2;
    
        pthread_attr_t attr1, attr2;
    
        pthread_attr_init(&attr1);
        pthread_attr_init(&attr2);

        pthread_create(&tid1, &attr1, runner, &x);
        pthread_create(&tid2, &attr2, runner, &y);

        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);
        
        fib[*i] = fib[x] + fib[y];
    }
    pthread_exit(0);
}
