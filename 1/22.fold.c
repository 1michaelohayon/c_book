#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1000
#define LINEBREAK 40

int getlinex(char line[], int maxline);
void foldline(char line[], int len);

int main()
{
	char line[MAXLINE];
	;
	int len;
	while ((len = getlinex(line, MAXLINE)) > -1)
	{

		foldline(line, len);
	}
}

void foldline(char line[], int len)
{
	int l = 0;
	int count = 0;

	for (int r = 0; r < len; r++)
	{
		if (line[r] == ' ' || line[r] == '\0' || line[r] == '\n')
		{
			count += r - l;
			if (count > LINEBREAK)
			{
				putchar('\n');
				l++;
				count = 0;
			}
			while (l < r)
			{
				putchar(line[l]);
				l++;
			}
		}
	}
	if (l > 0)
		putchar('\n');
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
