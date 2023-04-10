#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMBER 0

void push(double f);
double pop(void), peek(void);
int getop(char *s);

/* reverse Polish Calculator */
int main(int argc, char *argv[]) {
  int sign = 1;
  char *s;
  double op2;
  while (--argc > 0 && (s = *++argv)) {
    switch (getop(s)) {
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '%':
      op2 = pop();
      if (op2 != 0.0)
        push(fmod(pop(), op2));
      else {
        printf("error: zero divisor\n");
        return 1;
      }
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0)
        push(pop() / op2);
      else {
        printf("error: zero divisor\n");
        return 1;
      }
      break;
    default: 
        printf("error: unknown command\n");
        return 1;
    }
  }
  printf("\t%.2f\n", pop());
  return 0;
}

int getop(char *s) {
  if (strlen(s) == 1 && !isdigit(*s))
    return *s;
  
  return NUMBER;
}


#define MAXVAL 100
static int sp = 0;
static double val[MAXVAL];

void push(double f) {
  if (sp < MAXVAL) {
    val[sp++] = f;
  } else
    printf("error: stack fullm can't push %g\n", f);
}

double pop(void) {
  if (sp > 0)
    return val[--sp];
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

