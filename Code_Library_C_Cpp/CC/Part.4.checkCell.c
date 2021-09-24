#include "Header.h"

/* Part.4 连子状况检查模块 ************************************************** */

// 为避免报错设置矩阵首指针
int *pointera = &a[0][0], *pointerat = &at[0][0], *pointerar = &ar[0][0], *pointeral = &al[0][0];

// 数字重排程序：从大到小排列
int trick(unsigned int num)
{
	int x[10] = { 0,0,0,0,0,0,0,0,0,0 };
	int temp = 0;

	// 分离数字
	while (num > 0)
	{
		x[num % 10]++;
		num = num / 10;
	}

	// 重排模块
	for (int i = 9; i >= 0; --i)
		for (int j = 0; j != x[i]; ++j)
			temp = temp * 10 + i;
	return temp;
}

// 三一顶格落子计数不计分
int impossible_ooo_O = 0;

// 连子状况检查单元
int check_C(int i, int j, int *x, int result)
{
	// 避免溢出的漏洞补救
	if (x == pointera || x == pointerat)
	{
		if (i < 1 || i > SIDELENGTH || j < 1 || j > SIDELENGTH) return result;
	}
	else
	{
		if (i < 0 || i > SIDELENGTHXXXX - 1 || j < 1 || j > SIDELENGTH) return result;
	}

	int color = *(x + i * SIDELENGTHEX + j);

	for (int q = j - 4; q <= j; ++q)
	{
		if (*(x + i * SIDELENGTHEX + q) == color
			&& *(x + i * SIDELENGTHEX + q + 1) == color
			&& *(x + i * SIDELENGTHEX + q + 2) == color
			&& *(x + i * SIDELENGTHEX + q + 3) == color
			&& *(x + i * SIDELENGTHEX + q + 4) == color)
		{
			if (*(x + i * SIDELENGTHEX + q + 5) == color || *(x + i * SIDELENGTHEX + q - 1) == color)
				return result * 10 + QQQQQQ; // 长连 // 同行不会再有其他棋形故直接返回
			else
				return result * 10 + QQQQQ; // 五连 // 同行不会再有其他棋形故直接返回
		}

		else if (*(x + i * SIDELENGTHEX + q + 1) == color
			&& *(x + i * SIDELENGTHEX + q + 2) == color
			&& *(x + i * SIDELENGTHEX + q + 3) == color
			&& *(x + i * SIDELENGTHEX + q + 4) == color)
		{
			if (*(x + i * SIDELENGTHEX + q) == 0 && *(x + i * SIDELENGTHEX + q + 5) == 0)
				result = result * 10 + IVTOKENI; // 四连
			else if ((*(x + i * SIDELENGTHEX + q) == 0 && *(x + i * SIDELENGTHEX + q + 5) != color)
				|| (*(x + i * SIDELENGTHEX + q) != color && *(x + i * SIDELENGTHEX + q + 5) == 0))
				result = result * 10 + IVTOKENII; // 半四连
			else
				;
		}
		else if (*(x + i * SIDELENGTHEX + q - 1) != color
			&& *(x + i * SIDELENGTHEX + q) == color
			&& *(x + i * SIDELENGTHEX + q + 1) == color
			&& *(x + i * SIDELENGTHEX + q + 2) == color
			&& *(x + i * SIDELENGTHEX + q + 3) == 0
			&& *(x + i * SIDELENGTHEX + q + 4) == color) // 为避免与四连重复计数附加的条件
		{
			// 顺三一式四
			if (*(x + i * SIDELENGTHEX + q - 1) == 0 && q + 4 == j) impossible_ooo_O++; // 计数不计分
			else if (*(x + i * SIDELENGTHEX + q + 5) == 0 && q == j) result = result * 10 + IVTOKENIII; // Ooo_o_三一式四
			else result = result * 10 + IVQQQAQ; // 剩余所有三一式四
		}
		else if (*(x + i * SIDELENGTHEX + q) == color
			&& *(x + i * SIDELENGTHEX + q + 1) == 0
			&& *(x + i * SIDELENGTHEX + q + 2) == color
			&& *(x + i * SIDELENGTHEX + q + 3) == color
			&& *(x + i * SIDELENGTHEX + q + 4) == color
			&& *(x + i * SIDELENGTHEX + q + 5) != color) // 为避免与四连重复计数附加的条件
		{
			// 逆三一式四
			if (*(x + i * SIDELENGTHEX + q + 5) == 0 && q == j) impossible_ooo_O++; // 计数不计分
			else if (*(x + i * SIDELENGTHEX + q - 1) == 0 && q + 4 == j) result = result * 10 + IVTOKENIII; // _o_ooO三一式四
			else result = result * 10 + IVQQQAQ; // 剩余所有三一式四
		}
		else if (*(x + i * SIDELENGTHEX + q - 1) != color
			&& *(x + i * SIDELENGTHEX + q) == color
			&& *(x + i * SIDELENGTHEX + q + 1) == color
			&& *(x + i * SIDELENGTHEX + q + 2) == 0
			&& *(x + i * SIDELENGTHEX + q + 3) == color
			&& *(x + i * SIDELENGTHEX + q + 4) == color
			&& *(x + i * SIDELENGTHEX + q + 5) != color) // 为避免与三一重复计数附加的条件
		{
			if (*(x + i * SIDELENGTHEX + q + 5) == 0 && q == j) result = result * 10 + IVTOKENIII; // Oo_oo_二二式四
			else if (*(x + i * SIDELENGTHEX + q - 1) == 0 && q + 4 == j) result = result * 10 + IVTOKENIII; // _oo_oO二二式四
			else result = result * 10 + IVQQAQQ; // 二二式四
		}

		else if (
			*(x + i * SIDELENGTHEX + q) != color
			&& *(x + i * SIDELENGTHEX + q + 1) == 0
			&& *(x + i * SIDELENGTHEX + q + 2) == color
			&& *(x + i * SIDELENGTHEX + q + 3) == color
			&& *(x + i * SIDELENGTHEX + q + 4) == color
			&& *(x + i * SIDELENGTHEX + q + 5) == 0
			&& *(x + i * SIDELENGTHEX + q + 6) != color) // 为避免与三一重复计数附加的条件
		{
			if (color == 2) // 如果是黑子
			{
				if ((*(x + i * SIDELENGTHEX + q) == 0 && *(x + i * SIDELENGTHEX + q - 1) != color)
					|| (*(x + i * SIDELENGTHEX + q + 6) == 0 && *(x + i * SIDELENGTHEX + q + 7) != color))
					return result * 10 + IIIQQQ; // 活连三 // 同行不会再有其他棋形故直接返回
			}
			else // 如果是白子
			{
				if (*(x + i * SIDELENGTHEX + q) == 0 || *(x + i * SIDELENGTHEX + q + 6) == 0) // 不能两端都拦子
					result = result * 10 + IIIQQQ; // 连三
			}
		}
		else if (*(x + i * SIDELENGTHEX + q) == 0
			&& *(x + i * SIDELENGTHEX + q + 1) == color
			&& *(x + i * SIDELENGTHEX + q + 2) == color
			&& *(x + i * SIDELENGTHEX + q + 3) == 0
			&& *(x + i * SIDELENGTHEX + q + 4) == color
			&& *(x + i * SIDELENGTHEX + q + 5) == 0)
		{
			if (color == 2) // 如果是黑子
			{
				if (*(x + i * SIDELENGTHEX + q - 1) != color && *(x + i * SIDELENGTHEX + q + 6) != color)
					return result * 10 + IIIQQAQ; // 活跳三 // 同行不会再有其他棋形故直接返回
			}
			else // 如果是白子
				result = result * 10 + IIIQQAQ; // 跳三
		}
		else if (*(x + i * SIDELENGTHEX + q) == 0
			&& *(x + i * SIDELENGTHEX + q + 1) == color
			&& *(x + i * SIDELENGTHEX + q + 2) == 0
			&& *(x + i * SIDELENGTHEX + q + 3) == color
			&& *(x + i * SIDELENGTHEX + q + 4) == color
			&& *(x + i * SIDELENGTHEX + q + 5) == 0)
		{
			if (color == 2) // 如果是黑子
			{
				if (*(x + i * SIDELENGTHEX + q - 1) != color && *(x + i * SIDELENGTHEX + q + 6) != color)
					return result * 10 + IIIQQAQ; // 活跳三 // 同行不会再有其他棋形故直接返回
			}
			else // 如果是白子
				result = result * 10 + IIIQQAQ; // 跳三
		}
		else
			;
	}

	return result;
}

// 对特定格（进入函数前已落子）的一层连子状况检查
int check_Cell_1(int i, int j)
{
	int result = 0; // 检查结果计为result
	impossible_ooo_O = 0; // 初始化

	result = check_C(i, j, pointera, result); // 横向检查
	result = check_C(j, i, pointerat, result); // 纵向检查

	int u, v; // u、v的转换原理同上

	u = i - j + SIDELENGTH - 5;
	if (i <= j) v = i;
	else v = j;
	if (u >= 0 && u <= SIDELENGTHXXXX - 1 && v >= 1 && v <= SIDELENGTH) // 避免溢出
		result = check_C(u, v, pointerar, result); // 右斜向检查

	u = i + j - 6;
	if (i + j <= SIDELENGTH + 1) v = i;
	else v = SIDELENGTH + 1 - j;
	if (u >= 0 && u <= SIDELENGTHXXXX - 1 && v >= 1 && v <= SIDELENGTH) // 避免溢出
		result = check_C(u, v, pointeral, result); // 左斜向检查

	result = trick(result);
	return result;
}
