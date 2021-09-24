#include "Header.h"

vector<course> courses;

// 输入字符串以解析. 解析失败return 1, 否则return 0.
int getlineAnalysis(string str)
{
	string CodeAndName = "", CreditStr = "", PerformanceStr = "";
	int i = 0;

	/* 登记CodeAndName */
	for (; i != str.size(); ++i)
	{
		int countspace = 0; for (; isspace(str[i]); ++i) ++countspace; // 跳过空格并计数
		if (countspace > 0) // 对于跳过空格的场合
		{
			if (isdigit(str[i])) break; // 空格后如果为数字跳出循环
			else CodeAndName += " "; // 补偿空格
		}
		CodeAndName += str[i]; // 登记当前格
	}

	/* 登记CreditStr */
	for (; isdigit(str[i]); ++i) CreditStr += str[i]; // 登记当前数字格
	if (str[i] == '.')
	{
		CreditStr += str[i++]; // 登记当前格
		for (; isdigit(str[i]); ++i) CreditStr += str[i]; // 登记当前数字格
	}

	if (CreditStr == "") return 1; // 解析失败
	for (; isspace(str[i]); ++i); // 跳过空格

	/* 登记PerformanceStr */
	for (; isdigit(str[i]); ++i) PerformanceStr += str[i]; // 登记当前数字格

	if (PerformanceStr == "") return 1; // 解析失败
	course newcourse(CodeAndName, stof(CreditStr), stoi(PerformanceStr)); // 定义并初始化一个course类型变量
	courses.push_back(newcourse); // 加入容器
	return 0;
}

// 读取信息. 读取失败return 1, 否则return 0.
int readInformation()
{
	// 寻找相对路径下的course
	ifstream file;
	string road = "course"; file.open(road);
	// 寻找相对路径下的course.txt
	if (!file.is_open())
	{
		file.close();
		road = "course.txt"; file.open(road);
	}
	// 找不到course或者course.txt
	if (!file.is_open())
	{
		file.close();
		cout << "Cannot find \"course\". Enter the path of a specific file." << endl;
		getline(cin, road); file.open(road);
	}
	// 如果依然找不到
	if (!file.is_open())
	{
		file.close();
		cout << "Error: Cannot find \"" << road << "\"." << endl;
		return 1; // 返回1表示失败
	}

	cout << "Open successfully!" << endl;
	string temp;
	while (getline(file, temp))
	{
		if (temp != "" && getlineAnalysis(temp)) // 非空字符串解析失败
		{
			cout << "Error: illegal information in line \"" << temp << "\"" << endl;
			return 1; // 返回1表示失败
		}
	}

	cout << "Read successfully!" << endl;
	file.close();
	return 0;
}
