#include <stdio.h>

void expend(char s1[], char s2[]) {
  int i, x = 0;

  for (int i = 0; s1[i] != '\0'; i++) {
    if (s1[i + 1] == '-') {
      for (int j = 0; s1[i] + j <= s1[i + 2]; j++, x++) {
        if (s2[x - 1] == s1[i] + j)
          j++;
        s2[x] = s1[i] + j;
      }
    }
  }

  s2[x] = '\0';
}

void expend2(char s1[], char s2[]) {
  char c;
  int i, j;
  i = j = 0;
  while ((c = s1[i++]) != '\0')
    if (s1[i] == '-' && s1[i + 1] >= c) {
      i++;
      while (c < s1[i])
        s2[j++] = c++;
    } else
      s2[j++] = c;

  s2[j] = '\0';
}

int main() {

  char s1[] = "abcx";
  char s2[1000];

  // both expend and expend2 works
  expend2("a-z", s2);
  printf("%s\n", s2);
  expend2("1-9", s2);
  printf("%s\n", s2);
  expend2("a-c-z", s2);
  printf("%s\n", s2);
  expend2("a-cf-z", s2);
  printf("%s\n", s2);
  expend2("1-37-9", s2);
  printf("%s\n", s2);
}

// unused
int containstr(char x[], char s[]) {
  for (int i = 0; s[i] != '\0'; i++) {
    if (s[i] == x[0]) {
      int j;
      for (j = 0; x[j] != '\0'; j++)
        if (x[j] != s[i + j]) {
          j = 0;
          break;
        }
      if (x[j] == '\0')
        return 1;
    }
  }
  return 0;
}
