#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    if(argc < 2)
        printf("Insufficient number of arguments\n");
    int status;
    status = remove(argv[1]);
    if(status == 0)
        printf("%s deleted successfully\n",argv[1]);
    else
        printf("File could not be deleted\n");
    return 0;
}
