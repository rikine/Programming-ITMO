#include <iostream>
#include <iterator>
#include <algorithm>
#include "circular_buffer.h"

int main() {
	circular_buf<int> a(3, 7);
	a[2] = 3;
	try {
		a.push_front(60);
		for (int i = 0; i < 100; i++)
			std::cout << a[i] << " ";

		for (auto it = a.cbegin(); it != a.cend(); ++it)
			std::cout << *it << " ";
		
		std::cout << std::endl << a.end() - a.begin();
		std::cout << "SORT" << std::endl;
		sort(a.begin(), a.end());
		std::cout << "SORTED" << std::endl;

		for (auto it = a.cbegin(); it != a.cend(); ++it)
			std::cout << *it << " ";

		std::cout << std::endl;
		for (int i = 0; i < a.get_size(); i++)
			std::cout << a[i] << " ";

		a.erase(a.begin());

		std::cout << std::endl;
		for (auto it = a.cbegin(); it != a.cend(); ++it)
			std::cout << *it << " ";

		std::cout << std::endl;
		for (int i = 0; i < a.get_size(); i++)
			std::cout << a[i] << " ";

		a.insert(a.end() - 1, 13);

		std::cout << std::endl;
		for (auto it = a.cbegin(); it != a.cend(); ++it)
			std::cout << *it << " ";

		std::cout << std::endl;
		for (int i = 0; i < a.get_size(); i++)
			std::cout << a[i] << " ";
	}
	catch (std::exception& ex) {
		std::cout << ex.what();
	}
	return 0;
}
