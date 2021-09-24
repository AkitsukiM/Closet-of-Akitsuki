#include "Header.h"

/* 声明区：子模块函数声明 ************************************************** */

// 判断棋盘在函数check_Cell_2意义下的最优解
int check_Cells_2(int color);

// 输入己方色·级别. 判断己方列表中是否存在对应级别的轰炸机. 若存在则返回位置，否则返回0
int whereisthisbomber(int color, int level);

// 输入对方色·级别. 判断对方列表中是否存在对应级别的轰炸机. 若存在则返回位置，否则返回0
int whereisthatbomber(int color, int level);

/* Part.7 Person vs Artificial Ignorance 母模块 ************************************************** */

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
* 对方四连。
* 对方双四、四三。
* 对方以半四打头的必胜策略。
* 我方双三。
* 我方以三打头的必胜策略。
* 对方双三。
* 对方以三打头的必胜策略。
*
* 取有利格。
* 取不利格。
* 随机落子。
*/

// 计算机落子程序. 输入已下的步数.
int AI(int step)
{
	int color_this = (step + 1) % 2 + 1, color_that = step % 2 + 1;

	// 前三步随机
	int randi = 0, randj = 0;

	if (step == 0) return CENTERPOINT * 100 + CENTERPOINT;
	if (step == 1 || step == 2)
	{
		srand((unsigned)time(NULL));
		do
		{
			int randk = rand() % 9; // 取0~8随机数
			randi = randk % 3 - 1;
			randj = randk / 3 - 1; // 分配成(-1~1)*(-1~1)
		} while (a[playeri[1] + randi][playerj[1] + randj] > 0
			|| a[playeri[1] - randi][playerj[1] - randj] > 0); // 直到找到本格未落子且中心对称未落子的格
		return (playeri[1] + randi) * 100 + (playerj[1] + randj);
	}

	// 四五步布局
	if (step == 3 || step == 4) return check_Cells_2(color_this);

	// 主程序模块

	// 双方威胁度最高记录
	int attack = 0, attackP = 0;
	int defend = 0, defendP = 0;
	// 双方制胜格记录
	int thisVictoryP = 0, thatVictoryP = 0, bomberP = 0;

	for (int i = 1; i <= SIDELENGTH; ++i)
		for (int j = 1; j <= SIDELENGTH; ++j)
		{
			if (a[i][j] == 0) // 如果测试格为空
			{
				// 落己方色子
				putColoredPiece(i, j, color_this);
				int check_this = check_Cell_1(i, j);
				int is_this_legal = judgmentSimplified(i, j, check_this);

				if (is_this_legal) // 我方禁手跳过
				{
					// 取己方制胜格
					if (check_this % 10 == QQQQQ || check_this % 10 == QQQQQQ) thisVictoryP = i * 100 + j;
					// 取有利度最高的落子点或四连
					if ((check_this > attack && attack != IVTOKENI) || check_this == IVTOKENI)
					{
						attack = check_this;
						attackP = i * 100 + j; // 对有利格记录
					}
				}

				// 恢复
				// putColoredPiece(i, j, 0);

				// 落对方色子
				putColoredPiece(i, j, color_that);
				int check_that = check_Cell_1(i, j);
				int is_that_legal = judgmentSimplified(i, j, check_that);

				if (is_this_legal && is_that_legal) // 我方禁手与对方禁手均跳过
				{
					// 取对方制胜格
					if (check_that % 10 == QQQQQ || check_that % 10 == QQQQQQ) thatVictoryP = i * 100 + j;
					// 取不利度最高的落子点或四连
					if ((check_that > defend && defend != IVTOKENI) || check_that == IVTOKENI)
					{
						defend = check_that;
						defendP = i * 100 + j; // 对不利格记录
					}
				}

				// 恢复
				putColoredPiece(i, j, 0);
			}
		}

	// 返回己方制胜格
	if (thisVictoryP != 0) return thisVictoryP;
	// 返回对方制胜格
	if (thatVictoryP != 0) return thatVictoryP;
	// 若己方有四连、双四、四三
	if (attack == IVTOKENI
		|| (attack > IVINF * 10 && attack < 100)
		|| (attack > IVINF * 100 && attack < 1000)
		|| (attack > IVINF * 1000 && attack < 10000))
		return attackP;
	// 己方半四必胜预测
	if (bomberP = whereisthisbomber(color_this, 4)) return bomberP;

	// 若对方有双四、四三
	if ((defend > IVINF * 10 && defend < 100)
		|| (defend > IVINF * 100 && defend < 1000)
		|| (defend > IVINF * 1000 && defend < 10000))
		return defendP;
	// 对方半四必胜预测
	if (bomberP = whereisthatbomber(color_that, 4)) return bomberP;
	// 即使死也要死得有尊严之类的！
	if (defend == IVTOKENI) return defendP;

	// 若己方有双三
	if (attack > IIIINF * 10) return attackP;
	// 己方三必胜预测
	if (bomberP = whereisthisbomber(color_this, 3)) return bomberP;

	// 若对方有双三
	if (defend > IIIINF * 10) return defendP;
	// 对方三必胜预测
	if (bomberP = whereisthatbomber(color_that, 3)) return bomberP;

	return check_Cells_2(color_this);

	// 主程序模块结束

	// 若上述均不合则随机落子
	srand((unsigned)time(NULL));
	do
	{
		randi = rand() % SIDELENGTH + 1;
		randj = rand() % SIDELENGTH + 1;
	} while (a[randi][randj] > 0);
	return randi * 100 + randj;
}
