#include "Header.h"

/* Part.6 Person vs A.I. 子模块（检查与高级检查） ************************************************** */

double DefvsAtk = 8.0;

// 对特定格（进入函数前已落子）的二层连子状况检查
// 检查结果由三部分构成：此处己方落子后形成的局势·此处己方落子后己方再落一子形成的局势·此处己方落子后对方再落一子形成的局势
double check_Cell_2(int i, int j, int color, int check_it)
{
	int check_these = 0, check_those = 0, check_three = 0, check_four = 0;

	for (int p = 1; p <= SIDELENGTH; ++p)
		for (int q = 1; q <= SIDELENGTH; ++q)
		{
			if (a[p][q] == 0) // 遍历必须保证测试格为空
			{
				putColoredPiece(p, q, color); // 落己方色子
				int check_this = check_Cell_1(p, q);

				if (judgmentSimplified(p, q, check_this)) // 禁手无视
				{
					// 巨大化！五连或长连
					if (check_this % 10 == QQQQQ || check_this % 10 == QQQQQQ) check_this += 10;
					if (check_this >= IIIINF && check_this <= IIISUP) check_three += check_this;
					if (check_this >= IVINF && check_this <= IVSUP) check_four += check_this;
					if (check_this > check_these) check_these = check_this;
				}

				// putColoredPiece(p, q, 0); // 恢复

				putColoredPiece(p, q, (color == 2) ? 1 : 2); // 落对方色子
				int check_that = check_Cell_1(p, q);

				if (judgmentSimplified(p, q, check_that)) // 禁手无视
				{
					// 巨大化！五连或长连
					if (check_that % 10 == QQQQQ || check_that % 10 == QQQQQQ) check_that += 10;
					if (check_that > check_those) check_those = check_that;
				}

				putColoredPiece(p, q, 0); // 恢复
			}
		}

	return check_it + check_these + check_four + check_three - check_those * DefvsAtk;
}

// 判断棋盘在函数check_Cell_2意义下的最优解
int check_Cells_2(int color)
{
	int bestposition = 0; // 记录位置
	double bestresult = (double)MINUSINFINITY; // 记录结果

	for (int p = 1; p <= SIDELENGTH; ++p)
		for (int q = 1; q <= SIDELENGTH; ++q)
		{
			if (a[p][q] == 0) // 遍历必须保证测试格为空
			{
				putColoredPiece(p, q, color); // 落己方色子
				int check_it = check_Cell_1(p, q);

				if (judgmentSimplified(p, q, check_it)) // 禁手无视
				{
					double tempscore = check_Cell_2(p, q, color, check_it);
					if (tempscore > bestresult) // 超量替换
					{
						bestresult = tempscore;
						bestposition = p * 100 + q;
					}
				}

				putColoredPiece(p, q, 0); // 恢复
			}
		}

	return bestposition; // 返回最佳位置
}
