#include "Header.h"

/* ����������ģ�麯������ ************************************************** */

// �ж������ں���check_Cell_2�����µ����Ž�
int check_Cells_2(int color);

// ���뼺��ɫ������. �жϼ����б����Ƿ���ڶ�Ӧ����ĺ�ը��. �������򷵻�λ�ã����򷵻�0
int whereisthisbomber(int color, int level);

// ����Է�ɫ������. �ж϶Է��б����Ƿ���ڶ�Ӧ����ĺ�ը��. �������򷵻�λ�ã����򷵻�0
int whereisthatbomber(int color, int level);

/* Part.7 Person vs Artificial Ignorance ĸģ�� ************************************************** */

/*
* ԭ�������ȹ���
* �������Ӻ�Է����ܳ�˫���ĳ����࣬�������Ӻ󼺷��ܳ��ĳ����࣬�������Ӻ󼺷���һ�����ܳ��ĳ����ࡣ
*
* ���ֳ�������ȼ�˳���
*
* �ҷ�������
* �Է�������
*
* �ҷ�������
* �ҷ�˫�ġ�������
* �ҷ��԰��Ĵ�ͷ�ı�ʤ���ԡ�
* �Է�������
* �Է�˫�ġ�������
* �Է��԰��Ĵ�ͷ�ı�ʤ���ԡ�
* �ҷ�˫����
* �ҷ�������ͷ�ı�ʤ���ԡ�
* �Է�˫����
* �Է�������ͷ�ı�ʤ���ԡ�
*
* ȡ������
* ȡ������
* ������ӡ�
*/

// ��������ӳ���. �������µĲ���.
int AI(int step)
{
	int color_this = (step + 1) % 2 + 1, color_that = step % 2 + 1;

	// ǰ�������
	int randi = 0, randj = 0;

	if (step == 0) return CENTERPOINT * 100 + CENTERPOINT;
	if (step == 1 || step == 2)
	{
		srand((unsigned)time(NULL));
		do
		{
			int randk = rand() % 9; // ȡ0~8�����
			randi = randk % 3 - 1;
			randj = randk / 3 - 1; // �����(-1~1)*(-1~1)
		} while (a[playeri[1] + randi][playerj[1] + randj] > 0
			|| a[playeri[1] - randi][playerj[1] - randj] > 0); // ֱ���ҵ�����δ���������ĶԳ�δ���ӵĸ�
		return (playeri[1] + randi) * 100 + (playerj[1] + randj);
	}

	// ���岽����
	if (step == 3 || step == 4) return check_Cells_2(color_this);

	// ������ģ��

	// ˫����в����߼�¼
	int attack = 0, attackP = 0;
	int defend = 0, defendP = 0;
	// ˫����ʤ���¼
	int thisVictoryP = 0, thatVictoryP = 0, bomberP = 0;

	for (int i = 1; i <= SIDELENGTH; ++i)
		for (int j = 1; j <= SIDELENGTH; ++j)
		{
			if (a[i][j] == 0) // ������Ը�Ϊ��
			{
				// �伺��ɫ��
				putColoredPiece(i, j, color_this);
				int check_this = check_Cell_1(i, j);
				int is_this_legal = judgmentSimplified(i, j, check_this);

				if (is_this_legal) // �ҷ���������
				{
					// ȡ������ʤ��
					if (check_this % 10 == QQQQQ || check_this % 10 == QQQQQQ) thisVictoryP = i * 100 + j;
					// ȡ��������ߵ����ӵ������
					if ((check_this > attack && attack != IVTOKENI) || check_this == IVTOKENI)
					{
						attack = check_this;
						attackP = i * 100 + j; // ���������¼
					}
				}

				// �ָ�
				// putColoredPiece(i, j, 0);

				// ��Է�ɫ��
				putColoredPiece(i, j, color_that);
				int check_that = check_Cell_1(i, j);
				int is_that_legal = judgmentSimplified(i, j, check_that);

				if (is_this_legal && is_that_legal) // �ҷ�������Է����־�����
				{
					// ȡ�Է���ʤ��
					if (check_that % 10 == QQQQQ || check_that % 10 == QQQQQQ) thatVictoryP = i * 100 + j;
					// ȡ��������ߵ����ӵ������
					if ((check_that > defend && defend != IVTOKENI) || check_that == IVTOKENI)
					{
						defend = check_that;
						defendP = i * 100 + j; // �Բ������¼
					}
				}

				// �ָ�
				putColoredPiece(i, j, 0);
			}
		}

	// ���ؼ�����ʤ��
	if (thisVictoryP != 0) return thisVictoryP;
	// ���ضԷ���ʤ��
	if (thatVictoryP != 0) return thatVictoryP;
	// ��������������˫�ġ�����
	if (attack == IVTOKENI
		|| (attack > IVINF * 10 && attack < 100)
		|| (attack > IVINF * 100 && attack < 1000)
		|| (attack > IVINF * 1000 && attack < 10000))
		return attackP;
	// �������ı�ʤԤ��
	if (bomberP = whereisthisbomber(color_this, 4)) return bomberP;

	// ���Է���˫�ġ�����
	if ((defend > IVINF * 10 && defend < 100)
		|| (defend > IVINF * 100 && defend < 1000)
		|| (defend > IVINF * 1000 && defend < 10000))
		return defendP;
	// �Է����ı�ʤԤ��
	if (bomberP = whereisthatbomber(color_that, 4)) return bomberP;
	// ��ʹ��ҲҪ����������֮��ģ�
	if (defend == IVTOKENI) return defendP;

	// ��������˫��
	if (attack > IIIINF * 10) return attackP;
	// ��������ʤԤ��
	if (bomberP = whereisthisbomber(color_this, 3)) return bomberP;

	// ���Է���˫��
	if (defend > IIIINF * 10) return defendP;
	// �Է�����ʤԤ��
	if (bomberP = whereisthatbomber(color_that, 3)) return bomberP;

	return check_Cells_2(color_this);

	// ������ģ�����

	// ���������������������
	srand((unsigned)time(NULL));
	do
	{
		randi = rand() % SIDELENGTH + 1;
		randj = rand() % SIDELENGTH + 1;
	} while (a[randi][randj] > 0);
	return randi * 100 + randj;
}
