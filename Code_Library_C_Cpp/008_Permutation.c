#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
char settled[500];

void per(char a[], int len, int length)
{
	if (len == 0) 
	{
		for (int i = 0; i < length; ++i)
			printf("%c", settled[i]);
		printf("\n");
	}
	else
		for (int i = 0; i < len; ++i)
		{
			settled[length - len] = a[i];
			char temp[500];
			for (int j = 0; j < len; ++j)
			{
				if (j <= i) temp[j] = a[j];
				else temp[j - 1] = a[j];
			}
			per(temp, len - 1, length);
		}
}

int main()
{
	char a[500];
	scanf("%s", a); // In C11, "gets()" has been deleted.
	int count = strlen(a);
	per(a, count, count);
	return 0;
}
