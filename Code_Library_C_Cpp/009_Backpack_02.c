#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int mass[1024], value[1024], is[1024];

int put(int i, int left)
{
	if (i == 0)
	{
		if (mass[i] <= left) { is[i] = 1; return value[i]; }
		else { is[i] = 0; return 0; }
	}
	else
	{
		int case1, case2 = put(i - 1, left);
		if (left >= mass[i])
		{
			case1 = put(i - 1, left - mass[i]) + value[i];
			if (case1 > case2) { is[i] = 1; return case1; }
		}
		is[i] = 0; return put(i - 1, left);
	}
}

int main()
{
	int max, n, _mass = 0, _value = 0;
	scanf("%d%d", &max, &n);
	for (int i = 0; i < n; ++i) scanf("%d", &mass[i]);
	for (int i = 0; i < n; ++i) scanf("%d", &value[i]);
	_value = put(n - 1, max);
	for (int i = 0; i < n; ++i)
		if (is[i] == 1)
		{
			printf("%d %d\n", mass[i], value[i]);
			_mass += mass[i];
		}
	printf("%d %d\n", _mass, _value);
	return 0;
}
