#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define LEN 18

int main()
{
	int co[LEN] = { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2, 1 };
	int id[LEN]; // "330106199910190183"
	int n = 0;
	char c;
	while ((c = getchar()) != EOF)
	{
		if ((c >= '0' && c <= '9') && n < LEN) id[n++] = c - '0';
		else if ((c == 'X' || c == 'x') && n < LEN) id[n++] = 10;
		else if (c == '\n')
		{
			if (n == LEN)
			{
				int sum = 0;
				for (int i = 0; i < LEN - 1; ++i) sum += co[i] * id[i];
				sum = sum % 11;
				sum = (12 - sum) % 11;
				if (sum == id[LEN - 1]) printf("Right!\n");
				else printf("Wrong! It should be %d.\n", sum);
			}
			n = 0;
		}
		else
			;
	}
	return 0;
}
