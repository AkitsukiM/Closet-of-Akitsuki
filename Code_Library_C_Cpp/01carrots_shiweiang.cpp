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
			return -1;                 //����д��-1����Ϊ������0�����ܲ���ʱ���ܱ���
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
		if (n < 0)                     //��������˳���Ÿĳ� n < 0 �ˡ�
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
		cout << "I have " << n << " carrots" << endl;      //����д��ѭ���ں����������ŵ�������ʽҲ�������һ�¡�
		break;
	}
	system("pause");
	return 0;
}
