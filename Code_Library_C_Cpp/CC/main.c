#include "Header.h"

// 棋盘虚延一圈作为主矩阵
int a[SIDELENGTHEX][SIDELENGTHEX];
// 转置矩阵，右下斜矩阵，左下斜矩阵
int at[SIDELENGTHEX][SIDELENGTHEX], ar[SIDELENGTHXXXX][SIDELENGTHEX], al[SIDELENGTHXXXX][SIDELENGTHEX];

// 历史记录
int playeri[CELLTOTAL + 1], playerj[CELLTOTAL + 1];

/* 声明区：只在这里用到的一些函数不在头文件声明 ************************************************** */

void initializeAllMatrices(); // 初始化操作
int judgment(int i, int j, int step); // 禁手胜手平手判断（兼打印棋盘）
int positionInputAnalysis(); // 解析用户输入
int SelectionInputAnalysis(char *s); // 仅允许输入1/2的模式选择
int AI(int step); // 计算机落子程序. 输入已下的步数.
extern double DefvsAtk; // 通过命令行参数修改DefvsAtk的值

/* Part.9 主函数 ************************************************** */

// 对战主程序
void Personvs(int choice)
{
	printChessboard(0, 0);
	int step = 0, position = 0, chance = 0, color = 0;
	while (1)
	{
		if (step % 2 + 1 == choice && chance == 0) position = AI(step); // Attention Please!
		else position = positionInputAnalysis(); // AI(step);
		if (position == 0) // 返回0表退出
		{
			break;
		}

		// /* 测试模块
#ifdef TEST
		else if (position == 1) // 返回1表强行落白子
		{
			chance = 2;
			color = 1;
		}
		else if (position == 2) // 返回2表强行落黑子
		{
			chance = 2;
			color = 2;
		}
		else if (position == 3) // 返回3表结束强制阶段，请求AI落子
		{
			if (chance != 2) printf("ERROR: TEST IS NOT RUNNING!\n"); // 当不处于强制阶段时-s非法
			else
			{
				chance = 0;
				color = 0;
				if (step % 2 + 1 != choice) step++;
			}
		}
#endif
		// */

		else if (position == 9) // 返回9表悔棋
		{
			if (step > 0) // 步数计数为正时才可悔棋
			{
				putColoredPiece(playeri[step], playerj[step], 0); // 棋格清除
				playeri[step] = 0; // 记录清除
				playerj[step] = 0;
				step--; // 步数回退
				if (chance == 0) chance = 1;

				CLEARSCREEN; // 清空屏幕
				printChessboard(playeri[step], playerj[step]); // 打印棋盘
				printf("\nBACKWARD SUCCESSFUL!\n\n");
			}
			else
			{
				printf("ERROR: BACKWARD FORBIDDEN!\n");
			}
		}
		else
		{
			if (chance == 1) chance = 0;
			step++; // 步数前进
			playeri[step] = position / 100;
			playerj[step] = position % 100; // 记录写入
			putColoredPiece(playeri[step], playerj[step], (chance == 2) ? color : step % 2 + 1); // 棋子放置
			if (judgment(playeri[step], playerj[step], step)) break; // 判断
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc == 2 && atof(argv[1]) >= 0.0) DefvsAtk = atof(argv[1]);
	initializeAllMatrices();

	printf(VERSIONINFO);
	int choice = SelectionInputAnalysis("Select a mode:\nPerson vs Person (1)\nPerson vs Artificial Ignorance (2)\n");
	if (choice == 1) Personvs(0);
	else Personvs(SelectionInputAnalysis("Do you want to be white(1) or black(2) ? Enter your choice:\n"));

	SYSTEMPAUSE;
	return 0;
}
