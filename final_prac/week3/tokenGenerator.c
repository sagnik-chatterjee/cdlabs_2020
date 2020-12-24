#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char key[32][10] = {"auto", "double", "int", "struct", "break", "else", "long",
                    "switch", "case", "enum", "register", "typedef", "char",
                    "extern", "return", "union", "const", "float", "short",
                    "unsigned", "continue", "for", "signed", "void", "default",
                    "goto", "sizeof", "voltile", "do", "if", "static", "while"
                   };

struct token {
	char token_name[100];
	int index;
	unsigned int row, col
	char type[100];
} token;

void print_token(struct token s) {
	printf("<%s , %d , %d>", s.token_name, s.row, s.col);
	return ;
}

bool isKeyword(char *word) {
	for (int i = 0; i < 32; i++) {
		if (strcmp(key[i], word) == 0) {
			return 1;
		}
	}

	return 0;
}

bool isDelimiter(char ch) {
	if (ch == '/' || ch == '+' || ch == '-' || ch == '*' || ch == ',' ||
	        ch == ';' || ch == '>' || ch == '<' || ch == '=' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}')
		return true;
	else
		return false;
}

bool isRealNumber(char *str) {

}

bool isInteger(char ch) {

}

void removeComments() {
	FILE *fa = fopen("input.c", "r");
	FILE *fb = fopen("out1.c", "w");

	char ca , cb;
	ca = getc(fa);
	while (ca != EOF) {
		if (ca == ' ') {
			putc(ca, fb);
			if (cb == ' ' || cb == '\t') ca = getc(fa);
		}
		else if (ca == '/') {
			cb = getc(ca);
			if (cb == '/') {
				//read till the end of the line
				while (ca != '\n') ca = getc(fa);
			}
			else if (cb == '*') {
				do {
					while (ca != '*')ca = getc(fa);
				} while (ca != '/');
			} else {
				putc(ca, fb);
				putc(cb, fb);
			}
		}
		else putc(ca, fb);
		ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);
}

void removeDirectives() {
	FILE *fa , *fb;
}