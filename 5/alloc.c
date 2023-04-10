#define ALLOCSIZE 10000 /* size of available space */
#include <string.h>

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n) {                        /* return pointer to n characters */
  if (allocbuf + ALLOCSIZE - allocp >= n) { // if it fits
    allocp += n;
    return allocp - n; // old p
  } else               // not enough room
    return NULL;
}

void afree(char *p) { /* free storage pointed to by p *?*/
  if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
    allocp = p;
}

