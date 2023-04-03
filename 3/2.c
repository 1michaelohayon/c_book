#include <stdio.h>

void escape(char s[], char t[]) {
  int i, j;
  for (i = j = 0; s[i] != '\0'; i++, j++)
    switch (s[i]) {
    case '\t':
      t[j++] = '\\';
      t[j] = 't';
      break;
    case '\n':
      t[j++] = '\\';
      t[j] = 'n';
      break;
    default:
      t[j] = s[i];
    }
  t[j] = '\0';
}

int main() {
  char s[20] = "hey\nworld\t123";
  char t[20];

  escape(s, t);

  printf("%s\n", s);
  printf("%s\n", t);
}