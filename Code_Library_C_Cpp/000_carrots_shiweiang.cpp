#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int getnum()
{
	int n = 0;
	char c;
	while (1) {
		c = cin.get();
		if (c == '\n')
			break;
		else if (c < '0' || c > '9')
			return -1;                 //这里写作-1，因为当我有0个胡萝卜的时候不能报错。
		n = n * 10 + c - '0';
	}
	return n;
}

int main()
{
	int n;
	char c;
	while (1)
	{
		cout << "How many carrots do you have?" << endl;
		n = getnum();
		c = 0;
		if (n < 0)                     //所以这里顺带着改成 n < 0 了。
		{
			while (cin.get() != '\n')
				;
			string s;
			do
			{
				cout << "Input error" << endl << "Do you want to try again?(y/n)" << endl;
				getline(cin, s);
			} while (s != "y" && s != "n");
			if (s == "y")
				continue;
			else
				break;
		}
		cout << "I have " << n << " carrots" << endl;      //这里写个循环节好吗？怎样编排单复数形式也可以领教一下。
		break;
	}
	system("pause");
	return 0;
}
