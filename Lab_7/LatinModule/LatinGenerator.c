#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>

struct block
{
    int **arr;
    int n;
    int resp;
};

void *runner(void *param)
{
    struct block *b = param;
    int temp = b->resp;
    int index = b->resp - 1;
    int n = b->n;

    for(int i = 0; i < b->n; i++)
    {
        b->arr[index][i] = temp;
        temp++;
        if(temp == (n+1))
            temp = 1;
    }

    pthread_exit(0);
}

int main()
{
    int n;
    printf("Enter the degree of the matrix : ");
    scanf("%d", &n);

    int **arr = malloc(sizeof(int *)*n);
    for(int i = 0; i < n; i++)
        arr[i] = malloc(sizeof(int)*n);

    struct block b[n];
    for(int i = 0; i < n; i++)
    {
        b[i].arr = arr;
        b[i].n = n;
        b[i].resp = i+1;
    }

    pthread_t tid[n];

    pthread_attr_t attr[n];

    for(int i = 0; i < n; i++)
        pthread_attr_init(&attr[i]);

    for(int i = 0; i < n; i++)
    {
        pthread_create(&tid[i], &attr[i], runner, &b[i]);
    }

    for(int i = 0; i < n; i++)
    {
        pthread_join(tid[i], NULL);
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            printf("%d ",arr[i][j]);
        printf("\n");
    }

    return 0;
}