#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
	double sum = 0;
	for (int i = 1; i <= 100; ++i) sum += (1.0 * (i % 2 == 1 ? 1 : -1) / i);

	printf("sum = %f\n", sum);

	system("pause");
	return 0;
}
