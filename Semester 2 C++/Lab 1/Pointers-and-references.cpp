#include <iostream>
#include "functions.h"
using namespace std;

int main() {
	double a = 2.3, b = 4.55;
	floorr(a);
	cout << a << '\n';
	floorr(&b);
	cout << b << '\n' << '\n';

	a = 3.4568;
	int c = 5;
	invertion(a);
	cout << a << '\n';
	invertion(c);
	cout << c << '\n';
	
	a = 3.4568;
	c = 5;
	invertion(&a);
	cout << a << '\n';
	invertion(&c);
	cout << c << '\n' << '\n';

	double x = 0, y = 0, r = 1;
	Circle circle(x, y, r);
	circle.print();

	double x1 = 2, y1 = 3;
	move(circle, x1, y1);
	circle.print();
	move(&circle, &x1, &y1);
	circle.print();

	Matrix matr;

	double alf = 2.5;
	matr.print();
	multipl(matr, alf);
	matr.print();
	multipl(&matr, &alf);
	matr.print();
	return 0;
}
