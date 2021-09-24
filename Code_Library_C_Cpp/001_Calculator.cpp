#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

char char_plus(char a, char b, char c, char &d) 
{
	int k = static_cast<int>(a) + static_cast<int>(b) + static_cast<int>(c) - 144;
	if (k > 9) d = '1';
	return (static_cast<char>(k % 10 + 48));
}

string string_plus(string s1, string s2)
{
	string::size_type size = s1.size();
	if (s2.size() > size) size = s2.size();
	string str_1(size, '0'), str_2(size, '0'), str_0(size + 1, '0'), pre_result(size, '0'), str_result;
	for (string::size_type i = 0; i != size; ++i)
	{
		if (i < s1.size()) str_1[i] = s1[s1.size() - i - 1]; 
		if (i < s2.size()) str_2[i] = s2[s2.size() - i - 1]; 
		pre_result[i] = char_plus(str_1[i], str_2[i], str_0[i], str_0[i + 1]);
	}
	if (str_0[size] == '1') str_result = "1";
	for (string::size_type i = 0; i != size; ++i)
		str_result += pre_result[size - i - 1]; 
	return str_result;
}

char char_minus(char a, char b, char c, char &d) 
{
	int k = static_cast<int>(a) - static_cast<int>(b) - static_cast<int>(c) + 48;
	if (k < 0) d = '1';
	return (static_cast<char>((k + 10) % 10 + 48));
}

string string_minus(string s1, string s2) 
{
	string::size_type size = s1.size();
	if (s2.size() > size) size = s2.size();
	string str_1(size, '0'), str_2(size, '0'), str_0(size + 1, '0'), pre_result(size, '0'), str_result;
	for (string::size_type i = 0; i != size; ++i)
	{
		if (i < s1.size()) str_1[size - i - 1] = s1[s1.size() - i - 1]; 
		if (i < s2.size()) str_2[size - i - 1] = s2[s2.size() - i - 1]; 
	}

	if (str_1 == str_2) return "0";
	else if (str_1 > str_2)
	{
		for (string::size_type i = size - 1; i != -1; --i)
		{
			pre_result[i] = char_minus(str_1[i], str_2[i], str_0[i + 1], str_0[i]);
		}
		string::size_type j;
		for (j = 0; j != size; ++j)
			if (pre_result[j] != '0') break;
		for (string::size_type i = j; i != size; ++i)
			str_result += pre_result[i];
	}
	else
	{
		str_result = "-";
		for (string::size_type i = size - 1; i != -1; --i)
		{
			pre_result[i] = char_minus(str_2[i], str_1[i], str_0[i + 1], str_0[i]);
		}
		string::size_type j;
		for (j = 0; j != size; ++j)
			if (pre_result[j] != '0') break;
		for (string::size_type i = j; i != size; ++i)
			str_result += pre_result[i];
	}
	return str_result;
}

char charXchar(char a, char b, char c, char &d) 
{
	int k = (static_cast<int>(a) - 48) * (static_cast<int>(b) - 48) + static_cast<int>(c) - 48;
	d = static_cast<char>((k - k % 10) / 10 + 48);
	return (static_cast<char>(k % 10 + 48));
}

string stringXchar(string str, char a) 
{
	string::size_type size = str.size();
	string str_0(size + 1, '0'), pre_result(size,'0'), str_result;
	for (string::size_type i = 0; i != size; ++i)
		pre_result[i] = charXchar(str[size - i - 1], a, str_0[i], str_0[i + 1]);
	if (str_0[size] != '0') str_result = str_0[size];
	for (string::size_type i = 0; i != size; ++i)
		str_result += pre_result[size - i - 1]; 
	return str_result;
}

string stringXstring(string s1, string s2)
{
	string result = "0";
	for (string::size_type i = 0; i != s2.size(); ++i)
	{
		string add(i, '0');
		result = string_plus(result, stringXchar(s1, s2[s2.size() - i - 1]) + add);
	}
	return result;
}

int main()
{
again:cout << "Please input a and b to start calculating." << endl;
	string a, b;
	cin >> a >> b;
	cout << "Enter 1 for + (plus), 2 for - (minus), 3 for x (multiple):" << endl;
	int i = 0;
re:cin >> i;
	if (i < 1 || i > 3)
	{
		cout << "Illegal input! Please choose again." << endl;
		goto re;
	}

	if (i == 1) cout << a << " + " << b << endl << "= " << string_plus(a, b) << endl;
	else if (i == 2) cout << a << " - " << b << endl << "= " << string_minus(a, b) << endl;
	else cout << a << " x " << b << endl << "= " << stringXstring(a, b) << endl;

	cout << "Another calculation? Enter y for YES or n for NO." << endl;
	char c;
	cin >> c;
	if (c == 'n') return 0;
	else goto again;

	return 0;
}
