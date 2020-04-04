#include <iostream>
#include "functiontemplate.h"
#include "MatrixNM.h"

int main() {
	double a = 3.05; int b = 5;
	std::cout << "Enter number and a power\n";
	std::cout << power(a, b) << '\n';

	int n, m;
	try {
		std::cout << "Enter N and M of matrix\n";
		std::cin >> n >> m;
		MatrixNM<int> mat(n, m);
		int x, y;
		std::cout << "Enter coordinates of matrix\n";
		std::cin >> x >> y;
		std::cout << mat.get(x, y) << '\n';
		mat.fill();
	}
	catch (OutOfRange &ex) {
		std::cout << ex.what() << ex.show_index();
	}
	catch (WrongData &ex) {
		std::cout << ex.what() << ex.show_data();
	}
	return 0;
}
