#include <stdio.h>
#include <unistd.h>
#define N 3

int main() {
    pid_t pid;
    int array[N]={0};

    for(int i=0; i< N; i++){
        pid = fork();
        if(pid != 0){
            array[i]=0;
        } else if (pid == 0){
            array[i]=1;
        }
    }

    //print out binary values
    for(int i=0; i< N; i++){
        fprintf(stdout, "%d", array[i]);
    }
    fprintf(stdout, "\n");


    return 0;
}
