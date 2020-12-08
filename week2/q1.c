#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//todo
int main(int argc ,char **argv){
    FILE *fd ;
    char buffer[1024],ch ;

    //argv[1] is the name of the input file passed
    fd=fopen(argv[1],"w");

    if(fd==NULL){
        printf("Cannot open file for reading \n");
        exit(0);
    }

    ch= getc(fd);
    while(ch!=EOF){
        if(ca=='    ')
    }

}