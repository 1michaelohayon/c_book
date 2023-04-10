#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXTOKEN 100
#define SIZE(a) sizeof((a)) / sizeof((a)[0])


enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);
void paramdcl(void);
int gettoken();
void dclspc(char *);
bool typespc(void);
bool typeqaul(void);
void error(const char *);

int tokentype;           // type of last token
char token[MAXTOKEN];    // last token string
char name[MAXTOKEN];     // identfier name
char datatype[MAXTOKEN]; // data type = char, int, etc.
char out[1000];          // output string
bool prev = false;
int paramtype;

int main(void) {
  while (gettoken() != EOF) { 
    if (tokentype == '\n')    
      continue;
    datatype[0] = '\0';
    dclspc(datatype); 
    name[0] = out[0] = '\0';
    dcl();
    if (tokentype != '\n')
      printf("%s", "syntax error\n");
    else if (!prev)
      printf("%s: %s %s\n", name, out, datatype);
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

/* dirdcl: parse a direct declarator */
void dirdcl(void) {
  int type;
  if (tokentype == '(') { /* ( dcl ) */
    dcl();
    if (tokentype != ')')
      error("error: missing )\n");
  } else if (tokentype == NAME) {
    if (!name[0])
      strcpy(name, token);
  } else {
    if (paramtype)
      prev = true;
    else
      error("error: expected name or (dcl)\n");
  }
  while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(')
    if (type == PARENS)
      strcat(out, " function returning");
    else if (type == '(') {
      strcat(out, " function expecting");
      ;
      paramdcl();
      strcat(out, " and returning");
    } else {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
}

void paramdcl(void) {
  char temp[MAXTOKEN];
  do {
    temp[0] = '\0';
    gettoken();
    dclspc(temp);
    paramtype = 1;
    dcl();
    paramtype = 0;
    if (tokentype == ',')
      strcat(temp, ",");
    strcat(out, " ");
    strcat(out, temp);
  } while (tokentype == ',');
  if (tokentype != ')')
    error("missing ) in parameter declaration\n");
}

void dclspc(char *type) {
  int count;

  for (count = 0; tokentype == NAME && (typespc() || typeqaul()); ++count) {
    if (count)
      strcat(type, " ");
    strcat(type, token);
    gettoken();
  }
  prev = true;
}

bool typespc(void) {
  int isequal(const void *, const void *), combination_chk();
  static const char *typetab[] = {"char", "double", "float", "int", "void"};

  if (!bsearch(&token, typetab, SIZE(typetab), sizeof(char *), isequal))
    return false;
  return true;
}

bool typeqaul(void) {
  int isequal(const void *, const void *), combination_chk();
  static const char *qualtab[] = {"const", "volatile"};

  if (!bsearch(&token, qualtab, SIZE(qualtab), sizeof(char *), isequal))
    return false;
  return true;
}

int isequal(const void *s, const void *t) {
  return strcmp((char *)s, *(char **)t);
}

void error(const char *msg) {
  printf("%s", msg);
  prev = true;
}

int gettoken(void) {
  int c, getch(void);
  void ungetch(int);
  char *p = token;

  if (prev == true) {
    prev = false;
    return tokentype;
  }
  while ((c = getch()) == ' ' || c == '\t')
    ;
  if (c == '(') {
    if ((c = getch()) == ')') {
      strcpy(token, "()");
      return tokentype = PARENS;
    }
    ungetch(c);
    return tokentype = '(';
  }
  if (c == '[') {
    for (*p++ = c; (*p++ = getch()) != ']';)
      ;
    *p = '\0';
    return tokentype = BRACKETS;
  }
  if (isalpha(c)) {
    for (*p++ = c; isalnum(c = getch());)
      *p++ = c;
    *p = '\0';
    ungetch(c);
    return tokentype = NAME;
  }
  return tokentype = c;
}
