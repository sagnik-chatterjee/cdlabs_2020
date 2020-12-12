/*
AUTHOR : SAGNIK CHATTERJEE 
DATE : DEC 12,2020
USAGE : ./q1 input.c
where input is a valid c file 
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Basically symbol table is a  dictionary 

//items stored in symbol table :
// 1. Varibale names and constants
// 2. Procedure and function names
// 3. literal constants and strings
// 4. compiler generated temporaries
// 5. labels in source langauges

//Info used by compiler used by symbol table
// 1. Data type and name
// 2. declaring procedures
// 3. offset in storage
// 4. if structure or record then ,pointer to structure table
// 5. for params ,whether parameter passing by value or by reference
// 6. Number and type of args passed to function
// 7. BaseAddress


static int row=1,col=1;
char buf[2048];
char dbuf[128];

int ind=0;
char key[36][10] = {
	"auto","double","int","struct","break","else","long","switch",
"case","enum","register","typedef","char","extern","return","union",
"continue","for","signed","void","do","if","static",
"while","default","goto","sizeof","volatile","const","float",
"short","unsigned","printf","scanf","true","false"

};


const char *datatypes[]={"int","char","void","float","bool","double"};
const char specialSymbols[]={'?',';',':',','};
const char arithmeticSymbols[]={'*'};


struct token {
	char token_name [128];
	int index;
	unsigned int row, col; //Line numbers.
	char type[64];
} token;

struct sttable
{
	int sno;
	char lexeme[128];
	char dtype[64];
	char type[64];
	int size;
};
struct sttable fillTable(int sno,char *lexn,char *dt,char *t,int s)
{
	struct sttable tab;
	tab.sno=sno;
	strcpy(tab.lexeme,lexn);
	strcpy(tab.dtype,dt);
	strcpy(tab.type,t);
	tab.size=s;
	return tab;
}

int findTable(struct sttable *tab,char *nam,int n)
{
	int i=0;
	for(i=0;i<n;i++)
	{
		if(strcmp(tab[i].lexeme,nam)==0)
		{
			return 1;
		}
	}
	return 0;
}

void printTable(struct sttable *tab,int n)
{
	for(int i=0;i<n;i++)
	{
		printf("%d %s %s %s %d\n",tab[i].sno,tab[i].lexeme,tab[i].dtype,tab[i].type,tab[i].size);
	}
}
void fillToken(struct token *token,char c,int row,int col, char *type)
{
	token->row=row;
	token->col=col;
	strcpy(token->type,type);
	token->lexeme[0]=c;
	token->lexeme[1]='\0';
}


void print_token(struct token s) {
	printf("<%s,%d,%d>", s.token_name, s.row, s.col);
	return;
}

void removeComments(char **argv) {
	FILE *fa, *fb; int ca, cb;

	fa = fopen(argv[1], "r");
	if (fa == NULL) {
		printf("Cannot open %s for reading \n",argv[1]);
		exit(0);
	}
	fb = fopen("q1out.txt", "w+");
	if(fb==NULL){
		printf("Cannot open q1out.txt for writing\n");
		exit(0);
	}

	ca = getc(fa);
	while (ca != EOF) {
		if ( ca == ' ') {
			putc(ca, fb);
			while (ca == ' ' || ca == '\t') ca = getc(fa);
		}
		if (ca == '/') {
			cb = getc(fa);
			if (cb == '/') {
				while (ca != '\n') ca = getc(fa);
				putc(ca, fb);
			}
			else if ( cb == '*') {
				do {
					while (ca != '*') ca = getc(fa);
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

void removeDirectives(char **argv) {
	FILE *fa, *fb; int ca, cb;
		
	removeComments(argv);
	fa = fopen("q1out.txt", "r");
	if (fa == NULL) {
		printf("Cannot open q1out.txt for reading.\n");
		exit(0);
	}
	fb = fopen("q2tempout.txt", "w+");
	ca = getc(fa);
	while (ca != EOF) {
		if ( ca == '#') {
			do {
				ca = getc(fa);
			} while (ca != '\n');
		}
		putc(ca, fb);
		ca = getc(fa);
	}

	fclose(fa);
	fclose(fb);

	fa = fopen("q2tempout.txt", "r");
	if (fa == NULL) {
		printf("Cannot open q2tempout for reading.\n");
		return;
	}
	fb = fopen("q2out.txt", "w+");
	ca = fgetc(fa);
	while (ca == '\n') {
		ca = fgetc(fa);
	}
	while (ca != EOF) {

		putc(ca, fb);
		ca = fgetc(fa);
	}

	fclose(fa);
	fclose(fb);

	if (remove("q2tempout.txt") != 0) printf("Error removing q2tempout.\n");
}

int isKeyword(char* word) {//sz
	// printf("%s\n",word );
	for (int i = 0; i < 36; i++) {
		if (strcmp(key[i], word) == 0) return 1;
	}
	return 0;
}

void newLine()
{
	++row;
	col=1;
}

int isDataType(char *word)
{
	int i;
	for(i=0;i<sizeof(datatypes)/sizeof(char*);i++)
	{
		if(strcmp(word,datatypes[i])==0)
		{
			return 1;
		}
	}
	return 0;
}

bool isDelimiter(char ch)
{
	if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
	        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
	        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
	        ch == '[' || ch == ']' || ch == '{' || ch == '}')
		return true;
	return false;
}


bool isRealNumber(char* str)
{
	int i, len = strlen(str);
	bool hasDecimal = false;

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++) {
		if (str[i] != '0' && str[i] != '1' && str[i] != '2'
		        && str[i] != '3' && str[i] != '4' && str[i] != '5'
		        && str[i] != '6' && str[i] != '7' && str[i] != '8'
		        && str[i] != '9' && str[i] != '.' ||
		        (str[i] == '-' && i > 0))
			return (false);
		if (str[i] == '.')
			hasDecimal = true;
	}
	return hasDecimal;
}


bool isInteger(char* str)
{
	int i, len = strlen(str);

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++) {
		if (str[i] != '0' && str[i] != '1' && str[i] != '2'
		        && str[i] != '3' && str[i] != '4' && str[i] != '5'
		        && str[i] != '6' && str[i] != '7' && str[i] != '8'
		        && str[i] != '9' || str[i] == '.' || (str[i] == '-' && i > 0))
			return (false);
	}
	return (true);
}

int charIs(int c,const char *arr)
{
	int len
	if(arr==specialSymbols)
	{
	  	len=sizeof(specialSymbols)/sizeof(char);
	}
	else if(arr==arithmeticsymbols)
	{
	       	len=sizeof(arithmeticSymbols)/sizeof(char);
	}
	for(int i=0;i<len;i++)
	{
	   	if(c==arr[i])
	   	{
	   	  	return 1;
	    }
	}
	return 0;
}

struct token getNextToken(FILE *fa){

	int c;
	struct token tkn= 
	{
		.row=-1
	};
	int gotToken=0;
	while(!gotToken && (c=fgetc(fa))!=EOF)
	{
		if(charIs(c,specialsymbols))
		{
			fillToken(&tkn,c,row,col,"SS");
			gotToken=1;
			++col;
		}
		else if(charIs(c,arithmeticsymbols))
		{
			fseek(fa,-1,SEEK_CUR);
			c=getc(fa);
			if(isalnum(c)){//alnum a sys call to chck 
			fillToken(&tkn,c,row,col,"ARITHMETIC OPERATOR");
			gotToken=1;
			++col;
			}
			fseek(fa,1,SEEK_CUR);
		}
		else if(c=='(')
		{
			fillToken(&tkn,c,row,col,"LB");
			gotToken=1;
			col++;
		}
		else if(c==')')
		{
			fillToken(&tkn,c,row,col,"RB");
			gotToken=1;
			col++;
		}
		else if(c=='{')
		{
			fillToken(&tkn,c,row,col,"LC");
			gotToken=1;
			col++;
		}
		else if(c=='}')
		{
			fillToken(&tkn,c,row,col,"RC");
			gotToken=1;
			col++;
		}
		else if(c=='[')
		{
			fillToken(&tkn,c,row,col,"LS");
			gotToken=1;
			col++;
		}
		else if(c==']')
		{
			fillToken(&tkn,c,row,col,"RS");
			gotToken=1;
			col++;
		}
		else if(c=='+')
		{
			int x=fgetc(fa);
			if(x!='+')
			{
				fillToken(&tkn,c,row,col,"ARITHMETIC OPERATOR");
				gotToken=1;
				col++;
				fseek(fa,-1,SEEK_CUR);
			}
			else
			{
				fillToken(&tkn,c,row,col,"UNARY OPERATOR");
				strcpy(tkn.lexeme,"++");
				gotToken=1;
				col+=2;
			}
		}
		else if(c=='-')
		{
			int x=fgetc(fa);
			if(x!='-')
			{
				fillToken(&tkn,c,row,col,"ARITHMETIC OPERATOR");
				gotToken=1;
				col++;
				fseek(fa,-1,SEEK_CUR);
			}
			else
			{
				fillToken(&tkn,c,row,col,"UNARY OPERATOR");
				strcpy(tkn.lexeme,"++");
				gotToken=1;
				col+=2;
			}
		}
		else if(c=='=')
		{
			int x=fgetc(fa);
			if(x!='=')
			{
				fillToken(&tkn,c,row,col," ASSIGNMENT OPERATOR ");
				gotToken=1;
				col++;
				fseek(fa,-1,SEEK_CUR);
			}
			else
			{
				fillToken(&tkn,c,row,col," RELATIONAL OPERATOR ");
				strcpy(tkn.lexeme,"++");
				gotToken=1;
				col+=2;
			}
		}
		else if(isdigit(c))
		{
			fillToken(&tkn,c,row,col++," NUMBER ");
			int j=1;
			while((c=fgetc(fa))!=EOF && isdigit(c))
			{
				tkn.lexeme[j++]=c;
				col++;
			}
			tkn.lexeme[j]='\0';
			gotToken=1;
			fseek(fa,-1,SEEK_CUR);
		}
		else if(c == '#') 
		{
			while((c = fgetc(fa))!= EOF && c != '\n');
			newLine();
	    }
	    else if(c=='\n')
		{
			newLine();
			c = fgetc(fa);
			if(c == '#') 
			{
				while((c = fgetc(fa)) != EOF && c != '\n');
				newLine();
			}
			else if(c != EOF) 
			{
				fseek(fa, -1, SEEK_CUR);
			}
		}
		else if(isspace(c))
		{
		   	++col;
		}
		else if(isalpha(c) || c=='_')
		{
			tkn.row=row;
			tkn.col=col++;
			tkn.lexeme[0]=c;
			int j=1;
			while((c=fgetc(fa))!=EOF && isalnum(c))
			{
				tkn.lexeme[j++]=c;
				col++;
			}
			tkn.lexeme[j]='\0';
			if(isKeyword(tkn.lexeme))
			{
				strcpy(tkn.type," KEYWORD ");
			}
			else
			{
				strcpy(tkn.type," IDENTIFIER ");
			}
			gotToken=1;
			fseek(fa,-1,SEEK_CUR);
		}
		else if(c=='/')
		{
			int d=fgetc(fa);
			++col;
			if(d=='/')
			{
			   	while((c=fgetc(fa))!= EOF && c!='\n')
			   	{
			   	  	++col;
			   	}
			   	if(c=='\n')
			   	{
			   	    newLine();
			   	}
			}
			else if(d=='*')
			{
			   	do
			   	{
			   		if(d=='\n')
			   		{
			   		   	newLine();
			   		}
			   		while((c==fgetc(fa))!= EOF && c!='*')
			   		{
			   		   	++col;
			   		   	if(c=='\n')
			   		   	{
			   		   	 	newLine();
			   		   	}
			   		}
			   		++col;
			   	}while((d==fgetc(fa))!= EOF && d!='/' && (++col));
			   	++col;
			}
			else
			{
			   	fillToken(&tkn,c,row,--col,"arithmatic operator");
			   	gotToken=1;
			   	fseek(fa,-1,SEEK_CUR);
			}
		}
		else if(c=='"')
		{
			tkn.row=row;
			tkn.col=col;
			strcpy(tkn.type, "string literal ");
			int k = 1; 
			tkn.lexeme[0] = '"';
			while((c = fgetc(fa)) != EOF && c != '"') 
			{
				tkn.lexeme[k++] = c;
				++col;
			}
			tkn.lexeme[k] = '"';
			gotToken = 1;
		}
		else if(c == '<' || c == '>' || c == '!') 
	 	{
			fillToken(&tkn, c, row, col, "RELATIONAL OPERATOR");
			++col;
			int d = fgetc(fa);
			if(d == '=') 
			{
				++col;
				strcat(tkn.lexeme, "=");
			} 
			else 
			{
				if(c == '!')
				{
					strcpy(tkn.type, "LOGICAL OPERATOR");
				}
				fseek(fa, -1, SEEK_CUR);
			}
			gotToken = 1;
		} 
		else if(c == '&' || c == '|') 
		{
			int d = fgetc(fa);
			if(c == d) 
			{
					tkn.lexeme[0] = tkn.lexeme[1] = c;
					tkn.lexeme[2] = '\0';
					tkn.row = row;
					tkn.col = col; 
					++col; 
					gotToken = 1;
					strcpy(tkn.type, "LOGICAL OPERATOR");
			} 
			else 
			{
				fseek(fa, -1, SEEK_CUR);
			}
			++col;
		}
		else
		{
			++col;
		} 
	}
	return tkn;
}



int main(int argc, char **argv)
{
	FILE *fa, *fb;
	int ca, cb;
	
	if(argc<2){
		printf("[ERROR] Usage : %s <input_c_file>",argv[0]);
		exit(0);
	}
	fa =fopen(argv[1],"r");
	if(fa==NULL){
		printf("Cannot open file %s for reading ,for symbol table",argv[1]);
		exit(0);

	}
	fb = fopen("sampleout.c", "w+");
    if(fb==NULL){
    	printf("Cannot open file %s for writing. \n",argv[2]);
    	exit(0);
    }
	removeDirectives(argv);//removeDirectives internally calls the removeComments() function 
	fclose(fa);
	fclose(fb);

	/*
	fa=fopen("sampleout.c","r");
	if(fa==NULL){
		printf("Cannot open file sampleout.c for reading.\n");
		exit(0);
	}
	fb=fopen("temp.c","w+");
	ca=getc(fa);
	while(ca!=EOF){

	}
	*/

	return 0;
}
