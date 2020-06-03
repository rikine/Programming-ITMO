#pragma once
#include "GL/freeglut.h"
#include <array>

typedef unsigned char uchar;
typedef unsigned int uint;

class MyException : public std::exception
{
	const char *msg;

public:
	MyException(const char *msg) : msg(msg) {}

	const char *what() const noexcept override
	{
		return msg;
	}
};

class small_cube
{
private:
	std::array<uint, 6> color; // (UP, DOWN, FRONS, BACK, LEFT, RIGHT)

	//size of edge
	double size;

	//components of color (RGB)
	std::array<uchar, 3> _color;

public:
	small_cube() : size(0.0) {}

	void rotateZ() noexcept;
	void rotateY() noexcept;
	void rotateX() noexcept;

	void set_color(size_t i, const uchar color_);
	void set_color(size_t i, const uint color_);
	uchar get_color(size_t i);
	uchar *at(int i) noexcept;

	void draw();
	void draw(double x, double y, double z);

	double get_size() const noexcept { return size; }
	void set_size(const double size_) noexcept { size = size_; }

	~small_cube() = default;
};