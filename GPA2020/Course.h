#ifndef COURSE_H
#define COURSE_H

#include "Header.h"

class course
{
public:

	friend ostream &operator << (ostream &, const course &); // ������������
	friend course operator + (const course &, const course &); // ���ؼӷ������ // ֻ��ѧ���뼨���

	double gpa() // ƽ��ֵ(GPA)����ӿ�
	{
		if (courseCredit == 0) // �����ĸΪ0�����
			return 0;
		else
			return GPCredit / courseCredit;
	}

	/* ���캯�� */
	course(string CodeAndName, double Credit, int Performance) :
		courseCodeAndName(CodeAndName), courseCredit(Credit), coursePerformance(Performance)
	{
		GP = exchange(Performance);
		GPCredit = GP * Credit;
	}
	course() : course("", 0, 0) {}
	course(string CodeAndName) : course(CodeAndName, 0, 0) {}

	/* �������� */
	~course() {}

private:
	string courseCodeAndName; // �γ̱����γ�����
	double courseCredit; // ѧ��
	int coursePerformance; // �ɼ�
	double GP; // ���� // ע�⣺������Ϊ������
	double GPCredit; // ����� // ע�⣺������Ϊ�������
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
	if (cos1.GPCredit >= 0) // ����Ϊ�����ƣ���ʱΪ�Ǹ�����֣�
	{
		cos0.courseCredit += cos1.courseCredit; // ����ѧ��
		cos0.GPCredit += cos1.GPCredit; // ���ϼ����
	}
	if (cos2.GPCredit >= 0) // ����Ϊ�����ƣ���ʱΪ�Ǹ�����֣�
	{
		cos0.courseCredit += cos2.courseCredit; // ����ѧ��
		cos0.GPCredit += cos2.GPCredit; // ���ϼ����
	}
	return cos0;
}

#endif // !COURSE_H
