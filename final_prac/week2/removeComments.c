#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc , char **argv) {

	FILE *fa = fopen(argv[1], "r");
	FILE *fb = fopen(argv[2], "w");
	char ca = fgetc(fa);
	char cb;

	while (ca != EOF) {
		if (ca == '/') {
			cb = fgetc(fa);
			if (cb == '/') {
				while (ca != '\n')
					ca = fgetc(fa);
			}
			else if (cb == '*') {
				do {
					while (ca != '*')
						ca = fgetc(fa);
					ca = fgetc(fa);
				} while (ca != '/');
			}
			else {
				putc(ca, fb);
				putc(cb, fb);
			}
		}
		else  putc(ca, fb);
		ca = fgetc(fa);

	}
	fclose(fa);
	return 0;
}