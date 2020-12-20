#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc , char **argv) {
	FILE* fa;
	fa = fopen(argv[1], "r");
	if (fa == NULL) {
		printf("Could not read file \n");
		exit(1);
	}

	size_t len = 0;
	ssize_t read;
	char *line = NULL;

	int noOfChars = 0;
	int noOfLines = 0;


	char buffer[1024], c, d;
	c = fgetc(fa);
	while (c != EOF) {
		//printf("%c", c);//or fputc(c,filename);
		noOfChars += 1;
		c = fgetc(fa);
	}
	printf("No of chars:- %d", noOfChars);
	d = fgetc(fa);
	while ((read = getline(&line, &len, fa)) != -1) {
		printf("Retrived line of length %zu:\n", read);
		noOfLines += 1;
		printf("%s", line);
	}
	printf("No of lines:- %d", noOfLines);
	fclose(fa);
	return 0;
}