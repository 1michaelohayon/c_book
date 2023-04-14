#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#define LOCALFMT 100

int miniscanf(char *fmt, ...) {
    va_list ap;
    char *p, *sval;
    char localfmt[LOCALFMT];

    va_start(ap, fmt);
    int c, i = 0, match = 0, *ival;
    char *cval;
    unsigned *uval;
    double *dval;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            localfmt[i++] = *p;
            continue;
        }

        localfmt[i++] = '%';
        while (*(p + 1) && !isalpha(*(p + 1)))
            localfmt[i++] = *++p;

        localfmt[i++] = *(p + 1);
        localfmt[i] = '\0';

        switch (*++p) {
        case 'd':
        case 'i':
            ival = va_arg(ap, int *);
            scanf(localfmt, ival);
            match++;
            break;
        case 'c':
            cval = va_arg(ap, char *);
            scanf(localfmt, cval);
            match++;

            break;
        case 'x':
        case 'X':
        case 'u':
        case 'o':
            uval = va_arg(ap, unsigned *);
            scanf(localfmt, uval);
            match++;

            break;
        case 'f':
            dval = va_arg(ap, double *);
            scanf(localfmt, dval);
            match++;

            break;
        case 's':
            sval = va_arg(ap, char *);
            scanf(localfmt, sval);
            match++;
            break;
        }

        i = 0;
    }
    va_end(ap);
    return match;
}

int main() {
    int n;
    char c;
    char s[20];
    float f;
    printf("matches: %d\n", miniscanf("%d %c %s %f", &n, &c, &s, &f));
    printf("n: %d\n", n);
    printf("c: %c\n", c);
    printf("s:%s\n", s);
    printf("f:%f\n", f);
}