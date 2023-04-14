#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXWORD 100
#define HASHSIZE 101

struct nlist {
    struct nlist *next;
    char *key;
    char *val;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;

    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s) {
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->key) == 0)
            return np;
    return NULL;
}

struct nlist *install(char *key, char *val) {
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(key)) == NULL) {
        np = (struct nlist *)malloc(sizeof(*np));
        if (np == NULL || (np->key = strdup(key)) == NULL)
            return NULL;
        hashval = hash(key);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else
        free((void *)np->val);

    if ((np->val = strdup(val)) == NULL)
        return NULL;
    return np;
}

void undef(char *key) {
    int h;
    struct nlist *prev, *np;

    prev = NULL;
    h = hash(key);
    for (np = hashtab[h]; np != NULL; np = np->next) {
        if (strcmp(key, np->key) == 0)
            break;
        prev = np;
    }
    if (np != NULL) {
        if (prev == NULL)
            hashtab[h] = np->next;
        else
            prev->next = np->next;

        free((void *)np->key);
        free((void *)np->val);
        free((void *)np);
    }
}

int main() {
    int getword(char *word, int lim);
    int getch(void);
    void ungetch(int);

    char word[MAXWORD];
    enum { DEFINE, KEY, VAL };

    int anticipate = DEFINE;

    char key[MAXWORD];

    while (getword(word, MAXWORD) != EOF) {

        if (anticipate == DEFINE && word[0] == '#' &&
            strcmp(word, "#define") == 0)
            anticipate = KEY;
        else if (anticipate == KEY) {
            if (!isalpha(word[0])) {
                printf("error: #define incorrect usage, must begin with a "
                       "letter\n");
                return 1;
            }
            strcpy(key, word);
            anticipate = VAL;
        } else if (anticipate == VAL) {
            install(key, word);
            anticipate = DEFINE;
        }

        if (isalpha(word[0]) && lookup(word) != NULL) {
            printf("%s", lookup(word)->val);
        } else
            printf("%s", word);

        char c;
        if (isspace(c = getch()))
            putchar(' ');
        ungetch(c);
    }
    return 0;
}