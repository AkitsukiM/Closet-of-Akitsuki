#include "Header.h"

/* Part.2 棋盘打印模块 ************************************************** */

// 打印行标
void printLineNumber(int i)
{
	printf("%2d ", SIDELENGTH + 1 - i);
}

// 打印列标
void printColumnNumber(int j)
{
	printf("%c ", j + 64);
}

// 打印单元格
void printCell(int i, int j)
{
	if (a[i][j] == 2) printf("●"); // printf("%c%c", 0xa1, 0xf1); // 执黑为2标记为实心圆
	else if (a[i][j] == 1) printf("◎"); // printf("%c%c", 0xa1, 0xf2); // 执白为1标记为空心圆
	else
	{
		if (i == 1)
		{
			if (j == 1) printf("┏"); // printf("%c%c", 0xa9, 0xb3);
			else if (j == SIDELENGTH) printf("┓"); // printf("%c%c", 0xa9, 0xb7);
			else printf("┯"); // printf("%c%c", 0xa9, 0xd3);
		}
		else if (i == SIDELENGTH)
		{
			if (j == 1) printf("┗"); // printf("%c%c", 0xa9, 0xbb);
			else if (j == SIDELENGTH) printf("┛"); // printf("%c%c", 0xa9, 0xbf);
			else printf("┷"); // printf("%c%c", 0xa9, 0xdb);
		}
		else
		{
			if (j == 1) printf("┠"); // printf("%c%c", 0xa9, 0xc4);
			else if (j == SIDELENGTH) printf("┨"); // printf("%c%c", 0xa9, 0xcc);
			else printf("┼"); // printf("%c%c", 0xa9, 0xe0);
		}
		SPACE;
	}
}

// 打印棋盘. 输入最近一步的位置和步数
void printChessboard(int i, int j)
{
	CLEARSCREEN;

	for (int p = 1; p <= SIDELENGTH; ++p)
	{
		printLineNumber(p); // 打印左侧行标
		for (int q = 1; q <= SIDELENGTH; ++q)
		{
			if (p == i && q == j)
			{
				if (a[i][j] == 2) printf("▲"); // printf("%c%c", 0xa1, 0xf8); // 最近一着黑子标记为实心角
				else printf("△"); // printf("%c%c", 0xa1, 0xf7); // 最近一着白子标记为空心角
			}
			else
				printCell(p, q); // 打印单元格
		}
		printf("\n");
	}

	printf("   "); SPACE; // 补三格空位

	for (int q = 1; q <= SIDELENGTH; ++q) printColumnNumber(q); // 打印底侧列标
	printf("\n\nLast step: (%d, %d) / (%d, %c)\n", i, j,
		(i == 0) ? 0 : SIDELENGTH + 1 - i, (j == 0) ? '0' : 'A' + j - 1); // 特增行
}
