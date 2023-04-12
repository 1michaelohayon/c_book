#include <stdarg.h>
#include <stdio.h>
  
void minprintf(char *fmt, ...) {
  va_list ap; /* points to each unnamed arg in turn */
  char *p, *sval;
  int ival;
  double dval;

  va_start(ap, fmt); /* make ap point 1st unnamed arg */

  for (p = fmt; *p; p++) {
    if (*p != '%') {
      putchar(*p);
      continue;
    }
    switch (*++p) {
    case 'i':
    case 'd':
      ival = va_arg(ap, int);
      printf("%d", ival);
      break;
    case 'f':
      dval = va_arg(ap, double);
      printf("%f", dval);
      break;
    case 's':
      for (sval = va_arg(ap, char *); sval; sval++)
        putchar(*sval);
      break;
    case 'x':
    case 'X':
      ival = va_arg(ap, int);
      printf("%x", ival);
      break;
    case 'o':
      ival = va_arg(ap, int);
      printf("%o", ival);
      break;
    case 'c':
      putchar(va_arg(ap, int));
      break;
    default:
      putchar('%');
      putchar(*p);
      break;
    }
  }
  va_end(ap); /* clean when done */
}

int main() {
  minprintf("hello world %c\n", 'a');
}

