#include <vector>
#include <iostream>
#pragma once

class OutOfRange :public std::exception
{
private:
	int index;
public:
	OutOfRange(int index) : index(index) {}

	const char* what() const override{
		return "Out of range: index = ";
	}

	const int show_index() const {
		return index;
	}
};

class WrongData :public std::exception
{
private:
	char* data;
public:
	WrongData(char* data) : data(data) {}

	const char* what() const override {
		return "Wrong data: data = ";
	}

	const char* show_data() const {
		return data;
	}

	~WrongData() {
		delete[] data;
	}
};

template<class T>
class MatrixNM
{
private:
	int n, m;
	std::vector<std::vector<T>> matrix;
public:
	inline MatrixNM(int n, int m);

	inline void push(const int x, const int y, const T &data);

	inline T get(const int x, const int y);

	inline void fill();
};

template<class T>
inline MatrixNM<T>::MatrixNM(int n, int m) : n(n), m(m)
{
	if (n <= 0 || m <= 0)
		throw OutOfRange(n <= 0 ? n : m);
	matrix.resize(n, std::vector<T>(m));
}

template<class T>
inline void MatrixNM<T>::push(const int x, const int y, const T & data)
{
	if (x < 0 || y < 0 || x > n || y > m)
		throw OutOfRange(n <= 0 ? n : m);
	matrix[x][y] = data;
}

template<class T>
inline T MatrixNM<T>::get(const int x, const int y)
{
	if (x < 0 || y < 0 || x >= n || y >= m)
		throw OutOfRange(n <= 0 ? n : m);
	return matrix[x][y];
}

template<class T>
inline void MatrixNM<T>::fill()
{
	std::cout << "Enter n*m numbers\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			T data;
			std::cin >> data;
			if (std::cin.fail()) {
				char *c = new char[32767];
				std::cin.clear();
				std::cin.getline(c, 32767, '\n');
				throw WrongData(c);
			}
			matrix[i][j] = data;
		}
	}
}
