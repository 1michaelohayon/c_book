#include "calc.h"
#include <stdio.h>
#define MAXVAL 100

static int sp = 0;
static double val[MAXVAL];

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
