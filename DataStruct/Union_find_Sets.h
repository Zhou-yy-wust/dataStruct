#pragma once
#ifndef UNION_FIND_SETS
#define UNION_FIND_SETS
#include<iostream>
constexpr int Size = 100;

class Union_find_sets {
public:
	Union_find_sets() {   //���캯������ʼ����Ϊ��
		for (int i = 0; i != Size; i++) Sets[i] = 0;
		Num = Size;
	}

	Union_find_sets(int n) { //�Գ�ʼ�����鼯������Ԫ�ع��ɵ�������
		for (int i = 0; i != n; i++) Sets[i] = -1;
		Num = n;
	}

	int Find(int t) { //����t���ڼ��ϵĸ�����ѹ��·����ʽ
		if (t < 0 || t >= Size) return -1;
		int root = t, k;
		while (Sets[root] >= 0)
			root = Sets[root];
		while (t != root) { //������·���ϵ����н��ֱ�ӹ��ڸ��ϣ�ѹ��·��
			k = Sets[t];
			Sets[t] = root;
			t = k;
		}
		
		return root;
	}

	void Union(int root1, int root2) { //�ϲ���root1��root2Ϊ���ļ��ϣ���ȡС���ҵ�������
		if (root1 < 0 || root2 < 0 || root1 >= Size || root2 >= Size || root1==root2) return;
		if (Sets[root1] < Sets[root2]) {  //root1���ϴ�root2�ϲ���root1
			Sets[root1] += Sets[root2];
			Sets[root2] = root1;
		}
		else {
			Sets[root2] += Sets[root1];
			Sets[root1] = root2;
		}
		return;
	}

	void print() { //��ӡ�������
		bool *visit=new bool[Num];
		for (int i=0;i!=Num;i++)
			visit[i] = false;
		int p = 0;
		while (p < Num) {
			if (Sets[p] < 0) {
				std::cout << "Sets:"<<p<<" ,Size:" << -Sets[p] << " ,Elments: " ;
				for(int i=0;i!=Num;i++)
					if (!visit[i] && Find(i) == p) {
						visit[i] = true;
						std::cout << i << " ";
					}
				std::cout << std::endl;
			}
			p++;
		}
	}

	int GetElement(int pos) { return Sets[pos]; }
	int GetSize() { return Num; }

private:
	int Sets[Size];
	int Num = 0;
};



#endif
