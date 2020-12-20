#include <stdio.h>
#include <stdlib.h>

/*
SOME comments over here
this shoule not get printed
*/

//this part also should not get printed


int main(int argc , char **argv) {
	FILE *fa , *fb ;
	if (argc != 3) {
		printf("Error : Usage %s <fileInput.c> <fileOutput.c>", argv[0]);
		exit(1);
	}

	fa = fopen(argv[1], "r");
	fb = fopen(argv[2], "w");

	char ca; char cb;
	ca = getc(fa);
	while (ca != EOF) {
		if (ca == ' ') {
			putc(ca, fb);
			while (ca == ' ') {
				ca = getc(fa);
			}
		}
		if (ca == '/') {
			cb = getc(fa);
			if (cb == '/') {
				while (ca != '\n') {
					ca = getc(fa);
				}
			}
			else if (cb == '*') {
				do {
					while (ca != '*') {
						ca = getc(fa);
					}
					ca = getc(fa);
				} while (ca != '/');
			}
			else {
				putc(ca, fb);
				putc(cb, fb);
			}
		}
		else putc(ca, fb);
		ca = getc(fa);
	}

	fclose(fa);
	fclose(fb);
	return 0;
}