#include "Header.h"

/* Part.5 ����ʤ��ƽ���ж�ģ�� ************************************************** */

// �˴�����ʹ����һ�������Ӽ���
extern int impossible_ooo_O;

// ����ʤ��ƽ���жϣ����ӡ���̣�
int judgment(int i, int j, int step)
{
	CLEARSCREEN; // �����Ļ
	printChessboard(i, j); // ��ӡ����

	int count_3 = 0, count_4 = 0, count_5 = 0, count_6 = 0; // �������������ӳ����������
	int check_result = check_Cell_1(i, j); // ��ȡ����״�������
	printf("%d\n", check_result); // ��ӡ����״�������

	// ��ӡ��������
	/*
	for (int u = 0; u <= SIDELENGTHXXXX - 1; ++u)
	{
		for (int v = 0; v <= SIDELENGTHEX - 1; ++v) printf("%d ", ar[u][v]);
		printf("\t");
		for (int v = 0; v <= SIDELENGTHEX - 1; ++v) printf("%d ", al[u][v]);
		printf("\n");
	}
	// */

	// ��ӡ��ʷ��¼
	for (int t = 1; t <= step; ++t) printf("%d %c | ",
		(playeri[t] == 0) ? 0 : SIDELENGTH + 1 - playeri[t], (playerj[t] == 0) ? '0' : 'A' + playerj[t] - 1);
	printf("\n\n");

	// ��������״�������
	do
	{
		if (check_result % 10 >= IIIINF && check_result % 10 <= IIISUP) count_3++;
		else if (check_result % 10 >= IVINF && check_result % 10 <= IVSUP) count_4++;
		else if (check_result % 10 == QQQQQ) count_5++;
		else if (check_result % 10 == QQQQQQ) count_6++;
		else
			;
		check_result = check_result / 10; // ȥ����λ��
	} while (check_result > 0);

	// �ϲ���һ�������Ӽ���
	count_4 += impossible_ooo_O;

	if (a[i][j] == 2 && count_5 == 0 && (count_3 > 1 || count_4 > 1 || count_6 > 0))
	{
		printf("Black loses on (%d, %d). White wins!\n", i, j); // ���ӽ��ְ���ʤ
		return 1;
	}
	else if (count_5 > 0 || count_6 > 0) // ����������ʤ
	{
		if (a[i][j] == 2) printf("Black "); // ���һ��Ϊ���������ʤ
		else printf("White "); // ���һ��Ϊ���������ʤ
		printf("wins!\n");
		return 2;
	}
	else if (step == CELLTOTAL) // ƽ���ж�
	{
		printf("The game ends in draw.\n");
		return 3;
	}
	else
		return 0;
}

// ���ֵļ��ж�. �����򷵻�0. �Ϸ��򷵻�1.
int judgmentSimplified(int i, int j, int check_result)
{
	int count_3 = 0, count_4 = 0, count_5 = 0, count_6 = 0; // �������������ӳ����������

	// ��������״�������
	do
	{
		if (check_result % 10 >= IIIINF && check_result % 10 <= IIISUP) count_3++;
		else if (check_result % 10 >= IVINF && check_result % 10 <= IVSUP) count_4++;
		else if (check_result % 10 == QQQQQ) count_5++;
		else if (check_result % 10 == QQQQQQ) count_6++;
		else
			;
		check_result = check_result / 10; // ȥ����λ��
	} while (check_result > 0);

	// �ϲ���һ�������Ӽ���
	count_4 += impossible_ooo_O;

	// ����������ʱ��˫��˫�ĳ�������
	if (a[i][j] == 2 && count_5 == 0 && (count_3 > 1 || count_4 > 1 || count_6 > 0)) return 0;
	return 1;
}
