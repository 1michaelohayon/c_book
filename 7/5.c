#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXOP 1000
#define MAXVARS 26
#define NUMBER '0'
#define VAR '1'

enum mfunc {
    SIN = 'S',
    POW = '^',
    EXP = 'E',
    CLEAR = 'C',
    SWAP = 'P',
    PEEK = '?',
    ASSIGN = '=',
};

int args = 0;

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

        printf("\t%f\n", peek());
    }
    return 0;
}

bool bufstate = false;
/* getop: get next operator or numeric operand */
int getop(char s[]) {
    static char buff[MAXOP], *pb;
    if (!bufstate) {
        scanf("%s", buff);
        bufstate = true;
        pb = buff;
    }

    if (isdigit(*pb)) {
        while (isdigit(*pb))
            *s++ = *pb++;

        if (*pb == '\0') {
            bufstate = false;
        }
        *s = '\0';
        return NUMBER;
    }

    if (*pb == '\0' || *(pb + 1) == '\0') {
        bufstate = false;
    }
    *s = *pb++;
    return *s;
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
void clear() { sp = 0; }
void swaptop() {
    if (sp < 2)
        printf("error: minimum of 2 elements are required for a swap\n");
    else {
        int a = pop();
        int b = pop();
        push(a);
        push(b);
    }
    return;
}
double peek(void) {
    if (sp > 0)
        return val[sp - 1];
    else
        return 0.0;
}
