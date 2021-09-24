#include <fstream>
#include <string>

using namespace std;

int main()
{
	ifstream input("in.txt");
	ofstream output("out.txt");
	string temp;
	while (getline(input, temp))
	{
		output << temp << endl;
	}
	system("pause");
	return 0;
}
