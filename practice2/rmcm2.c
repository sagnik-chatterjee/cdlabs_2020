#include <stdio.h>
#include <stdlib.h>


int main(int argc , char **argv) {
	if (argc != 3) {
		printf("Error: Usage %s <inputfile1> <outputfile>", argv[0]);
		exit(1);
	}
	FILE *fa , *fb;
	fa = fopen(argv[1], "r");
	fb = fopen(argv[2], "w");
	if (fa < 0) {
		printf("COuld not open the file for reading\n");
		exit(1);
	}
	if (fb < 0) {
		printf("COuld not open the file for writing \n");
		exit(1);
	}

	char ca, cb;
	ca = getc(fa);
	while (ca != EOF) {
		if (ca == ' ') {
			putc(ca, fb);
			while (ca == ' ') {
				ca = getc(fa);
			}
		}
		if (ca == '-') {
			cb = getc(fa);
			if (cb == '-') {
				while (cb != '\n') {
					ca = getc(fa);
				}
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
	printf("Done.");
	return 0;
}

