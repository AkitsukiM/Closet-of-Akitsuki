#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

char a_plus(char a, char b, char c, char *d)
{
	int k = (int)a + (int)b + (int)c - 144;
	if (k > 9) *d = '1';
	return (char)(k % 10 + 48);
}

int main()
{
	const int length = 1000;
	printf("Please input a and b to calculate a + b:\n");
	char a[1001], b[1001], c[1001], result[1001];
	for (int i = 0; i <= length; i++) // Initialize the arrays
	{
		a[i] = b[i] = result[i] = ' ';
		c[i] = '0';
	}

	for (int i = 0; i <= length; i++) // Input the data
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
	for (int i = length; i >= 0; i--) // Count the number of the character ' '
	{
		if (a[i] == ' ') space_a += 1;
		else break;
	}
	for (int i = length; i >= 0; i--)
	{
		if (b[i] == ' ') space_b += 1;
		else break;
	}

	for (int i = length; i >= space_a; i--) // Make sure that all the digits align on the right
		a[i] = a[i - space_a];
	for (int i = length; i >= space_b; i--)
		b[i] = b[i - space_b];
	int less_space;
	if (space_a > space_b)
	{
		less_space = space_b;
		for (int i = space_b; i < space_a; i++)
			a[i] = '0';
	}
	else if (space_b > space_a)
	{
		less_space = space_a;
		for (int i = space_a; i < space_b; i++)
			b[i] = '0';
	}
	else
		less_space = space_a;

	for (int i = length; i >= less_space; i--) // NUCLEUS: use a function to calculate a plus b
		result[i] = a_plus(a[i], b[i], c[i], &c[i - 1]);

	for (int i = space_a; i <= length; i++) // Output the result
		printf("%c", a[i]);
	printf(" + ");
	for (int i = space_b; i <= length; i++)
		printf("%c", b[i]);
	printf(" = ");
	if (c[less_space - 1] == '1')
	{
		result[less_space - 1] = '1';
		for (int i = less_space - 1; i <= length; i++)
			printf("%c", result[i]);
	}
	else
		for (int i = less_space; i <= length; i++)
			printf("%c", result[i]);
	printf("\n");

	system("pause");
	return 0;
}
