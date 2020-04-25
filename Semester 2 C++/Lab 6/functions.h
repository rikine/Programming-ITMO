#pragma once

template<class ItFirst, class UnaryFunc>
bool any_of(ItFirst begin, ItFirst end, UnaryFunc f) {
	while (begin != end)
		if (f(*begin++))
			return true;
	return false;
}

template<class ItFirst, class UnaryFunc>
bool is_partitioned(ItFirst begin, ItFirst end, UnaryFunc f) {
	char changed = 0;
	char parted = -1;
	while (begin != end) {
		bool cur = f(*begin++);
		if (cur && parted == -1)
			parted = 1;
		else if (!cur && parted == -1)
			parted = 0;
		else if (!cur && !parted && changed)
			return false;
		else if (cur && parted && changed)
			return false;

		if (!changed) {
			if (cur && !parted)
				changed = 1;
			else if (!cur && parted)
				changed = 1;
		}
	}
	return true;
}

template<class ItFirst, class T>
T find_not(ItFirst begin, ItFirst end, T element) {
	while (begin != end) {
		if (element != *begin)
			return *begin;
		begin++;
	}
	return T();
}
