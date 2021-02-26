#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> //linux specific library for fork related calls
#include<time.h>
#include<sys/wait.h>
#include<errno.h>

int main(int argc, char *argv)
{
    int fd[2];
    int fd2[2];
    //fd[0] for read
    //fd[1] for write
    pipe(fd);
    pipe(fd2);

    int id = fork();
    if(id == -1)
    {
        printf("fork error\n");
        return 1;
    }
    else if(id > 0) // parent
    {
        char str[108] = "MalayalaM";
        char reverstr[108];
        int slen = strlen(str);
        close(fd[0]);
        write(fd[1], &slen, sizeof(slen));
        write(fd[1], str, strlen(str)*sizeof(char));
        close(fd[1]);
        printf("<inside parent>Sent string from parent = %s\n", str);

        close(fd2[1]);
        read(fd2[0], reverstr, slen*sizeof(char));
        close(fd2[0]);
        printf("<inside parent>Received string from child = %s\n", reverstr);

        printf("<inside parent>Pallindrome checking ...\n");
        if(strcmp(str,reverstr) == 0)
            printf("<inside parent>String is pallindrome\n");
        else
            printf("<inside parent>String is not a pallindrome\n");

        wait(NULL);
    }
    else // child
    {
        char rstr[108];
        char revstr[108];
        int rslen;
        close(fd[1]);
        read(fd[0], &rslen, sizeof(rslen));
        read(fd[0], rstr, rslen);
        close(fd[0]);
        
        printf("<inside child>String reversing ...\n");
        for(int k = rslen-1, j = 0; k >= 0; k--, j++)
            revstr[j] = rstr[k];

        close(fd2[0]);
        write(fd2[1], revstr, rslen*sizeof(char));
        close(fd2[1]);
    }

    return 0;
}