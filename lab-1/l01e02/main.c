#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#define SIGUSR1 101
#define SIGUSR2 102

void manager (int sig);
int array [2] = {0};
int i=0;

int main() {
    printf("Hello, World!\n");
    signal(SIGUSR1, manager);
    signal(SIGUSR2, manager);
    while(1){}
    return 0;
}

void manager (int sig){
    if(i<2){
      array[i]=sig;
    }else {

        if(sig == SIGUSR1){
            if(array[0]==array[1]==SIGUSR1)
                return 0;
        }else if(sig == SIGUSR2){

        }
    }

    i++;
}