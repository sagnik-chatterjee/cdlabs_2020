#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void removeComment(FILE *fa, FILE *fb) {
	char c;
	while (c != EOF) {
		if (c == '') {
			putc(c, fb);
			while (c == '') {
				c = getc(fa);
			}
		}
		if (c == '/') {
			cb = getc(fa);
			if (cb == '/') {
				while (c != '\n')
					c = getc(fa);
			}
			else if (cb == '*') {
				do {
					while (c != '*')
						c = getc(fa);
					c = getc(fa);
				} while (c != '/')
				}
			else {
				putc(c, fb);
				putc(cb, fb);
			}
		}
		else putc(c, fb);
		c = getc(fa);
	}

}


int main(int argc , char **argv) {
	if (argc != 2) {
		printf("ERROR Uasge : %s <filename>", argv[0]);
		exit(1);
	}

	FILE *fa = fopen(argv[1], "r");
	if (fa == NULL) {
		printf("Couldnt open file for reading \n");
		exit(1);
	}







	return 0;
}