#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>

struct block_transpose
{
    int **arr;
    int **trr;
    int resp;
    int n;
};

struct block_product
{
    int **arr;
    int **trr;
    int **prr;
    int n;
    int x; 
    int y;
};

void *runner_transpose(void *param)
{
    struct block_transpose *bt = param;
    for(int i = 0; i < bt->n; i++)
    {
        bt->trr[i][bt->resp] = bt->arr[bt->resp][i];
    }
}

void *runner_product(void *param)
{
    struct block_product *bp = param;
    bp->prr[bp->x][bp->y] = 0;
    for(int i = 0; i < bp->n; i++)
    {
        bp->prr[bp->x][bp->y] += ((bp->arr[bp->x][i])*(bp->trr[i][bp->y]));
    }
}

_Bool isOrthogonal(int **prr, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i!=j && prr[i][j]!=0)
                return 0;
            if(i==j && prr[i][j]!=1)
                return 0;
        }
    }
    return 1;
}

int main()
{
    int n;
    printf("Enter the degree of the matrix : ");
    scanf("%d", &n);

    int **arr = malloc(sizeof(int *)*n);
    for(int i = 0; i < n; i++)
        arr[i] = malloc(sizeof(int)*n);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &arr[i][j]);

    int **trr = malloc(sizeof(int *)*n);
    for(int i = 0; i < n; i++)
        trr[i] = malloc(sizeof(int)*n);

    int **prr = malloc(sizeof(int *)*n);
    for(int i = 0; i < n; i++)
        prr[i] = malloc(sizeof(int)*n);

    // Transpose calculation

    struct block_transpose bt[n];

    for(int i = 0; i < n; i++)
    {
        bt[i].arr = arr;
        bt[i].trr = trr;
        bt[i].resp = i;
        bt[i].n = n;
    }

    pthread_t tid[n];

    pthread_attr_t attr[n];

    for(int i = 0; i < n; i++)
        pthread_attr_init(&attr[i]);

    for(int i = 0; i < n; i++)
    {
        pthread_create(&tid[i], &attr[i], runner_transpose, &bt[i]);
    }

    for(int i = 0; i < n; i++)
    {
        pthread_join(tid[i], NULL);
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            printf("%d ", trr[i][j]);
        printf("\n");
    }

    // Product calculation

    int NUM_THREAD_MUL = n*n;

    struct block_product bp[NUM_THREAD_MUL];
    for(int i = 0; i < NUM_THREAD_MUL; i++)
    {
        bp[i].arr = arr;
        bp[i].trr = trr;
        bp[i].prr = prr;
        bp[i].n = n;
        bp[i].x = i/n;
        bp[i].y = i%n;
    }

    pthread_t ttid[NUM_THREAD_MUL];

    pthread_attr_t atttr[NUM_THREAD_MUL];

    for(int i = 0; i < NUM_THREAD_MUL; i++)
        pthread_attr_init(&atttr[i]);

    for(int i = 0; i < NUM_THREAD_MUL; i++)
    {
        pthread_create(&ttid[i], &atttr[i], runner_product, &bp[i]);
    }

    for(int i = 0; i < NUM_THREAD_MUL; i++)
    {
        pthread_join(ttid[i], NULL);
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            printf("%d ", prr[i][j]);
        printf("\n");
    }

    if(isOrthogonal(prr,n))
        printf("Matrix is orthogonal\n");
    else
        printf("Matrix is not orthogonal\n");

    return 0;
}