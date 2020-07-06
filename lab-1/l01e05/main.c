#include <stdio.h>
#include <pthread.h>
#define N 2

void *recursive (void *);

int main() {

    long int array[N];
    pthread_t *t;
    for(int i=0;i<N;i++){
        pthread_create(t, NULL, recursive, (void *) &array);
    }
    return 0;
}

void *recursive (void *array){
    long int *path;
    path = (long int *) array;
}
