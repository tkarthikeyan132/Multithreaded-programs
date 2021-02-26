#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>

int main()
{
    char *str = malloc(sizeof(char)*(1000));
    int slen;

    printf("Enter the string :");
    fgets(str, 1000, stdin);
    slen = strlen(str);
    slen--;


    printf("String is :%s", str);
    printf("String length is %d\n", slen);

    _Bool arr[127] = {0}; // to indicate whether particular character exists or not
    int NUM_PROCESS = 0;

    for(int i = 0; i < slen; i++)
    {
        if(arr[str[i]] == 0)
        {
            arr[str[i]] = 1;
            NUM_PROCESS++;
        }
    }

    printf("NUM_PROCESS : %d\n", NUM_PROCESS);

    int brr[127] = {-1}; // store the newly  assigned index
    for(int i = 0; i < 127; i++)
        brr[i] = -1;

    char trr[NUM_PROCESS]; // index to char mapping

    int index = 0;
    
    for(int i = 0; i < slen; i++)
    {
        if(brr[str[i]] == -1)
        {
            brr[str[i]] = index;
            trr[index] = str[i];
            index++;
        }
    }

    int *frr = malloc(sizeof(int)*NUM_PROCESS);
    for(int i = 0; i < NUM_PROCESS; i++)
        frr[i] = 0;

    

    // process

    for(int i = 0; i < NUM_PROCESS; i++)
    {
        if(vfork() == 0)
        {
            for(int j = 0; j < slen; j++)
            {
                if(str[j] == trr[i])
                    frr[brr[trr[i]]]++;
            }
            exit(0);
        }
    }

    for(int i = 0; i < NUM_PROCESS; i++)
    wait(NULL);

    for(int i = 0; i < NUM_PROCESS; i++)
        printf("%c : %d\n", trr[i], frr[i]);

    return 0;
}
