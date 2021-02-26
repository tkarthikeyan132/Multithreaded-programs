#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

int n; // number of elements in an array
float mean, median;

void *runner1(void *param);

void *runner2(void *param);

void *runner3(void *param);

int main()
{
    printf("Enter the number of elements : ");
    scanf("%d",&n);
    int *arr = (int *)malloc(sizeof(int)*n);
    printf("Enter the elements : ");
    for(int i = 0; i < n; i++)
        scanf("%d",(arr+i));
    
    pthread_t tid1, tid2, tid3;
    
    pthread_attr_t attr1, attr2, attr3;
    
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);
    pthread_attr_init(&attr3);

    pthread_create(&tid1, &attr1, runner1, arr);
    pthread_create(&tid2, &attr2, runner2, arr);
    pthread_create(&tid3, &attr3, runner3, arr);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    printf("Mean is %f\n", mean);
    printf("Median is %f\n", median);

    return 0;
}

void *runner1(void *param) // mean 
{
    int *arr = param;
    long sum = 0;
    for(int i = 0; i < n; i++)
        sum += *(arr+i);
    mean = (float)sum / n;
    pthread_exit(0);
}

void *runner2(void *param) // median
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
    if(n%2) //odd
        median = arr[n/2];
    else
        median = (arr[n/2] + arr[n/2 - 1])/(float)2;
    pthread_exit(0);
}

void *runner3(void *param) // mode
{
    int *arr = param;
    int maxi = 0; // highest value of brr
    int nm = 0; // number of modes
    int brr[n];
    for(int j = 0; j < n; j++)
        brr[j] = 1;

    for(int j = 0; j < n-1; j++)
    {
        if(brr[j]!=-1)
        {
            for(int k = j+1; k < n; k++)
            {
                if(arr[j] == arr[k])
                {
                    brr[j]++;
                    brr[k] = -1;
                }
            }
        }
    }
    for(int k = 0; k < n; k++)
    {
        if(brr[k] > maxi)
            maxi = brr[k];
    }

    if(maxi != 1)
    {
        for(int i = 0; i < n; i++)
            if(brr[i] == maxi)
                nm++;
        if(nm == 1)
        {
            printf("Mode is ");
            for(int i = 0; i < n; i++)
                if(brr[i] == maxi)
                    printf("%d", arr[i]);
            printf("\n");
        }
        else
        {
            printf("Modes are ");
            for(int i = 0; i < n; i++)
                if(brr[i] == maxi)
                    printf("%d ", arr[i]);
            printf("\n");
        }
        
    }
    else
        printf("No Mode exists\n");
    pthread_exit(0);
}