#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };
void resetall(void);
void dcl(void);
void dirdcl(void);
int gettoken(void);
void error(char *s);

int tokentype;           // type of last token
char token[MAXTOKEN];    // last token string
char name[MAXTOKEN];     // identfier name
char datatype[MAXTOKEN]; // data type = char, int, etc.
char out[1000];          // output string

int errors = 0;

/* convert declrations to words */
int main() {
  while (gettoken() != EOF) { // 1st token
    strcpy(datatype, token);  // is the datatype
    out[0] = '\0';
    dcl(); // parse rest of line
    if (tokentype != '\n') {
      error("syntax");
    }
    if (!errors)
      printf("%s: %s %s\n", name, out, datatype);
    resetall();
  }
  return 0;
}

/* dcl: parse a declartor */
void dcl(void) {
  int ns;
  for (ns = 0; gettoken() == '*';) /* count * s */
    ns++;
  dirdcl();
  while (ns--)
    strcat(out, " pointer to");
}

/* drdcl: parse direct declarator */
void dirdcl(void) {
  int type;
  if (tokentype == '(') {
    dcl();
    if (tokentype != ')') {
      error("missing )");
      return;
    }
  } else if (tokentype == NAME)
    strcpy(name, token);
  else {
    error("expected name or (dcl)");
    return;
  }
  while ((type = gettoken()) == PARENS || type == BRACKETS)
    if (type == PARENS)
      strcat(out, " function returning");
    else {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
}

int gettoken(void) { // returns next toke
  int c, getch(void);
  void ungetch(int);
  char *p = token;

  while ((c = getch()) == ' ' || c == '\t')
    ;
  if (c == '(') {
    if ((c = getch()) == ')') {
      strcpy(token, "()");
      return tokentype = PARENS;
    } else {
      ungetch(c);
      return tokentype = '(';
    }
  } else if (c == '[') {
    for (*p++ = c; (*p++ = getch()) != ']';)
      ;
    *p = '\0';
    return tokentype = BRACKETS;
  } else if (isalpha(c)) {
    for (*p++ = c; isalnum(c = getch());)
      *p++ = c;
    *p = '\0';
    ungetch(c);
    return tokentype = NAME;
  } else
    return tokentype = c;
}

void resetstr(char *s) {
  while (*s)
    *s++ = '\0';
}
void resetall(void) {
  void bufreset(void);
  resetstr(out);
  bufreset();
  errors = 0;
}

void error(char *s) {
  errors++;
  printf("error %d: %s\n", errors, s);
}
