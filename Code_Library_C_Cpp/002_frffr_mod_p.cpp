#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using num = long long;

num fxp(num x, num a, num b, num c, num p)
{
	return (a*((x*x) % p) + b*x + c) % p;
}

int main()
{
	num a(0), b(0), c(0), r1(0), r2(0), p(1), k(1);
	cout << "The function f(x) = a * x ^ 2 + b * x + c. a, b, c = ?" << endl;
	cin >> a >> b >> c;
	cout << "The initial numbers r[1] and r[2]. r[1], r[2]?" << endl;
	cin >> r1 >> r2;
	cout << "Mod p. p = ?" << endl;
	cin >> p;

	//��̬���淽�����������м���������ݴ���������
	vector<num> vec = { r1%p,r2%p };
	num pre = 2;
	while (k > 0)
	{
		cout << "To solve r[k]. k = ? (Or input a non-positive integer to quit)" << endl;
		cin >> k;
		if (k > pre)
		{
			for (num i = pre; i < k; i++)
			{
				num temp;
				temp = (fxp(vec[i - 1], a, b, c, p) + fxp(fxp(vec[i - 2], a, b, c, p), a, b, c, p)) % p;
				vec.push_back(temp);
			}
			pre = k;
		}
		if (k > 0) cout << "r[k] = " << vec[k - 1] << "." << endl;
	}

	/*
	//�ù����ӷ�������ʵʱ��ѯ�����洢�ϴε����ݡ�
	num aa, bb, cc;
	while (k > 0)
	{
		cout << "To solve r[k]. k = ? (Or input a non-positive integer to quit)" << endl;
		cin >> k;
		aa = r1%p;
		bb = r2%p;
		if (k == 1) bb = aa;
		if (k > 2)
			for (num i = 2; i < k; i++)
			{
				cc = (fxp(bb, a, b, c, p) + fxp(fxp(aa, a, b, c, p), a, b, c, p)) % p;
				aa = bb;
				bb = cc;
			}
		if (k > 0) cout << "r[k] = " << bb << "." << endl;
	}
	*/

	return 0;
}
