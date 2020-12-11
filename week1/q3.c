/*
AUTHOR :SAGNIK CHATTERJEE 
DATE : DEC 8,2020 
USAGE: ./q3 file1 file2 file3 

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc ,char **argv){
    if(argc<3){
        printf("[ERROR] Format if ./q3 inpfile1 inpfile2 resfile \n");
        exit(0);
    }
    FILE *fd1, *fd2, *fd3;

    char buffer1[1024],ch,buffer2[1024];

    fd1=fopen(argv[1],"r");
    fd2=fopen(argv[2],"r");
    fd3=fopen(argv[3],"w");

    if(fd1==NULL){
        printf("[ERROR] Could not read from the first input file.\n");
        exit(0);
    }
    if(fd2==NULL){
        printf("[ERROR] Could not read from the second input file.\n");
        exit(0);
    }
    if(fd3==NULL){
        printf("[ERROR] Could not read from the output file.\n");
        exit(0);
    }

    //addding the characters to the buffer
    buffer1[1023]='\n';
    buffer2[1023]='\n'; 
    for(ch = getc(fd1); ch != EOF ;ch = getc(fd1)){
     strncat(buffer1,&ch,1);   
    }

    for(ch = getc(fd2); ch != EOF ;ch = getc(fd2)){
     strncat(buffer2,&ch,1);   
    }

    for(int i=0;i<1024;i++){
        fputc(buffer1[i],fd3);
        fputc(buffer2[i],fd3);
    }


    printf("Contents copied to %s",argv[3]);
    fclose(fd1);
    fclose(fd2);
    fclose(fd3);
    return 0;

}