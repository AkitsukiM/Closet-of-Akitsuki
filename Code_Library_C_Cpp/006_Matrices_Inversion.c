#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef long double num;

int main()
{
	int n = 0;
	printf("rank(A) = n. Enter the n.\n");
	scanf("%d", &n);
	num a[100][200];
re:printf("Enter the matrix.\n");
	for (int i = 0; i != n; ++i)
		for (int j = 0; j != n; ++j)
			scanf("%lf", &a[i][j]);
	for (int i = 0; i != n; ++i)
	{
		for (int j = n; j != 2 * n; ++j) a[i][j] = 0;
		a[i][n + i] = 1;
	}

	num s = 0;
	for (int i = 0; i != n; ++i)
	{
		if (a[i][i] == 0)
		{
			int t = i + 1;
			for (; t != n; ++t)
				if (a[t][i] != 0)
				{
					num temp;
					for (int k = i; k != 2 * n; ++k) 
					{ temp = a[i][k]; a[i][k] = a[t][k]; a[t][k] = temp; }
					break;
				}
			if (t == n)
			{
				printf("The rank of matrix is not n. Please try again. ");
				goto re;
			}
		}
		for (int t = i + 1; t != n; ++t)
		{
			s = -a[t][i] / a[i][i];
			for (int k = i; k != 2 * n; ++k) a[t][k] += a[i][k] * s;
		}
		s = 1 / a[i][i];
		for (int k = i; k != 2 * n; ++k) a[i][k] *= s;
	}
	for (int i = n - 1; i != -1; --i)
		for (int t = i - 1; t != -1; --t)
		{
			s = -a[t][i];
			for (int k = i; k != 2 * n; ++k) a[t][k] += a[i][k] * s;
		}
	
	printf("\nA ^ -1 = \n");
	for (int i = 0; i != n; ++i)
	{
		for (int j = n; j != 2 * n; ++j) printf("\t%lf", a[i][j]);
		printf("\n");
	}
	getchar(); getchar();
	return 0;
}
