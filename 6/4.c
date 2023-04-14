#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100
#define MAXLEN 500

struct tnode {  // tree node
    char *word; // points to the text
    int count;
    struct tnode *left;  // left child
    struct tnode *right; // right child
};
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
void isort(struct tnode *v[], int len);

struct tnode *arr[MAXLEN];
int len = 0;
void tntoArr(struct tnode *root) {
    if (root != NULL) {
        tntoArr(root->left);
        arr[len++] = root;
        tntoArr(root->right);
    }
}

/* word frequency count */
int main() {
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);
    tntoArr(root);
    isort(arr, len);
    while (len--)
        printf("%4d %s\n", arr[len]->count, arr[len]->word);

    return 0;
}

/* talloc: make a tnode */
struct tnode *talloc(void) {
    return (struct tnode *)malloc(sizeof(struct tnode));
}

/* add a node with w, at or below  */
struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;    // repeated word
    else if (cond < 0) // less than into left subtree
        p->left = addtree(p->left, w);
    else // greater than into right subtree
        p->right = addtree(p->right, w);

    return p;
}

/* in-order print of tree */
void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

void swap(struct tnode *v[], int a, int b) {
    struct tnode *tmp = v[a];
    v[a] = v[b];
    v[b] = tmp;
}

void isort(struct tnode *v[], int len) {
    for (int i = 1; i < len; i++) {
        int j = i - 1;
        while (j >= 0 && v[j + 1]->count < v[j]->count) {
            swap(v, j, j + 1);
            j--;
        }
    }
}
