#include<iostream>


int Max_diff(int A[], int n) {
	int max = A[0], i = 1, maxdiff = max - A[i];
	for (i = 1; i != n; i++) {
		if (maxdiff < max - A[i]) maxdiff = max - A[i];
		std::cout <<"i="<<i<< ", max=" << max << ", maxdiff=" << maxdiff << std::endl;

		if (max < A[i]) max = A[i];
		
	}
	return maxdiff;
}

int main() {
	int A[] = { 2,4,1,16,7,5,11,9 };
	int n = sizeof(A) / sizeof(int);
	int maxdiff = Max_diff(A, n);
	std::cout << maxdiff;
}