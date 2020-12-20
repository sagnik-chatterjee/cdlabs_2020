//program to count the number of lines and characters ina file

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int main(int argc , char **argv) {
	FILE *fa;
	if (argc != 2) {
		printf("Usasge : %s <inputfile>", argv[0]);
		exit(1);
	}
	fa = fopen(argv[1], "r");
	if (fa < 0) {
		printf("Could not open the file for reading \n");
		exit(1);
	}
	char buffer[100];
	printf("The number of characters and the number of lines in file are : \n");
	char ca = fgetc(fa);
	int charcounter = 0;
	int linecount = 0;
	while (ca != EOF) {
		if (isalnum(ca)) {
			charcounter += 1;
		}
		else if (ca == '\n') {
			linecount += 1;
		}
		ca = fgetc(fa);
	}
	printf("%d\n", charcounter);
	printf("%d\n", linecount);
	return 0;
}