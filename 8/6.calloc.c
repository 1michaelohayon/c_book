#include "malloc.c"
#include <stdio.h>

void *contiguous_alloc(unsigned n, unsigned size) {
  char *p, *arr;
  unsigned i;
  if ((p = arr = memalloc(i = size * n)) == NULL)
    return NULL;

  while(i--)
    *arr++ = 0;
  return p;
}

int main() {

  int len = 8;
  int *arr = (int *)contiguous_alloc(len, sizeof(int));

  for (int i = 0; i < len; i++)
    printf("%d\n", arr[i]);
}
