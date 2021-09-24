#include "Header.h"

/* Part.2 ���̴�ӡģ�� ************************************************** */

// ��ӡ�б�
void printLineNumber(int i)
{
	printf("%2d ", SIDELENGTH + 1 - i);
}

// ��ӡ�б�
void printColumnNumber(int j)
{
	printf("%c ", j + 64);
}

// ��ӡ��Ԫ��
void printCell(int i, int j)
{
	if (a[i][j] == 2) printf("��"); // printf("%c%c", 0xa1, 0xf1); // ִ��Ϊ2���Ϊʵ��Բ
	else if (a[i][j] == 1) printf("��"); // printf("%c%c", 0xa1, 0xf2); // ִ��Ϊ1���Ϊ����Բ
	else
	{
		if (i == 1)
		{
			if (j == 1) printf("��"); // printf("%c%c", 0xa9, 0xb3);
			else if (j == SIDELENGTH) printf("��"); // printf("%c%c", 0xa9, 0xb7);
			else printf("��"); // printf("%c%c", 0xa9, 0xd3);
		}
		else if (i == SIDELENGTH)
		{
			if (j == 1) printf("��"); // printf("%c%c", 0xa9, 0xbb);
			else if (j == SIDELENGTH) printf("��"); // printf("%c%c", 0xa9, 0xbf);
			else printf("��"); // printf("%c%c", 0xa9, 0xdb);
		}
		else
		{
			if (j == 1) printf("��"); // printf("%c%c", 0xa9, 0xc4);
			else if (j == SIDELENGTH) printf("��"); // printf("%c%c", 0xa9, 0xcc);
			else printf("��"); // printf("%c%c", 0xa9, 0xe0);
		}
		SPACE;
	}
}

// ��ӡ����. �������һ����λ�úͲ���
void printChessboard(int i, int j)
{
	CLEARSCREEN;

	for (int p = 1; p <= SIDELENGTH; ++p)
	{
		printLineNumber(p); // ��ӡ����б�
		for (int q = 1; q <= SIDELENGTH; ++q)
		{
			if (p == i && q == j)
			{
				if (a[i][j] == 2) printf("��"); // printf("%c%c", 0xa1, 0xf8); // ���һ�ź��ӱ��Ϊʵ�Ľ�
				else printf("��"); // printf("%c%c", 0xa1, 0xf7); // ���һ�Ű��ӱ��Ϊ���Ľ�
			}
			else
				printCell(p, q); // ��ӡ��Ԫ��
		}
		printf("\n");
	}

	printf("   "); SPACE; // �������λ

	for (int q = 1; q <= SIDELENGTH; ++q) printColumnNumber(q); // ��ӡ�ײ��б�
	printf("\n\nLast step: (%d, %d) / (%d, %c)\n", i, j,
		(i == 0) ? 0 : SIDELENGTH + 1 - i, (j == 0) ? '0' : 'A' + j - 1); // ������
}
