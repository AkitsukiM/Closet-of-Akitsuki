#include <iostream>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;

const long double pi = 3.1415926535897932384626433832795028841971;
const long num = 36000;
const long double delta = pi * 2 / num;

int main()
{
	long double R, h_0, eta, lambda, v, time = 0.0, add;
	long double h[36000];
	cout << "The radius of the orbit is equal to R. R =" << endl;
	cin >> R;
	cout << "The initial snow depth is h[0]. h[0] =" << endl;
	cin >> h_0;
	cout << "The product of the speed of the truck and the snow depth is a given. Enter the given:" << endl;
	cin >> eta;
	cout << "The falling speed of the snow is a given. Enter the given:" << endl;
	cin >> lambda;
	for (int i = 0; i != num; ++i)
		h[i] = h_0;

	long counter = 0;
	cout << endl;
	while(1)
	{
		if (counter == num) counter = 0;
		cout << "t = " << time << endl;
		cout << "\tthe degree of angle: " << (double)counter * 360.0 / num << "\tx = " << R * cos(delta * counter)
			<< "\ty = " << R * sin(delta * counter) << endl;
		v = eta / h[counter];
		cout << "\tv = " << v << endl;
		time += delta * R * h[counter] / eta;
		add = delta * R * h[counter] * lambda / eta;
		h[counter] = 0.0;
		for (int i = 0; i != num; ++i)
			h[i] += add;
		counter += 1;
	}
	return 0;
}
