#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

int main(int argc , char **argv) {
	FILE * fa = fopen(argv[1], "r");
	char c;
	fseek(fa, -1, SEEK_END);
	for (int i = ftell(fa); i >= 0; --i) {
		fseek(fa, i, SEEK_SET);
		c = fgetc(fa);
		putchar(c);
	}
	fclose(fa);

	return 0;

}