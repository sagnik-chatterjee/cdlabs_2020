#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc , char **argv) {

	FILE* f = fopen(argv[1], "r");
	char c;
	c = fgetc(f);
	int noofLines = 0;
	int noofchars = 0;

	while (c != EOF) {
		if (c == '\n') {
			noofLines += 1;
		}
		else if (isalpha(c)) {
			noofchars += 1;
		}
		c = fgetc(f);
	}
	printf("Lines :- %d", noofLines);
	printf("Cahrs :- %d", noofchars);
	fclose(f);
	return 0;
}