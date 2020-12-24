#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct token {
	char lexeme[128];
	int row, col;
	char type[64];
};

char *arithmaticsymbols[] = {'+', '/', '*', '-', '^'};

char *specialsymbols = {'.'};

static int row = 1, col = 1;

void printToken(struct token s) {
	printf("<%s %d %d> ", s.lexeme, s.row, s.col);
	return ;
}

bool isInteger(char *word) {

}
