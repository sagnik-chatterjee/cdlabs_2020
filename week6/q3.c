

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int curr = 0;
char str[100];

void S();
void A();
void APrime();
void B();

void valid() {
	printf("------VALID-----\n");
	exit(0);
}

void invalid() {
	printf("------INVALID-----\n");
	exit(0);
}


void S() {
	if (str[curr] == 'a') {
		curr++;
		A();
		if (str[curr] == 'c') {
			curr++;
			B();
			if (str[curr] == 'e') {
				curr++;
				return ;
			}
			else{
			invalid();
		}
	  }
	  else{
	  	invalid();	
	  }
	} 

	else {
	 	invalid();
	}
}

void APrime(){
	if(str[curr]=='b'){
		curr++;
		APrime();
		return ;
	}
}

void A() {
	if (str[curr] == 'b') {
		curr++;
		APrime();
	}
	else{
		invalid();
	}
}

void B(){
	if(str[curr]=='d'){
		curr++;
		return ;
	}
}
int main() {
	printf("Enter the string \n");
	scanf("%s", str);
	S();
	if (str[curr] == '$')
		valid();
	else invalid();
	return 0;
}