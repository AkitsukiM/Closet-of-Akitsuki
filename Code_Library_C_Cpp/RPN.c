#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#define MAXSTORAGE 100
#define SYSTEMPAUSE system("pause")

// ��������
char operatorStorage[MAXSTORAGE]; // '0':int | '1':double | '(' | ')' | '*' | '/' | '%' | '+' | '-'
int intStorage[MAXSTORAGE];
double doubleStorage[MAXSTORAGE];
// ��������ָʾ��
char *operatorStorageIterator;
int *intIterator;
double *doubleIterator;
// ָʾ����ʼ������
void initializeIterator()
{
	operatorStorageIterator = operatorStorage;
	intIterator = intStorage;
	doubleIterator = doubleStorage;
}

// �հ��ַ��жϺ���
int myisspace(char c)
{
	if (c <= ' ') return 1;
	else return 0;
}

// �����ַ��жϺ���
int myisdigital(char c)
{
	if (c >= '0' && c <= '9') return 1;
	else return 0;
}

// �ַ���ת������������
int arrayToint(char a[])
{
	int i = 0, sign = 1, result = 0;
	for (; myisspace(a[i]); i++); // �����հ��ַ�
	if (a[i] == '-' || a[i] == '+') sign = (a[i++] == '-') ? -1 : 1; // ��ȡ����
	for (; myisdigital(a[i]); i++) result = result * 10 + (a[i] - '0'); // ��ȡ����
	return sign * result;
}

// �ַ���ת����˫���ȸ���������
double arrayTodouble(char a[])
{
	int i = 0, result = 0, power = 1;
	double sign = 1.0;
	for (; myisspace(a[i]); i++); // �����հ��ַ�
	if (a[i] == '-' || a[i] == '+') sign = (a[i++] == '-') ? -1.0 : 1.0; // ��ȡ����
	for (; myisdigital(a[i]); i++) result = result * 10 + (a[i] - '0'); // ��ȡ����
	if (a[i] == '.') i++;
	for (; myisdigital(a[i]); i++)
	{
		result = result * 10 + (a[i] - '0'); // ��ȡ����
		power *= 10;
	}
	return sign * result / power;
}

// ����һ���ַ���Ϊ�������ʽ
void mygetline(char arithmeticExpression[])
{
	int i = 0;
	char temp = getchar();
	while (i < MAXSTORAGE && temp != EOF && temp != '\n')
	{
		arithmeticExpression[i++] = temp;
		temp = getchar();
	}
	if (temp == '\n') arithmeticExpression[i++] = '\n';
	arithmeticExpression[i] = '\0';
}

// �����������ʽ
void sperateExpression(char arithmeticExpression[])
{
	// �����ַ��ݴ�����
	char DigitalStorage[MAXSTORAGE];
	// iָ���������ʽ��jָ���ݴ����飬haspointָʾ�Ƿ�С���㣬useDigitalStorageָʾ�Ƿ���Ҫʹ���ݴ�����
	int i = 0, j = 0, haspoint = 0, useDigitalStorage = 0;
	while (arithmeticExpression[i] != '\0')
	{
		// ���������ַ�
		while (myisdigital(arithmeticExpression[i]) || arithmeticExpression[i] == '.')
		{
			// ָʾʹ���ݴ�����
			useDigitalStorage = 1;
			// �����ݴ�����
			DigitalStorage[j++] = arithmeticExpression[i++];
			// ָʾ����С����
			if (arithmeticExpression[i] == '.') haspoint = 1;
		}
		// ��������������
		if (useDigitalStorage == 1)
		{
			// ��ӽ�����
			DigitalStorage[j] = '\0';
			// ��Ӧת��
			if (haspoint == 0)
			{
				// ��Ӧint
				*(operatorStorageIterator++) = '0';
				*(intIterator++) = arrayToint(DigitalStorage);
			}
			else
			{
				// ��Ӧdouble
				*(operatorStorageIterator++) = '1';
				*(doubleIterator++) = arrayTodouble(DigitalStorage);
			}
			// ��ʼ��
			j = 0;
			haspoint = 0;
			useDigitalStorage = 0;
		}
		else if (arithmeticExpression[i] == '-')
		{
			// ��'-'�����ף���Ϊ����
			if (i == 0)
			{
				DigitalStorage[j++] = '-';
			}
			// ��'-'ǰ�������ֻ�����ţ���Ϊ����
			else if (*(operatorStorageIterator - 1) != '0' && *(operatorStorageIterator - 1) != '1' 
				&& *(operatorStorageIterator - 1) != ')')
			{
				DigitalStorage[j++] = '-';
			}
			// ���������Ϊ����
			else
			{
				*(operatorStorageIterator++) = '-';
			}
			// ָ����һλ
			i++;
		}
		else if (arithmeticExpression[i] == '(' || arithmeticExpression[i] == ')'
			|| arithmeticExpression[i] == '*' || arithmeticExpression[i] == '/' || arithmeticExpression[i] == '%' 
			|| arithmeticExpression[i] == '+')
		{
			*(operatorStorageIterator++) = arithmeticExpression[i++];
		}
		else
		{
			i++;
		}
	}
	// ��ӽ�����
	*operatorStorageIterator = '\0';
}

// ����Ϊ�沨�����ʽ (Reverse Polish Notation)
int arithmeticExpressionToRPN()
{
	// ������ջ��ջ��ָ��
	char operatorStack[MAXSTORAGE] = { '(' };
	char *operatorStackIterator = operatorStack;
	int operatingNumberCount = 0;

	for (; *operatorStorageIterator != '\0'; operatorStorageIterator++)
	{
		// ��Ϊ���֣���������������1
		if (*operatorStorageIterator == '0')
		{
			printf("%d ", *(intIterator++));
			operatingNumberCount++;
		}
		else if (*operatorStorageIterator == '1')
		{
			printf("%lf ", *(doubleIterator++));
			operatingNumberCount++;
		}
		// ��Ϊ'('��������ѹջ����������Ϊ0
		else if (*operatorStorageIterator == '(')
		{
			*(++operatorStackIterator) = *operatorStorageIterator;
			operatingNumberCount = 0;
		}
		// ��Ϊ')'������������ֱ������'('����������Ϊ1
		else if (*operatorStorageIterator == ')')
		{
			// ����������ֱ������'('
			for (; *operatorStackIterator != '('; operatorStackIterator--)
			{
				printf("%c ", *operatorStackIterator);
			}
			// ջ��ָ��ָ��'('ǰһλ
			operatorStackIterator--;
			operatingNumberCount = 1;
		}
		// ��Ϊ'*''/''%'
		else if (*operatorStorageIterator == '*' || *operatorStorageIterator == '/' || *operatorStorageIterator == '%')
		{
			// ���������Ϊ1��������ѹջ
			if (operatingNumberCount == 1)
			{
				*(++operatorStackIterator) = *operatorStorageIterator;
			}
			// ���������Ϊ2
			else if (operatingNumberCount == 2)
			{
				// ���ջ��Ϊ'+''-'��������ѹջ
				if (*operatorStackIterator == '+' || *operatorStackIterator == '-')
				{
					*(++operatorStackIterator) = *operatorStorageIterator;
				}
				// ���ջ��Ϊ'*''/''%'
				else
				{
					// ����ջ��
					printf("%c ", *operatorStackIterator);
					// ������ѹջ
					*operatorStackIterator = *operatorStorageIterator;
				}
				// ��������Ϊ1
				operatingNumberCount = 1;
			}
			// ���������Ϊ����������
			else
			{
				printf("\nError: Ambiguous operator!\n");
				SYSTEMPAUSE;
				return -1;
			}
		}
		// ��Ϊ'+''-'
		else if (*operatorStorageIterator == '+' || *operatorStorageIterator == '-')
		{
			// ���������Ϊ1��������ѹջ
			if (operatingNumberCount == 1)
			{
				*(++operatorStackIterator) = *operatorStorageIterator;
			}
			// ���������Ϊ2
			else if (operatingNumberCount == 2)
			{
				// ����������ֱ������'('
				for (; *operatorStackIterator != '('; operatorStackIterator--)
				{
					printf("%c ", *operatorStackIterator);
				}
				// ������ѹջ
				*(++operatorStackIterator) = *operatorStorageIterator;
				// ��������Ϊ1
				operatingNumberCount = 1;
			}
			// ���������Ϊ����������
			else
			{
				printf("\nError: Ambiguous operator!\n");
				SYSTEMPAUSE;
				return -1;
			}
		}
		// ע������µĲ��������ȼ��ϵͣ����ȵ������ȼ��ϸߵĲ�������ѹջ������ֱ��ѹջ
		// �����������
		else
		{
			printf("\nError: Ambiguous operator!\n");
			SYSTEMPAUSE;
			return -1;
		}
	}

	// ����������ֱ������'('
	for (; *operatorStackIterator != '('; operatorStackIterator--)
	{
		printf("%c ", *operatorStackIterator);
	}
	printf("\nWORKING DONE!\n");
	SYSTEMPAUSE;
	return 0;
}

int main()
{
	// 2: Ϊ�˴洢��Ҫ��'\n'��'\0'
	char arithmeticExpression[MAXSTORAGE + 2];
	// �����������ʽ
	mygetline(arithmeticExpression);
	// ��ʼ��ָʾ��
	initializeIterator();
	// �����������ʽ
	sperateExpression(arithmeticExpression);
	// ���³�ʼ��ָʾ��
	initializeIterator();
	// ����Ϊ�沨�����ʽ
	return arithmeticExpressionToRPN();
}
