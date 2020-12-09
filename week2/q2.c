/*
AUTHOR :SAGNIK CHATTERJEE 
DATE :dec9,2020
Usage : ./q2 file1  file2 

file1 is the input C file 
file2 is the result file 

Here input taken from file1check.c and written to file2 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char **argv){
    FILE *fa, *fb;
    //argv[1] is the input file for reading 

    char ch;
    fa=fopen(argv[1],"r");
    fb=fopen(argv[2],"w");
    if(fa==NULL){
        printf("[ERROR] Couldnt the open for reading .\n");
        exit(0);
    }
    if(fb==NULL){
        printf("[ERROR] Couldn't open the file for writing.\n");
        exit(0);
    }
    char buffer[1024];//the buffer from whcih we will write to fd
    char ignore[1024];//we would read the line but will write to this ignore array 

    char *line=NULL;
    size_t len=0;
    ssize_t read;
    buffer[1023]='\n';
    while((read =getline(&line,&len,fa))!=-1){
        if(strstr(line,"#define")!=NULL || strstr(line,"#include")!=NULL){
        continue;
        }
        else{
            fputs(line,fb);
        }
    }
      

    printf("Contents copied to %s",argv[2]);
    fclose(fa);
    fclose(fb);
    return 0;
}