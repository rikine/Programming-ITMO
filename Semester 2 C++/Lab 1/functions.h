#include <iostream>
#include <ctime>
using namespace std;

#pragma once

void floorr(double *x);
void floorr(double &x);

void invertion(double *x);
void invertion(double &x);
void invertion(int *x);
void invertion(int &x);

struct Circle
{
	double x;
	double y;
	double r;

	Circle(double x, double y, double r);

	void print();
};

void move(Circle *circle, double *x1, double *y1);
void move(Circle &circle, double &x1, double &y1);

struct Matrix 
{
	double a[3][3];

	Matrix();

	void print();
};

void multipl(Matrix *matr, double *alf);
void multipl(Matrix &matr, double &alf);