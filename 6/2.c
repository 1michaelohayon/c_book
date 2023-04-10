#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100
#define DEFAULT_N 6

struct tn {
  char *word;
  int countn; // counts identical words based on the first 6 chars
  bool identical;
  struct tn *left;
  struct tn *right;
};

struct tn *addtree(struct tn *, char *, bool *identical);

int getword(char *, int);
void treeprint(struct tn *);
int getword(char *, int);

unsigned n_occur = DEFAULT_N; // n chars to compare, defaults to 6 if no arg

int main(int argc, char *argv[]) {
  if (argc > 1) {
    char *p = argv[1];
    if (*p == '-')
      p++;
    for (; *p != '\0'; p++)
      if (!isdigit(*p)) {
        printf("error: arg is not a number\n");
        return 1;
      }
    n_occur = abs(atoi(argv[1]));
  }
  struct tn *root;
  bool tmp = false;

  char word[MAXWORD];
  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]))
      root = addtree(root, word, &tmp);
  treeprint(root);

  return 0;
}

/* talloc: make a tnode */
struct tn *talloc(void) { return (struct tn *)malloc(sizeof(struct tn)); }

// identical on the first n chars, but diff somewhere thereafter
int strncmp_then_dif(char *s, struct tn *p, int n, bool *identical) {
  int i;
  char *t = p->word;

  for (i = 0; *s == *t; i++, s++, t++)
    if (*s == '\0')
      return 0;
  if (i >= n) { // if identical in the first n chars
    *identical = true;
    p->identical = true;
  }
  return *s - *t;
}

/* add a node with w, at or below  */
struct tn *addtree(struct tn *p, char *w, bool *identical) {
  int cond;
  if (p == NULL) {
    p = talloc();
    p->word = strdup(w);
    p->countn = 1;
    p->identical = *identical;
    p->left = p->right = NULL;

  } else if ((cond = strncmp_then_dif(w, p, n_occur, identical)) < 0)
    p->left = addtree(p->left, w, identical);
  else // greater than into right subtree
    p->right = addtree(p->right, w, identical);
  return p;
}

/* in-order print of tree */
void treeprint(struct tn *p) {
  if (p != NULL) {
    treeprint(p->left);
    if (p->identical)
      printf("%4d %s\n", p->countn, p->word);
    treeprint(p->right);
  }
}
