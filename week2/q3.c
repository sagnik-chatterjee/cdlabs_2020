/*
AUTHOR: SAGNIK CHATTERJEE 
DATE : DEC 9,2020
USAGE : ./q3 file1  
where file1 is the input c file 

prints the result to the console 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
//#include <stdbool.h>
#include <stddef.h>

const char *keywords[32] = {
	"auto","double","int","struct","break","else","long",
	"switch","case","enum","register","typedef","char",
	"extern","return","union","continue","for","signed",
	"void","do","if","static","while","default",
	"goto","sizeof","volatile","const","float","short",
	"unsigned"
};

const char delimiters[]=" .,;:!-()\n\t";

int isKeyword (char *word) {
	int i;
	for (i = 0; i < 32; ++i) {
		if (strcmp(word, keywords[i]) == 0) {
			return 1;
		}
	}
	return 0;
}


void printUpperCase (char *word) {
	int l = strlen(word);
	char z;
	int i;
	printf("Keywords are :\n");
	for (i = 0; i < l; ++i) {
		z = word[i];
		printf("%c", z > 96 ? z - 32 : z);
	}
	printf("\n");
}

int main(int argc ,char **argv){

	
	FILE *fd1;

	//argv[1] is the input c file we give
	fd1=fopen(argv[1],"r");

	if(fd1==NULL){
		printf("[ERROR] Can't open the file to read from. \n");
		exit(0);
	}	
	char buffer[1024];
	while(fgets(buffer,1024,fd1) >0){
		//temp copy of string 
		char *cp =(char*)malloc(1024*sizeof(char));
		strcpy(cp,buffer); 
	
		char *token=(char*)malloc(256*sizeof(char));
		
		do {//strsep :- extract the token from string,returns null if token not found 
			token =strsep(&cp,delimiters);
			if(token!=NULL)
			{
				if(isKeyword(token)){
					printUpperCase(token);
				}
			} 
		}while(token!=NULL);
	}

	fclose(fd1);	
	//while writing to file use toupper() to make it capital 
	//since toupper() runs on a char , run a loop or can use ascii style 
return 0;
}