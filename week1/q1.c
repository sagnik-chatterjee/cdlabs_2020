/*
AUTHOR: SAGNIK CHATTERJEE
DATE : DEC 8,2020
Usage : ./q1 (then follow the onscreen instrcutions)
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE* fd1;
    char buffer[100],ch;

    printf("Enter the name of the file to open\n");
    scanf("%s",buffer);

    fd1=fopen(buffer,"r");

    if(fd1==NULL){
        printf("Can't open the file for reading ,maybe not exists");
        exit(0);
    }

    //reading the files character by character 

    ch = fgetc(fd1);
    //count the number of characaters
    int charCount=0;
    while(ch!=EOF){
        charCount+=1;
        ch=fgetc(fd1);
    }
    //count the number fo lines 
    int lineCount=0;
    
    for(ch=getc(fd1);ch!=EOF;ch=getc(fd1)){
       if(ch=='\n'){
           lineCount+=1;
       } 
    }
    fclose(fd1);
    printf("The number of characters in the file are : %d\n",charCount);
    printf("The number of lines in the file are : %d\n",lineCount);
   
    return 0;
}