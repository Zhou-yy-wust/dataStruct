#pragma once
#ifndef KMP_H
#define KMP_H
#include<iostream>
int question_p90(int n, int x) {
	if (n == 0)
		return 1;
	else if (n == 1)
		return 2 * x;
	else
		return 2 * x * question_p90(n - 1, x) - 2 * (n - 1) * question_p90(n - 2, x);
}

int* Next(char* str, int n) {
	int* next = new int[n];
	int i = 0, j = -1;
	next[i] = j;
	while (i < n - 1) {
		if (j == -1 || str[i] == str[j])
			next[++i] = ++j;
		else
			j = next[j];
	}
	for (int k = 0; k != n; k++)
		std::cout << next[k] << " ";
	std::cout << std::endl;
	return next;
}

int* Nextval(char* str, int n) {
	int* nextval = new int[n];
	int i = 0, j = -1;
	nextval[i] = j;
	while (i != n - 1) {
		if (j == -1 || str[i] == str[j]) {
			nextval[++i] = ++j;
			if (str[i] == str[j])
				nextval[i] = nextval[j];
		}
		else
			j = nextval[j];
	}
	for (int k = 0; k != n; k++)
		std::cout << nextval[k] << " ";
	std::cout << std::endl;
	return nextval;
}

int Index_KMP(char* str, int n, char* s, int m) {
	int* next = Nextval(s, m);
	int i = 0, j = 0;
	while (i != n && j != m) {
		if (j == -1 || str[i] == s[j])
			++i, ++j;
		else
			j = next[j];
	}
	if (j == m)
		return i - m;
	else
		return -1;
}
#endif
