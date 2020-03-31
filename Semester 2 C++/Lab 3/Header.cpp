#include "Header.h"

square::square(double x, double y, double a, double alpha) : x(x), y(y), a(a), alpha(alpha), sqre(a*a) { }

void square::print()
{
	std::cout << "Side = " << a << std::endl;
	std::cout << "square = " << a * a << std::endl;
	std::cout << "x = " << x << " y = " << y << std::endl;
}

bool square::operator==(square &a)
{
	return this->sqre == a.sqre;
}

bool square::operator!=(square &a)
{
	return this->sqre != a.sqre;
}

bool square::operator<(square &a)
{
	return this->sqre < a.sqre;
}

bool square::operator>(square &a)
{
	return this->sqre > a.sqre;
}

square& square::operator*(double a)
{
	this->a *= a;
	this->sqre = this->a * this->a;
	return *this;
}

square& square::operator+(double *a) {
	this->x += a[0];
	this->y += a[1];
	return *this;
}

square square::operator*=(double a)
{
	return square::operator*(a);
}

square square::operator+=(double * a)
{
	return square::operator+(a);
}
