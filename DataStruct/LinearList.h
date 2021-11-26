#pragma
#ifndef LINEARLIST_H
#define LINEARLIST_H
#include<memory>
#include<iostream>
constexpr int LINK_MAXSIZE = 20;
template<typename T>struct LNode {
	T data;
	LNode* next;
};

template <typename T> class Static_List {
public:
	Static_List()  { //构造函数
		sqlist = new T[LINK_MAXSIZE];
    }
	~Static_List() { delete []sqlist; }
	//增、删、查、判满、判空、返回长度
	bool Insert(const T&,unsigned pos); 
	bool Delete(T&,unsigned pos);   
	unsigned LocateElem(const T&);
    bool GetElem(T&,unsigned pos);
	bool IsEmpty() { return length == 0; }
	bool IsFull() { return length == LINK_MAXSIZE; }
	unsigned Length() { return length; }
	void print();
private:
	T* sqlist = nullptr;
	unsigned length = 0;
};



template<typename T>class Dynamic_List {
public:
	Dynamic_List(unsigned len) :length(len), max(2*len) {
		list = new T[max];}
	Dynamic_List(T* l, unsigned len) :list(l), length(len), max(2 * len) {};
	//~Dynamic_List() { delete[] list; }
	// 判空、插入、删除、按位、按值查找
	bool IsEmpty() { return length == 0; }
	bool Insert(const T&, unsigned);
	bool Delete(T&, unsigned);
	unsigned LocateElem(const T&);
	bool GetElem(T&, unsigned);
	unsigned Length() { return length; }
	T* GetList() { return list; }
	//打印
	void print();
private:
	T* list;
	unsigned length;
	unsigned max;

	//内存分配
	bool IsFull() { return length == max; }
	void Alloctor();
};



template<typename T>class Link_List {
public:
	Link_List() :List(new LNode<T>) { List->next = nullptr; }
	~Link_List();
	void HeadInsert(int n);
	void TailInsert(int n);
	LNode<T>* GetElem(int pos)const;
	LNode<T>* LocateElem(const T&)const;
	bool Insert(const T& t, int pos);
	bool Delete(T& t, int pos);
	int Length();
	void print();
private:
	LNode<T>* List;
};


template <typename T> struct LStack {
	~LStack() {
		LNode<T>* p = top; while (p) { LNode<T>* t = p->next; delete p; p = t; }
	}
	void Initialize(int);
	bool IsEmpty() { return top == nullptr; }
	bool Push(const T&);
	bool Pop(T&);
	bool GetTop(T&);
	void print();
	LNode<T>* top = nullptr;
};



template<typename T>
struct LQueue{
	LQueue():front(new LNode<T>{ 0,nullptr }),rear(front){}
	void Initialize(int n);
	bool IsEmpty() { return rear == front; }
	bool EnQueue(const T& t);
	bool DeQueue(T& t);
	bool GetHead(T& t);
	void print();
	LNode<T>* front = nullptr, *rear = nullptr;
};

/*
* 
* Defines operations for static linked list
* 
*/


template <typename T>
bool Static_List<T>::Insert(const T& t, unsigned pos) {
	if (IsFull() || pos > length+1 ||pos ==0)
		return false;
	for (unsigned p = length; p > pos-1; p--)
		sqlist[p] = sqlist[p - 1];
	sqlist[pos-1] = t;
	length++;
	return true;
}

template<typename T>
bool Static_List<T>::Delete(T& t, unsigned pos) {
	if (pos > length || pos==0)
		return false;
	t = sqlist[pos - 1];
	for (unsigned p = pos ; p != length; p++)
		sqlist[p-1] = sqlist[p];
	length--;
	return true;
}

template<typename T>
unsigned Static_List<T>::LocateElem(const T& t) {
	for (unsigned i = 0; i != length; i++)
		if (sqlist[i] == t)
			return i + 1;
	return 0;
}

template<typename T>
bool Static_List<T>::GetElem(T&t,unsigned pos) {
	if (IsEmpty() || pos > length ||pos==0)
		return false;
	t = sqlist[pos - 1];
	return true;
}

template<typename T>
void Static_List<T>::print() {
	for (unsigned i = 0; i != length; i++) {
		std::cout << sqlist[i] << " ";
		if ((i+1) % 10 == 0)
			std::cout << std::endl;
	}
	std::cout << std::endl;
}

/*
* 
* Defines operations for dynamic squential list;
*
*/
template<typename T>
void Dynamic_List<T>::Alloctor() {
	max = max * 3 / 2;
	T* newlist = new T[max];
	for (unsigned p = 0; p != length; p++) {
		newlist[p] = list[p];
	}
	delete[] list;
	list = newlist;
}

template<typename T>
bool Dynamic_List<T>::Insert(const T& t, unsigned pos) {
	if (pos == 0 || pos>length+1)
		return false;
	if (IsFull())
		Alloctor();
	unsigned p = length;
	while (p >= pos) {
		list[p] = list[p - 1];
		p--;
	}
	list[p] = t;
	length++;
	return true;
}

template<typename T>
bool Dynamic_List<T>::Delete(T& t, unsigned pos) {
	if (pos == 0 || pos > length)
		return false;
	unsigned p = pos;
	t = list[p - 1];
	while (p != length) {
		list[p - 1] = list[p];
		p++;
	}
	length--;
	return true;
}

template<typename T>
unsigned Dynamic_List<T>::LocateElem(const T& t) {
	unsigned p = 0;
	while (p != length) {
		if (list[p++] == t)
			return p;
	}
	return 0;
}

template<typename T>
bool Dynamic_List<T>::GetElem(T&, unsigned pos) {
	if (pos == 0 || pos > length)
		return false;
	T = list[pos - 1];
	return true;
}

template<typename T>
void Dynamic_List<T>::print() {
	if (IsEmpty())
		std::cout << "Dynamic list is empty!" << std::endl;
	for (unsigned p = 0; p != length; p++) {
		std::cout << list[p] << " ";
		if ((p + 1) % 10 == 0)
			std::cout << std::endl;
	}
	std::cout << std::endl;
}

/*
* 
* Defines operations for linked list
*
*/
template<typename T>
Link_List<T>::~Link_List() {
	LNode<T>* del = List;
	while (del) {
		LNode<T>* p = del;
		del = del->next;
		delete p;
	}
}

template<typename T>
void Link_List<T>::HeadInsert(int n) {
	if (n <= 0)
		return;
	int count = 0;
	T t;
	while (count++ != n && std::cin >> t) {
		LNode<T>* newnode = new LNode<T>;
		newnode->data = t;
		newnode->next = List->next;
		List->next = newnode;
	}
}

template<typename T>
void Link_List<T>::TailInsert(int n) {
	if (n <= 0)
		return;
	int count = 0;
	T t;
	LNode<T>* tailptr = List;
	while (count++ != n &&std::cin >> t) {
		LNode<T>* newnode = new LNode<T>;
		newnode->data = t;
		tailptr->next = newnode;
		tailptr = newnode;
	}
	tailptr->next = nullptr;
}

template<typename T>
LNode<T>* Link_List<T>::GetElem(int pos)const {
	if (pos < 0)
		return nullptr;
	int p = 0;
	LNode<T> *ptr = List;
	while (ptr && p != pos) {
		ptr = ptr->next;
		p++;
	}
		return ptr;
}

template<typename T>
LNode<T>* Link_List<T>::LocateElem(const T& t)const {
	LNode<T>* ptr = List->next;
	while (ptr && ptr->data != t)
		ptr = ptr->next;
	return ptr;
}

template<typename T>
bool Link_List<T>::Insert(const T& t, int pos) {
	LNode<T>* pre = GetElem(pos - 1);
	if (!pre)
		return false;
	LNode<T>* newnode = new LNode<T>;
	newnode->data = t;
	newnode->next = pre->next;
	pre->next = newnode;
	return true;
}

template<typename T>
bool Link_List<T>::Delete(T& t, int pos) {
	LNode<T>* pre = GetElem(pos - 1);
	if (!pre || !pre->next)
		return false;
	LNode<T>* delnode = pre->next;
	t = delnode->data;
	pre->next = delnode->next;
	delete delnode;
	return true;
}

template<typename T>
int Link_List<T>::Length() {
	int len = 0;
	LNode<T>* ptr = List;
	while (ptr->next) {
		ptr = ptr->next;
		len++;
	}
	return len;
}

template<typename T>
void Link_List<T>::print() {
	int count=0;
	LNode<T>* ptr = List->next;
	if (!ptr)
		std::cout << "Link list is empty" << std::endl;
	std::cout << "The length of list is " << Length() << " ,and the "
		"content of list as follow: " << std::endl;
	while (ptr) {
		std::cout << ptr->data << " ";
		if (++count % 20 == 0)
			std::cout << std::endl;
		ptr = ptr->next;
	}
	std::cout << std::endl;
}

/*
* Link Stack
* 
*/
template<typename T>
void LStack<T>::Initialize(int n) {
	if (n <= 0)
		return;
	int count = 0;
	T t;
	while (std::cin >> t) {
		LNode<T>* newnode = new LNode<T>{ t,top };
		top = newnode;
		if (++count >= n)
			break;
	}
}

template<typename T>
bool LStack<T>::Push(const T& t) {
	LNode<T>* newnode = new LNode<T>{ t,top };
	top = newnode;
	return true;
}

template<typename T>
bool LStack<T>::Pop(T& t) {
	if (IsEmpty())
		return false;
	t = top->data;
	LNode<T>* temp = top;
	top = top->next;
	delete temp;
	return true;
}

template<typename T>
bool LStack<T>::GetTop(T& t) {
	if (IsEmpty())
		return false;
	t = top->data;
	return true;
}

template<typename T>
void LStack<T>::print() {
	if (IsEmpty())
		std::cout << "The stack is emtpy";
	LNode<T>* p = top;
	int n = 0;
	while (p) {
		std::cout << p->data << " ";
		if (++n % 10 == 0)
			std::cout << std::endl;
		p = p->next;
	}
	std::cout << std::endl;
}
/*
* Link Queue
* 
*/
template<typename T>
void LQueue<T>::Initialize(int n) {
	if (n <= 0) return;
	T t;
	std::cout << "Initialize queue( " << n << " ):" << std::endl;
	for (int count = 0; count != n; count++) {
		std::cin >> t;
		LNode<T>* newnode = new LNode<T>;
		newnode->data = t;
		newnode->next = rear->next;
		rear->next = newnode;
		rear = newnode;
	}
}

template<typename T>
bool LQueue<T>::EnQueue(const T& t) {
	LNode<T>* newnode = new LNode<T>;
	newnode->data = t, newnode->next = rear->next;
	rear->next = newnode, rear = newnode;
	return true;
}

template<typename T>
bool LQueue<T>::DeQueue(T& t) {
	if (IsEmpty()) return false;
	LNode<T>* q = front->next;
	t = q->data;
	front->next = q->next;
	delete q;
	if (front->next == nullptr)
		rear = front;
	return true;
}

template<typename T>
bool LQueue<T>::GetHead(T& t) {
	if (IsEmpty()) return false;
	t = front->next->data;
	return true;
}

template<typename T>
void LQueue<T>::print() {
	if (IsEmpty())
		std::cout << "Queue is emtpy!";
	else
		for (LNode<T>* q = front->next; q; q = q->next)
			std::cout << q->data << " ";
	std::cout << std::endl;
}
#endif