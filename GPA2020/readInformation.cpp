#include "Header.h"

vector<course> courses;

// �����ַ����Խ���. ����ʧ��return 1, ����return 0.
int getlineAnalysis(string str)
{
	string CodeAndName = "", CreditStr = "", PerformanceStr = "";
	int i = 0;

	/* �Ǽ�CodeAndName */
	for (; i != str.size(); ++i)
	{
		int countspace = 0; for (; isspace(str[i]); ++i) ++countspace; // �����ո񲢼���
		if (countspace > 0) // ���������ո�ĳ���
		{
			if (isdigit(str[i])) break; // �ո�����Ϊ��������ѭ��
			else CodeAndName += " "; // �����ո�
		}
		CodeAndName += str[i]; // �Ǽǵ�ǰ��
	}

	/* �Ǽ�CreditStr */
	for (; isdigit(str[i]); ++i) CreditStr += str[i]; // �Ǽǵ�ǰ���ָ�
	if (str[i] == '.')
	{
		CreditStr += str[i++]; // �Ǽǵ�ǰ��
		for (; isdigit(str[i]); ++i) CreditStr += str[i]; // �Ǽǵ�ǰ���ָ�
	}

	if (CreditStr == "") return 1; // ����ʧ��
	for (; isspace(str[i]); ++i); // �����ո�

	/* �Ǽ�PerformanceStr */
	for (; isdigit(str[i]); ++i) PerformanceStr += str[i]; // �Ǽǵ�ǰ���ָ�

	if (PerformanceStr == "") return 1; // ����ʧ��
	course newcourse(CodeAndName, stof(CreditStr), stoi(PerformanceStr)); // ���岢��ʼ��һ��course���ͱ���
	courses.push_back(newcourse); // ��������
	return 0;
}

// ��ȡ��Ϣ. ��ȡʧ��return 1, ����return 0.
int readInformation()
{
	// Ѱ�����·���µ�course
	ifstream file;
	string road = "course"; file.open(road);
	// Ѱ�����·���µ�course.txt
	if (!file.is_open())
	{
		file.close();
		road = "course.txt"; file.open(road);
	}
	// �Ҳ���course����course.txt
	if (!file.is_open())
	{
		file.close();
		cout << "Cannot find \"course\". Enter the path of a specific file." << endl;
		getline(cin, road); file.open(road);
	}
	// �����Ȼ�Ҳ���
	if (!file.is_open())
	{
		file.close();
		cout << "Error: Cannot find \"" << road << "\"." << endl;
		return 1; // ����1��ʾʧ��
	}

	cout << "Open successfully!" << endl;
	string temp;
	while (getline(file, temp))
	{
		if (temp != "" && getlineAnalysis(temp)) // �ǿ��ַ�������ʧ��
		{
			cout << "Error: illegal information in line \"" << temp << "\"" << endl;
			return 1; // ����1��ʾʧ��
		}
	}

	cout << "Read successfully!" << endl;
	file.close();
	return 0;
}
