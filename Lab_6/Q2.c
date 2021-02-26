#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

int n; // size of the array

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
    
    pthread_t tid1, tid2;
    
    pthread_attr_t attr1, attr2;
    
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    pthread_create(&tid1, &attr1, runner1, arr);
    pthread_create(&tid2, &attr2, runner2, arr);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}

void *runner1(void *param)
{
    int *arr = param;
    for(int j = 1; j < n; j++)
        {
            int key = arr[j];
            int i = j-1;
            while(i>=0 && arr[i]>key)
            {
                arr[i+1] = arr[i];
                i = i-1;
            }
            arr[i+1] = key;
        }
    printf("Sorted array in ascending order : ");
    for(int i = 0; i < n; i++)
        printf("%d ",*(arr+i));
    printf("\n");
}

void *runner2(void *param)
{
    int *arr = param;
    for(int j = 1; j < n; j++)
        {
            int key = arr[j];
            int i = j-1;
            while(i>=0 && arr[i]<key)
            {
                arr[i+1] = arr[i];
                i = i-1;
            }
            arr[i+1] = key;
        }
    printf("Sorted array in descending order : ");
    for(int i = 0; i < n; i++)
        printf("%d ",*(arr+i));
    printf("\n");
}