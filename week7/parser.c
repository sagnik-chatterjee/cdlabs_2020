#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "foreigntoken.h"


struct token curr;
FILE *f1;
void invalid(){
	printf("error");
	exit(0);
}
void program()
{
	
	if(strcmp(curr.lexeme,"ain")==0){
		curr=getNextToken(f1);
		if(strcmp(curr.lexeme,"(")==0){
			curr=getNextToken(f1);
			if(strcmp(curr.lexeme,")")==0){
				curr=getNextToken(f1);
				if(strcmp(curr.lexeme,"{")==0){
					curr=getNextToken(f1);
					declarations();
					assign_stat();
					if(strcmp(curr.lexeme,"}")==0){
						return;
					}
					else {
					printf(" [ERROR] Missing } at row:%d and col:%d.\n\n",curr.row,curr.col);
					exit(0);
				}
			}
				else{
					printf(" [ERROR] Missing { at row:%d and col:%d.\n\n",curr.row,curr.col);
					exit(0);
				}
			}
			else{
					printf(" [ERROR] Missing ) at row:%d and col:%d.\n\n",curr.row,curr.col);
					exit(0);
				}
		}
		else{
					printf(" [ERROR] Missing ( at row:%d and col:%d.\n\n",curr.row,curr.col);
					exit(0);
			}
	}
	else {
					printf("[ERROR] Missing main function\n\n");
					exit(0);
				}
}

void declarations()
{
	
	if(isdtype(curr.lexeme)==0)
	{
		return;
	}
	data_type();
	identifier_list();
	if(strcmp(curr.lexeme,";")==0)
	{
		curr=getNextToken(f1);
		declarations();
	}
	else {
		printf(" [ERROR] Missing ; at row:%d and col:%d.\n\n",curr.row,curr.col);
		 exit(0);
		}


}

void data_type()
{
	if(strcmp(curr.lexeme,"int")==0)
	{
		curr=getNextToken(f1);
		return;
	}
	else if(strcmp(curr.lexeme,"char")==0)
	{
		curr=getNextToken(f1);
		return;
	}
	else 
				{
					printf("\nMissing data type at row:%d and col:%d.\n\n",curr.row,curr.col);
					exit(0);
				}
}

void identifier_list()
{
	if(strcmp(curr.type,"identifier")==0)
	{
		curr=getNextToken(f1);
		if(strcmp(curr.lexeme,",")==0)
		{
			curr=getNextToken(f1);
			identifier_list();
		}
		else return;
	}

	else 
		{
			printf("\nMissing identifier at row:%d and col:%d.\n\n",curr.row,curr.col);
			exit(0);
		}
}

void assign_stat(){
	if(strcmp(curr.type,"identifier")==0){
		curr=getNextToken(f1);
		if(strcmp(curr.lexeme,"=")==0){
			curr=getNextToken(f1);
			if(strcmp(curr.type,"identifier")==0){
				curr=getNextToken(f1);
				if(strcmp(curr.lexeme,";")==0){
					curr=getNextToken(f1);
					return;
				}
			}
		else if(strcmp(curr.type,"number")==0){
			curr=getNextToken(f1);
			if(strcmp(curr.lexeme,";")==0){
					curr=getNextToken(f1);
					return;
			}else{
			 printf("\nMissing ; at row:%d and col:%d.\n\n",curr.row,curr.col);
			 exit(0);
			}
		}
		else{
			printf("\nMissing identifier at row:%d and col:%d.\n\n",curr.row,curr.col);
			exit(0);
		}
	}else{
			printf("\nMissing = at row:%d and col:%d.\n\n",curr.row,curr.col);
			exit(0);
 		}
	}else{
			printf("\nMissing identifier at row:%d and col:%d.\n\n",curr.row,curr.col);
			exit(0);
		}
}

int main()
{
	FILE *fa, *fb;
	int ca, cb;
	
	fa = fopen("input.c", "r");
	if (fa == NULL){
		printf("Cannot open file \n");
		return 0; 
	}
	fb = fopen("fileout.c", "w");
	ca = getc(fa);
	while (ca != EOF){
		if(ca==' '){
			putc(ca,fb);
			while(ca==' ')
				ca = getc(fa);
		}if (ca=='/'){
			cb = getc(fa);
			if (cb == '/'){
				while(ca != '\n')
					ca = getc(fa);
			}
			else if (cb == '*'){
				do{
					while(ca != '*')
						ca = getc(fa);
					ca = getc(fa);
				}while (ca != '/');
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
	fa = fopen("fileout.c", "r");
	if(fa == NULL){
		printf("Cannot open file");
		return 0;
	}
	fb = fopen("temp.c", "w");
	ca = getc(fa);
	while(ca != EOF){
		if(ca == '#'){
			while(ca != '\n'){
				ca = getc(fa);
			}
		}
		ca = getc(fa);
		if(ca != EOF && ca != '#'){
			putc(ca, fb);
		}
	}
	fclose(fa);
	fclose(fb);
	
	fa = fopen("temp.c", "r");
	fb = fopen("fileout.c", "w");
	ca = getc(fa);
	while(ca != EOF){
		putc(ca, fb);
		ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);
	remove("temp.c");
	f1=fopen("fileout.c","r");
	if(f1==NULL)
	  {
	  	printf("Error! File cannot be opened!\n");
	  	return 0;
	  }
	struct token tkn;
	curr=getNextToken(f1);
	program();
	printf("\nCompiled\n\n");
    fclose(f1);
}
