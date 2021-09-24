#include "Header.h"

// ���ӻ���. ������Ǳ����ص���ɫ. ���������б��������б���Ч����.
int stupidMachine(int *positions, int color)
{
	int positionsnum = 0;
	for (int i = 1; i <= SIDELENGTH; ++i)
		for (int j = 1; j <= SIDELENGTH; ++j)
		{
			if (a[i][j] == 0)
			{
				putColoredPiece(i, j, color); // �����ص���ɫ
				int check_that = check_Cell_1(i, j);

				if (judgmentSimplified(i, j, check_that)) // ��������
				{
					if (check_that % 10 == QQQQQ || check_that % 10 == QQQQQQ) // ��������ʱ���ҽ��е����ط�ʽ
					{
						putColoredPiece(i, j, 0); // �ж�ǰ�Ȼָ�
						*positions = i * 100 + j;
						return 1;
					}
					else if (check_that == IVTOKENI || check_that == IVTOKENIII) // ���������ϻ�����������
					{
						*(positions + positionsnum) = i * 100 + j; // д�������б�
						positionsnum++; // �����б���Ч��������
					}
					else
						;
				}

				putColoredPiece(i, j, 0); // �ָ�
			}
		}
	return positionsnum;
}

// ��в�����. ������ɫ�뼶��. �ش���в���б�����в����Ч����. ������в��������.
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

				if (judgmentSimplified(p, q, check_this)) // ��������
				{
					if (check_this >= IVINF && check_this <= IVSUP)	// д���ĵļ�¼
					{
						*(bombv + (*bombc)++) = p * 100 + q;
						levelc++;
					}
					else if (check_this >= IIIINF && check_this <= IIISUP) // д�����ļ�¼
					{
						if (level == 3) *(bombv + (*bombc)++) = p * 100 + q;
						levelc++;
					}
					else
						;
				}

				putColoredPiece(p, q, 0); // �ָ�
			}
		}
	return levelc;
}

// ��ը��ģ��. ����Ϊ�����ӣ��ж��Ƿ�ʼ��ը. �����ըɫ����ը������ը������������.
int bomber(int color, int level, int RBQOld, int layer)
{
	if (layer == 0) return 0; // ��������ÿ��򷵻�0
	int color_that = (color == 2) ? 1 : 2; // �Է�ɫ��

	int list_that[MAXPOINTS];
	int listcount_that = stupidMachine(list_that, color); // ��ȡ�Է������������б�

	for (int t = 0; t < listcount_that; ++t) // ����ÿһ�ֿ��ܵ����ط�ʽ
	{
		int thati = list_that[t] / 100;
		int thatj = list_that[t] % 100;
		putColoredPiece(thati, thatj, color_that); // �Է���������
		int check_those = 0, check_victory = 0, attack = 0, defend = 3; // ��ʼ��ע�⣡

		/* Section.1 ȷ��˫������ */

		for (int p = 1; p <= SIDELENGTH; ++p)
			for (int q = 1; q <= SIDELENGTH; ++q)
			{
				if (a[p][q] == 0)
				{
					putColoredPiece(p, q, color);
					int check_this = check_Cell_1(p, q), attack_temp = 0;

					if (judgmentSimplified(p, q, check_this)) // ��������
					{
						if (check_this % 10 == QQQQQ || check_this % 10 == QQQQQQ) // �����������
							attack_temp = 5;
						else if (check_this == IVTOKENI
							|| (check_this > IVINF * 10 && check_this < 100)
							|| (check_this > IVINF * 100 && check_this < 1000)
							|| (check_this > IVINF * 1000 && check_this < 10000)) // ���������˫�ġ�����
							attack_temp = 4;
						else if (level == 3 && check_this > IIIINF * 10) // ������ը�����˫������
							attack_temp = 3;
						else
							;
					}
					if (attack_temp > attack) attack = attack_temp; // ת��

					// putColoredPiece(p, q, 0); // �ָ�

					putColoredPiece(p, q, color_that);
					int check_that = check_Cell_1(p, q), defend_temp = 0;

					if (judgmentSimplified(p, q, check_that)) // ��������
					{
						if (check_that % 10 == QQQQQ || check_that % 10 == QQQQQQ) // ������������
							defend_temp = 5;
						else if (level == 3
							&& (check_that == IVTOKENI
								|| (check_that > IVINF * 10 && check_that < 100)
								|| (check_that > IVINF * 100 && check_that < 1000)
								|| (check_that > IVINF * 1000 && check_that < 10000))) // ����˫�ġ�����������
							defend_temp = 4;
						else
							;
					}
					if (defend_temp > defend) defend = defend_temp; // ת��

					putColoredPiece(p, q, 0); // �ָ�
				}
			}

		if (attack >= defend) check_victory = 1; // �ж���ը������
		else if (defend == 4) level = 4; // �ж���ը����������
		else if (defend == 5)
		{
			putColoredPiece(thati, thatj, 0); // �ж�ǰ�Ȼָ�
			return 0; // �ٽ��Է���ʤ�Ĳ��Ǻ�ը�㣡
		}
		else
			;

		/* End Section.1 ȷ��˫������ */

		/* Section.2 ��ȡ�ҷ���ը�� */

		// ���Ѿ���ը�ɹ��������һ�ֶԷ���������ж�
		// ����ݹ�
		if (check_victory == 0)
		{
			// ������һ����ը�����п������ӵ��¼
			int bombc = 0, bombv[MAXPOINTS];
			int RBQNew = bombSearch(&bombc, bombv, color, level);

			if (RBQNew >= RBQOld) // ����ը���������
			{
				for (int n = 0; n < bombc; ++n)
				{
					int thisi = bombv[n] / 100;
					int thisj = bombv[n] % 100; // ����λ��

					putColoredPiece(thisi, thisj, color); // �ҷ�����
					if (bomber(color, level, RBQNew, layer - 1)) // �ݹ顤���¼�����1
					{
						check_victory = 1; // ����һ��·��ʹ�ú�ը�ɹ�
						putColoredPiece(thisi, thisj, 0); // �ж�ǰ�Ȼָ�
						break; // ����ѭ��
					}
					putColoredPiece(thisi, thisj, 0); // �ָ�
				}
			}
		}

		/* End Section.2 ��ȡ�ҷ���ը�� */

		putColoredPiece(thati, thatj, 0); // �ָ�

		if (check_victory == 0) return 0; // ���ڶԷ���һ�����ط�ʽʹ���ҷ��޷�������ը���ⲻ�Ǻ�ը��
	}

	return 1; // ��ը�ɹ�
}

// ���뼺��ɫ������. �жϼ����б����Ƿ���ڶ�Ӧ����ĺ�ը��. �������򷵻�λ�ã����򷵻�0
int whereisthisbomber(int color, int level)
{
	int bombc = 0, bombv[MAXPOINTS];
	int RBQNew = bombSearch(&bombc, bombv, color, level);
	for (int n = 0; n < bombc; ++n)
	{
		int thisi = bombv[n] / 100;
		int thisj = bombv[n] % 100; // ����λ��

		if (a[thisi][thisj] == 0)
		{
			putColoredPiece(thisi, thisj, color);
			if (bomber(color, level, RBQNew, BOMBERLAYER)) // �����ը������
			{
				putColoredPiece(thisi, thisj, 0); // �ж�ǰ�Ȼָ�
				return bombv[n]; // ����λ��
			}
			putColoredPiece(thisi, thisj, 0); // �ָ�
		}
	}
	return 0; // �����ں�ը��������0
}

// ����Է�ɫ������. �ж϶Է��б����Ƿ���ڶ�Ӧ����ĺ�ը��. �������򷵻�λ�ã����򷵻�0
int whereisthatbomber(int color, int level)
{
	int bombc = 0, bombv[MAXPOINTS];
	int RBQNew = bombSearch(&bombc, bombv, color, level);
	for (int n = 0; n < bombc; ++n)
	{
		int thisi = bombv[n] / 100;
		int thisj = bombv[n] % 100; // ����λ��

		if (a[thisi][thisj] == 0)
		{
			putColoredPiece(thisi, thisj, color);
			if (bomber(color, level, RBQNew, BOMBERLAYER)) // �����ը������
			{
				putColoredPiece(thisi, thisj, (color == 2) ? 1 : 2); // ����ɫ����ͼ����
				if (judgmentSimplified(thisi, thisj, check_Cell_1(thisi, thisj)) // ����ô�Ϊ�Ϸ�����
					&& whereisthisbomber(color, 3) == 0) // �Ҳ��ٴ��ں�ը��
				{
					putColoredPiece(thisi, thisj, 0); // �ж�ǰ�Ȼָ�
					return bombv[n]; // ����λ��
				}
			}
			putColoredPiece(thisi, thisj, 0); // �ָ�
		}
	}
	return 0; // �����ں�ը��������0
}
