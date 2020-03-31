#include <iostream>
#include "IntStack.h"
using namespace std;

int main() {
	bool c;
	int n;
	IntStack a;
	cout << "Limited depth of stack? 1 - true, 0 - false : ";
	cin >> c;
	if (c) {
		cout << "Depth of Stack = ";
		cin >> n;
		IntStack is(n);
		a = is;
	}
	cout << "Amount of numbers: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		int b;
		cin >> b;
		a.push(b);
	}
	cout << "All stack: \n";
	a.print();
	cout << "Let's see top element = ";
	cout << a.back() << "\n";
	cout << "Let's remove top element\n";
	a.pop();
	a.print();
	cout << "Copy this stack to another? 1 - true, 0 - false : ";
	cin >> c;
	if (c) {
		IntStack is1(a);
		cout << "New stack\n";
		is1.print();
	}
	cout << "Check, if stack is empty : ";
	cout << a.empty() << "  Size = " << a.getsize();
	return 0;
}
