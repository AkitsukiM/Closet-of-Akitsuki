#include<iostream>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main()
{
	cout << "Calculating the Det of a matrix!" << endl;
	char judge('y');
	while (judge = 'y')
	{
		cout << endl;
		typedef double in;
		int n = 1;
		cout << "Please input the dimension:" << endl;
		cin >> n;
		vector<in> line(n, 0);
		vector< vector<in> > matrix(n, line);

		cout << "Please input the number:" << endl;
		for (vector< vector<in> >::iterator lineiter = matrix.begin(); lineiter != matrix.end(); ++lineiter)
		{
			for (vector<in>::iterator coliter = (*lineiter).begin(); coliter != (*lineiter).end(); ++coliter)
			{
				cin >> *coliter;
			}
		}

		vector<double> line_to_mult(n, 1);
		vector< vector<double> > matrix_to_mult(n, line_to_mult);
		vector< vector<double> >::iterator lineiter_mult = matrix_to_mult.begin();
		int exp(0), y(0);

		for (vector< vector<in> >::iterator lineiter_1 = matrix.begin(); lineiter_1 != matrix.end(); ++lineiter_1)
		{
			for (vector< vector<in> >::iterator lineiter_2 = lineiter_1 + 1; lineiter_2 != matrix.end(); ++lineiter_2)
			{
				vector<in>::iterator iter_1 = (*lineiter_1).begin() + y;
				vector<in>::iterator iter_2 = (*lineiter_2).begin() + y;
				vector<double>::iterator iter_mult = (*lineiter_mult).begin();
				if (*iter_1 == 0)
				{
					vector<in> temp(*lineiter_1);
					*lineiter_1 = *lineiter_2;
					*lineiter_2 = temp;
					exp += 1;
					iter_mult += 1;
					continue;
				}
				if (*iter_2 == 0)
				{
					iter_mult += 1;
					continue;
				}
				double k = -(*iter_2) / (*iter_1);
				(*iter_mult) = k;
				iter_mult += 1;
				vector<in>::iterator iter_to_plus_1 = (*lineiter_1).begin();
				for (vector<in>::iterator iter_to_plus_2 = (*lineiter_2).begin(); iter_to_plus_2 != (*lineiter_2).end(); ++iter_to_plus_2)
				{
					(*iter_to_plus_2) = (*iter_to_plus_1) + (*iter_to_plus_2) / k;
					++iter_to_plus_1;
				}
			}
			lineiter_mult += 1;
			y += 1;
		}

		double S(1);
		for (int i = 0; i != n; ++i)
		{
			S = S*(*((*(matrix.begin() + i)).begin() + i));
		}
		for (vector< vector<double> >::iterator lineiter = matrix_to_mult.begin(); lineiter != matrix_to_mult.end(); ++lineiter)
		{
			for (vector<double>::iterator coliter = (*lineiter).begin(); coliter != (*lineiter).end(); ++coliter)
			{
				S = S*(*coliter);
			}
		}
		for (int i = 0; i != exp; ++i)
			S = -S;
		cout << "Det = " << S << "\n\nOne more? Yes(y) or No(n)" << endl;
		cin >> judge;
		if (judge != 'y') return 0;
	}
}
