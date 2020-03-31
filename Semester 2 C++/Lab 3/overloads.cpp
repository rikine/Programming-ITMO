#include <iostream>
#include "Header.h"
using namespace std;

int main() {
	double vector[2];
	double a;
	double x, y, alpha, edge;
	cout << "Enter x coordinate: ";
	cin >> x;
	cout << "Enter y coordinate: ";
	cin >> y;
	cout << "Enter lenght of edge: ";
	cin >> edge;
	cout << "Enter alpha in rad: ";
	cin >> alpha;
	square sq(x, y, edge, alpha);
	sq.print();
	cout << "Resize the edge in: ";
	cin >> a;
	sq *= a;
	sq.print();
	cout << "Move the square: ";
	cin >> vector[0] >> vector[1];
	sq += vector;
	sq.print();

	cout << "Another square\n";
	double x1, y1, alpha1, edge1;
	cout << "Enter x coordinate: ";
	cin >> x1;
	cout << "Enter y coordinate: ";
	cin >> y1;
	cout << "Enter lenght of edge: ";
	cin >> edge1;
	cout << "Enter alpha in rad: ";
	cin >> alpha1;
	square sq1(x1, y1, edge1, alpha1);

	if (sq1 == sq)
		cout << "squares are equal\n";
	if (sq1 < sq)
		cout << "2 square is smaller\n";
	if (sq1 > sq)
		cout << "1 square is smaller\n";
	if (sq1 != sq)
		cout << "squares aren't equal\n";
	system("pause");
	return 0;
}
