#include "Header.h"

/* Part.8 �û�����ģ�� ************************************************** */

#define MAXGETLINE 5
#define SKIPSPACE s = str; while ((c = getchar()) <= 32); *s++ = c

// ʷ���������������ַ���getline()����
int mygetline(char *str, int size)
{
	char c;
	char *SKIPSPACE;
	while ((c = getchar()) != '\n')
	{
		if (s < str + size - 1) *s++ = c; // �����ַ������СΪsize����'\0'����ʵ��ֻ�����len - 1���ַ�
		else
		{
			printf("ERROR: TOO MANY CHARACTERS! INPUT AGAIN:\n");
			while ((c = getchar()) != '\n');
			SKIPSPACE;
		}
	}
	*s = '\0';
	return s - str;
}

// �ж��ַ��Ƿ����Ҫ��. �հ׷���0�����ַ���1��A-O��ĸ����2��a-o��ĸ����3����������-1
int isLegalCharacter(char c)
{
	if (c <= ' ') return 0;
	else if (c >= '0' && c <= '9') return 1;
	else if (c >= 'A' && c <= 'O') return 2;
	else if (c >= 'a' && c <= 'o') return 3;
	else return -1;
}

// �����û�����
int positionInputAnalysis()
{
	char str[MAXGETLINE];
	char *s;
	int i, j;
	while (1) {
		mygetline(str, MAXGETLINE);
		s = str; i = j = 0; // ��ʼ��
		if (*s == '-' && *(s + 1) == 'q') // ����-q���˳�
		{
			return 0;
		}

		// /* ����ģ��
#ifdef TEST
		else if (*s == '+' && *(s + 1) == 's' && *(s + 2) == 'w') // ����+sw��ǿ�������
		{
			return 1;
		}
		else if (*s == '+' && *(s + 1) == 's' && *(s + 2) == 'b') // ����+sb��ǿ�������
		{
			return 2;
		}
		else if (*s == '-' && *(s + 1) == 's') // ����-s�Խ���ǿ�ƽ׶�
		{
			return 3;
		}
#endif
		// */

		else if (*s == '-' && *(s + 1) == 'z') // ����-z�Ի���
		{
			return 9;
		}
		else if (isLegalCharacter(*s) == 1) // ���Ϊ����
		{
			i = *s - '0'; // ��¼������
			if (isLegalCharacter(*(s + 1)) == 1) // �����һλ��������
				i = i * 10 + (*++s - '0'); // ָ����һλ������ӵ���λ��
			i = SIDELENGTH + 1 - i; // ����
			while (isLegalCharacter(*++s) == 0); // �����հ��ַ���������������ã����ж�
			if (isLegalCharacter(*s) >= 2) // ���Ϊ��ĸ
			{
				j = *s - ((isLegalCharacter(*s) == 2) ? 'A' : 'a') + 1; // ��ĸת��Ϊ����
				if (i >= 1 && i <= SIDELENGTH && a[i][j] == 0) // ����ø��б���ȷ�Ҹø�Ϊ��
					return i * 100 + j; // ��������ֵ
			}
		}
		else if (isLegalCharacter(*s) >= 2) // ���Ϊ��ĸ
		{
			j = *s - ((isLegalCharacter(*s) == 2) ? 'A' : 'a') + 1; // ��ĸת��Ϊ����
			while (isLegalCharacter(*++s) == 0); // �����հ��ַ���������������ã����ж�
			if (isLegalCharacter(*s) == 1) // ���Ϊ����
			{
				i = *s - '0'; // ��¼������
				if (isLegalCharacter(*(s + 1)) == 1) // �����һλ��������
				{
					i = i * 10 + (*++s - '0'); // ָ����һλ������ӵ���λ��
					i = SIDELENGTH + 1 - i; // ����
					if (i >= 1 && i <= SIDELENGTH && a[i][j] == 0) // ����ø��б���ȷ�Ҹø�Ϊ��
						return i * 100 + j; // ��������ֵ
				}
				else if (isLegalCharacter(*(s + 1)) == 0) // �����һλΪ��
				{
					i = SIDELENGTH + 1 - i; // ����
					if (i >= 1 && i <= SIDELENGTH && a[i][j] == 0) // ����ø��б���ȷ�Ҹø�Ϊ��
						return i * 100 + j; // ��������ֵ
				}
				else
					; // �����������if
			}
		}
		else
			;
		printf("ERROR: ILLEGAL INPUT! PLEASE TRY AGAIN:\n");
	}
}

// ����������1/2��ģʽѡ��
int SelectionInputAnalysis(char *s)
{
	printf("%s", s);
	char modeSelection[2];
	while (1)
	{
		mygetline(modeSelection, 2);
		if (*modeSelection == '1') return 1;
		else if (*modeSelection == '2') return 2;
		else printf("ERROR: ILLEGAL INPUT! PLEASE TRY AGAIN:\n");
	}
}
