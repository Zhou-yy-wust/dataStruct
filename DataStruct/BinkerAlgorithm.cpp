#include "BinkerAlgorithm.h"

void Main() {
	int n = 5, m = 3;
	int** Max = nullptr, ** Allocation = nullptr, * Avaliable = nullptr;
	Initialize(Max, Allocation, Avaliable, n, m);
	Banker_Algorithm(Max, Allocation, Avaliable, n, m);
}

void Initialize(int**& Max, int**& Allocation, int*& Avaliable, int n, int m) {
	Max = new int* [n];
	for (int i = 0; i != n; i++)
		Max[i] = new int[m];
	Allocation = new int* [n];
	for (int i = 0; i != n; i++)
		Allocation[i] = new int[m];
	Avaliable = new int[m];



	int t = 0;
	std::cout << "Input the maximun need martrix( " << n
		<< " rows and " << m << "columns):" << std::endl;
	for (int i = 0; i != n; i++)
		for (int j = 0; j != m; j++) {
			if (!(std::cin >> t)) return;
			Max[i][j] = t;
		}
	std::cout << "The maximun need martrix has been initailized."
		"\nThe following input allocation martrix:" << std::endl;
	for (int i = 0; i != n; i++)
		for (int j = 0; j != m; j++) {
			if (!(std::cin >> t))
				return;
			Allocation[i][j] = t;
		}
	std::cout << "The allocation martrix has been initialized."
		"\nThe following input avaliable vector(" << m << "):" << std::endl;
	for (int i = 0; i != m; i++) {
		if (!(std::cin >> t))
			return;
		Avaliable[i] = t;
	}

}

void Banker_Algorithm(int** Max, int** Allocation, int* Avaliable, int n, int m) {
	int** Need = new int* [n];
	for (int i = 0; i != n; i++)
		Need[i] = new int[m];
	SubMatrix(Need, Max, Allocation, n, m);
	int* Requests = new int[m];
	int k = 0;
	while (1) {
		k = GetRequestion(Requests, m);
		if (k < 0) break;
		if (!IsGreater(Need[k], Requests, m) || !IsGreater(Avaliable, Requests, m)) {
			std::cout << "The currently allocated resource request is invalid" << std::endl;
			return;
		}
		//Predistribution
		AddVector(Allocation[k], Allocation[k], Requests, m);
		SubVector(Need[k], Need[k], Requests, m);
		SubVector(Avaliable, Avaliable, Requests, m);
		if (!Security(Need, Allocation, Avaliable, n, m)) {
			SubVector(Allocation[k], Allocation[k], Requests, m);
			AddVector(Need[k], Need[k], Requests, m);
			AddVector(Avaliable, Avaliable, Requests, m);
		}
	}
	Delete(Max, Allocation, Need, Avaliable, Requests, n, m);
}

void AddMatrix(int** sum, int** augend, int** addend, int row, int column) {
	for (int i = 0; i != row; i++)
		AddVector(sum[i], augend[i], addend[i], column);
}

void SubMatrix(int** diff, int** minuend, int** subtrahend, int row, int column) {
	for (int i = 0; i != row; i++)
		SubVector(diff[i], minuend[i], subtrahend[i], column);
}

void AddVector(int* sum, int* augend, int* addend, int n) {
	for (int i = 0; i != n; i++)
		sum[i] = augend[i] + addend[i];
}

void SubVector(int* diff, int* minuend, int* subtrahend, int n) {
	for (int i = 0; i != n; i++)
		diff[i] = minuend[i] - subtrahend[i];
}

int GetRequestion(int* Requests, int n) {
	int t, k;
	std::cout << "Which process requirement is this(enter -1 to exit):";
	std::cin >> k;
	if (k == -1) return k;
	std::cout << "\nPlease enter the current resource request(" << n << "):" << std::endl;
	for (int i = 0; i != n; i++) {
		if (!(std::cin >> t))
			return 0;
		Requests[i] = t;
	}
	return k;
}

bool IsGreater(int* A, int* B, int n) {
	for (int i = 0; i != n; i++)
		if (A[i] < B[i])
			return false;
	return true;
}

void Delete(int** Max, int** Allocation, int** Need, int* Avaliable, int* Requests, int n, int m) {
	delete[]Avaliable;
	delete[] Requests;
	for (int i = 0; i != n; i++) {
		delete[]Max[i];
		delete[]Allocation[i];
		delete[]Need[i];
	}
	delete[] Max;
	delete[]Allocation;
	delete[]Need;
}

bool Security(int** Need, int** Allocation, int* Avaliable, int n, int m) {
	int* seq = new int[n]; //记录分配顺序
	int** allocseq = new int* [n]; //记录分配数量
	for (int i = 0; i != n; i++)
		allocseq[i] = new int[m];
	int* A = new int[n];
	for (int i = 0; i != n; i++)
		A[i] = 0;
	int* Work = new int[m];
	for (int i = 0; i != m; i++)
		Work[i] = Avaliable[i];

	bool search = false;
	for (int i = 0; i != n; i++) {
		search = false;
		for (int j = 0; j != n; j++) {
			if (!A[j])    //第j个进程未被分配
				if (IsGreater(Work, Need[j], m)) {  //找到需求小于空闲的进程j
					A[j] = 1;
					search = true;
					AddVector(Work, Work, Allocation[j], m);
					for (int k = 0; k != m; k++)
						allocseq[i][k] = Need[j][k];
					seq[i] = j;
					break;
				}
		}
		if (!search)
			break;
	}

	if (search) {  //分配成功
		std::cout << "The system is in the safe state." << std::endl;
		std::cout << "The order of assignment is as follows:" << std::endl;
		for (int i = 0; i != n; i++) {
			std::cout << "Process: " << seq[i] << ",   Allocated: ";
			for (int j = 0; j != m; j++) {
				std::cout << allocseq[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
	else   //分配失败
		std::cout << "The system is in the unsafe state." << std::endl;

	for (int i = 0; i != n; i++) //删除辅助空间
		delete[]allocseq[i];
	delete[] allocseq;
	delete[]seq;
	delete[]Work;
	return search;
}

void print(int** p, int n, int m) {
	for (int i = 0; i != n; i++) {
		for (int j = 0; j != m; j++) {
			std::cout << p[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
