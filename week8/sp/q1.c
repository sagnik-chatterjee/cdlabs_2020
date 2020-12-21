#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.c"
void prog();
void dec();
void ilist();
void iprime();
void dtype();
void slist();
void s();
void AS();
void expn();
void eprime();
void se();
void seprime();
void t();
void tprime();
void f();
void relop();
void ao();
void mo();
struct token tkn;
FILE *f1;
void invalid()
{
	printf("~~~~~~~~~~INVALID~~~~~~~~~~\n");
	exit(0);
}
void valid()
{
	printf("~~~~~~~~~~SUCCESS~~~~~~~~~~\n");
	exit(0);
} void updatecurrent()
{
	tkn = getNextToken(f1);
}
void prog()
{
	updatecurrent();
	if (strcmp(tkn.lexeme, "main") == 0)
	{
		updatecurrent();
		if (strcmp(tkn.lexeme, "(") == 0)
		{
			updatecurrent();
			if (strcmp(tkn.lexeme, ")") == 0)
			{
				updatecurrent();
				if (strcmp(tkn.lexeme, "{") == 0)
				{
					dec();
					slist();
					updatecurrent();
					if (strcmp(tkn.lexeme, "}") != 0)
						invalid();
				}
				else
					invalid();
			}
			else
				invalid();
		}
		else
			invalid();
	}
	else
		invalid();
}
void dec()
{
	updatecurrent();
	if (strcmp(tkn.lexeme, "int") == 0 || strcmp(tkn.lexeme, "char") == 0)
	{
		dtype();
		ilist();
		if (strcmp(tkn.lexeme, ";") == 0)
		{
			dec();
		}
		else
			invalid();
	} else
		return;
}
void slist()
{
	if (strcmp(tkn.lexeme, "id") == 0)
	{
		s();
		if (strcmp(tkn.lexeme, "id") == 0)
		{
			slist();
		}
	}
	else
		return;
}
void s()
{
	AS();
	updatecurrent();
	if (strcmp(tkn.lexeme, ";") != 0)
		invalid();
}
void AS()
{
	if (strcmp(tkn.lexeme, "id") == 0)
	{
		updatecurrent();
		if (strcmp(tkn.lexeme, "=") == 0)
		{
			expn();
		}
		else
			invalid();
	}
	else
		invalid();
}
void expn()
{
	se();
	eprime();
}
void se()
{
	t();
	seprime();
}
void t()
{
	f();
	tprime();
}
void f()
{
	updatecurrent();
	if (strcmp(tkn.lexeme, "id") != 0 && strcmp(tkn.lexeme, "num") != 0)
		invalid();
}
void seprime()
{
	if (strcmp(tkn.lexeme, "+") == 0 || strcmp(tkn.lexeme, "-") == 0)
	{
		ao();
		t();
		seprime();
	}
	else
		return;
}
void tprime()
{
	if (strcmp(tkn.lexeme, "*") == 0 || strcmp(tkn.lexeme, "/") == 0 || strcmp(tkn.lexeme, "%") == 0)
	{
		mo();
		f();
		tprime();
	}
	else
		return;
}
void eprime()
{
	if (strcmp(tkn.lexeme, "==") == 0 || strcmp(tkn.lexeme, "!=") == 0 || strcmp(tkn.lexeme
	        , "<=") == 0 || strcmp(tkn.lexeme, ">=") == 0 || strcmp(tkn.lexeme, "<") == 0 || strcmp(tkn.lexeme, ">") == 0)
	{
		relop();
		se();
	}
	else return;
}
void relop()
{
	updatecurrent();
	if (strcmp(tkn.lexeme, "==") != 0 && strcmp(tkn.lexeme, "!=") != 0 && strcmp(tkn.lexeme, "<=") != 0 && strcmp(tkn.lexeme, ">=") != 0 && strcmp(tkn.lexeme, ">") != 0
	        && strcmp(tkn.lexeme, "<") != 0)
		invalid();
}
void ao()
{
	updatecurrent();
	if (strcmp(tkn.lexeme, "+") != 0 && strcmp(tkn.lexeme, "-") != 0)
		invalid();
}
void mo()
{
	updatecurrent();
	if (strcmp(tkn.lexeme, "*") != 0 && strcmp(tkn.lexeme, "/") != 0 && strcmp(tkn.lexeme, "%") != 0)
		invalid();
}
void dtype()
{
	if (strcmp(tkn.lexeme, "int") != 0 && strcmp(tkn.lexeme, "char") != 0)
		invalid();
}
void ilist()
{
	updatecurrent();
	if (strcmp(tkn.lexeme, "id") != 0)
		invalid();
	iprime();
}
void iprime()
{
	updatecurrent();
	if (strcmp(tkn.lexeme, ",") == 0)
		ilist();
	else if (strcmp(tkn.lexeme, "[") == 0)
	{
		updatecurrent();
		if (strcmp(tkn.lexeme, "num") == 0) {
			updatecurrent();
			if (strcmp(tkn.lexeme, "]") == 0)
			{
				updatecurrent();
				if (strcmp(tkn.lexeme, ",") == 0)
				{
					ilist();
				}
				else
					return;
			}
			else
				invalid();
		}
		else invalid();
	}
	else
		return;
}
void parse()
{
	prog();
	valid();
}
int main()
{
	f1 = fopen("input.c", "r");
	if (f1 == NULL)
	{
		printf("File does not exist!!!\n");
		exit(0);
	}
	parse();
}
