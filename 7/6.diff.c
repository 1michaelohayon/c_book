#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("%s usage: require 2 files\n", argv[0]);
    return 1;
  }

  int line_number = 1;
  FILE *fp1, *fp2;
  if ((fp1 = fopen(argv[1], "r")) == NULL) {
    printf("%s: can't open %s\n", argv[0], argv[1]);
    return 1;
  }
  if ((fp2 = fopen(argv[2], "r")) == NULL) {
    printf("%s: can't open %s\n", argv[0], argv[2]);
    return 1;
  }

  char line1[MAXLINE], line2[MAXLINE];

  for (;   
       fgets(line1, MAXLINE, fp1) != NULL && fgets(line2, MAXLINE, fp2) != NULL;
       ++line_number)
    if (strcmp(line1, line2)) 
      printf("line %d:\n----\n>%s\n<%s\n----\n", line_number, line1, line2);
    
  fclose(fp1);
  fclose(fp2);
  return 0;
}