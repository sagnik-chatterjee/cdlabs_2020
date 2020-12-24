#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc , char **argv) {
	FILE* fa, fb;
	fa = fopen(argv[1], "r");
	fb = fopen(argv[2], "w+");

	int sizeofFile = 0;

	char buffer[1024];
	buffer[0] = '\n';
	char c = fgetc(fa);
	while (c != EOF) {
		strncat(buffer, &c, 1);
		c = fgetc(fa);
	}
	buffer[1024] = '\0';

	int sizeofFile = 0;
	c = fgetc(fa);
	//size
	sizeofFile = lseek(f, 0, SEEK_END) + 1;

	printf("%d", sizeofFile);
	for (int i = 1024; i >= 0; i--) {
		fputc(buffer[i], fb);
	}
	fclose(fa);
	fclose(fb);
	return 0;
}