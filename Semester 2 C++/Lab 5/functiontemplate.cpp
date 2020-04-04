template<class T>
inline T power(T n, int power_) {
	T temp = n = power_ >= 0 ? n : 1 / n;
	for (int i = 1; i < std::abs(power_); i++)
		n *= temp;
	return n;
}