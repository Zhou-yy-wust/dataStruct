#pragma once
#ifndef SORTALGORITHM_H
#define SORTALGOTITHM_H
#include"LinearList.h"
template<typename T>
void InsertSort(T*A, int n) {  
	//直接插入排序，A[0]视为初始有序表，将后序元素依次插入,
	//最好时间复杂度遍历表O[n]，平均时间复杂度O[n2]，空间复杂度O[1]
	//稳定性算法，但当判断条件改变后可变为不稳定性算法
	//适用于顺序表、链表，链表需从头开始查找插入位置
	int i=0, j=0;
	for (int i = 1; i != n; i++) {
		if ( A[i - 1]>A[i]) {
			T t = A[i];
			for (int j = i - 1; j >= 0 && A[j]>t; j--)
				A[j + 1] = A[j];
			A[j+1] = A[i];
		}
	}
}

template<typename T>
void InsertSort_Binary(T* A, int n) {
	//在直接插入排序的基础上，查找插入位置使用折半查找
	//平均时间复杂度，由于依然要移动位置，所以为O[n2]，空间复杂度O[1]
	//稳定性算法
	//仅仅适用于顺序表
	int i = 0, j = 0,low=0,high=0,mid=0;
	for (int i = 1; i != n; i++) {
		if (A[i - 1] > A[i]) { //执行折半插入，也可省略判断条件，直接折半插入
			low = 0, high = i - 1;
			T t = A[i];
			while (low <= high) {
				mid = (low + high) / 2;
				if (A[mid] > t)
					high = mid - 1;
				else
					low = mid + 1;
			}
			//插入位置在high+1，总是位于low与high之间，又跳出循环有high<low；
			for (int j = i - 1; j >= high + 1; j++)
				A[j + 1] = A[j];
			A[high + 1] = t;
		}
	}
}

template<typename T>
void ShellSort(T* A, int n) {
	//将表分为几个步长为d的几个子表，对子表进行插入排序
	//时间复杂度O[n2]，空间复杂度O[1]
	//不稳定算法，因为相等的几个值将在不同的子表中排序
	//仅适用于顺序表
	int j = 0;
	for (int dk = n / 2; dk != 0; dk /= 2) {
		for (int i = dk; i != n; i++)
			if (A[i] < A[i - dk]) {//执行插入算法
				T t= A[i];
				for (j = i - dk; j >= 0 && A[j] > t; j -= dk)
					A[j + dk] = A[j];
				A[j+dk] = t;
			}
	}
}

template <typename T>
void BubbleSort(T *A, int n) {
	//冒泡排序，每次冒泡都使得一个最大值或最小值处于最终位置
	//最好时间复杂度冒泡依次退出，O[n]；平均时间复杂度O[n2]，空间复杂度O[1]
	//稳定性算法
	for (int i = 0; i != n-1; i++) {
		bool flag = false;
		for(int j =n-1;j!=i;j--)
			if (A[j] < A[j - 1]) {
				T t = A[j];
				A[j] = A[j - 1], A[j - 1] = t;
				flag = true;
			}
		if (!flag)
			break;
	}
}

template<typename T>
int Partition(T* A, int low, int high) {
	T pivot = A[low];
	std::cout << "\nPivot = " << pivot << ", Compare : ";
	while (low < high) {
		while (high > low && A[high]>=pivot && std::cout<<A[high]<<" ") high--; 
		A[low] = A[high];
		while (high > low && A[low]<=pivot && std::cout << A[low] << " ")  low++;
		A[high] = A[low];
	}
	A[low] = pivot;
	return low;
}

template<typename T>
int Partition_Random(T* A, int low, int high) {
	int pivot_pos = rand() % (high - low+1) + low;
	T pivot = A[pivot_pos];
	A[pivot_pos] = A[low], A[low] = pivot;
	while (low < high) {
		while (low < high && A[high] >= pivot) high--;
		A[low] = A[high];
		while (low < high && A[low] <= pivot) low++;
		A[high] = A[low];
	}
}

template<typename T>
void QuickSort(T* A, int low, int high) {
	//基于分治法，根据pivot将表划分为两个子表，左子表<pivot,右子表>pivot，然后递归
	//最坏时间复杂度O[n2],最好时间复杂度O[nlogn]，最好空间复杂度O[logn],最坏O[n]
	//不稳定算法
	if (low >= high) return;
		int pivot_pos = Partition(A, low, high);
		QuickSort(A, low, pivot_pos - 1);
		QuickSort(A, pivot_pos + 1, high);
}

template<typename T>
void SelectSort(T* A, int n) {
	//简单选择排序
	//时间复杂度O[n2]，空间复杂度O[1]
	//不稳定排序
	for (int i = 0; i != n - 2; i++) {
		int min_pos = i,j;
		for (int j = i; j != n - 1; j++)
			if (A[j] < A[min_pos])
				min_pos = j;
		if (min_pos == j)continue;
		T t = A[min_pos];
		A[min_pos] = A[i], A[i] = t;
	}
}

template<typename T>
void HeadAdjust(T A[], int len, int k) {
	A[0] = A[k];
	for (int i = 2 * k; i <= len; i *= 2) {
		if (i<len && A[i]<A[i + 1])
			i++;
		if (A[0] >= A[i]) break;
		else
			A[k] = A[i], k = i;
	}
	A[k] = A[0];
}

template<typename T>
void HeapSort(T A[],int len) {
	//堆排序，建堆时间复杂度O[n],下调时间复杂度O[nlogn],总时间复杂度O[nlogn]
	//不稳定算法
	BuildMaxHeap(A, len);
	for (int i = len; i > 1; i--) {
		T t = A[i];
		A[i] = A[1], A[1] = t;
		HeadAdjust(A, i - 1, 1);
	}
}

template<typename T>
void BuildMaxHeap(T A[], int len) {
	for (int i = len / 2; i != 0; i--)
		HeadAdjust(A, len, i);
}

/*
* Heap
*/
typedef enum{MAX,MIN}Heap_Type;
template <typename T> class Heap {
public:
	Heap(T* data, unsigned len,Heap_Type Type);
	//Heap(T* data, unsigned len) { Heap(data, len, MAX); }
	void BuildHeap();
	void HeapSort();
	void Insert(const T&);
	void Delete();
	void print();
private:
	Dynamic_List<T> list;
	T* heap = list.GetList();
	unsigned element_num = 0;
	Heap_Type type;
	void AdjustHeap(unsigned root,unsigned len);
};

template<typename T>
Heap<T>::Heap(T* data, unsigned len,Heap_Type Type ):list(len) {
	element_num = len;
	for (int pos = 1; pos <= len; pos++)
		list.Insert(data[pos - 1], pos+1);
	heap = list.GetList();
	type = Type;

	//建堆
	BuildHeap();
}

template<typename T>
void Heap<T>::BuildHeap() {
	for (int root = element_num / 2; root != 0; root--)
		AdjustHeap(root,element_num);
}

template<typename T>
void Heap<T>::AdjustHeap(unsigned root,unsigned len) {
	heap[0] = heap[root];
	if (type == MAX) {
		for (int r = root; r <= len; r *= 2) {
			if (r < len && heap[r] < heap[r + 1])
				r++;
			if (heap[0] > heap[r]) break;
			heap[root] = heap[r], root = r;
		}
	}
	else
		for (int r = root; r <= len; r *= 2) {
			if (r < len && heap[r] > heap[r + 1])
				r++;
			if (heap[0] < heap[r]) break;
			heap[root] = heap[r], root = r;
		}
	heap[root] = heap[0];
}

template<typename T>
void Heap<T>::HeapSort() {
	for (int pos = element_num; pos != 1; pos--) {
		heap[0] = heap[1];
		heap[1] = heap[pos];
		heap[pos] = heap[0];
		AdjustHeap(1, pos-1);
	}
}

template<typename T>
void Heap<T>::Insert(const T& t) {
	element_num++;
	list.Insert(t,element_num + 1);
	heap = list.GetList();
	for (int parent = element_num / 2, child = element_num; parent >= 1; parent /= 2)
		if (type == MAX && heap[parent] >= heap[child] || type == MIN && heap[parent] <= heap[child])
			break;
		else {
			heap[0] = heap[parent], heap[parent] = heap[child], heap[child] = heap[0];
			child = parent;
		}
			
}

template<typename T>
void Heap<T>::Delete() {
	heap[1] = heap[element_num--];
	AdjustHeap(1, element_num);
}

template<typename T>
void Heap<T>::print() {
	int p = 1, level = 0, count = 10;
	while (p <= element_num) {
		level++;
		for (int i = 1; i <= 1 << (level - 1) && p<=element_num; i++, p++)
			std::cout << heap[p] << "  ";
		std::cout << std::endl;
	}
}

/*
* 
* 
* 
*/
template<typename T>
void Merge(T*A, int low, int mid, int high) {
	T* B = new T[high - low + 1];
	for (int i = low; i <= high; i++)
		B[i - low] = A[i];
	int p1 = 0, p2 = low + 1, p3 = low;
	while (p1 <= low && p2 <= high) {
		if (B[p1] <= B[p2])
			A[p3++] = B[p1]++;
		else
			A[p3++] = B[p2++];
	}
	while (p1 <= low) A[p3++] = B[p1++];
	while (p2 <= high) A[p3++] = B[p2++];
	delete []B;
}

template<typename T>
void MergeSort(T* A, int low, int high) {
	if (low >= high) return;
	int mid = (low + high) / 2;
	MergeSort(A, low, mid);
	MergeSort(A, mid + 1, high);
	Merge(A, low, mid, high);
}



/*
* 
* 
*/

template<typename T>
void Bothway_BubbleSort(T* A, int n) {
	int start = 0, end = n - 1;
	while (start < end) {
		bool flag = false;
		for (int i = end; i != start; i--) 
			if (A[i] < A[i - 1]) {
				T t = A[i];
				A[i] = A[i - 1], A[i - 1] = t;
				flag = true;
			}
		start++;
		for (int i = start; i != end; i++) 
			if (A[i] > A[i + 1]) {
				T t = A[i];
				A[i] = A[i + 1], A[i + 1] = t;
				flag = true;
			}
		end--;
		if (!flag)
			break;
	}
}

void Odds_Before_Evens(int* A, int n) {
	int low = 0, high = n - 1;
	while (low < high) {
		while (low < high && A[low] % 2 != 0) low++; //找到第一个偶数
		int t = A[low];
		while (high > low && A[high] % 2 == 0) high--; //找到最后一个奇数
		A[low] = A[high], A[high] = t;
	}
}

int question6(int* A, int n) {
	//重点如果不实用递归，找寻第K个位置需要两个变量记录正在执行快排操作的其实地址
	//快排优势，当只有整体需要排序，而某一小整体并不需要排序时便可适用
	//例如找寻第k小元素，并不关心k之前的元素如何排列，也不关心k之后的元素如何排列；
	//实现方法，递归于非递归，重点掌握非递归，因为不需要空间复杂度。
	int pivot = 0, low = 0, cur_low = 0, high = n - 1, cur_high = n - 1;
	while (cur_low < cur_high) {
		low = cur_low, high = cur_high;
		pivot = A[cur_low];
		while (low < high) {
			while (low < high && A[high] >= pivot) high--;
			A[low] = A[high];
			while (low < high && A[low] <= pivot) low++;
			A[high] = A[low];
		}
		A[low] = pivot;
		if (low == n / 2 - 1) break;
		if (low > n / 2 - 1)
			cur_high = low - 1;
		else
			cur_low = low + 1;
	}

	int sum1 = 0, sum2 = 0;
	for (int i = 0; i != n / 2; i++) sum1 += A[i];
	for (int i = n / 2; i != n; i++) sum2 += A[i];
	return sum2 - sum1;
}

enum color{RED,WHITE,BLUE} ;
void Flag_Arrange(color* A, int n) {
	int red_p = 0, work = 0, blue_p = n - 1;
	while (work <= blue_p) {
		color t = A[work];
		switch (A[work]) {
		case RED: A[work] = A[red_p], A[red_p] = t, red_p++;
			break;
		case BLUE:A[work] = A[blue_p], A[blue_p] = t, red_p++;
			break;
		case WHITE:work++;
		}
	}
}

#endif
