#pragma once
#include "scube.h"
#include "solver.h"
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <algorithm>
#include <exception>

class Iinit
{
public:
	virtual void input() = 0;
	virtual void clear() = 0;
};

class IDisplay
{
public:
	virtual void draw() = 0;
};

class ISolver
{
public:
	virtual void solver() = 0;
};

class IFigure : public Iinit,
				public IDisplay,
				public ISolver
{};

class Cube : public IFigure
{
private:
	//size of cube
	double size;

	//angel
	std::array<int, 6> rotate;

	//number of side
	int current;

	//auxiliary
	std::array<std::array<std::array<bool, 3>, 3>, 3> ok;
	std::array<std::array<small_cube, 3>, 3> tmp;

	//solution
	std::vector<uchar> path;

	//for shuffling
	bool shuff;

protected:
	//27 parts of cube
	std::array<std::array<std::array<small_cube, 3>, 3>, 3> parts;

	//colors of all sides (auxiliary)
	std::array<std::array<uchar, 9>, 6> colors_by_s;

	//default colors
	std::array<uint, 6> default_colors;

public:
	Cube() : current(-1), shuff(false) {}

	//make a default cube
	void clear() override;
	//input of a cube
	void input() override;

	//for drawing a cube
	void draw() override;
	void rot90(int idx, int sign);
	void Rotate(int idx, int angle);

	//solving
	void solver() override;
	std::vector<uchar> &solution() { return path; }
	void check_invariants();

	//auxiliary
	int get_current() const noexcept { return current; }
	void set_def_col(const std::array<uint, 6> &def_col) noexcept;
	void set_size(const double size_);

	void make_shuffeled();

private:
	//update colors of sides
	void update_colors() noexcept;
};