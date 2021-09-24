#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

char char_plus(char a, char b, char c, char *d)
{
	int k = (int)a + (int)b + (int)c - 144;
	if (k > 9) *d = '1';
	return (char)(k % 10 + 48);
}

void string_plus(char s1[], char s2[], int length, int space_s1, int space_s2)
{
	int less_space;
	if (space_s1 > space_s2)
	{
		less_space = space_s2;
		for (int i = space_s2; i < space_s1; i++)
			s1[i] = '0';
	}
	else if (space_s2 > space_s1)
	{
		less_space = space_s1;
		for (int i = space_s1; i < space_s2; i++)
			s2[i] = '0';
	}
	else
		less_space = space_s1;

	char c[1001], result[1000];
	c[1000] = '0';
	for (int i = 0; i <= length; i++) 
	{
		c[i] = result[i] = '0';
	}
	for (int i = length; i >= less_space; i--) 
		result[i] = char_plus(s1[i], s2[i], c[i + 1], &c[i]);

	for (int i = space_s1; i <= length; i++)
		printf("%c", s1[i]);
	printf(" + ");
	for (int i = space_s2; i <= length; i++)
		printf("%c", s2[i]);
	printf("\n= ");
	if (c[less_space] == '1') printf("1");
	for (int i = less_space; i <= length; i++)
		printf("%c", result[i]);
	printf("\n");
}

char char_minus(char a, char b, char c, char *d)
{
	int k = (int)a - (int)b - (int)c + 48;
	if (k < 0) *d = '1';
	return (char)((k + 10) % 10 + 48);
}

void string_minus(char s1[], char s2[], int length, int space_s1, int space_s2)
{
	int less_space;
	if (space_s1 > space_s2) 
	{
		less_space = space_s2;
		for (int i = space_s2; i < space_s1; i++)
			s1[i] = '0';
	}
	else if (space_s2 > space_s1)
	{
		less_space = space_s1;
		for (int i = space_s1; i < space_s2; i++)
			s2[i] = '0';
	}
	else
		less_space = space_s1;

	char c[1001], result[1000];
	c[1000] = '0';
	for (int i = 0; i <= length; i++)
	{
		c[i] = result[i] = '0';
	}
	
	for (int i = space_s1; i <= length; i++) 
		printf("%c", s1[i]);
	printf(" - ");
	for (int i = space_s2; i <= length; i++)
		printf("%c", s2[i]);
	printf("\n= ");
	
	if (strcmp(s1, s2) == 0) printf("0");
	else if (strcmp(s1, s2) > 0)
	{
		for (int i = length; i >= less_space; i--)
			result[i] = char_minus(s1[i], s2[i], c[i + 1], &c[i]);
		int j;
		for (j = 0; j <= length; j++)
			if (result[j] != '0') break;
		for (int i = j; i <= length; i++)
			printf("%c", result[i]);
	}
	else
	{
		printf("-");
		for (int i = length; i >= less_space; i--)
			result[i] = char_minus(s2[i], s1[i], c[i + 1], &c[i]);
		int j;
		for (j = 0; j <= length; j++)
			if (result[j] != '0') break;
		for (int i = j; i <= length; i++)
			printf("%c", result[i]);
	}
	printf("\n");
}

char charXchar(char a, char b, char c, char *d)
{
	int k = ((int)a - 48)* ((int)b - 48) + (int)c - 48;
	*d = (char)((k - k % 10) / 10 + 48);
	return (char)(k % 10 + 48);
}

void stringXstring(char s1[], char s2[], int length, int space_s1, int space_s2)
{
	char result[2001];
	for (int i = 0; i <= 2 * length + 2; i++)
	{
		result[i] = '0';
	}

	for (int i = length; i >= space_s2; i--)
	{
		char temp_1[1001], temp_0[1002];
		for (int j = 0; j <= length + 1; j++)
		{
			temp_1[j] = temp_0[j] = '0';
		}
		for (int j = length; j >= space_s1; j--)
			temp_1[j + 1] = charXchar(s1[j], s2[i], temp_0[j + 1], &temp_0[j]);
		if (temp_0[space_s1] != '0') temp_1[space_s1] = temp_0[space_s1];
		for (int j = 0; j <= length + 2; j++)
		{
			temp_0[j] = '0';
		}
		for (int j = length + 1; j >= space_s1; j--)
			result[i + j + 1] = char_plus(result[i + j + 1], temp_1[j], temp_0[j + 1], &temp_0[j]);
		if (temp_0[space_s1] == '1') result[i + space_s1] = '1';
	}

	for (int i = space_s1; i <= length; i++)
		printf("%c", s1[i]);
	printf(" x ");
	for (int i = space_s2; i <= length; i++)
		printf("%c", s2[i]);
	printf("\n= ");
	int j;
	for (j = 0; j <= 2 * length + 2; j++)
		if (result[j] != '0') break;
	for (int i = j; i <= 2 * length + 2; i++)
		printf("%c", result[i]);
	printf("\n");
}

int main()
{
	const int length = 999;
again:printf("Please input a and b to start calculating.\n");
	char a[1000], b[1000];
	for (int i = 0; i <= length; i++) 
	{
		a[i] = b[i] = ' ';
	}

	for (int i = 0; i <= length; i++) 
	{
		char temp;
	re_a:temp = getchar();
		if (i == 0 && temp == ' ') goto re_a;
		if (temp > '9' || temp < '0') break;
		else a[i] = temp;
	}
	for (int i = 0; i <= length; i++)
	{
		char temp;
	re_b:temp = getchar();
		if (i == 0 && temp == ' ') goto re_b;
		if (temp > '9' || temp < '0') break;
		else b[i] = temp;
	}

	int space_a = 0, space_b = 0;
	for (int i = length; i >= 0; i--) 
	{
		if (a[i] == ' ') space_a += 1;
		else break;
	}
	for (int i = length; i >= space_a; i--) 
		a[i] = a[i - space_a];

	for (int i = length; i >= 0; i--)
	{
		if (b[i] == ' ') space_b += 1;
		else break;
	}
	for (int i = length; i >= space_b; i--)
		b[i] = b[i - space_b];

	printf("Enter 1 for + (plus), 2 for - (minus), 3 for x (multiple):\n");
	int i = 0;
re:scanf("%d", &i);
	if (i < 1 || i > 3)
	{
		printf("Illegal input! Please choose again.\n");
		goto re;
	}

	if (i == 1) string_plus(a, b, length, space_a, space_b);
	else if (i == 2) string_minus(a, b, length, space_a, space_b);
	else stringXstring(a, b, length, space_a, space_b);

	printf("Another calculation? Enter y for YES or n for NO.\n");
	char c;
	getchar(); scanf("%c", &c); getchar();
	if (c == 'n') return 0;
	else goto again;

	return 0;
}
