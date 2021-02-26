#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<time.h>

int main()
{
    int arr[3][3] = {1,2,3,4,5,6,7,8,9};
    int brr[3][3] = {1,1,1,1,1,1,1,1,1};
    int res[3][3] = {0,0,0,0,0,0,0,0,0};
    printf("Printing array A:\n");
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
            printf("%d ",arr[i][j]);
        printf("\n");
    }
    printf("Printing array B:\n");
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
            printf("%d ",brr[i][j]);
        printf("\n");
    }
    int fd1[2], fd2[2], fd3[2], fd4[2], fd5[2], fd6[2], fd7[2], fd8[2], fd9[2];
    pipe(fd1); pipe(fd2); pipe(fd3); pipe(fd4); pipe(fd5); pipe(fd6); pipe(fd7); pipe(fd8); pipe(fd9);
    int pid1 = fork();
    if(pid1 == 0) // 1st row 1st column
    {
        int temp = arr[0][0]*brr[0][0] + arr[0][1]*brr[1][0] + arr[0][2]*brr[2][0];
        
        close(fd1[0]);
        write(fd1[1], &temp, 4);
        close(fd1[1]);
    }
    else
    {
        int pid2 = fork();
        if(pid2 == 0) // 1st row 2nd column
        {
            int temp = arr[0][0]*brr[0][1] + arr[0][1]*brr[1][1] + arr[0][2]*brr[2][1];
            
            close(fd2[0]);
            write(fd2[1], &temp, 4);
            close(fd2[1]);
        }
        else
        {
            int pid3 = fork();
            if(pid3 == 0) // 1st row 3rd column
            {
                int temp = arr[0][0]*brr[0][2] + arr[0][1]*brr[1][2] + arr[0][2]*brr[2][2];
                
                close(fd3[0]);
                write(fd3[1], &temp, 4);
                close(fd3[1]);
            }
            else
            {
                int pid4 = fork();
                if(pid4 == 0) // 2nd row 1st column
                {
                    int temp = arr[1][0]*brr[0][0] + arr[1][1]*brr[1][0] + arr[1][2]*brr[2][0];
                    
                    close(fd4[0]);
                    write(fd4[1], &temp, 4);
                    close(fd4[1]);
                }
                else
                {
                    int pid5 = fork();
                    if(pid5 == 0) // 2nd row 2nd column
                    {
                        int temp = arr[1][0]*brr[0][1] + arr[1][1]*brr[1][1] + arr[1][2]*brr[2][1];
                        
                        close(fd5[0]);
                        write(fd5[1], &temp, 4);
                        close(fd5[1]);
                    }
                    else
                    {
                        int pid6 = fork();
                        if(pid6 == 0) // 2nd row 3rd column
                        {
                            int temp = arr[1][0]*brr[0][2] + arr[1][1]*brr[1][2] + arr[1][2]*brr[2][2];
                            
                            close(fd6[0]);
                            write(fd6[1], &temp, 4);
                            close(fd6[1]);
                        }
                        else
                        {
                            int pid7 = fork();
                            if(pid7 == 0) // 3rd row 1st column
                            {
                                int temp = arr[2][0]*brr[0][0] + arr[2][1]*brr[1][0] + arr[2][2]*brr[2][0];
                                
                                close(fd7[0]);
                                write(fd7[1], &temp, 4);
                                close(fd7[1]);
                            }
                            else
                            {
                                int pid8 = fork();
                                if(pid8 == 0) // 3rd row 2nd column
                                {
                                    int temp = arr[2][0]*brr[0][1] + arr[2][1]*brr[1][1] + arr[2][2]*brr[2][1];
                                    
                                    close(fd8[0]);
                                    write(fd8[1], &temp, 4);
                                    close(fd8[1]);
                                }
                                else
                                {
                                    int pid9 = fork();
                                    if(pid9 == 0) // 3rd row 3rd column
                                    {
                                        int temp = arr[2][0]*brr[0][2] + arr[2][1]*brr[1][2] + arr[2][2]*brr[2][2];
                                        
                                        close(fd9[0]);
                                        write(fd9[1], &temp, 4);
                                        close(fd9[1]);
                                    }
                                    else
                                    {
                                        close(fd1[1]);
                                        read(fd1[0], &res[0][0], 4);
                                        close(fd1[0]);
                                        
                                        close(fd2[1]);
                                        read(fd2[0], &res[0][1], 4);
                                        close(fd2[0]);
                                        
                                        close(fd3[1]);
                                        read(fd3[0], &res[0][2], 4);
                                        close(fd3[0]);
                                        
                                        close(fd4[1]);
                                        read(fd4[0], &res[1][0], 4);
                                        close(fd4[0]);
                                        
                                        close(fd5[1]);
                                        read(fd5[0], &res[1][1], 4);
                                        close(fd5[0]);
                                        
                                        close(fd6[1]);
                                        read(fd6[0], &res[1][2], 4);
                                        close(fd6[0]);
                                        
                                        close(fd7[1]);
                                        read(fd7[0], &res[2][0], 4);
                                        close(fd7[0]);
                                        
                                        close(fd8[1]);
                                        read(fd8[0], &res[2][1], 4);
                                        close(fd8[0]);
                                        
                                        close(fd9[1]);
                                        read(fd9[0], &res[2][2], 4);
                                        close(fd9[0]);
                                        
                                        printf("\nPrinting result array:");
                                        for(int i = 0; i < 3; i++)
                                        {
                                            printf("\n");
                                            for(int j = 0; j < 3; j++)
                                                printf("%d ",res[i][j]);
                                        }
                                        printf("\n");
                        
                                    }//9
                                }//8
                            }//7
                        }//6
                    }//5
                }//4
            }//3
        }//2
    }//1
    return 0;
}
