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
    char *str;
    int *frr;
    int slen;
    char c;
    int ci;
};

void *runner(void *param)
{
    struct block *b = param;
    for(int i = 0; i < (b->slen); i++)
    {
        if(b->str[i] == (b->c))
            b->frr[b->ci]++;
    }
    pthread_exit(0);
}

int main()
{
    char *str = malloc(sizeof(char)*(1000));
    int slen;

    printf("Enter the string :");
    fgets(str, 1000, stdin);
    slen = strlen(str);
    slen--;


    printf("String is :%s", str);
    printf("String length is %d\n", slen);

    _Bool arr[127] = {0}; // to indicate whether particular character exists or not
    int NUM_THREAD = 0;

    for(int i = 0; i < slen; i++)
    {
        if(arr[str[i]] == 0)
        {
            arr[str[i]] = 1;
            NUM_THREAD++;
        }
    }

    printf("NUM_THREAD : %d\n", NUM_THREAD);

    int brr[127] = {-1}; // store the newly  assigned index
    for(int i = 0; i < 127; i++)
        brr[i] = -1;

    char trr[NUM_THREAD]; // index to char mapping

    int index = 0;
    
    for(int i = 0; i < slen; i++)
    {
        if(brr[str[i]] == -1)
        {
            brr[str[i]] = index;
            trr[index] = str[i];
            index++;
        }
    }

    int *frr = malloc(sizeof(int)*NUM_THREAD);
    for(int i = 0; i < NUM_THREAD; i++)
        frr[i] = 0;

    struct block b[NUM_THREAD];
    for(int i = 0; i < NUM_THREAD; i++)
    {
        b[i].str = str;
        b[i].slen = slen;
        b[i].frr = frr;
        b[i].c = trr[i];
        b[i].ci = brr[trr[i]];
    }

    pthread_t tid[NUM_THREAD];

    pthread_attr_t attr[NUM_THREAD];

    for(int i = 0; i < NUM_THREAD; i++)
        pthread_attr_init(&attr[i]);

    for(int i = 0; i < NUM_THREAD; i++)
        pthread_create(&tid[i], &attr[i], runner, &b[i]);

    for(int i = 0; i < NUM_THREAD; i++)
        pthread_join(tid[i], NULL);

    printf("HISTOGRAM\n");

    for(int i = 0; i < NUM_THREAD; i++)
        printf("%c : %d\n", trr[i], frr[i]);

    free(str);

    return 0;
}