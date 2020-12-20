#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "q1.c"

void prog();
void dec();
void ilist();
void isprime();
void dtype();
void slist();
void s();
void AS();
void expn();
void eprime();
void se();
void seprime();
void t();
void f();
void relop();
void ao();
void mo();

struct token tkn;
FILE *f1;

void invalid() {
	printf("-------- INVALID --------- \n");
	exit(0);
}
void valid() {
	printf(" -------- VALID --------- \n");
	exit(0);
}

void updateCurrent() {
	tkn = getNextToken(f1);
}

void prog() {
	updateCurrent();
	if (strcmp(tkn.lexemeName, "main") == 0) {
		updateCurrent();
		if (strcmp(tkn.lexemeName, "(") == 0) {
			updateCurrent();
			if (strcmp(tkn.lexemeName, ")") == 0) {
				updateCurrent();
				if (strcmp(tkn.lexemeName, "{") == 0) {
					dec();
					slist();
					updateCurrent();
					if (strcmp(tkn.lexemeName, "}") != 0)
						invalid();
				}
				else invalid();
			} else invalid();
		} else invalid();
	} else invalid();
}

void dec() {
	updateCurrent();
	if (strcmp(tkn.lexemeName, "int") == 0 || strcmp(tkn.lexemeName, "char") == 0) {
		dtype();
		list();
		if (strcmp(tkn.lexemeName, ",") == 0) {
			dec();

		}
		else {
			invalid();
		}
	}
	else return ;
}

void slist() {
	if (strcmp(tkn.lexemeName, "id") == 0) {
		s();
		if (strcmp(tkn.lexemeName, "id") == 0) {
			slist();
		}
	} else return ;
}

void s() {
	AS();
	updateCurrent();
	if (strcmp(tkn.lexemeName, ";") != 0) {
		invalid();
	}
}

void AS() {
	if (strcmp(tkn.lexemeName, "id") == 0) {
		updateCurrent();
		if (strcmp(tkn.lexemeName, "=") == 0) {
			expn();
		}
		else {
			invalid();
		}
	}
	else
		invalid();
}

void expn() {
	se();
	prime();
}

void set() {
	t();
	seprime()
}

void t() {
	f();
	tprime();
}
void f() {
	updatecurrent();
	if (strcmp(tkn.lexemeName, "id") != 0 && strcmp(tkn.lexemeName, "num") != 0)
		invalid();
}
void seprime() {
	if (strcmp(tkn.lexemeName, "+") == 0 || strcmp(tkn.lexemeName, "-") == 0) {
		ao();
		t();
		seprime();
	}
	else
		return;
}
void tprime() {
	if (strcmp(tkn.lexemeName, "*") == 0 || strcmp(tkn.lexemeName, "/") == 0 || strcmp(tkn.lexemeNa
	        me, "%") == 0) {
		mo();
		f();
		tprime();
	}
	else return;
}

void eprime() {
	if (strcmp(tkn.lexemeName, "==") == 0 || strcmp(tkn.lexemeName, "!=") == 0 || strcmp(tkn.lexeme
	        Name, "<=") == 0 || strcmp(tkn.lexemeName, ">=") == 0 || strcmp(tkn.lexemeName, "<") == 0 || strc
	        mp(tkn.lexemeName, ">") == 0) {
		relop();
		se();
	}
	else return;
}

void relop() {
	updatecurrent();
	if (strcmp(tkn.lexemeName, "==") != 0 && strcmp(tkn.lexemeName, "!=") != 0 && strcmp(tkn.lexe
	        meName, "<=") != 0 && strcmp(tkn.lexemeName, ">=") != 0 && strcmp(tkn.lexemeName, ">") != 0
	        && strcmp(tkn.lexemeName, "<") != 0)
		invalid();
}

void ao() {
	updatecurrent();
	if (strcmp(tkn.lexemeName, "+") != 0 && strcmp(tkn.lexemeName, "-") != 0)
		invalid();
}
void mo() {
	updatecurrent();
	if (strcmp(tkn.lexemeName, "*") != 0 && strcmp(tkn.lexemeName, "/") != 0 && strcmp(tkn.lexeme
	        Name, "%") != 0)
		invalid();
}
void dtype() {
	if (strcmp(tkn.lexemeName, "int") != 0 && strcmp(tkn.lexemeName, "char") != 0)
		invalid();
}
void ilist() {
	updatecurrent();
	if (strcmp(tkn.lexemeName, "id") != 0)
		invalid();
	iprime();
}

void iprime() {
	updatecurrent();
	if (strcmp(tkn.lexemeName, ",") == 0)
		ilist();
	else if (strcmp(tkn.lexemeName, "[") == 0) {
		updatecurrent();
		if (strcmp(tkn.lexemeName, "num") == 0) {
			updatecurrent();
			if (strcmp(tkn.lexemeName, "]") == 0) {
				updatecurrent();
				if (strcmp(tkn.lexemeName, ",") == 0) {
					ilist();
				}
				else return;
			} else invalid();
		} else invalid();
	} else return;
}

void parse() {
	prog();
	valid();
}

int main(int argc , char **argv) {
	if (argc != 2) {
		printf("Error : Usage %s <inputfile>", argv[0]);
		exit(1);
	}
	f1 = fopen(argv[1], "r");
	if (f1 == NULL) {
		printf("FIle does not exist!\n");
		exit(1);
	}
	parse();
}
