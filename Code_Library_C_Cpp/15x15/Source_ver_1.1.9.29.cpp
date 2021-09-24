/*
* Gobang Console Game
* Version 1.1.9.31
* (c) 2018 ヴワル魔法図書館. All rights reserved.
* 
* Date modified: 2018/08/31
* Update Info:
* 1. 
* Bug Report:
* 1. 
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

const int m = 15;
const int center = m / 2 + 1; // 方便使用中心点
const int mm = m + 2; // 方便使用指针
int a[17][17]; // 将棋盘虚延一圈视为一个(m+2)*(m+2)的矩阵
int at[17][17], ar[21][17], al[21][17]; // at为转置矩阵. ar, al为两个(2m-9)*(m+2)的斜向矩阵.

int *first[4] = { &a[0][0], &at[0][0], &ar[0][0], &al[0][0] };
int **aa = &first[0];

int player_i[225], player_j[225]; // 历史记录

// double time_total = 0, time_black = 0, time_white = 0;

// 数字重排程序：除9以外的数字从大到小排列
int trick(unsigned int num)
{
	int x[10] = { 0,0,0,0,0,0,0,0,0,0 };
	int temp = 0;

	// 分离数字
	do
	{
		x[num % 10]++;
		num = (num - num % 10) / 10;
	} while (num > 0);

	// 重排模块
	for (int i = 8; i >= 0; --i)
		for (int j = 0; j != x[i]; ++j)
			temp = temp * 10 + i;
	for (int j = 0; j != x[9]; ++j)
		temp = temp * 10 + 9;
	return temp;
}

// 打印行标
void print_Ln(int i)
{
	printf("%c ", i + 64);
}

// 打印列标
void print_Col(int j)
{
	switch (j)
	{
	case 1: printf("%c%c", 0xa2, 0xc5); break;
	case 2: printf("%c%c", 0xa2, 0xc6); break;
	case 3: printf("%c%c", 0xa2, 0xc7); break; 
	case 4: printf("%c%c", 0xa2, 0xc8); break;
	case 5: printf("%c%c", 0xa2, 0xc9); break;
	case 6: printf("%c%c", 0xa2, 0xca); break;
	case 7: printf("%c%c", 0xa2, 0xcb); break;
	case 8: printf("%c%c", 0xa2, 0xcc); break;
	case 9: printf("%c%c", 0xa2, 0xcd); break;
	case 10: printf("%c%c", 0xa2, 0xce); break;
	case 11: printf("%c%c", 0xa2, 0xcf); break;
	case 12: printf("%c%c", 0xa2, 0xd0); break;
	case 13: printf("%c%c", 0xa2, 0xd1); break;
	case 14: printf("%c%c", 0xa2, 0xd2); break;
	case 15: printf("%c%c", 0xa2, 0xd3); break;
	default: printf("  ");
	}
}

// 打印单元格
void print_Cell(int i, int j)
{
	if (a[i][j] == 2) printf("%c%c", 0xa1, 0xf1); // 执黑为2标记为实心圆
	else if (a[i][j] == 1) printf("%c%c", 0xa1, 0xf0); //执白为1标记为空心圆
	else
	{
		if (j == m)
		{
			if (i == 1) printf("%c%c", 0xa9, 0xb4);
			else if (i == m) printf("%c%c", 0xa9, 0xbc);
			else printf("%c%c", 0xa9, 0xc8);
		}
		else if (j == 1)
		{
			if (i == 1) printf("%c%c", 0xa9, 0xb0);
			else if (i == m) printf("%c%c", 0xa9, 0xb8);
			else printf("%c%c", 0xa9, 0xc0);
		}
		else
		{
			if (i == 1) printf("%c%c", 0xa9, 0xd0);
			else if (i == m) printf("%c%c", 0xa9, 0xd8);
			else printf("%c%c", 0xa9, 0xe0);
		}
	}
}

// 打印棋盘
void print_Chess(int i, int j, int step)
{
	// printf("Black:  %.1f\tWhite:  %.1f\n\n", time_black, time_white); // 特别打印！

	printf("  "); // 特增行*
	for (int q = 0; q <= m; ++q) print_Col(q); // 打印最上端列标行
	printf("\n");

	for (int p = 1; p <= m; ++p)
	{
		print_Ln(p); // 打印行标
		print_Col(p); // 特增行*
		for (int q = 1; q <= m; ++q)
		{
			if (p == i && q == j)
			{
				if (step % 2 == 1) printf("%c%c", 0xa1, 0xf6); // 最近一着黑子显示为方块
				else printf("%c%c", 0xa1, 0xf2); // 最近一着白子显示为双圆
			}
			else
				print_Cell(p, q); // 打印单元格
		}
		printf("\n");
	}
	printf("\nLast Step: (%d, %d)\n", i, j); // 特增行*
}

/*
* ar:
* "0"-"m-5": position from (0,m-5)-(6,m+1) to (0,0)-(m+1,m+1), size from 7 to m+2
* "m-5+1"-"m-5+m-5": position from (1,0)-(m+1,m) to (m-5,0)-(m+1,6), size from m+1 to 7
* al:
* "0"-"m-5": position from (0,6)-(6,0) to (0,m+1)-(m+1,0), size from 7 to m+2
* "m-5+1"-"m-5+m-5": position from (1,m+1)-(m+1,1) to (m-5,m+1)-(m+1,m-5), size from m+1 to 7
* 
* 对于a[i][j]
* ar:
* 处于编号为 i - j + m - 5 的行
* 当 i - j <= 0 时编号为 i
* 当 i - j > 0 时编号为 j
* al:
* 处于编号为 i + j - 6 的行
* 当 i + j <= m + 1 时编号为 i
* 当 i + j > m + 1 时编号为 m + 1 - j
*/

// 对特定格更新辅助矩阵
void renew_Cell(int i_x, int j_x, int **xx)
{
	int *x = *xx, *xt = *(xx + 1), *xr = *(xx + 2), *xl = *(xx + 3);

	int i_xr, j_xr;

	// 由转置矩阵可知
	*(xt + j_x * mm + i_x) = *(x + i_x * mm + j_x);

	i_xr = i_x - j_x + m - 5;
	if (i_x <= j_x) j_xr = i_x;
	else j_xr = j_x;
	// 避免溢出的漏洞补救
	if (i_xr >= 0 && i_xr <= 2 * m - 10 && j_xr >= 1 && j_xr <= m)
		*(xr + i_xr * mm + j_xr) = *(x + i_x * mm + j_x);

	i_xr = i_x + j_x - 6;
	if (i_x + j_x <= m + 1) j_xr = i_x;
	else j_xr = m + 1 - j_x;
	// 避免溢出的漏洞补救
	if (i_xr >= 0 && i_xr <= 2 * m - 10 && j_xr >= 1 && j_xr <= m)
		*(xl + i_xr * mm + j_xr) = *(x + i_x * mm + j_x);
}

// 棋子范围记录
// int tp = center, bm = center, lt = center, rt = center;
// 棋子范围拓展记录
// int tp_plus = tp - 2, bm_plus = bm + 2, lt_plus = lt - 2, rt_plus = rt + 2;

// 代理落子程序
void new_Cell(int i_x, int j_x, int **xx, int color)
{
	int *x = *xx, *xt = *(xx + 1), *xr = *(xx + 2), *xl = *(xx + 3);

	*(x + i_x * mm + j_x) = color; // 落子

	// 注：去除了棋子范围记录代码

	renew_Cell(i_x, j_x, xx); // 更新辅助矩阵
}

// 针对三一式四的特殊情况额外记录并设置为全局变量
int result_3 = 0;

// 连子状况检查单元**
int check_C(int i_x, int j_x, int *x, int result)
{
	// 避免溢出的漏洞补救
	if (x == *aa || x == *(aa + 1))
	{
		if (i_x < 1 || i_x > m || j_x < 1 || j_x > m) return result;
	}
	else
	{
		if (i_x < 0 || i_x > 2 * m - 10 || j_x < 1 || j_x > m) return result;
	}

	int color = *(x + i_x * mm + j_x);

	for (int j = j_x - 4; j <= j_x; ++j)
	{
		if (*(x + i_x * mm + j) == color && *(x + i_x * mm + j + 1) == color && *(x + i_x * mm + j + 2) == color
			&& *(x + i_x * mm + j + 3) == color && *(x + i_x * mm + j + 4) == color)
		{
			if (j < j_x && *(x + i_x * mm + j + 5) == color) result = result * 10 + 1; // 长连
			result = result * 10 + 9; // 五连
		}

		else if (*(x + i_x * mm + j + 1) == color && *(x + i_x * mm + j + 2) == color && *(x + i_x * mm + j + 3) == color && *(x + i_x * mm + j + 4) == color)
		{
			if (*(x + i_x * mm + j) < 0 && *(x + i_x * mm + j + 5) < 0)
				result = result * 10 + 8; // 四连
			else if ((*(x + i_x * mm + j) < 0 && *(x + i_x * mm + j + 5) != color) // 为避免与五连重复计数附加的条件
				|| *(x + i_x * mm + j + 5) < 0) // 注：此处不必附加条件，因为满足附加条件的已经计入五连
				result = result * 10 + 5; // 半四连
			else
				;
		}
		else if (*(x + i_x * mm + j) == color && *(x + i_x * mm + j + 1) == color && *(x + i_x * mm + j + 2) == color
			&& *(x + i_x * mm + j + 3) < 0 && *(x + i_x * mm + j + 4) == color
			&& *(x + i_x * mm + j - 1) != color) // 为避免与四连重复计数附加的条件
		{
			if (*(x + i_x * mm + j - 1) < 0 && j == j_x - 4) // 排除自由式三一顶格落子
				;
			else
			{
				// 顺三一式四
				if (j == j_x && *(x + i_x * mm + j + 5) < 0) result = result * 10 + 7; // Ooo_o_三一式四
				else result = result * 10 + 4; // 剩余所有三一式四
				if (*(x + i_x * mm + j - 1) < 0) result_3++; // 如果三一的三是独立的，记一次result_3
			}
		}
		else if (*(x + i_x * mm + j + 4) == color && *(x + i_x * mm + j + 3) == color && *(x + i_x * mm + j + 2) == color
			&& *(x + i_x * mm + j + 1) < 0 && *(x + i_x * mm + j) == color
			&& *(x + i_x * mm + j + 5) != color) // 为避免与四连重复计数附加的条件
		{
			if (*(x + i_x * mm + j + 5) < 0 && j == j_x) // 排除自由式三一顶格落子
				;
			else
			{
				// 逆三一式四
				if (j == j_x - 4 && *(x + i_x * mm + j - 1) < 0) result = result * 10 + 7; // _o_ooO三一式四
				else result = result * 10 + 4; // 剩余所有三一式四
				if (*(x + i_x * mm + j + 5) < 0) result_3++; // 如果三一的三是独立的，记一次result_3
			}
		}
		else if (*(x + i_x * mm + j) == color && *(x + i_x * mm + j + 1) == color && *(x + i_x * mm + j + 2) < 0
			&& *(x + i_x * mm + j + 3) == color && *(x + i_x * mm + j + 4) == color
			&& *(x + i_x * mm + j - 1) != color && *(x + i_x * mm + j + 5) != color) // 为避免与三一重复计数附加的条件
		{
			if (j == j_x && *(x + i_x * mm + j + 5) < 0) result = result * 10 + 7; // Oo_oo_二二式四
			else if (j == j_x - 4 && *(x + i_x * mm + j - 1) < 0) result = result * 10 + 7; // _oo_oO二二式四
			else result = result * 10 + 4; // 二二式四
		}

		else if (*(x + i_x * mm + j + 1) == color && *(x + i_x * mm + j + 2) == color && *(x + i_x * mm + j + 3) == color
			&& *(x + i_x * mm + j) < 0 && *(x + i_x * mm + j + 4) < 0
			&& *(x + i_x * mm + j - 1) != color && *(x + i_x * mm + j + 5) != color) // 为避免与三一重复计数附加的条件
			result = result * 10 + 3; // 三连
		else if (*(x + i_x * mm + j + 1) == color && *(x + i_x * mm + j + 2) == color && *(x + i_x * mm + j + 3) < 0 && *(x + i_x * mm + j + 4) == color
			&& (*(x + i_x * mm + j) < 0 && *(x + i_x * mm + j + 5) < 0))
			result = result * 10 + 2; // 二一式三
		else if (*(x + i_x * mm + j + 1) == color && *(x + i_x * mm + j + 2) < 0 && *(x + i_x * mm + j + 3) == color && *(x + i_x * mm + j + 4) == color
			&& (*(x + i_x * mm + j) < 0 && *(x + i_x * mm + j + 5) < 0))
			result = result * 10 + 2; // 一二式三
		else
			;
	}

	return result;
}

// 对特定格（必须先落子！）的一层连子状况检查
int check_Cell_1(int i_x, int j_x, int **xx)
{
	int *x = *xx, *xt = *(xx + 1), *xr = *(xx + 2), *xl = *(xx + 3);

	int result = 0; // 检查结果计为result
	result_3 = 0; // 同时初始化三一式四额外记录变量

	// 横向检查
	result = check_C(i_x, j_x, x, result);

	// 纵向检查
	result = check_C(j_x, i_x, xt, result);

	// 斜向检查，原理同上。
	int i_xr, j_xr;

	i_xr = i_x - j_x + m - 5;
	if (i_x <= j_x) j_xr = i_x;
	else j_xr = j_x;

	// 右斜向检查
	result = check_C(i_xr, j_xr, xr, result);

	i_xr = i_x + j_x - 6;
	if (i_x + j_x <= m + 1) j_xr = i_x;
	else j_xr = m + 1 - j_x;

	// 左斜向检查
	result = check_C(i_xr, j_xr, xl, result);

	result = trick(result);
	return result;
}

// 对特定格（必须先落子！）的二层连子状况检查
int check_Cell_2(int i_x, int j_x, int **xx, int color)
{
	int temp = 0, temp_3 = 0;

	int judgment_simplified(int i, int j, int check_result); // 函数声明

	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= m; ++j)
		{
			if (*(*xx + i * mm + j) < 0) // 遍历必须保证测试格为空
			{
				new_Cell(i, j, xx, color); // 落指定色子
				int check_result = check_Cell_1(i, j, xx);

				if (((check_result > temp && temp != 9) || temp == 9) // 取有利度最高的落子点或五连
					&& judgment_simplified(i, j, check_result) != 1) // 禁手无视
					temp = check_result;

				if (check_result == 3 && judgment_simplified(i, j, check_result) != 1) // 三连构造统计
					temp_3++;

				new_Cell(i, j, xx, -1); // 恢复
			}
		}

	return temp * 100 + temp_3;
}

// 指示递归层数，全局变量
int processes = 0;

// 对特定格（必须先落子！）的N层连子状况检查 // 指针传递N层预测的对方威胁度与己方威胁度
void check_Cell_N(int i_x, int j_x, int **xx, int step, int *danger_rt, int *profit_rt)
{
	int N = 4;

	int N_temp = (step - 3) / 2;
	if (N_temp < 0) N_temp = 0;
	else if (N_temp > N) N_temp = N;
	else
		;

	int AI_result = 0;
	int AI_i[8] = { 0,0,0,0,0,0,0,0 }, AI_j[8] = { 0,0,0,0,0,0,0,0 }; // N * 2
	int check_result = 0;

	int AI(int **xx, int step); // 函数声明

	for (int layer = 0; layer != N_temp; ++layer)
	{
		// 落对方色子
		AI_result = AI(xx, step + 1); // 执行计算机落子程序
		processes--; // 恢复上级递归层数

		AI_i[layer * 2] = AI_result % 100;
		AI_j[layer * 2] = AI_result / 100;

		new_Cell(AI_i[layer * 2], AI_j[layer * 2], xx, step % 2 + 1);

		// 对方色子检查
		check_result = check_Cell_1(AI_i[layer * 2], AI_j[layer * 2], xx);
		if (check_result > *danger_rt) *danger_rt = check_result;

		// 落己方色子
		AI_result = AI(xx, step); // 执行计算机落子程序
		processes--; // 恢复上级递归层数

		AI_i[layer * 2 + 1] = AI_result % 100;
		AI_j[layer * 2 + 1] = AI_result / 100;

		new_Cell(AI_i[layer * 2 + 1], AI_j[layer * 2 + 1], xx, (step + 1) % 2 + 1);

		// 己方色子检查
		check_result = check_Cell_1(AI_i[layer * 2 + 1], AI_j[layer * 2 + 1], xx);
		if (check_result > *profit_rt) *profit_rt = check_result;
	}

	// 恢复
	for (int t = 0; t != N_temp * 2; ++t) new_Cell(AI_i[t], AI_j[t], xx, -1);
}

// 胜手禁手判断
int judgment(int i, int j, int step)
{
	system("cls"); // 清空屏幕
	print_Chess(i, j, step); // 打印棋盘

	int count_3 = 0, count_4 = 0, count_5 = 0, count_6 = 0; // 对三子四子五子长连情况计数
	int check_result = check_Cell_1(i, j, aa); // 获取连子状况检查结果
	printf("%d\n", check_result); // 打印连子状况检查结果

	// printf("%d %d %d %d\n%d %d %d %d\n\n", tp, bm, lt, rt, tp_plus, bm_plus, lt_plus, rt_plus); // 打印棋子范围

	// 打印辅助矩阵
	/*
	for (int ir = 0; ir <= 2 * m - 10; ++ir)
	{
		for (int jr = 0; jr <= m + 1; ++jr) printf("%d ", ar[ir][jr]);
		printf("\t");
		for (int jr = 0; jr <= m + 1; ++jr) printf("%d ", al[ir][jr]);
		printf("\n");
	}
	// */

	// 打印历史记录
	// /*
	for (int t = 0; t != step; ++t) printf("%d %d | ", player_i[t], player_j[t]);
	printf("\n\n");
	// */

	// 分离连子状况检查结果 // **
	do
	{
		if (check_result % 10 == 3 || check_result % 10 == 2) count_3++;
		else if (check_result % 10 >= 4 && check_result % 10 <= 8) count_4++;
		else if (check_result % 10 == 9) count_5++;
		else if (check_result % 10 == 1) count_6++;
		else
			;
		check_result = (check_result - check_result % 10) / 10; // 去除个位数
	} while (check_result > 0);
	count_3 += result_3; // 合并额外统计部分

	if (a[i][j] == 2 && count_6 > 0 && count_5 == (count_6 * 2)) // 黑子长连禁手
	{
		printf("Black loses on (%d, %d). White wins!\n", i, j); // 黑子禁手白子胜
		return 1;
	}
	if (count_5 > 0) // 五连获胜
	{
		if (step % 2 == 1) printf("Black "); // 奇数步黑子胜
		else printf("White "); // 偶数步白子胜
		printf("wins!\n");
		return 2;
	}
	if (a[i][j] == 2 && (count_3 > 1 || count_4 > 1)) // 黑子双三双四禁手
	{
		printf("Black loses on (%d, %d). White wins!\n", i, j); // 黑子禁手白子胜
		return 1;
	}

	// 平局判断模块
	if (step == m * m)
	{
		printf("The game ends in draw.\n");
		return 3;
	}

	return 0;
}

// 禁手的简单判断
int judgment_simplified(int i, int j, int check_result)
{
	int count_3 = 0, count_4 = 0, count_5 = 0, count_6 = 0; // 对三子四子五子长连情况计数

	// 分离连子状况检查结果 // **
	do
	{
		if (check_result % 10 == 3 || check_result % 10 == 2) count_3++;
		else if (check_result % 10 >= 4 && check_result % 10 <= 8) count_4++;
		else if (check_result % 10 == 9) count_5++;
		else if (check_result % 10 == 1) count_6++;
		else
			;
		check_result = (check_result - check_result % 10) / 10; // 去除个位数
	} while (check_result > 0);
	count_3 += result_3; // 合并额外统计部分

	if (a[i][j] == 2 && count_6 > 0 && count_5 == (count_6 * 2)) return 1; // 黑子长连禁手
	if (a[i][j] == 2 && (count_3 > 1 || count_4 > 1)) return 1; // 黑子双三双四禁手
	return 0;
}

/*
* 原三个优先规则：
* 摒弃落子后对方可能成双成四成三侧，优先落子后己方能成四成三侧，优先落子后己方下一步可能成四成三侧。
*
* 禁手除外的优先级顺序表：
*
* 我方五连。
* 对方五连。
*
* 我方四连。
* 我方双四、四三。
* 我方以半四打头的必胜策略。
* 对方四连。（必胜策略与两步测试）
* 对方双四、四三。
* 对方以半四打头的必胜策略。
*
* 我方双三。
* 我方以三打头的必胜策略。
* 对方双三。
* 对方以三打头的必胜策略。
*
* 双方含值处。
* 我方两步成双。
*
* 我方半四、三，预测威胁度最高的。
* 对方半四、三，预测威胁度最高的。
*
* 我方两步最大值。
*
* 取有利格。
* 取不利格。
* 随机落子。
*/

// 落子较佳位置判断程序模块
int good(int *position, int size, int **xx, int step, int *max_rt, int *min_rt, int stage)
{
	int i[32], j[32], check_result[32];
	int max = 0, min = 0, max_p = 0, min_p = 0;

	for (int t = 0; t != size; ++t)
	{
		i[t] = (*(position + t)) % 100;
		j[t] = (*(position + t)) / 100;

		// 状况检查并恢复
		new_Cell(i[t], j[t], xx, (step + 1) % 2 + 1);

		// 优先落子位对方可以成四成三侧
		if (stage == 0) check_result[t] = check_Cell_2(i[t], j[t], xx, step % 2 + 1);
		// 优先落子位己方可以成四成三侧
		else if (stage == 1) check_result[t] = check_Cell_1(i[t], j[t], xx);
		// 优先落子后己方下一步可能成四成三侧
		else if (stage == 2) check_result[t] = check_Cell_2(i[t], j[t], xx, (step + 1) % 2 + 1);
		/*
		else if (stage == 3 || stage == 5)
		{
			// 优先落子位对方可以成四成三侧，统一单位
			int temp_danger_rt = check_Cell_2(i[t], j[t], xx, step % 2 + 1) / 100;
			// 优先落子后己方下一步可以成五侧
			int temp_profit_rt = check_Cell_2(i[t], j[t], xx, (step + 1) % 2 + 1) / 100;
			// 如果不是成五，检查结果无效化
			if (step > 5 && temp_profit_rt % 10 != 9) temp_profit_rt = 0;

			if (stage == 3)
				// 注意danger的值需要反向
				check_result[t] = temp_profit_rt * 100 + 100 - temp_danger_rt;
			else
				// 注意profit的值需要反向
				check_result[t] = temp_danger_rt * 100 + 100 - temp_profit_rt;
		}
		*/
		// 以上部分删除，stage代号随之调整
		else if (stage == 3 || stage == 4)
		{
			int temp_danger_rt = 0, temp_profit_rt = 0;
			check_Cell_N(i[t], j[t], xx, step, &temp_danger_rt, &temp_profit_rt);

			if (stage == 3)	check_result[t] = temp_profit_rt * 100 + 100 - temp_danger_rt;
			else check_result[t] = temp_danger_rt * 100 + 100 - temp_profit_rt;
		}
		else
			;

		new_Cell(i[t], j[t], xx, -1);

		// 取最大值与最小值
		if (t == 0)
		{
			max = min = check_result[t];
			max_p = min_p = *(position + t);
		}
		else
		{
			if (check_result[t] > max)
			{
				max = check_result[t];
				max_p = *(position + t);
			}
			if (check_result[t] < min)
			{
				min = check_result[t];
				min_p = *(position + t);
			}
		}
	}

	// 指针..._rt传递N层检查结果
	if (stage == 3 || stage == 4) *max_rt = max;
	if (stage == 4) *min_rt = min;

	if (max != min)
	{
		if (stage >= 1 && stage <= 3) return max_p;
		else return min_p;
	}
	else return 0;
}

// 落子较佳位置判断程序传统模式
int good_ex(int *position, int size, int **xx, int step)
{
	int pst = good(position, size, xx, step, NULL, NULL, 0);
	if (pst != 0) return pst;
	else
	{
		pst = good(position, size, xx, step, NULL, NULL, 1);
		if (pst != 0) return pst;
		else
		{
			pst = good(position, size, xx, step, NULL, NULL, 2);
			if (pst != 0) return pst;
			else return *position;
		}
	}
}

// 落子较佳位置判断程序预测模式
int good_bns(int *position, int size, int **xx, int step, int *max_rt, int *min_rt, bool amI)
{
	if (amI == true)
	{
		int pst = good(position, size, xx, step, max_rt, NULL, 3);
		if (pst != 0) return pst;
		else
		{
			pst = good(position, size, xx, step, NULL, NULL, 1);
			if (pst != 0) return pst;
			else return *position;
		}
	}
	else
	{
		int pst = good(position, size, xx, step, max_rt, min_rt, 4);
		if (pst != 0) return pst;
		else
		{
			pst = good(position, size, xx, step, NULL, NULL, 1);
			if (pst != 0) return pst;
			else return *position;
		}
	}
}

// 计算机落子程序
int AI(int **xx, int step)
{
	processes++; // 进入函数

	// 与processes相关的空间复杂度（最高调用次数）
	const int complex = 1;

	// 前三步随机
	int rand_i = 0, rand_j = 0;

	if (step == 0) return center * 100 + center;
	if (step == 1 || step == 2)
	{
		do
		{
			srand((unsigned)time(NULL));
			int rand_ij = rand() % 9;
			rand_i = rand_ij % 3 - 1;
			rand_j = rand_ij / 3 - 1;
		} while (a[center + rand_i][center + rand_j] >= 0 || a[center - rand_i][center - rand_j] >= 0);
		return (center + rand_j) * 100 + (center + rand_i);
	}

	// 四五步布局
	if (step == 3 || step == 4)
	{
		int best_rt = 0, best_position = 0;
		for (int i = 0; i <= m; ++i)
			for (int j = 0; j <= m; ++j)
			{
				if (*(*xx + i * mm + j) < 0) // 遍历必须保证测试格为空
				{
					// 落己方色子
					new_Cell(i, j, xx, (step + 1) % 2 + 1);

					int temp_danger_rt = check_Cell_2(i, j, xx, step % 2 + 1);
					int temp_profit_rt = check_Cell_2(i, j, xx, (step + 1) % 2 + 1);

					// 不许连着出四
					if (temp_profit_rt < 400)
					{
						// 提高danger比重且保证值为正
						int temp_rt = temp_profit_rt + 400 - temp_danger_rt * 2;
						if (temp_rt > best_rt)
						{
							best_rt = temp_rt;
							best_position = j * 100 + i;
						}
					}

					// 恢复
					new_Cell(i, j, xx, -1);
				}
			}
		return best_position;
	}

	// 主程序模块

	// 双方威胁度最高记录
	int profit = 0, profitP = 0;
	int danger = 0, dangerP = 0;

	// 初始化数组与对应的指针 // 注意与good函数处的对应
	const int size = 16;
	int this_4P[16], that_4P[16], this_3P[32], that_3P[32];
	for (int t = 0; t != size; ++t)
		this_4P[t] = that_4P[t] = this_3P[2 * t] = that_3P[2 * t] = this_3P[2 * t + 1] = that_3P[2 * t + 1] = 0;

	int *this_4_first = &this_4P[0], *that_4_first = &that_4P[0], *this_3_first = &this_3P[0], *that_3_first = &that_3P[0];

	// 有效个数的统计
	int this_4_size = 0, that_4_size = 0, this_3_size = 0, that_3_size = 0;

	// 特别地，需要统计对方四连
	int that_8P[8] = { 0,0,0,0,0,0,0,0 };
	int *that_8_first = &that_8P[0];
	int that_8_size = 0;

	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= m; ++j)
		{
			if (*(*xx + i * mm + j) < 0) // 如果测试格为空
			{
				// 禁手判断标识
				bool is_this_illegal = false, is_that_illegal = false;

				// 落己方色子
				new_Cell(i, j, xx, (step + 1) % 2 + 1);
				int check_this = check_Cell_1(i, j, xx);
				is_this_illegal = judgment_simplified(i, j, check_this);

				if (is_this_illegal == false) // 我方禁手跳过
				{
					// 取己方制胜格
					if (check_this % 10 == 9) return j * 100 + i; // 若己方有制胜格则落子
					// 取有利度最高的落子点或四连
					if ((check_this > profit && profit != 8) || check_this == 8)
					{
						profit = check_this;
						profitP = j * 100 + i; // 对有利格记录
					}
					// 取与四相关的所有落子点
					if (check_this == 4 || check_this == 5)
					{
						for (int t = 0; t != size; ++t)
							if (this_4P[t] == 0)
							{
								this_4P[t] = j * 100 + i; // 挑空位坐
								this_4_size++;
								break;
							}
					}
					// 取与三相关的所有落子点 // 注意：size * 2！
					if (check_this == 2 || check_this == 3)
					{
						for (int t = 0; t != size * 2; ++t)
							if (this_3P[t] == 0)
							{
								this_3P[t] = j * 100 + i; // 挑空位坐
								this_3_size++;
								break;
							}
					}
				}

				// 恢复
				new_Cell(i, j, xx, -1);

				// 落对方色子
				new_Cell(i, j, xx, step % 2 + 1);
				int check_that = check_Cell_1(i, j, xx);
				is_that_illegal = judgment_simplified(i, j, check_that);

				if (is_this_illegal == false && is_that_illegal == false) // 我方禁手与对方禁手均跳过
				{
					// 取对方制胜格
					if (check_that % 10 == 9) return j * 100 + i; // 若己方有制胜格则落子
					// 取不利度最高的落子点或四连
					if ((check_that > danger && danger != 8) || check_that == 8)
					{
						danger = check_that;
						dangerP = j * 100 + i; // 对不利格记录
					}
					// 取与四连相关的所有落子点
					if (check_that == 8 || check_that == 7)
					{
						for (int t = 0; t != size; ++t)
							if (that_8P[t] == 0)
							{
								that_8P[t] = j * 100 + i; // 挑空位坐
								that_8_size++;
								break;
							}
					}
					// 取与四相关的所有落子点
					if (check_that == 4 || check_that == 5)
					{
						for (int t = 0; t != size; ++t)
							if (that_4P[t] == 0)
							{
								that_4P[t] = j * 100 + i; // 挑空位坐
								that_4_size++;
								break;
							}
					}
					// 取与三相关的所有落子点 // 注意：size * 2！
					if (check_that == 2 || check_that == 3)
					{
						for (int t = 0; t != size * 2; ++t)
							if (that_3P[t] == 0)
							{
								that_3P[t] = j * 100 + i; // 挑空位坐
								that_3_size++;
								break;
							}
					}
				}

				// 恢复
				new_Cell(i, j, xx, -1);
			}
		}

	// 若己方有双四、四三、四连 // 落子有利格
	if (profit > 40 || profit == 8) return profitP;
	// 己方半四有利预测 // 注意：rt对应最佳参考值，ad对应最佳地址
	int this_4_max_rt = 0, this_4_ad = 0;
	if (processes <= complex && this_4_size > 0)
		this_4_ad = good_bns(this_4_first, this_4_size, xx, step, &this_4_max_rt, NULL, true);
	if (this_4_max_rt >= 800) return this_4_ad;

	// 若对方有四连
	if (that_8_size > 1)
	{
		if (processes <= complex) return good_bns(that_8_first, that_8_size, xx, step, &danger, &danger, false);
		else return good_ex(that_8_first, that_8_size, xx, step);
	}
	// 若对方有双四、四三、四连 // 围堵不利格
	if (danger > 40 || danger == 8) return dangerP;
	// 对方半四不利预测 // 注意：rt对应最佳参考值，ad对应最佳地址
	int that_4_max_rt = 0, that_4_min_rt = 0, that_4_ad = 0;
	if (processes <= complex && that_4_size > 0)
		that_4_ad = good_bns(that_4_first, that_4_size, xx, step, &that_4_max_rt, &that_4_min_rt, false);
	if (that_4_max_rt >= 800 && that_4_min_rt < 800) return that_4_ad;

	// 若己方有双三 // 落子有利格
	if (profit > 20) return profitP;
	// 己方三有利预测 // 注意：rt对应最佳参考值，ad对应最佳地址
	int this_3_max_rt = 0, this_3_ad = 0;
	if (processes <= complex && this_3_size > 0)
		this_3_ad = good_bns(this_3_first, this_3_size, xx, step, &this_3_max_rt, NULL, true);
	if (this_3_max_rt >= 800) return this_3_ad;

	// 若对方有双三 // 围堵不利格
	if (danger > 20) return dangerP;
	// 对方三不利预测 // 注意：rt对应最佳参考值，ad对应最佳地址
	int that_3_max_rt = 0, that_3_min_rt = 0, that_3_ad = 0;
	if (processes <= complex && that_3_size > 0)
		that_3_ad = good_bns(that_3_first, that_3_size, xx, step, &that_3_max_rt, &that_3_min_rt, false);
	if (that_3_max_rt >= 800 && that_3_min_rt < 800) return that_3_ad;

	/*
	// 双方含值处
	for (int t = 0; t != this_4_size; ++t)
	{
		for (int s = 0; s != that_4_size; ++s)
			if (this_4P[t] == that_4P[s]) return this_4P[t];
		for (int s = 0; s != that_3_size; ++s)
			if (this_4P[t] == that_3P[s]) return this_4P[t];
	}
	for (int t = 0; t != this_3_size; ++t)
	{
		for (int s = 0; s != that_4_size; ++s)
			if (this_3P[t] == that_4P[s]) return this_3P[t];
		for (int s = 0; s != that_3_size; ++s)
			if (this_3P[t] == that_3P[s]) return this_3P[t];
	}
	*/

	// 己方落子后的检验
	int profit_twice = 0, profit_ji = 0;
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= m; ++j)
		{
			if (*(*xx + i * mm + j) < 0) // 遍历必须保证测试格为空
			{
				// 落己方色子
				new_Cell(i, j, xx, (step + 1) % 2 + 1);

				int result_once = check_Cell_1(i, j, xx);
				int result_twice = check_Cell_2(i, j, xx, (step + 1) % 2 + 1);

				// 取二层检验有利度最高的落子点 // 对自带Buff的进行Buff加成
				if ((result_twice > 2000 || result_twice < 400)
					&& judgment_simplified(i, j, result_once) != 1) // 禁手无视
				{
					// 如果是两步成双，获得一次Buff加成机会
					if (result_twice > 2000) result_twice += result_once * 10000;
					if (result_twice > profit_twice)
					{
						profit_twice = result_twice;
						profit_ji = j * 100 + i;
					}
				}

				// 恢复
				new_Cell(i, j, xx, -1);
			}
		}

	// 我方两步成双
	if (profit_twice > 2000) return profit_ji;

	if (processes <= complex)
	{
		// 落子落子后己方威胁度最高之格
		if (this_4_size > 0 || this_3_size > 0)
		{
			if (this_4_max_rt > this_3_max_rt) return this_4_ad;
			else return this_3_ad;
		}

		// 落子落子后对方威胁度最低之格
		if (that_4_size > 0 && that_3_size > 0)
		{
			if (that_4_min_rt < that_3_min_rt) return that_4_ad;
			else return that_3_ad;
		}
		else if (that_4_size > 0) return that_4_ad;
		else if (that_3_size > 0) return that_3_ad;
		else
			;
	}
	else
	{
		if (this_4_size > 0) return good_ex(this_4_first, this_4_size, xx, step);
		if (this_3_size > 0) return good_ex(this_3_first, this_3_size, xx, step);

		if (profit_twice > 303) return profit_ji;

		if (that_4_size > 0) return good_ex(that_4_first, that_4_size, xx, step);
		if (that_3_size > 0) return good_ex(that_3_first, that_3_size, xx, step);
	}

	// 我方两步最大值
	if (profit_twice > 0) return profit_ji;

	if (profit > 0) return profitP; // 落子有利格
	if (danger > 0) return dangerP; // 围堵不利格

	// 主程序模块结束

	// 若上述均不合则随机落子
	do
	{
		// srand((unsigned)time(NULL));
		rand_i = rand() % m + 1;
		rand_j = rand() % m + 1;
	} while (a[rand_i][rand_j] >= 0);
	return rand_j * 100 + rand_i;
}

int main()
{
	// 初始化斜向矩阵
	for (int ir = 0; ir <= 2 * m - 10; ++ir)
		for (int jr = 0; jr <= m + 1; ++jr)
		{
			ar[ir][jr] = al[ir][jr] = 3; // 默认均为阻拦
		}
	
	// 初始化矩阵
	for (int i = 0; i <= m + 1; ++i)
		for (int j = 0; j <= m + 1; ++j)
		{
			// 外圈为3表示阻拦。其余为负表示为空
			if (i == 0 || i == m + 1 || j == 0 || j == m + 1) a[i][j] = 3;
			else
			{
				a[i][j] = -1;
				renew_Cell(i, j, aa); // 第一次更新辅助矩阵
			}
		}

	// 初始化历史记录
	for (int t = 0; t != m * m; ++t) player_i[t] = player_j[t] = 0;

	// 玩家选择白子或黑子
	int choice = 0;
	do 
	{
		system("cls");
		printf("Do you want to be white(1) or black(2) ? Enter your choice: ");
		scanf("%d", &choice);
	}
	while (choice != 1 && choice != 2);

	int AI_result = 0;
	int step = 0; // 统计已下的步数

	// 刷新屏幕
	system("color fc");
	system("cls");
	print_Chess(player_i[step], player_j[step], step);

	// /* 试验区

	while (1)
	{
		// 计算机落子
		// 若上一步落子是玩家选择色子，则这一步是计算机落子。
		if (step % 2 + 1 == choice)
		{
			AI_result = AI(aa, step); // 执行计算机落子程序
			processes--; // 恢复上级递归层数

			player_i[step] = AI_result % 100;
			player_j[step] = AI_result / 100;

			// 步数为奇落黑子，步数为偶落白子。 // 安全起见分开写
			new_Cell(player_i[step], player_j[step], aa, (step + 1) % 2 + 1);
			step++;

			// Previous Version:
			// ++step! 先加后调用哦
			// new_Cell(player_i, player_j, aa, ++step % 2 + 1);

			if (judgment(player_i[step - 1], player_j[step - 1], step) > 0) break;
		}
		// 玩家落子
		else
		{
		input:scanf("%d%d", &player_i[step], &player_j[step]); // 落子
			if (player_i[step] == 0 && player_j[step] == 0) break; // (0,0)表示结束
			else if (player_i[step] >= 1 && player_i[step] <= m && player_j[step] >= 1 && player_j[step] <= m) // 判定是否落在棋盘内
			{
				if (a[player_i[step]][player_j[step]] < 0) // 如果落子点为空
				{
					// 步数为奇落黑子，步数为偶落白子。 // 安全起见分开写
					new_Cell(player_i[step], player_j[step], aa, (step + 1) % 2 + 1);
					step++;

					if (judgment(player_i[step - 1], player_j[step - 1], step) > 0) break;

					// 调试模块
					/*
					int debug = 0; scanf("%d", &debug);
					if (debug == 0) break;
					else if (debug == 1 || debug == 2)
					{
						step += debug % 2;
						goto input;
					}
					else
						;
					// */
				}
				else goto input; // 否则落子点不为空并请求重新落子
			}
			else goto input; // 否则落子点越界并请求重新落子
		}
	}

	/*
	// AI to AI!
	int judge = 0;

	while (time_total < 100)
	{
		AI_result = AI(aa, step); // 执行计算机落子程序
		processes--; // 恢复上级递归层数

		player_i[step] = AI_result % 100;
		player_j[step] = AI_result / 100;

		// 步数为奇落黑子，步数为偶落白子。 // 安全起见分开写
		new_Cell(player_i[step], player_j[step], aa, (step + 1) % 2 + 1);
		step++;

		judge = judgment(player_i[step - 1], player_j[step - 1], step);
		if (judge > 0)
		{
			time_total++;
			if (judge == 3)
			{
				time_black += 0.5;
				time_white += 0.5;
			}
			else time_black++;
			goto start;
		}
		system("pause");

		AI_result = AI(aa, step); // 执行计算机落子程序
		processes--; // 恢复上级递归层数

		player_i[step] = AI_result % 100;
		player_j[step] = AI_result / 100;

		// 步数为奇落黑子，步数为偶落白子。 // 安全起见分开写
		new_Cell(player_i[step], player_j[step], aa, (step + 1) % 2 + 1);
		step++;

		judge = judgment(player_i[step - 1], player_j[step - 1], step);
		if (judge > 0)
		{
			time_total++;
			if (judge == 3)
			{
				time_black += 0.5;
				time_white += 0.5;
			}
			else time_white++;
			goto start;
		}
		system("pause");
	}
	// */

	system("pause");
	return 0;
}
