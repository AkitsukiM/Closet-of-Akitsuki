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

struct Cell a[18][32]; // a[line + 2][column + 2]
struct Cell a_copy[18][32];
const int line = 16, column = 30, mine = 99; // 行数/列数/地雷数

int previous = 0, next = 0; // 暂时用于对o_o的调用次数进行计数
int success = 1; // 反证执行判断

int count_mine, count_opened, count_progress; // 计数

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
			if ((*(pointer + x * (column + 2) + y)).sign == 3)
			{
				int count = 0;
				for (int s = -1; s <= 1; ++s)
					for (int t = -1; t <= 1; ++t)
					{
						temp = pointer + (x + s)*(column + 2) + y + t;
						if ((*temp).sign == 1) count++;
					}
				// 如果已打开则当周围雷数等于周边地雷标记数时打开周边未标记格
				if ((*(pointer + x * (column + 2) + y)).number == count)
				{
					for (int s = -1; s <= 1; ++s)
						for (int t = -1; t <= 1; ++t)
						{
							temp = pointer + (x + s)*(column + 2) + y + t;
							if ((*temp).sign == 0) o_o(pointer, x + s, y + t, 0);
						}
				}
			}
			if ((*(pointer + x * (column + 2) + y)).sign == 0)
			{
				(*(pointer + x * (column + 2) + y)).sign = 3; // 如果未标记则打开
				if ((*(pointer + x * (column + 2) + y)).number == 0) // 如果打开后为零则继续打开周边未标记格
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
			if ((*(pointer + x * (column + 2) + y)).sign < 3)
				(*(pointer + x * (column + 2) + y)).sign
				= ((*(pointer + x * (column + 2) + y)).sign + 1) % 3;
		}
		next++;
	}
}

void autoplay(struct Cell *pointer)
{
	int mine_count, unsigned_count, number_temp;
	struct Cell *temp;
	for (int i = 1; i <= line; ++i)
		for (int j = 1; j <= column; ++j)
		{
			// 调取周边地雷数
			number_temp = (*(pointer + i * (column + 2) + j)).number;
			mine_count = unsigned_count = 0;

			// 如果已打开且周边地雷数不为零(即显示数字格)则执行操作
			if ((*(pointer + i * (column + 2) + j)).sign == 3 && number_temp != 0)
			{
				// 计数地雷标记数/计数未标记数
				for (int s = -1; s <= 1; ++s)
					for (int t = -1; t <= 1; ++t)
					{
						temp = pointer + (i + s)*(column + 2) + j + t;
						if ((*temp).sign == 1) mine_count++;
						if ((*temp).sign == 0) unsigned_count++;
					}

				// 若数字格的数减去地雷标记数等于零且不等于未标记数则打开周边八格所有未标记格
				if (number_temp - mine_count == 0 && unsigned_count != 0) o_o(pointer, i, j, 0);

				// 若数字格的数减去地雷标记数等于未标记数则对周边八格所有未标记格进行地雷标记
				if (number_temp - mine_count == unsigned_count)
				{
					for (int s = -1; s <= 1; ++s)
						for (int t = -1; t <= 1; ++t)
						{
							temp = pointer + (i + s)*(column + 2) + j + t;
							if ((*temp).sign == 0) o_o(pointer, i + s, j + t, 1);
						}
				}
			}
		}
}

void logic(struct Cell *pointer, struct Cell *pointer_copy)
{
	// pass：是否为考察对象(0否/1是). 
	int pass, mine_count, unsigned_count, number_temp;
	struct Cell *temp;

	// 遍历地图
	for (int i = 1; i <= line; ++i)
		for (int j = 1; j <= column; ++j)
		{
			// 初始化pass
			pass = 0;
			// 若a[i][j]未标记
			if ((*(pointer + i * (column + 2) + j)).sign == 0)
			{
				// 且a[i][j]周边有已打开的格子则a[i][j]为考察对象
				for (int s = -1; s <= 1; ++s)
					for (int t = -1; t <= 1; ++t)
						if ((*(pointer + (i + s)*(column + 2) + j + t)).sign == 3
							&& (*(pointer + (i + s)*(column + 2) + j + t)).number != 0) pass = 1;
			}

			// 若a[i][j]为考察对象
			if (pass == 1)
			{
				// 反证判断(0反证失败/1反证成功)
				int disproof = 0;
				if (disproof == 0)
				{
					// a_copy为a的一个副本
					for (int ii = 0; ii <= line + 1; ++ii)
						for (int jj = 0; jj <= column + 1; ++jj)
						{
							(*(pointer_copy + ii * (column + 2) + jj)).number
								= (*(pointer + ii * (column + 2) + jj)).number;
							(*(pointer_copy + ii * (column + 2) + jj)).sign
								= (*(pointer + ii * (column + 2) + jj)).sign;
						}

					// 假设考察对象为地雷
					(*(pointer_copy + i * (column + 2) + j)).sign = 1;
					// 低阶逻辑推理
					autoplay(pointer_copy);
					// 逻辑推理验证
					// 遍历地图
					for (int ii = 1; ii <= line; ++ii)
						for (int jj = 1; jj <= column; ++jj)
						{
							// 若a[ii][jj]已打开
							if ((*(pointer + ii * (column + 2) + jj)).sign == 3)
							{
								// 调取a[ii][jj]周边地雷数
								number_temp = (*(pointer + ii * (column + 2) + jj)).number;
								mine_count = unsigned_count = 0;
								// 对a_copy[ii][jj]计数地雷标记数/计数未标记数
								for (int s = -1; s <= 1; ++s)
									for (int t = -1; t <= 1; ++t)
									{
										temp = pointer_copy + (ii + s)*(column + 2) + jj + t;
										if ((*temp).sign == 1) mine_count++;
										if ((*temp).sign == 0) unsigned_count++;
									}
								// 若周边都已打开或标记但(副本的)地雷标记数不等于(原本的)周边地雷数
								if (unsigned_count == 0 && mine_count != number_temp)
								{
									// 矛盾！故考察对象可以打开
									o_o(pointer, i, j, 0);
									// 反证成功
									disproof = success = 1;
								}
							}
						}
				}
				// 若反证不成功
				if (disproof == 0)
				{
					// 重做副本
					for (int ii = 0; ii <= line + 1; ++ii)
						for (int jj = 0; jj <= column + 1; ++jj)
						{
							(*(pointer_copy + ii * (column + 2) + jj)).number
								= (*(pointer + ii * (column + 2) + jj)).number;
							(*(pointer_copy + ii * (column + 2) + jj)).sign
								= (*(pointer + ii * (column + 2) + jj)).sign;
						}

					// 假设考察对象不为地雷
					(*(pointer_copy + i * (column + 2) + j)).sign = 3;
					// 低阶逻辑推理
					autoplay(pointer_copy);
					// 遍历地图
					for (int ii = 1; ii <= line; ++ii)
						for (int jj = 1; jj <= column; ++jj)
						{
							// 若a[ii][jj]已打开
							if ((*(pointer + ii * (column + 2) + jj)).sign == 3)
							{
								// 调取a[ii][jj]周边地雷数
								number_temp = (*(pointer + ii * (column + 2) + jj)).number;
								mine_count = unsigned_count = 0;
								// 对a_copy[ii][jj]计数地雷标记数/计数未标记数
								for (int s = -1; s <= 1; ++s)
									for (int t = -1; t <= 1; ++t)
									{
										temp = pointer_copy + (ii + s)*(column + 2) + jj + t;
										if ((*temp).sign == 1) mine_count++;
										if ((*temp).sign == 0) unsigned_count++;
									}
								// 若周边都已打开或标记但(副本的)地雷标记数不等于(原本的)周边地雷数
								if (unsigned_count == 0 && number_temp != mine_count)
								{
									// 矛盾！故考察对象为地雷
									(*(pointer + i * (column + 2) + j)).sign = 1;
									// 反证成功
									disproof = success = 1;
								}
							}
						}
				}
			}
		}
}

void result_print()
{
	// system("pause");
	// 进度计数
	count_mine = count_opened = 0;
	for (int ii = 1; ii <= line; ++ii)
		for (int jj = 1; jj <= column; ++jj)
		{
			if (a[ii][jj].sign == 1) count_mine++; // 地雷计数
			if (a[ii][jj].sign == 3) count_opened++; // 已打开格计数
		}
	count_progress = (count_mine + count_opened) * 100 / (line * column);

	// 若检测无误则显示
	system("cls");
	// 装饰
	printf("Progress: %d%c\tMines: %d / %d\n\n", count_progress, '%', count_mine, mine);
	for (int jj = 0; jj < column; ++jj) printf("==");
	printf("\n\n");
	// 正文
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
	// 装饰
	printf("\n");
	for (int jj = 0; jj < column; ++jj) printf("==");
	printf("\n\n");
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

	// When autoplay, this line is unnecessary.
	// scanf("%d%d%d", &xx, &yy, &is_click); // 输入行/列/0左键1右键

	srand((unsigned)time(NULL));

	// For autoplay
	// 注：随机有两种办法. 一种是行列各自随机. 一种是数字随机转换成行列.
	xx = rand() % line + 1;
	yy = rand() % column + 1;

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

	struct Cell *first = &a[0][0];
	struct Cell *first_copy = &a_copy[0][0];

	while (1)
	{
		// 用户操作
		// 在Autoplay状态下无需用户输入
		// o_o(first, xx, yy, is_click);

		// 自动操作
		// 在低阶与高阶逻辑推理均失效时，点开任意格
		while (a[xx][yy].sign != 0) // 第一次：没有打开任何格子故sign依旧为0
		{
			xx = rand() % line + 1;
			yy = rand() % column + 1;
		}
		o_o(first, xx, yy, is_click);

		// 失败的判断
		for (int s = -1; s <= 1; ++s)
			for (int t = -1; t <= 1; ++t)
			{
				if (a[xx + s][yy + t].sign == 3 && a[xx + s][yy + t].is == 1)
				{
					system("cls");
					// 装饰
					printf("Progress: %d%c\tMines: %d / %d\n\n", count_progress, '%', count_mine, mine);
					for (int jj = 0; jj < column; ++jj) printf("==");
					printf("\n\n");
					// 正文
					for (int ii = 1; ii <= line; ++ii)
					{
						for (int jj = 1; jj <= column; ++jj)
						{
							if (ii == xx + s && jj == yy + t)
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
					// 装饰
					printf("\n");
					for (int jj = 0; jj < column; ++jj) printf("==");
					printf("\n\n");

					printf("You lose. Error:  %d  %d\n", xx, yy);
					getchar(); // getchar();
					return 0; // 游戏失败
				}
			}

		// 内循环低阶逻辑推理/外循环高阶逻辑推理
		while (success != 0) // success的初始值为1：进入循环
		{
			while (previous != next) // 调用了o_o函数且没有重调故previous和next必然不等：进入循环
			{
				previous = next;
				autoplay(first); // 当无法继续进行低阶逻辑推理时previous == next：此时退出循环
			}
			success = 0;
			logic(first, first_copy); // 当无法继续进行高阶逻辑推理时success的值不会改变：此时退出循环
		}

		// 重置previous/next/success
		previous = next;
		success = 1;

		result_print(); // 结果输出

		// 胜利的判断
		if (count_opened == line * column - mine)
		{
			printf("You win.\n");
			break; // 游戏胜利
		}

		// 在Autoplay状态下无需用户输入
		// scanf("%d%d%d", &xx, &yy, &is_click); // 继续输入
	}

	getchar(); // getchar();
	return 0;
}
