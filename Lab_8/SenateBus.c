#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<pthread.h>
#include<semaphore.h>

#define BUS_CAPACITY 10
#define NUM_BUSES 2
#define NUM_PASSENGERS 28

void *Bus(void *param);
void *rider(void *param);

int riders = 0; //number of riders waiting in the bus stop

sem_t mutex, multiplex, bus, allAboard;

int main()
{
    pthread_t pid[NUM_PASSENGERS];
    pthread_t bid[NUM_BUSES];

    sem_init(&mutex, 0, 1);
    sem_init(&multiplex, 0, BUS_CAPACITY);
    sem_init(&bus, 0, 0);
    sem_init(&allAboard, 0, 0);

    int temppid[NUM_PASSENGERS];
    for(int i = 0; i < NUM_PASSENGERS; i++)
        temppid[i] = i + 1;

    int tempbid[NUM_BUSES];
    for(int i = 0; i < NUM_BUSES; i++)
        tempbid[i] = i + 1;

    for(int i = 0; i < NUM_PASSENGERS; i++)
        pthread_create(&pid[i], NULL, rider, &temppid[i]);

    for(int i = 0; i < NUM_BUSES; i++)
        pthread_create(&bid[i], NULL, Bus, &tempbid[i]);

    for(int i = 0; i < NUM_PASSENGERS; i++)
        pthread_join(pid[i], NULL);

    for(int i = 0; i < NUM_BUSES; i++)
        pthread_join(bid[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&multiplex);
    sem_destroy(&bus);
    sem_destroy(&allAboard);

    return 0;
}

void *Bus(void *param)
{
    int *f = param;

    sem_wait(&mutex);
    if(riders > 0)
    {
        sem_post(&bus);
        sem_wait(&allAboard);
    }
    sem_post(&mutex);

    printf("Bus %d departed from the bus stop\n", *f);
}

void *rider(void *param)
{
    int *f = param;
    
    sem_wait(&multiplex);
        sem_wait(&mutex);
            riders+=1;
        sem_post(&mutex);

        sem_wait(&bus);
    sem_post(&multiplex);

    printf("rider %d is boarding the bus\n", *f);
    sleep(2);

    riders -= 1;
    if(riders == 0)
        sem_post(&allAboard);
    else 
        sem_post(&bus);

    printf("rider %d boarded the bus\n", *f);
}

