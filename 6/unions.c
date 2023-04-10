#include <stdio.h>

union u_tag {
  int ival; 
  float fval;
  char *sval;

} u;

int main() {
  union u;
  // u.fval = 7.4;
  // u.sval = "hello";
  u.ival = 5;

  enum { INT, FLOAT, STRING };

  int utype = INT;
  if (utype == INT)
    printf("%d\n", u.ival);
  else if (utype == FLOAT)
    printf("%f\n", u.fval);
  else if (utype == STRING)
    printf("%s\n", u.sval);
  else
    printf("bad type %d, in utype\n", utype);
}