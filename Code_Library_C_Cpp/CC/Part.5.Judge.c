#include "Header.h"

/* Part.5 禁手胜手平手判断模块 ************************************************** */

// 此处声明使用三一顶格落子计数
extern int impossible_ooo_O;

// 禁手胜手平手判断（兼打印棋盘）
int judgment(int i, int j, int step)
{
	CLEARSCREEN; // 清空屏幕
	printChessboard(i, j); // 打印棋盘

	int count_3 = 0, count_4 = 0, count_5 = 0, count_6 = 0; // 对三子四子五子长连情况计数
	int check_result = check_Cell_1(i, j); // 获取连子状况检查结果
	printf("%d\n", check_result); // 打印连子状况检查结果

	// 打印辅助矩阵
	/*
	for (int u = 0; u <= SIDELENGTHXXXX - 1; ++u)
	{
		for (int v = 0; v <= SIDELENGTHEX - 1; ++v) printf("%d ", ar[u][v]);
		printf("\t");
		for (int v = 0; v <= SIDELENGTHEX - 1; ++v) printf("%d ", al[u][v]);
		printf("\n");
	}
	// */

	// 打印历史记录
	for (int t = 1; t <= step; ++t) printf("%d %c | ",
		(playeri[t] == 0) ? 0 : SIDELENGTH + 1 - playeri[t], (playerj[t] == 0) ? '0' : 'A' + playerj[t] - 1);
	printf("\n\n");

	// 分离连子状况检查结果
	do
	{
		if (check_result % 10 >= IIIINF && check_result % 10 <= IIISUP) count_3++;
		else if (check_result % 10 >= IVINF && check_result % 10 <= IVSUP) count_4++;
		else if (check_result % 10 == QQQQQ) count_5++;
		else if (check_result % 10 == QQQQQQ) count_6++;
		else
			;
		check_result = check_result / 10; // 去除个位数
	} while (check_result > 0);

	// 合并三一顶格落子计数
	count_4 += impossible_ooo_O;

	if (a[i][j] == 2 && count_5 == 0 && (count_3 > 1 || count_4 > 1 || count_6 > 0))
	{
		printf("Black loses on (%d, %d). White wins!\n", i, j); // 黑子禁手白子胜
		return 1;
	}
	else if (count_5 > 0 || count_6 > 0) // 五连或长连获胜
	{
		if (a[i][j] == 2) printf("Black "); // 最近一步为黑子则黑子胜
		else printf("White "); // 最近一步为白子则白子胜
		printf("wins!\n");
		return 2;
	}
	else if (step == CELLTOTAL) // 平局判断
	{
		printf("The game ends in draw.\n");
		return 3;
	}
	else
		return 0;
}

// 禁手的简单判断. 禁手则返回0. 合法则返回1.
int judgmentSimplified(int i, int j, int check_result)
{
	int count_3 = 0, count_4 = 0, count_5 = 0, count_6 = 0; // 对三子四子五子长连情况计数

	// 分离连子状况检查结果
	do
	{
		if (check_result % 10 >= IIIINF && check_result % 10 <= IIISUP) count_3++;
		else if (check_result % 10 >= IVINF && check_result % 10 <= IVSUP) count_4++;
		else if (check_result % 10 == QQQQQ) count_5++;
		else if (check_result % 10 == QQQQQQ) count_6++;
		else
			;
		check_result = check_result / 10; // 去除个位数
	} while (check_result > 0);

	// 合并三一顶格落子计数
	count_4 += impossible_ooo_O;

	// 黑子无五连时的双三双四长连禁手
	if (a[i][j] == 2 && count_5 == 0 && (count_3 > 1 || count_4 > 1 || count_6 > 0)) return 0;
	return 1;
}
