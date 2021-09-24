#include "Header.h"

/* Part.3 �������ģ�� ************************************************** */

/*
* ar:
* "0"-"m-5": position from (0,m-5)-(6,m+1) to (0,0)-(m+1,m+1), size from 7 to m+2
* "m-5+1"-"m-5+m-5": position from (1,0)-(m+1,m) to (m-5,0)-(m+1,6), size from m+1 to 7
* al:
* "0"-"m-5": position from (0,6)-(6,0) to (0,m+1)-(m+1,0), size from 7 to m+2
* "m-5+1"-"m-5+m-5": position from (1,m+1)-(m+1,1) to (m-5,m+1)-(m+1,m-5), size from m+1 to 7
*
* ����a[i][j]
* ar:
* ���ڱ��Ϊ i - j + m - 5 ����
* �� i - j <= 0 ʱ���Ϊ i
* �� i - j > 0 ʱ���Ϊ j
* al:
* ���ڱ��Ϊ i + j - 6 ����
* �� i + j <= m + 1 ʱ���Ϊ i
* �� i + j > m + 1 ʱ���Ϊ m + 1 - j
*/

// ���ض�����¸�������
void updateAllMatrices(int i, int j)
{
	int u, v;

	// ��ת�þ����֪
	at[j][i] = a[i][j];

	u = i - j + SIDELENGTH - 5;
	if (i <= j) v = i;
	else v = j;
	if (u >= 0 && u <= SIDELENGTHXXXX - 1 && v >= 1 && v <= SIDELENGTH) // �������
		ar[u][v] = a[i][j];

	u = i + j - 6;
	if (i + j <= SIDELENGTH + 1) v = i;
	else v = SIDELENGTH + 1 - j;
	if (u >= 0 && u <= SIDELENGTHXXXX - 1 && v >= 1 && v <= SIDELENGTH) // �������
		al[u][v] = a[i][j];
}

// ��ʼ������
void initializeAllMatrices()
{
	// ��ʼ��б�����
	for (int u = 0; u <= SIDELENGTHXXXX - 1; ++u)
		for (int v = 0; v <= SIDELENGTHEX - 1; ++v)
		{
			ar[u][v] = al[u][v] = 3; // ��ʼ������Ϊ����
		}

	// ��ʼ����������ת�þ���
	for (int i = 0; i <= SIDELENGTHEX - 1; ++i)
		for (int j = 0; j <= SIDELENGTHEX - 1; ++j)
		{
			if (i == 0 || i == SIDELENGTHEX - 1 || j == 0 || j == SIDELENGTHEX - 1) a[i][j] = 3;
			else a[i][j] = 0;
			updateAllMatrices(i, j);
		}

	// ��ʼ����ʷ��¼
	for (int t = 0; t <= CELLTOTAL; ++t) playeri[t] = playerj[t] = 0;
}

// �������ӳ���
void putColoredPiece(int i, int j, int color)
{
	a[i][j] = color;
	updateAllMatrices(i, j);
}
