/*
AUTHOR : SAGNIK CHATTERJEE 
DATE : DEC 8,2020 
USAGE : 

*/
//removal of single and multiline comments 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc ,char **argv){
    FILE *fa, *fb;
    int ca,cb; 
    //argv[1 ] is the input c file 
    fa=open(argv[1],"r");
    if(fa==NULL){
        printf("Cannot open the file for reading .\n");
        exit(0);
    }
    //argv[2] is the output c file to which wew write 
    fb = fopen(argv[2], "w");
    ca = getc(fa);
    while (ca != EOF){
        if(ca==' ')
        {
            putc(ca,fb);
            while(ca==' ')
            ca = getc(fa);
        }
        if (ca=='/')
        {
            cb = getc(fa);
            if (cb == '/')
            {   
                while(ca != '\n')
                ca = getc(fa);
            }
            else if (cb == '*')
            {
                do
                {
                    while(ca != '*')
                    ca = getc(fa);
                    ca = getc(fa);
                } while (ca != '/');
            }
            else{
                putc(ca,fb);
                putc(cb,fb);
            }
        }
        else putc(ca,fb);
        ca = getc(fa);
        }
    fclose(fa);
    fclose(fb);
    return 0;
 }
