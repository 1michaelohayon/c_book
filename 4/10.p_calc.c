#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

double vars[MAXVARS];

int getop(char[]);
void push(double f), clear(void), swaptop(void), mathfunc(char s[]);
double pop(void), peek(void);

/* reverse Polish Calculator */
int main() {
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

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

/* push: push f onto the stack */
void push(double f) {
    if (sp < MAXVAL) {
        val[sp++] = f;
    } else
        printf("error: stack fullm can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}
/* clear stack */
void clear() { sp = 0; }

/* swap top two elements */
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

int getlinex(char s[], int lim) {
    int c, i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}
#define MAXLINE 100
int j = 0;
char line[MAXLINE];

/* getop: get next operator or numeric operand */
int getop(char s[]) {
    int c, i;
    if (line[j] == '\0') {
        if (getlinex(line, MAXLINE) == 0)
            return EOF;
        else
            j = 0;
    }

    while ((s[0] = c = line[j++]) == ' ' || c == '\t')
        ;

    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-')
        return c;
    i = 0;
    if (c == '-') {
        if (isdigit(c = line[j++]) || c == '.')
            s[++i] = c;
        else if (c != EOF) {
            j--;
            return '-';
        }
    }
    if (isdigit(c))
        while (isdigit(s[++i] = c = line[j++]))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = line[j++]))
            ;

    s[i] = '\0';
    j--;
    return NUMBER;
}
