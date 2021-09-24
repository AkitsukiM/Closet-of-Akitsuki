#include <cstdio>
#include <cstdlib>
#include <Windows.h>

int main()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	
	DWORD fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT; SetConsoleMode(hIn, fdwMode);
	
	INPUT_RECORD mouseRec;
	DWORD res;

	while (1)
	{
		ReadConsoleInput(hIn, &mouseRec, 2, &res);
		if (mouseRec.EventType == MOUSE_EVENT)
		{
			if (mouseRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK) break;
			if (mouseRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				int mouseX = mouseRec.Event.MouseEvent.dwMousePosition.X;
				int mouseY = mouseRec.Event.MouseEvent.dwMousePosition.Y;
				printf("Position: (%d, %d)\n", mouseX, mouseY);
			}
		}
	}

	system("pause");
	return 0;
}
