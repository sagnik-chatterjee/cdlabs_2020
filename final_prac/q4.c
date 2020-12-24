#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc , char **argv) {

	FILE *fa = fopen(argv[1], "r");

	int newlines = 0;
	int semicols = 0;
	int blankspaces = 0;

	char ca = fgetc(fa);
	char cb;
	while (ca != EOF) {
		if (ca == '\n') {
			newlines++;
		}
		else if (ca == ' ') {
			blankspaces++;
		}
		else if (ca == ';') {
			semicols++;
		}

	}
	printf("Total Number of blankspaces :%d", blankspaces);
	printf("Total Number of newlines :%d", newlines);
	printf("Total Number of semicols :%d", semicols);

	fclose(fa);
	return 0;
}