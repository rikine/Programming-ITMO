#pragma once

class Out_Of_Range : public std::exception {
	const char *msg;
public:
	Out_Of_Range() : msg("Out Of Range") {}

	const char* what() const override {
		return msg;
	}
};

template<class T>
class circular_buf;

template<class T>
class my_iter : public std::iterator<std::random_access_iterator_tag, T> {
	friend class circular_buf<T>;

	T* value;
	size_t size;
	T* start;

public:
	my_iter(T* it, T* start, size_t size) : value(it), size(size), start(start) {}
	my_iter(const my_iter& b) :value(b.value), size(b.size), start(b.start) {}

	bool operator!=(my_iter const& b) {
		return value != b.value;
	}
	bool operator==(my_iter const& b) {
		return value == b.value;
	}

	typename my_iter::reference operator*() {
		return *value;
	}

	my_iter& operator++() {
		if (value + 1 == start + size) {
			value = start + size;
			return *this;
		}
		intptr_t t = abs(intptr_t(value + 1 - start + size)) % size;
		value = start + t;
		return *this;
	}

	my_iter operator++(int) {
		my_iter<T> temp(value, start, size);
		if (value + 1 == start + size) {
			value = start + size;
			return *this;
		}
		intptr_t t = abs(intptr_t(value + 1 - start + size)) % size;
		value = start + t;
		return temp;
	}

	my_iter& operator--() {
		intptr_t t = abs(intptr_t(value - 1 - start + size)) % size;
		value = start + t;
		return *this;
	}

	my_iter operator--(int) {
		my_iter<T> temp(value, start, size);
		intptr_t t = abs(intptr_t(value - 1 - start + size)) % size;
		value = start + t;
		return temp;
	}

	my_iter& operator+(size_t n) {
		if (value + n == start + size) {
			value = start + size;
			return *this;
		}
		intptr_t t = abs(intptr_t(value + n - start + size)) % size;
		value = start + t;
		return *this;
	}

	my_iter& operator-(size_t n) {
		intptr_t t = abs(intptr_t(value - n - start + size)) % size;
		value = start + t;
		return *this;
	}

	my_iter& operator[](size_t n) {
		intptr_t t = n % size;
		value = start + t;
		return *this;
	}

	my_iter& operator-=(const my_iter& b) {
		if (abs(intptr_t(value - b.value)) == intptr_t(start + size)) {
			value = start + size;
			return *this;
		}
		value = (T*)(value - b.value);
		return *this;
	}

	my_iter& operator+=(const my_iter& b) {
		if (abs(intptr_t(value) + intptr_t(b.value)) == intptr_t(start + size)) {
			value = start + size;
			return *this;
		}
		intptr_t t = abs(intptr_t(value) + intptr_t(b.value)) % size;
		value = start + t;
		return *this;
	}

	bool operator<(my_iter& b) {
		return value < b.value;
	}

	T* operator->() {
		return value;
	}

	template<class T>
	friend int operator-(my_iter<T>& a, my_iter<T>& b);

	template<class T>
	friend const int operator-(const my_iter<T>& a, const my_iter<T>& b);

	template<class T>
	friend int operator+(my_iter<T>& a, my_iter<T>& b);

	template<class T>
	friend const int operator+(const my_iter<T>& a, const my_iter<T>& b);
};

template<class T>
int operator-(my_iter<T> & a, my_iter<T> & b)
{
	my_iter<T> temp(a);
	temp -= b;
	return intptr_t(temp.value);
}

template<class T>
const int operator-(const my_iter<T> & a, const my_iter<T> & b)
{
	my_iter<T> temp(a);
	temp -= b;
	return intptr_t(temp.value);
}

template<class T>
int operator+(my_iter<T>& a, my_iter<T>& b) {
	my_iter<T> temp(a);
	temp += b;
	return intptr_t(temp.value);
}

template<class T>
const int operator+(const my_iter<T>& a, const my_iter<T>& b) {
	my_iter<T> temp(a);
	temp += b;
	return intptr_t(temp.value);
}

template<class T>
class circular_buf {
public:
	typedef my_iter<T> iterator;
	typedef my_iter<const T> const_iterator;

private:
	T* data;
	size_t size;
	size_t capacity;

	circular_buf(const circular_buf<T>&) = delete;
	circular_buf<T>& operator=(const circular_buf<T>&) = delete;

	void check() {
		if (size == 0) {
			data = nullptr;
			capacity = 0;
		}
	}

public:
	circular_buf() :size(0), capacity(0) {}

	circular_buf(const size_t size) :size(size), capacity(size) {
		if (size <= 0)
			throw Out_Of_Range;
		data = new T[size];
	}

	circular_buf(const size_t size, const T elem) :size(size), capacity(size) {
		if (size <= 0)
			throw Out_Of_Range();
		data = new T[size];
		std::fill(data, data + size, elem);
	}

	void reserve(const size_t new_cap);

	void clear() {
		if (size == 0)
			data = nullptr;
		else {
			size = 0;
			capacity = 0;
			delete[] data;
			data = nullptr;
		}
	}

	~circular_buf() {
		clear();
	}

	T front() const {
		if (size == 0)
			throw Out_Of_Range();
		return data[0];
	}

	void push_front(const T& elem);

	void pop_front();

	T back() const {
		if (size == 0)
			throw Out_Of_Range();
		return data[size - 1];
	}

	void push_back(const T& elem);

	void pop_back();

	T& operator[](int i);

	iterator begin() const {
		return iterator(data, data, size);
	}

	iterator end() const {
		return iterator(data + size, data, size);
	}

	const_iterator cbegin() const {
		return const_iterator(data, data, size);
	}

	const_iterator cend() const {
		return const_iterator(data + size, data, size);
	}

	void erase(const_iterator it);
	void erase(iterator it);

	void insert(iterator it, const T& value);
	void insert(const_iterator it, const T& value);

	size_t get_size() {
		return size;	
	}
};

template<class T>
std::ostream& operator<< (std::ostream& os, my_iter<T>& it) {
	os << it;
	return os;
}

template<class T>
std::ostream& operator<< (std::ostream& os, my_iter<T> it) {
	os << &it;
	return os;
}

template<class T>
inline void circular_buf<T>::reserve(const size_t new_cap)
{
	if (capacity > new_cap)
		return;

	if (data == nullptr)
		data = new T[new_cap];
	else {
		T* temp = new T[new_cap];
		for (size_t i = 0; i < size; i++)
			temp[i] = data[i];
		delete[] data;
		data = temp;
		capacity = new_cap;
	}
}

template<class T>
inline void circular_buf<T>::push_front(const T & elem)
{
	if (capacity >= size + 1) {
		std::copy(data, data + size, data + 1);
		data[0] = elem;
		size++;
	}
	else {
		T* temp = new T[capacity + 10];
		std::copy(data, data + size, temp + 1);
		temp[0] = elem;
		delete[] data;
		data = temp;
		size++;
		capacity += 10;
	}
	check();
}

template<class T>
inline void circular_buf<T>::pop_front()
{
	if (size == 0)
		throw Out_Of_Range();
	T* temp = new T[capacity];
	std::copy(data + 1, data + size, temp);
	size--;
	delete[] data;
	data = temp;
	check();
}

template<class T>
inline void circular_buf<T>::push_back(const T & elem)
{
	if (capacity >= size + 1 && size != 0)
		data[size++] = elem;
	else {
		T* temp = new T[capacity + 10];
		capacity += 10;
		std::copy(data, data + size, temp);
		temp[size] = elem;
		size++;
		delete[] data;
		data = temp;
	}
	check();
}

template<class T>
inline void circular_buf<T>::pop_back()
{
	if (size == 0)
		throw Out_Of_Range();

	size--;
	check();
}

template<class T>
inline T & circular_buf<T>::operator[](int i)
{
	if (size == 0)
		throw Out_Of_Range();
	if (i < 0)
		return data[(i + size) % size];
	else
		return data[i % size];
}

template<class T>
inline void circular_buf<T>::erase(const_iterator it)
{
	if (size == 0)
		throw Out_Of_Range();
	int to = end() - it - 1;
	int from = size - to - 1;

	T* temp = new T[capacity];
	std::copy(data, data + from, temp);
	std::copy(data + from + 1, data + size, temp + from);
	delete[] data;
	data = temp;
	size--;
}

template<class T>
inline void circular_buf<T>::erase(iterator it)
{
	if (size == 0)
		throw Out_Of_Range();

	int to = end() - it - 1;
	int from = size - to - 1;

	T* temp = new T[capacity];
	std::copy(data, data + from, temp);
	std::copy(data + from + 1, data + size, temp + from);
	delete[] data;
	data = temp;
	size--;
}

template<class T>
inline void circular_buf<T>::insert(iterator it, const T & value)
{
	int to = end() - it - 1;
	int from = size - to - 1;
	if (capacity >= size + 1) {
		std::copy(data, data + from, data);
		std::copy(data + from, data + size, data + from + 1);
		data[from] = value;
	}
	else {
		T* temp = new T[capacity + 10];
		std::copy(data, data + size, temp);
		std::copy(data, data + from, data);
		std::copy(data + from, data + size, data + from + 1);
		temp[from] = value;
		delete[] data;
		data = temp;
		capacity += 10;
	}
	size++;
}

template<class T>
inline void circular_buf<T>::insert(const_iterator it, const T & value)
{
	int to = end() - it - 1;
	int from = size - to - 1;
	if (capacity >= size + 1) {
		std::copy(data, data + from, data);
		std::copy(data + from, data + size, data + from + 1);
		data[from] = value;
	}
	else {
		T* temp = new T[capacity + 10];
		std::copy(data, data + size, temp);
		std::copy(data, data + from, data);
		std::copy(data + from, data + size, data + from + 1);
		temp[from] = value;
		delete[] data;
		data = temp;
		capacity += 10;
	}
	size++;
}
