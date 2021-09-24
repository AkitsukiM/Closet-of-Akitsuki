#include <thread>
#include <cstdio>
#include <cstdlib>
#include <Windows.h>

using namespace std;

int ct = 0;
int st = 0;
int isEnd = 0;

void CALLBACK TimerProc(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
	printf("WM_TIMER in work thread count = %d\n", ct++);
}

void thread_timer()
{
	SetTimer(NULL, 0, 1000, TimerProc);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_TIMER) DispatchMessage(&msg);
		if (ct == 6) break;
	}
	KillTimer(NULL, 0);
}

void CALLBACK ScreenProc(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime)
{
	if (st % 2 == 0) system("color fc");
	else system("color 0f");
	st++;
}

void thread_screen()
{
	SetTimer(NULL, 1, 500, ScreenProc);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_TIMER) DispatchMessage(&msg);
		if (isEnd == 1) break;
	}
	KillTimer(NULL, 1);
}

int main()
{
	thread timer{ thread_timer };
	thread screen{ thread_screen };
	timer.join();
	isEnd = 1;
	screen.join();

	system("pause");
	return 0;
}
