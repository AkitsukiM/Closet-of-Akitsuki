#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdbool>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main()
{
	bool isEND = false;

	int n;
	cout << "No.n Prime Number, n:" << endl;
	cin >> n;
	int sup = n * log2(n);

	clock_t t1, t2;
	t1 = clock();

	vector<bool> a(sup, true);
	a[0] = false;
	a[1] = false;
	a[2] = true;
	int count = 1; // 素数个数计数
	int k = 3; // 素数列素数指示器
	int i = 3; // 素数倍乘筛法指示器

	while (1)
	{
		for (int j = 3; j < sup / i; j += 2) a[i * j] = false; // 素数倍乘筛法
		for (; k < (i + 2) * (i + 2); k += 2) // 素数列获取
		{
			if (a[k] == true) count++;
			if (count == n)
			{
				cout << k << endl;
				isEND = true;
				break;
			}
		}
		if (isEND == true) break;
		for (i += 2; a[i] == false; i += 2); // 步长为2判断下一个用于筛法的素数
	}

	t2 = clock();
	cout << double((t2 - t1)) / CLOCKS_PER_SEC << "s" << endl;
	system("pause");
	return 0;
}
