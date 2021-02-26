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
    int n, flag, type; 
    n = atoi(argv[1]);
    if(argc - 4 != n)
    {
        printf("Insufficient number of arguments\n");
        exit(0);
    }
    flag = atoi(argv[n+2]);
    type = atoi(argv[n+3]); //type = 0 for char, 1 for int, 2 for float
    
    if(type == 0)
    {
        char arr[n];
        for(int i = 2; i <= n+1; i++)
        {
            arr[i-2] = *argv[i];
        }
        
        for(int j = 1; j < n; j++)
        {
            char key = arr[j];
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
                printf("%c ",arr[k]);
            }
        }
        else
        {
            for(int k = n-1; k >= 0; k--)
            {
                printf("%c ",arr[k]);
            }
        }
        printf("\n");
    }
    
    else if(type == 1)
    {
        int arr[n];
        for(int i = 2; i <= n+1; i++)
        {
            arr[i-2] = atoi(argv[i]);
        }
        
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
    }
    
    else if(type == 2)
    {
        float arr[n];
        for(int i = 2; i <= n+1; i++)
        {
            arr[i-2] = atof(argv[i]);
        }
        
        for(int j = 1; j < n; j++)
        {
            float key = arr[j];
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
                printf("%f ",arr[k]);
            }
        }
        else
        {
            for(int k = n-1; k >= 0; k--)
            {
                printf("%f ",arr[k]);
            }
        }
        printf("\n");
    }
    
    else
    {
        printf("Data type not supported by the function\n");
        exit(0);
    }
    
    return 0;
}
