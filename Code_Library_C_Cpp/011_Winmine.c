#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Cell
{
	int is; // �Ƿ����� (0����/1����)
	int number; // ��Χ����
	int sign; // ��� (0δ���/1���ױ��/2���ʱ��/3�Ѵ�)
};

struct Cell a[18][32]; // a[line + 2][column + 2]
struct Cell a_copy[18][32];
const int line = 16, column = 30, mine = 99; // ����/����/������

int previous = 0, next = 0; // ��ʱ���ڶ�o_o�ĵ��ô������м���
int success = 1; // ��ִ֤���ж�

int count_mine, count_opened, count_progress; // ����

void print_num(int num)
{
	if (num == 0) printf("  ");
	else if (num == 1) printf("%c%c", 0xa2, 0xd9);
	else if (num == 2) printf("%c%c", 0xa2, 0xda);
	else if (num == 3) printf("%c%c", 0xa2, 0xdb);
	else if (num == 4) printf("%c%c", 0xa2, 0xdc);
	else if (num == 5) printf("%c%c", 0xa2, 0xdd);
	else if (num == 6) printf("%c%c", 0xa2, 0xde);
	else if (num == 7) printf("%c%c", 0xa2, 0xdf);
	else if (num == 8) printf("%c%c", 0xa2, 0xe0);
	else printf("%c%c", 0xa2, 0xe1);
}

// ���������Դ�δ��Ǹ�
void o_o(struct Cell *pointer, int x, int y, int click)
{
	if (x > 0 && x <= line && y > 0 && y <= column) // �����޶���Χ
	{
		if (click == 0) // �������
		{
			struct Cell *temp;
			if ((*(pointer + x * (column + 2) + y)).sign == 3)
			{
				int count = 0;
				for (int s = -1; s <= 1; ++s)
					for (int t = -1; t <= 1; ++t)
					{
						temp = pointer + (x + s)*(column + 2) + y + t;
						if ((*temp).sign == 1) count++;
					}
				// ����Ѵ�����Χ���������ܱߵ��ױ����ʱ���ܱ�δ��Ǹ�
				if ((*(pointer + x * (column + 2) + y)).number == count)
				{
					for (int s = -1; s <= 1; ++s)
						for (int t = -1; t <= 1; ++t)
						{
							temp = pointer + (x + s)*(column + 2) + y + t;
							if ((*temp).sign == 0) o_o(pointer, x + s, y + t, 0);
						}
				}
			}
			if ((*(pointer + x * (column + 2) + y)).sign == 0)
			{
				(*(pointer + x * (column + 2) + y)).sign = 3; // ���δ������
				if ((*(pointer + x * (column + 2) + y)).number == 0) // ����򿪺�Ϊ����������ܱ�δ��Ǹ�
				{
					for (int s = -1; s <= 1; ++s)
						for (int t = -1; t <= 1; ++t)
						{
							temp = pointer + (x + s)*(column + 2) + y + t;
							if ((*temp).sign == 0) o_o(pointer, x + s, y + t, 0);
						}
				}
			}
		}
		else // �Ҽ�����
		{
			if ((*(pointer + x * (column + 2) + y)).sign < 3)
				(*(pointer + x * (column + 2) + y)).sign
				= ((*(pointer + x * (column + 2) + y)).sign + 1) % 3;
		}
		next++;
	}
}

void autoplay(struct Cell *pointer)
{
	int mine_count, unsigned_count, number_temp;
	struct Cell *temp;
	for (int i = 1; i <= line; ++i)
		for (int j = 1; j <= column; ++j)
		{
			// ��ȡ�ܱߵ�����
			number_temp = (*(pointer + i * (column + 2) + j)).number;
			mine_count = unsigned_count = 0;

			// ����Ѵ����ܱߵ�������Ϊ��(����ʾ���ָ�)��ִ�в���
			if ((*(pointer + i * (column + 2) + j)).sign == 3 && number_temp != 0)
			{
				// �������ױ����/����δ�����
				for (int s = -1; s <= 1; ++s)
					for (int t = -1; t <= 1; ++t)
					{
						temp = pointer + (i + s)*(column + 2) + j + t;
						if ((*temp).sign == 1) mine_count++;
						if ((*temp).sign == 0) unsigned_count++;
					}

				// �����ָ������ȥ���ױ�����������Ҳ�����δ���������ܱ߰˸�����δ��Ǹ�
				if (number_temp - mine_count == 0 && unsigned_count != 0) o_o(pointer, i, j, 0);

				// �����ָ������ȥ���ױ��������δ���������ܱ߰˸�����δ��Ǹ���е��ױ��
				if (number_temp - mine_count == unsigned_count)
				{
					for (int s = -1; s <= 1; ++s)
						for (int t = -1; t <= 1; ++t)
						{
							temp = pointer + (i + s)*(column + 2) + j + t;
							if ((*temp).sign == 0) o_o(pointer, i + s, j + t, 1);
						}
				}
			}
		}
}

void logic(struct Cell *pointer, struct Cell *pointer_copy)
{
	// pass���Ƿ�Ϊ�������(0��/1��). 
	int pass, mine_count, unsigned_count, number_temp;
	struct Cell *temp;

	// ������ͼ
	for (int i = 1; i <= line; ++i)
		for (int j = 1; j <= column; ++j)
		{
			// ��ʼ��pass
			pass = 0;
			// ��a[i][j]δ���
			if ((*(pointer + i * (column + 2) + j)).sign == 0)
			{
				// ��a[i][j]�ܱ����Ѵ򿪵ĸ�����a[i][j]Ϊ�������
				for (int s = -1; s <= 1; ++s)
					for (int t = -1; t <= 1; ++t)
						if ((*(pointer + (i + s)*(column + 2) + j + t)).sign == 3
							&& (*(pointer + (i + s)*(column + 2) + j + t)).number != 0) pass = 1;
			}

			// ��a[i][j]Ϊ�������
			if (pass == 1)
			{
				// ��֤�ж�(0��֤ʧ��/1��֤�ɹ�)
				int disproof = 0;
				if (disproof == 0)
				{
					// a_copyΪa��һ������
					for (int ii = 0; ii <= line + 1; ++ii)
						for (int jj = 0; jj <= column + 1; ++jj)
						{
							(*(pointer_copy + ii * (column + 2) + jj)).number
								= (*(pointer + ii * (column + 2) + jj)).number;
							(*(pointer_copy + ii * (column + 2) + jj)).sign
								= (*(pointer + ii * (column + 2) + jj)).sign;
						}

					// ���迼�����Ϊ����
					(*(pointer_copy + i * (column + 2) + j)).sign = 1;
					// �ͽ��߼�����
					autoplay(pointer_copy);
					// �߼�������֤
					// ������ͼ
					for (int ii = 1; ii <= line; ++ii)
						for (int jj = 1; jj <= column; ++jj)
						{
							// ��a[ii][jj]�Ѵ�
							if ((*(pointer + ii * (column + 2) + jj)).sign == 3)
							{
								// ��ȡa[ii][jj]�ܱߵ�����
								number_temp = (*(pointer + ii * (column + 2) + jj)).number;
								mine_count = unsigned_count = 0;
								// ��a_copy[ii][jj]�������ױ����/����δ�����
								for (int s = -1; s <= 1; ++s)
									for (int t = -1; t <= 1; ++t)
									{
										temp = pointer_copy + (ii + s)*(column + 2) + jj + t;
										if ((*temp).sign == 1) mine_count++;
										if ((*temp).sign == 0) unsigned_count++;
									}
								// ���ܱ߶��Ѵ򿪻��ǵ�(������)���ױ����������(ԭ����)�ܱߵ�����
								if (unsigned_count == 0 && mine_count != number_temp)
								{
									// ì�ܣ��ʿ��������Դ�
									o_o(pointer, i, j, 0);
									// ��֤�ɹ�
									disproof = success = 1;
								}
							}
						}
				}
				// ����֤���ɹ�
				if (disproof == 0)
				{
					// ��������
					for (int ii = 0; ii <= line + 1; ++ii)
						for (int jj = 0; jj <= column + 1; ++jj)
						{
							(*(pointer_copy + ii * (column + 2) + jj)).number
								= (*(pointer + ii * (column + 2) + jj)).number;
							(*(pointer_copy + ii * (column + 2) + jj)).sign
								= (*(pointer + ii * (column + 2) + jj)).sign;
						}

					// ���迼�����Ϊ����
					(*(pointer_copy + i * (column + 2) + j)).sign = 3;
					// �ͽ��߼�����
					autoplay(pointer_copy);
					// ������ͼ
					for (int ii = 1; ii <= line; ++ii)
						for (int jj = 1; jj <= column; ++jj)
						{
							// ��a[ii][jj]�Ѵ�
							if ((*(pointer + ii * (column + 2) + jj)).sign == 3)
							{
								// ��ȡa[ii][jj]�ܱߵ�����
								number_temp = (*(pointer + ii * (column + 2) + jj)).number;
								mine_count = unsigned_count = 0;
								// ��a_copy[ii][jj]�������ױ����/����δ�����
								for (int s = -1; s <= 1; ++s)
									for (int t = -1; t <= 1; ++t)
									{
										temp = pointer_copy + (ii + s)*(column + 2) + jj + t;
										if ((*temp).sign == 1) mine_count++;
										if ((*temp).sign == 0) unsigned_count++;
									}
								// ���ܱ߶��Ѵ򿪻��ǵ�(������)���ױ����������(ԭ����)�ܱߵ�����
								if (unsigned_count == 0 && number_temp != mine_count)
								{
									// ì�ܣ��ʿ������Ϊ����
									(*(pointer + i * (column + 2) + j)).sign = 1;
									// ��֤�ɹ�
									disproof = success = 1;
								}
							}
						}
				}
			}
		}
}

void result_print()
{
	// system("pause");
	// ���ȼ���
	count_mine = count_opened = 0;
	for (int ii = 1; ii <= line; ++ii)
		for (int jj = 1; jj <= column; ++jj)
		{
			if (a[ii][jj].sign == 1) count_mine++; // ���׼���
			if (a[ii][jj].sign == 3) count_opened++; // �Ѵ򿪸����
		}
	count_progress = (count_mine + count_opened) * 100 / (line * column);

	// �������������ʾ
	system("cls");
	// װ��
	printf("Progress: %d%c\tMines: %d / %d\n\n", count_progress, '%', count_mine, mine);
	for (int jj = 0; jj < column; ++jj) printf("==");
	printf("\n\n");
	// ����
	for (int ii = 1; ii <= line; ++ii)
	{
		for (int jj = 1; jj <= column; ++jj)
		{
			if (a[ii][jj].sign == 3) print_num(a[ii][jj].number); // ��ʾ����
			else if (a[ii][jj].sign == 2) printf("%c%c", 0xa3, 0xbf); // ��ʾ�ʺ�
			else if (a[ii][jj].sign == 1) printf("%c%c", 0xa1, 0xf1); // ��ʾ����
			else printf("%c%c", 0xa8, 0x80); // ����ԭװ
		}
		printf("\n");
	}
	// װ��
	printf("\n");
	for (int jj = 0; jj < column; ++jj) printf("==");
	printf("\n\n");
}

int main()
{
	// ��״̬��ʼ��
	for (int i = 0; i <= line + 1; ++i)
		for (int j = 0; j <= column + 1; ++j)
			a[i][j].sign = 0;

	// ����������Ϊ�Ѵ�
	for (int i = 0; i <= line + 1; ++i) a[i][0].sign = a[i][column + 1].sign = 3;
	for (int j = 1; j <= column; ++j) a[0][j].sign = a[line + 1][j].sign = 3;

	// δ�򿪵ĵ�ͼ���
	for (int i = 0; i < line; ++i)
	{
		for (int j = 0; j < column; ++j)
			printf("%c%c", 0xa8, 0x80);
		printf("\n");
	}

	// Ͷ�ŵ���
	int position = 0, x = 0, y = 0, xx = 0, yy = 0, is_click = 0;

	// When autoplay, this line is unnecessary.
	// scanf("%d%d%d", &xx, &yy, &is_click); // ������/��/0���1�Ҽ�

	srand((unsigned)time(NULL));

	// For autoplay
	// ע����������ְ취. һ�������и������. һ�����������ת��������.
	xx = rand() % line + 1;
	yy = rand() % column + 1;

	do
	{
		// ����״̬��ʼ��
		for (int i = 0; i <= line + 1; ++i)
			for (int j = 0; j <= column + 1; ++j)
				a[i][j].is = a[i][j].number = 0;

		// Ͷ�ŵ���
		for (int i = 1; i <= mine; ++i)
		{
			position = rand() % (line * column);
			y = position % column + 1;
			x = (position - y) / column + 1;
			if (a[x][y].is == 1)
			{
				i -= 1;
				continue;
			} // ��������������Ͷ��
			else
				a[x][y].is = 1;
		}

		// ������׼���
		for (int s = -1; s <= 1; ++s)
			for (int t = -1; t <= 1; ++t)
				if (a[xx + s][yy + t].is == 1) a[xx][yy].number++;
	} while (a[xx][yy].number != 0); // ��������Ϊ�������õ�ͼ

									 // ���׼���
	for (int i = 1; i <= line; ++i)
		for (int j = 1; j <= column; ++j)
			for (int s = -1; s <= 1; ++s)
				for (int t = -1; t <= 1; ++t)
					if (a[i + s][j + t].is == 1) a[i][j].number++;

	struct Cell *first = &a[0][0];
	struct Cell *first_copy = &a_copy[0][0];

	while (1)
	{
		// �û�����
		// ��Autoplay״̬�������û�����
		// o_o(first, xx, yy, is_click);

		// �Զ�����
		// �ڵͽ���߽��߼������ʧЧʱ���㿪�����
		while (a[xx][yy].sign != 0) // ��һ�Σ�û�д��κθ��ӹ�sign����Ϊ0
		{
			xx = rand() % line + 1;
			yy = rand() % column + 1;
		}
		o_o(first, xx, yy, is_click);

		// ʧ�ܵ��ж�
		for (int s = -1; s <= 1; ++s)
			for (int t = -1; t <= 1; ++t)
			{
				if (a[xx + s][yy + t].sign == 3 && a[xx + s][yy + t].is == 1)
				{
					system("cls");
					// װ��
					printf("Progress: %d%c\tMines: %d / %d\n\n", count_progress, '%', count_mine, mine);
					for (int jj = 0; jj < column; ++jj) printf("==");
					printf("\n\n");
					// ����
					for (int ii = 1; ii <= line; ++ii)
					{
						for (int jj = 1; jj <= column; ++jj)
						{
							if (ii == xx + s && jj == yy + t)
								printf("%c%c", 0xa8, 0x92); // �㿪���״���ʾȦ��
							else if (a[ii][jj].sign == 3)
								print_num(a[ii][jj].number); // ��ȷ�㿪����ʾ����
							else if ((a[ii][jj].sign == 1 || a[ii][jj].sign == 2) && a[ii][jj].is == 1)
								printf("%c%c", 0xa1, 0xf1); // �����ȷ��ʾ����
							else if ((a[ii][jj].sign == 1 || a[ii][jj].sign == 2) && a[ii][jj].is == 0)
								printf("%c%c", 0xa1, 0xc1); // ��Ǵ�����ʾ��
							else if (a[ii][jj].is == 1)
								printf("%c%c", 0xa8, 0x91); // δ���δ�򿪵�����ʾȦ��
							else
								printf("%c%c", 0xa8, 0x80); // ����ԭװ
						}
						printf("\n");
					}
					// װ��
					printf("\n");
					for (int jj = 0; jj < column; ++jj) printf("==");
					printf("\n\n");

					printf("You lose. Error:  %d  %d\n", xx, yy);
					getchar(); // getchar();
					return 0; // ��Ϸʧ��
				}
			}

		// ��ѭ���ͽ��߼�����/��ѭ���߽��߼�����
		while (success != 0) // success�ĳ�ʼֵΪ1������ѭ��
		{
			while (previous != next) // ������o_o������û���ص���previous��next��Ȼ���ȣ�����ѭ��
			{
				previous = next;
				autoplay(first); // ���޷��������еͽ��߼�����ʱprevious == next����ʱ�˳�ѭ��
			}
			success = 0;
			logic(first, first_copy); // ���޷��������и߽��߼�����ʱsuccess��ֵ����ı䣺��ʱ�˳�ѭ��
		}

		// ����previous/next/success
		previous = next;
		success = 1;

		result_print(); // ������

		// ʤ�����ж�
		if (count_opened == line * column - mine)
		{
			printf("You win.\n");
			break; // ��Ϸʤ��
		}

		// ��Autoplay״̬�������û�����
		// scanf("%d%d%d", &xx, &yy, &is_click); // ��������
	}

	getchar(); // getchar();
	return 0;
}
