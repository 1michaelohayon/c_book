#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);
int gettoken(void);
int findnext(void);

int tokentype;           // type of last token
char token[MAXTOKEN];    // last token string
char name[MAXTOKEN];     // identfier name
char datatype[MAXTOKEN]; // data type = char, int, etc.
char out[1000];          // output string
int prev = 0;

/* convert word descriptions to declartion */
int main() {
  int type;
  char temp[MAXTOKEN];

  while (gettoken() != EOF) {
    strcpy(out, token);
    while ((type = gettoken()) != '\n')
      if (type == PARENS || type == BRACKETS)
        strcat(out, token);
      else if (type == '*') {
        if ((type = findnext()) == PARENS || type == BRACKETS)
          sprintf(temp, "(*%s)", out);
        else
          sprintf(temp, "*%s", out);
        strcpy(out, temp);
      } else if (type == NAME) {
        sprintf(temp, "%s %s", token, out);
        strcpy(out, temp);
      } else
        printf("invalid input at %s\n", token);

    printf("%s\n", out);
  }
  return 0;
}

/* dcl: parse a declartor */
void dcl(void) {
  int ns;
  for (ns = 0; gettoken() == '*';) /* count * s */
    ns++;
  dirdcl();
  while (ns-- > 0)
    strcat(out, " pointer to");
}

/* drdcl: parse direct declarator */
void dirdcl(void) {
  int type;
  if (tokentype == '(') {
    dcl();
    if (tokentype != ')')
      printf("error: missing )\n");
  } else if (tokentype == NAME)
    strcpy(name, token);
  else
    printf("error:: expected name or (dcl)\n");

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

  if (prev) {
    prev = 0;
    return tokentype;
  }

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

int findnext(void) {
  int type = gettoken();
  prev = 1;
  return type;
}
