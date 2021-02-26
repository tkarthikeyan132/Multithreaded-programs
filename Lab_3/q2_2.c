#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int pid;
    int n;
    printf("Enter the value of n : ");
    scanf("%d",&n);
    int arr[n+1];
    for(int i = 1; i <= n; i++)
        arr[i] = i;
    printf("Series generated : ");
    for(int i = 1; i <= n; i++)
        printf("%d ",arr[i]);
    printf("\n");
    pid = fork();
    if(pid > 0) // sum of odd indexes by parent
    {
        int sumo = 0;
        for(int i = 1; i <= n; i = i+2)
            sumo+=arr[i];
        printf("Sum of odd terms is %d\n",sumo);
    }
    else if(pid == 0) // sum of even indexes by child
    {
        int sume = 0;
        for(int i = 2; i <= n; i = i+2)
            sume+=arr[i];
        printf("Sum of even terms is %d\n",sume);
    }
    else
    {
        printf("Fork failed!!!\n");
    }
    return 0;
}
