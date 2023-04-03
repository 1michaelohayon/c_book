#include <stdio.h>
#define MAXLINE 1000
#define INLINE 1
#define OUT 0
#define IN 2

int getlinex(char s[], int lim);

/* removes comments for a single line that starts with //   and entire blocks that are contained inside like this one */
int main()
{
	int c;
	char load = '\0';
	int state = OUT;
	char pair[MAXLINE];

	while ((c = getchar()) != EOF)
	{
		if (c == '/' && !load && state == OUT)
		{
			load = '/';
			continue;
		}

		if (c == '/' && load == '/' && state == OUT)
		{
			state = INLINE;
			load = '\0';
		}
		else if (c == '*' && load == '/' && state == OUT)
		{
			state = IN;
			load = '\0';
			continue;
		}
		else if (c != '/' && load == '/' && state == OUT)
		{
			putchar(load);
			load = '\0';
		}

		if (state == IN)
		{
			if (c == '*')
				load = '*';
			else if (load == '*' && c == '/')
			{
				state = OUT;
				load = '\0';
			}
		}
		else if (state == INLINE && c == '\n')
			state = OUT;

		else if (state == OUT)
			putchar(c);
	}
}

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
