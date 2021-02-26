#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>

double piarr[1024];

void *runner(void *param);

_Bool isInside(float x, float y); // whether point is inside circle of diameter 1

int main()
{
    double pi = 0.0;
    int *arr = (int *)malloc(sizeof(int)*(1024));
    for(int i = 0; i < 1024; i++)
        arr[i] = i;
    // pi is estimated using monte carlo simulation using 1024 threads
    pthread_t tid[1024];
    
    pthread_attr_t attr[1024];

    for(int i = 0; i < 1024; i++)
        pthread_attr_init(&attr[i]);
    
    for(int i = 0; i < 1024; i++)
        pthread_create(&tid[i], &attr[i], runner, &arr[i]);

    for(int j = 0; j < 1024; j++)
        pthread_join(tid[j], NULL);

    for(int i = 0; i < 1024; i++)
        pi += (piarr[i]*10000);

    pi /= (1024*10000);

    printf("Estimated pi value using monte carlo simulation is %lf\n", pi);

    return 0;
}

void *runner(void *param)
{
    int *i = param;
    double pi;
    int inside_circle = 0;
    int inside_square = 0;

    float x[10000], y[10000];
    for(int i = 0; i < 10000; i++)
    {
        x[i] = ((float)rand()/(float)RAND_MAX)*2;
        y[i] = ((float)rand()/(float)RAND_MAX)*2;
    }
    
    for(int k = 0; k < 10000; k++)
    {
        if(isInside(x[k], y[k]))
            inside_circle++;
        inside_square++;
    }

    pi = 4*(double)inside_circle/inside_square;

    piarr[*i] = pi;
}

_Bool isInside(float x, float y)
{
    if((((x-1.0)*(x-1.0))+((y-1.0)*(y-1.0))) < 1.0)
        return 1;
    else
        return 0;
}