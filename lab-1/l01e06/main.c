#include <stdio.h>
#include <stdlib.h>
#include "semaphore.h"
#include "pthread.h"

#define BUFFER_SIZE 16

sem_t *full, *empty;
int buffer[BUFFER_SIZE];
int head = 0, tail = 0; //head, tail pointers initially pointing to zero

void enqueue(int );
void dequeue(int *);
void * Producer(void *);
void * Consumer(void *);

int main() {

    full = (sem_t *)malloc(sizeof(sem_t));
    empty = (sem_t *)malloc(sizeof(sem_t));
    if(full ==NULL || empty == NULL){
        fprintf(stderr, "Error in creation of semaphores\n");
        exit(EXIT_FAILURE);
    }
    sem_init(full, 0, 0);
    sem_init(empty, 0, BUFFER_SIZE);
    pthread_t producer, consumer;
    void *res;

    pthread_create(&producer, NULL, Producer, NULL);
    pthread_create(&consumer, NULL, Consumer, NULL);

    pthread_join(producer, res);
    pthread_join(producer, res);

    return 0;
}

void enqueue(int val){
    buffer[tail] = val;
    tail= (tail +1) % BUFFER_SIZE;
}
void dequeue(int *val){
    *val = buffer[head];
    head= (head +1) % BUFFER_SIZE;
}
void * Producer(void *arg){
    for(int i=0;i<1000;i++){
        sem_wait(empty);
            enqueue(i);
        sem_post(full);
    }
    sem_wait(empty);
        enqueue(-1);
    sem_post(full);
}
void * Consumer(void *arg){
    int var;
    FILE *fout;
    fout = fopen("out.txt", "w");
    while (var!=-1){
        sem_wait(full);
            dequeue(&var);
            if(var!=-1)
                fprintf(fout, "%d\n", var);
        sem_post(empty);
    }
}
