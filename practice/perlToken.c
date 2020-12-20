#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>


bool isRealNumber(char *str) {
	int l = strlen(str);
	bool hasDecimal = false;
	for (int i = 0; i < l; i++) {
		if (str[i] == '0' || str[i] == '1' || str[i] == '2' || str[i] == '3' || str[i] == '4' || str[i] == '5'
		        || str[i] == '6' || str[i] == '7' || str[i] == '8' || str[i] == '9' ||
		        str[i] == '.' || (str[i] == '-' && i = 0) ) {
			return true;
			hasDecimal = true;
		}
	}
	return hasDecimal;
}

bool isInteger(char *str) {
	int l = strlen(str);
	for (int i = 0; i < l; i++) {
		if (str[i] == '0' || str[i] == '1' || str[i] == '2' || str[i] == '3' || str[i] == '4' || str[i] == '5'
		        || str[i] == '6' || str[i] == '7' || str[i] == '8' || str[i] == '9') {
			return true;
		}
	}
	return false;
}


void removeCOmmnets(FILE *fa) {
	//commnets in perl start with # and are single line
}
int main(int argc , char **argv) {

	FILE *fa = fopen(argv[1], "r");

}