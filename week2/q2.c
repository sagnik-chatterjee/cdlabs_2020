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

    buffer[1023]='\n';
    //to remove the garbage values     

    for(ch= getc(fa);ch!=EOF;ch=getc(fa)){
        //traverse thorugh the fa and then write to fb
        if(ch =='#'){
            //since preprocesseros start with # in their stmt , this will mean 
            //fscanf(fa,"%*[^\n]");//jumps to the next line 
            //ref:  https://stackoverflow.com/questions/16107976/skip-a-line-while-reading-a-file-in-c
            fgets(ignore,sizeof(ignore),fa);
        }
        else {
            strncat(buffer,&ch,1);//store the other characters in buffer 
        }
    }

    buffer[1023]='\0'; //to remove the grbae values at the end of the string 

    for(int i=0;i<1024;i++){
        fputc(buffer[i],fb);
    }

    printf("Contents copied to %s",argv[2]);
    fclose(fa);
    fclose(fb);
    return 0;
}