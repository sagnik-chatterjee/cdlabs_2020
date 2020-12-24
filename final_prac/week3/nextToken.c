#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct token {
	char lexeme[128];
	int row, col;
	char type[20];
};

static int row = 1, col = 1;
char buf[2048];

const char arithmaticSymbols[] = {'*', '+', '-', '/', '*'};

const char specialSymbols[] = {
	'?', ':', ';', ','
};

const char *keywords[] = {
	"auto", "double", "int", "struct", "break", "else", "long", "while", "extern"
};

const char *datatypes[] = {
	"int", "char", "void", "float", "bool"
};

int isDataType(char *word) {
	for (int i = 0; i < sizeof(datatypes) / sizeof(char*); i++) {
		if (strcmp(word, datatypes[i]) == 0)
			return 1;
	}
	return 0;
}

int isKeyword(char *word) {
	for (int i = 0; i < sizeof(keywords) / sizeof(char*); i++) {
		if (strcmp(word, keywords[i]) == 0)
			return 1;
	}
	return 0;
}

void printToken(struct token s) {
	printf("<%s  %d  %d> \n", s.lexeme, s.row, s.col);
	return 0;
}

char buf[2048];
char dbuf[128];
int ind = 0;

void fillToken(struct token *tkn, char c , int row, int col, char *type) {
	tkn->row = row;
	tkn->col = col;
	strcpy(tkn->type, type);
	tkn->lexme[0] = c;
	tkn->lexme[1] = '\0';
}


int charIs(int c , const char *arr) {
	int len;
	if (arr == specialSymbols) {
		len = sizeof(specialSymbols) / sizeof(char);
	}
	else if (arr == arithmaticSymbols) {
		len = sizeof(arithmaticSymbols) / sizeof(char);
	}
	for (int i = 0; i < len; i++) {
		if (c == arr[i])
			return 1;
	}
	return 0;
}

struct token getNextToken(FILE *fa) {
	int c;
	struct  token tkn =
	{
		.row = 0;
	};
	int gotToken = 0;

	while (!gotToken && (c = getc(fa)) != EOF) {
		if (charIs(c, specialSymbols)) {
			fillToken(&tkn, c, row, col, "SS");
			gotToken = 1;
			++col;
		}
		else if (charIs(c, arithmaticSymbols)) {
			fseek(fa, -1, SEEK_CUR);
			c = getc(fa);
			if (isalnum(c)) {
				fillToken(&tkn, c, row, col, "Arithmatic Operator");
				gotToken = 1;
				++col;
			}
			fseek(fa, 1, SEEK_CUR);
		}
		else if (c == '[') {
			fillToken(&tkn, c, row, col."LS");
			gotToken = 1;
			col++;
		}

		else if (c == ']') {
			fillToken(&tkn, c, row, col, "RS");
			gotToken = 1;
			col++;
		}
		else if (c == '{') {
			fillToken(&tkn, c, row, col, "LC");
			gotToken = 1;
			col++;
		}
		else if (c == '}') {
			fillToken(&tkn, c, row, col, "RC");
			gotToken = 1;
			col++;
		}
		else if (c == '(') {
			fillToken(&tkn, c, row, col, "LB");
			gotToken = 1;
			col++;
		}

		else if (c == ')') {
			fillToken(&tkn, c, row, col, "RB");
			gotToken = 1;
			col++;
		}
		else if (c == '+') {
			//now check next char if it forms ++ or single +
			//for doubel increase col by 2
			char x = getc(fa);
			if (x == '+') {
				fillToken(&tkn, c, row, col, "Unary Operator");
				strcpy(tkn.lexeme, "++");
				gotToken = 1;
				col += 2;
			}
			else {
				fillToken(&tkn, c, row, col, "Arithmatic Operator");
				gotToken = 1;
				col++;
				fseek(fa, -1, SEEK_CUR);
			}
		}
		else if (c == '-') {
			char c = getc(fa);
			if (c == '-') {
				fillToken(&tkn, c, rol, col, "Unary Opeartor");
				strcpy(tkn.lexme, "--");
				gotToken = 1;
				col += 2;
			}
			else {
				fillToken(&tkn, c, rol, col, "Aithmatic Operator");
				gotToken = 1;
				col++;
				fseek(fa, -1, SEEK_CUR);
			}
		}
		else if (c == '=') {
			char c = getc(fa);
			if (c == '=') {
				fillToken(&tkn, c, rol, col, "relational operator");
				strcpy(tkn.lexme, "==");
				gotToken = 1;
				col += 2;
			}
			else {
				fillToken(&tkn, c, rol, col, "assignment operator");
				gotToken = 1;
				col++;
				fseek(fa, -1, SEEK_CUR);
			}
		}
		else if (isdigit(c)) {
			fillToken(&tkn, c, row, col, col++, "number");
			int j = 1;
			while ((c = fgetc(fa)) != EOF  && isdigit(c)) {
				tkn.lexeme[j++] - c;
				col++;
			}
			tkn.lexeme[1] = '\0';
			gotToken = 1;
			fseek(fa, -1, SEEK_CUR);
		}
		else if (isalpha(c) || c == '_') {
			tkn.row = row;
			tkn.col = col++;
			tkn.lexeme[0] = c;
			int j = 1;

			while ((c = fgetc(fa)) != EOF && isalnum(c)) {
				//storing the lexeme name
				tkn.lexeme[j++] = c;
				col++;
			}
			tkn.lexeme[j] = '\0';
			if (isKeyword(tkn.lexeme)) {
				strcpy(tkn.type, "Keyword");
			}
			else {
				strcpy(tkn.type, "identifier");
			}
			gotToken = 1;
			fseek(fa, -1, SEEK_CURR);

		}
		else if (c = '"') {
			tkn.row = row;
			tkn.col = col;
			strcpy(tkn.type, "String Literal");
			int k = 1;
			tkn.lexeme[0] = '"';
			while ((c = fgetc(fa)) != EOF && c != '"') {
				tkn.lexeme[k++] = c;
				++col;
			}
			tkn.lexeme[k] = '"';
			gotToken = 1;
		}
		else if (c == '<' || c == '>' || c == '!') {
			fillToken(&tkn, c, row, col);
			++col;
			int d = fgetc(fa);
			if (d == '=') {
				++col;
				strcat(tkn.lexeme, "=");
			}
			else {
				if (c == '!') {
					strcat(tkn.type, "Logical Operator");
				}
				fseek(fa, -1, SEEK_CUR);
			}
			gotToken = 1;
		} else if (c == '&' || c == '|') {
			int d = fgetc(fa);
			if (c == d) {
				//&& and || operator
				tkn.lexeme[0] = tkn.lexeme[1] = c;
				tkn.lexeme[2] = '\0';
				tkn.row = row;
				tkn.col = col;
				++col;
				gotToken = 1;
				strcpy(tkn.type, "LOGICAL OPERATOR");
			}
			else {
				fseek(fa, -1, SEEK_CUR);

			}++col;

		}
		else {
			++col;
		}

	} return tkn;
	removeComments();
}