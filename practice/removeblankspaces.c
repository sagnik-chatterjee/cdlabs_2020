#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc , char **argv) {

	FILE *fa = fopen(argv[1], "r");
	FILE *fb = fopen("out1", "w");
	char buffer[1024], c;
	c = getc(fa); char b;
	while (c != EOF) {
		if (c == '\0') {
			while (c == '\0' || c == '\t' )
				putc('\0', fb);
		}
		else if (c == '\t') {
			while (c == '\0' || c == '\t')
				putc('\t', fb);
		}
		putc(c, fb);
		c = getc(fa);
	}
	fclose(fa);
	fclose(fb);
	return 0;
}