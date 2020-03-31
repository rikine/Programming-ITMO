#include "IntStack.h"

IntStack::IntStack(int maxdep) :maxdep(maxdep), top(nullptr), size(0) {}

IntStack::IntStack(const IntStack & temp)
{
	if (temp.top == nullptr)
		return;

	maxdep = temp.maxdep;
	size = temp.size;
	Node *t = temp.top;
	Node *p = new Node(t->value, nullptr);
	top = p;
	t = t->prev;
	while (t != nullptr) {
		p->prev = new Node(t->value, nullptr);
		p = p->prev;
		t = t->prev;
	}
}

IntStack::~IntStack()
{
	while (size) {
		Node *temp = top;
		top = top->prev;
		delete temp;
		size--;
	}
}

void IntStack::push(const int a)
{
	if (size >= maxdep)
		return;

	if (top == nullptr)
		top = new Node(a, nullptr);
	else {
		Node *temp = new Node(a, nullptr);
		temp->prev = top;
		top = temp;
	}

	size++;
}

const int IntStack::pop()
{
	if (!top)
		return NULL;
	
	Node *temp = top;
	top = top->prev;
	int a = temp->value;
	delete temp;
	size--;
	return a;
}

int IntStack::getsize()
{
	return size;
}

bool IntStack::empty()
{
	return size == 0;
}

int IntStack::back()
{
	return top->value;
}

void IntStack::print()
{
	Node *temp = top;
	while (temp != nullptr) {
		cout << temp->value << "\n";
		temp = temp->prev;
	}
	cout << endl;
}

IntStack::Node::Node(int value, Node * prev) : value(value), prev(nullptr) {}