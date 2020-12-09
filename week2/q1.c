/*
AUTHOR: SAGNIK CHATTERJEE
DATE : 9 DEC,2020
USAGE: ./q1 file1 file2 
file1 is the input file 
file2 is the output file 

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc ,char **argv){
    FILE *fd , *fd1;
    char buffer[1024],ch ;

    //argv[1] is the name of the input file passed
    fd=fopen(argv[1],"r");

    if(fd==NULL){
        printf("Cannot open file for reading \n");
        exit(0);
    }
    //argv[2] is the name of the output file to which result is written 

    fd1=fopen(argv[2],"w");

    if(fd1==NULL){
        printf("[ERROR] Can't open file or writing \n");
        exit(0);
    }

    //dicard extra whitespace and tabs 
    do {
        ch=getc(fd);
        if(ch!=' '&& ch!='\n' && ch!='\r' && ch !='\t'){
            putc(ch,fd1);
        }
        else{
            putc(' ',fd1);
        }
    }while(ch!=EOF);
    printf("Wrote to the output file.\n");
    fclose(fd);
    fclose(fd1);

return 0;
}