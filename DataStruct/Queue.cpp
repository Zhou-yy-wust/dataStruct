#include "Queue.h"

void Circle_Queue::Initialize(int n) {
	front = rear = 0;
	if (n <= 0) return;
	int count = 0;
	Type t;
	std::cout << "Initialize queue:(maximum = " << (n >= QUEUE_MAXSIZE - 1 ? QUEUE_MAXSIZE - 1 : n) << "):" << std::endl;
	while (!IsFull()) {
		std::cin >> t;
		data[rear] = t;
		rear = (rear + 1) % QUEUE_MAXSIZE;
		if (++count == n)
			break;
	}
}

bool Circle_Queue::EnQueue(const Type& t) {
	if (IsFull()) return false;
	data[rear] = t;
	rear = (rear + 1) % QUEUE_MAXSIZE;
	return true;
}

bool Circle_Queue::DeQueue(Type& t) {
	if (IsEmpty()) return false;
	t = data[front];
	front = (front + 1) % QUEUE_MAXSIZE;
	return true;
}

bool Circle_Queue::GetHead(Type& t) {
	if (IsFull()) return false;
	t = data[front];
}

void Circle_Queue::print() {
	if (IsEmpty())
		std::cout << "Queue is emtpy!";
	else
		for (int p = front; p != rear; p = (p + 1) % QUEUE_MAXSIZE)
			std::cout << data[p] << " ";
	std::cout << std::endl;
}


void Link_Queue::Initialize(int n) {
	front = new qNode{ 0,nullptr };
	rear = front;
	if (n <= 0) return;
	Type t;
	std::cout << "Initialize queue( " << n << " ):" << std::endl;
	for (int count = 0; count != n; count++) {
		std::cin >> t;
		qNode* newnode = new qNode;
		newnode->data = t;
		newnode->next = rear->next;
		rear->next = newnode;
		rear = newnode;
	}
}

bool Link_Queue::EnQueue(const Type& t) {
	qNode* newnode = new qNode;
	newnode->data = t, newnode->next = rear->next;
	rear->next = newnode, rear = newnode;
	return true;
}

bool Link_Queue::DeQueue(Type& t) {
	if (IsEmpty()) return false;
	qNode* q = front->next;
	t = q->data;
	front->next = q->next;
	delete q;
	if (front->next == nullptr)
		rear = front;
	return true;
}

bool Link_Queue::GetHead(Type& t) {
	if (IsEmpty()) return false;
	t = front->next->data;
	return true;
}

void Link_Queue::print() {
	if (IsEmpty())
		std::cout << "Queue is emtpy!";
	else
		for (qNode* q = front->next; q; q = q->next)
			std::cout << q->data << " ";
	std::cout << std::endl;
}
