#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1000
#define SPACES 4

int getlinex(char line[], int maxline);
void foldline(char line[], int len);

int main()
{
	char line[MAXLINE];
	;
	int len;
	while ((len = getlinex(line, MAXLINE)) > -1)
		foldline(line, len);
}

void foldline(char line[], int len)
{
	for (int i = 0; i < len; i++)
		if (line[i] == '\t')
		{
			for (int x = 0; x < SPACES; x++)
				putchar(' ');
		}
		else
		{
			putchar(line[i]);
		}
}

/* getline: read a line into s, return length */
int getlinex(char s[], int lim)
{
	int i, c;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		s[i] = c;

	if (c == '\n')
		s[i++] = c;

	s[i] = '\0';

	return i;
}
