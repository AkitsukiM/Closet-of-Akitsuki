/*
* ���������
* CC 2019 (Version 1.9.1.4)
* Copyright (c) 2018-2019 �����ħ������^. All rights reserved.
*
* Date modified: 2019/01/11
* Update Info:
* 0. ���ļ���ʽ��д
* 1. �޸���һЩ�����ж��ϵ�©��. �����˺�ը��ģ��.
*    x1 �޸��˻������γ���ʱ���ܳ��ֵı���©��.
*    x2 ͨ�������в�������DEF/ATK����. ����˰汾��Ϣ��ʾ.
*    x3 �Ժ�ը��ģ��Ľӿڽ����˵���������.
*    x4 �޸���һ����������ӽ���λ��©��.
*/

#ifndef _HEADER_H
#define _HEADER_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/* Part.1 ����ȫ�ֱ��� ************************************************** */

#define VERSIONINFO "\
* A Game of Sorrow in the Season of White Album\n\
* CC 2019 (Version 1.9.1.4)\n\
* Copyright (c) 2018-2019 Yu Hongtian. All rights reserved.\n\
\n"

// SIDELENGTH �߳� 15
#define SIDELENGTH 15
// SIDELENGTHEX ��չ�߳� SIDELENGTH + 2 = 17
#define SIDELENGTHEX 17
// SIDELENGTHXX б��߳� SIDELENGTH * 2 - 9 = 21
#define SIDELENGTHXXXX 21
// CELLTOTAL SIDELENGTH * SIDELENGTH = 225
#define CELLTOTAL 225
// CENTERPOINT ���ĵ� SIDELENGTH / 2 + 1 = 8
#define CENTERPOINT 8
// MINUSINFINITY ������� -2147483647
#define MINUSINFINITY -2147483647
// Differences between Windows-VisualStudio & Linux-gcc
#ifndef LINUX
#define _CRT_SECURE_NO_WARNINGS
#define CLEARSCREEN system("cls")
#define SYSTEMPAUSE system("pause")
#define TEST
#else
#define CLEARSCREEN system("clear")
#define SYSTEMPAUSE
#endif
// Ȩ��֮�ƣ����ո�
#ifndef DELSPACE
#define SPACE printf(" ")
#else
#define SPACE
#endif

// ��������һȦ��Ϊ������
extern int a[SIDELENGTHEX][SIDELENGTHEX];
// ת�þ�������б��������б����
extern int at[SIDELENGTHEX][SIDELENGTHEX], ar[SIDELENGTHXXXX][SIDELENGTHEX], al[SIDELENGTHXXXX][SIDELENGTHEX];

// ��ʷ��¼
extern int playeri[CELLTOTAL + 1], playerj[CELLTOTAL + 1];

/* Part.2 ���̴�ӡģ�� ************************************************** */

void printChessboard(int i, int j); // ��ӡ����. �������һ����λ�úͲ���

/* Part.3 �������ģ�� ************************************************** */

void putColoredPiece(int i, int j, int color); // �������ӳ���

/* Part.4 ����״�����ģ�� ************************************************** */

// ���������ֺ궨��

// ����
#define QQQQQQ 2
// ����
#define QQQQQ 1
// ����
#define IVTOKENI 9
// ������
#define IVTOKENII 8
// ��һʽ�����������������
#define IVTOKENIII 7
// ��һʽ��
#define IVQQQAQ 6
// ����ʽ��
#define IVQQAQQ 5
// ����
#define IIIQQQ 4
// ��һʽ��
#define IIIQQAQ 3

// �ĵ��Ͻ����½�
#define IVSUP 9
#define IVINF 5
#define IIISUP 4
#define IIIINF 3

int check_Cell_1(int i, int j); // ���ض��񣨽��뺯��ǰ�����ӣ���һ������״�����

/* Part.5 ����ʤ��ƽ���ж�ģ�� ************************************************** */

int judgmentSimplified(int i, int j, int check_result); // ���ֵļ��ж�. �����򷵻�0. �Ϸ��򷵻�1.

/* Part.6 Person vs A.I. ��ģ�飨�����߼���飩 ************************************************** */

#define MAXPOINTS 64
#define BOMBERLAYER 8

/* Part.7 Person vs Artificial Ignorance ĸģ�� ************************************************** */

/* Part.8 �û�����ģ�� ************************************************** */

/* Part.9 ������ ************************************************** */


#endif // !_HEADER_H
