#include "Header.h"

/* Part.8 用户输入模块 ************************************************** */

#define MAXGETLINE 5
#define SKIPSPACE s = str; while ((c = getchar()) <= 32); *s++ = c

// 史上最完美的限制字符数getline()函数
int mygetline(char *str, int size)
{
	char c;
	char *SKIPSPACE;
	while ((c = getchar()) != '\n')
	{
		if (s < str + size - 1) *s++ = c; // 由于字符数组大小为size（含'\0'），实际只能填充len - 1个字符
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

// 判断字符是否符合要求. 空白返回0，数字返回1，A-O字母返回2，a-o字母返回3，其他返回-1
int isLegalCharacter(char c)
{
	if (c <= ' ') return 0;
	else if (c >= '0' && c <= '9') return 1;
	else if (c >= 'A' && c <= 'O') return 2;
	else if (c >= 'a' && c <= 'o') return 3;
	else return -1;
}

// 解析用户输入
int positionInputAnalysis()
{
	char str[MAXGETLINE];
	char *s;
	int i, j;
	while (1) {
		mygetline(str, MAXGETLINE);
		s = str; i = j = 0; // 初始化
		if (*s == '-' && *(s + 1) == 'q') // 输入-q以退出
		{
			return 0;
		}

		// /* 测试模块
#ifdef TEST
		else if (*s == '+' && *(s + 1) == 's' && *(s + 2) == 'w') // 输入+sw以强行落白子
		{
			return 1;
		}
		else if (*s == '+' && *(s + 1) == 's' && *(s + 2) == 'b') // 输入+sb以强行落黑子
		{
			return 2;
		}
		else if (*s == '-' && *(s + 1) == 's') // 输入-s以结束强制阶段
		{
			return 3;
		}
#endif
		// */

		else if (*s == '-' && *(s + 1) == 'z') // 输入-z以悔棋
		{
			return 9;
		}
		else if (isLegalCharacter(*s) == 1) // 如果为数字
		{
			i = *s - '0'; // 记录该数字
			if (isLegalCharacter(*(s + 1)) == 1) // 如果下一位仍是数字
				i = i * 10 + (*++s - '0'); // 指向下一位，将其加到个位上
			i = SIDELENGTH + 1 - i; // 倒置
			while (isLegalCharacter(*++s) == 0); // 跳过空白字符：先自增，后调用，再判断
			if (isLegalCharacter(*s) >= 2) // 如果为字母
			{
				j = *s - ((isLegalCharacter(*s) == 2) ? 'A' : 'a') + 1; // 字母转化为数字
				if (i >= 1 && i <= SIDELENGTH && a[i][j] == 0) // 如果该格行标正确且该格为空
					return i * 100 + j; // 返回坐标值
			}
		}
		else if (isLegalCharacter(*s) >= 2) // 如果为字母
		{
			j = *s - ((isLegalCharacter(*s) == 2) ? 'A' : 'a') + 1; // 字母转化为数字
			while (isLegalCharacter(*++s) == 0); // 跳过空白字符：先自增，后调用，再判断
			if (isLegalCharacter(*s) == 1) // 如果为数字
			{
				i = *s - '0'; // 记录该数字
				if (isLegalCharacter(*(s + 1)) == 1) // 如果下一位仍是数字
				{
					i = i * 10 + (*++s - '0'); // 指向下一位，将其加到个位上
					i = SIDELENGTH + 1 - i; // 倒置
					if (i >= 1 && i <= SIDELENGTH && a[i][j] == 0) // 如果该格行标正确且该格为空
						return i * 100 + j; // 返回坐标值
				}
				else if (isLegalCharacter(*(s + 1)) == 0) // 如果下一位为空
				{
					i = SIDELENGTH + 1 - i; // 倒置
					if (i >= 1 && i <= SIDELENGTH && a[i][j] == 0) // 如果该格行标正确且该格为空
						return i * 100 + j; // 返回坐标值
				}
				else
					; // 其他情况结束if
			}
		}
		else
			;
		printf("ERROR: ILLEGAL INPUT! PLEASE TRY AGAIN:\n");
	}
}

// 仅允许输入1/2的模式选择
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
