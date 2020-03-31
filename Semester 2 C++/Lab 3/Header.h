#include <iostream>
#pragma once

class square {
private:
	double x;
	double y;
	double a;
	double alpha;
	double sqre;
public:
	square(double x, double y, double a, double alpha);

	void print();

	bool operator==(square &a);

	bool operator!=(square &a);

	bool operator<(square &a);

	bool operator>(square &a);

	square& operator*(double a);

	square& operator+(double *a);

	square operator*=(double a);

	square operator+=(double *a);
};