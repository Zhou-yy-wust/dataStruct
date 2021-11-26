#pragma once
#ifndef CHARPTER2_3_7
#define CHARPTER2_3_7
#include<iostream>
typedef char Type;
typedef struct lNode {
	Type data;
	lNode* next;
}lNode,*List;
/*
* Link List Defined Without Head Node 
* 
*/
struct No_Head_List {
	void HeadInsert(int n);
	void TailInsert(int n);
	void print();
	int Length() { lNode* p = list; int len = 0; while (p) { len++; p = p->next; }return len; }
	List list;
};

void No_Head_List::HeadInsert(int n) {
	if (n <= 0)
		return;
	int count = 0;
	Type t;
	list = nullptr;
	while (std::cin >> t) {
		lNode *newnode = new lNode;
		newnode->data = t;
		newnode->next = list;
		list = newnode;
		if (++count == n)
			break;
	}
}

void No_Head_List::TailInsert(int n) {
	if (n <= 0)
		return;
	int count = 1;
	Type t;
	std::cin >> t;
	list = new lNode{ t,nullptr };
	lNode* tailnode = list;
	while ( ++count<=n && std::cin >> t) {
		lNode* newnode = new lNode;
		newnode->data = t;
		tailnode->next = newnode;
		tailnode = newnode;
	}
	tailnode->next = nullptr;
}

void No_Head_List::print() {
	int count = 0;
	lNode* ptr = list;
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
* Link List Defined With Head Node 
* 
*/
struct Head_List {
	void HeadInsert(int n);
	void TailInsert(int n);
	void print();
	int Length() { lNode* p = list->next; int len = 0; while (p) { len++; p = p->next; }return len; }
	List list;
};

void Head_List::HeadInsert(int n) {
	list = new lNode{ 0,nullptr };
	if (n <= 0) return;
	Type t;
	int count = 0;
	while (++count <= n && std::cin >> t) {
		lNode* newnode = new lNode;
		newnode->data = t;
		newnode->next = list->next;
		list->next = newnode;
	}
}

void Head_List::TailInsert(int n) {
	list = new lNode{ 0,nullptr };
	if (n <= 0) return;
	lNode* tailnode = list;
	int  count = 0;
	Type t;
	while (++count <= n && std::cin >> t) {
		lNode* newnode = new lNode;
		newnode->data = t;
		newnode->next = tailnode->next;
		tailnode->next = newnode;
		tailnode = newnode;
	}
	tailnode->next = nullptr;
}

void Head_List::print() {
	int count = 0;
	lNode* ptr = list->next;
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
* Questions on page 38
* 
*/
void question1(List& L,Type x) {
	if (!L)
		return;
	if (L->data == x) {
		lNode* ptr = L;
		L = L->next;
		delete ptr;
		question1(L, x);
	}
	else
		question1(L->next, x);
}

void question2(List& L, Type x) {
	lNode* work = L->next; //First element
	lNode* tail = L;
	while (work) {
		if (work->data != x) {
			tail->next = work;
			tail = tail->next;
			work = work->next;
		}
		else {
			lNode* t = work;
			work = work->next;
			delete t;
		}
	}
	tail->next = nullptr;
}

void question3(List& L) {
	lNode*work = L->next;
	L->next = nullptr;
	while (work) {
		lNode* t = work->next;
		work->next = L->next;
		L->next = work;
		work = t;
	}
	work = L->next;
	while (work) {
		std::cout << work->data << " ";
		work= work->next;
	}
}

void question4(List& L) {
	int minium = 0x7fffffff;
	lNode* minnode=L, * ptr = L;
	while (ptr->next) {
		if (minium > ptr->next->data)
			minium=ptr->next->data,minnode = ptr;
		ptr=ptr->next;
	}
	ptr = minnode->next;
	minnode->next = ptr->next;
	delete ptr;
}

void question5(List& L) {
	lNode* work = L->next;
	L->next = nullptr;
	while (work) {
		lNode* t = work->next;
		work->next = L->next;
		L->next = work;
		work = t;
	}
}

void question6(List& L) {
	lNode* p = L->next->next, * q = L;
	L->next->next = nullptr;
	lNode* t;
	while (p) {
		t = p->next;
		for (q = L; q->next; q = q->next) {
			if (q->next->data > p->data) {
				p->next = q->next;
				q->next = p;
				break;
			}
		}
		if (!q->next) {
			p->next = q->next;
			q->next = p;
		}
		p = t;
	}
}

void question7(List& L, int min, int max) {
	if (min > max) return;
	lNode* p = L->next,*q=L;
	L->next = nullptr;
	while (p) {
		lNode* t = p->next;
		if (p->data >= min && p->data <= max)
			delete p;
		else {
			p->next = q->next;
			q->next = p;
			q = p;
		}
		p = t;
	}
}

List question8(Head_List& list1, Head_List& list2) {
	int len1 = list1.Length(), len2 = list1.Length();
	Head_List shortlist = len1 < len2 ? list1 : list2;
	Head_List longlist = len1 < len2 ? list2 : list1;
	int diff = (len1 - len2 > 0) ? len1 - len2 : len2 - len1;
	while (diff-- > 0)
		longlist.list = longlist.list->next;
	while (longlist.list) {
		if (longlist.list == shortlist.list)
			return longlist.list;
		longlist.list = longlist.list->next;
		shortlist.list = shortlist.list->next;
	}
	return nullptr;
}

void question9(List& L) {
	question6(L); //call question6 for rank list
	lNode* q = L->next;
	while (q) {
		std::cout << q->data << " ";
		lNode* t = q->next;
		delete q;
		q = t;
	}
	delete L;
}

List question10(List& LA) {
	lNode* LB = new lNode{0,nullptr};
	lNode* tailA = LA, *tailB = LB;
	lNode* q = LA->next;
	LA->next = nullptr;
	while (q) {
		lNode* t = q->next;
		if (q->data % 2 == 0) { //Even insert LB
			q->next = tailB->next;
			tailB->next = q;
			tailB = q;
		}
		else {  //Odd Insert LA
			q->next = tailA->next;
			tailA->next = q;
			tailA = q;
		}
		q = t;
	}
	return LB;
}

List question11(List& LA) {
	lNode* LB = new lNode{ 0,nullptr };
	lNode* tail = LA, *work = LA->next;
	LA->next = nullptr;
	int pos = 1;
	while (work) {
		lNode* t = work->next;
		if (pos++ % 2 == 1) { //Insert at the end of LA
			work->next = tail->next;
			tail->next = work;
			tail = work;
		}
		else {  //Insert at the front of LB
			work->next = LB->next;
			LB->next = work;
		}
		work = t;
	}
	tail->next = nullptr;
	return LB;
}

void question12(List& L) {
	lNode* work = L->next->next;
	lNode* tail = L->next;
	tail->next = nullptr;
	while (work) {
		lNode* t = work->next;
		if (work->data != tail->data) {   //Insert at end of tailnode
			work->next = tail->next;
			tail->next = work;
			tail = work;
		}
		else {   //Delete current node
			delete work;
		}
		work = t;
	}
	tail->next = nullptr;
}

void question13(List& LA, List& LB) {
	lNode* workA = LA->next, * workB = LB->next,*t=nullptr;
	LA->next = nullptr;
	while (workA && workB) {
		if (workA->data <= workB->data) //A<=B, so insert A at the front of LA
			t = workA,workA=workA->next;
		else                            //Else insert B at the front of LA
			t = workB,workB=workB->next;
		t->next = LA->next;
		LA->next = t;
	}
	while (workA) {
		t = workA->next;
		workA->next = LA->next;
		LA->next = workA;
		workA = t;
	}
	while (workB) {
		t = workB->next;
		workB->next = LA->next;
		LA->next = workB;
		workB = t;
	}
	LB->next = LA->next;
}

List question14(List& LA, List& LB) {
	lNode* workA = LA->next, *workB = LB->next;
	lNode* LC = new lNode{ 0,nullptr };
	lNode* tail = LC;
	while (workA && workB) {
		if (workA->data < workB->data) //A<B, so pointer workA take a step backward
			workA = workA->next;
		else if (workB->data < workA->data) //B<A,so does it
			workB = workB->next;
		else { //A=B,put the equal data on the end of LC, and pointer workA and workB take a step backward together
			lNode* newnode = new lNode;
			newnode->data = workA->data;
			newnode->next = tail->next;
			tail->next = newnode;
			tail = newnode;
			workA = workA->next;
			workB = workB->next;
		}
	}
	tail->next = nullptr;
	return LC;
}

void question15(List& LA, List& LB) {
	lNode* workA = LA->next, * workB = LB->next;
	lNode* workC = LA;
	workC->data = 0x7fffffff, workC->next = nullptr;
	while (workA && workB) {
		lNode* ta = workA->next, * tb = workB->next;
		if (workA->data > workB->data) {
			delete workB;
			workB = tb;
		}
		else if (workA->data < workB->data) {
			delete workA;
			workA = ta;
		}
		else if(workA->data == workB->data && workA->data== workC->data){   //delete node A and B
			delete workA, workB;
			workA = ta, workB = tb;
		}
		else { //A=B,and A!=C,put A at the end of LC,then delte B
			workA->next = workC->next;
			workC->next = workA;
			workC = workA;
			delete workB;
			workA = ta, workB = tb;
		}
	}
	while (workA) {
		lNode* t = workA->next;
		delete workA;
		workA = t;
	}
	while (workB) {
		lNode* t = workB->next;
		delete workB;
		workB = t;
	}
	delete LB;
	workC->next = nullptr;
}

bool question16(List& LA, List& LB) {
	lNode* workA = LA->next, * workB = LB->next;
	while (workA->data!=workB->data) { //find the first element that is equal b1
		if (!workA)    //Dont have the same element as b1,return fasle
			return false;
		workA = workA->next;
	}
	while (workB) {
		if (!workA || workA->data!=workB->data)
			return false;
		workA = workA->next;
		workB = workB->next;
	}
	return true;
}

Type question21(List& LA,int k) {
	if (k <= 0) return 0;
	lNode* work = LA->next, * ret = LA->next;
	int pos = 1;
	while (pos++<=k && work) {
		work = work->next;
	}
	if (!work) return 0;
	while (work) {
		work = work->next;
		ret = ret->next;
	}
	return ret->data;
}

Type Abs(Type x) { return x >= 0 ? x : -x; }
void question23(List&L, int n) {
	int* index = new int[n+1];
	for (int i = 0; i != n+1; i++)
		index[i] = 0;
	lNode* q = L, *p = L->next;
	q->next = nullptr;
	while (p) {
		lNode* t = p->next;
		if (index[Abs(p->data)] == 0) {
			index[Abs(p->data)] = 1;
			p->next = q->next;
			q->next = p;
			q = p;
		}
		else {
			delete p;
		}
		p = t;
	}
	delete[]index;
}

void question25(List& L) {
	int len = 0,pos=0;
	lNode* p = L->next;
	while (p) {  //Get length of list
		len++;
		p = p->next;
	}
	lNode* L1 = new lNode{ 0,nullptr };
	p = L->next;
	while (p) {
		lNode* node = p->next;
		if (++pos > ((len+1 )/ 2))  {  //Put p at the head of L1
			p->next = L1->next;
			L1->next = p;
		}
		p = node;
	}
	lNode* q = L1->next;
	p = L->next;
	while (q && p) {
		lNode* t1 = q->next, * t2 = p->next;
		q->next = p->next;
		p->next = q;
		q = t1, p = t2;
	}
	p->next = nullptr;
	delete L1;


}
#endif

