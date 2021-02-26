#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    int id;
    id = fork();
    if(id > 0)
    {
        printf("Parent will sleep\n");
        sleep(10);
        printf("Me as a parent is alive\n");
    }
    if(id == 0)
    {
        printf("I am child\n");
        printf("Me as a child is dying\n");
        exit(0);
    }
    return 0;
}
