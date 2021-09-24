#include "Header.h"

// ��������һȦ��Ϊ������
int a[SIDELENGTHEX][SIDELENGTHEX];
// ת�þ�������б��������б����
int at[SIDELENGTHEX][SIDELENGTHEX], ar[SIDELENGTHXXXX][SIDELENGTHEX], al[SIDELENGTHXXXX][SIDELENGTHEX];

// ��ʷ��¼
int playeri[CELLTOTAL + 1], playerj[CELLTOTAL + 1];

/* ��������ֻ�������õ���һЩ��������ͷ�ļ����� ************************************************** */

void initializeAllMatrices(); // ��ʼ������
int judgment(int i, int j, int step); // ����ʤ��ƽ���жϣ����ӡ���̣�
int positionInputAnalysis(); // �����û�����
int SelectionInputAnalysis(char *s); // ����������1/2��ģʽѡ��
int AI(int step); // ��������ӳ���. �������µĲ���.
extern double DefvsAtk; // ͨ�������в����޸�DefvsAtk��ֵ

/* Part.9 ������ ************************************************** */

// ��ս������
void Personvs(int choice)
{
	printChessboard(0, 0);
	int step = 0, position = 0, chance = 0, color = 0;
	while (1)
	{
		if (step % 2 + 1 == choice && chance == 0) position = AI(step); // Attention Please!
		else position = positionInputAnalysis(); // AI(step);
		if (position == 0) // ����0���˳�
		{
			break;
		}

		// /* ����ģ��
#ifdef TEST
		else if (position == 1) // ����1��ǿ�������
		{
			chance = 2;
			color = 1;
		}
		else if (position == 2) // ����2��ǿ�������
		{
			chance = 2;
			color = 2;
		}
		else if (position == 3) // ����3�����ǿ�ƽ׶Σ�����AI����
		{
			if (chance != 2) printf("ERROR: TEST IS NOT RUNNING!\n"); // ��������ǿ�ƽ׶�ʱ-s�Ƿ�
			else
			{
				chance = 0;
				color = 0;
				if (step % 2 + 1 != choice) step++;
			}
		}
#endif
		// */

		else if (position == 9) // ����9�����
		{
			if (step > 0) // ��������Ϊ��ʱ�ſɻ���
			{
				putColoredPiece(playeri[step], playerj[step], 0); // ������
				playeri[step] = 0; // ��¼���
				playerj[step] = 0;
				step--; // ��������
				if (chance == 0) chance = 1;

				CLEARSCREEN; // �����Ļ
				printChessboard(playeri[step], playerj[step]); // ��ӡ����
				printf("\nBACKWARD SUCCESSFUL!\n\n");
			}
			else
			{
				printf("ERROR: BACKWARD FORBIDDEN!\n");
			}
		}
		else
		{
			if (chance == 1) chance = 0;
			step++; // ����ǰ��
			playeri[step] = position / 100;
			playerj[step] = position % 100; // ��¼д��
			putColoredPiece(playeri[step], playerj[step], (chance == 2) ? color : step % 2 + 1); // ���ӷ���
			if (judgment(playeri[step], playerj[step], step)) break; // �ж�
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc == 2 && atof(argv[1]) >= 0.0) DefvsAtk = atof(argv[1]);
	initializeAllMatrices();

	printf(VERSIONINFO);
	int choice = SelectionInputAnalysis("Select a mode:\nPerson vs Person (1)\nPerson vs Artificial Ignorance (2)\n");
	if (choice == 1) Personvs(0);
	else Personvs(SelectionInputAnalysis("Do you want to be white(1) or black(2) ? Enter your choice:\n"));

	SYSTEMPAUSE;
	return 0;
}
