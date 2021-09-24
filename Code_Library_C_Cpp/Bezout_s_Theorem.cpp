#include<iostream>
#include<cstdlib>
#include<deque>

using std::cin;
using std::cout;
using std::endl;
using std::deque;

void sgn(int n)
{
	if (n < 0)
		cout << " - " << -n << "k";
	else
		cout << " + " << n << "k";
}

int main()
{
	cout << "Please input a and b to calculate their greatest common divider:" << endl;
	int a(1), b(1);
	cin >> a >> b;
	int aa = a, bb = b;
	deque<bool> deq;
	while (a != b)
	{
		if (a > b)
		{
			a -= b;
			deq.push_front(false);
		}
		else
		{
			b -= a;
			deq.push_front(true);
		}
	}
	cout << "gcd(a, b) = " << a << endl;
	int lambda(1), myu(0);
	for (deque<bool>::iterator iter = deq.begin(); iter != deq.end(); ++iter)
	{
		if (*iter == false)
			myu -= lambda;
		else
			lambda -= myu;
	}
	if (a != 1)
	{
		cout << "For a and b are not co-prime, the satisfying pair of lambda and myu is not alone." << endl;
		cout << "lambda = " << lambda;
		sgn(-bb / a);
		cout << ", myu = " << myu;
		sgn(aa / a);
		cout << ", auto k: Z" << endl;
	}
	else
		cout << "lambda = " << lambda << ", myu = " << myu << endl;
	system("pause");
	return 0;
}
