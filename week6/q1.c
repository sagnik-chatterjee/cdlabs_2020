#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int curr=0;
char str[100];
void S();
void T();
void TPrime();

void invalid() {
	printf("------ ERROR-------\n");
	exit(1);
}

void valid() {
	printf("--------SUCCESS------\n");
	exit(0);
}

void S() {
	if(str[curr]=='a'){
		curr++;
		return;
	}
	else if(str[curr]='>'){
		curr++;
		return;
	}
	else if(str[curr]=='('){
		curr++;	
		T();	
		if(str[curr]==')'){
			curr++;
			return ;
		}
		invalid();
	}
	else
	{
		invalid();
	}
}

void T() {
	S();
	TPrime();
}

void TPrime(){
	if(str[curr]==','){
		curr++;
		S(); 
	}
}


int main() {
	printf("Enter string \n");
	scanf("%s",str);
	S();
	if(str[curr]=='$'){
		valid();
	}
	else{
		invalid();
	}
}