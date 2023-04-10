#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100

struct linklist {
  int ln;
  struct linklist *next;
};

struct tnode {
  char *word;
  struct linklist *lines;
  struct tnode *left;
  struct tnode *right;
};
struct tnode *addtree(struct tnode *, char *, int);
int getword(char *, int);
int filter(char *);
void treeprint(struct tnode *p);

int main() {
  struct tnode *root = NULL;
  char word[MAXWORD];
  int ln = 1;

  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]) && filter(word) == -1)
      root = addtree(root, word, ln);
    else if (word[0] == '\n')
      ln++;

  treeprint(root);
  return 0;
}

/* talloc: make a tnode */
struct tnode *talloc(void) {
  return (struct tnode *)malloc(sizeof(struct tnode));
}
/* lalloc: make a linkedlist node */
struct linklist *lalloc(void) {
  return (struct linklist *)malloc(sizeof(struct linklist));
}

void addline(struct tnode *p, int line_n) {
  struct linklist *temp = p->lines;

  while (temp->next != NULL && temp->ln != line_n)
    temp = temp->next;
  if (temp->ln != line_n) {
    temp->next = lalloc();
    temp->next->ln = line_n;
    temp->next->next = NULL;
  }
}

struct tnode *addtree(struct tnode *p, char *w, int ln) {
  int cond;
  if (p == NULL) {
    p = talloc();
    p->word = strdup(w);
    p->lines = lalloc();
    p->lines->ln = ln;
    p->lines->next = NULL;
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0)
    addline(p, ln);
  else if (cond < 0)
    p->left = addtree(p->left, w, ln);
  else
    p->right = addtree(p->right, w, ln);
  return p;
}

void treeprint(struct tnode *p) {
  struct linklist *temp;
  if (p != NULL) {
    treeprint(p->left);
    printf("%10s: ", p->word);
    for (temp = p->lines; temp != NULL; temp = temp->next)
      printf("%4d ", temp->ln);
    printf("\n");
    treeprint(p->right);
  }
}

int filter(char *w) {
  static char *nw[] = {"a", "an", "and", "are", "in", "is", "of", "or", "that", "the", "this", "to"};

  int cond, mid;
  int low = 0;
  int high = sizeof(nw) / sizeof(char *) - 1;

  while (low <= high) {
    mid = low + (high - low) ;
    if ((cond = strcmp(w, nw[mid])) < 0)
      high = mid-1;
    else if (cond > 0)
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}
