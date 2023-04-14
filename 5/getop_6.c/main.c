#include "calc.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXOP 1000

int getop(char[]);
void push(double f), clear(void), swaptop(void), mathfunc(char s[]);
double pop(void), peek(void);

/* reverse Polish Calculator */
int main() {
    double vars[MAXVARS];
    int type, lastType;
    double op2, v;
    char s[MAXOP];
    while ((type = getop(s)) != EOF) {
        switch (type) {

        case NUMBER:
            push(atof(s));
            break;
        case SIN:
            push(sin(pop()));
            break;
        case POW:
            op2 = pop();
            push(pow(pop(), op2));
            break;
        case EXP:
            push(exp(pop()));
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
            else
                printf("error: zero divisor\n");
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            break;
        case '\n':
            if (lastType != PEEK && lastType != CLEAR && lastType != SWAP &&
                lastType != ASSIGN) {
                v = pop();
                printf("\t%.8g\n", v);
            }
            break;
        case CLEAR:
            clear();
            break;
        case SWAP:
            swaptop();
            break;
        case PEEK:
            printf("\t%.8g\n", peek());
            break;
        case ASSIGN:
            pop();
            if (islower(lastType))
                vars[lastType - 'a'] = pop();
            else
                printf("error no variable\n");
            break;
        default:
            if (islower(type))
                push(vars[type - 'a']);
            else if (type == 'V')
                push(v);
            else
                printf("error: unknown command %s\n", s);
            break;
        }
        lastType = type;
    }
    return 0;
}
