#include "Stack.h"

/*
* Define Sequence Stack
*
*/
void SqStack::Initialize(int n) {
	if (n < 0 || n > LINK_MAXSIZE)
		exit(-1);
	top = -1;
	Type t;
	while (std::cin >> t) {
		if (top == n - 1)
			break;
		data[++top] = t;
	}
}

bool SqStack::Pop(Type& t) {
	if (IsEmpty())
		return false;
	t = data[top--];
	return true;
}

bool SqStack::Push(const Type& t) {
	if (IsFull())
		return false;
	data[++top] = t;
	return true;
}

bool SqStack::GetTop(Type& t) {
	if (IsEmpty())
		return false;
	t = data[top];
	return true;
}

void SqStack::print() {
	if (IsEmpty())
		std::cout << "The stack is empty";
	else
		for (int i = 0; i <= top; i++) {
			std::cout << data[i] << " ";
			if (i + 1 % 10 == 0)
				std::cout << std::endl;
		}
	std::cout << std::endl;

}

/*
* Define link stack
*
*/

void LinkStack::Initialize(int n) {
	if (n <= 0)
		return;
	int count = 0;
	Type t;
	while (std::cin >> t) {
		sNode* newnode = new sNode{ t,top };
		top = newnode;
		if (++count >= n)
			break;
	}
}

bool LinkStack::Push(const Type& t) {
	sNode* newnode = new sNode{ t,top };
	top = newnode;
	return true;
}

bool LinkStack::Pop(Type& t) {
	if (IsEmpty())
		return false;
	t = top->data;
	sNode* temp = top;
	top = top->next;
	delete temp;
	return true;
}

bool LinkStack::GetTop(Type& t) {
	if (IsEmpty())
		return false;
	t = top->data;
	return true;
}

void LinkStack::print() {
	if (IsEmpty())
		std::cout << "The stack is emtpy";
	sNode* p = top;
	int n = 0;
	while (p) {
		std::cout << p->data << " ";
		if (++n % 10 == 0)
			std::cout << std::endl;
		p = p->next;
	}
	std::cout << std::endl;
}