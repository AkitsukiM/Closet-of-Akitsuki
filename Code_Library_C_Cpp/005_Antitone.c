#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int a[9], b[9] = { 0,0,0,0,0,0,0,0,0 };
	int count = 0;
	for (int i = 0; i < 9; i++)
		scanf("%d", &a[i]);
	for (int i = 0; i < 9; i++)
	{
		count = 0;
		for (int j = 0; j < 9; j++)
			if (b[j] == 0)
			{
				if (count == a[i]) { b[j] = i + 1; break; }
				else count += 1;
			}
	}
	for (int i = 0; i < 9; i++)
		printf("%d ", b[i]);
	printf("\n"); getchar(); getchar();
	return 0;
}
