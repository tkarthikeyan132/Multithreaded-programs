#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

#define MAX 100000
int top = -1;

void push(int arr[], int n);
void MagicSquare(int size, int arr[][size]);
void OddOrderMagicSquare(int size, int arr[][size]);
void DoublyEvenMagicSquare(int size, int arr[][size]);
void SinglyEvenMagicSquare(int size, int arr[][size]);
void displayMagicSquare(int size, int arr[][size]);

int main()
{
    int size;
    printf("Enter the order of the matrix:");
    scanf("%d",&size);
    int arr[size][size];
    
    int pid;
    pid = vfork();
    if(pid == 0)
    {
        if(size < 3)
        {
            printf("Order of the matrix should be greater than 2\n");
            exit(-1);
        }
        MagicSquare(size,arr);
        exit(0);
    }
    else
    {
        wait(NULL);
        displayMagicSquare(size, arr);
    }
    return 0;
}

void push(int a[], int n)
{
    if(top == MAX-1)
    {
        printf("\nStack is full!!");
    }
    else
    {
        top = top + 1;
        a[top] = n;
    }
}

void MagicSquare(int size, int arr[][size])
{
    if(size%2 == 1)
        OddOrderMagicSquare(size, arr);
    else if(size%4 == 0)
        DoublyEvenMagicSquare(size, arr);
    else
        SinglyEvenMagicSquare(size, arr);
}

void OddOrderMagicSquare(int size, int arr[][size])
{
    int square = size*size;
    int i = 0, j = size/2, k;
    
    for(k = 1; k <= square; ++k)
    {
        arr[i][j] = k;
        i--;
        j++;
        
        if(k%size == 0)
        {
            i = i+2;
            --j;
        }
        else
        {
            if(j == size)
                j = j - size;
            else if(i < 0)
                i = i + size;
        }
    }
}

void DoublyEvenMagicSquare(int size, int arr[][size])
{
    int I[size][size];
    int J[size][size];
    
    int i, j;
    
    int index = 1;
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            I[i][j] = ((i+1)%4)/2;
            J[j][i] = ((i+1)%4)/2;
            arr[i][j] = index;
            index++;
        }
    }
        
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            if(I[i][j] == J[i][j])
                arr[i][j] = size*size - arr[i][j] + 1;
        }
    }
}

void SinglyEvenMagicSquare(int size, int arr[][size])
{
    int N = size;
    int halfN = N/2;
    int k = (N-2)/4;
    
    int temp;
    
    int swapCol[N];
    int index = 0;
    int miniMagic[halfN][halfN];
    
    OddOrderMagicSquare(halfN, miniMagic);
    
    for(int i = 0; i < halfN; i++)
        for(int j = 0; j < halfN; j++)
        {
            arr[i][j] = miniMagic[i][j]; //A
            arr[i+halfN][j+halfN] = miniMagic[i][j] + halfN*halfN; //B
            arr[i][j+halfN] = miniMagic[i][j] + 2*halfN*halfN; //C
            arr[i+halfN][j] = miniMagic[i][j] + 3*halfN*halfN; //D
        }
        
    for(int i = 1; i <= k; i++)
        swapCol[index++] = i;
    
    for(int i = N-k+2; i <= N; i++)
        swapCol[index++] = i;
    
    for(int i = 1; i <= halfN; i++)
        for(int j = 1; j <= index; j++)
        {
            temp = arr[i-1][swapCol[j-1]-1];
            arr[i-1][swapCol[j-1]-1] = arr[i+halfN-1][swapCol[j-1] - 1];
            arr[i+halfN-1][swapCol[j-1]-1] = temp;
        }
        
    temp = arr[k][0];
    arr[k][0] = arr[k+halfN][0];
    arr[k+halfN][0] = temp;
    
    temp = arr[k+halfN][k];
    arr[k+halfN][k] = arr[k][k];
    arr[k][k] = temp;
}

void displayMagicSquare(int size, int arr[][size])
{
    printf("Magic number:%d\n", size*(size*size + 1)/2);
    
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
            printf("%5d  ", arr[i][j]);
        printf("\n");
    }
}
