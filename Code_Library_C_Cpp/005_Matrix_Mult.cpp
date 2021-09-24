#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

using num = int;

int main()
{
	num m(0), s(0), n(0);
	cout << "Matrix A: m x s; Matrix B: s x n. Please enter the number: m, s, n." << endl;
	cin >> m >> s >> n;
	vector<num> line_A(s, 0), line_B(n, 0), line_AB(n, 0);
	vector< vector<num> > Matrix_A(m, line_A), Matrix_B(s, line_B), Matrix_AB(m, line_AB);
	cout << "Please input the matrix A:" << endl;
	for (vector< vector<num> >::iterator iter_r = Matrix_A.begin(); iter_r != Matrix_A.end(); ++iter_r)
		for (vector<num>::iterator iter_c = (*iter_r).begin(); iter_c != (*iter_r).end(); ++iter_c)
			cin >> *iter_c;
	cout << "Please input the matrix B:" << endl;
	for (vector< vector<num> >::iterator iter_r = Matrix_B.begin(); iter_r != Matrix_B.end(); ++iter_r)
		for (vector<num>::iterator iter_c = (*iter_r).begin(); iter_c != (*iter_r).end(); ++iter_c)
			cin >> *iter_c;
	cout << endl << "A x B = " << endl;
	for (vector< vector<num> >::size_type i = 0; i != m; ++i)
		for (vector<num>::size_type j = 0; j != n; ++j)
			for (auto k = 0; k != s; ++k)
				(Matrix_AB[i])[j] = (Matrix_A[i])[k] * (Matrix_B[k])[j] + (Matrix_AB[i])[j];
	for (vector< vector<num> >::iterator iter_r = Matrix_AB.begin(); iter_r != Matrix_AB.end(); ++iter_r)
	{
		for (vector<num>::iterator iter_c = (*iter_r).begin(); iter_c != (*iter_r).end(); ++iter_c)
			cout << *iter_c << " ";
		cout << endl;
	}
	getchar(); getchar();
	return 0;
}
