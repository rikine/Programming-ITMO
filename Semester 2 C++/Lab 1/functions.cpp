#include "functions.h"

void floorr(double *x)
{
	*x = int(*x);
}

void floorr(double &x)
{
	x = int(x);
}

void invertion(double *x)
{
	*x = -(*x);
}

void invertion(double &x)
{
	x = -x;
}

void invertion(int *x)
{
	*x = -(*x);
}

void invertion(int &x)
{
	x = -x;
}

void move(Circle *circle, double *x1, double *y1)
{
	circle->x += *x1;
	circle->y += *y1;
}

void move(Circle & circle, double &x1, double &y1)
{
	circle.x += x1;
	circle.y += y1;
}

void multipl(Matrix * matr, double * alf)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			matr->a[i][j] *= *alf;
}

void multipl(Matrix & matr, double & alf)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			matr.a[i][j] *= alf;
}

Circle::Circle(double x, double y, double r)
{
	this->x = x;
	this->y = y;
	this->r = r;
}

void Circle::print()
{
	cout << "Circle coordinates: " << '\n';
	cout << "x: " << x << '\n';
	cout << "y: " << y << '\n';
	cout << "r: " << r << '\n';
	cout << '\n';
}

Matrix::Matrix()
{
	srand(time(0));
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			a[i][j] = rand() % 10;
}

void Matrix::print()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			cout << a[i][j] << '\t';
		cout << '\n';
	}

	cout << '\n';
}