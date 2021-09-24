/*
* "Get A Name!!" Application on Windows 10 systems
* Version 1.2.1
* (c) 2018 ヴワル魔法図書館. All rights reserved.
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
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出设备句柄
HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE); // 获取标准输入设备句柄

// 单击以选择之函数
int choose(vector<string> choices, WORD att, int space)
{
	// 获取光标所在位置
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int csbiX = 0, csbiY = 0;

	// 获取控制台窗口信息
	if (GetConsoleScreenBufferInfo(hOut, &csbi))
	{
		csbiX = csbi.dwCursorPosition.X;
		csbiY = csbi.dwCursorPosition.Y;
	}
	else
	{
		printf("Error: 获取光标位置失败\n");
		return -1;
	}

	SetConsoleTextAttribute(hOut, att); // 更改字符属性

	// 输出容器choices所包含的字符
	for (auto iter = choices.begin(); iter != choices.end(); ++iter)
	{
		cout << *iter;
		for (int i = 0; i < space; ++i) cout << ends;
	}
	cout << "\n" << endl;

	SetConsoleTextAttribute(hOut, csbi.wAttributes); // 恢复字符属性

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

						op = ed; op += space; ed += space; // 更改为下一个字符串的上下限
					}
				}
			}
		}
	}

	return -1; // 事实上永远不会到这一步，因为除非while循环中正确点击以返回函数值，否则会被困在while循环中
}

int main()
{
	ShowWindow(GetForegroundWindow(), SW_MAXIMIZE);

	// 读入相对路径
	ifstream namefile("Namelist.txt");
	// 若相对路径下不存在名为Namelist.txt的文档
	if (!namefile.is_open())
	{
		// 关闭文件
		namefile.close();

		cout << "Enter the full path of a list. It must be a *.txt document." << endl;
		string road;
		getline(cin, road);
		// 读入绝对路径
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

	srand((unsigned)time(NULL)); // 以系统时间为随机数种子
	while (1)
	{
		ReadConsoleInput(hIn, &keyRec, 1, &res);
		if (keyRec.EventType == KEY_EVENT)
		{
			if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) break; // 按ESC键退出循环
			if (keyRec.Event.KeyEvent.bKeyDown)
			{
				if ((int)keyRec.Event.KeyEvent.uChar.AsciiChar == 13) // 按下Enter键
				{
					int rand_result = rand() % size; // 获取随机数
					string printtemp = *(namevec.begin() + rand_result); // 获取随机数对应的字符串
					savevec.push_back(printtemp); // 将字符串记录到容器savevec中
					cout << printtemp << endl; // 输出该字符串
				}
			}
		}
	}

	cout << "Do you want to save this random list? (Click)\n" << endl;

	vector<string> choices = { "[YES]","[NO]" }; // YES or NO 判断模块
	WORD att = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY; // 文本颜色是黄色
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
