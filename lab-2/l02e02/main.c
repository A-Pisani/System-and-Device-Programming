#include <stdio.h>
#include "stdlib.h"
#include <time.h>
#include <math.h>
#include "pthread.h"
#include <unistd.h>
#include "semaphore.h"

#define LOWER 1
#define UPPER 9

typedef struct td_s{
    pthread_t tID;
    int id;
    int n;
    int *m;
    int tmpSum;
    int *arr;
}td_t;

pthread_barrier_t *b1, *b2;

void generateRandoms(int lower, int upper, int *array, double n);
void *threadFunction(void *);

int main(int argc, char **argv) {
    setbuf(stdout, 0);
    srand(time(0));
    // Receives an integer value n as argument of the command line
    if(argc!=2){
        fprintf(stderr, "Wrong number of arguments! Run as: %s array_length\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    double n = atoi(argv[1]);
    int m = (int) pow((double) 2,n);
    //Randomly generates an array v of 2^n integer elements in the range [1-9]
    int *array;
    array = (int *)malloc(m* sizeof(int));
    if(array == NULL){
        fprintf(stderr, "Error in array memory allocation\n");
        exit(EXIT_FAILURE);
    }
    generateRandoms(LOWER, UPPER, array, m);
    //Printing randomly generated array
    for (int i = 0; i < m; i++)
        fprintf(stdout, "v[%d]=%d ",i, array[i]);
    fprintf(stdout, "\n\n");
    td_t *thread;
    thread = (td_t *) malloc((m-1)* sizeof(td_t));
    if(thread==NULL){
        fprintf(stderr, "Error in threads memory allocation\n");
        exit(EXIT_FAILURE);
    }
    b1 = (pthread_barrier_t *)malloc(n* sizeof(pthread_barrier_t));
    b2 = (pthread_barrier_t *)malloc(n* sizeof(pthread_barrier_t));

    int k=m;
    for (int i = 0; i < n; ++i) {
        pthread_barrier_init(&b1[i], NULL, --k);
        pthread_barrier_init(&b2[i], NULL, k);
    }


    int l=m;
    for (int i = 0; i < (m-1); ++i) {
        thread[i].id = i + 1;
        thread[i].n = n;
        thread[i].m = &m;
        thread[i].tmpSum = array[i+1];    //initialize to 0 for a simpler re-initialization...
        thread[i].arr = array;      //added
        pthread_create(&thread[i].tID, NULL, threadFunction, (void *) &thread[i]);
    }

    fprintf(stdout, "MAIN THREAD -> v[%d]=%d\n", 0, array[0]);
    for (int i = 0; i < (l-1); ++i) {   //added
        //printf("waiting thread %d\n", thread[i].id);
        //sleep(2);
        pthread_join(thread[i].tID, NULL);
        //printf("received thread %d\n", thread[i].id);
        fprintf(stdout, "MAIN THREAD -> v[%d]=%d\n", thread[i].id, thread[i].arr[i+1]);
    }
    //sleep(10);


    return 0;
}

void generateRandoms(int lower, int upper, int *array, double n){
    for (int i = 0; i < n; i++)
        array[i] = (rand() %  (upper - lower + 1)) + lower;
}
void *threadFunction(void *arg){
    td_t *th = (td_t *) arg;
    //fprintf(stdout, "Hi! I am Thread %d\n", th->id);
    int tmp1, tmp2;
    for(int i=0; i< th->n; i++){
        //fprintf(stdout, "\n");
        if(th->id-(int)pow(2,i)>=0)
            th->tmpSum += th->arr[th->id-(int)pow(2,i)];
        //first barrier
        //printf("T%d waiting on first barrier \n",th->id);
        pthread_barrier_wait(&b1[i]);
        //printf("first barrier overcome\n");
        // begin CS
        th->arr[th->id] = th->tmpSum;
        // end CS

        //second barrier
        pthread_barrier_wait(&b2[i]);
        //printf("2nd barrier overcome\n");
        //fprintf(stdout, "T%d -> v[%d]=%d\n", th->id, th->id, th->arr[th->id]);
        if(th->id == (i + 1)){
            pthread_exit(NULL);
        }

    }
    //th->tmpSum = th->arr[th->id -1] + th->arr[th->id];
return (void *)0;
}