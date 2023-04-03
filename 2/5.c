#include <stdio.h>

int any(char s1[], char s2[]) {
  int i, j, k;

  for (i = 0; s1[i] != '\0'; i++)

    for (j = 0; s2[j] != '\0'; j++)
      if (s1[i] == s2[j])
        return i;

  return -1;
}

int main() {
  char s1[] = "abc";
  char s2[] = "dbcd";

  printf("%d\n", any(s1, s2));
}