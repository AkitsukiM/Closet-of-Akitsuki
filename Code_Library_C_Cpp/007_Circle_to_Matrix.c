#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int m = 1, n = 1, min = 0, count = 0;
	int a[100][100];
	printf("Enter the dimension m, n:\n");
	scanf("%d%d", &m, &n);
	printf("Enter the matrix:\n");
	for (int i = 0; i != m; ++i)
		for (int j = 0; j != n; ++j)
			scanf("%d", &a[i][j]);
	min = (m + 1) / 2; if (n < m) min = (n + 1) / 2;
	for (int i = 0; i < min; ++i)
	{
		for (int j = i; j != n - i; ++j)
		{
			printf("%d\t", a[i][j]); count += 1;
			if (count == n) { printf("\n"); count = 0; }
		}
		for (int j = i + 1; j < m - i; ++j)
		{
			printf("%d\t", a[j][n - i - 1]); count += 1;
			if (count == n) { printf("\n"); count = 0; }
		}
		if (m - i - 1 > 0)
			for (int j = n - i - 2; j >= i; --j)
			{
				printf("%d\t", a[m - i - 1][j]); count += 1;
				if (count == n) { printf("\n"); count = 0; }
			}
		if (n - i - 1 > 0)
			for (int j = m - i - 2; j > i; --j)
			{
				printf("%d\t", a[j][i]); count += 1;
				if (count == n) { printf("\n"); count = 0; }
			}
	}
	getchar(); getchar();
	return 0;
}
