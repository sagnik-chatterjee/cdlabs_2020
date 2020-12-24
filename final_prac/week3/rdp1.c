#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int curr = 0;
char str[128];


void S();
void T();
void TPrime();

void valid() {
	printf("----successfully parsed -----\n");
	return 0;
}
void invalid() {
	printf("------parsing failed-------\n");
	return 0;
}

void S() {
	if (str[curr] == 'a') {
		cur++;
		return ;
	}
	else if (str[curr] == '>') {
		curr++;
		return ;
	}
	else if (str[curr] == '(') {
		curr++;
		T();
		if (str[curr] == ')') {
			cur++;
		}
		else {
			invalid();
		}
	}
	else {
		invalid();
	}
}

void T() {
	S();
	TPrime();
}

void TPrime() {
	if (str[curr] == ',') {
		curr++;
		S();
		TPrime();
	}
}

int main() {
	printf("Enter the string\n");
	scanf("%s", str);
	S();
	if (str[curr] == '$') {
		valid();
	}
	else {
		invalid();
	}
	return 0;
}