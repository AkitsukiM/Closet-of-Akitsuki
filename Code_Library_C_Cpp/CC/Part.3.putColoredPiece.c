#include "Header.h"

/* Part.3 矩阵操作模块 ************************************************** */

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
void updateAllMatrices(int i, int j)
{
	int u, v;

	// 由转置矩阵可知
	at[j][i] = a[i][j];

	u = i - j + SIDELENGTH - 5;
	if (i <= j) v = i;
	else v = j;
	if (u >= 0 && u <= SIDELENGTHXXXX - 1 && v >= 1 && v <= SIDELENGTH) // 避免溢出
		ar[u][v] = a[i][j];

	u = i + j - 6;
	if (i + j <= SIDELENGTH + 1) v = i;
	else v = SIDELENGTH + 1 - j;
	if (u >= 0 && u <= SIDELENGTHXXXX - 1 && v >= 1 && v <= SIDELENGTH) // 避免溢出
		al[u][v] = a[i][j];
}

// 初始化操作
void initializeAllMatrices()
{
	// 初始化斜向矩阵
	for (int u = 0; u <= SIDELENGTHXXXX - 1; ++u)
		for (int v = 0; v <= SIDELENGTHEX - 1; ++v)
		{
			ar[u][v] = al[u][v] = 3; // 初始化设置为阻拦
		}

	// 初始化主矩阵与转置矩阵
	for (int i = 0; i <= SIDELENGTHEX - 1; ++i)
		for (int j = 0; j <= SIDELENGTHEX - 1; ++j)
		{
			if (i == 0 || i == SIDELENGTHEX - 1 || j == 0 || j == SIDELENGTHEX - 1) a[i][j] = 3;
			else a[i][j] = 0;
			updateAllMatrices(i, j);
		}

	// 初始化历史记录
	for (int t = 0; t <= CELLTOTAL; ++t) playeri[t] = playerj[t] = 0;
}

// 代理落子程序
void putColoredPiece(int i, int j, int color)
{
	a[i][j] = color;
	updateAllMatrices(i, j);
}
