#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Cell
{
	int is; // 是否有雷 (0无雷/1有雷)
	int number; // 周围雷数
	int sign; // 标记 (0未标记/1地雷标记/2疑问标记/3已打开)
};

struct Cell a[12][12]; // a[line + 2][column + 2]
const int line = 10, column = 10, mine = 10; // 行数/列数/地雷数

void print_num(int num)
{
	if (num == 0) printf("  ");
	else if (num == 1) printf("%c%c", 0xa2, 0xd9);
	else if (num == 2) printf("%c%c", 0xa2, 0xda);
	else if (num == 3) printf("%c%c", 0xa2, 0xdb);
	else if (num == 4) printf("%c%c", 0xa2, 0xdc);
	else if (num == 5) printf("%c%c", 0xa2, 0xdd);
	else if (num == 6) printf("%c%c", 0xa2, 0xde);
	else if (num == 7) printf("%c%c", 0xa2, 0xdf);
	else if (num == 8) printf("%c%c", 0xa2, 0xe0);
	else printf("%c%c", 0xa2, 0xe1);
}

// 函数：用以打开未标记格
void o_o(struct Cell *pointer, int x, int y, int click)
{
	if (x > 0 && x <= line && y > 0 && y <= column) // 必须限定范围
	{
		if (click == 0) // 左键单击
		{
			struct Cell *temp;
			if ((*(pointer + x*(column + 2) + y)).sign == 3)
			{
				int count = 0;
				for (int s = -1; s <= 1; ++s)
					for (int t = -1; t <= 1; ++t)
					{
						temp = pointer + (x + s)*(column + 2) + y + t;
						if ((*temp).sign == 1) count++;
					}
				// 如果已打开则当周围雷数等于周边地雷标记数时打开周边未标记格
				if ((*(pointer + x*(column + 2) + y)).number == count)
				{
					for (int s = -1; s <= 1; ++s)
						for (int t = -1; t <= 1; ++t)
						{
							temp = pointer + (x + s)*(column + 2) + y + t;
							if ((*temp).sign == 0) o_o(pointer, x + s, y + t, 0);
						}
				}
			}
			if ((*(pointer + x*(column + 2) + y)).sign == 0)
			{
				(*(pointer + x*(column + 2) + y)).sign = 3; // 如果未标记则打开
				if ((*(pointer + x*(column + 2) + y)).number == 0) // 如果打开后为零则继续打开周边未标记格
				{
					for (int s = -1; s <= 1; ++s)
						for (int t = -1; t <= 1; ++t)
						{
							temp = pointer + (x + s)*(column + 2) + y + t;
							if ((*temp).sign == 0) o_o(pointer, x + s, y + t, 0);
						}
				}
			}
		}
		else // 右键单击
		{
			if ((*(pointer + x*(column + 2) + y)).sign < 3)
				(*(pointer + x*(column + 2) + y)).sign
				= ((*(pointer + x*(column + 2) + y)).sign + 1) % 3;
		}
	}
}

int main()
{
	// 打开状态初始化
	for (int i = 0; i <= line + 1; ++i)
		for (int j = 0; j <= column + 1; ++j)
			a[i][j].sign = 0;

	// 虚拟区域设为已打开
	for (int i = 0; i <= line + 1; ++i) a[i][0].sign = a[i][column + 1].sign = 3;
	for (int j = 1; j <= column; ++j) a[0][j].sign = a[line + 1][j].sign = 3;

	// 未打开的地图输出
	for (int i = 0; i < line; ++i)
	{
		for (int j = 0; j < column; ++j)
			printf("%c%c", 0xa8, 0x80);
		printf("\n");
	}

	// 投放地雷
	int position = 0, x = 0, y = 0, xx = 0, yy = 0, is_click = 0;
	scanf("%d%d%d", &xx, &yy, &is_click); // 输入行/列/0左键1右键
	srand((unsigned)time(NULL));
	do
	{
		// 地雷状态初始化
		for (int i = 0; i <= line + 1; ++i)
			for (int j = 0; j <= column + 1; ++j)
				a[i][j].is = a[i][j].number = 0;

		// 投放地雷
		for (int i = 1; i <= mine; ++i)
		{
			position = rand() % (line * column);
			y = position % column + 1;
			x = (position - y) / column + 1;
			if (a[x][y].is == 1)
			{
				i -= 1;
				continue;
			} // 若已有雷则重新投放
			else
				a[x][y].is = 1;
		}

		// 局域地雷计数
		for (int s = -1; s <= 1; ++s)
			for (int t = -1; t <= 1; ++t)
				if (a[xx + s][yy + t].is == 1) a[xx][yy].number++;
	} while (a[xx][yy].number != 0); // 若计数不为零则重置地图

	// 地雷计数
	for (int i = 1; i <= line; ++i)
		for (int j = 1; j <= column; ++j)
			for (int s = -1; s <= 1; ++s)
				for (int t = -1; t <= 1; ++t)
					if (a[i + s][j + t].is == 1) a[i][j].number++;

	int count;
	struct Cell *first = &a[0][0];

	// 用户操作
	while (1)
	{
		o_o(first, xx, yy, is_click);
		// 检测是否正确扫雷
		count = 0;
		for (int i = 1; i <= line; ++i)
			for (int j = 1; j <= column; ++j)
			{
				if (a[i][j].sign == 3 && a[i][j].is == 1)
				{
					system("cls");
					for (int ii = 1; ii <= line; ++ii)
					{
						for (int jj = 1; jj <= column; ++jj)
						{
							if (ii == i&&jj == j)
								printf("%c%c", 0xa8, 0x92); // 点开地雷处显示圈加
							else if (a[ii][jj].sign == 3)
								print_num(a[ii][jj].number); // 正确点开处显示数字
							else if ((a[ii][jj].sign == 1 || a[ii][jj].sign == 2) && a[ii][jj].is == 1)
								printf("%c%c", 0xa1, 0xf1); // 标记正确显示地雷
							else if ((a[ii][jj].sign == 1 || a[ii][jj].sign == 2) && a[ii][jj].is == 0)
								printf("%c%c", 0xa1, 0xc1); // 标记错误显示叉
							else if (a[ii][jj].is == 1)
								printf("%c%c", 0xa8, 0x91); // 未标记未打开的雷显示圈点
							else
								printf("%c%c", 0xa8, 0x80); // 其他原装
						}
						printf("\n");
					}
					printf("%d %d %d\n", xx, yy, is_click);
					getchar(); getchar();
					return 0; // 游戏失败
				}
				if (a[i][j].sign == 3) count++;
			}

		// 若检测无误则显示
		system("cls");
		for (int ii = 1; ii <= line; ++ii)
		{
			for (int jj = 1; jj <= column; ++jj)
			{
				if (a[ii][jj].sign == 3) print_num(a[ii][jj].number); // 显示数字
				else if (a[ii][jj].sign == 2) printf("%c%c", 0xa3, 0xbf); // 显示问号
				else if (a[ii][jj].sign == 1) printf("%c%c", 0xa1, 0xf1); // 显示地雷
				else printf("%c%c", 0xa8, 0x80); // 其他原装
			}
			printf("\n");
		}

		if (count == line*column - mine) break; // 游戏胜利
		scanf("%d%d%d", &xx, &yy, &is_click); // 继续输入
	}

	getchar(); getchar();
	return 0;
}
