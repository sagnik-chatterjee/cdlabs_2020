//things to be done: 
// 1. create a structure of token weach time and return which has the row number 
//col number and he token type 
// 2. Tokens to be identified : 
//arithmatic operators 
//realtional opeartors
//logical operators
// special symbols 
//keywords 
//numerical constants 
//string literals 
//identifiers 

//3. also ignore all the tokes when encountered inside a single or multiline commnet 
//or inside string literal 

//4. preprocesser directive should also be stripped 
/*
Author : SAGNIK CHATTERJEE 
DATE :DEC 9,2020 
USAGE: ./q1 file1.c 
where file1.c is an input c file 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum ttx {
	TOKEN_TYPE_ID,
	TOKEN_TYPE_KEYWORD,
	TOKEN_TYPE_NUM,
	TOKEN_TYPE_OP,
	TOKEN_TYPE_SPECIAL,
	TOKEN_TYPE_NULL
} token_type;


typedef struct tokenx {
	token_type type;
	char value[16];
	ste_t entry;
}token_t;




const char *keywords[32] = { 
    "auto","double","int","struct","break","else","long", 
    "switch","case","enum","register","typedef","char", 
    "extern","return","union","continue","for","signed", 
    "void","do","if","static","while","default", 
    "goto","sizeof","volatile","const","float","short", 
    "unsigned" 
}; 


bool isKeyword(char value[16]){
	for(int i=0;i<32;i++){
		if(strcmp(value,keywords[i])==0){
			return true;
		}
	}
	return false;
}

bool isDigit (char ch) {
	return (ch >= '0' && ch <= '9');
}

bool isNumerical (char ch) {
	return (isDigit(ch) || ch == '.' || ch == 'e' || ch == 'E');
}

bool isAlphabet (char ch) {
	return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));
}

bool isValidID (char ch) {
	return (isDigit(ch) || isAlphabet(ch) || ch == '_');
}

const char *SPECIAL_SYMBOLS = "[]{}(),;:.#";

bool isSpecialSymbol (char ch) {
	return (strchr(SPECIAL_SYMBOLS, ch) != NULL);
}

const char *OPERATORS = "+-*/%<>=!&|^~";

bool isOperator (char ch) {
	return (strchr(OPERATORS, ch) != NULL);
	//strchr returns a poiner to the first occurence of character ch 
}

int main(int argc ,char **argv){
	FILE *fd ;

	fd=fopen(argv[1],"r");

	if(fd==NULL){
		printf("[ERROR] Some error reading from the input file.\n ");
		exit(0);
	}

	//this removes the preprocessers from the file 
	char buffer[1024],c;
	char *line=NULL;
    size_t len=0;
    ssize_t read;
    
    buffer[1023]='\n';
    
    while((read =getline(&line,&len,fa))!=-1){
        if(strstr(line,"#define")!=NULL || strstr(line,"#include")!=NULL){
        continue;
        }
        else{
            strcat(buffer,line);
        }
    }



	/*
	while(c!=EOF){
		int i=0;
		buffer[0]='\0';
		if(c=='='){

		}

	}
	*/
} 
