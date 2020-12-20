#include <stdio.h>
#include <stdlib.h>

void E();
void EPrime();

void match(char t) {
	char l;
	if (l == t) {
		l = getchar();
	}
	else {
		printf("Error");
	}
}

void E() {
	char l;
	if (l == 'i') {
		match('i');
		EPrime();
	}

}

void EPrime() {
	char l;
	if (l == '+') {
		match('+');
		match('i');
		EPrime();
	}
	else {
		return ;
	}
}

int main() {

	E();
	char l;
	if (l == '$') {
		printf("Successfully parsed\n");
	}
	else {
		printf("Parsing unsuccessful\n");
	}
}