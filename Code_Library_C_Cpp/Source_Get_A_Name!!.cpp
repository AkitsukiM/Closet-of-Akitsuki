/*
* "Get A Name!!" Application on Windows 10 systems
* Version 1.2.1
* (c) 2018 �����ħ������^. All rights reserved.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdbool>
#include <ctime>
#include <cstdlib>
#include <Windows.h>

using namespace std;
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // ��ȡ��׼����豸���
HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE); // ��ȡ��׼�����豸���

// ������ѡ��֮����
int choose(vector<string> choices, WORD att, int space)
{
	// ��ȡ�������λ��
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int csbiX = 0, csbiY = 0;

	// ��ȡ����̨������Ϣ
	if (GetConsoleScreenBufferInfo(hOut, &csbi))
	{
		csbiX = csbi.dwCursorPosition.X;
		csbiY = csbi.dwCursorPosition.Y;
	}
	else
	{
		printf("Error: ��ȡ���λ��ʧ��\n");
		return -1;
	}

	SetConsoleTextAttribute(hOut, att); // �����ַ�����

	// �������choices���������ַ�
	for (auto iter = choices.begin(); iter != choices.end(); ++iter)
	{
		cout << *iter;
		for (int i = 0; i < space; ++i) cout << ends;
	}
	cout << "\n" << endl;

	SetConsoleTextAttribute(hOut, csbi.wAttributes); // �ָ��ַ�����

	INPUT_RECORD mouseRec;
	DWORD res;

	while (1)
	{
		ReadConsoleInput(hIn, &mouseRec, 1, &res);
		if (mouseRec.EventType == MOUSE_EVENT)
		{
			if (mouseRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				int mouseX = mouseRec.Event.MouseEvent.dwMousePosition.X;
				int mouseY = mouseRec.Event.MouseEvent.dwMousePosition.Y;
				if (mouseY == csbiY)
				{
					int op = csbiX, ed = csbiX;
					for (auto iter = choices.begin(); iter != choices.end(); ++iter)
					{
						ed += (*iter).size();
						if (mouseX >= op && mouseX < ed) return (iter - choices.begin());

						op = ed; op += space; ed += space; // ����Ϊ��һ���ַ�����������
					}
				}
			}
		}
	}

	return -1; // ��ʵ����Զ���ᵽ��һ������Ϊ����whileѭ������ȷ����Է��غ���ֵ������ᱻ����whileѭ����
}

int main()
{
	ShowWindow(GetForegroundWindow(), SW_MAXIMIZE);

	// �������·��
	ifstream namefile("Namelist.txt");
	// �����·���²�������ΪNamelist.txt���ĵ�
	if (!namefile.is_open())
	{
		// �ر��ļ�
		namefile.close();

		cout << "Enter the full path of a list. It must be a *.txt document." << endl;
		string road;
		getline(cin, road);
		// �������·��
		namefile.open(road);
		if (!namefile.is_open())
		{
			cout << "System cannot open \"" << road << "\"." << endl;
			system("pause");
			return -1;
		}
	}

	vector<string> namevec, savevec;
	string temp;
	
	while (getline(namefile, temp))
	{
		namevec.push_back(temp);
	}
	namefile.close();
	auto size = namevec.size();
	cout << "Read successfully! Press Enter to continue or Esc to quit." << endl;

	INPUT_RECORD keyRec;
	DWORD res;

	srand((unsigned)time(NULL)); // ��ϵͳʱ��Ϊ���������
	while (1)
	{
		ReadConsoleInput(hIn, &keyRec, 1, &res);
		if (keyRec.EventType == KEY_EVENT)
		{
			if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) break; // ��ESC���˳�ѭ��
			if (keyRec.Event.KeyEvent.bKeyDown)
			{
				if ((int)keyRec.Event.KeyEvent.uChar.AsciiChar == 13) // ����Enter��
				{
					int rand_result = rand() % size; // ��ȡ�����
					string printtemp = *(namevec.begin() + rand_result); // ��ȡ�������Ӧ���ַ���
					savevec.push_back(printtemp); // ���ַ�����¼������savevec��
					cout << printtemp << endl; // ������ַ���
				}
			}
		}
	}

	cout << "Do you want to save this random list? (Click)\n" << endl;

	vector<string> choices = { "[YES]","[NO]" }; // YES or NO �ж�ģ��
	WORD att = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY; // �ı���ɫ�ǻ�ɫ
	int toPrint = choose(choices, att, 3);

	if (toPrint == 0)
	{
		ofstream save("out.txt");
		for (auto iter = savevec.begin(); iter != savevec.end(); ++iter)
		{
			save << *iter << endl;
		}
		cout << "Save successfully!" << endl;
	}

	system("pause");
	return 0;
}
