#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string>

using namespace std;

int typedet(string stri)
{
    int ci = 0;
    int cc = 0;
    int cd = 0;
    for(int i = 0; i < stri.length(); i++)
    {
        if(stri[i] == '.')
            cd++;
        else if(stri[i] >= 48 && stri[i] <= 57)
            ci++;
        else if(( stri[i] >= 65 && stri[i] <= 90 )||(stri[i] >= 97 && stri[i] <= 122))
            cc++;
    }
    if(cd == 1)
        return 2;
    else if(ci == stri.length())
        return 1;
    else if(cc == stri.length())
        return 0;
    else 
        return -1;
}
    
int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        printf("No arguments provided\n");
        exit(0);
    }
    int n, flag, type; 
    n = atoi(argv[1]);
    if(argc - 3 != n)
    {
        printf("Insufficient number of arguments\n");
        exit(0);
    }
    flag = atoi(argv[n+2]);
    string test = argv[2];
    type = typedet(argv[2]);
    
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
