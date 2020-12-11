#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void T() {
	T();
	S();
}

void S() {

}


void invalid() {
	printf("------ ERROR-------\n");
	exit(1);
}

void valid() {
	printf("--------SUCCESS------\n");
	exit(0);
}

int main(int argc, char **argv) {

}