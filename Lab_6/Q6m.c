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
    int *arr;
    int start;
    int end;
};

void merge(int *arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
 
    // Create temp arrays 
    int L[n1], R[n2];
 
    // Copy data to temp arrays L[] and R[] 
    for(int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for(int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    // Merge the temp arrays back into arr[l..r]
     
    // Initial index of first subarray
    int i = 0; 
     
    // Initial index of second subarray
    int j = 0; 
     
    // Initial index of merged subarray
    int k = l;
     
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j]) 
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    // Copy the remaining elements of
    // L[], if there are any 
    while (i < n1) 
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    // Copy the remaining elements of
    // R[], if there are any 
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
// l is for left index and r is 
// right index of the sub-array
// of arr to be sorted */
void *runner(void *param)
{
    struct block *b = param;
    if ((b->start) < (b->end))
    {
         
        // Same as (l+r)/2, but avoids 
        // overflow for large l and h
        int m = (b->start) + ((b->end) - (b->start)) / 2;
 
        struct block lb;
        struct block rb;

        lb.arr = b->arr;
        lb.start = b->start;
        lb.end = m;

        rb.arr = b->arr;
        rb.start = m+1;
        rb.end = b->end;

        pthread_t tid1, tid2;

        pthread_attr_t attr1, attr2;

        pthread_attr_init(&attr1);
        pthread_attr_init(&attr2);

        pthread_create(&tid1, &attr1, runner, &lb);
        pthread_create(&tid2, &attr2, runner, &rb);
        
        // Sort first and second halves
        // mergeSort((b->arr), (b->start), m);
        // mergeSort((b->arr), m + 1, (b->end));

        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);
 
        merge((b->arr), (b->start), m, (b->end));
    }
    pthread_exit(0);
}
 
// UTILITY FUNCTIONS 
// Function to print an array 
void printArray(int *A, int size)
{
    for(int i = 0; i < size; i++)
        printf("%d ",*(A+i));
}
 
// Driver code
int main()
{
    int arr_size;
    printf("Enter the size of the array : ");
    scanf("%d", &arr_size);

    int arr[arr_size];
    printf("Enter the elements of the array : ");
    for(int y = 0; y < arr_size; y++)
        scanf("%d",&arr[y]);

    struct block b;
    b.arr = arr;
    b.start = 0;
    b.end = arr_size - 1;
 
    pthread_t tid;

    pthread_attr_t attr;

    pthread_attr_init(&attr);

    pthread_create(&tid, &attr, runner, &b);
    //mergeSort(arr, 0, arr_size - 1);
 
    pthread_join(tid, NULL);

    printf("Sorted array : ");
    printArray(arr, arr_size);

    printf("\n");

    return 0;
}