                //  VERSION B
#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"

#define UPPER 0.5
#define LOWER -0.5

typedef struct th_s{
    pthread_t tid;
    int id;
    float *v1, *mati;
    float tmpRes;
    int size;
} th_t;

float *parziali;

void * tf(void *);
void printVectors(float *, float *, float **, int);

int main(int argc, char **argv) {

    if(argc!=2){
        fprintf(stderr, "Wrong number of parameters! Run as: [%s] [size_of_vec]", argv[0]);
        exit(EXIT_FAILURE);
    }

    //srand(time(0));

    int n = atoi(argv[1]);
    parziali = (float *)calloc(n*sizeof(float), 0.0);

    float final = 0.0;
    float *v1, *v2, **mat, *res;
    v1 = (float *)malloc(n*sizeof(float));
    v2 = (float *)malloc(n*sizeof(float));
    mat = (float **)malloc(n*sizeof(float *));
    res = (float *)calloc(n*sizeof(float), 0.0);

    th_t *t;
    t=(th_t *)malloc(n*sizeof(th_t));

    if(v1 == NULL || v2 == NULL || mat == NULL || res == NULL || t == NULL){
        fprintf(stderr, "Error in malloc");
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<n; i++){
        mat[i] = (float *)malloc(n*sizeof(float ));
        if(mat[i] == NULL){
            fprintf(stderr, "Error in malloc");
            exit(EXIT_FAILURE);
        }
        v1[i] =(double) rand()/RAND_MAX*(UPPER - LOWER) + LOWER;
        v2[i] =(double) rand()/RAND_MAX*(UPPER - LOWER) + LOWER;
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            mat[j][i] =(double) rand()/RAND_MAX*(UPPER - LOWER) + LOWER;
            //mat[i][j] =(double) rand()/RAND_MAX*1-0.5;    //sequential version in which mat is not transposed
    }

    printVectors(v1, v2, mat, n);

    for(int i=0;i<n;i++){
        t[i].v1 = v1;
        t[i].mati = mat[i];
        t[i].tmpRes = 0.0;
        t[i].size = n;
        t[i].id = i;
        pthread_create(&t[i].tid, NULL, tf, (void *) &t[i]);
    }


/*    for(int i=0;i<n;i++){         //sequential version, substituted by line 62
        for(int j=0;j<n;j++){
            res[i]+=v1[j]*mat[j][i];
        }
    }
*/


    for(int j=0;j<n;j++){
        //final+=res[j]*v2[j];
        pthread_join(t[j].tid, NULL);
        final += t[j].tmpRes*v2[j];
    }

    fprintf(stdout, "%f\n", final);

    return 0;
}

void *tf(void *arg){
    th_t *t;
    t = (th_t *) arg;
    //printf("thread %d \n", t->id);
    for(int i=0; i<t->size; i++){
        t->tmpRes += t->v1[i]*t->mati[i];

    }
    pthread_exit((void *)0);
}

void printVectors(float *v1, float *v2, float **mat, int n){
    fprintf(stdout, "v1: ");
    for(int i=0; i<n; i++){
        fprintf(stdout, "%f ", v1[i]);
    }
    printf(" \n");

    fprintf(stdout, "mat: \n");
    for(int i=0; i<n; i++){
        for(int j=0; j<n;j++)
            fprintf(stdout, "%f ", mat[j][i]);  //in the sequential version mat is not transposed
        fprintf(stdout, "\n");
    }

    fprintf(stdout, "v2: ");
    for(int i=0; i<n; i++){
        fprintf(stdout, "%f ", v2[i]);
    }
    fprintf(stdout, "\n");
}
/*      VERSION A
#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"

#define UPPER 0.5
#define LOWER -0.5

typedef struct th_s{
    pthread_t tid;
    int id;
    float *v1, *mati;
    float tmpRes;
    int size;
} th_t;

void * tf(void *);
void printVectors(float *, float *, float **, int);

int main(int argc, char **argv) {

    if(argc!=2){
        fprintf(stderr, "Wrong number of parameters! Run as: [%s] [size_of_vec]", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    float final = 0.0;
    float *v1, *v2, **mat, *res;
    v1 = (float *)malloc(n*sizeof(float));  v2 = (float *)malloc(n*sizeof(float));
    mat = (float **)malloc(n*sizeof(float *));
    res = (float *)calloc(n*sizeof(float), 0.0);

    th_t *t;
    t=(th_t *)malloc(n*sizeof(th_t));

    if(v1 == NULL || v2 == NULL || mat == NULL || res == NULL || t == NULL){
        fprintf(stderr, "Error in malloc");
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<n; i++){
        mat[i] = (float *)malloc(n*sizeof(float ));
        if(mat[i] == NULL){
            fprintf(stderr, "Error in malloc");
            exit(EXIT_FAILURE);
        }
        v1[i] =(double) rand()/RAND_MAX*(UPPER - LOWER) + LOWER;
        v2[i] =(double) rand()/RAND_MAX*(UPPER - LOWER) + LOWER;
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            mat[j][i] =(double) rand()/RAND_MAX*(UPPER - LOWER) + LOWER;
        //mat[i][j] =(double) rand()/RAND_MAX*1-0.5;    //sequential version in which mat is not transposed
    }

    printVectors(v1, v2, mat, n);

    for(int i=0;i<n;i++){
        t[i].v1 = v1;   t[i].mati = mat[i];
        t[i].tmpRes = 0.0;  t[i].size = n;  t[i].id = i;
        pthread_create(&t[i].tid, NULL, tf, (void *) &t[i]);
    }

*/
/*    for(int i=0;i<n;i++){         //sequential version, substituted by line 62
        for(int j=0;j<n;j++){
            res[i]+=v1[j]*mat[j][i];
        }
    }
*//*

    for(int j=0;j<n;j++){
        //final+=res[j]*v2[j];      //uncomment for sequential version
        pthread_join(t[j].tid, NULL);
        final += t[j].tmpRes*v2[j];
    }
    fprintf(stdout, "%f\n", final);

    return 0;
}

void *tf(void *arg){
    th_t *t;
    t = (th_t *) arg;
    //printf("thread %d \n", t->id);
    for(int i=0; i<t->size; i++){
        t->tmpRes += t->v1[i]*t->mati[i];
    }
    pthread_exit((void *)0);
}

void printVectors(float *v1, float *v2, float **mat, int n){
    fprintf(stdout, "v1: ");
    for(int i=0; i<n; i++){
        fprintf(stdout, "%f ", v1[i]);
    }
    printf(" \n");

    fprintf(stdout, "mat: \n");
    for(int i=0; i<n; i++){
        for(int j=0; j<n;j++)
            fprintf(stdout, "%f ", mat[j][i]);  //in the sequential version mat is not transposed
        fprintf(stdout, "\n");
    }

    fprintf(stdout, "v2: ");
    for(int i=0; i<n; i++){
        fprintf(stdout, "%f ", v2[i]);
    }
    fprintf(stdout, "\n");
}
*/

