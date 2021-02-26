#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex, writeblock;

int data = 0, rcount = 0;

void *reader(void *arg);
void *writer(void *arg);

int main()
{
    int i, b;
    pthread_t rtid[3], wtid[3];

    sem_init(&mutex, 0, 1);
    sem_init(&writeblock, 0, 1);

    int twid[3] = {0,1,2};
    int trid[3] = {0,1,2};

    // for(int i = 0; i <= 2; i++)
    // {
        pthread_create(&wtid[0], NULL, writer, &twid[0]);
        pthread_create(&wtid[1], NULL, writer, &twid[1]);
        pthread_create(&wtid[2], NULL, writer, &twid[2]);
        pthread_create(&rtid[0], NULL, reader, &trid[0]);
        pthread_create(&rtid[1], NULL, reader, &trid[1]);
        pthread_create(&rtid[2], NULL, reader, &trid[2]);
        
    // }

    // for(int i = 0; i <= 2; i++)
    // {
        pthread_join(wtid[0], NULL);
        pthread_join(rtid[0], NULL);
        pthread_join(wtid[1], NULL);
        pthread_join(rtid[1], NULL);
        pthread_join(wtid[2], NULL);
        pthread_join(rtid[2], NULL);
    // }

    sem_destroy(&mutex);
    sem_destroy(&writeblock);

    return 0;
}

void *reader(void *arg)
{
    int *f;
    f = arg;

    sem_wait(&mutex);
    rcount = rcount + 1;

    if(rcount == 1) // first reader
        sem_wait(&writeblock);

    sem_post(&mutex);

    printf("Data read by the reader %d is %d\n", *f, data);

    sem_wait(&mutex);
    rcount = rcount - 1;

    if(rcount == 0) // last reader
        sem_post(&writeblock);

    sleep(3);
    
    sem_post(&mutex);
}

void *writer(void *arg)
{
    int *f;
    f = arg;

    sem_wait(&writeblock);

    data++;

    printf("Data written by the writer %d is %d\n", *f, data);
    sleep(3);

    sem_post(&writeblock);
}