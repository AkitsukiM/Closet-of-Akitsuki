/*
* Gobang Console Game
* Version 1.1.9.31
* (c) 2018 �����ħ������^. All rights reserved.
* 
* Date modified: 2018/08/31
* Update Info:
* 1. 
* Bug Report:
* 1. 
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

const int m = 15;
const int center = m / 2 + 1; // ����ʹ�����ĵ�
const int mm = m + 2; // ����ʹ��ָ��
int a[17][17]; // ����������һȦ��Ϊһ��(m+2)*(m+2)�ľ���
int at[17][17], ar[21][17], al[21][17]; // atΪת�þ���. ar, alΪ����(2m-9)*(m+2)��б�����.

int *first[4] = { &a[0][0], &at[0][0], &ar[0][0], &al[0][0] };
int **aa = &first[0];

int player_i[225], player_j[225]; // ��ʷ��¼

// double time_total = 0, time_black = 0, time_white = 0;

// �������ų��򣺳�9��������ִӴ�С����
int trick(unsigned int num)
{
	int x[10] = { 0,0,0,0,0,0,0,0,0,0 };
	int temp = 0;

	// ��������
	do
	{
		x[num % 10]++;
		num = (num - num % 10) / 10;
	} while (num > 0);

	// ����ģ��
	for (int i = 8; i >= 0; --i)
		for (int j = 0; j != x[i]; ++j)
			temp = temp * 10 + i;
	for (int j = 0; j != x[9]; ++j)
		temp = temp * 10 + 9;
	return temp;
}

// ��ӡ�б�
void print_Ln(int i)
{
	printf("%c ", i + 64);
}

// ��ӡ�б�
void print_Col(int j)
{
	switch (j)
	{
	case 1: printf("%c%c", 0xa2, 0xc5); break;
	case 2: printf("%c%c", 0xa2, 0xc6); break;
	case 3: printf("%c%c", 0xa2, 0xc7); break; 
	case 4: printf("%c%c", 0xa2, 0xc8); break;
	case 5: printf("%c%c", 0xa2, 0xc9); break;
	case 6: printf("%c%c", 0xa2, 0xca); break;
	case 7: printf("%c%c", 0xa2, 0xcb); break;
	case 8: printf("%c%c", 0xa2, 0xcc); break;
	case 9: printf("%c%c", 0xa2, 0xcd); break;
	case 10: printf("%c%c", 0xa2, 0xce); break;
	case 11: printf("%c%c", 0xa2, 0xcf); break;
	case 12: printf("%c%c", 0xa2, 0xd0); break;
	case 13: printf("%c%c", 0xa2, 0xd1); break;
	case 14: printf("%c%c", 0xa2, 0xd2); break;
	case 15: printf("%c%c", 0xa2, 0xd3); break;
	default: printf("  ");
	}
}

// ��ӡ��Ԫ��
void print_Cell(int i, int j)
{
	if (a[i][j] == 2) printf("%c%c", 0xa1, 0xf1); // ִ��Ϊ2���Ϊʵ��Բ
	else if (a[i][j] == 1) printf("%c%c", 0xa1, 0xf0); //ִ��Ϊ1���Ϊ����Բ
	else
	{
		if (j == m)
		{
			if (i == 1) printf("%c%c", 0xa9, 0xb4);
			else if (i == m) printf("%c%c", 0xa9, 0xbc);
			else printf("%c%c", 0xa9, 0xc8);
		}
		else if (j == 1)
		{
			if (i == 1) printf("%c%c", 0xa9, 0xb0);
			else if (i == m) printf("%c%c", 0xa9, 0xb8);
			else printf("%c%c", 0xa9, 0xc0);
		}
		else
		{
			if (i == 1) printf("%c%c", 0xa9, 0xd0);
			else if (i == m) printf("%c%c", 0xa9, 0xd8);
			else printf("%c%c", 0xa9, 0xe0);
		}
	}
}

// ��ӡ����
void print_Chess(int i, int j, int step)
{
	// printf("Black:  %.1f\tWhite:  %.1f\n\n", time_black, time_white); // �ر��ӡ��

	printf("  "); // ������*
	for (int q = 0; q <= m; ++q) print_Col(q); // ��ӡ���϶��б���
	printf("\n");

	for (int p = 1; p <= m; ++p)
	{
		print_Ln(p); // ��ӡ�б�
		print_Col(p); // ������*
		for (int q = 1; q <= m; ++q)
		{
			if (p == i && q == j)
			{
				if (step % 2 == 1) printf("%c%c", 0xa1, 0xf6); // ���һ�ź�����ʾΪ����
				else printf("%c%c", 0xa1, 0xf2); // ���һ�Ű�����ʾΪ˫Բ
			}
			else
				print_Cell(p, q); // ��ӡ��Ԫ��
		}
		printf("\n");
	}
	printf("\nLast Step: (%d, %d)\n", i, j); // ������*
}

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
void renew_Cell(int i_x, int j_x, int **xx)
{
	int *x = *xx, *xt = *(xx + 1), *xr = *(xx + 2), *xl = *(xx + 3);

	int i_xr, j_xr;

	// ��ת�þ����֪
	*(xt + j_x * mm + i_x) = *(x + i_x * mm + j_x);

	i_xr = i_x - j_x + m - 5;
	if (i_x <= j_x) j_xr = i_x;
	else j_xr = j_x;
	// ���������©������
	if (i_xr >= 0 && i_xr <= 2 * m - 10 && j_xr >= 1 && j_xr <= m)
		*(xr + i_xr * mm + j_xr) = *(x + i_x * mm + j_x);

	i_xr = i_x + j_x - 6;
	if (i_x + j_x <= m + 1) j_xr = i_x;
	else j_xr = m + 1 - j_x;
	// ���������©������
	if (i_xr >= 0 && i_xr <= 2 * m - 10 && j_xr >= 1 && j_xr <= m)
		*(xl + i_xr * mm + j_xr) = *(x + i_x * mm + j_x);
}

// ���ӷ�Χ��¼
// int tp = center, bm = center, lt = center, rt = center;
// ���ӷ�Χ��չ��¼
// int tp_plus = tp - 2, bm_plus = bm + 2, lt_plus = lt - 2, rt_plus = rt + 2;

// �������ӳ���
void new_Cell(int i_x, int j_x, int **xx, int color)
{
	int *x = *xx, *xt = *(xx + 1), *xr = *(xx + 2), *xl = *(xx + 3);

	*(x + i_x * mm + j_x) = color; // ����

	// ע��ȥ�������ӷ�Χ��¼����

	renew_Cell(i_x, j_x, xx); // ���¸�������
}

// �����һʽ�ĵ�������������¼������Ϊȫ�ֱ���
int result_3 = 0;

// ����״����鵥Ԫ**
int check_C(int i_x, int j_x, int *x, int result)
{
	// ���������©������
	if (x == *aa || x == *(aa + 1))
	{
		if (i_x < 1 || i_x > m || j_x < 1 || j_x > m) return result;
	}
	else
	{
		if (i_x < 0 || i_x > 2 * m - 10 || j_x < 1 || j_x > m) return result;
	}

	int color = *(x + i_x * mm + j_x);

	for (int j = j_x - 4; j <= j_x; ++j)
	{
		if (*(x + i_x * mm + j) == color && *(x + i_x * mm + j + 1) == color && *(x + i_x * mm + j + 2) == color
			&& *(x + i_x * mm + j + 3) == color && *(x + i_x * mm + j + 4) == color)
		{
			if (j < j_x && *(x + i_x * mm + j + 5) == color) result = result * 10 + 1; // ����
			result = result * 10 + 9; // ����
		}

		else if (*(x + i_x * mm + j + 1) == color && *(x + i_x * mm + j + 2) == color && *(x + i_x * mm + j + 3) == color && *(x + i_x * mm + j + 4) == color)
		{
			if (*(x + i_x * mm + j) < 0 && *(x + i_x * mm + j + 5) < 0)
				result = result * 10 + 8; // ����
			else if ((*(x + i_x * mm + j) < 0 && *(x + i_x * mm + j + 5) != color) // Ϊ�����������ظ��������ӵ�����
				|| *(x + i_x * mm + j + 5) < 0) // ע���˴����ظ�����������Ϊ���㸽���������Ѿ���������
				result = result * 10 + 5; // ������
			else
				;
		}
		else if (*(x + i_x * mm + j) == color && *(x + i_x * mm + j + 1) == color && *(x + i_x * mm + j + 2) == color
			&& *(x + i_x * mm + j + 3) < 0 && *(x + i_x * mm + j + 4) == color
			&& *(x + i_x * mm + j - 1) != color) // Ϊ�����������ظ��������ӵ�����
		{
			if (*(x + i_x * mm + j - 1) < 0 && j == j_x - 4) // �ų�����ʽ��һ��������
				;
			else
			{
				// ˳��һʽ��
				if (j == j_x && *(x + i_x * mm + j + 5) < 0) result = result * 10 + 7; // Ooo_o_��һʽ��
				else result = result * 10 + 4; // ʣ��������һʽ��
				if (*(x + i_x * mm + j - 1) < 0) result_3++; // �����һ�����Ƕ����ģ���һ��result_3
			}
		}
		else if (*(x + i_x * mm + j + 4) == color && *(x + i_x * mm + j + 3) == color && *(x + i_x * mm + j + 2) == color
			&& *(x + i_x * mm + j + 1) < 0 && *(x + i_x * mm + j) == color
			&& *(x + i_x * mm + j + 5) != color) // Ϊ�����������ظ��������ӵ�����
		{
			if (*(x + i_x * mm + j + 5) < 0 && j == j_x) // �ų�����ʽ��һ��������
				;
			else
			{
				// ����һʽ��
				if (j == j_x - 4 && *(x + i_x * mm + j - 1) < 0) result = result * 10 + 7; // _o_ooO��һʽ��
				else result = result * 10 + 4; // ʣ��������һʽ��
				if (*(x + i_x * mm + j + 5) < 0) result_3++; // �����һ�����Ƕ����ģ���һ��result_3
			}
		}
		else if (*(x + i_x * mm + j) == color && *(x + i_x * mm + j + 1) == color && *(x + i_x * mm + j + 2) < 0
			&& *(x + i_x * mm + j + 3) == color && *(x + i_x * mm + j + 4) == color
			&& *(x + i_x * mm + j - 1) != color && *(x + i_x * mm + j + 5) != color) // Ϊ��������һ�ظ��������ӵ�����
		{
			if (j == j_x && *(x + i_x * mm + j + 5) < 0) result = result * 10 + 7; // Oo_oo_����ʽ��
			else if (j == j_x - 4 && *(x + i_x * mm + j - 1) < 0) result = result * 10 + 7; // _oo_oO����ʽ��
			else result = result * 10 + 4; // ����ʽ��
		}

		else if (*(x + i_x * mm + j + 1) == color && *(x + i_x * mm + j + 2) == color && *(x + i_x * mm + j + 3) == color
			&& *(x + i_x * mm + j) < 0 && *(x + i_x * mm + j + 4) < 0
			&& *(x + i_x * mm + j - 1) != color && *(x + i_x * mm + j + 5) != color) // Ϊ��������һ�ظ��������ӵ�����
			result = result * 10 + 3; // ����
		else if (*(x + i_x * mm + j + 1) == color && *(x + i_x * mm + j + 2) == color && *(x + i_x * mm + j + 3) < 0 && *(x + i_x * mm + j + 4) == color
			&& (*(x + i_x * mm + j) < 0 && *(x + i_x * mm + j + 5) < 0))
			result = result * 10 + 2; // ��һʽ��
		else if (*(x + i_x * mm + j + 1) == color && *(x + i_x * mm + j + 2) < 0 && *(x + i_x * mm + j + 3) == color && *(x + i_x * mm + j + 4) == color
			&& (*(x + i_x * mm + j) < 0 && *(x + i_x * mm + j + 5) < 0))
			result = result * 10 + 2; // һ��ʽ��
		else
			;
	}

	return result;
}

// ���ض��񣨱��������ӣ�����һ������״�����
int check_Cell_1(int i_x, int j_x, int **xx)
{
	int *x = *xx, *xt = *(xx + 1), *xr = *(xx + 2), *xl = *(xx + 3);

	int result = 0; // �������Ϊresult
	result_3 = 0; // ͬʱ��ʼ����һʽ�Ķ����¼����

	// ������
	result = check_C(i_x, j_x, x, result);

	// ������
	result = check_C(j_x, i_x, xt, result);

	// б���飬ԭ��ͬ�ϡ�
	int i_xr, j_xr;

	i_xr = i_x - j_x + m - 5;
	if (i_x <= j_x) j_xr = i_x;
	else j_xr = j_x;

	// ��б����
	result = check_C(i_xr, j_xr, xr, result);

	i_xr = i_x + j_x - 6;
	if (i_x + j_x <= m + 1) j_xr = i_x;
	else j_xr = m + 1 - j_x;

	// ��б����
	result = check_C(i_xr, j_xr, xl, result);

	result = trick(result);
	return result;
}

// ���ض��񣨱��������ӣ����Ķ�������״�����
int check_Cell_2(int i_x, int j_x, int **xx, int color)
{
	int temp = 0, temp_3 = 0;

	int judgment_simplified(int i, int j, int check_result); // ��������

	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= m; ++j)
		{
			if (*(*xx + i * mm + j) < 0) // �������뱣֤���Ը�Ϊ��
			{
				new_Cell(i, j, xx, color); // ��ָ��ɫ��
				int check_result = check_Cell_1(i, j, xx);

				if (((check_result > temp && temp != 9) || temp == 9) // ȡ��������ߵ����ӵ������
					&& judgment_simplified(i, j, check_result) != 1) // ��������
					temp = check_result;

				if (check_result == 3 && judgment_simplified(i, j, check_result) != 1) // ��������ͳ��
					temp_3++;

				new_Cell(i, j, xx, -1); // �ָ�
			}
		}

	return temp * 100 + temp_3;
}

// ָʾ�ݹ������ȫ�ֱ���
int processes = 0;

// ���ض��񣨱��������ӣ�����N������״����� // ָ�봫��N��Ԥ��ĶԷ���в���뼺����в��
void check_Cell_N(int i_x, int j_x, int **xx, int step, int *danger_rt, int *profit_rt)
{
	int N = 4;

	int N_temp = (step - 3) / 2;
	if (N_temp < 0) N_temp = 0;
	else if (N_temp > N) N_temp = N;
	else
		;

	int AI_result = 0;
	int AI_i[8] = { 0,0,0,0,0,0,0,0 }, AI_j[8] = { 0,0,0,0,0,0,0,0 }; // N * 2
	int check_result = 0;

	int AI(int **xx, int step); // ��������

	for (int layer = 0; layer != N_temp; ++layer)
	{
		// ��Է�ɫ��
		AI_result = AI(xx, step + 1); // ִ�м�������ӳ���
		processes--; // �ָ��ϼ��ݹ����

		AI_i[layer * 2] = AI_result % 100;
		AI_j[layer * 2] = AI_result / 100;

		new_Cell(AI_i[layer * 2], AI_j[layer * 2], xx, step % 2 + 1);

		// �Է�ɫ�Ӽ��
		check_result = check_Cell_1(AI_i[layer * 2], AI_j[layer * 2], xx);
		if (check_result > *danger_rt) *danger_rt = check_result;

		// �伺��ɫ��
		AI_result = AI(xx, step); // ִ�м�������ӳ���
		processes--; // �ָ��ϼ��ݹ����

		AI_i[layer * 2 + 1] = AI_result % 100;
		AI_j[layer * 2 + 1] = AI_result / 100;

		new_Cell(AI_i[layer * 2 + 1], AI_j[layer * 2 + 1], xx, (step + 1) % 2 + 1);

		// ����ɫ�Ӽ��
		check_result = check_Cell_1(AI_i[layer * 2 + 1], AI_j[layer * 2 + 1], xx);
		if (check_result > *profit_rt) *profit_rt = check_result;
	}

	// �ָ�
	for (int t = 0; t != N_temp * 2; ++t) new_Cell(AI_i[t], AI_j[t], xx, -1);
}

// ʤ�ֽ����ж�
int judgment(int i, int j, int step)
{
	system("cls"); // �����Ļ
	print_Chess(i, j, step); // ��ӡ����

	int count_3 = 0, count_4 = 0, count_5 = 0, count_6 = 0; // �������������ӳ����������
	int check_result = check_Cell_1(i, j, aa); // ��ȡ����״�������
	printf("%d\n", check_result); // ��ӡ����״�������

	// printf("%d %d %d %d\n%d %d %d %d\n\n", tp, bm, lt, rt, tp_plus, bm_plus, lt_plus, rt_plus); // ��ӡ���ӷ�Χ

	// ��ӡ��������
	/*
	for (int ir = 0; ir <= 2 * m - 10; ++ir)
	{
		for (int jr = 0; jr <= m + 1; ++jr) printf("%d ", ar[ir][jr]);
		printf("\t");
		for (int jr = 0; jr <= m + 1; ++jr) printf("%d ", al[ir][jr]);
		printf("\n");
	}
	// */

	// ��ӡ��ʷ��¼
	// /*
	for (int t = 0; t != step; ++t) printf("%d %d | ", player_i[t], player_j[t]);
	printf("\n\n");
	// */

	// ��������״������� // **
	do
	{
		if (check_result % 10 == 3 || check_result % 10 == 2) count_3++;
		else if (check_result % 10 >= 4 && check_result % 10 <= 8) count_4++;
		else if (check_result % 10 == 9) count_5++;
		else if (check_result % 10 == 1) count_6++;
		else
			;
		check_result = (check_result - check_result % 10) / 10; // ȥ����λ��
	} while (check_result > 0);
	count_3 += result_3; // �ϲ�����ͳ�Ʋ���

	if (a[i][j] == 2 && count_6 > 0 && count_5 == (count_6 * 2)) // ���ӳ�������
	{
		printf("Black loses on (%d, %d). White wins!\n", i, j); // ���ӽ��ְ���ʤ
		return 1;
	}
	if (count_5 > 0) // ������ʤ
	{
		if (step % 2 == 1) printf("Black "); // ����������ʤ
		else printf("White "); // ż��������ʤ
		printf("wins!\n");
		return 2;
	}
	if (a[i][j] == 2 && (count_3 > 1 || count_4 > 1)) // ����˫��˫�Ľ���
	{
		printf("Black loses on (%d, %d). White wins!\n", i, j); // ���ӽ��ְ���ʤ
		return 1;
	}

	// ƽ���ж�ģ��
	if (step == m * m)
	{
		printf("The game ends in draw.\n");
		return 3;
	}

	return 0;
}

// ���ֵļ��ж�
int judgment_simplified(int i, int j, int check_result)
{
	int count_3 = 0, count_4 = 0, count_5 = 0, count_6 = 0; // �������������ӳ����������

	// ��������״������� // **
	do
	{
		if (check_result % 10 == 3 || check_result % 10 == 2) count_3++;
		else if (check_result % 10 >= 4 && check_result % 10 <= 8) count_4++;
		else if (check_result % 10 == 9) count_5++;
		else if (check_result % 10 == 1) count_6++;
		else
			;
		check_result = (check_result - check_result % 10) / 10; // ȥ����λ��
	} while (check_result > 0);
	count_3 += result_3; // �ϲ�����ͳ�Ʋ���

	if (a[i][j] == 2 && count_6 > 0 && count_5 == (count_6 * 2)) return 1; // ���ӳ�������
	if (a[i][j] == 2 && (count_3 > 1 || count_4 > 1)) return 1; // ����˫��˫�Ľ���
	return 0;
}

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
* �Է�����������ʤ�������������ԣ�
* �Է�˫�ġ�������
* �Է��԰��Ĵ�ͷ�ı�ʤ���ԡ�
*
* �ҷ�˫����
* �ҷ�������ͷ�ı�ʤ���ԡ�
* �Է�˫����
* �Է�������ͷ�ı�ʤ���ԡ�
*
* ˫����ֵ����
* �ҷ�������˫��
*
* �ҷ����ġ�����Ԥ����в����ߵġ�
* �Է����ġ�����Ԥ����в����ߵġ�
*
* �ҷ��������ֵ��
*
* ȡ������
* ȡ������
* ������ӡ�
*/

// ���ӽϼ�λ���жϳ���ģ��
int good(int *position, int size, int **xx, int step, int *max_rt, int *min_rt, int stage)
{
	int i[32], j[32], check_result[32];
	int max = 0, min = 0, max_p = 0, min_p = 0;

	for (int t = 0; t != size; ++t)
	{
		i[t] = (*(position + t)) % 100;
		j[t] = (*(position + t)) / 100;

		// ״����鲢�ָ�
		new_Cell(i[t], j[t], xx, (step + 1) % 2 + 1);

		// ��������λ�Է����Գ��ĳ�����
		if (stage == 0) check_result[t] = check_Cell_2(i[t], j[t], xx, step % 2 + 1);
		// ��������λ�������Գ��ĳ�����
		else if (stage == 1) check_result[t] = check_Cell_1(i[t], j[t], xx);
		// �������Ӻ󼺷���һ�����ܳ��ĳ�����
		else if (stage == 2) check_result[t] = check_Cell_2(i[t], j[t], xx, (step + 1) % 2 + 1);
		/*
		else if (stage == 3 || stage == 5)
		{
			// ��������λ�Է����Գ��ĳ����࣬ͳһ��λ
			int temp_danger_rt = check_Cell_2(i[t], j[t], xx, step % 2 + 1) / 100;
			// �������Ӻ󼺷���һ�����Գ����
			int temp_profit_rt = check_Cell_2(i[t], j[t], xx, (step + 1) % 2 + 1) / 100;
			// ������ǳ��壬�������Ч��
			if (step > 5 && temp_profit_rt % 10 != 9) temp_profit_rt = 0;

			if (stage == 3)
				// ע��danger��ֵ��Ҫ����
				check_result[t] = temp_profit_rt * 100 + 100 - temp_danger_rt;
			else
				// ע��profit��ֵ��Ҫ����
				check_result[t] = temp_danger_rt * 100 + 100 - temp_profit_rt;
		}
		*/
		// ���ϲ���ɾ����stage������֮����
		else if (stage == 3 || stage == 4)
		{
			int temp_danger_rt = 0, temp_profit_rt = 0;
			check_Cell_N(i[t], j[t], xx, step, &temp_danger_rt, &temp_profit_rt);

			if (stage == 3)	check_result[t] = temp_profit_rt * 100 + 100 - temp_danger_rt;
			else check_result[t] = temp_danger_rt * 100 + 100 - temp_profit_rt;
		}
		else
			;

		new_Cell(i[t], j[t], xx, -1);

		// ȡ���ֵ����Сֵ
		if (t == 0)
		{
			max = min = check_result[t];
			max_p = min_p = *(position + t);
		}
		else
		{
			if (check_result[t] > max)
			{
				max = check_result[t];
				max_p = *(position + t);
			}
			if (check_result[t] < min)
			{
				min = check_result[t];
				min_p = *(position + t);
			}
		}
	}

	// ָ��..._rt����N������
	if (stage == 3 || stage == 4) *max_rt = max;
	if (stage == 4) *min_rt = min;

	if (max != min)
	{
		if (stage >= 1 && stage <= 3) return max_p;
		else return min_p;
	}
	else return 0;
}

// ���ӽϼ�λ���жϳ���ͳģʽ
int good_ex(int *position, int size, int **xx, int step)
{
	int pst = good(position, size, xx, step, NULL, NULL, 0);
	if (pst != 0) return pst;
	else
	{
		pst = good(position, size, xx, step, NULL, NULL, 1);
		if (pst != 0) return pst;
		else
		{
			pst = good(position, size, xx, step, NULL, NULL, 2);
			if (pst != 0) return pst;
			else return *position;
		}
	}
}

// ���ӽϼ�λ���жϳ���Ԥ��ģʽ
int good_bns(int *position, int size, int **xx, int step, int *max_rt, int *min_rt, bool amI)
{
	if (amI == true)
	{
		int pst = good(position, size, xx, step, max_rt, NULL, 3);
		if (pst != 0) return pst;
		else
		{
			pst = good(position, size, xx, step, NULL, NULL, 1);
			if (pst != 0) return pst;
			else return *position;
		}
	}
	else
	{
		int pst = good(position, size, xx, step, max_rt, min_rt, 4);
		if (pst != 0) return pst;
		else
		{
			pst = good(position, size, xx, step, NULL, NULL, 1);
			if (pst != 0) return pst;
			else return *position;
		}
	}
}

// ��������ӳ���
int AI(int **xx, int step)
{
	processes++; // ���뺯��

	// ��processes��صĿռ临�Ӷȣ���ߵ��ô�����
	const int complex = 1;

	// ǰ�������
	int rand_i = 0, rand_j = 0;

	if (step == 0) return center * 100 + center;
	if (step == 1 || step == 2)
	{
		do
		{
			srand((unsigned)time(NULL));
			int rand_ij = rand() % 9;
			rand_i = rand_ij % 3 - 1;
			rand_j = rand_ij / 3 - 1;
		} while (a[center + rand_i][center + rand_j] >= 0 || a[center - rand_i][center - rand_j] >= 0);
		return (center + rand_j) * 100 + (center + rand_i);
	}

	// ���岽����
	if (step == 3 || step == 4)
	{
		int best_rt = 0, best_position = 0;
		for (int i = 0; i <= m; ++i)
			for (int j = 0; j <= m; ++j)
			{
				if (*(*xx + i * mm + j) < 0) // �������뱣֤���Ը�Ϊ��
				{
					// �伺��ɫ��
					new_Cell(i, j, xx, (step + 1) % 2 + 1);

					int temp_danger_rt = check_Cell_2(i, j, xx, step % 2 + 1);
					int temp_profit_rt = check_Cell_2(i, j, xx, (step + 1) % 2 + 1);

					// �������ų���
					if (temp_profit_rt < 400)
					{
						// ���danger�����ұ�ֵ֤Ϊ��
						int temp_rt = temp_profit_rt + 400 - temp_danger_rt * 2;
						if (temp_rt > best_rt)
						{
							best_rt = temp_rt;
							best_position = j * 100 + i;
						}
					}

					// �ָ�
					new_Cell(i, j, xx, -1);
				}
			}
		return best_position;
	}

	// ������ģ��

	// ˫����в����߼�¼
	int profit = 0, profitP = 0;
	int danger = 0, dangerP = 0;

	// ��ʼ���������Ӧ��ָ�� // ע����good�������Ķ�Ӧ
	const int size = 16;
	int this_4P[16], that_4P[16], this_3P[32], that_3P[32];
	for (int t = 0; t != size; ++t)
		this_4P[t] = that_4P[t] = this_3P[2 * t] = that_3P[2 * t] = this_3P[2 * t + 1] = that_3P[2 * t + 1] = 0;

	int *this_4_first = &this_4P[0], *that_4_first = &that_4P[0], *this_3_first = &this_3P[0], *that_3_first = &that_3P[0];

	// ��Ч������ͳ��
	int this_4_size = 0, that_4_size = 0, this_3_size = 0, that_3_size = 0;

	// �ر�أ���Ҫͳ�ƶԷ�����
	int that_8P[8] = { 0,0,0,0,0,0,0,0 };
	int *that_8_first = &that_8P[0];
	int that_8_size = 0;

	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= m; ++j)
		{
			if (*(*xx + i * mm + j) < 0) // ������Ը�Ϊ��
			{
				// �����жϱ�ʶ
				bool is_this_illegal = false, is_that_illegal = false;

				// �伺��ɫ��
				new_Cell(i, j, xx, (step + 1) % 2 + 1);
				int check_this = check_Cell_1(i, j, xx);
				is_this_illegal = judgment_simplified(i, j, check_this);

				if (is_this_illegal == false) // �ҷ���������
				{
					// ȡ������ʤ��
					if (check_this % 10 == 9) return j * 100 + i; // ����������ʤ��������
					// ȡ��������ߵ����ӵ������
					if ((check_this > profit && profit != 8) || check_this == 8)
					{
						profit = check_this;
						profitP = j * 100 + i; // ���������¼
					}
					// ȡ������ص��������ӵ�
					if (check_this == 4 || check_this == 5)
					{
						for (int t = 0; t != size; ++t)
							if (this_4P[t] == 0)
							{
								this_4P[t] = j * 100 + i; // ����λ��
								this_4_size++;
								break;
							}
					}
					// ȡ������ص��������ӵ� // ע�⣺size * 2��
					if (check_this == 2 || check_this == 3)
					{
						for (int t = 0; t != size * 2; ++t)
							if (this_3P[t] == 0)
							{
								this_3P[t] = j * 100 + i; // ����λ��
								this_3_size++;
								break;
							}
					}
				}

				// �ָ�
				new_Cell(i, j, xx, -1);

				// ��Է�ɫ��
				new_Cell(i, j, xx, step % 2 + 1);
				int check_that = check_Cell_1(i, j, xx);
				is_that_illegal = judgment_simplified(i, j, check_that);

				if (is_this_illegal == false && is_that_illegal == false) // �ҷ�������Է����־�����
				{
					// ȡ�Է���ʤ��
					if (check_that % 10 == 9) return j * 100 + i; // ����������ʤ��������
					// ȡ��������ߵ����ӵ������
					if ((check_that > danger && danger != 8) || check_that == 8)
					{
						danger = check_that;
						dangerP = j * 100 + i; // �Բ������¼
					}
					// ȡ��������ص��������ӵ�
					if (check_that == 8 || check_that == 7)
					{
						for (int t = 0; t != size; ++t)
							if (that_8P[t] == 0)
							{
								that_8P[t] = j * 100 + i; // ����λ��
								that_8_size++;
								break;
							}
					}
					// ȡ������ص��������ӵ�
					if (check_that == 4 || check_that == 5)
					{
						for (int t = 0; t != size; ++t)
							if (that_4P[t] == 0)
							{
								that_4P[t] = j * 100 + i; // ����λ��
								that_4_size++;
								break;
							}
					}
					// ȡ������ص��������ӵ� // ע�⣺size * 2��
					if (check_that == 2 || check_that == 3)
					{
						for (int t = 0; t != size * 2; ++t)
							if (that_3P[t] == 0)
							{
								that_3P[t] = j * 100 + i; // ����λ��
								that_3_size++;
								break;
							}
					}
				}

				// �ָ�
				new_Cell(i, j, xx, -1);
			}
		}

	// ��������˫�ġ����������� // ����������
	if (profit > 40 || profit == 8) return profitP;
	// ������������Ԥ�� // ע�⣺rt��Ӧ��Ѳο�ֵ��ad��Ӧ��ѵ�ַ
	int this_4_max_rt = 0, this_4_ad = 0;
	if (processes <= complex && this_4_size > 0)
		this_4_ad = good_bns(this_4_first, this_4_size, xx, step, &this_4_max_rt, NULL, true);
	if (this_4_max_rt >= 800) return this_4_ad;

	// ���Է�������
	if (that_8_size > 1)
	{
		if (processes <= complex) return good_bns(that_8_first, that_8_size, xx, step, &danger, &danger, false);
		else return good_ex(that_8_first, that_8_size, xx, step);
	}
	// ���Է���˫�ġ����������� // Χ�²�����
	if (danger > 40 || danger == 8) return dangerP;
	// �Է����Ĳ���Ԥ�� // ע�⣺rt��Ӧ��Ѳο�ֵ��ad��Ӧ��ѵ�ַ
	int that_4_max_rt = 0, that_4_min_rt = 0, that_4_ad = 0;
	if (processes <= complex && that_4_size > 0)
		that_4_ad = good_bns(that_4_first, that_4_size, xx, step, &that_4_max_rt, &that_4_min_rt, false);
	if (that_4_max_rt >= 800 && that_4_min_rt < 800) return that_4_ad;

	// ��������˫�� // ����������
	if (profit > 20) return profitP;
	// ����������Ԥ�� // ע�⣺rt��Ӧ��Ѳο�ֵ��ad��Ӧ��ѵ�ַ
	int this_3_max_rt = 0, this_3_ad = 0;
	if (processes <= complex && this_3_size > 0)
		this_3_ad = good_bns(this_3_first, this_3_size, xx, step, &this_3_max_rt, NULL, true);
	if (this_3_max_rt >= 800) return this_3_ad;

	// ���Է���˫�� // Χ�²�����
	if (danger > 20) return dangerP;
	// �Է�������Ԥ�� // ע�⣺rt��Ӧ��Ѳο�ֵ��ad��Ӧ��ѵ�ַ
	int that_3_max_rt = 0, that_3_min_rt = 0, that_3_ad = 0;
	if (processes <= complex && that_3_size > 0)
		that_3_ad = good_bns(that_3_first, that_3_size, xx, step, &that_3_max_rt, &that_3_min_rt, false);
	if (that_3_max_rt >= 800 && that_3_min_rt < 800) return that_3_ad;

	/*
	// ˫����ֵ��
	for (int t = 0; t != this_4_size; ++t)
	{
		for (int s = 0; s != that_4_size; ++s)
			if (this_4P[t] == that_4P[s]) return this_4P[t];
		for (int s = 0; s != that_3_size; ++s)
			if (this_4P[t] == that_3P[s]) return this_4P[t];
	}
	for (int t = 0; t != this_3_size; ++t)
	{
		for (int s = 0; s != that_4_size; ++s)
			if (this_3P[t] == that_4P[s]) return this_3P[t];
		for (int s = 0; s != that_3_size; ++s)
			if (this_3P[t] == that_3P[s]) return this_3P[t];
	}
	*/

	// �������Ӻ�ļ���
	int profit_twice = 0, profit_ji = 0;
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= m; ++j)
		{
			if (*(*xx + i * mm + j) < 0) // �������뱣֤���Ը�Ϊ��
			{
				// �伺��ɫ��
				new_Cell(i, j, xx, (step + 1) % 2 + 1);

				int result_once = check_Cell_1(i, j, xx);
				int result_twice = check_Cell_2(i, j, xx, (step + 1) % 2 + 1);

				// ȡ���������������ߵ����ӵ� // ���Դ�Buff�Ľ���Buff�ӳ�
				if ((result_twice > 2000 || result_twice < 400)
					&& judgment_simplified(i, j, result_once) != 1) // ��������
				{
					// �����������˫�����һ��Buff�ӳɻ���
					if (result_twice > 2000) result_twice += result_once * 10000;
					if (result_twice > profit_twice)
					{
						profit_twice = result_twice;
						profit_ji = j * 100 + i;
					}
				}

				// �ָ�
				new_Cell(i, j, xx, -1);
			}
		}

	// �ҷ�������˫
	if (profit_twice > 2000) return profit_ji;

	if (processes <= complex)
	{
		// �������Ӻ󼺷���в�����֮��
		if (this_4_size > 0 || this_3_size > 0)
		{
			if (this_4_max_rt > this_3_max_rt) return this_4_ad;
			else return this_3_ad;
		}

		// �������Ӻ�Է���в�����֮��
		if (that_4_size > 0 && that_3_size > 0)
		{
			if (that_4_min_rt < that_3_min_rt) return that_4_ad;
			else return that_3_ad;
		}
		else if (that_4_size > 0) return that_4_ad;
		else if (that_3_size > 0) return that_3_ad;
		else
			;
	}
	else
	{
		if (this_4_size > 0) return good_ex(this_4_first, this_4_size, xx, step);
		if (this_3_size > 0) return good_ex(this_3_first, this_3_size, xx, step);

		if (profit_twice > 303) return profit_ji;

		if (that_4_size > 0) return good_ex(that_4_first, that_4_size, xx, step);
		if (that_3_size > 0) return good_ex(that_3_first, that_3_size, xx, step);
	}

	// �ҷ��������ֵ
	if (profit_twice > 0) return profit_ji;

	if (profit > 0) return profitP; // ����������
	if (danger > 0) return dangerP; // Χ�²�����

	// ������ģ�����

	// ���������������������
	do
	{
		// srand((unsigned)time(NULL));
		rand_i = rand() % m + 1;
		rand_j = rand() % m + 1;
	} while (a[rand_i][rand_j] >= 0);
	return rand_j * 100 + rand_i;
}

int main()
{
	// ��ʼ��б�����
	for (int ir = 0; ir <= 2 * m - 10; ++ir)
		for (int jr = 0; jr <= m + 1; ++jr)
		{
			ar[ir][jr] = al[ir][jr] = 3; // Ĭ�Ͼ�Ϊ����
		}
	
	// ��ʼ������
	for (int i = 0; i <= m + 1; ++i)
		for (int j = 0; j <= m + 1; ++j)
		{
			// ��ȦΪ3��ʾ����������Ϊ����ʾΪ��
			if (i == 0 || i == m + 1 || j == 0 || j == m + 1) a[i][j] = 3;
			else
			{
				a[i][j] = -1;
				renew_Cell(i, j, aa); // ��һ�θ��¸�������
			}
		}

	// ��ʼ����ʷ��¼
	for (int t = 0; t != m * m; ++t) player_i[t] = player_j[t] = 0;

	// ���ѡ����ӻ����
	int choice = 0;
	do 
	{
		system("cls");
		printf("Do you want to be white(1) or black(2) ? Enter your choice: ");
		scanf("%d", &choice);
	}
	while (choice != 1 && choice != 2);

	int AI_result = 0;
	int step = 0; // ͳ�����µĲ���

	// ˢ����Ļ
	system("color fc");
	system("cls");
	print_Chess(player_i[step], player_j[step], step);

	// /* ������

	while (1)
	{
		// ���������
		// ����һ�����������ѡ��ɫ�ӣ�����һ���Ǽ�������ӡ�
		if (step % 2 + 1 == choice)
		{
			AI_result = AI(aa, step); // ִ�м�������ӳ���
			processes--; // �ָ��ϼ��ݹ����

			player_i[step] = AI_result % 100;
			player_j[step] = AI_result / 100;

			// ����Ϊ������ӣ�����Ϊż����ӡ� // ��ȫ����ֿ�д
			new_Cell(player_i[step], player_j[step], aa, (step + 1) % 2 + 1);
			step++;

			// Previous Version:
			// ++step! �ȼӺ����Ŷ
			// new_Cell(player_i, player_j, aa, ++step % 2 + 1);

			if (judgment(player_i[step - 1], player_j[step - 1], step) > 0) break;
		}
		// �������
		else
		{
		input:scanf("%d%d", &player_i[step], &player_j[step]); // ����
			if (player_i[step] == 0 && player_j[step] == 0) break; // (0,0)��ʾ����
			else if (player_i[step] >= 1 && player_i[step] <= m && player_j[step] >= 1 && player_j[step] <= m) // �ж��Ƿ�����������
			{
				if (a[player_i[step]][player_j[step]] < 0) // ������ӵ�Ϊ��
				{
					// ����Ϊ������ӣ�����Ϊż����ӡ� // ��ȫ����ֿ�д
					new_Cell(player_i[step], player_j[step], aa, (step + 1) % 2 + 1);
					step++;

					if (judgment(player_i[step - 1], player_j[step - 1], step) > 0) break;

					// ����ģ��
					/*
					int debug = 0; scanf("%d", &debug);
					if (debug == 0) break;
					else if (debug == 1 || debug == 2)
					{
						step += debug % 2;
						goto input;
					}
					else
						;
					// */
				}
				else goto input; // �������ӵ㲻Ϊ�ղ�������������
			}
			else goto input; // �������ӵ�Խ�粢������������
		}
	}

	/*
	// AI to AI!
	int judge = 0;

	while (time_total < 100)
	{
		AI_result = AI(aa, step); // ִ�м�������ӳ���
		processes--; // �ָ��ϼ��ݹ����

		player_i[step] = AI_result % 100;
		player_j[step] = AI_result / 100;

		// ����Ϊ������ӣ�����Ϊż����ӡ� // ��ȫ����ֿ�д
		new_Cell(player_i[step], player_j[step], aa, (step + 1) % 2 + 1);
		step++;

		judge = judgment(player_i[step - 1], player_j[step - 1], step);
		if (judge > 0)
		{
			time_total++;
			if (judge == 3)
			{
				time_black += 0.5;
				time_white += 0.5;
			}
			else time_black++;
			goto start;
		}
		system("pause");

		AI_result = AI(aa, step); // ִ�м�������ӳ���
		processes--; // �ָ��ϼ��ݹ����

		player_i[step] = AI_result % 100;
		player_j[step] = AI_result / 100;

		// ����Ϊ������ӣ�����Ϊż����ӡ� // ��ȫ����ֿ�д
		new_Cell(player_i[step], player_j[step], aa, (step + 1) % 2 + 1);
		step++;

		judge = judgment(player_i[step - 1], player_j[step - 1], step);
		if (judge > 0)
		{
			time_total++;
			if (judge == 3)
			{
				time_black += 0.5;
				time_white += 0.5;
			}
			else time_white++;
			goto start;
		}
		system("pause");
	}
	// */

	system("pause");
	return 0;
}
