#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int n;
    printf("Enter the number of elements : ");
    scanf("%d",&n);
    int arr[n];
    printf("Enter the elements : ");
    for(int i = 0; i < n; i++)
        scanf("%d",&arr[i]);
    int pid;
    pid = fork();
    if(pid > 0) // parent will do ascending sort
    {
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
            printf("%d ",arr[i]);
        printf("\n");
    }
    else if(pid == 0) // child will do descending sort
    {
        wait(NULL);
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
            printf("%d ",arr[i]);
        printf("\n");
    }
    else
    {
        printf("Fork error!!!\n");
    }
    return 0;
}
