/*
* 五子棋程序
* CC 2019 (Version 1.9.1.4)
* Copyright (c) 2018-2019 ヴワル魔法図書館. All rights reserved.
*
* Date modified: 2019/01/11
* Update Info:
* 0. 多文件方式编写
* 1. 修复了一些棋形判断上的漏洞. 完善了轰炸机模块.
*    x1 修复了活四棋形出现时可能出现的崩溃漏洞.
*    x2 通过命令行参数调节DEF/ATK比例. 添加了版本信息显示.
*    x3 对轰炸机模块的接口进行了调节与整合.
*    x4 修复了一个计算机落子禁手位的漏洞.
*/

#ifndef _HEADER_H
#define _HEADER_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/* Part.1 宏与全局变量 ************************************************** */

#define VERSIONINFO "\
* A Game of Sorrow in the Season of White Album\n\
* CC 2019 (Version 1.9.1.4)\n\
* Copyright (c) 2018-2019 Yu Hongtian. All rights reserved.\n\
\n"

// SIDELENGTH 边长 15
#define SIDELENGTH 15
// SIDELENGTHEX 拓展边长 SIDELENGTH + 2 = 17
#define SIDELENGTHEX 17
// SIDELENGTHXX 斜向边长 SIDELENGTH * 2 - 9 = 21
#define SIDELENGTHXXXX 21
// CELLTOTAL SIDELENGTH * SIDELENGTH = 225
#define CELLTOTAL 225
// CENTERPOINT 中心点 SIDELENGTH / 2 + 1 = 8
#define CENTERPOINT 8
// MINUSINFINITY 负无穷大 -2147483647
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
// 权宜之计：补空格
#ifndef DELSPACE
#define SPACE printf(" ")
#else
#define SPACE
#endif

// 棋盘虚延一圈作为主矩阵
extern int a[SIDELENGTHEX][SIDELENGTHEX];
// 转置矩阵，右下斜矩阵，左下斜矩阵
extern int at[SIDELENGTHEX][SIDELENGTHEX], ar[SIDELENGTHXXXX][SIDELENGTHEX], al[SIDELENGTHXXXX][SIDELENGTHEX];

// 历史记录
extern int playeri[CELLTOTAL + 1], playerj[CELLTOTAL + 1];

/* Part.2 棋盘打印模块 ************************************************** */

void printChessboard(int i, int j); // 打印棋盘. 输入最近一步的位置和步数

/* Part.3 矩阵操作模块 ************************************************** */

void putColoredPiece(int i, int j, int color); // 代理落子程序

/* Part.4 连子状况检查模块 ************************************************** */

// 单棋形评分宏定义

// 长连
#define QQQQQQ 2
// 五连
#define QQQQQ 1
// 四连
#define IVTOKENI 9
// 半四连
#define IVTOKENII 8
// 二一式三除四连外的衍生物
#define IVTOKENIII 7
// 三一式四
#define IVQQQAQ 6
// 二二式四
#define IVQQAQQ 5
// 三连
#define IIIQQQ 4
// 二一式三
#define IIIQQAQ 3

// 四的上界与下界
#define IVSUP 9
#define IVINF 5
#define IIISUP 4
#define IIIINF 3

int check_Cell_1(int i, int j); // 对特定格（进入函数前已落子）的一层连子状况检查

/* Part.5 禁手胜手平手判断模块 ************************************************** */

int judgmentSimplified(int i, int j, int check_result); // 禁手的简单判断. 禁手则返回0. 合法则返回1.

/* Part.6 Person vs A.I. 子模块（检查与高级检查） ************************************************** */

#define MAXPOINTS 64
#define BOMBERLAYER 8

/* Part.7 Person vs Artificial Ignorance 母模块 ************************************************** */

/* Part.8 用户输入模块 ************************************************** */

/* Part.9 主函数 ************************************************** */


#endif // !_HEADER_H
