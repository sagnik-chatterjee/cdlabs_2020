#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct token {
	char lexeme[128];
	int row, col;
	char type[20];
};

void invalid() {
	printf("Error");
	return 0;
}

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

void newLine() {
	++row;
	col = 1;
}

void removeComments(FILE *fa) {
	fa = fopen("input.c", 'r');
	FILE *fb = fopen("out2.c", "w+");

	char ca = getc(fa);
	char cb;
	while (ca != EOF) {
		if (ca == '/') {
			cb = getc(fa);
			if (cb == '/') {
				while (ca != '\n') {
					ca = getc(fa);
				}
			}
			else if (cb == '*') {
				do {
					while (ca != '*')
						ca = getc(fa);
					ca = getc(fa);

				} while (ca != '/');
			}
			else {
				putc(ca, fb);
				putc(cb, fb);
			}
		}
		else putc(ca, fb);
		ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);

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
				tkn.lexeme[j++] = c;
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
		else if (c == '/') {
			char d = fgetc(fa);
			++col;
			if (d == '/') {
				while ((c = fgetc(fa)) != EOF && c != '\n') {
					col++;
				}
			}
			else if (d == '*') {
				do {
					if (d = '\n') {
						newLine();
					}
					while ((c = getc(fa)) != EOF && c != '*') {
						++col;
						if (c == '\n') {
							newLine();
						}
					}
					++col;
				} while ((d = fgetc(fa)) != EOF && d != '/' && (++col));
				++col;
			} else {
				fillToken(&tkn, c, row, --col, "arithmatic operator");
				gotToken = 1;
				fseek(fa, -1, SEEK_CUR);
			}
		}
	}
	return tkn;

}

struct sttable {
	int sno;
	char lexeme[128];
	char dtype[64];
	char type[64];
	int size;
};

struct sttable fillTable(int sno, char *lexem, char*dt, char *type, int size) {
	struct sttable tab;
	tab.sno = sno;
	strcpy(tab.lexeme, lexeme);
	strcpy(tab.dt, dt);
	strcpy(tab.type, type);
	tab.size = s;
	return tab;
}

void printTable(struct sttable *tab, int n) {
	for (int i = 0; i < n; i++) {
		printf("| %d | %s | %s | %s | %d |\n",
		       tab[i].sno, tab[i].lexeme, tab[i].dtype, tab[i].type, tab[i].size);
	}
}

int findTable(struct sttable *tab , char *nam , int n) {

	for (int i = 0; i < n; i++) {
		if (strcmp(tab[i].lexeme, nam) == 0) {
			return 1;
		}
	} return 0;
}

int getST(FILE *fa) {
	FILE *fb;
	int ca , cb;
	//conf check for fa

	fb = fopen("inp.c", "r");
	removeComments(fb);
	fa = fopen("out2.c", "r");

	fb = fopen("temp.c", "w+");
	ca = getc(fa);

	while (ca != EOF) {
		if (ca == '"') {
			putc(ca, fb);
			ca = getc(fa);
			while (ca != '"') {
				putc(ca, fb);
				ca = getc(fa);
			}
		}
		else if (ca == '#') {
			while (ca != '\n') {
				ca = getc(fa);
			}
			ca = getc(fa);
		}
		putc(ca, fb);
		ca = getc(fa);
	}
	fclose(fa);
	flcose(fb);

	fa = fopen("temp.c", "r");
	fb = fopen("out4.c", "w");
	ca = getc(fa);
	while (ca != EOF) {
		putc(ca, fb);
		ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);
	remove("temp.c");
	FILE *f1 = fopen("out4.c", "r");
	if (f1 == NULL)
	{
		printf("Error! File cannot be opened!\n");
		return 0;
	}
	struct token tkn;
	struct sttable st[10][100];
	int flag = 0, i = 0, j = 0;
	int tabsz[10];
	char w[25];
	w[0] = '\0';

	while ((tkn = getNextToken(f1)).row != -1) {
		printf("<%s , %d , %d , %s>\n", tkn.lexeme, tkn.row, tkn.col, tkn.type);

		if (strcmp(tkn.type, "KEYWORD") == 0) {
			if (isdtype(tkn.lexeme) == 1) {
				strcpy(dbuf, tkn.lexeme);
			}
		}
		else if (strcmp(tkn.type, "identifier") == 0) {
			strcpy(w, tkn.lexeme);
			tkn = getNextToken(f1);
			printf("<%s, %d, %d, %s>\n", tkn.lexeme, tkn.row, tkn.col, tkn.type);

			if (strcmp(tkn.type, "LB") == 0) {
				if (findTable(st[i], w, j) == 0) {
					ind++;
					st[i][j++] = fillTable(ind, w, dbuf, "func", -1);

				}
			}
			if (strcmp(tkn.type, "LS") == 0) {
				if (findTable(st[i], w, j) == 0) {
					tkn = getNextToken(f1);
					printf("<%s , %d , %d, %s>\n", tkn.lexeme, tkn.row, tkn.col, tkn.type);
					int s = 0;
					if (strcmp(tkn.type, "NUMBER") == 0) {
						s = atoi(tkn.lexeme);
					}
					ind++;
					st[i][j++] = fillTable(ind, w, dbuf, "id", sizeof(duf) * s);

				}
			}
			else {
				if (findTable(st[i], w, j) == 0) {
					ind++;
					st[i][j++] = fillTable(ind, w, dbuf, "id", sizeof(dbuf));
				}
			}
			else if (strcmp(tkn.type, "LC") == 0) {
				flag++;
			}
			else if (strcmp(tkn.type, "RC") == 0) {
				flag--;
				if (flag == 0) {
					tabsz[i] = j;
					i++;
					j = 0;
					ind = 0;
				}
			}
		}
	}
	int k = 0;
	for (k = 0; k < i; k++) {
		printf("FUnction %d\n".k + 1);
		printTable(st[k], tabsz[k]);
		print("\n\n");
	}
	fclose(f1);
}
FILE *f1;



void Program() {
	if (strcmp(token.lexeme, "main") == 0) {
		token = getNextToken(f1);

		if (strcmp(token.lexeme, "(") == 0) {
			token = getNextToken(f1);

			if (strcmp(token.lexeme, ")") == 0) {
				token = getNextToken(f1);

				if (strcmp(token.lexeme, "{") == 0) {
					token = getNextToken(f1);
					declarations();
					assign_stat();
					if (strcmp(token.lexeme, "}") == 0) {
						return ;
					}
					else {
						printf("[ERROR] MIsing } at at row :%d and col:%d", token.row, token.col);
						exit(0);
					}
				}
				else {
					printf("Error missing { at row :%d and col :%d", token.row, token.col);
				}

			}
			else {
				printf("Missing ) at row %d and col %d", token.row, token.col);
			}

		}
		else {
			printf("Missing ( at row %d and col %d", token.row, token.col);
		}
	}
	else {
		printf("Missing main function \n\n");
		exit(0);
	}
}

void declarations() {
	if (isDataType(token.lexeme) == 0) {
		return ;
	}
	datatypes();
	identifier_list();

	if (strcmp(token.lexeme, ";") == 0) {
		token = getNextToken(f1);
		declarations();
	}
	else {
		printf("Missing ; at row %d and col %d", token.row, token.col);
	}
}

void statement() {
	if (strncmp(token.type, "identifier") == 0) {
		token = getNextToken(f1);
		assign_stat();
		if (strncmp(token.lexeme, ";") == 0) {
			token = getNextToken(f1);
			return ;
		} else {
			//print missing error
		}
	}
	else if (strncmp(token.lexeme, "if") == 0) {
		token = getNextToken(f1);
		decisionstat();
	}
	else if (strncmp(token.lexeme, "while") == 0 || strncmp(token.lexeme, "for") == 0) {
		token = getNextToken(f1);
		loopingstmt();
	}
}


void datatypes() {
	if (strncmp(token.lexeme, "int") == 0) {
		token = getNextToken(f1);
		return ;
	}
	else if (strncmp(token.lexeme, "char") == 0) {
		token = getNextToken(f1);
		return ;
	}
	else {
		printf("Missing data type at row :%d and col %d", token.row , token.col);
		exit(0);
	}
}


void identifier_list() {
	if (strncmp(token.type, "identifier") == 0) {
		token = getNextToken(token);
		if (strncmp(token.lexeme, ",") == 0) {
			token = getNextToken(f1);
			identifier_list();
		}
		else
			return ;
	}
	else {
		printf("Missing identifier at row %d and col %d", token.row , token.col);
	}
}

void assign_stat() {
	if (strncmp(token.type, "identifier") == 0) {
		token = getNextToken(f1);
		if (strncmp(token.lexeme, "=") == 0) {
			token = getNextToken(f1);
			if (strncmp(token.type, "identifier") == 0) {
				token = getNextToken(f1);
				if (strncmp(token.lexeme, ";") == 0) {
					token = getNextToken(f1);
					return ;
				}
				else if (strncmp(token.type, "number") == 0) {
					token = getNextToken(f1);
					if (strncmp(token.lexeme, ";") == 0) {
						token = getNextToken(f1);
					}
					else {
						printf("MISSING ; AT ROW %d and col %d", token.row , token.col);
					}
				}//other non mathced error messages
			}
		}
	}
}


void decisionstat() {

}