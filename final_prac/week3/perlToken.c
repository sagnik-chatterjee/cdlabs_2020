#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct token {
	char lexeme[128];
	int row , col;
	char type[64];
};

static int row = 1, col = 1;
char buffer[2048];
char dbuf[128];


const char *keywords[2] = {"scalar", "foreach"};
const char *specialsymbols[1] = {";"};
const char *arithmaticsymbols = {'+'};




void removeComment() {
	FILE *f1 = fopen("input.pl", "r");
	FILE *f2 = fopen("out1.pl", "w+");

	char ch ;
	char cb;
	ch = getc(f1);
	while (ch != EOF) {
		if (ch == '#') {
			cb = getc(f1);
			if (cb != '!') {
				//conitnue till the end of the while
				while (ch != '\n')ch = getc(f1);
			}
			else putc(cb, f2);
			else putc(ch, f2);
		} else putc(ch, f2);
		ch = getc(f1);
	}
	fclose(f1);
	fclose(f2);
}

void printToken() {
	printf("<%s %d %d>", token.lexeme, token.row, token.col);
	return 0;
}

void removePath() {
	FILE *f1 = fopen("out1.pl", "r");
	FILE *f2 = fopen("out2.pl", "w+");

	char ch , cb;
	ch = getc(f1);
	while (ch != EOF) {
		if (ch == '#') {
			cb = getc(f1);
			if (cb == '!') {
				while (ca != '\n')ca = getc(f1);
			} else {
				putc(ch, f2);
				putc(cb, f2);
			}
		} else putc(ch, f2);
		ch = getc(f1);
	}
	fclose(f1);
	fclose(f2);
}

bool isKeyword(char *str) {
	for (int i = 0; i < sizeof(keywords); i++) {
		if (strcmp(keywords[i], str) == 0) {
			return truel;
		}
	}
	return false;
}

void fillToken(struct token *s, char c , int row , int col, char *type) {
	s->lexeme[0] = c;
	s->lexeme[1] = '\0';
	s->row = row;
	s->col = col;
	strcpy(s->type, type);
}

int charIs(int c, char *arr) {
	int len ;
	if (arr == specialsymbols) {
		len = sizeof(specialsymbols) / sizeof(char);
	} else if (arr == arithmaticsymbols) {
		len = sizeof(arithmaticsymbols) / sizeof(char);
	}
	for (int i = 0; i < len; i++) {
		if (c == arr[i]) {
			return 1;
		}
	} return 0;
}

void newLine() {
	++row;
	col = 1;
}

struct getNextToken(FILE *fa) {
	int c;
	struct token tkn = {
		.row = -1;
	}
	c = getc(fa);
	int gotToken = 0;

	while (!gotToken && (c != EOF)) {
		if (charIs(c, specialsymbols) == 0) {
			fillToken(&tkn, c, row, col, "SS");
			gotToken = 1;
			++col;
		}
		else if (charIs(c, arithmaticsymbols) == 0) {
			fseek(fa, -1, SEEK_CUR);
			if (isalnum(c)) {
				fillToken(&tkn, c, row, col, "Arithamtic symbol");
				++col;
				gotToken = 1;

			}
			fseek(fa, 1, SEEK_CUR);

		}

		else if (c == '{') {
			fillToken(&tkn, c, row, col, "LB");
			col++;
			gotToken = 1;
		}
		else if (c == '}') {
			fillToken(&tkn, c, row, col, "RB");
			col++;
			gotToken = 1;
		}
		else if (c == '$') {
			char b = getc(fa);
			char buffer1[1024];

			//incomplete

		} else if (c == '+') {
			int b = getc(fa);
			if (b == '+') {
				fillToken(&tkn, c, row, col, "Unary Operator");
				gotToken = 1;
				col += 2;

			}
			else {
				fillToken(&tkn, c, row, col, "Arithamtic ");
				gotToken = 1;
				col += 1;
				fseek(fa, -1, SEEK_CUR);
			}
		}
		else if (c == "(") {
			char b = getc(fa);
			if (b == '@') {
				char d = getc(fa);
				if (d == '_') {
					fillToken(&tkn, c, row, col, "specailsymbol");
					gotToken = 1;
					col += 1;

				}
			}

		}
	}
}



int main() {

}