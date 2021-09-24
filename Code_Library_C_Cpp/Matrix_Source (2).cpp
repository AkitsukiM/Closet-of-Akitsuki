#include<iostream>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int _x(int exp)
{
	if (exp % 2 == 0) return 1;
	if (exp % 2 == 1) return -1;
}

vector< vector<double> > _delete(vector< vector<double> > matrix_original, vector<double>::size_type i)
{
	vector< vector<double> > matrix(matrix_original);
	matrix.erase(matrix.begin());
	for (vector< vector<double> >::iterator lineiter = matrix.begin(); lineiter != matrix.end(); ++lineiter)
	{
		(*lineiter).erase((*lineiter).begin() + i);
	}
	return matrix;
}

double calc_matrix(vector< vector<double> > matrix)
{
	if (matrix.size() == 1) return *(*matrix.begin()).begin();
	double S = 0;
	vector<double>::size_type n = (*matrix.begin()).size();
	for (vector<double>::size_type i = 0; i != n; ++i)
	{
		S = S + _x(i)*calc_matrix(_delete(matrix, i));
	}
	return S;
}

void _calc(int n)
{
	vector<double> line(n, 0);
	vector< vector<double> > Matrix_II(n, line);

	cout << "Please input the number:" << endl;
	for (vector< vector<double> >::iterator lineiter = Matrix_II.begin(); lineiter != Matrix_II.end(); ++lineiter)
	{
		for (vector<double>::iterator coliter = (*lineiter).begin(); coliter != (*lineiter).end(); ++coliter)
		{
			cin >> *coliter;
		}
	}

	cout << "Det = " << calc_matrix(Matrix_II) << endl;
}

int main()
{
	cout << "Calculating the Det of a matrix!\n[Version 2.0]\n";
	char judge('y');
	while (judge == 'y')
	{
		cout << endl;
		int n = 1;
		cout << "Please input the dimension:" << endl;
		cin >> n;
		if (n == 0)
		{
			cout << "Det = 1\n\nOne more? Enter y for Yes or n for No\n";
			cin >> judge;
			if (judge != 'y')
				return 0;
			else
				continue;
		}
		else
			_calc(n);
		cout << "\nOne more? Enter y for Yes or n for No\n";
		cin >> judge;
		if (judge != 'y')
			return 0;
		else
			cout << "\n========================================\n";
	}
}
