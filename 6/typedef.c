#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct tnode *Treeptr;

typedef struct tnode {
    char *word;
    int count;
    Treeptr left;
    Treeptr right;
} Treenode;

Treeptr talloc(void) { return (Treeptr)malloc(sizeof(Treenode)); }

/* PEI: pointer to a function (of two char* args) returning int */
typedef int (*PEI)(char *, char *);

int dummy(PEI x) {
    if (x == 0)
        return 1;
    return 0;
}

int numcmp(char *, char *);
int strcmpx(char *, char *);

int main(int argc, char *argv[]) {

    PEI cmp = isdigit(*argv[1]) ? numcmp : strcmpx;
    int res = dummy(cmp);

    typedef int Length;
    typedef char *String;

    String str = "Hello World";
    Length len = 283;

    printf("%s, %d\n", str, len);
    return 0;
}

int numcmp(char *s1, char *s2) {
    double v1 = atof(s1), v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

int strcmpx(char *s, char *t) {
    int i;
    for (i = 0; s[i] == t[i]; i++)
        if (!s[i])
            return 0;
    return s[i] - t[i];
}