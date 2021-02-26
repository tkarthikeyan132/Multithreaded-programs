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

// A utility function to swap two elements 
void swap(int* a, int* b) 
{ 
	int t = *a; 
	*a = *b; 
	*b = t; 
} 

/* This function takes last element as pivot, places 
the pivot element at its correct position in sorted 
array, and places all smaller (smaller than pivot) 
to left of pivot and all greater elements to right 
of pivot */
int partition (int arr[], int low, int high) 
{ 
	int pivot = arr[high]; // pivot 
	int i = (low - 1); // Index of smaller element 

	for (int j = low; j <= high- 1; j++) 
	{ 
		// If current element is smaller than the pivot 
		if (arr[j] < pivot) 
		{ 
			i++; // increment index of smaller element 
			swap(&arr[i], &arr[j]); 
		} 
	} 
	swap(&arr[i + 1], &arr[high]); 
	return (i + 1); 
} 

/* The main function that implements QuickSort 
arr[] --> Array to be sorted, 
low --> Starting index, 
high --> Ending index */
void *runner(void *param) 
{ 
	struct block *b = param;
    if ((b->start) < (b->end)) 
	{ 
		/* pi is partitioning index, arr[p] is now 
		at right place */
		int pi = partition(b->arr, b->start, b->end); 

        struct block lb;
        struct block rb;

        lb.arr = b->arr;
        lb.start = b->start;
        lb.end = pi - 1;

        rb.arr = b->arr;
        rb.start = pi + 1;
        rb.end = b->end;

        pthread_t tid1, tid2;

        pthread_attr_t attr1, attr2;

        pthread_attr_init(&attr1);
        pthread_attr_init(&attr2);

        pthread_create(&tid1, &attr1, runner, &lb);
        pthread_create(&tid2, &attr2, runner, &rb);
        
		// Separately sort elements before 
		// partition and after partition 
		// quickSort(arr, low, pi - 1); 
		// quickSort(arr, pi + 1, high); 
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);
	} 
    pthread_exit(0);
} 

/* Function to print an array */
void printArray(int arr[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++) 
		printf("%d ", arr[i]); 
	printf("\n"); 
} 

// Driver program to test above functions 
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
	//quickSort(arr, 0, n-1); 

	pthread_join(tid, NULL);

    printf("Sorted array : ");
    printArray(arr, arr_size);

	return 0; 
} 
