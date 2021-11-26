#pragma once
#ifndef GRAPH_H
#define GRAPH_H
#include<iostream>
#include"LinearList.h"
#include"Union_find_Sets.h"
constexpr int Inf = 0x0fffffff;
using VertexType = char;
using EdgeType = int;
/*
* ÁÚ½Ó¾ØÕó
*/
struct MGraph {
	MGraph() :Vex(nullptr), Edge(nullptr) {};
	~MGraph();
	void Initialize();
	VertexType FirstNeighbor(VertexType v);
	VertexType NextNeighbor(VertexType v, VertexType w);
	void BFSTraverse(const VertexType& );
	void DFSTraverse(const VertexType&);
	EdgeType Prim(VertexType);
	EdgeType* Dijkstra(VertexType);
	bool IsTree();
	VertexType* TopoSort();
	int ComponentCount();
	bool HasACyclic();
	void Transposition();
	int Kosaroju();
private:
	VertexType *Vex;
	EdgeType **Edge;
	int vexnum = 0;
	int Getpos(VertexType );
	void BFS(VertexType, bool*);
	void DFS(VertexType, bool*);
	void DFS_Kosaroju(VertexType, bool*,LStack<VertexType> &);
	void DFS_Kosaroju_reverse(VertexType , bool* , int*,int );
	void Putout(int*,int);
	void DFS(VertexType,bool*, int& Vnum, int& Enum);
	void DFS_NR(VertexType);
	void Show_Path(EdgeType*,VertexType*, VertexType);
	void Degree(int*);
	
};



/*
* ÁÚ½Ó±í
*/
struct ArcNode {
	VertexType Vex=0;
	int info=0;
	ArcNode* next=nullptr;
};

struct VNode {
	VertexType Vex=0;
	ArcNode* first=nullptr;
};

struct ALGraph {
	ALGraph() :vertices(nullptr),vexnum(0),arcnum(0) {};
	ALGraph(VNode* p, int vex, int arc) :vertices(p), vexnum(vex), arcnum(arc) {};

	VertexType FirstNeighbor(const VertexType&);
	VertexType NextNeighbor(const VertexType&, const VertexType&);
	void FindPath(const VertexType&, const VertexType&);

	void BFSTraverse(const VertexType&);
	void DFSTraverse(const VertexType&);
	void DFS_NR(VertexType t);
	void Initialize();

private:
	VNode* vertices;
	int vexnum, arcnum;
	int Getpos(const VertexType&);
	void BFS(VertexType, bool*);
	void DFS(VertexType, bool*);
	void find_path(const VertexType&, const VertexType&,VertexType*path,bool *visit,int distance);
	void ShowPath(VertexType*, int);
};



#endif
