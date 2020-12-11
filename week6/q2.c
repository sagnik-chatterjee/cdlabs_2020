#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int curr = 0;
char str[100];

void invalid() {
	printf("------ERROR-----\n");
	exit(0);
}

void valid() {
	printf("------SUCCESS-----\n");
	exit(0);
}

void S() {
	U();
	V();
	W();
}

void U() {
	if (str[curr] == '(') {
		curr++;
		S();
		if (str[curr] == ')') {
			curr++;
			return ;
		}
	}
	else if (str[curr] == 'a') {
		S();
		str[curr++] = 'b';
	}
	else {
		str[curr++] = 'd';
	}
}


void V() {
	if (str[curr] == 'a') {
		V();
	}
}


void W() {
	if (str[curr] == 'c') {
		W();
	}
}

int main() {
	printf("Enter string\n");
	scanf("%s", str);
	S();
	if (str[curr] == '$')
		valid();
	else {
		printf("%c\n", str[curr]);
		invalid();
	}
}