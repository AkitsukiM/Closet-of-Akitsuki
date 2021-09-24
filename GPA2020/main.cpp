#include "Header.h"

extern vector<course> courses;
int readInformation();

int main()
{
	if (!readInformation())
	{
		course sumcourse;
		for (vector<course>::iterator iter = courses.begin(); iter != courses.end(); ++iter)
			sumcourse = sumcourse + *iter;
		cout << sumcourse.gpa() << endl;
	}

	THEEND;
}
