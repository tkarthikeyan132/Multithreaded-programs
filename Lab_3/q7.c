#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int BinarySearch(int *arr, int beg, int end, int key)
{
    if(beg > end)
        return -1;
    int mid = beg + (end - beg)/2;
    if(arr[mid] == key)
    {
        if(mid > beg && arr[mid-1] == key)
            return BinarySearch(arr, beg, mid-1, key);
        else
            return mid;
    }
    else if(arr[mid] > key)
        return BinarySearch(arr, beg, mid-1, key);
    else
        return BinarySearch(arr, mid+1, end, key);
}

int main()
{
    int n, midd;
    printf("Enter the number of elements : ");
    scanf("%d",&n);
    if(n%2)
        midd = n/2 + 1;
    else
        midd = n/2;
    int arr[n];
    printf("Enter the elements : ");
    for(int i = 0; i < n; i++)
        scanf("%d",&arr[i]);
    int key;
    printf("Enter the key to be searched : ");
    scanf("%d",&key);
    int pid;
    pid = fork();
    if(pid > 0) // parent will do search in left side
    {
        for(int j = 1; j < midd; j++)
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
        printf("First half array sorted in ascending order : ");
        for(int i = 0; i < midd; i++)
            printf("%d ",arr[i]);
        printf("\n");
        
        int res1;
        res1 = BinarySearch(arr, 0, midd-1, key);
        if(res1 == -1)
            printf("key not found in first half\n");
        else
        {
            int count = 1;
            while(arr[res1+1]==key && res1 < midd-1)
            {
                count++;
                res1++;
            }
            printf("key found %d times in first half\n", count);
        }
    }
    else if(pid == 0) // child will do search in right side
    {
        wait(NULL);
        for(int j = midd+1; j < n; j++)
        {
            int key = arr[j];
            int i = j-1;
            while(i>=midd && arr[i]>key)
            {
                arr[i+1] = arr[i];
                i = i-1;
            }
            arr[i+1] = key;
        }
        printf("Second half array sorted in ascending order : ");
        for(int i = midd; i < n; i++)
            printf("%d ",arr[i]);
        printf("\n");
        
        int res2 = BinarySearch(arr, midd, n-1, key);
        if(res2 == -1)
            printf("key not found in second half\n");
        else
        {
            int count = 1;
            while(arr[res2+1]==key && res2 < n-1)
            {
                count++;
                res2++;
            }
            printf("key found %d times in second half\n", count);
        }
    }
    else
    {
        printf("Fork error!!!\n");
    }
    return 0;
}
