#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<pthread.h>
#include<time.h>
#include<string.h>

#define DICT_LIM 20
int NUM_WORDS = 0; //number of words in dictionary
struct word
{
    char word[25];
    char meaning1[100];
    char meaning2[100];
};
struct word W[DICT_LIM];

//0:Producer
//1:Consumer
//flag[i] = true implies P'i wants to enter critical section
bool flag[2] = {false, false};
//turn = i implies P'i turn
int turn = -1; 

void *producer(void *param)
{
    do
    {
        flag[0] = true;
        turn = 1;

        //being humble towards consumer
        while(flag[1] && turn == 1);

        //critical section begins
        if(NUM_WORDS == DICT_LIM)
            printf("Dictionary is full\n");
        else
        {
            char w[25];
            char mean1[100];
            char mean2[100];
            printf("<producer>\n");
            printf("Enter the word : ");
            gets(w);
            printf("Enter the meaning 1 : ");
            gets(mean1);
            printf("Enter the meaning 2 : ");
            gets(mean2);
            strcpy(W[NUM_WORDS].word, w);
            strcpy(W[NUM_WORDS].meaning1, mean1);
            strcpy(W[NUM_WORDS].meaning2, mean2);
            NUM_WORDS++;
        }
        //critical section ends 

        flag[0] = false;

    } while (true);
    
    pthread_exit(0);
}

void *consumer(void *param)
{
    do
    {
        flag[1] = true;
        turn = 0;

        //being humble towards producer
        while(flag[0] && turn == 0);

        //critical section begins
        if(NUM_WORDS == 0)
            printf("Dictionary is empty\n");
        else
        {
            char w[25];
            int flag = -1;
            printf("<consumer>\n");
            printf("Enter the word to be searched : ");
            gets(w);
            for(int i = 0; i < NUM_WORDS; i++)
            {
                if(strcmp(w,W[i].word) == 0)
                {
                    printf("primary meaning : %s\n", W[i].meaning1);
                    printf("secondary meaning : %s\n", W[i].meaning2);
                    flag = 0;
                    break;
                }
            }
            if(flag)
                printf("Requested word not found\n");
        }
        //critical section ends
        flag[1] = false;

    } while (true);

    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    pthread_t pid, cid;
    pthread_attr_t attr1, attr2;

    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);
    
    pthread_create(&pid, &attr1, producer, NULL);
    pthread_create(&cid, &attr2, consumer, NULL);

    pthread_join(pid, NULL);
    pthread_join(cid, NULL);

    return 0;
}