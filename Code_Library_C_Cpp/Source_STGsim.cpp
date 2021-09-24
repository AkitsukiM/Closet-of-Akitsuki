/*
* Simplified STG Game at the Command Prompt
* Version 1.1.2
* (c) 2018 �����ħ������^. All rights reserved.
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

HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // ��ȡ��׼����豸���
HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE); // ��ȡ��׼�����豸���

int a[34][44]; // һ�� (m + 4) * (n + 4) �ľ���ʵ�ʳ� x: 2 - (m + 1); y: 2 - (n + 1)
const int m = 30, n = 40; // һ�� m * n �ĳ�

bool isEnd = false;

int PosMeX = m, PosMeY = n / 2 + 2, power = 2; // ����X������Y��Powerֵ�����Ϊ2��

int Time_EveryMove = 1000; // �л���е����ƶ����ʱ��
int StepEnemy = 1;
int StepDanmaku = 1;

// �л���е��� // �������¼���־��Ԫ��ࣿ������Ҫ����Ϊ�á�
struct Pos
{
	int Style;
	int X;
	int Y;
};

list<Pos> Enemy;
list<Pos> Danmaku;

// �¼���־��Ԫ
struct EVENT
{
	int Style;
	int X;
	int Y;
};
// �¼���־
vector<EVENT> EventLog;

// ���ù��
void RestoreCCP()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,m + 4 });
}

// ������ֵ����ʾ����ģ��
void SetCCP(int x, int y, int style)
{
	// ������ʾ��ײ��>�л�>��Ļ>����>�ӵ�>�ӻ�
	if (style > a[x][y] || style <= 2)
	{
		// ��x�е�y�и�������
		a[x][y] = style;

		// ��ֹ���
		if (x >= 2 && x <= m + 1 && y >= 2 && y <= n + 1)
		{
			// ������ڸø�ĺ�һλ
			SetConsoleCursorPosition(hOut, { (short)(y + 1),(short)(x) });

			// �˸񲢸���
			if (style == 0) printf("\b ");
			else if (style == 1) printf("\bA"); // �Ի���������
			else if (style == 2) printf("\bA"); // �Ի����˳���
			else if (style == 3) printf("\b "); // �ӻ�
			else if (style == 4) printf("\b*"); // �ӵ�
			else if (style == 11) printf("\bP"); // ���ߣ�P��
			else if (style == 21) printf("\bO"); // ��Ļ
			else if (style == 31) printf("\bV"); // �л�
			else if (style == 100) printf("\b!"); // ײ��
			else
				;
		}
	}
}

// �Ի��ƶ��̺߳���
void thread_MoveMe()
{
	INPUT_RECORD keyRec;
	DWORD res;
	while (isEnd == false)
	{
		ReadConsoleInput(hIn, &keyRec, 1, &res);
		if (keyRec.EventType == KEY_EVENT)
		{
			// ��ESC��
			if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
				EventLog.push_back({ 2,PosMeX,PosMeY });
			else if (keyRec.Event.KeyEvent.bKeyDown)
			{
				if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_LEFT && PosMeY > 2)
				{
					EventLog.push_back({ 0,PosMeX,PosMeY }); // �����Ի�
					for (int i = 2; i < PosMeX; ++i)
						if (a[i][PosMeY + power] == 4) // �������Ϊ�ӵ�
							EventLog.push_back({ 0,i,PosMeY + power }); // �����ӵ�
					if (power > 0) 
						if (a[PosMeX][PosMeY + power] == 3) // �������Ϊ�ӻ�
							EventLog.push_back({ 0,PosMeX,PosMeY + power }); // �����ӻ�
					PosMeY--;
					for (int i = 2; i < PosMeX; ++i) EventLog.push_back({ 4,i,PosMeY - power }); // �½��ӵ�
					if (power > 0) EventLog.push_back({ 3,PosMeX,PosMeY - power }); // �½��ӻ�
				}
				else if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_UP && PosMeX > 2)
				{
					for (int j = PosMeY - power; j <= PosMeY + power; ++j)
					{
						if (a[PosMeX][j] < 10) // ������ǳ־õ��˻�е�
							EventLog.push_back({ 0,PosMeX,j }); // �����Ի����ӻ�
						if (a[PosMeX - 1][j] == 4) // ������ǳ־õ��˻�е�
							EventLog.push_back({ 0,PosMeX - 1,j }); // �����ӵ�
					}
					PosMeX--;
					for (int j = PosMeY - power; j < PosMeY; ++j) EventLog.push_back({ 3,PosMeX,j }); // �½�����ӻ�
					for (int j = PosMeY + power; j > PosMeY; --j) EventLog.push_back({ 3,PosMeX,j }); // �½��Ҳ��ӻ�
				}
				else if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT && PosMeY < n + 1)
				{
					EventLog.push_back({ 0,PosMeX,PosMeY }); // �����Ի�
					for (int i = 2; i < PosMeX; ++i)
						if (a[i][PosMeY - power] == 4) // �������Ϊ�ӵ�
							EventLog.push_back({ 0,i,PosMeY - power }); // �����ӵ�
					if (power > 0)
						if (a[PosMeX][PosMeY - power] == 3) // �������Ϊ�ӻ�
							EventLog.push_back({ 0,PosMeX,PosMeY - power }); // �����ӻ�
					PosMeY++;
					for (int i = 2; i < PosMeX; ++i) EventLog.push_back({ 4,i,PosMeY + power }); // �½��ӵ�
					if (power > 0) EventLog.push_back({ 3,PosMeX,PosMeY + power }); // �½��ӻ�
				}
				else if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_DOWN && PosMeX < m + 1)
				{
					for (int j = PosMeY - power; j <= PosMeY + power; ++j) EventLog.push_back({ 4,PosMeX,j }); // �½��ӵ�
					PosMeX++;
					for (int j = PosMeY - power; j < PosMeY; ++j) EventLog.push_back({ 3,PosMeX,j }); // �½�����ӻ�
					for (int j = PosMeY + power; j > PosMeY; --j) EventLog.push_back({ 3,PosMeX,j }); // �½��Ҳ��ӻ�
				}
				else
					;

				if (a[PosMeX][PosMeY] > 20) EventLog.push_back({ 100,PosMeX,PosMeY }); // �ж�ײ��
				else if (a[PosMeX][PosMeY] == 11) 
				{
					power++; // Power����
					EventLog.push_back({ 0,PosMeX,PosMeY }); // ����P��
					EventLog.push_back({ 1,PosMeX,PosMeY }); // �½��Ի�
				}
				else EventLog.push_back({ 1,PosMeX,PosMeY }); // �½��Ի�
			}
			else
				;
		}
	}
}

// �л��ƶ��̺߳���
void thread_MoveEn()
{

}

void CALLBACK Timer_MoveDm(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime)
{
	srand((unsigned)time(NULL));
	for (auto iter = Danmaku.begin(); iter != Danmaku.end(); ++iter)
	{
		if ((*iter).Style == a[(*iter).X][(*iter).Y]) // �������Ϊ��Ļ
			EventLog.push_back({ 0,(*iter).X,(*iter).Y }); // ������Ļ

		// �ƶ���Ļ
		(*iter).X += (rand() % (2 * StepDanmaku + 1) - StepDanmaku);
		(*iter).Y += (rand() % (2 * StepDanmaku + 1) - StepDanmaku);
		// ��ĻԽ����ĻʧЧ��ע�������ʹ�ã�
		if ((*iter).X < 2 || (*iter).X > m + 1 || (*iter).Y < 2 || (*iter).Y > n + 1)
		{
			auto one_off_iter = iter;
			--iter;
			Danmaku.erase(one_off_iter);
		}
		else
		{
			int num = a[(*iter).X][(*iter).Y];
			if (num == 1) EventLog.push_back({ 100,(*iter).X,(*iter).Y }); // �Ի�ײ���ж�
			else EventLog.push_back({ (*iter).Style,(*iter).X,(*iter).Y });
		}
	}
}

// ��Ļ�ƶ��̺߳���
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

// �����ƶ��̺߳���
void thread_MoveIt()
{

}

// ��Ļ����̺߳���
void thread_PrintS()
{
	// ��ʼ�����ʿ������β
	int i = 0, ed = EventLog.size();
	while (isEnd == false)
	{
		for (; i != ed; ++i)
		{
			SetCCP((EventLog[i]).X, (EventLog[i]).Y, (EventLog[i]).Style);
			// ������������ײ��������Ľ�����ʶ������ѭ��
			if ((EventLog[i]).Style == 2 || (EventLog[i]).Style == 100)
			{
				isEnd = true; break;
			}
			RestoreCCP();
		}
		// ���÷��ʿ������β����for���������ƺ���������i��
		// i = ed;
		ed = EventLog.size();
		
		// ����ʱisEnd == false�ͻ�����whileѭ��������������
	}
}

// ��ʼ������
void ini()
{
	// ǰ�˴������
	ShowWindow(GetForegroundWindow(), SW_MAXIMIZE);

	// ��ʼ��������ӡ // -1 ��ʾ�߽� // 0 ��ʾ�ո�
	for (int i = 0; i <= m + 3; ++i)
	{
		if (i == 0 || i == m + 3) // ��һ�������һ�� // ֵ��Ϊ-1 // �����Ϊ" "
		{
			for (int j = 0; j <= n + 3; ++j)
			{
				a[i][j] = -1; printf(" ");
			}
		}
		else if (i == 1 || i == m + 2) // �ڶ����뵹���ڶ��� // ֵ��Ϊ-1 // ��һ�������һ�����" "���������"="
		{
			a[i][0] = -1; printf(" ");
			for (int j = 1; j <= n + 2; ++j)
			{
				a[i][j] = -1; printf("=");
			}
			a[i][n + 3] = -1; printf(" ");
		}
		else // ���� // ��һ�������һ��ֵΪ-1�����" "���ڶ����뵹���ڶ���ֵΪ-1�����"|"���м�ֵΪ0�����" "
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

	// ע���Ի�/�ӻ�/�ӵ�
	EventLog.push_back({ 1,PosMeX,PosMeY }); // �½��Ի�
	for (int j = PosMeY - power; j < PosMeY; ++j) EventLog.push_back({ 3,PosMeX,j }); // �½�����ӻ�
	for (int j = PosMeY + power; j > PosMeY; --j) EventLog.push_back({ 3,PosMeX,j }); // �½��Ҳ��ӻ�
	for (int j = PosMeY - power; j <= PosMeY + power; ++j)
		for (int i = 2; i < PosMeX; ++i)
			EventLog.push_back({ 4,i,j }); // �½��ӵ�

}

int main()
{
	ini();

	thread MoveMe{ thread_MoveMe }; // �Ի��ƶ��߳�
	thread MoveEn{ thread_MoveEn }; // �л��ƶ��߳�
	thread MoveDm{ thread_MoveDm }; // ��Ļ�ƶ��߳�
	thread MoveIt{ thread_MoveIt }; // �����ƶ��߳�
	thread PrintS{ thread_PrintS }; // ��Ļ����߳�
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
