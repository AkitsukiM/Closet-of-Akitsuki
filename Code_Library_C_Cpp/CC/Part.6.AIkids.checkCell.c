#include "Header.h"

/* Part.6 Person vs A.I. ��ģ�飨�����߼���飩 ************************************************** */

double DefvsAtk = 8.0;

// ���ض��񣨽��뺯��ǰ�����ӣ��Ķ�������״�����
// ������������ֹ��ɣ��˴��������Ӻ��γɵľ��ơ��˴��������Ӻ󼺷�����һ���γɵľ��ơ��˴��������Ӻ�Է�����һ���γɵľ���
double check_Cell_2(int i, int j, int color, int check_it)
{
	int check_these = 0, check_those = 0, check_three = 0, check_four = 0;

	for (int p = 1; p <= SIDELENGTH; ++p)
		for (int q = 1; q <= SIDELENGTH; ++q)
		{
			if (a[p][q] == 0) // �������뱣֤���Ը�Ϊ��
			{
				putColoredPiece(p, q, color); // �伺��ɫ��
				int check_this = check_Cell_1(p, q);

				if (judgmentSimplified(p, q, check_this)) // ��������
				{
					// �޴󻯣���������
					if (check_this % 10 == QQQQQ || check_this % 10 == QQQQQQ) check_this += 10;
					if (check_this >= IIIINF && check_this <= IIISUP) check_three += check_this;
					if (check_this >= IVINF && check_this <= IVSUP) check_four += check_this;
					if (check_this > check_these) check_these = check_this;
				}

				// putColoredPiece(p, q, 0); // �ָ�

				putColoredPiece(p, q, (color == 2) ? 1 : 2); // ��Է�ɫ��
				int check_that = check_Cell_1(p, q);

				if (judgmentSimplified(p, q, check_that)) // ��������
				{
					// �޴󻯣���������
					if (check_that % 10 == QQQQQ || check_that % 10 == QQQQQQ) check_that += 10;
					if (check_that > check_those) check_those = check_that;
				}

				putColoredPiece(p, q, 0); // �ָ�
			}
		}

	return check_it + check_these + check_four + check_three - check_those * DefvsAtk;
}

// �ж������ں���check_Cell_2�����µ����Ž�
int check_Cells_2(int color)
{
	int bestposition = 0; // ��¼λ��
	double bestresult = (double)MINUSINFINITY; // ��¼���

	for (int p = 1; p <= SIDELENGTH; ++p)
		for (int q = 1; q <= SIDELENGTH; ++q)
		{
			if (a[p][q] == 0) // �������뱣֤���Ը�Ϊ��
			{
				putColoredPiece(p, q, color); // �伺��ɫ��
				int check_it = check_Cell_1(p, q);

				if (judgmentSimplified(p, q, check_it)) // ��������
				{
					double tempscore = check_Cell_2(p, q, color, check_it);
					if (tempscore > bestresult) // �����滻
					{
						bestresult = tempscore;
						bestposition = p * 100 + q;
					}
				}

				putColoredPiece(p, q, 0); // �ָ�
			}
		}

	return bestposition; // �������λ��
}
