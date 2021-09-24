#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int settled[1024], result[1024], mass[1024], value[1024];
int n = 0, max = 0, max_mass = 0, max_value = 0;

void put_01(int len)
{
	if (len == n)
	{
		int sum_mass = 0, sum_value = 0;
		for (int i = 0; i < n; ++i) sum_mass += settled[i] * mass[i];
		if (sum_mass <= max)
		{
			for (int i = 0; i < n; ++i) sum_value += settled[i] * value[i];
			if (sum_value > max_value || (sum_value == max_value && sum_mass < max_mass))
				for (int i = 0; i < n; ++i)
				{
					result[i] = settled[i];
					max_mass = sum_mass;
					max_value = sum_value;
				}
		}
	}
	else
		for (int i = 0; i < 2; ++i)
		{
			settled[len] = i;
			put_01(len + 1);
		}
}

int main()
{
	scanf("%d%d", &max, &n);
	for (int i = 0; i < n; ++i) scanf("%d", &mass[i]);
	for (int i = 0; i < n; ++i) scanf("%d", &value[i]);
	max_mass = max;
	put_01(0, n);
	for (int i = 0; i < n; ++i)
		if (result[i] != 0) printf("%d %d\n", mass[i], value[i]);
	printf("%d %d\n", max_mass, max_value);
	return 0;
}
