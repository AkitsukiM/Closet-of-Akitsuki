#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int m = 0, s = 0, n = 0;
	printf("Matrix A: m x s; Matrix B: s x n. Please enter the number: m, s, n.\n");
	scanf("%d%d%d", &m, &s, &n);
	int Matrix_A[10][10], Matrix_B[10][10], Matrix_AB[10][10];
	printf("Please input the matrix A:\n");
	for (int r = 0; r != m; ++r)
		for (int c = 0; c != s; ++c)
			scanf("%d", &Matrix_A[r][c]);
	printf("Please input the matrix B:\n");
	for (int r = 0; r != s; ++r)
		for (int c = 0; c != n; ++c)
			scanf("%d", &Matrix_B[r][c]);
	printf("\nA x B =\n");
	for (int i = 0; i != m; ++i)
		for (int j = 0; j != n; ++j)
		{
			Matrix_AB[i][j] = 0;
			for (int k = 0; k != s; ++k)
				Matrix_AB[i][j] += (Matrix_A[i][k] * Matrix_B[k][j]);
		}
	for (int r = 0; r != m; ++r)
	{
		for (int c = 0; c != n; ++c)
			printf("%d\t", Matrix_AB[r][c]);
		printf("\n");
	}
	getchar(); getchar();
	return 0;
}
