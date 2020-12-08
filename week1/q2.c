/*
AUTHOR : SAGNIK CHATTERJEE 
DATE: DEC 8 ,2020
USAGE : ./q2 file1 file2 
file1 is the inpuit file (from which it is read)
file2 is the output file (to which it will be written)
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc ,char **argv){
    FILE *fd1 ,*fd2;
    
    char buffer[1024],ch;
    //buffer is the intermedaite in which we store the 
    //char taken from the file and then address them reversely 

    //argv[1] is the name of the input file to read 
    //argv[2] is the name of the output file in which to write the reverse result 
    fd1=fopen(argv[1],"r");

    if(fd1==NULL){
        printf("[ERROR] File could not be opened for reading. \n");
        exit(0);
    }

    fd2=fopen(argv[2],"w");
    if(fd2==NULL){
        printf("[ERROR] File could not be opened for writing. \n");
        exit(0);
    }
    buffer[0]='\n';//for removing the garbage value before strncat 
    for(ch = getc(fd1); ch!=EOF ; ch=getc(fd1)){
        //read the file and store the result in buffer 
        strncat(buffer,&ch,1);//appending the character to the character 
    }
    //buffer[1023]='\0';
    //now writing th reverse of it into the fd2 
    for(int i=1023;i>=0;i--){
        fputc(buffer[i],fd2);
    }
    printf("Contents copied to %s",argv[1]);
    fclose(fd1);
    fclose(fd2);
    return 0;
}