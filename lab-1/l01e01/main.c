#include <stdio.h>
#include <stdlib.h>
#include "fcntl.h "

#define N 30
typedef struct student {
    int id, mark;
    long rNum;
    char sur[N+1], name[N+1];
}Student;

int main(int argc, char **argv) {
    if(argc!=4){
        fprintf(stderr,"Wrong number of parameters! Run as: %s file_input_1 file_output_1 file_output_2\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file1, *file3;
    int file2;
    Student s;      //temporary variable

    if ((file1 = fopen(argv[1], "r")) == NULL) {
        printf("Error! opening file 1");
        exit(1);
    }

    if ((file2 = open(argv[2], O_WRONLY, "w")) == -1) {
        printf("Error! opening file 2");
        exit(2);
    }
    
    while(fscanf(file1, "%d%ld%s%s%d", &s.id, &s.rNum, s.sur, s.name, &s.mark ) != EOF){
        if(write(file2, &s, sizeof(Student))==-1){
            fprintf(stderr,"Error in Write I/O\n");
            return 4;
        }
    }
    close(file2);
    fclose(file1);
    if ((file3 = fopen(argv[3], "w")) == NULL) {
        printf("Error! opening file 3");
        exit(3);
    }
    if ((file2 = open(argv[2], O_RDONLY, "r")) == -1) {
        printf("Error! opening file 2");
        exit(2);
    }

    while(read(file2, &s, sizeof(Student))!=0){
        fprintf(stdout, "%d %ld %s %s %d", s.id, s.rNum, s.sur, s.name, s.mark );
    }

    close(file2);
    fclose(file3);
    return 0;
}
