#include<iostream>
//#include<stdexcept>
using namespace::std;

int main()
{
	int a, b;
	while (cin >> a >> b)
	{
		try
		{
			if (!(a == b))
				throw runtime_error("a doesn't equal b.");
			cout << "a = b" << endl;
			return 0;
		}
		catch (runtime_error er)
		{
			cout << er.what() << "\nTry Again? Enter y or n" << endl;
			char c;
			cin >> c;
			if (cin&&c == 'n') break;
		}
	}
}