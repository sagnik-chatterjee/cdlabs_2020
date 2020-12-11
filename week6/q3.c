/*
After removing left recursion
S: a A c B e
A: b C
C: b C
B: d

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int curr = 0;
char str[100];

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
				valid();
			}
			invalid();
		} invalid();
	} invalid();
}

void A() {
	if (str[curr] == 'b') {
		C();

	}

}

void C() {
	if (str[curr] == 'b') {
		C();
	}
}


void B() {
	if (str[curr] == 'b') {
		valid();

	}
	else {
		invalid();
	}
}


int main() {
	printf("Enter the string \n");
	scanf("%s", &str);
	S();
	if (str[curr] == '$')
		valid();
	else invalid();
	return 0;
}