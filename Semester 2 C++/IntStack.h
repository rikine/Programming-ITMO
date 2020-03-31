#include <iostream>
using namespace std;
#pragma once

class IntStack
{
private:
	int maxdep;
	int size;
	class Node
	{
	public:
		Node *prev;
		int value;

		Node(int value = NULL, Node *prev = nullptr);
	};

	mutable Node *top;
public:
	explicit IntStack(int maxdep = INT_MAX);
	explicit IntStack(const IntStack &temp);
	~IntStack();

	void push(const int a);
	const int pop();
	int getsize();
	bool empty();
	int back();
	void print();
};