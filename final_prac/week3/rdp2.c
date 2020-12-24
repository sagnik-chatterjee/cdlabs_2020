#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int curr = 0;
char str[128];

void valid() {
	printf("----successfully parsed ------\n");
	return 0;
}
void invalid() {
	printf("------parsing failed ------\n");
	return 0;
}


void S();
void U();
void V();
void W();

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
			return;
		}
		else {
			invalid();
		}
	}
	else if (str[curr] == 'a') {
		curr++;
		S();
		if (str[curr] == 'b') {
			curr++;
			return ;
		}
		else {
			invalid();
		}
	}
	else if (str[curr] == 'd') {
		curr++;
		return ;
	}
	else {
		invalid();
	}
}

void V() {
	if (str[curr] == 'a') {
		curr++;
		V();
	}
}

void W() {
	if (str[curr] == 'c') {
		curr++;
		W();
	}
}

int main() {
	printf("Enter the string to parse\n");
	scanf("%s", str);
	if (str[curr] == '$') {
		valid();
	}
	else {
		invalid();
	}
	return 0;
}