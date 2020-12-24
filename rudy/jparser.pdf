#include "lexical_analyzer.h"

FILE *f1;
struct token t;
char *datatype[] = {"int", "char"};
void program();
void declarations();
void statement_list();
void data_type();
void identifier_list();
void statement();
void assign_stat();
void expn();
void simple_expn();
void term();
void factor();
void tprime();
void seprime();
void eprime();

void decision_stat();
void looping_stat();
void dprime();

void dprime() {
    if (strcmp(t.lexeme, "else") == 0) {
        t = getNextToken(f1);
        if (strcmp(t.lexeme, "{") == 0) {
            t = getNextToken(f1);
            statement_list();
            if (strcmp(t.lexeme, "}") == 0) {
                t = getNextToken(f1);
                return;
            }
            else {
                printf("%d.%d : Expected a \" } \" \n", t.row, t.col);
                exit(0);
            }

        }
        else {
            printf("%d.%d : Expected a \" { \" \n", t.row, t.col);
            exit(0);
        }
    }
    else
        return;

}

void looping_stat() {
    if (strcmp(t.lexeme, "while") == 0) {
        t = getNextToken(f1);
        if (strcmp(t.lexeme, "(") == 0) {
            t = getNextToken(f1);
            expn();
            if (strcmp(t.lexeme, ")") == 0) {
                t = getNextToken(f1);
                if (strcmp(t.lexeme, "{") == 0) {
                    t = getNextToken(f1);
                    statement_list();
                    if (strcmp(t.lexeme, "}") == 0) {
                        t = getNextToken(f1);
                        return;
                    }
                    else {
                        printf("%d.%d : Expected a \" } \" \n", t.row, t.col);
                        exit(0);
                    }
                }
                else {
                    printf("%d.%d : Expected a \" { \" \n", t.row, t.col);
                    exit(0);
                }
            }
            else {
                printf("%d.%d : Expected a \" ) \" \n", t.row, t.col);
                exit(0);
            }
        }
        else {
            printf("%d.%d : Expected a \" ( \" \n", t.row, t.col);
            exit(0);
        }
    }
    else if (strcmp(t.lexeme, "for") == 0) {
        t = getNextToken(f1);
        if (strcmp(t.lexeme, "(") == 0) {
            t = getNextToken(f1);
            assign_stat();
            if (strcmp(t.lexeme, ";") == 0) {
                t = getNextToken(f1);
                expn();
                if (strcmp(t.lexeme, ";") == 0) {
                    t = getNextToken(f1);
                    assign_stat();
                    if (strcmp(t.lexeme, ")") == 0) {
                        t = getNextToken(f1);
                        if (strcmp(t.lexeme, "{") == 0) {
                            t = getNextToken(f1);
                            statement_list();
                            if (strcmp(t.lexeme, "}") == 0) {
                                t = getNextToken(f1);
                                return;
                            }
                            else {
                                printf("%d.%d : Expected a \" } \" \n", t.row, t.col);
                                exit(0);
                            }
                        }
                        else {
                            printf("%d.%d : Expected a \" { \" \n", t.row, t.col);
                            exit(0);
                        }
                    }
                    else {
                        printf("%d.%d : Expected a \" ) \" \n", t.row, t.col);
                        exit(0);
                    }
                }
                else {
                    printf("%d.%d : Expected a \" ; \" \n", t.row, t.col);
                    exit(0);
                }
            }
            else {
                printf("%d.%d : Expected a \" ; \" \n", t.row, t.col);
                exit(0);
            }
        }
        else {
            printf("%d.%d : Expected a \" ( \" \n", t.row, t.col);
            exit(0);
        }
    }
    else {
        printf("%d.%d : Expected a \" while or for \" \n", t.row, t.col);
        exit(0);
    }
}

void decision_stat() {
    if (strcmp(t.lexeme, "if") == 0) {
        t = getNextToken(f1);
        if (strcmp(t.lexeme, "(") == 0) {
            t = getNextToken(f1);
            expn();
            if (strcmp(t.lexeme, ")") == 0) {
                t = getNextToken(f1);
                if (strcmp(t.lexeme, "{") == 0) {
                    t = getNextToken(f1);
                    statement_list();
                    if (strcmp(t.lexeme, "}") == 0) {
                        t = getNextToken(f1);
                        dprime();
                        return;
                    }
                    else {
                        printf("%d.%d : Expected a \" } \" \n", t.row, t.col);
                        exit(0);
                    }
                }
                else {
                    printf("%d.%d : Expected a \" { \" \n", t.row, t.col);
                    exit(0);
                }
            }
            else {
                printf("%d.%d : Expected a \" ) \" \n", t.row, t.col);
                exit(0);
            }
        }
        else {
            printf("%d.%d : Expected a \" ( \" \n", t.row, t.col);
            exit(0);
        }
    }
    else {
        printf("%d.%d : Expected a \" if \" \n", t.row, t.col);
        exit(0);
    }
}

void identifier_list() {
    if (strcmp(t.type, "IDENTIFIER") == 0) {
        t = getNextToken(f1);

        if (strcmp(t.lexeme, ",") == 0) {
            t = getNextToken(f1);

            identifier_list();
        }
        else if (strcmp(t.lexeme, "[") == 0) {
            t = getNextToken(f1);

            if (strcmp(t.type, "NUMBER") == 0) {
                t = getNextToken(f1);

                if (strcmp(t.lexeme, "]") == 0) {
                    t = getNextToken(f1);

                    if (strcmp(t.lexeme, ",") == 0) {
                        t = getNextToken(f1);

                        identifier_list();
                    }
                    else
                        return;
                }
                else {
                    printf("%d.%d : Expected a \" ] \" \n", t.row, t.col);
                    exit(0);
                }
            }
            else {
                printf("%d.%d : Expected a number\n", t.row, t.col);
                exit(0);
            }
        }
        else
            return;
    }
    else {
        printf("%d.%d : Expected a IDENTIFIER\n", t.row, t.col);
        exit(0);
    }
}

int isDatatype(char *x) {
    int n = sizeof(datatype) / sizeof(char *);
    for (int i = 0; i < n; i++)
        if (strcmp(t.lexeme, datatype[i]) == 0)
            return 1;
    return 0;
}

void data_type() {
    int n = sizeof(datatype) / sizeof(char *);
    for (int i = 0; i < n; i++) {
        if (strcmp(t.lexeme, datatype[i]) == 0) {
            t = getNextToken(f1);

            return;
        }
    }
    printf("%d.%d : Expected a valid datatype\n", t.row, t.col);
    exit(0);
}

void declarations() {
    if (isDatatype(t.lexeme)) {
        data_type();
        identifier_list();
        if (strcmp(t.lexeme, ";") == 0) {
            t = getNextToken(f1);

            declarations();
        }
        else {
            printf("%d.%d : Expected \" ; \"", t.row, t.col);
            exit(0);
        }
    }
    else
        return;
}
void program() {
    t = getNextToken(f1);

    if (strcmp(t.lexeme, "main") == 0) {
        t = getNextToken(f1);

        if (strcmp(t.lexeme, "(") == 0) {
            t = getNextToken(f1);

            if (strcmp(t.lexeme, ")") == 0) {
                t = getNextToken(f1);

                if (strcmp(t.lexeme, "{") == 0) {
                    t = getNextToken(f1);

                    declarations();
                    statement_list();
                    if (strcmp(t.lexeme, "}") == 0) {
                        t = getNextToken(f1);
                        if (t.row == -1) {
                            printf("Parse Successful\n");
                            return ;
                        }
                        else {
                            printf("Error found token after main.\n");
                        }
                    }
                    else {
                        printf("%d.%d : Expected \" } \"\n", t.row, t.col);
                        exit(0);
                    }
                }
                else {
                    printf("%d.%d : Expected \" { \"\n", t.row, t.col);
                    exit(0);
                }
            }
            else {
                printf("%d.%d : Expected \" ) \" \n", t.row, t.col);
                exit(0);
            }
        }
        else {
            printf("%d.%d : Expected \" ( \"\n", t.row, t.col);
            exit(0);
        }
    }
    else {
        printf("%d.%d : Expected \" main() \" \n", t.row, t.col);
        exit(0);
    }
}

void statement_list() {
    if (strcmp(t.type, "IDENTIFIER") == 0 || strcmp(t.lexeme, "if") == 0 || strcmp(t.lexeme, "for") == 0 || strcmp(t.lexeme, "while") == 0) {
        statement();
        statement_list();
    }
    return;
}
void statement() {
    if (strcmp(t.type, "IDENTIFIER") == 0) {
        assign_stat();
        if (strcmp(t.lexeme, ";") == 0) {
            t = getNextToken(f1);
            return;
        }
        else {
            printf("%d.%d : Expected \" ; \"\n", t.row, t.col);
            exit(0);
        }
    }
    else if (strcmp(t.lexeme, "if") == 0)
        decision_stat();
    else if (strcmp(t.lexeme, "while") == 0 || strcmp(t.lexeme, "for") == 0)
        looping_stat();
    else {
        printf("%d.%d : Expected \" statement \"\n", t.row, t.col);
        exit(0);
    }
}
void assign_stat() {
    if (strcmp(t.type, "IDENTIFIER") == 0) {
        t = getNextToken(f1);

        if (strcmp(t.lexeme, "=") == 0) {
            t = getNextToken(f1);

            expn();
            return;
        }
        else {
            printf("%d.%d : Expected \" = \" \n", t.row, t.col);
            exit(0);
        }
    }
    else {
        printf("%d.%d : Expected IDENTIFIER from assign_stat\n", t.row, t.col);
        exit(0);
    }
}

void expn() {
    simple_expn();
    eprime();
    return;
}
void simple_expn() {
    if (strcmp(t.type, "IDENTIFIER") == 0 || strcmp(t.type, "NUMBER") == 0) {
        term();
        seprime();
    }
    else {
        printf("%d.%d : Expected IDENTIFIER or NUMBER\n", t.row, t.col);
        exit(0);
    }
}
void term() {
    factor();
    tprime();
}
void factor() {
    if (strcmp(t.type, "IDENTIFIER") == 0 || strcmp(t.type, "NUMBER") == 0) {
        t = getNextToken(f1);

        return;
    }
    else {
        printf("%d.%d : Expected IDENTIFIER or NUMBER\n", t.row, t.col);
        exit(0);
    }
}
int isMulop(char *s) {
    if (strcmp(s, "*") == 0 || strcmp(s, "/") == 0 || strcmp(s, "%") == 0)
        return 1;
    else
        return 0;
}
int isAddop(char *s) {
    if (strcmp(s, "+") == 0 || strcmp(s, "-") == 0)
        return 1;
    else
        return 0;
}
void tprime() {
    if (isMulop(t.lexeme)) {
        t = getNextToken(f1);

        factor();
        tprime();
    }
    return;
}
void seprime() {
    if (isAddop(t.lexeme)) {
        t = getNextToken(f1);
        term();
        seprime();
    }
    return;
}
int isRelop(char *s) {
    if (strcmp(s, "==") == 0 || strcmp(s, "!=") == 0 || strcmp(s, "<=") == 0 || strcmp(s, ">=") == 0 || strcmp(s, "<") == 0 || strcmp(s, ">") == 0)
        return 1;
    else
        return 0;
}
void eprime() {
    if (isRelop(t.lexeme)) {
        t = getNextToken(f1);

        simple_expn();
    }
    return;
}
int main(int argc, char *argv[]) {
    FILE *fa, *fb;
    int ca, cb;
    fa = fopen(argv[1], "r");
    if (argc != 3) {
        printf("Insufficient arguments\n");
    }
    if (fa == NULL) {
        printf("Cannot open file \n");
        exit(0);
    }
    fb = fopen(argv[2], "w+");
    ca = getc(fa);
    while (ca != EOF) {
        if (ca == ' ') {
            putc(ca, fb);
            while (ca == ' ')
                ca = getc(fa);
        }
        if (ca == '/') {
            cb = getc(fa);
            if (cb == '/') {
                while (ca != '\n')
                    ca = getc(fa);
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
    fa = fopen(argv[2], "r");
    if (fa == NULL) {
        printf("Cannot open file");
        return 0;
    }
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
            while (ca != '\n')
                ca = getc(fa);
            ca = getc(fa);
        }
        putc(ca, fb);
        ca = getc(fa);
    }
    fclose(fa);
    fclose(fb);

    fa = fopen("temp.c", "r");
    fb = fopen(argv[2], "w");
    ca = getc(fa);
    while (ca != EOF) {
        putc(ca, fb);
        ca = getc(fa);
    }
    fclose(fa);
    fclose(fb);
    remove("temp.c");
    f1 = fopen(argv[2], "r");
    if (f1 == NULL) {
        printf("Error! File cannot be opened!\n");
        return 0;
    }
    program();
    return 0;
}
