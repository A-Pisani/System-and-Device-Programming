#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pthread.h"
#include "semaphore.h"

sem_t *sa, *sb;
int n;
static void *TA(void *);
static void *TB(void *);

int main(int argc, char **argv)
{
    if(argc!=2){
        fprintf(stderr, "Error in the command line\n");
        exit(EXIT_FAILURE);
    }
    int num_threads, i;
    int * pi;
    pthread_t th;
    num_threads=atoi(argv[1]);
    sa = (sem_t*)malloc(sizeof(sem_t));
    sb = (sem_t*)malloc(sizeof(sem_t));
    sem_init(sa,0,1);
    sem_init(sb,0,0);
    setbuf(stdout,0);
    for(i=0;i<2*num_threads;i++){
        pi=(int*)malloc(sizeof(int)); *pi=i;
        pthread_create(&th, NULL, TB, pi);
    }
    for(i=0;i<num_threads;i++){
        pi=(int*)malloc(sizeof(int)); *pi=i;
        pthread_create(&th, NULL, TA, pi);
    }
    pthread_exit(0);
    return 0;
}

static void *TA(void *arg){
    int *pi=(int *)arg;
    int id = *pi;
    pthread_detach(pthread_self());
    sleep(1);
    sem_wait(sa);
    printf("A%d ", id);
    n++;
    sem_post(sb);
    return 0;
}

static void *TB(void *arg){
    int *pi=(int *)arg;
    int id = *pi;
    pthread_detach(pthread_self());
    sleep(1);
    sem_wait(sb);
    n++;
    printf("B%d ", id);
    if(n>=3){
        printf("\n");
        n=0;
        sem_post(sa);
    }else{
        sem_post(sb);
    }
    return 0;
}