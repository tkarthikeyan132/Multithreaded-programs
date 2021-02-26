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

struct block
{
    char word_to_be_searched[25];
    int beg;
    int end;
    int flag;
};

struct block_check
{
    char word_to_be_searched[25];
    int beg;
    int end;
    int flag;
};

void *search(void *param)
{
    struct block *b = param;
    for(int i = b->beg; i <= (b->end); i++)
    {
        if(strcmp(b->word_to_be_searched,W[i].word) == 0)
        {
            printf("primary meaning : %s\n", W[i].meaning1);
            printf("secondary meaning : %s\n", W[i].meaning2);
            b->flag = 0;
            break;
        }
    }
}

void *search_check(void *param)
{
    struct block_check *b = param;
    for(int i = b->beg; i <= (b->end); i++)
    {
        if(strcmp(b->word_to_be_searched,W[i].word) == 0)
        {
            printf("Word already exists in the dictionary\n");
            printf("primary meaning : %s\n", W[i].meaning1);
            printf("secondary meaning : %s\n", W[i].meaning2);
            b->flag = 0;
            break;
        }
    }
}

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

            pthread_t aid, bid;
            pthread_attr_t attra, attrb;
            pthread_attr_init(&attra);
            pthread_attr_init(&attrb);

            int mid = NUM_WORDS/2;
            struct block_check x, y;
            strcpy(x.word_to_be_searched, w);
            strcpy(y.word_to_be_searched, w);
            x.beg = 0;
            x.end = mid - 1;
            y.beg = mid;
            y.end = NUM_WORDS - 1;
            x.flag = 1;
            y.flag = 1;

            pthread_create(&aid, &attra, search_check, &x);
            pthread_create(&bid, &attrb, search_check, &y);

            pthread_join(aid, NULL);
            pthread_join(bid, NULL);

            if(x.flag && y.flag)
            {
                printf("Enter the meaning 1 : ");
                gets(mean1);
                printf("Enter the meaning 2 : ");
                gets(mean2);
                strcpy(W[NUM_WORDS].word, w);
                strcpy(W[NUM_WORDS].meaning1, mean1);
                strcpy(W[NUM_WORDS].meaning2, mean2);
                NUM_WORDS++;
            }
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
            
            printf("<consumer>\n");
            printf("Enter the word to be searched : ");
            gets(w);
            
            pthread_t pid, qid;
            pthread_attr_t attrp, attrq;
            pthread_attr_init(&attrp);
            pthread_attr_init(&attrq);
            
            int mid = NUM_WORDS/2;
            struct block p, c;
            strcpy(p.word_to_be_searched, w);
            strcpy(c.word_to_be_searched, w);
            p.beg = 0;
            p.end = mid;
            c.beg = mid + 1;
            c.end = NUM_WORDS - 1;
            p.flag = 1;
            c.flag = 1;

            pthread_create(&pid, &attrp, search, &p);
            pthread_create(&qid, &attrq, search, &c);

            pthread_join(pid, NULL);
            pthread_join(qid, NULL);

            if(p.flag && c.flag)
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