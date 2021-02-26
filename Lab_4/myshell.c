#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<time.h>

char lastsearched[10][128] = {"---", "---", "---", "---", "---", "---", "---", "---", "---", "---"};

void Parser(char * buff, char **args);
void RemoveNextLine(char *buff);
void get_pwd(char *buff);
void record(char *cmd);
void showrecord(int n);

int main()
{
    while(1)
    {
        char buff[256];
        char *args[50];
        char current_path[256];
        int status = 0;
        pid_t wpid;
        
        get_pwd(current_path);
        printf("\n[TKarthikeyan@iiitdm]:%s$", current_path);
        fgets(buff, sizeof(buff), stdin);
        Parser(buff, args);
        record(buff);
        if(strcmp(args[0], "exit()") == 0)
        {
            printf("Thanks for using my shell\n");
            exit(0);
        }
        else if(strcmp(args[0], "cd") == 0)
            chdir(args[1]);
        else if(args[0][0] == '!')
            showrecord(args[0][1]-48);
        else if(fork() == 0)
        {
            if(execvp(args[0], args) < 0)
                printf("exec failed\n");
            exit(0);
        }
        else
            while((wpid = wait(&status)) > 0);
    }
    return 0;
}

void get_pwd(char *buff)
{
    int fd[2];
    pipe(fd);
    if(fork() == 0)
    {
        close(fd[0]);
        dup2(fd[1], 1);
        execlp("pwd", "pwd", NULL);
    }
    else
    {
        close(fd[1]);
        read(fd[0], buff, 256);
        close(fd[0]);
        RemoveNextLine(buff);
    }
}

void Parser(char *buff, char **args)
{
    int i = 0;
    RemoveNextLine(buff);
    char *token = strtok(buff, " ");
    args[i] = token;
    i++;
    
    while(1)
    {
        token = strtok(NULL, " ");
        if(token == NULL)
            break;
        args[i] = token;
        i++;
    }
    args[i] = (char *)NULL;
}

void RemoveNextLine(char *buff)
{
    int i = 0;
    while(buff[i] != '\n')
        i++;
    buff[i] = '\0';
}    

void record(char *cmd)
{
    for(int i = 8; i >= 0; i--)
        strcpy(lastsearched[i+1], lastsearched[i]);
    strcpy(lastsearched[0], cmd);
}

void showrecord(int n)
{
    if(n > 10)
    {
        printf("Sorry only last 10 can be retrieved\n");
        n = 10;
    }
    for(int i = 0; i < n; i++)
        printf("%s\n", lastsearched[i]);
}
    
