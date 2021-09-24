#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#define MAXSTORAGE 100
#define SYSTEMPAUSE system("pause")

// 操作序列
char operatorStorage[MAXSTORAGE]; // '0':int | '1':double | '(' | ')' | '*' | '/' | '%' | '+' | '-'
int intStorage[MAXSTORAGE];
double doubleStorage[MAXSTORAGE];
// 操作序列指示器
char *operatorStorageIterator;
int *intIterator;
double *doubleIterator;
// 指示器初始化函数
void initializeIterator()
{
	operatorStorageIterator = operatorStorage;
	intIterator = intStorage;
	doubleIterator = doubleStorage;
}

// 空白字符判断函数
int myisspace(char c)
{
	if (c <= ' ') return 1;
	else return 0;
}

// 数字字符判断函数
int myisdigital(char c)
{
	if (c >= '0' && c <= '9') return 1;
	else return 0;
}

// 字符串转化成整型数据
int arrayToint(char a[])
{
	int i = 0, sign = 1, result = 0;
	for (; myisspace(a[i]); i++); // 跳过空白字符
	if (a[i] == '-' || a[i] == '+') sign = (a[i++] == '-') ? -1 : 1; // 读取符号
	for (; myisdigital(a[i]); i++) result = result * 10 + (a[i] - '0'); // 读取数字
	return sign * result;
}

// 字符串转换成双精度浮点型数据
double arrayTodouble(char a[])
{
	int i = 0, result = 0, power = 1;
	double sign = 1.0;
	for (; myisspace(a[i]); i++); // 跳过空白字符
	if (a[i] == '-' || a[i] == '+') sign = (a[i++] == '-') ? -1.0 : 1.0; // 读取符号
	for (; myisdigital(a[i]); i++) result = result * 10 + (a[i] - '0'); // 读取数字
	if (a[i] == '.') i++;
	for (; myisdigital(a[i]); i++)
	{
		result = result * 10 + (a[i] - '0'); // 读取数字
		power *= 10;
	}
	return sign * result / power;
}

// 读入一行字符作为算术表达式
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

// 分离算术表达式
void sperateExpression(char arithmeticExpression[])
{
	// 数字字符暂存数组
	char DigitalStorage[MAXSTORAGE];
	// i指向算术表达式，j指向暂存数组，haspoint指示是否含小数点，useDigitalStorage指示是否需要使用暂存数组
	int i = 0, j = 0, haspoint = 0, useDigitalStorage = 0;
	while (arithmeticExpression[i] != '\0')
	{
		// 读入数字字符
		while (myisdigital(arithmeticExpression[i]) || arithmeticExpression[i] == '.')
		{
			// 指示使用暂存数组
			useDigitalStorage = 1;
			// 存入暂存数组
			DigitalStorage[j++] = arithmeticExpression[i++];
			// 指示含有小数点
			if (arithmeticExpression[i] == '.') haspoint = 1;
		}
		// 若含有数字特征
		if (useDigitalStorage == 1)
		{
			// 添加结束符
			DigitalStorage[j] = '\0';
			// 对应转存
			if (haspoint == 0)
			{
				// 对应int
				*(operatorStorageIterator++) = '0';
				*(intIterator++) = arrayToint(DigitalStorage);
			}
			else
			{
				// 对应double
				*(operatorStorageIterator++) = '1';
				*(doubleIterator++) = arrayTodouble(DigitalStorage);
			}
			// 初始化
			j = 0;
			haspoint = 0;
			useDigitalStorage = 0;
		}
		else if (arithmeticExpression[i] == '-')
		{
			// 若'-'在行首，记为负号
			if (i == 0)
			{
				DigitalStorage[j++] = '-';
			}
			// 若'-'前不是数字或后括号，记为负号
			else if (*(operatorStorageIterator - 1) != '0' && *(operatorStorageIterator - 1) != '1' 
				&& *(operatorStorageIterator - 1) != ')')
			{
				DigitalStorage[j++] = '-';
			}
			// 其他情况记为减号
			else
			{
				*(operatorStorageIterator++) = '-';
			}
			// 指向下一位
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
	// 添加结束符
	*operatorStorageIterator = '\0';
}

// 解析为逆波兰表达式 (Reverse Polish Notation)
int arithmeticExpressionToRPN()
{
	// 操作符栈与栈顶指针
	char operatorStack[MAXSTORAGE] = { '(' };
	char *operatorStackIterator = operatorStack;
	int operatingNumberCount = 0;

	for (; *operatorStorageIterator != '\0'; operatorStorageIterator++)
	{
		// 若为数字，弹出，操作数加1
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
		// 若为'('，操作符压栈，操作数置为0
		else if (*operatorStorageIterator == '(')
		{
			*(++operatorStackIterator) = *operatorStorageIterator;
			operatingNumberCount = 0;
		}
		// 若为')'，弹出操作符直至遇到'('，操作数置为1
		else if (*operatorStorageIterator == ')')
		{
			// 弹出操作符直至遇到'('
			for (; *operatorStackIterator != '('; operatorStackIterator--)
			{
				printf("%c ", *operatorStackIterator);
			}
			// 栈顶指针指向'('前一位
			operatorStackIterator--;
			operatingNumberCount = 1;
		}
		// 若为'*''/''%'
		else if (*operatorStorageIterator == '*' || *operatorStorageIterator == '/' || *operatorStorageIterator == '%')
		{
			// 如果操作数为1，操作符压栈
			if (operatingNumberCount == 1)
			{
				*(++operatorStackIterator) = *operatorStorageIterator;
			}
			// 如果操作数为2
			else if (operatingNumberCount == 2)
			{
				// 如果栈顶为'+''-'，操作符压栈
				if (*operatorStackIterator == '+' || *operatorStackIterator == '-')
				{
					*(++operatorStackIterator) = *operatorStorageIterator;
				}
				// 如果栈顶为'*''/''%'
				else
				{
					// 弹出栈顶
					printf("%c ", *operatorStackIterator);
					// 操作符压栈
					*operatorStackIterator = *operatorStorageIterator;
				}
				// 操作数置为1
				operatingNumberCount = 1;
			}
			// 如果操作数为其它，报错
			else
			{
				printf("\nError: Ambiguous operator!\n");
				SYSTEMPAUSE;
				return -1;
			}
		}
		// 若为'+''-'
		else if (*operatorStorageIterator == '+' || *operatorStorageIterator == '-')
		{
			// 如果操作数为1，操作符压栈
			if (operatingNumberCount == 1)
			{
				*(++operatorStackIterator) = *operatorStorageIterator;
			}
			// 如果操作数为2
			else if (operatingNumberCount == 2)
			{
				// 弹出操作符直至遇到'('
				for (; *operatorStackIterator != '('; operatorStackIterator--)
				{
					printf("%c ", *operatorStackIterator);
				}
				// 操作符压栈
				*(++operatorStackIterator) = *operatorStorageIterator;
				// 操作数置为1
				operatingNumberCount = 1;
			}
			// 如果操作数为其它，报错
			else
			{
				printf("\nError: Ambiguous operator!\n");
				SYSTEMPAUSE;
				return -1;
			}
		}
		// 注：如果新的操作符优先级较低，则先弹出优先级较高的操作符再压栈；否则直接压栈
		// 其他情况报错
		else
		{
			printf("\nError: Ambiguous operator!\n");
			SYSTEMPAUSE;
			return -1;
		}
	}

	// 弹出操作符直至遇到'('
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
	// 2: 为了存储必要的'\n'与'\0'
	char arithmeticExpression[MAXSTORAGE + 2];
	// 读入算术表达式
	mygetline(arithmeticExpression);
	// 初始化指示器
	initializeIterator();
	// 分离算术表达式
	sperateExpression(arithmeticExpression);
	// 重新初始化指示器
	initializeIterator();
	// 解析为逆波兰表达式
	return arithmeticExpressionToRPN();
}
