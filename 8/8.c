#include "malloc.c"

unsigned bfree(char *p, unsigned n) {
  Header *hp;

  if (n < sizeof(Header))
    return 0;
    
  hp = (Header *)p;
  hp->s.size = n / sizeof(Header);

  freem((void *)(hp+1));
  return hp->s.size;
}