#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const char* keywords = {"continue", "int", "float", "while", "for"
                        , "volatile", "do", "return", "void"
                       };//small sample

bool isKeyword(char *str) {
	for (int i = 0; i < sizeof(keywords); i++) {
		if (strncmp(str, keywords[i]) == 0) {
			return true;
		}
	}
	return false;
}

char * toUpper(char *str) {
	char *result;
	for (int i = 0; i < sizeof(str); i++) {
		strncat(result, toupper(str[i]))
	}
	return result;
}


int main(int argc , char **argv) {
	FILE *fa = fopen(argv[1], "r");
	//FILE *fb = fopen(argv[2], "w");


	char buffer[1024];
	char temp[1024];

	char ca = fgetc(fa);
	char cb;

	while (ca != EOF) {
		if (isalpha(ca)) {
			cb = fgetc(ca);
			while (cb != ' ') {
				strncat(buffer, &cb, 1);
			}
			buffer[1024] = '\0';
			if (isKeyword(buffer) == true) {
				printf(" STIRNG :- %s", toUpper(buffer));
			}
		}
		ca = fgetc(ca);
	}

	fclose(fa);
	return 0;

}