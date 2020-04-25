#include <iostream>
#include <vector>
#include "functions.h"
using namespace std;

template<class T>
bool foo(T a) {
	return a > 0 ? true : false;
}

int main() {
	vector<int> a(5, -1);
	vector<int> b(5, 4);
	b[4] = -1; b[3] = -2;
	cout << boolalpha;
	cout << any_of(a.begin(), a.end(), foo<int>) << endl;
	cout << is_partitioned(b.begin(), b.end(), foo<int>) << endl;
	cout << find_not(b.begin(), b.end(), 4) << endl;
	return 0;
}
