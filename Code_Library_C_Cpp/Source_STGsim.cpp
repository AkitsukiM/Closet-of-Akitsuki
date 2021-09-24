/*
* Simplified STG Game at the Command Prompt
* Version 1.1.2
* (c) 2018 ヴワル魔法図書館. All rights reserved.
*/

#include <iostream>
#include <vector>
#include <list>
#include <thread>
#include <cstdio>
#include <cstdlib>
#include <cstdbool>
#include <ctime>
#include <Windows.h>

using namespace std;

HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出设备句柄
HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE); // 获取标准输入设备句柄

int a[34][44]; // 一个 (m + 4) * (n + 4) 的矩阵，实际场 x: 2 - (m + 1); y: 2 - (n + 1)
const int m = 30, n = 40; // 一个 m * n 的场

bool isEnd = false;

int PosMeX = m, PosMeY = n / 2 + 2, power = 2; // 坐标X，坐标Y，Power值（最高为2）

int Time_EveryMove = 1000; // 敌机与敌弹的移动间隔时长
int StepEnemy = 1;
int StepDanmaku = 1;

// 敌机与敌弹类 // 好像与事件日志单元差不多？不过不要混用为好。
struct Pos
{
	int Style;
	int X;
	int Y;
};

list<Pos> Enemy;
list<Pos> Danmaku;

// 事件日志单元
struct EVENT
{
	int Style;
	int X;
	int Y;
};
// 事件日志
vector<EVENT> EventLog;

// 重置光标
void RestoreCCP()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,m + 4 });
}

// 更改数值与显示的子模块
void SetCCP(int x, int y, int style)
{
	// 优先显示：撞弹>敌机>弹幕>道具>子弹>子机
	if (style > a[x][y] || style <= 2)
	{
		// 第x行第y列更改数字
		a[x][y] = style;

		// 防止溢出
		if (x >= 2 && x <= m + 1 && y >= 2 && y <= n + 1)
		{
			// 光标置于该格的后一位
			SetConsoleCursorPosition(hOut, { (short)(y + 1),(short)(x) });

			// 退格并更新
			if (style == 0) printf("\b ");
			else if (style == 1) printf("\bA"); // 自机（正常）
			else if (style == 2) printf("\bA"); // 自机（退出）
			else if (style == 3) printf("\b "); // 子机
			else if (style == 4) printf("\b*"); // 子弹
			else if (style == 11) printf("\bP"); // 道具：P点
			else if (style == 21) printf("\bO"); // 弹幕
			else if (style == 31) printf("\bV"); // 敌机
			else if (style == 100) printf("\b!"); // 撞弹
			else
				;
		}
	}
}

// 自机移动线程函数
void thread_MoveMe()
{
	INPUT_RECORD keyRec;
	DWORD res;
	while (isEnd == false)
	{
		ReadConsoleInput(hIn, &keyRec, 1, &res);
		if (keyRec.EventType == KEY_EVENT)
		{
			// 按ESC键
			if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
				EventLog.push_back({ 2,PosMeX,PosMeY });
			else if (keyRec.Event.KeyEvent.bKeyDown)
			{
				if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_LEFT && PosMeY > 2)
				{
					EventLog.push_back({ 0,PosMeX,PosMeY }); // 消除自机
					for (int i = 2; i < PosMeX; ++i)
						if (a[i][PosMeY + power] == 4) // 如果表现为子弹
							EventLog.push_back({ 0,i,PosMeY + power }); // 消除子弹
					if (power > 0) 
						if (a[PosMeX][PosMeY + power] == 3) // 如果表现为子机
							EventLog.push_back({ 0,PosMeX,PosMeY + power }); // 消除子机
					PosMeY--;
					for (int i = 2; i < PosMeX; ++i) EventLog.push_back({ 4,i,PosMeY - power }); // 新建子弹
					if (power > 0) EventLog.push_back({ 3,PosMeX,PosMeY - power }); // 新建子机
				}
				else if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_UP && PosMeX > 2)
				{
					for (int j = PosMeY - power; j <= PosMeY + power; ++j)
					{
						if (a[PosMeX][j] < 10) // 如果不是持久敌人或敌弹
							EventLog.push_back({ 0,PosMeX,j }); // 消除自机与子机
						if (a[PosMeX - 1][j] == 4) // 如果不是持久敌人或敌弹
							EventLog.push_back({ 0,PosMeX - 1,j }); // 消除子弹
					}
					PosMeX--;
					for (int j = PosMeY - power; j < PosMeY; ++j) EventLog.push_back({ 3,PosMeX,j }); // 新建左侧子机
					for (int j = PosMeY + power; j > PosMeY; --j) EventLog.push_back({ 3,PosMeX,j }); // 新建右侧子机
				}
				else if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT && PosMeY < n + 1)
				{
					EventLog.push_back({ 0,PosMeX,PosMeY }); // 消除自机
					for (int i = 2; i < PosMeX; ++i)
						if (a[i][PosMeY - power] == 4) // 如果表现为子弹
							EventLog.push_back({ 0,i,PosMeY - power }); // 消除子弹
					if (power > 0)
						if (a[PosMeX][PosMeY - power] == 3) // 如果表现为子机
							EventLog.push_back({ 0,PosMeX,PosMeY - power }); // 消除子机
					PosMeY++;
					for (int i = 2; i < PosMeX; ++i) EventLog.push_back({ 4,i,PosMeY + power }); // 新建子弹
					if (power > 0) EventLog.push_back({ 3,PosMeX,PosMeY + power }); // 新建子机
				}
				else if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_DOWN && PosMeX < m + 1)
				{
					for (int j = PosMeY - power; j <= PosMeY + power; ++j) EventLog.push_back({ 4,PosMeX,j }); // 新建子弹
					PosMeX++;
					for (int j = PosMeY - power; j < PosMeY; ++j) EventLog.push_back({ 3,PosMeX,j }); // 新建左侧子机
					for (int j = PosMeY + power; j > PosMeY; --j) EventLog.push_back({ 3,PosMeX,j }); // 新建右侧子机
				}
				else
					;

				if (a[PosMeX][PosMeY] > 20) EventLog.push_back({ 100,PosMeX,PosMeY }); // 判定撞弹
				else if (a[PosMeX][PosMeY] == 11) 
				{
					power++; // Power增加
					EventLog.push_back({ 0,PosMeX,PosMeY }); // 消除P点
					EventLog.push_back({ 1,PosMeX,PosMeY }); // 新建自机
				}
				else EventLog.push_back({ 1,PosMeX,PosMeY }); // 新建自机
			}
			else
				;
		}
	}
}

// 敌机移动线程函数
void thread_MoveEn()
{

}

void CALLBACK Timer_MoveDm(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime)
{
	srand((unsigned)time(NULL));
	for (auto iter = Danmaku.begin(); iter != Danmaku.end(); ++iter)
	{
		if ((*iter).Style == a[(*iter).X][(*iter).Y]) // 如果表现为弹幕
			EventLog.push_back({ 0,(*iter).X,(*iter).Y }); // 消除弹幕

		// 移动弹幕
		(*iter).X += (rand() % (2 * StepDanmaku + 1) - StepDanmaku);
		(*iter).Y += (rand() % (2 * StepDanmaku + 1) - StepDanmaku);
		// 弹幕越界则弹幕失效，注意迭代器使用！
		if ((*iter).X < 2 || (*iter).X > m + 1 || (*iter).Y < 2 || (*iter).Y > n + 1)
		{
			auto one_off_iter = iter;
			--iter;
			Danmaku.erase(one_off_iter);
		}
		else
		{
			int num = a[(*iter).X][(*iter).Y];
			if (num == 1) EventLog.push_back({ 100,(*iter).X,(*iter).Y }); // 自机撞弹判定
			else EventLog.push_back({ (*iter).Style,(*iter).X,(*iter).Y });
		}
	}
}

// 弹幕移动线程函数
void thread_MoveDm()
{
	MSG msg;
	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);

	SetTimer(NULL, 0, Time_EveryMove, Timer_MoveDm);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_TIMER)
		{
			DispatchMessage(&msg);
			if (isEnd == true) break;
		}
	}

	KillTimer(NULL, 0);
}

// 道具移动线程函数
void thread_MoveIt()
{

}

// 屏幕输出线程函数
void thread_PrintS()
{
	// 初始化访问开端与结尾
	int i = 0, ed = EventLog.size();
	while (isEnd == false)
	{
		for (; i != ed; ++i)
		{
			SetCCP((EventLog[i]).X, (EventLog[i]).Y, (EventLog[i]).Style);
			// 若主动结束或撞弹，则更改结束标识并跳出循环
			if ((EventLog[i]).Style == 2 || (EventLog[i]).Style == 100)
			{
				isEnd = true; break;
			}
			RestoreCCP();
		}
		// 重置访问开端与结尾（由for语句的特性似乎无需重置i）
		// i = ed;
		ed = EventLog.size();
		
		// 若此时isEnd == false就会跳出while循环进而结束函数
	}
}

// 初始化函数
void ini()
{
	// 前端窗口最大化
	ShowWindow(GetForegroundWindow(), SW_MAXIMIZE);

	// 初始化数表并打印 // -1 表示边界 // 0 表示空格
	for (int i = 0; i <= m + 3; ++i)
	{
		if (i == 0 || i == m + 3) // 第一行与最后一行 // 值均为-1 // 输出均为" "
		{
			for (int j = 0; j <= n + 3; ++j)
			{
				a[i][j] = -1; printf(" ");
			}
		}
		else if (i == 1 || i == m + 2) // 第二行与倒数第二行 // 值均为-1 // 第一个与最后一个输出" "，其余输出"="
		{
			a[i][0] = -1; printf(" ");
			for (int j = 1; j <= n + 2; ++j)
			{
				a[i][j] = -1; printf("=");
			}
			a[i][n + 3] = -1; printf(" ");
		}
		else // 其余 // 第一个与最后一个值为-1，输出" "；第二个与倒数第二个值为-1，输出"|"；中间值为0，输出" "
		{
			a[i][0] = -1; printf(" ");
			a[i][1] = -1; printf("|");
			for (int j = 2; j <= n+1; ++j)
			{
				a[i][j] = 0; printf(" ");
			}
			a[i][n + 2] = -1; printf("|");
			a[i][n + 3] = -1; printf(" ");
		}

		printf("\n");
	}

	// 注入自机/子机/子弹
	EventLog.push_back({ 1,PosMeX,PosMeY }); // 新建自机
	for (int j = PosMeY - power; j < PosMeY; ++j) EventLog.push_back({ 3,PosMeX,j }); // 新建左侧子机
	for (int j = PosMeY + power; j > PosMeY; --j) EventLog.push_back({ 3,PosMeX,j }); // 新建右侧子机
	for (int j = PosMeY - power; j <= PosMeY + power; ++j)
		for (int i = 2; i < PosMeX; ++i)
			EventLog.push_back({ 4,i,j }); // 新建子弹

}

int main()
{
	ini();

	thread MoveMe{ thread_MoveMe }; // 自机移动线程
	thread MoveEn{ thread_MoveEn }; // 敌机移动线程
	thread MoveDm{ thread_MoveDm }; // 弹幕移动线程
	thread MoveIt{ thread_MoveIt }; // 道具移动线程
	thread PrintS{ thread_PrintS }; // 屏幕输出线程
	PrintS.join();
	isEnd = true;
	MoveIt.join();
	MoveDm.join();
	MoveEn.join();
	MoveMe.join();

	RestoreCCP();
	system("pause");
	return 0;
}
