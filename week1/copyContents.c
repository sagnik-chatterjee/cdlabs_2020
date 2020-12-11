//program to copy the contents of source file to a destination file 

#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *fd1,*fd2;
    char filename[100];
    char c;
    printf("Enter the filename to open for reading : \n");
    scanf("%s",filename);

    fd1 = fopen(filename,"r"); //open file for reading 
    if(fd1==NULL){
        printf("Can't open the file for reading %s\n",filename);
        exit(0);
    }

    printf("Enter the filename to open for writing : \n");
    scanf("%s",filename);

    fd2= fopen(filename,"w");
    c=fgetc(fd1);//read the contents from fd1 character by character 

    while(c!=EOF){
        fputc(c,fd2);
        c=fgetc(fd1);
    }
    printf("COntents copied to %s",filename);

    fclose(fd1);
    fclose(fd2);
    return 0;

}