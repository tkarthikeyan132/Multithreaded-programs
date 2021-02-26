#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<pthread.h>
#include<semaphore.h>

#define DINING_CAPACITY 5

int eating = 0;
int readyToLeave = 0;

sem_t mutex, okToLeave;

void *dine(void *param);

int main()
{
    pthread_t tid[DINING_CAPACITY];

    sem_init(&mutex, 0, 1);
    sem_init(&okToLeave, 0, 0);

    int tempid[DINING_CAPACITY];
    for(int i = 0; i < DINING_CAPACITY; i++)
        tempid[i] = i + 1;

    for(int i = 0; i < DINING_CAPACITY; i++)
        pthread_create(&tid[i], NULL, dine, &tempid[i]);

    for(int i = 0; i < DINING_CAPACITY; i++)
        pthread_join(tid[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&okToLeave);

    return 0;
}

void *dine(void *param)
{
    int *f = param;
    printf("Diner %d entered the dining hall\n", *f);

    sem_wait(&mutex);
    eating++;
    printf("Diner %d is eating\n", *f);
    if(eating == 2 && readyToLeave == 1)
    {
        sem_post(&okToLeave);
        readyToLeave--;
    }
    sem_post(&mutex);
    sleep(5);

    sem_wait(&mutex);
    eating--;
    readyToLeave++;
    printf("Diner %d is ready to leave\n", *f);

    if(eating == 1 && readyToLeave == 1)
    {
        sem_post(&mutex);
        sem_wait(&okToLeave);
    }
    else if(eating == 0 && readyToLeave == 2)
    {
        sem_post(&okToLeave);
        readyToLeave-=2;
        sem_post(&mutex);
    }
    else
    {
        readyToLeave--;
        sem_post(&mutex);
    }
    
    printf("Diner %d has left the hall\n", *f);
}