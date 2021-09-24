#include <iostream>
#include <cstdio>
#include <Windows.h>

using namespace std;

int main()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出设备句柄
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE); // 获取标准输入设备句柄

	INPUT_RECORD keyRec;
	DWORD state = 0, res;
	while (1)
	{
		ReadConsoleInput(hIn, &keyRec, 1, &res);
		if (keyRec.EventType == KEY_EVENT)
		{
			if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) break; // 按ESC键退出循环
			if (keyRec.Event.KeyEvent.bKeyDown)
			{	
				if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_LEFT) cout << "left" << endl;
				if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_UP) cout << "up" << endl;
				if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT)cout << "right" << endl;
				if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_DOWN) cout << "down" << endl;
				printf("%d\n", (int)keyRec.Event.KeyEvent.uChar.AsciiChar);
			}
		}
	}
	system("pause");
	return 0;
}
