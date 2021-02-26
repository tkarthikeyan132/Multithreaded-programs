#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<time.h>

int main()
{
    int n;
    printf("Enter the order of matrix:");
    scanf("%d",&n);
    int arr[n][n];
    printf("Enter the matrix in row-wise manner(space separated):");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d",&arr[i][j]);
    
    printf("Entered matrix:\n");
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            printf("%d  ",arr[i][j]);
        printf("\n");
    }
        
    int fd1[2], fd2[2], fd3[2];
    pipe(fd1);
    pipe(fd2);
    pipe(fd3);
    
    int pid1 = fork(); 
    if(pid1 == 0) // take care of row sum
    {
        int temp = 0;
        int rowsum[n];
        for(int i = 0; i < n; i++)
        {
            rowsum[i] = 0;
            for(int j = 0; j < n; j++)
                rowsum[i]+=arr[i][j];
        }
        for(int k = 0; k < n-1; k++)
        {
            if(rowsum[k]!=rowsum[k+1])
            {
                temp = -1;
                break;
            }
        }
        if(temp!=-1)
            temp = rowsum[0];
        printf("rowflag:%d\n",temp);
        
        close(fd1[0]);
        write(fd1[1], &temp, 4);
        close(fd1[1]);
    }
    else
    {
        int pid2 = fork();
        if(pid2 == 0) // take care of column sum
        {
            int temp = 0;
            int colsum[n];
            for(int i = 0; i < n; i++)
            {
                colsum[i] = 0;
                for(int j = 0; j < n; j++)
                    colsum[i]+=arr[j][i];
            }
            for(int k = 0; k < n-1; k++)
            {
                if(colsum[k]!=colsum[k+1])
                {
                    temp = -1;
                    break;
                }
            }
            if(temp!=-1)
                temp = colsum[0];
            printf("colflag:%d\n",temp);
            
            close(fd2[0]);
            write(fd2[1], &temp, 4);
            close(fd2[1]);
        }
        else
        {
            int pid3 = fork();
            if(pid3 == 0) // take care of diagonal sum
            {
                int temp = 0;
                int diagsum[2] = {0,0};
                for(int i = 0; i < n; i++)
                {
                    for(int j = 0; j < n; j++)
                    {
                        if(i==j)
                            diagsum[0]+=arr[i][j];
                        if(i+j == n-1)
                            diagsum[1]+=arr[i][j];
                    }
                }
                if(diagsum[0] == diagsum[1])
                    temp = diagsum[0];
                else
                    temp = -1;
                printf("diagflag:%d\n",temp);
                
                close(fd3[0]);
                write(fd3[1], &temp, 4);
                close(fd3[1]);
            }
            else // will integrate the separate results
            {
                int rowflag, colflag, diagflag;
                
                close(fd1[1]);
                read(fd1[0], &rowflag, 4);
                close(fd1[0]);
                
                close(fd2[1]);
                read(fd2[0], &colflag, 4);
                close(fd2[0]);
                
                close(fd3[1]);
                read(fd3[0], &diagflag, 4);
                close(fd3[0]);
                
                if(rowflag == -1 || colflag == -1 || diagflag == -1)
                    printf("Not a magic square\n");
                else
                {
                    if(rowflag == colflag && colflag == diagflag)
                        printf("It is a magic square\n");
                    else
                        printf("Not a magic square\n");
                } //4
            }//3
        }//2
    }//1
    return 0;
}
