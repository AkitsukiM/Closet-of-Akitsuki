#include <iostream>
#include <cstdbool>

using std::cin;
using std::cout;
using std::endl;

int sqr(int n) // 开方下取整算法
{
	int i = 1;
	for (i = 1; i < n; i++)
		if (i*i <= n && (i + 1)*(i + 1) > n) break;
	return i;
}

bool is_prime(int n) // 质数判断算法
{
	bool is = true;
	int s = sqr(n);
	for (int i = 2; i <= s; i++)
		if (n%i == 0) { is = false; break; }
	return is;
}

int main()
{
	int a, b, p, m, b_mod_p, pre(1);
	cout << "To solve the minimum m satisfied with a ^ m ~ b (mod p). Prime numbers a, b, p = ?" << endl;
re:cin >> a >> b >> p;
	if (is_prime(a) == false || is_prime(b) == false || is_prime(p) == false)
	{
		cout << "Illegal input. Enter a, b, p again." << endl;
		goto re;
	}

	b_mod_p = b%p;
	for (m = 0; m < p; m++)
	{
		if (pre%p == b_mod_p)
		{
			cout << "Min(m) = " << m << "." << endl;
			break;
		}
		pre *= a;
	}
	if (m == p) cout << "No satisfied m!" << endl;
	
	cin.get(); cin.get();
	return 0;
}
