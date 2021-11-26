#pragma once
#ifndef STACK_H
#define STACK_H
#include<iostream>
constexpr int LINK_MAXSIZE = 10;
typedef char Type;
struct sNode {
	Type data;
	sNode* next;
};
/*
* Define sequence stack
* 
*/
struct SqStack{
	void Initialize(int n);
	bool Pop(Type &);
	bool Push(const Type&);
	void print();
	bool GetTop(Type&);
	bool IsFull() { return top == LINK_MAXSIZE - 1; }
	bool IsEmpty() { return top == -1; }
	Type data[LINK_MAXSIZE];
	int top=-1;
};

/*
* Define chain stack
* 
*/

struct LinkStack {
	~LinkStack() {
		sNode* p = top; while (p) {sNode* t = p->next; delete p; p = t;} }
	void Initialize(int);
	bool IsEmpty() { return top == nullptr; }
	bool Push(const Type&);
	bool Pop(Type&);
	bool GetTop(Type&);
	void print();

	sNode* top=nullptr;
};

#endif
