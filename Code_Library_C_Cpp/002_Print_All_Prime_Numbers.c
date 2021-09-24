#include <stdio.h>
#include <stdbool.h>

bool is_prime_number(int n)
{
	bool is = true;
	for (int i = 2; i <= n / 2; i++)
	{
		if (n % i == 0) is = false;
		else continue;
	}
	return is;
}

int main()
{
	int num = 0;
	for (int i = 2; i < 100; i++)
	{
		if (is_prime_number(i))
		{
			printf("%5d", i);
			num += 1;
		}
		if (num % 10 == 0) printf("\n");
	}
	printf("\n");
	getchar();
	return 0;
}

/*
*#include <stdio.h>
*int main()
*{
*	 int count = 0, m = 2, i;
*	 for (; m <= 100; m++)
*	 {
*		 for (i = 2; i <= m / 2; i++)
*			 if (m % i == 0) break;
*		 if (i <= m / 2) continue;
*		 count++;
*		 printf("%5d", m);
*		 if (count % 10 == 0) printf("\n");
*	 }
*	 printf("\n");
*	 return 0;
*}
*/