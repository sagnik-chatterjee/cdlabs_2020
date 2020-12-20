#include <stdio.h>
#include <stdlib.h>

int main(int argc , char **argv) {
	if (argc != 3) {
		fprintf("Error");
		exit(1);
	}
	FILE* fa = fopen(argv[1], "r");
	FILE* fb = fopen(argv[2], "w");

	fseek(fa, -1L, SEEK_END);
	while (fseek(fa, -1L, SEEK_CURR) != -1) {
		char c = getc(fa);
		putc(c, fb);
	}
	fclose(fa);
	fclose(fb);
	return 0;
}