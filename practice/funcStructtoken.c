#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct token {
	char token_name[100];
	int row, col;
	int index;
	char type[100];
} token;

void printToken(struct token s) {
	printf("<%s %d %d>", s.token_name, s.row, s.col);
	return 0;
}

bool isFunction(char *str) {

}

bool isStruct(char *str) {
//chck for struct keyword
}

bool hasReturnType(char *str) {
	if (strcmp(str, "bool") == 0 || strcmp(str, "void") == 0 || strcmp(str, "int") == 0
	        strcmp(str, "double") == 0 || strcmp(str, "float") == 0 ) {
		//other cases likelong long ,short int etc will also come
		return true;
	}
	return false;
}

bool hasDelimiter(char ch) {
	if (ch == '(' || ch == ')' || )
	}

int main(int argc , char **argv) {

}