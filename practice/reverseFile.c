#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc , char **argv) {
	if (argc != 3) {
		printf("ERROR : Usage  %s <inputfilename> <outputfilename>", argv[0]);
		exit(1);
	}
	FILE *fa = fopen(argv[1], "r");
	FILE *fb = fopen(argv[2], "w");

	char buffer[1024], c, d;

	buffer[0] = '\n';
	c = fgetc(fa);
	while (c != EOF) {
		strncat(buffer, &c, 1);
		c = fgetc(fa);
	}
	for (int i = 1023; i > 0; i--) {
		fputc(buffer[i], fb);
	}
	fclose(fb);
	fclose(fa);
	return 0;

}