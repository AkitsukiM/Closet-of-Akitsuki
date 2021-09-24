#ifndef COURSE_H
#define COURSE_H

#include "Header.h"

class course
{
public:

	friend ostream &operator << (ostream &, const course &); // 重载输出运算符
	friend course operator + (const course &, const course &); // 重载加法运算符 // 只加学分与绩点分

	double gpa() // 平均值(GPA)计算接口
	{
		if (courseCredit == 0) // 避免分母为0的情况
			return 0;
		else
			return GPCredit / courseCredit;
	}

	/* 构造函数 */
	course(string CodeAndName, double Credit, int Performance) :
		courseCodeAndName(CodeAndName), courseCredit(Credit), coursePerformance(Performance)
	{
		GP = exchange(Performance);
		GPCredit = GP * Credit;
	}
	course() : course("", 0, 0) {}
	course(string CodeAndName) : course(CodeAndName, 0, 0) {}

	/* 析构函数 */
	~course() {}

private:
	string courseCodeAndName; // 课程编号与课程名称
	double courseCredit; // 学分
	int coursePerformance; // 成绩
	double GP; // 绩点 // 注意：两级制为负绩点
	double GPCredit; // 绩点分 // 注意：两级制为负绩点分
};

inline ostream &operator << (ostream &os, const course &cos)
{
	os << cos.courseCodeAndName << endl
		<< "Course Credit: " << cos.courseCredit << endl
		<< "Course Performance: " << cos.coursePerformance << endl
		<< "Grade Point: " << cos.GP << endl;
	return os;
}

inline course operator + (const course &cos1, const course &cos2)
{
	course cos0;
	if (cos1.GPCredit >= 0) // 若不为两级制（此时为非负绩点分）
	{
		cos0.courseCredit += cos1.courseCredit; // 加上学分
		cos0.GPCredit += cos1.GPCredit; // 加上绩点分
	}
	if (cos2.GPCredit >= 0) // 若不为两级制（此时为非负绩点分）
	{
		cos0.courseCredit += cos2.courseCredit; // 加上学分
		cos0.GPCredit += cos2.GPCredit; // 加上绩点分
	}
	return cos0;
}

#endif // !COURSE_H
