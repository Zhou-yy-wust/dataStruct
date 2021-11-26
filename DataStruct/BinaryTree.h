#pragma once
#ifndef BINARYTREE_H
#define BINARYTREE_H
#include<iostream>
#include"LinearList.h"
constexpr int MAXSIZE = 50;
constexpr int nul = 0x80000000;
using Type = char;
using SSBinarytTree = Type*;
void Initialize_SSBinaryTree(SSBinarytTree& tree, int n);

struct TreeNode {
	Type data;
	TreeNode* left, * right;
};

class BinaryTree {
public:
	BinaryTree() :tree(nullptr) {}
	BinaryTree(TreeNode* p) :tree(p) {}

	void Initialize() { initialize(tree); }

	TreeNode* PreInCreat(Type*, Type*, int);

	void Pre2Post_FullTree(Type*, Type* , int);
	
	TreeNode* LeafLink();

	void PrePrint() { preprint(tree); }
	void PrePrint_NR();
	
	Type Preorder_K(int );

	void InPrint() { inprint(tree); }
	void InPrint_NR();

	void PostPrint() { postprint(tree); }
	void PostPrint_NR();

	void Print_x_Ancestor(Type );
	
	void LevelPrint();
	void LevelPrint_R2L();
	
	void Print_Data_Equal_k(Type k);
	
	int GetHight() { return gethight(tree); }
	int GetHight_NR();
	
	int GetLeafSize() { return get_leaf_size(tree); }

	int GetBranchSize() { return get_branch_size(tree); }

	int GetLevelSuze(int x) { return get_level_size(tree, x); }

	int GetWidth();

	int GetWPL() { return get_wpl(tree, 1); }
	
	bool IsComplete();

	TreeNode* Ancestor(TreeNode*, TreeNode*);

	bool IsSimilar(TreeNode* tree1) { return is_similar(tree, tree1); }

	bool IsBST();
	
	TreeNode* GetParent(TreeNode* child) {return  get_parent(tree, child); }

	TreeNode* FindElement(const Type t) { return find_element(tree, t); }
	
	void ExchangeNode() { exchange_node(tree); }
	
	void Get_InfixExpre() { get_infix_expre(tree); }
	void Get_InfixExpre_NR();
	
	void Destroy(TreeNode*);
	void Destroy_x_root(TreeNode*&, Type x);
private:
	TreeNode* tree;

	void initialize(TreeNode*&);

	TreeNode* pre_in_creat(Type*, int, int, Type*, int, int);

	void pre2post_fulltree(Type*, int, int, Type*, int, int);

	void preprint(TreeNode*);

	Type preorder_k(TreeNode*, int& k);

	void inprint(TreeNode*);

	void postprint(TreeNode*);

	bool print_x_ancestor(TreeNode*, Type x);

	void print_data_equal_k(TreeNode*,Type *,int ,Type &,Type k);

	int gethight(TreeNode*);

	int get_leaf_size(TreeNode*);

	int get_branch_size(TreeNode*);

	int get_level_size(TreeNode*, int);

	int get_wpl(TreeNode*, int);

	bool ancestor(TreeNode*, TreeNode*, TreeNode*, TreeNode*& ancestor);

	bool is_similar(TreeNode*, TreeNode*);
	
	bool is_BST(TreeNode*& , TreeNode*& );

	TreeNode* get_parent(TreeNode*, TreeNode*);

	TreeNode* find_element(TreeNode*, const Type);

	void  exchange_node(TreeNode*);

	void get_infix_expre(TreeNode*);
};

/*
* Thread Yree
* 
*/

struct ThreadNode {
	Type data;
	ThreadNode* left, * right;
	int ltag = 0, rtag = 0;  //tag=0,则表示为父子关系，=1则表示前驱后继关系
};

class ThreadTree {
public:
	void Initialize() { Initialize(tree); };//先序遍历初始化，传入tree参数
	void CreatInThread();   //中序线索化
	void Inorder();         //遍历中序线索二叉树
	void CreatPreThread();  //线序线索化
	void Preorder();       //遍历先序线索二叉树
	ThreadNode* tree;
private:
	void Initialize(ThreadNode*&);
	void PreThread(ThreadNode*& post, ThreadNode*& pre);
	ThreadNode* FirstNode(ThreadNode*);
	ThreadNode* In_NextNode(ThreadNode*);
	ThreadNode* In_PreNode(ThreadNode*);
	ThreadNode* Pre_NextNode(ThreadNode*);
	void InThread(ThreadNode*& post, ThreadNode*& pre);
};

/*
* BST
* 
*/
using T = int;
struct BST_Node {
	T data;
	BST_Node* left, * right;
};


class BinarySearchTree {
public:
	BinarySearchTree() :root(nullptr) {};
	BinarySearchTree(BST_Node* p) :root(p) {};
	void Initialize();
	BST_Node* FindElement(const T&);
	BST_Node* FindElement_NR(const T&);
	bool Insert(const T&);
	bool DeleteElement(const T&);
	void Print();
	

private:
	BST_Node* root;
	BST_Node* find_element(BST_Node*, const T&);
	bool insert(BST_Node*&, const T&);
	bool delete_element(BST_Node*&, BST_Node*&,T&);
	void print(BST_Node*);
};


using AVL_Type = int;
struct AVL_Node {
	AVL_Type data;
	AVL_Node* left, * right;
};
class AVL_Tree {
public:
	AVL_Tree() :tree(nullptr){};
	AVL_Tree(AVL_Node* p) :tree(p) {};
	void Initialize();
	void Insert(const AVL_Type&);
	void Print();
	void Print_Pre();
	AVL_Node* FindElemnt(const AVL_Type &t);
private:
	AVL_Node* tree;
	int GetHight(AVL_Node*);
	int BalanceFactor(AVL_Node*);
	void Right_Rotate(AVL_Node*&);
	void Left_Rotate(AVL_Node*&);
	void ReBalance(AVL_Node*&);
	void insert(AVL_Node*&, const AVL_Type&);
	void print(AVL_Node*);
	void print_pre(AVL_Node*);
	void To_Balance(AVL_Node*&);
};



Type question_P127(SSBinarytTree tree, int pos1, int pos2);
#endif
