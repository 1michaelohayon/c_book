#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1000
#define TAB 4

int getlinex(char line[], int maxline);
void foldline(char line[], int len);

/* replaces all possible spaces with tabs, if there are 5 spaces and tab is set to 4, the result is 1 tab 1 space*/
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
		if (line[i] == ' ')
		{
			int x = 0;
			while (line[i + x] == ' ' || line[i + x] == '\0')
				x++;
			int tabs = x / TAB;
			i += x - 1;
			while (x > 0)
			{
				if (tabs > 0)
				{
					putchar('\t');
					tabs--;
					x -= TAB;
				}
				else
				{
					putchar(' ');
					x--;
				}
			}
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
