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
    int **orr;
    int x;
    int y;
};

void *runner(void *param)
{
    struct block *b = param;
    b->orr[b->x][b->y] = 1;
}

_Bool isOrthogonal(int **orr, int n) // can be parallelised
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(orr[i][j] != 1)
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

    printf("Enter Matrix 1 (row-wise) : ");

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &arr[i][j]);

    int **brr = malloc(sizeof(int *)*n);
    for(int i = 0; i < n; i++)
        brr[i] = malloc(sizeof(int)*n);

    printf("Enter Matrix 2 (row-wise) : ");

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &brr[i][j]);

    int **orr = malloc(sizeof(int *)*n);
    for(int i = 0; i < n; i++)
        orr[i] = malloc(sizeof(int)*n);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            orr[i][j] = -1;

    int *hash1 = malloc(sizeof(int)*10000);
    int *hash2 = malloc(sizeof(int)*10000);

    int index1 = 0, index2 = 0;
    for(int i = 0; i < n; i++)
    {
        hash1[arr[0][i]] = index1;
        hash2[brr[0][i]] = index2;
        index1++;
        index2++;
    }

    int **H1 = malloc(sizeof(int *)*n);
    for(int i = 0; i < n; i++)
        H1[i] = malloc(sizeof(int)*n);

    int **H2 = malloc(sizeof(int *)*n);
    for(int i = 0; i < n; i++)
        H2[i] = malloc(sizeof(int)*n);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        {
            H1[i][j] = hash1[arr[i][j]];
            H2[i][j] = hash2[brr[i][j]];
        }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            printf("%d ", H1[i][j]);
        printf("\n");
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            printf("%d ", H2[i][j]);
        printf("\n");
    }

    //orthogonal verification

    int NUM_THREAD_MUL = n*n;

    struct block b[NUM_THREAD_MUL];
    for(int i = 0; i < NUM_THREAD_MUL; i++)
    {
        int x = i/n;
        int y = i%n;
        b[i].orr = orr;
        b[i].x = H1[x][y];
        b[i].y = H2[x][y];
    }

    pthread_t tid[NUM_THREAD_MUL];

    pthread_attr_t attr[NUM_THREAD_MUL];

    for(int i = 0; i < NUM_THREAD_MUL; i++)
        pthread_attr_init(&attr[i]);

    for(int i = 0; i < NUM_THREAD_MUL; i++)
    {
        pthread_create(&tid[i], &attr[i], runner, &b[i]);
    }

    for(int i = 0; i < NUM_THREAD_MUL; i++)
    {
        pthread_join(tid[i], NULL);
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            printf("%d ", orr[i][j]);
        printf("\n");
    }

    if(isOrthogonal(orr,n))
        printf("Matrix is orthogonal\n");
    else
        printf("Matrix is not orthogonal\n");

    return 0;
}