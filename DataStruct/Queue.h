#pragma once
#ifndef QUEUE_H
#define QUEUE_H
#include<iostream>

constexpr int QUEUE_MAXSIZE = 10;
using Type = int;

struct qNode {
	Type data;
	qNode* next;
};

struct Circle_Queue {
	void Initialize(int n);
	bool IsEmpty() { return front == rear; }
	bool IsFull() { return (rear + 1) % QUEUE_MAXSIZE == front; }
	bool EnQueue(const Type&);
	bool DeQueue(Type&);
	bool GetHead(Type&);
	void print();
	Type data[QUEUE_MAXSIZE];
	int front, rear;
};


struct Link_Queue {
	void Initialize(int n);
	bool IsEmpty() { return rear == front; }
	bool EnQueue(const Type& t);
	bool DeQueue(Type& t);
	bool GetHead(Type& t);
	void print();
	qNode* front=nullptr, * rear=nullptr;
};

#endif