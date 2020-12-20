#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc , char **argv) {
	FILE *fa = fopen(argv[1], "r");

	char c;
	char buffer[1024];

	int totalLines = 0;
	int endSems = 0;
	int blanckSpaces = 0;

	for (c = fgetc(fa); c != EOF; c = fgetc(fa)) {
		if (c == '\n') {
			totalLines += 1;
		}
		else if (c == ';') {
			endSems++;
		}
		else if (c == ' ') {
			blanckSpaces += 1;
		}
	}
	printf("Total Lines : %d", totalLines);
	printf("Total Commas : %d", endSems);
	printf("Total Blank spaces : %d", blanckSpaces);
	return 0;
}

