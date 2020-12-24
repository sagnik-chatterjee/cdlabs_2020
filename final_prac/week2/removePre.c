#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc , char **argv) {

	FILE *fa = fopen(argv[1], "r");
	FILE *fb = fopen(argv[2], "w");



	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	while (getline(&line, &len, fa) != -1) {
		if (strstr(line, "#define") != NULL || strstr(line, "#include") != NULL) {
			continue;//skip this line
		}
		else {
			//write to fb
			fputs(line, fb);
		}
	}
	printf("DOne");
	fclose(fa);
	fclose(fb);
}