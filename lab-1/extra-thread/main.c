#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <zconf.h>

typedef struct threadData{
    pthread_t threadID;
    int ID;
    int line;
    int sum;
    FILE *fp;
}threadD;

static void *threadFunction(void *);
sem_t *sem;

int main(int argc, char **argv ) {
    if(argc!=3){
        fprintf(stderr,"Wrong number of parameters! Run as: [%s] [int] [in_file]\n", argv[0]);
        return EXIT_FAILURE;
    }

    threadD *td;
    FILE *fp;
    void *retval;
    int nT = atoi(argv[1]);
    fp = fopen(argv[2], "r");
    td = (threadD *)malloc(nT* sizeof(threadD));
    sem = (sem_t *)malloc(sizeof(sem_t));
    if (fp == NULL || td == NULL) {
        printf("Error! opening file 1");
        exit(1);
    }

    sem_init(sem, 0, 1);     //0 -> not_shared; 1 -> init_value

    for(int i=0; i<nT; i++){
        td[i].fp=fp;
        td[i].ID=i;
        td[i].line = td[i].sum = 0;
        pthread_create(&td[i].threadID, NULL, threadFunction, (void *) &td[i]);
    }
    int total =0,  line = 0;

    for(int i=0; i<nT; i++){
        pthread_join(td[i].threadID, retval);
        line += td[i].line;
        total += td[i].sum;
    }
    fprintf(stdout, "Total: Sum= %d, #lines= %d\n", total, line);

    fclose(fp);
    sem_destroy(sem);
    return 0;
}

static void *threadFunction(void *param){
    int n, readval;
    threadD *td ;
    td = (threadD *) param;

    fprintf(stdout, "Thread %d enters in action \n", td->ID);

    do{
        sem_wait(sem);
            readval = fscanf(td->fp, "%d", &n);
        sem_post(sem);
        if(readval != EOF){
            td->sum+=n;
            td->line+=1;
        }
        sleep(1);
    }while(readval != EOF);

    fprintf(stdout, "Thread %d: Sum= %d, #lines= %d\n", td->ID, td->sum, td->line);

    pthread_exit((void *) 1) ;
}