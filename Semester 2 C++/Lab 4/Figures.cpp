#include "Figures.h"

double Rectangle::square() const
{
	return a * b;
}

double Rectangle::perimeter() const
{
	return (a + b) * 2;
}

double Rectangle::mass() const 
{
	return mass_;
}

Vector2D Rectangle::position() const
{
	return position_;
}

bool Rectangle::operator==(const IPhysObject & ob) const
{
	return mass() == ob.mass();
}

bool Rectangle::operator<(const IPhysObject & ob) const
{
	return mass() < ob.mass();
}

void Rectangle::draw() const
{
	std::cout << "\nName = " << name << "\na = " << a << "\nb = " << b;
	std::cout << "\nMass = " << mass_ << "\nsize = " << size();
	std::cout << "\nPosition: x = " << position_.x << " y = " << position_.y;
}

void Rectangle::initFromDialog()
{
	std::cout << "Enter Rectangle's sides a and b, enter mass and position (x, y)\n";
	std::cin >> a >> b >> mass_ >> position_.x >> position_.y;
	std::cout << "Rectangle created";
}

const std::string Rectangle::classname() const
{
	return name;
}

unsigned int Rectangle::size() const
{
	return sizeof(*this);
}

double Circle::square() const
{
	return 3.14 * r * r;
}

double Circle::perimeter() const
{
	return 2 * 3.14 * r;
}

double Circle::mass() const
{
	return mass_;
}

Vector2D Circle::position() const
{
	return position_;
}

bool Circle::operator==(const IPhysObject & ob) const
{
	return mass() == ob.mass();
}

bool Circle::operator<(const IPhysObject & ob) const
{
	return mass() < ob.mass();
}

void Circle::draw() const
{
	std::cout << "\nName = " << name << "\nr = " << r;
	std::cout << "\nMass = " << mass_ << "\nsize = " << size();
	std::cout << "\nPosition: x = " << position_.x << " y = " << position_.y;
}

void Circle::initFromDialog()
{
	std::cout << "Enter Circle's radius, enter mass and position (x, y)\n";
	std::cin >> r >> mass_ >> position_.x >> position_.y;
	std::cout << "Rectangle created";
}

const std::string Circle::classname() const
{
	return name;
}

unsigned int Circle::size() const
{
	return sizeof(*this);
}
