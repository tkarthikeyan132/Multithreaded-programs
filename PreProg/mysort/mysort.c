#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        printf("No arguments provided\n");
        exit(0);
    }
    int n, flag;
    n = atoi(argv[1]);
    if(argc - 3 != n)
    {
        printf("Insufficient number of arguments\n");
        exit(0);
    }
    int arr[n];
    for(int i = 2; i <= n+1; i++)
    {
        arr[i-2] = atoi(argv[i]);
    }
    flag = atoi(argv[n+2]);
    for(int j = 1; j < n; j++)
    {
        int key = arr[j];
        int i = j - 1;
        while(i>=0 && arr[i]>key)
        {
            arr[i+1] = arr[i];
            i = i-1;
        }
        arr[i+1] = key;
    }
    if(flag==1)
    {
        for(int k = 0; k < n; k++)
        {
            printf("%d ",arr[k]);
        }
    }
    else
    {
        for(int k = n-1; k >= 0; k--)
        {
            printf("%d ",arr[k]);
        }
    }
    printf("\n");
    return 0;
}
