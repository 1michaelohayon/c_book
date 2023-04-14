#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define abs(x) ((x) < 0 ? -(x) : (x))

int atoi(char *s) {
    char *s_b = s;
    while (isspace(*s)) // skip white space
        s++;
    int sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')
        s++;

    int n;
    for (; isdigit(*s); s++)
        n = 10 * n + (*s - '0');
    s = s_b;
    return sign * n;
}
void swap(char *pa, char *pb) {
    char tmp = *pa;
    *pa = *pb;
    *pb = tmp;
}
void reverse(char *s) {
    char *rp = &s[strlen(s) - 1];
    while (s < rp)
        swap(s++, rp--);
}
void itoa(int n, char *s) {
    char *ps = s;
    int sign = n;

    do {
        *s++ = abs(n % 10) + '0';
    } while ((n /= 10) != 0);
    if (sign < 0)
        *s++ = '-';
    *s = '\0';
    reverse(ps);
}
double atof(char *s) {
    double val, power;
    int exp, i, sign;

    for (; isspace(*s); s++)
        ;

    sign = (*s == '-') ? -1 : 1;

    if (*s == '+' || *s == '-')
        s++;

    for (val = 0.0; isdigit(*s); s++)
        val = 10.0 * val + (*s - '0');

    if (*s == '.')
        s++;

    for (power = 1.0; isdigit(*s); s++) {
        val = 10.0 * val + (*s - '0');
        power *= 10.0;
    }

    return sign * val / power;
}

int strindex(char s[], char t[]) {
    char *sbeg = s;
    char *ps, *pt;
    for (; *s; s++) {
        for (ps = s, pt = t; *pt && *ps == *pt; pt++, ps++)
            ;
        if (pt > t && *pt == '\0')
            return s - sbeg;
    }
    return -1;
}

// getop: getop_6/getop.c

int getlinex(char *s, int lim) {
    int c;
    char *ps = s;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - ps;
}

int main() {

    int a[] = {1, 72, 23, 4, 5};
    int *pa = &a[0];

    ++*pa;

    printf("%d\n", *pa);

    printf("%d\n", atoi("-542"));

    char s[] = "hello";
    reverse(s);
    printf("%s\n", s);

    char b[20];
    itoa(50326, b);

    printf("%s\n", b);

    char s3[] = "hello World";
    char t3[] = "orld";
    printf("strindex:%d\n", strindex(s3, t3));

    printf("%2.f\n", atof("1948"));

#define LINEMAX 100
    char sbuf[LINEMAX];
    while (getlinex(sbuf, LINEMAX) > 1)
        printf("sbuff: %s\n", sbuf);

    return 0;
}