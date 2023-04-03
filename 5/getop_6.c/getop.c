#include "calc.h"
#include <ctype.h>
#include <stdio.h>

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char *s) {
  int c;
  while ((*s = c = getch()) == ' ' || c == '\t')
    ;
  *(s + 1) = '\0';

  if (!isdigit(c) && c != '.' && (c != '-'))
    return c;

  int i = 0;
  if (c == '-') {
    if (isdigit(c = getch()) || c == '.')
      *++s = c;
    else if (c != EOF) {
      ungetch(c);
      return '-';
    }
  }
  if (isdigit(c))
    while (isdigit(*++s = c = getch()))
      ;

  if (c == '.')
    while (isdigit(*++s = c = getch()))
      ;
  *s = '\0';
  if (c != EOF)
    ungetch(c);
  return NUMBER;
}
