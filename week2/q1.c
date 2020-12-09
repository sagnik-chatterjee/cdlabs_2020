#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//todo
int main(int argc ,char **argv){
    FILE *fd ;
    char buffer[1024],c ;

    //argv[1] is the name of the input file passed
    fd=fopen(argv[1],"w");

    if(fd==NULL){
        printf("Cannot open file for reading \n");
        exit(0);
    }


    while( (c =getchar()) !=EOF){
        if(c =='\r')continue;//escape character for carriage return in the text 
        if(c =='\n'){
            //also for new lines and carraige return handling 
            putchar(c);
            while((c=getchar())=='\n' || c=='\r'){}
            if(c!=EOF) {
                //ungetc(c,stdin)
            }else {
                break};
        }

    }   

}