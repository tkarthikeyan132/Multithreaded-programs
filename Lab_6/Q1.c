#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

int arr[100000];
long long rrr[100000];


long long ArmStrCalculation(int n)
{
    int te = n;
    int ND = 0;
    while(te!=0) // number of digits in number
    {
        ND++;
        te/=10;
    }
    long long sum = 0;
    while(n!=0) // armstrong number calculation
    {
        int temp = n%10;
        sum = sum + pow(temp,ND);
        n/=10;
    }
    return sum;
}

struct block
{
    int x;
    int y;
};

void *runner(void *param)
{
    struct block *data = param;
    for(int y = data->x; y <= data->y; y++)
    {
        rrr[y] = ArmStrCalculation(arr[y]);
    }
    pthread_exit(0);
}

int main()
{
    int a,b;
    printf("Enter the range [a, b] : ");
    scanf("%d",&a);
    scanf("%d",&b);

    for(int k = a; k <= b; k++)
        arr[k] = k;

    int start[4];
    int end[4];
    int n = b - a + 1;
    int mid1 = a + (n/4);
    int mid2 = a + 2*(n/4);
    int mid3 = a + 3*(n/4);

    start[0] = a;       end[0] = mid1 - 1;
    start[1] = mid1;    end[1] = mid2 - 1;
    start[2] = mid2;    end[2] = mid3 - 1;
    start[3] = mid3;    end[3] = b;

    pthread_t tid;
    pthread_attr_t attr;
    for(int z = 0; z < 4; z++)
    {
        struct block *data = (struct block *)malloc(sizeof(struct block));
        data->x = start[z];
        data->y = end[z];
        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, runner, data);
        pthread_join(tid, NULL);
    }
    
    printf("List of Armstrong numbers : ");
    for(int i = a; i <= b; i++)
    {
        if(arr[i] == rrr[i])
            printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}