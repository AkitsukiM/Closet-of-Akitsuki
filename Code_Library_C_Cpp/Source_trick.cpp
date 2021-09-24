#include <iostream>

using namespace::std;

int trick(int num)
{
	int x[10] = { 0,0,0,0,0,0,0,0,0,0 };
	int temp = 0;

	do
	{
		x[num % 10]++;
		num = (num - num % 10) / 10;
	} while (num > 0);

	for (int i = 8; i >= 0; --i)
		for (int j = 0; j != x[i]; ++j)
			temp = temp * 10 + i;
	for (int j = 0; j != x[9]; ++j)
		temp = temp * 10 + 9;
	return temp;
}

int main()
{
	int cry = 0;
	do
	{
		cout << trick(cry) << endl;
		cin >> cry;
	} while (cry >= 0);

	system("pause");
	return 0;
}
