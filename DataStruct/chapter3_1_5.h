#pragma once
#ifndef CHAPTER_3_1_5_H
#define CHARTER_3_1_5_H
#include<iostream>
#include"LinearList.h"
bool question3(char* op, int n) {
	int push = 0, pop = 0;
	for (int i = 0; i != n; i++) {
		if (op[i] == 'I')
			push++;
		else
			pop++;
		if (push < pop) {
			std::cout << "Operation illegal" << std::endl;
			return false;
		}
	}
	std::cout << "Operation legal" << std::endl;
	return true;
}

bool question4(Link_List<char> &cl) {
	LNode<char>* p1 = cl.GetElem(0), * p2 = cl.GetElem(0);
	LStack<char> s;
	while (p2 && p2->next) {
		p1 = p1->next, p2 = p2->next->next;
		s.Push(p1->data);
	}
	char c;
	(p2 == nullptr) ? p1 = p1 : p1 = p1->next;
	while (p1) {
		s.Pop(c);
		if (c != p1->data)
			return false;
		p1 = p1->next;
	}
	return true;
}

#endif
