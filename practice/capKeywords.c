#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **keywords = {
	"auto", "break", "case", "const", "continue",
	"default", "do", "char"
	, "double", "else", "for", "int"
};//done only for a subset

char *delimiters = " .,;:!-()\n\t";


int isKeywWord(char *word) {
	for (int i = 0; i < 32; i++) {
		if (strcmp(word, keywords[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

void printUpperCase(char *str) {
	int l = strlen(str);
	char z;
	for (int i = 0; i < l; i++) {
		z = str[i];
		printf("Upper Version:- %c"toupper(z));
	}
	print("\n");
}

int main(int argc , char **argv) {

	FILE *fa = fopen(argv[1], "r");

	char c = getc(fa);
	char buffer[1024];


	char buffer[1024];
	while (fgets(buffer, 1024, fd1) > 0) {
		//temp copy of string
		char *cp = (char*)malloc(1024 * sizeof(char));
		strcpy(cp, buffer);

		char *token = (char*)malloc(256 * sizeof(char));

		do {//strsep :- extract the token from string,returns null if token not found
			token = strsep(&cp, delimiters);
			if (token != NULL)
			{
				if (isKeyword(token)) {
					printUpperCase(token);
				}
			}
		} while (token != NULL);
	}
	fclose(fa);
	return 0;
}