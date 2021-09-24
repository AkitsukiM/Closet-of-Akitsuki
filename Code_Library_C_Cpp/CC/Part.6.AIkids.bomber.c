#include "Header.h"

// 落子机器. 输入的是被拦截的颜色. 返回落子列表与落子列表有效长度.
int stupidMachine(int *positions, int color)
{
	int positionsnum = 0;
	for (int i = 1; i <= SIDELENGTH; ++i)
		for (int j = 1; j <= SIDELENGTH; ++j)
		{
			if (a[i][j] == 0)
			{
				putColoredPiece(i, j, color); // 被拦截的颜色
				int check_that = check_Cell_1(i, j);

				if (judgmentSimplified(i, j, check_that)) // 禁手无视
				{
					if (check_that % 10 == QQQQQ || check_that % 10 == QQQQQQ) // 五连或长连时有且仅有的拦截方式
					{
						putColoredPiece(i, j, 0); // 中断前先恢复
						*positions = i * 100 + j;
						return 1;
					}
					else if (check_that == IVTOKENI || check_that == IVTOKENIII) // 四连及以上或四连衍生物
					{
						*(positions + positionsnum) = i * 100 + j; // 写入落子列表
						positionsnum++; // 落子列表有效长度增加
					}
					else
						;
				}

				putColoredPiece(i, j, 0); // 恢复
			}
		}
	return positionsnum;
}

// 威胁点查找. 输入颜色与级别. 回传威胁点列表与威胁点有效长度. 返回威胁棋形总数.
int bombSearch(int *bombc, int *bombv, int color, int level)
{
	int levelc = 0;
	for (int p = 1; p <= SIDELENGTH; ++p)
		for (int q = 1; q <= SIDELENGTH; ++q)
		{
			if (a[p][q] == 0)
			{
				putColoredPiece(p, q, color);
				int check_this = check_Cell_1(p, q);

				if (judgmentSimplified(p, q, check_this)) // 禁手无视
				{
					if (check_this >= IVINF && check_this <= IVSUP)	// 写入四的记录
					{
						*(bombv + (*bombc)++) = p * 100 + q;
						levelc++;
					}
					else if (check_this >= IIIINF && check_this <= IIISUP) // 写入三的记录
					{
						if (level == 3) *(bombv + (*bombc)++) = p * 100 + q;
						levelc++;
					}
					else
						;
				}

				putColoredPiece(p, q, 0); // 恢复
			}
		}
	return levelc;
}

// 轰炸机模块. （认为已落子）判断是否开始轰炸. 输入轰炸色·轰炸级·轰炸点总数·层数.
int bomber(int color, int level, int RBQOld, int layer)
{
	if (layer == 0) return 0; // 如果层数置空则返回0
	int color_that = (color == 2) ? 1 : 2; // 对方色子

	int list_that[MAXPOINTS];
	int listcount_that = stupidMachine(list_that, color); // 获取对方的拦截落子列表

	for (int t = 0; t < listcount_that; ++t) // 对于每一种可能的拦截方式
	{
		int thati = list_that[t] / 100;
		int thatj = list_that[t] % 100;
		putColoredPiece(thati, thatj, color_that); // 对方拦截落子
		int check_those = 0, check_victory = 0, attack = 0, defend = 3; // 初始化注意！

		/* Section.1 确认双方棋形 */

		for (int p = 1; p <= SIDELENGTH; ++p)
			for (int q = 1; q <= SIDELENGTH; ++q)
			{
				if (a[p][q] == 0)
				{
					putColoredPiece(p, q, color);
					int check_this = check_Cell_1(p, q), attack_temp = 0;

					if (judgmentSimplified(p, q, check_this)) // 禁手无视
					{
						if (check_this % 10 == QQQQQ || check_this % 10 == QQQQQQ) // 轰出五连或长连
							attack_temp = 5;
						else if (check_this == IVTOKENI
							|| (check_this > IVINF * 10 && check_this < 100)
							|| (check_this > IVINF * 100 && check_this < 1000)
							|| (check_this > IVINF * 1000 && check_this < 10000)) // 轰出四连、双四、四三
							attack_temp = 4;
						else if (level == 3 && check_this > IIIINF * 10) // 三级轰炸机轰出双三以上
							attack_temp = 3;
						else
							;
					}
					if (attack_temp > attack) attack = attack_temp; // 转存

					// putColoredPiece(p, q, 0); // 恢复

					putColoredPiece(p, q, color_that);
					int check_that = check_Cell_1(p, q), defend_temp = 0;

					if (judgmentSimplified(p, q, check_that)) // 禁手无视
					{
						if (check_that % 10 == QQQQQ || check_that % 10 == QQQQQQ) // 出现五连或长连
							defend_temp = 5;
						else if (level == 3
							&& (check_that == IVTOKENI
								|| (check_that > IVINF * 10 && check_that < 100)
								|| (check_that > IVINF * 100 && check_that < 1000)
								|| (check_that > IVINF * 1000 && check_that < 10000))) // 出现双四、四三、四连
							defend_temp = 4;
						else
							;
					}
					if (defend_temp > defend) defend = defend_temp; // 转存

					putColoredPiece(p, q, 0); // 恢复
				}
			}

		if (attack >= defend) check_victory = 1; // 判定轰炸机成立
		else if (defend == 4) level = 4; // 判定轰炸机必须升级
		else if (defend == 5)
		{
			putColoredPiece(thati, thatj, 0); // 中断前先恢复
			return 0; // 促进对方获胜的不是轰炸点！
		}
		else
			;

		/* End Section.1 确认双方棋形 */

		/* Section.2 获取我方轰炸点 */

		// 若已经轰炸成功则进入下一种对方拦截情况判断
		// 否则递归
		if (check_victory == 0)
		{
			// 己方下一步轰炸的所有可能落子点记录
			int bombc = 0, bombv[MAXPOINTS];
			int RBQNew = bombSearch(&bombc, bombv, color, level);

			if (RBQNew >= RBQOld) // 若轰炸点个数不减
			{
				for (int n = 0; n < bombc; ++n)
				{
					int thisi = bombv[n] / 100;
					int thisj = bombv[n] % 100; // 解析位置

					putColoredPiece(thisi, thisj, color); // 我方落子
					if (bomber(color, level, RBQNew, layer - 1)) // 递归·若下级传回1
					{
						check_victory = 1; // 存在一条路径使得轰炸成功
						putColoredPiece(thisi, thisj, 0); // 中断前先恢复
						break; // 跳出循环
					}
					putColoredPiece(thisi, thisj, 0); // 恢复
				}
			}
		}

		/* End Section.2 获取我方轰炸点 */

		putColoredPiece(thati, thatj, 0); // 恢复

		if (check_victory == 0) return 0; // 存在对方的一种拦截方式使得我方无法继续轰炸：这不是轰炸点
	}

	return 1; // 轰炸成功
}

// 输入己方色·级别. 判断己方列表中是否存在对应级别的轰炸机. 若存在则返回位置，否则返回0
int whereisthisbomber(int color, int level)
{
	int bombc = 0, bombv[MAXPOINTS];
	int RBQNew = bombSearch(&bombc, bombv, color, level);
	for (int n = 0; n < bombc; ++n)
	{
		int thisi = bombv[n] / 100;
		int thisj = bombv[n] % 100; // 解析位置

		if (a[thisi][thisj] == 0)
		{
			putColoredPiece(thisi, thisj, color);
			if (bomber(color, level, RBQNew, BOMBERLAYER)) // 如果轰炸机成立
			{
				putColoredPiece(thisi, thisj, 0); // 中断前先恢复
				return bombv[n]; // 返回位置
			}
			putColoredPiece(thisi, thisj, 0); // 恢复
		}
	}
	return 0; // 不存在轰炸机，返回0
}

// 输入对方色·级别. 判断对方列表中是否存在对应级别的轰炸机. 若存在则返回位置，否则返回0
int whereisthatbomber(int color, int level)
{
	int bombc = 0, bombv[MAXPOINTS];
	int RBQNew = bombSearch(&bombc, bombv, color, level);
	for (int n = 0; n < bombc; ++n)
	{
		int thisi = bombv[n] / 100;
		int thisj = bombv[n] % 100; // 解析位置

		if (a[thisi][thisj] == 0)
		{
			putColoredPiece(thisi, thisj, color);
			if (bomber(color, level, RBQNew, BOMBERLAYER)) // 如果轰炸机成立
			{
				putColoredPiece(thisi, thisj, (color == 2) ? 1 : 2); // 己方色子试图拦截
				if (judgmentSimplified(thisi, thisj, check_Cell_1(thisi, thisj)) // 如果该处为合法落子
					&& whereisthisbomber(color, 3) == 0) // 且不再存在轰炸机
				{
					putColoredPiece(thisi, thisj, 0); // 中断前先恢复
					return bombv[n]; // 返回位置
				}
			}
			putColoredPiece(thisi, thisj, 0); // 恢复
		}
	}
	return 0; // 不存在轰炸机，返回0
}
