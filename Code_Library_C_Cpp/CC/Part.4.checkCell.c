#include "Header.h"

/* Part.4 ����״�����ģ�� ************************************************** */

// Ϊ���ⱨ�����þ�����ָ��
int *pointera = &a[0][0], *pointerat = &at[0][0], *pointerar = &ar[0][0], *pointeral = &al[0][0];

// �������ų��򣺴Ӵ�С����
int trick(unsigned int num)
{
	int x[10] = { 0,0,0,0,0,0,0,0,0,0 };
	int temp = 0;

	// ��������
	while (num > 0)
	{
		x[num % 10]++;
		num = num / 10;
	}

	// ����ģ��
	for (int i = 9; i >= 0; --i)
		for (int j = 0; j != x[i]; ++j)
			temp = temp * 10 + i;
	return temp;
}

// ��һ�������Ӽ������Ʒ�
int impossible_ooo_O = 0;

// ����״����鵥Ԫ
int check_C(int i, int j, int *x, int result)
{
	// ���������©������
	if (x == pointera || x == pointerat)
	{
		if (i < 1 || i > SIDELENGTH || j < 1 || j > SIDELENGTH) return result;
	}
	else
	{
		if (i < 0 || i > SIDELENGTHXXXX - 1 || j < 1 || j > SIDELENGTH) return result;
	}

	int color = *(x + i * SIDELENGTHEX + j);

	for (int q = j - 4; q <= j; ++q)
	{
		if (*(x + i * SIDELENGTHEX + q) == color
			&& *(x + i * SIDELENGTHEX + q + 1) == color
			&& *(x + i * SIDELENGTHEX + q + 2) == color
			&& *(x + i * SIDELENGTHEX + q + 3) == color
			&& *(x + i * SIDELENGTHEX + q + 4) == color)
		{
			if (*(x + i * SIDELENGTHEX + q + 5) == color || *(x + i * SIDELENGTHEX + q - 1) == color)
				return result * 10 + QQQQQQ; // ���� // ͬ�в��������������ι�ֱ�ӷ���
			else
				return result * 10 + QQQQQ; // ���� // ͬ�в��������������ι�ֱ�ӷ���
		}

		else if (*(x + i * SIDELENGTHEX + q + 1) == color
			&& *(x + i * SIDELENGTHEX + q + 2) == color
			&& *(x + i * SIDELENGTHEX + q + 3) == color
			&& *(x + i * SIDELENGTHEX + q + 4) == color)
		{
			if (*(x + i * SIDELENGTHEX + q) == 0 && *(x + i * SIDELENGTHEX + q + 5) == 0)
				result = result * 10 + IVTOKENI; // ����
			else if ((*(x + i * SIDELENGTHEX + q) == 0 && *(x + i * SIDELENGTHEX + q + 5) != color)
				|| (*(x + i * SIDELENGTHEX + q) != color && *(x + i * SIDELENGTHEX + q + 5) == 0))
				result = result * 10 + IVTOKENII; // ������
			else
				;
		}
		else if (*(x + i * SIDELENGTHEX + q - 1) != color
			&& *(x + i * SIDELENGTHEX + q) == color
			&& *(x + i * SIDELENGTHEX + q + 1) == color
			&& *(x + i * SIDELENGTHEX + q + 2) == color
			&& *(x + i * SIDELENGTHEX + q + 3) == 0
			&& *(x + i * SIDELENGTHEX + q + 4) == color) // Ϊ�����������ظ��������ӵ�����
		{
			// ˳��һʽ��
			if (*(x + i * SIDELENGTHEX + q - 1) == 0 && q + 4 == j) impossible_ooo_O++; // �������Ʒ�
			else if (*(x + i * SIDELENGTHEX + q + 5) == 0 && q == j) result = result * 10 + IVTOKENIII; // Ooo_o_��һʽ��
			else result = result * 10 + IVQQQAQ; // ʣ��������һʽ��
		}
		else if (*(x + i * SIDELENGTHEX + q) == color
			&& *(x + i * SIDELENGTHEX + q + 1) == 0
			&& *(x + i * SIDELENGTHEX + q + 2) == color
			&& *(x + i * SIDELENGTHEX + q + 3) == color
			&& *(x + i * SIDELENGTHEX + q + 4) == color
			&& *(x + i * SIDELENGTHEX + q + 5) != color) // Ϊ�����������ظ��������ӵ�����
		{
			// ����һʽ��
			if (*(x + i * SIDELENGTHEX + q + 5) == 0 && q == j) impossible_ooo_O++; // �������Ʒ�
			else if (*(x + i * SIDELENGTHEX + q - 1) == 0 && q + 4 == j) result = result * 10 + IVTOKENIII; // _o_ooO��һʽ��
			else result = result * 10 + IVQQQAQ; // ʣ��������һʽ��
		}
		else if (*(x + i * SIDELENGTHEX + q - 1) != color
			&& *(x + i * SIDELENGTHEX + q) == color
			&& *(x + i * SIDELENGTHEX + q + 1) == color
			&& *(x + i * SIDELENGTHEX + q + 2) == 0
			&& *(x + i * SIDELENGTHEX + q + 3) == color
			&& *(x + i * SIDELENGTHEX + q + 4) == color
			&& *(x + i * SIDELENGTHEX + q + 5) != color) // Ϊ��������һ�ظ��������ӵ�����
		{
			if (*(x + i * SIDELENGTHEX + q + 5) == 0 && q == j) result = result * 10 + IVTOKENIII; // Oo_oo_����ʽ��
			else if (*(x + i * SIDELENGTHEX + q - 1) == 0 && q + 4 == j) result = result * 10 + IVTOKENIII; // _oo_oO����ʽ��
			else result = result * 10 + IVQQAQQ; // ����ʽ��
		}

		else if (
			*(x + i * SIDELENGTHEX + q) != color
			&& *(x + i * SIDELENGTHEX + q + 1) == 0
			&& *(x + i * SIDELENGTHEX + q + 2) == color
			&& *(x + i * SIDELENGTHEX + q + 3) == color
			&& *(x + i * SIDELENGTHEX + q + 4) == color
			&& *(x + i * SIDELENGTHEX + q + 5) == 0
			&& *(x + i * SIDELENGTHEX + q + 6) != color) // Ϊ��������һ�ظ��������ӵ�����
		{
			if (color == 2) // ����Ǻ���
			{
				if ((*(x + i * SIDELENGTHEX + q) == 0 && *(x + i * SIDELENGTHEX + q - 1) != color)
					|| (*(x + i * SIDELENGTHEX + q + 6) == 0 && *(x + i * SIDELENGTHEX + q + 7) != color))
					return result * 10 + IIIQQQ; // ������ // ͬ�в��������������ι�ֱ�ӷ���
			}
			else // ����ǰ���
			{
				if (*(x + i * SIDELENGTHEX + q) == 0 || *(x + i * SIDELENGTHEX + q + 6) == 0) // �������˶�����
					result = result * 10 + IIIQQQ; // ����
			}
		}
		else if (*(x + i * SIDELENGTHEX + q) == 0
			&& *(x + i * SIDELENGTHEX + q + 1) == color
			&& *(x + i * SIDELENGTHEX + q + 2) == color
			&& *(x + i * SIDELENGTHEX + q + 3) == 0
			&& *(x + i * SIDELENGTHEX + q + 4) == color
			&& *(x + i * SIDELENGTHEX + q + 5) == 0)
		{
			if (color == 2) // ����Ǻ���
			{
				if (*(x + i * SIDELENGTHEX + q - 1) != color && *(x + i * SIDELENGTHEX + q + 6) != color)
					return result * 10 + IIIQQAQ; // ������ // ͬ�в��������������ι�ֱ�ӷ���
			}
			else // ����ǰ���
				result = result * 10 + IIIQQAQ; // ����
		}
		else if (*(x + i * SIDELENGTHEX + q) == 0
			&& *(x + i * SIDELENGTHEX + q + 1) == color
			&& *(x + i * SIDELENGTHEX + q + 2) == 0
			&& *(x + i * SIDELENGTHEX + q + 3) == color
			&& *(x + i * SIDELENGTHEX + q + 4) == color
			&& *(x + i * SIDELENGTHEX + q + 5) == 0)
		{
			if (color == 2) // ����Ǻ���
			{
				if (*(x + i * SIDELENGTHEX + q - 1) != color && *(x + i * SIDELENGTHEX + q + 6) != color)
					return result * 10 + IIIQQAQ; // ������ // ͬ�в��������������ι�ֱ�ӷ���
			}
			else // ����ǰ���
				result = result * 10 + IIIQQAQ; // ����
		}
		else
			;
	}

	return result;
}

// ���ض��񣨽��뺯��ǰ�����ӣ���һ������״�����
int check_Cell_1(int i, int j)
{
	int result = 0; // �������Ϊresult
	impossible_ooo_O = 0; // ��ʼ��

	result = check_C(i, j, pointera, result); // ������
	result = check_C(j, i, pointerat, result); // ������

	int u, v; // u��v��ת��ԭ��ͬ��

	u = i - j + SIDELENGTH - 5;
	if (i <= j) v = i;
	else v = j;
	if (u >= 0 && u <= SIDELENGTHXXXX - 1 && v >= 1 && v <= SIDELENGTH) // �������
		result = check_C(u, v, pointerar, result); // ��б����

	u = i + j - 6;
	if (i + j <= SIDELENGTH + 1) v = i;
	else v = SIDELENGTH + 1 - j;
	if (u >= 0 && u <= SIDELENGTHXXXX - 1 && v >= 1 && v <= SIDELENGTH) // �������
		result = check_C(u, v, pointeral, result); // ��б����

	result = trick(result);
	return result;
}
