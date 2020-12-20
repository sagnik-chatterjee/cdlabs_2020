#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void S();
void L();
void LPrime();

void invalid() {
	printf("ERROR");
	exit(0);
}

void valid() {
	printf("ERROR");
	exit(0);
}

int curr = 0;
char str[100];

void S() {
	if (str[curr] == '(') {
		curr++;
		L();
		if (str[curr] == ')') {
			curr++;
			return;
		}
		else {
			invalid();
		}
	} else if (str[curr] == 'a') {
		curr++;
		return;
	}
	else {
		invalid();
	}
}
void L() {
	S();
	LPrime();
}
void LPrime() {
	if (str[curr] == ',') {
		curr++;
		S();
		LPrime();
		return ;
	}
}

int main() {
	printf("Enter string to parse using rdp\n");
	scanf("%s", str);
	S();
	if (str[curr] == '$') {
		valid();
	}
	else {
		invalid();
	}
}