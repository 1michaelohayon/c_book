#include <stdio.h>

char lower(char c) { return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c; }

int main() {
  char str[] = "My NaMe Is MiChael";
  for (int i = 0; str[i] != '\0'; putchar(lower(str[i++])))
    ;

  return 0;
}