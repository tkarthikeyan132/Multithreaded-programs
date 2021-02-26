#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

int n; // number of elements in an array
int p = 0; // number of occurance of particular element
int ele; // element to be searched

void *runner1(void *param);

void *runner2(void *param);

int main()
{
    printf("Enter the number of elements : ");
    scanf("%d",&n);
    int *arr = (int *)malloc(sizeof(int)*n);
    printf("Enter the elements : ");
    for(int i = 0; i < n; i++)
        scanf("%d",(arr+i));
    printf("Enter the element to be searched : ");
    scanf("%d",&ele);
    
    pthread_t tid1, tid2;
    
    pthread_attr_t attr1, attr2;
    
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    pthread_create(&tid1, &attr1, runner1, arr);
    pthread_create(&tid2, &attr2, runner2, arr);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("Element %d is found %d times in an array\n", ele, p);

    return 0;
}

void *runner1(void *param)
{
    int *arr = param;
    for(int i = 0; i < n/2; i++)
        if(*(arr+i) == ele)
            p++;
}

void *runner2(void *param)
{
    int *arr = param;
    for(int i = n/2; i < n; i++)
        if(*(arr+i) == ele)
            p++;
}