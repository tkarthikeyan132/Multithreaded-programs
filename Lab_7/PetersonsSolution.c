#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<pthread.h>
#include<time.h>

#define BS 5
int in = 0;
int out = 0;
int buffer[BS];

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
        int next_produced_item;
        flag[0] = true;
        turn = 1;

        //being humble towards consumer
        while(flag[1] && turn == 1);

        //critical section begins
        next_produced_item = rand()%1000;
        while((in+1)%BS == out); //do nothing as buffer is full
        buffer[in] = next_produced_item;
        in = (in+1)%BS;
        printf("<producer> Produced Item : %d\n", next_produced_item);
        printf("<producer> Buffer : %d %d %d %d %d      in : %d     out : %d\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], in, out); //why not for loop? To make the operation atomic
        printf("\n");
        sleep(1);
        //critical section ends 

        flag[0] = false;

    } while (true);
    
    pthread_exit(0);
}

void *consumer(void *param)
{
    do
    {
        int next_consumed_item;
        flag[1] = true;
        turn = 0;

        //being humble towards producer
        while(flag[0] && turn == 0);

        //critical section begins
        while(in == out); //do nothing as buffer is empty
        next_consumed_item = buffer[out];
        out = (out+1)%BS;
        printf("<consumer> Consumed Item : %d\n", next_consumed_item);
        printf("<consumer> Buffer : %d %d %d %d %d      in : %d     out : %d\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], in, out); //why not for loop? To make the operation atomic
        printf("\n");
        sleep(3);
        //critical section ends
        flag[1] = false;

    } while (true);

    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    srand(time(0)); 

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