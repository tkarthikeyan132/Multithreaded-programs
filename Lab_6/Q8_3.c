#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>

#define N 3

struct block_adj 
{
    int **arr;
    int **adrr;
    int i;
    int j;
};

struct block_inv
{
    int **arr;
    float **inver;
    int i;
    int j;
    int det;
};

struct block_transpose
{
    int **arr;
    int **trr;
    int resp;
};

void *runner_adj(void *param)
{
    struct block_adj *b = param;
    int **temp = malloc(sizeof(int)*(N-1));
    for(int i = 0; i < (N-1); i++)
    {
        temp[i] = malloc(sizeof(int)*(N-1));
    }

    int i = 0, j = 0; 
	for (int row = 0; row < N; row++) 
	{ 
		for (int col = 0; col < N; col++) 
		{ 
			if (row != (b->i) && col != (b->j)) 
			{ 
				temp[i][j++] = b->arr[row][col];  
				if (j == (N - 1)) 
				{ 
					j = 0; 
					i++; 
				} 
			} 
		} 
	}

    int sign = 1;
    if(((b->i)+(b->j))%2)
        sign = -1;

    b->adrr[b->i][b->j] =  sign*((temp[0][0]*temp[1][1])-(temp[0][1]*temp[1][0]));

}

void *runner_transpose(void *param)
{
    struct block_transpose *bt = param;
    for(int i = 0; i < N; i++)
    {
        bt->trr[i][bt->resp] = bt->arr[bt->resp][i];
    }
}

void *runner_inv(void *param)
{
    struct block_inv *b = param;
    b->inver[b->i][b->j] = (float)b->arr[b->i][b->j] / b->det;
}

void printarray(int **arr, int size)
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}

int main()
{
    printf("Enter an 3x3 matrix row-wise : ");
    int **arr = malloc(sizeof(int)*N);
    for(int i = 0; i < N; i++)
    {
        arr[i] = malloc(sizeof(int)*N);
        for(int j = 0; j < N; j++)
            scanf("%d", &arr[i][j]);
    }
    printf("Given array is \n");
    printarray(arr, N); 

    int **adrr = malloc(sizeof(int *)*N); // cofactor matrix untransposed
    for(int i = 0; i < N; i++)
        adrr[i] = malloc(sizeof(int)*N);

    int **atrr = malloc(sizeof(int *)*N); // cofactor matrix transposed
    for(int i = 0; i < N; i++)
        atrr[i] = malloc(sizeof(int)*N);

    float **inver = malloc(sizeof(float *)*N); // inverse
    for(int i = 0; i < N; i++)
        inver[i] = malloc(sizeof(float)*N);

    // cofactor matrices creation
    struct block_adj b[3][3];
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            b[i][j].arr = arr;
            b[i][j].adrr = adrr;
            b[i][j].i = i; 
            b[i][j].j = j;
        }

    pthread_t tid[3][3];
    
    pthread_attr_t attr[3][3];

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            pthread_attr_init(&attr[i][j]);
    
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            pthread_create(&tid[i][j], &attr[i][j], runner_adj, &b[i][j]);
        }

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            pthread_join(tid[i][j], NULL);

    printf("Cofactor matrix untransposed\n");
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
            printf("%d ", adrr[i][j]);
        printf("\n");
    }

    // Transpose calculation

    struct block_transpose bt[N];

    for(int i = 0; i < N; i++)
    {
        bt[i].arr = adrr;
        bt[i].trr = atrr;
        bt[i].resp = i;
    }

    pthread_t ttid[N];

    pthread_attr_t atttr[N];

    for(int i = 0; i < N; i++)
        pthread_attr_init(&atttr[i]);

    for(int i = 0; i < N; i++)
    {
        pthread_create(&ttid[i], &atttr[i], runner_transpose, &bt[i]);
    }

    for(int i = 0; i < N; i++)
    {
        pthread_join(ttid[i], NULL);
    }

    printf("Cofactor matrix transposed\n");
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
            printf("%d ", atrr[i][j]);
        printf("\n");
    }

    int determinant = (arr[0][0]*adrr[0][0]) + (arr[0][1]*adrr[0][1]) + (arr[0][2]*adrr[0][2]);

    printf("determinant is %d\n", determinant);
    // dividing each element by determinant to get inverse

    struct block_inv bi[3][3];
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            bi[i][j].arr = atrr;
            bi[i][j].i = i; 
            bi[i][j].j = j;
            bi[i][j].det = determinant;
            bi[i][j].inver = inver;
        }

    pthread_t tttid[3][3];
    
    pthread_attr_t attttr[3][3];

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            pthread_attr_init(&attttr[i][j]);
    
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            pthread_create(&tttid[i][j], &attttr[i][j], runner_inv, &bi[i][j]);
        }

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            pthread_join(tttid[i][j], NULL);

    printf("Inverse\n");
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
            printf("%.2f ", inver[i][j]);
        printf("\n");
    }

    return 0;
}
