#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>

int L[1000][1000];
char Y[] = "AGGTAB"; 
char X[] = "GXTXAYB"; 

int min(int a, int b); 

int max(int a, int b); 

struct block
{
    int x;
    int y;
};

/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
//int lcs( char *X, char *Y, int m, int n ) 
void *runner(void *param)
{
/* Following steps build L[m+1][n+1] in bottom up fashion. Note 
	that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
    struct block *b = param;
    int i = b->x;
    int j = b->y;
    
    /*for (int i=0; i <= m; i++) 
    { 
        for (int j=0; j <= n; j++) 
        { 
        if (i == 0 || j == 0) 
            L[i][j] = 0; */

        if (X[i-1] == Y[j-1]) 
        {
            L[i][j] = L[i-1][j-1] + 1; 
        }
        else
            L[i][j] = max(L[i-1][j], L[i][j-1]); 
      /*  } 
    } 
        
    //L[m][n] contains length of LCS for X[0..n-1] and Y[0..m-1] 
    return L[m][n]; */
    pthread_exit(0);
} 

/* Utility function to get max of 2 integers */
int min(int a, int b) 
{ 
	return (a > b)? b : a; 
}

int max(int a, int b) 
{ 
	return (a > b)? a : b; 
}

/* Driver program to test above function */
int main() 
{ 
    printf("Enter main string(larger) : ");
    scanf("%s",X);

    printf("Enter sub string(smaller) : ");
    scanf("%s",Y);

    int m = strlen(X); 
    int n = strlen(Y); 

    int mi = min(m,n);
    int ma = max(m,n);

    for(int i = 0; i <= ma; i++)
    {
        L[0][i] = 0;
        L[i][0] = 0;
    }

    for(int k = 1; k <= mi; k++) // L[1,k]...
    {
        int tx = 1;
        int ty = k;
        int strand_size = 0;
        while(ty!=0 && tx!=(ma+1))
        {
            strand_size++;
            tx++;
            ty--;
        }

        int strand_x[strand_size];
        int strand_y[strand_size];
        tx = 1;     ty = k;
        int temp = 0;

        while(ty!=0 && tx!=(ma+1))
        {
            strand_x[temp] = tx;
            strand_y[temp] = ty;
            temp++;
            tx++;
            ty--;
        }
        // for(int i = 0; i < strand_size; i++)
        //     printf("(%d,%d),", strand_x[i], strand_y[i]);
        // printf("\n");

        int NUM_THREADS = strand_size;

        struct block b[NUM_THREADS];
        for(int i = 0; i < NUM_THREADS; i++)
        {
            b[i].x = strand_x[i];
            b[i].y = strand_y[i];
        }
        
        pthread_t tid[NUM_THREADS];

        pthread_attr_t attr[NUM_THREADS];

        for(int i = 0; i < NUM_THREADS; i++)
            pthread_attr_init(&attr[i]);

        for(int i = 0; i < NUM_THREADS; i++)
        {
            pthread_create(&tid[i], &attr[i], runner, &b[i]);
        }

        for(int i = 0; i < NUM_THREADS; i++)
            pthread_join(tid[i], NULL);

    }

    for(int k = 2; k <= ma; k++) // L[k,mi]...
    {
        int tx = k;
        int ty = mi;
        int strand_size = 0;
        while(ty!=0 && tx!=(ma+1))
        {
            strand_size++;
            tx++;
            ty--;
        }

        int strand_x[strand_size];
        int strand_y[strand_size];
        tx = k;     ty = mi;
        int temp = 0;

        while(ty!=0 && tx!=(ma+1))
        {
            strand_x[temp] = tx;
            strand_y[temp] = ty;
            temp++;
            tx++;
            ty--;
        }

        int NUM_THREADS = strand_size;

        struct block b[NUM_THREADS];
        for(int i = 0; i < NUM_THREADS; i++)
        {
            b[i].x = strand_x[i];
            b[i].y = strand_y[i];
        }

        pthread_t tid[NUM_THREADS];

        pthread_attr_t attr[NUM_THREADS];

        for(int i = 0; i < NUM_THREADS; i++)
            pthread_attr_init(&attr[i]);

        for(int i = 0; i < NUM_THREADS; i++)
        {
            pthread_create(&tid[i], &attr[i], runner, &b[i]);
        }

        for(int i = 0; i < NUM_THREADS; i++)
            pthread_join(tid[i], NULL);
    }

    //printf("Length of LCS is %d", lcs( X, Y, m, n ) );
    printf("X:%s\n",X);
    printf("Y:%s\n",Y); 
    printf("LCS is %d\n",L[m][n]);
    for(int i = 0; i <= ma; i++)
    {
        for(int j = 0; j <= mi; j++)
        {
            printf("%d ",L[i][j]);
        }
        printf("\n");
    }

    return 0; 
} 

