#pragma once
#ifndef CHAPTER2_2_3_H
#define CHAPTER2_2_3_H
#include<iostream>
constexpr int STACK_MAXSIZE = 50;

typedef struct {
	int data[STACK_MAXSIZE];
	int length ;
}Sqlist;

void print(const Sqlist& list) {
	if (list.length <= 0)
		std::cout << "The list is Empty!" << std::endl;
	std::cout << "The content of list:" << std::endl;
	for (int p = 0; p != list.length; p++) {
		std::cout << list.data[p] << " ";
		if ((p + 1) % 10 == 0 && p!=list.length-1)
			std::cout << std::endl;
	}
	std::cout << "\nThe length of list: " << list.length << std::endl;
}

int question1(Sqlist& list) {
	if (list.length <= 0)
		exit(-1);
	int min = 100, pos = 0;
	for (int p = 0; p != list.length; p++) { //Find mininum value and its position
		if (list.data[p] < min) {
			min = list.data[p];
			pos = p;
		}
	}

	list.data[pos] = list.data[--list.length]; //Detele
	return min;
}

void question2(Sqlist& list) {
	if (list.length <= 0) exit(-1);
	int front = 0, rear = list.length - 1;
	while (front <= rear) {     //until front above rear
		int temp = list.data[front];
		list.data[front] = list.data[rear];
		list.data[rear] = temp;
		front++, rear--;
	}
}

void question3(Sqlist& list,int x) {
	if (list.length <= 0) exit(-1);
	int p = 0, count = 0;
	while ((p + count) != list.length) {
		list.data[p] = list.data[p + count];
		if (list.data[p] == x) {
			count++;
			list.data[p] = list.data[p+count];
			continue;
		}
		p++;
	}
	list.length -= count;
}

void question4(Sqlist& list, int s, int t) {
	if (list.length == 0 || s >= t) exit(-1);
	int p = 0, q = 0;
	while (q != list.length) {
		if (list.data[p] < s)
			p++;
		if (list.data[q] <= t) {
			q++;
			continue;
		}
		list.data[p++] = list.data[q++];
	}
	list.length -= (q - p);
}

void question5(Sqlist& list, int s, int t) {
	if (list.length == 0 || s >= t) exit(-1);
	int p = 0, count = 0;
	while (p + count != list.length) {
		list.data[p] = list.data[p + count];
		if (list.data[p] >= s && list.data[p] <= t) {
			count++;
			continue;
		}
		p++;
	}
	list.length -= count;
}

void question6(Sqlist& list) {
	if (list.length == 0) exit(-1);
	Sqlist temp;
	int p = 0, q = 0;
	temp.data[q] = list.data[p];
	while (p != list.length) {
		if (list.data[p] == temp.data[q]) {
			p++;
			continue;
		}
		temp.data[++q] = list.data[p++];
	}
	for (int i = 0;  i != q;i++) 
		list.data[i] = temp.data[i];
	list.length = q;
}

Sqlist question7(const Sqlist& list1, const Sqlist& list2) {
	if ((list1.length | list2.length) == 0) exit(-1);
	Sqlist result;
	int p = 0, q = 0, r = 0;
	while (p != list1.length && q != list2.length) {
		if (list1.data[p] <= list2.data[q])
			result.data[r++] = list1.data[p++];
		else
			result.data[r++] = list2.data[q++];
	}
	while (p != list1.length)
		result.data[r++] = list1.data[p++];
	while (q != list2.length)
		result.data[r++] = list2.data[q++];
	result.length = r;
	return result;
}


void Traverse(int* arr, int start, int end) {
	while (start <= end) {
		int temp = arr[start - 1];
		arr[start - 1] = arr[end - 1];
		arr[end - 1] = temp;
		start++, end--;
	}
}
void question8(int* arr, int n, int m) {
	if (n <= 0 || m <= 0) exit(-1);
	Traverse(arr, 1, n + m);
	Traverse(arr, 1, n);
	Traverse(arr, n + 1, n + m);
}

int question9(Sqlist& list, int x) {
	int start = 0, end = list.length - 1, mid ;
	while (start <= end) {
		mid = (start + end) / 2;
		if (list.data[mid] == x)
			return mid;
		if (list.data[mid] > x)
			end = mid - 1;
		else
			start = mid + 1;
	}
	for (int p = list.length ; p >= start+1;p--) {
		list.data[p ] = list.data[p-1];
	}
	list.data[start] = x;
	list.length++;
	return -1;
}

/*
* Question 10 on page 18, time complexity is O(n),
* space complexity is O(1)
*/
void question10(int* arr, int n, int p) {
	if (n <= 0 || p <= 0) exit(-1);
	Traverse(arr, 1, n );
	Traverse(arr, 1, n-p);
	Traverse(arr, n -p+1, n );
}

/*
* Question 11 on page 18, time complexity is O(n),
* space complexity is O(1)
*/
int question11(int* arr1, int n1, int* arr2, int n2) {
	int p1 = 0, p2 = 0, count = 0;
	int ret=0;
	while (p1 < n1 && p2 < n2 && count<(n1+n2+1)/2) {
		if (arr1[p1] < arr2[p2])
			ret = arr1[p1++];
		else
			ret = arr2[p2++];
		count++;
	}
	if (count != (n1 + n2) / 2) {
		if (p1 == n1)
			ret = arr2[p2 + (n1 + n2+1) / 2 - count];
		if(p2==n2)
			ret = arr1[p1 + (n1 + n2+1) / 2 - count];
	}
	return ret;
}

/*
* Question 12 on page 18, time complexity is O(n),
* space complexity is O(1)
*/
int question12( int* arr,int n ){
	int count = 1, t = arr[0];
	for (int p = 1; p != n; p++) {
		if (arr[p] != t)
			count--;
		else
			count++;
		if (count < 0) {
		   count=1, t = arr[p];
		}
	}
	if (count > 0)
		return t;
	exit(-1);
}

/*
* Question 13 on page 18, time complexity is O(n),
* space complexity is O(n)
*/
int question13(int* arr, int n) {
	int* ptr = new int[n];
	for (int p = 0; p != n; p++)
		ptr[p] = 1;
	for (int p = 0; p != n; p++) 
		if (0 < arr[p] && arr[p]<= n)
			ptr[arr[p]-1] = 0;
	int p = 0;
	while (ptr[p] == 0)
		p++;
	delete[] ptr;
	return p + 1;
}

/*
* Question 14 on page 18, time complexity is O(n1*log(max(n2,n3))), 
* space complexity is O(1)
*/
struct Traid {
	int a; int b; int c;
};

int Distance(Traid t) {
	int t1 = ((t.a - t.b) > 0) ? (t.a - t.b) : (t.b - t.a);
	int t2 = ((t.a - t.c) > 0) ? (t.a - t.c) : (t.c - t.a);
	int t3 = ((t.c - t.b) > 0) ? (t.c - t.b) : (t.b - t.c);
	return t1 + t2 + t3;
}

int FindPos(int* arr, int n, int x) {
	int head = 0, end = n - 1, mid=0;
	while (head <= end) {
		mid = (head + end) / 2;
		if (arr[mid] == x)
			return mid;
		if (arr[mid] > x)
			end = mid - 1;
		else
			head = mid + 1;
	}
	return mid;
}

int Min(int a, int b) {
	return (a > b) ? b : a;
}

int question14(int *arr1,int n1,int *arr2,int n2,int *arr3,int n3) {
	int min = 100;
	for (int p1 = 0; p1 != n1; p1++) {
		int a = arr1[p1];
		int pos2 = FindPos(arr2, n2, a);
		int pos3 = FindPos(arr3, n3, a);
		Traid t1 = { a,arr2[pos2],arr3[pos3] };
		min = Min(min, Distance(t1));
		if (pos2 + 1 != n2) {
			Traid t2 = { a,arr2[pos2 + 1],arr3[pos3] };
			min = Min(min, Distance(t2));
		}
		if (pos3 + 1 != n3) {
			Traid t2 = { a,arr2[pos2 ],arr3[pos3+1] };
			min = Min(min, Distance(t2));
		}
		if (pos2 + 1 != n2 && pos3 + 1 != n3) {
			Traid t2 = { a,arr2[pos2 + 1],arr3[pos3+1] };
			min = Min(min, Distance(t2));
		}
	}
	return min;
}
#endif
